// Copyright 2011-2020 David Robillard <d@drobilla.net>
// SPDX-License-Identifier: ISC

#ifndef ZIX_BTREE_H
#define ZIX_BTREE_H

#include "common.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
   @addtogroup zix
   @{
   @name BTree
   @{
*/

/**
   A B-Tree.
*/
typedef struct ZixBTreeImpl ZixBTree;

/**
   A B-Tree node (opaque).
*/
typedef struct ZixBTreeNodeImpl ZixBTreeNode;

/**
   An iterator over a B-Tree.

   Note that modifying the trees invalidates all iterators, so all iterators
   are const iterators.
*/
typedef struct ZixBTreeIterImpl ZixBTreeIter;

/**
   Create a new (empty) B-Tree.
*/
ZIX_API
ZixBTree*
zix_btree_new(ZixComparator cmp, const void* cmp_data, ZixDestroyFunc destroy);

/**
   Free `t`.
*/
ZIX_API
void
zix_btree_free(ZixBTree* t);

/**
   Return the number of elements in `t`.
*/
ZIX_PURE_API
size_t
zix_btree_size(const ZixBTree* t);

/**
   Insert the element `e` into `t`.
*/
ZIX_API
ZixStatus
zix_btree_insert(ZixBTree* t, void* e);

/**
   Remove the value `e` from `t`.

   @param t Tree to remove from.

   @param e Value to remove.

   @param out Set to point to the removed pointer (which may not equal `e`).

   @param next If non-NULL, pointed to the value following `e`.  If *next is
   also non-NULL, the iterator is reused, otherwise a new one is allocated.  To
   reuse an iterator, no items may have been added since its creation.
*/
ZIX_API
ZixStatus
zix_btree_remove(ZixBTree* t, const void* e, void** out, ZixBTreeIter** next);

/**
   Set `ti` to an element equal to `e` in `t`.
   If no such item exists, `ti` is set to NULL.
*/
ZIX_API
ZixStatus
zix_btree_find(const ZixBTree* t, const void* e, ZixBTreeIter** ti);

/**
   Set `ti` to the smallest element in `t` that is not less than `e`.

   Wildcards are supported, so if the search key `e` compares equal to many
   values in the tree, `ti` will be set to the least such element.  The search
   key `e` is always passed as the second argument to the comparator.
*/
ZIX_API
ZixStatus
zix_btree_lower_bound(const ZixBTree* t, const void* e, ZixBTreeIter** ti);

/**
   Return the data associated with the given tree item.
*/
ZIX_PURE_API
void*
zix_btree_get(const ZixBTreeIter* ti);

/**
   Return an iterator to the first (smallest) element in `t`.

   The returned iterator must be freed with zix_btree_iter_free().
*/
ZIX_PURE_API
ZixBTreeIter*
zix_btree_begin(const ZixBTree* t);

/**
   Return an iterator to the end of `t` (one past the last element).

   The returned iterator must be freed with zix_btree_iter_free().
*/
ZIX_API
ZixBTreeIter*
zix_btree_end(const ZixBTree* t);

/**
   Return a new copy of `i`.
*/
ZIX_API
ZixBTreeIter*
zix_btree_iter_copy(const ZixBTreeIter* i);

/**
   Return true iff `lhs` is equal to `rhs`.
*/
ZIX_PURE_API
bool
zix_btree_iter_equals(const ZixBTreeIter* lhs, const ZixBTreeIter* rhs);

/**
   Return true iff `i` is an iterator to the end of its tree.
*/
ZIX_PURE_API
bool
zix_btree_iter_is_end(const ZixBTreeIter* i);

/**
   Increment `i` to point to the next element in the tree.
*/
ZIX_API
void
zix_btree_iter_increment(ZixBTreeIter* i);

/**
   Free `i`.
*/
ZIX_API
void
zix_btree_iter_free(ZixBTreeIter* i);

/**
   @}
   @}
*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ZIX_BTREE_H */
