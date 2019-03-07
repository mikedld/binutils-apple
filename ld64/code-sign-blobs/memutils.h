/*
 * Copyright (c) 2000-2004 Apple Computer, Inc. All Rights Reserved.
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */


//
// memutils - memory-related low-level utilities for easier living
//
#ifndef _H_MEMUTILS
#define _H_MEMUTILS

//#include <security_utilities/utilities.h>
#include <sys/types.h>
#include <stdlib.h>
#include <algorithm>

// Patch 09/11/2016 - Alex Barker
#include <cstddef>


//
// Encapsulate these very sharp tools in a separate (ugly-named) namespace
//
namespace Security {
namespace LowLevelMemoryUtilities {


//
// The default system alignment.
//
static const size_t systemAlignment = 4;


//
// Get the local alignment for a type, as used by the acting compiler.
//
// Patch 12/28/2014
//template <class T>
//inline size_t alignof() { struct { char c; T t; } s; return sizeof(s) - sizeof(T); }

//
// Get the local offset of a field in a (struct or class) type, as layed out
// by the acting compiler.
// NB: "offsetof" is a standard-defined macro. Don't use that.
//
template <class Type, class Field>
inline size_t fieldOffsetOf(Field (Type::*field))
{
	Type *object = 0;	// we don't REALLY need this, but it's easier to read
	return uintptr_t(&(object->*field)) - uintptr_t(object);
}


//
// Round up a size or pointer to an alignment boundary.
// Alignment must be a power of two; default is default alignment.
//
inline size_t alignUp(size_t size, size_t alignment = systemAlignment)
{
	return ((size - 1) & ~(alignment - 1)) + alignment;
}

inline void *alignUp(void *p, size_t alignment = systemAlignment)
{
	return reinterpret_cast<void *>(alignUp(uintptr_t(p), alignment));
}

inline const void *alignUp(const void *p, size_t alignment = systemAlignment)
{
	return reinterpret_cast<const void *>(alignUp(uintptr_t(p), alignment));
}

template <class T>
// Patch 09/11/2016 - Alex Barker
// Patch 12/28/2014
inline const T *increment(const void *p, std::ptrdiff_t offset)
{ return reinterpret_cast<const T *>(uintptr_t(p) + offset); }

template <class T>
// Patch 09/11/2016 - Alex Barker
// Patch 12/28/2014
inline T *increment(void *p, std::ptrdiff_t offset)
{ return reinterpret_cast<T *>(uintptr_t(p) + offset); }

// Patch 09/11/2016 - Alex Barker
// Patch 12/28/2014
inline const void *increment(const void *p, std::ptrdiff_t offset)
{ return increment<const void>(p, offset); }

// Patch 09/11/2016 - Alex Barker
// Patch 12/28/2014
inline void *increment(void *p, std::ptrdiff_t offset)
{ return increment<void>(p, offset); }

template <class T>
// Patch 09/11/2016 - Alex Barker
// Patch 12/28/2014
inline const T *increment(const void *p, std::ptrdiff_t offset, size_t alignment)
{ return increment<const T>(alignUp(p, alignment), offset); }

template <class T>
// Patch 09/11/2016 - Alex Barker
// Patch 12/28/2014
inline T *increment(void *p, std::ptrdiff_t offset, size_t alignment)
{ return increment<T>(alignUp(p, alignment), offset); }

// Patch 09/11/2016 - Alex Barker
// Patch 12/28/2014
inline const void *increment(const void *p, std::ptrdiff_t offset, size_t alignment)
{ return increment<const void>(p, offset, alignment); }

// Patch 09/11/2016 - Alex Barker
// Patch 12/28/2014
inline void *increment(void *p, std::ptrdiff_t offset, size_t alignment)
{ return increment<void>(p, offset, alignment); }

// Patch 09/11/2016 - Alex Barker
// Patch 12/28/2014
inline std::ptrdiff_t difference(const void *p1, const void *p2)
{ return uintptr_t(p1) - uintptr_t(p2); }


} // end namespace LowLevelMemoryUtilities
} // end namespace Security

#endif //_H_MEMUTILS