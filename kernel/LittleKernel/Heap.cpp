#include "Kernel.h"



Heap& Heap::Create(uint32 start, uint32 end_addr, uint32 max, uint8 supervisor, uint8 readonly) {
	// All our assumptions are made on startAddress and endAddress being page-aligned.
    ASSERT(start%0x1000 == 0);
    ASSERT(end_addr%0x1000 == 0);
    
    MON.Write("Heap create:");
    MON.Write("\n    start        = "); MON.WriteHex(start);
    MON.Write("\n    end          = "); MON.WriteHex(end_addr);
    MON.Write("\n    max          = "); MON.WriteHex(max);
    MON.Write("\n    supervisor   = "); MON.WriteHex(supervisor);
    MON.Write("\n    readonly     = "); MON.WriteDec(readonly);
    MON.Put('\n');
    
    // Initialise the index.
    index.Place( (void*)start, HEAP_INDEX_SIZE);
    
    // Shift the start address forward to resemble where we can start putting data.
    start += sizeof(void*)*HEAP_INDEX_SIZE;

    // Make sure the start address is page-aligned.
    if ((start & 0x00000FFF) != 0) {
        start &= 0xFFFFF000;
        start += 0x1000;
    }
    // Write the start, end and max addresses into the heap structure.
    this->start_address = start;
    this->end_address = end_addr;
    this->max_address = max;
    this->supervisor = supervisor;
    this->readonly = readonly;
	
    // We start off with one large hole in the index.
    Header *hole = (Header*) start;
    hole->size = end_addr-start;
    hole->magic = HEAP_MAGIC;
    hole->is_hole = 1;
    index.Insert(*hole);
	return *this;
}
	
void* Heap::Allocate(uint32 size, uint8 page_align) {
	// Make sure we take the size of header/footer into account.
    uint32 new_size = size + sizeof(Header) + sizeof(Footer);
    // Find the smallest hole that will fit.
    int32 iterator = FindSmallestHole(new_size, page_align);

    if (iterator == -1) // If we didn't find a suitable hole
    {
        // Save some previous data.
        uint32 old_length = end_address - start_address;
        uint32 old_end_address = end_address;

        // We need to allocate some more space.
        Expand(old_length+new_size);
        uint32 new_length = end_address-start_address;

        // Find the endmost header. (Not endmost in size, but in location).
        iterator = 0;
        // Vars to hold the index of, and value of, the endmost header found so far.
        uint32 idx = -1; uint32 value = 0x0;
        while (iterator < index.GetSize())
        {
            uint32 tmp = (uint32)&index[iterator];
            if (tmp > value)
            {
                value = tmp;
                idx = iterator;
            }
            iterator++;
        }

        // If we didn't find ANY headers, we need to add one.
        if (idx == -1)
        {
            Header *header = (Header *)old_end_address;
            header->magic = HEAP_MAGIC;
            header->size = new_length - old_length;
            header->is_hole = 1;
            Footer *footer = (Footer *) (old_end_address + header->size - sizeof(Footer));
            footer->magic = HEAP_MAGIC;
            footer->header = header;
            index.Insert(*header);
        }
        else
        {
            // The last header needs adjusting.
            Header *header = &index[idx];
            header->size += new_length - old_length;
            // Rewrite the footer.
            Footer *footer = (Footer *) ( (uint32)header + header->size - sizeof(Footer) );
            footer->header = header;
            footer->magic = HEAP_MAGIC;
        }
        // We now have enough space. Recurse, and call the function again.
        return Allocate(size, page_align);
    }

    Header *orig_hole_header = &index[iterator];
    uint32 orig_hole_pos = (uint32)orig_hole_header;
    uint32 orig_hole_size = orig_hole_header->size;
    // Here we work out if we should split the hole we found into two parts.
    // Is the original hole size - requested hole size less than the overhead for adding a new hole?
    if (orig_hole_size-new_size < sizeof(Header)+sizeof(Footer))
    {
        // Then just increase the requested size to the size of the hole we found.
        size += orig_hole_size-new_size;
        new_size = orig_hole_size;
    }

    // If we need to page-align the data, do it now and make a new hole in front of our block.
    if (page_align && orig_hole_pos & 0x00000FFF)
    {
        uint32 new_location   = orig_hole_pos + 0x1000 /* page size */ - (orig_hole_pos&0xFFF) - sizeof(Header);
        Header *hole_header = (Header *)orig_hole_pos;
        hole_header->size     = 0x1000 /* page size */ - (orig_hole_pos&0xFFF) - sizeof(Header);
        hole_header->magic    = HEAP_MAGIC;
        hole_header->is_hole  = 1;
        Footer *hole_footer = (Footer *) ( (uint32)new_location - sizeof(Footer) );
        hole_footer->magic    = HEAP_MAGIC;
        hole_footer->header   = hole_header;
        orig_hole_pos         = new_location;
        orig_hole_size        = orig_hole_size - hole_header->size;
    }
    else
    {
        // Else we don't need this hole any more, delete it from the index.
        index.Remove(iterator);
    }

    // Overwrite the original header...
    Header *block_header  = (Header *)orig_hole_pos;
    block_header->magic     = HEAP_MAGIC;
    block_header->is_hole   = 0;
    block_header->size      = new_size;
    // ...And the footer
    Footer *block_footer  = (Footer *) (orig_hole_pos + sizeof(Header) + size);
    block_footer->magic     = HEAP_MAGIC;
    block_footer->header    = block_header;

    // We may need to write a new hole after the allocated block.
    // We do this only if the new hole would have positive size...
    if (orig_hole_size - new_size > 0)
    {
        Header *hole_header = (Header *) (orig_hole_pos + sizeof(Header) + size + sizeof(Footer));
        hole_header->magic    = HEAP_MAGIC;
        hole_header->is_hole  = 1;
        hole_header->size     = orig_hole_size - new_size;
        Footer *hole_footer = (Footer *) ( (uint32)hole_header + orig_hole_size - new_size - sizeof(Footer) );
        if ((uint32)hole_footer < end_address)
        {
            hole_footer->magic = HEAP_MAGIC;
            hole_footer->header = hole_header;
        }
        // Put the new hole in the index;
        index.Insert(*hole_header);
    }
    
    // ...And we're done!
    return (void *) ( (uint32)block_header+sizeof(Header) );
}

