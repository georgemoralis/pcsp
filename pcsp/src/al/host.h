/*
 * host.h
 *
 *  Created on: 22 nov. 2008
 *      Author: hli
 */

#ifndef HOST_H_
#define HOST_H_

#if defined(__i386__) /* gcc */ || defined(_M_IX86) /* msvc */ || defined(_X86_) || defined(__386__) || defined(i386)
#include "host_x86.h"
#elif defined(__x86_64__) /* gcc */ || defined(_M_X64) /* msvc */ || defined(_M_AMD64) /* msvc */ 
#include "host_x86_64.h"
#else
#include "host_any.h"
#endif

#endif /* HOST_H_ */
