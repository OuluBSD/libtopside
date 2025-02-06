#include "Kernel.h"



int Monitor::Init() {
	// The VGA framebuffer starts at 0xB8000.
	video_memory = (uint16*) 0xB8000;
	
	// Stores the cursor position.
	cursor_x = 0;
	cursor_y = 0;
	
	return 0;
}

// Updates the hardware cursor.
void Monitor::MoveCursor() {
	// The screen is 80 characters wide...
	cursorLocation = cursor_y * 80 + cursor_x;
	outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
	outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
	outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
	outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}


// Scrolls the text on the screen up by one line.
void Monitor::Scroll() {

	// Get a space character with the default colour attributes.
	//uint8 attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	uint8 attributeByte = (15 << 4) | (0 & 0x0F);
	uint16 blank = 0x20 /* space */ | (attributeByte << 8);
	
	// Row 25 is the end, this means we need to scroll up
	if (cursor_y >= 25) {
		// Move the current text chunk that makes up the screen
		// back in the buffer by a line
		int i;
		for (i = 0 * 80; i < 24*80; i++) {
			video_memory[i] = video_memory[i+80];
		}
		
		// The last line should now be blank. Do this by writing
		// 80 spaces to it.
		for (i = 24 * 80; i < 25*80; i++) {
			video_memory[i] = blank;
		}
		// The cursor should now be on the last line.
		cursor_y = 24;
	}
}


// Writes a single character out to the screen.
void Monitor::Put(dword d, int count) {
	char c = (char)d;
	// The background colour is black (0), the foreground is white (15).
	//uint8 backColour = 0;
	//uint8 foreColour = 15;
	uint8 backColour = 15;
	uint8 foreColour = 0;
	
	// The attribute byte is made up of two nibbles - the lower being the
	// foreground colour, and the upper the background colour.
	uint8  attributeByte = (backColour << 4) | (foreColour & 0x0F);
	// The attribute byte is the top 8 bits of the word we have to send to the
	// VGA board.
	uint16 attribute = attributeByte << 8;
	uint16 *location;
	
	// Handle a backspace, by moving the cursor back one space
	if (c == 0x08 && cursor_x) {
		cursor_x--;
	}
	
	// Handle a tab by increasing the cursor's X, but only to a point
	// where it is divisible by 8.
	else if (c == 0x09) {
		cursor_x = (cursor_x + 8) & ~(8 - 1);
	}
	
	// Handle carriage return
	else if (c == '\r') {
		cursor_x = 0;
	}
	
	// Handle newline by moving cursor back to left and increasing the row
	else if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	}
	// Handle any other printable character.
	else if (c >= ' ') {
		location = video_memory + (cursor_y * 80 + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}
					
	// Check if we need to insert a new line because we have reached the end
	// of the screen.
	if (cursor_x >= 80) {
		cursor_x = 0;
		cursor_y ++;
	}
	
	// Scroll the screen if needed.
	Scroll();
	// Move the hardware cursor.
	MoveCursor();
}


// Clears the screen, by copying lots of spaces to the framebuffer.
void Monitor::Clear() {
	// Make an attribute byte for the default colours
	//uint8 attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	uint8 attributeByte = (15 << 4) | (0 & 0x0F);
	uint16 blank = 0x20 /* space */ | (attributeByte << 8);
	
	int i;
	for (i = 0; i < 80*25; i++) {
		video_memory[i] = blank;
	}
	
	// Move the hardware cursor back to the start.
	cursor_x = 0;
	cursor_y = 0;
	MoveCursor();
}


// Outputs a null-terminated ASCII string to the MON.
void Monitor::Write(const char *c) {
	int i = 0;
	while (c[i]) {
		Put(c[i++]);
	}
}



void Monitor::WriteDec(int i) {
	if (i < 0)
		Put('-');
	bool foundfirst = 0;
	for (int j = 9; j >= 0; j--) {
		int pow = Pow10(j);
		int k = i / pow;
		i = i % pow;
		if (k < 0)
			k *= -1;
		if (!foundfirst && k)
			foundfirst = 1;
		if (foundfirst)
			Put('0' + k);
	}
	if (!foundfirst)
		Put('0');
}

void Monitor::WriteHexPtr(void* p) {
	WriteHexInt((size_t)p);
}

void Monitor::WriteHexInt(size_t n) {
	//WriteDec(n); Put('\n');
	Put('0');
	Put('x');
	for (int i = 0; i < 8; i++) {
		int j = (n & 0xF0000000) >> (32 - 4);
		//WriteDec(n); Put(' '); WriteDec(j); Put('\n');
		if (j < 10)
			Put('0' + j);
		else
			Put('A' + j - 10);
		n = n << 4;
	}
}

void Monitor::NewLine() {
	Write("\n");
};