int32 Heap::FindSmallestHole(uint32 size, uint8 page_align) {
	// Find the smallest hole that will fit.
    uint32 iterator = 0;
    while (iterator < index.GetSize())
    {
        Header *header = &index[iterator];
        // If the user has requested the memory be page-aligned
        if (page_align > 0)
        {
            // Page-align the starting point of this header.
            uint32 location = (uint32)header;
            int32 offset = 0;
            if (((location+sizeof(Header)) & 0x00000FFF) != 0)
                offset = 0x1000 /* page size */  - (location+sizeof(Header))%0x1000;
            int32 hole_size = (int32)header->size - offset;
            // Can we fit now?
            if (hole_size >= (int32)size)
                break;
        }
        else if (header->size >= size)
            break;
        iterator++;
    }
    // Why did the loop exit?
    if (iterator == index.GetSize())
        return -1; // We got to the end and didn't find anything.
    else
        return iterator;
}

void Heap::Expand(uint32 new_size) {
	// Sanity check.
	MON.Write("Heap expand:");
    MON.Write("\n    start_address = "); MON.WriteHex(start_address);
    MON.Write("\n    new_size      = "); MON.WriteHex(new_size);
    MON.Write("\n    current_size  = "); MON.WriteHex(end_address - start_address);
    
    ASSERT(new_size > end_address - start_address);

    // Get the nearest following page boundary.
    if ((new_size&0x00000FFF) != 0)
    {
        new_size &= 0xFFFFF000;
        new_size += 0x1000;
    }

    // Make sure we are not overreaching ourselves.
    MON.Write("\n    new_end       = "); MON.WriteHex(start_address+new_size);
    MON.Write("\n    max_end       = "); MON.WriteHex(max_address);
    MON.Put('\n');
    ASSERT(start_address+new_size <= max_address);

    // This should always be on a page boundary.
    uint32 old_size = end_address-start_address;

    uint32 i = old_size;
    while (i < new_size) {
        AllocFrame( GetPage(start_address+i, 1, global->kernel_directory),
                     (supervisor)?1:0, (readonly)?0:1);
        i += 0x1000 /* page size */;
    }
    end_address = start_address+new_size;
}

uint32 Heap::Contract(uint32 new_size) {
	// Sanity check.
    ASSERT(new_size < end_address-start_address);

    // Get the nearest following page boundary.
    if (new_size&0x1000)
    {
        new_size &= 0x1000;
        new_size += 0x1000;
    }

    // Don't contract too far!
    if (new_size < HEAP_MIN_SIZE)
        new_size = HEAP_MIN_SIZE;

    uint32 old_size = end_address-start_address;
    uint32 i = old_size - 0x1000;
    while (new_size < i)
    {
        FreeFrame(GetPage(start_address+i, 0, global->kernel_directory));
        i -= 0x1000;
    }

    end_address = start_address + new_size;
    return new_size;
}

