// Copyright 2012-2020 David Robillard <d@drobilla.net>
// SPDX-License-Identifier: ISC

#ifndef ZIX_DIGEST_H
#define ZIX_DIGEST_H

#include "common.h"

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
   Return an initial empty digest value.
*/
ZIX_CONST_API
uint32_t
zix_digest_start(void);

/**
   Update `hash` to include `buf`, a buffer of `len` bytes.

   This can be used for any size or alignment.
*/
ZIX_PURE_API
uint32_t
zix_digest_add(uint32_t hash, const void* buf, size_t len);

/**
   Update `hash` to include `buf`, a 64-bit aligned buffer of `len` bytes.

   Both `buf` and `len` must be evenly divisible by 8 (64 bits).
*/
ZIX_PURE_API
uint32_t
zix_digest_add_64(uint32_t hash, const void* buf, size_t len);

/**
   Update `hash` to include `ptr`.

   This hashes the value of the pointer itself, and does not dereference `ptr`.
*/
ZIX_CONST_API
uint32_t
zix_digest_add_ptr(uint32_t hash, const void* ptr);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ZIX_DIGEST_H */