void Heap::Free(void *p) {
	// Exit gracefully for null pointers.
    if (p == 0)
        return;

    // Get the header and footer associated with this pointer.
    Header *header = (Header*) ( (uint32)p - sizeof(Header) );
    Footer *footer = (Footer*) ( (uint32)header + header->size - sizeof(Footer) );

    // Sanity checks.
    ASSERT(header->magic == HEAP_MAGIC);
    ASSERT(footer->magic == HEAP_MAGIC);

    // Make us a hole.
    header->is_hole = 1;

    // Do we want to add this header into the 'free holes' index?
    char do_add = 1;

    // Unify left
    // If the thing immediately to the left of us is a footer...
    Footer *test_footer = (Footer*) ( (uint32)header - sizeof(Footer) );
    if (test_footer->magic == HEAP_MAGIC &&
        test_footer->header->is_hole == 1)
    {
        uint32 cache_size = header->size; // Cache our current size.
        header = test_footer->header;     // Rewrite our header with the new one.
        footer->header = header;          // Rewrite our footer to point to the new header.
        header->size += cache_size;       // Change the size.
        do_add = 0;                       // Since this header is already in the index, we don't want to add it again.
    }

    // Unify right
    // If the thing immediately to the right of us is a header...
    Header *test_header = (Header*) ( (uint32)footer + sizeof(Footer) );
    if (test_header->magic == HEAP_MAGIC &&
        test_header->is_hole)
    {
        header->size += test_header->size; // Increase our size.
        test_footer = (Footer*) ( (uint32)test_header + // Rewrite it's footer to point to our header.
                                    test_header->size - sizeof(Footer) );
        footer = test_footer;
        // Find and remove this header from the index.
        uint32 iterator = 0;
        while ( (iterator < index.GetSize()) &&
                (&index[iterator] != (void*)test_header) )
            iterator++;

        // Make sure we actually found the item.
        ASSERT(iterator < index.GetSize());
        // Remove it.
        index.Remove(iterator);
    }

    // If the footer location is the end address, we can contract.
    if ( (uint32)footer+sizeof(Footer) == end_address)
    {
        uint32 old_length = end_address-start_address;
        uint32 new_length = Contract( (uint32)header - start_address);
        // Check how big we will be after resizing.
        if (header->size - (old_length-new_length) > 0)
        {
            // We will still exist, so resize us.
            header->size -= old_length-new_length;
            footer = (Footer*) ( (uint32)header + header->size - sizeof(Footer) );
            footer->magic = HEAP_MAGIC;
            footer->header = header;
        }
        else
        {
            // We will no longer exist :(. Remove us from the index.
            uint32 iterator = 0;
            while ( (iterator < index.GetSize()) &&
                    (&index[iterator] != (void*)test_header) )
                iterator++;
            // If we didn't find ourselves, we have nothing to remove.
            if (iterator < index.GetSize())
                index.Remove(iterator);
        }
    }

    // If required, add us to the index.
    if (do_add == 1)
        index.Insert(*header);
}













uint32 KMemoryAllocateBase(uint32 sz, int align, uint32 *phys)
{
	//MON.Write("KMemoryAllocateBase: ").WriteDec(sz).Write(", ").WriteDec(align).Write(", ").WriteHex(phys).NewLine();
	
    //if (kheap != 0)
    //{
        void *addr = global->kheap.Allocate(sz, (uint8)align);
        if (phys != 0)
        {
            Page *page = GetPage((uint32)addr, 0, global->kernel_directory);
            *phys = page->frame*0x1000 + (uint32)addr&0xFFF;
        }
        return (uint32)addr;
    /*}
    else
    {
        if (align == 1 && (placement_address & 0x00000FFF) )
        {
            // Align the placement address;
            placement_address &= 0xFFFFF000;
            placement_address += 0x1000;
        }
        if (phys)
        {
            *phys = placement_address;
        }
        uint32 tmp = placement_address;
        placement_address += sz;
        return tmp;
    }*/
}

uint32 KMemoryAllocateAligned(uint32 sz) {
	return KMemoryAllocateBase(sz, 1, 0);
}

uint32 KMemoryAllocatePhysical(uint32 sz, uint32 *phys) {
	return KMemoryAllocateBase(sz, 0, phys);
}

uint32 KMemoryAllocateAlignedPhysical(uint32 sz, uint32 *phys) {
	return KMemoryAllocateBase(sz, 1, phys);
}

uint32 KMemoryAllocate(uint32 sz) {
	return KMemoryAllocateBase(sz, 0, 0);
}

void KFree(void* addr) {global->kheap.Free(addr);}
