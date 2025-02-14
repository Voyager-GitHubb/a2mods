// Anduril: Narsil-inspired UI for SpaghettiMonster.
// (Anduril is Aragorn's sword, the blade Narsil reforged)
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Usually a program would be structured like this...
 * - Library headers
 * - App headers
 * - App code
 *
 * ... in each source file.
 * ... and each library and part of the program would be linked together.
 *
 * But this doesn't follow that pattern, because it's using the
 *   -fwhole-program
 * flag to reduce the compiled size.  It lets us fit more features
 * in a tiny MCU chip's ROM.
 *
 * So the structure is like this instead...
 * - App-level configuration headers
 *   - Default config
 *   - Per build target config
 * - Library-level configuration headers
 * - Library code (FSM itself)
 * - App headers
 * - App code (all of it, inline)
 *
 * Don't do this in regular programs.  It's weird and kind of gross.
 * But in this case it gives us a bunch of much-needed space, so... woot.
 *
 * Also, there are a ton of compile-time options because it needs to build
 * a bunch of different versions and each one needs to be trimmed as small
 * as possible.  These are mostly "USE" flags.
 */
/********* load up MCU info, like ROM size and such *********/
// arch/mcu.h: Attiny portability header.
// Copyright (C) 2014-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// This helps abstract away the differences between various attiny MCUs.
/* Copyright (c) 2002, 2003, 2004, 2007 Marek Michalkiewicz
   Copyright (c) 2005, 2006 Bjoern Haase
   Copyright (c) 2008 Atmel Corporation
   Copyright (c) 2008 Wouter van Gulik
   Copyright (c) 2009 Dmitry Xmelkov
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/* Copyright (c) 2002, Marek Michalkiewicz <marekm@amelek.gda.pl>
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.  */
/* avr/sfr_defs.h - macros for accessing AVR special function registers */
/* $Id$ */
/** \defgroup avr_sfr_notes Additional notes from <avr/sfr_defs.h>
    \ingroup avr_sfr
   The \c <avr/sfr_defs.h> file is included by all of the \c <avr/ioXXXX.h>
   files, which use macros defined here to make the special function register
   definitions look like C variables or simple constants, depending on the
   <tt>_SFR_ASM_COMPAT</tt> define.  Some examples from \c <avr/iocanxx.h> to
   show how to define such macros:
\code
\endcode
   If \c _SFR_ASM_COMPAT is not defined, C programs can use names like
   <tt>PORTA</tt> directly in C expressions (also on the left side of
   assignment operators) and GCC will do the right thing (use short I/O
   instructions if possible).  The \c __SFR_OFFSET definition is not used in
   any way in this case.
   Define \c _SFR_ASM_COMPAT as 1 to make these names work as simple constants
   (addresses of the I/O registers).  This is necessary when included in
   preprocessed assembler (*.S) source files, so it is done automatically if
   \c __ASSEMBLER__ is defined.  By default, all addresses are defined as if
   they were memory addresses (used in \c lds/sts instructions).  To use these
   addresses in \c in/out instructions, you must subtract 0x20 from them.
   For more backwards compatibility, insert the following at the start of your
   old assembler source file:
\code
\endcode
   This automatically subtracts 0x20 from I/O space addresses, but it's a
   hack, so it is recommended to change your source: wrap such addresses in
   macros defined here, as shown below.  After this is done, the
   <tt>__SFR_OFFSET</tt> definition is no longer necessary and can be removed.
   Real example - this code could be used in a boot loader that is portable
   between devices with \c SPMCR at different addresses.
\verbatim
<avr/iom163.h>: #define SPMCR _SFR_IO8(0x37)
<avr/iom128.h>: #define SPMCR _SFR_MEM8(0x68)
\endverbatim
\code
	out	_SFR_IO_ADDR(SPMCR), r24
	sts	_SFR_MEM_ADDR(SPMCR), r24
\endcode
   You can use the \c in/out/cbi/sbi/sbic/sbis instructions, without the
   <tt>_SFR_IO_REG_P</tt> test, if you know that the register is in the I/O
   space (as with \c SREG, for example).  If it isn't, the assembler will
   complain (I/O address out of range 0...0x3f), so this should be fairly
   safe.
   If you do not define \c __SFR_OFFSET (so it will be 0x20 by default), all
   special register addresses are defined as memory addresses (so \c SREG is
   0x5f), and (if code size and speed are not important, and you don't like
   the ugly \#if above) you can always use lds/sts to access them.  But, this
   will not work if <tt>__SFR_OFFSET</tt> != 0x20, so use a different macro
   (defined only if <tt>__SFR_OFFSET</tt> == 0x20) for safety:
\code
	sts	_SFR_ADDR(SPMCR), r24
\endcode
   In C programs, all 3 combinations of \c _SFR_ASM_COMPAT and
   <tt>__SFR_OFFSET</tt> are supported - the \c _SFR_ADDR(SPMCR) macro can be
   used to get the address of the \c SPMCR register (0x57 or 0x68 depending on
   device). */
/* These only work in C programs.  */
/* Copyright (c) 2004,2005,2007,2012 Joerg Wunsch
   Copyright (c) 2005, Carlos Lamas
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2004,2005 Marek Michalkiewicz
   Copyright (c) 2005, Carlos Lamas
   Copyright (c) 2005,2007 Joerg Wunsch
   Copyright (c) 2013 Embecosm
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/*
 * ISO/IEC 9899:1999  7.18 Integer types <stdint.h>
 */
/** \file */
/** \defgroup avr_stdint <stdint.h>: Standard Integer Types
    \code #include <stdint.h> \endcode
    Use [u]intN_t if you need exactly N bits.
    Since these typedefs are mandated by the C99 standard, they are preferred
    over rolling your own typedefs.  */
/*
 * __USING_MINT8 is defined to 1 if the -mint8 option is in effect.
 */
/* Integer types */
/* actual implementation goes here */
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));
typedef signed int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
/** \name Integer types capable of holding object pointers
    These allow you to declare variables of the same size as a pointer. */
/*@{*/
/** \ingroup avr_stdint
    Signed pointer compatible type. */
typedef int16_t intptr_t;
/** \ingroup avr_stdint
    Unsigned pointer compatible type. */
typedef uint16_t uintptr_t;
/*@}*/
/** \name Minimum-width integer types
   Integer types having at least the specified width */
/*@{*/
/** \ingroup avr_stdint
    signed int with at least 8 bits. */
typedef int8_t int_least8_t;
/** \ingroup avr_stdint
    unsigned int with at least 8 bits. */
typedef uint8_t uint_least8_t;
/** \ingroup avr_stdint
    signed int with at least 16 bits. */
typedef int16_t int_least16_t;
/** \ingroup avr_stdint
    unsigned int with at least 16 bits. */
typedef uint16_t uint_least16_t;
/** \ingroup avr_stdint
    signed int with at least 32 bits. */
typedef int32_t int_least32_t;
/** \ingroup avr_stdint
    unsigned int with at least 32 bits. */
typedef uint32_t uint_least32_t;
/** \ingroup avr_stdint
    signed int with at least 64 bits.
    \note This type is not available when the compiler
    option -mint8 is in effect. */
typedef int64_t int_least64_t;
/** \ingroup avr_stdint
    unsigned int with at least 64 bits.
    \note This type is not available when the compiler
    option -mint8 is in effect. */
typedef uint64_t uint_least64_t;
/*@}*/
/** \name Fastest minimum-width integer types
   Integer types being usually fastest having at least the specified width */
/*@{*/
/** \ingroup avr_stdint
    fastest signed int with at least 8 bits. */
typedef int8_t int_fast8_t;
/** \ingroup avr_stdint
    fastest unsigned int with at least 8 bits. */
typedef uint8_t uint_fast8_t;
/** \ingroup avr_stdint
    fastest signed int with at least 16 bits. */
typedef int16_t int_fast16_t;
/** \ingroup avr_stdint
    fastest unsigned int with at least 16 bits. */
typedef uint16_t uint_fast16_t;
/** \ingroup avr_stdint
    fastest signed int with at least 32 bits. */
typedef int32_t int_fast32_t;
/** \ingroup avr_stdint
    fastest unsigned int with at least 32 bits. */
typedef uint32_t uint_fast32_t;
/** \ingroup avr_stdint
    fastest signed int with at least 64 bits.
    \note This type is not available when the compiler
    option -mint8 is in effect. */
typedef int64_t int_fast64_t;
/** \ingroup avr_stdint
    fastest unsigned int with at least 64 bits.
    \note This type is not available when the compiler
    option -mint8 is in effect. */
typedef uint64_t uint_fast64_t;
/*@}*/
/** \name Greatest-width integer types
   Types designating integer data capable of representing any value of
   any integer type in the corresponding signed or unsigned category */
/*@{*/
/** \ingroup avr_stdint
    largest signed int available. */
typedef int64_t intmax_t;
/** \ingroup avr_stdint
    largest unsigned int available. */
typedef uint64_t uintmax_t;
/*@}*/
/* Helping macro */
/** \name Limits of specified-width integer types
   C++ implementations should define these macros only when
   __STDC_LIMIT_MACROS is defined before <stdint.h> is included */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an int8_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int8_t can hold. */
/** \ingroup avr_stdint
    largest value an uint8_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int16_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int16_t can hold. */
/** \ingroup avr_stdint
    largest value an uint16_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int32_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int32_t can hold. */
/** \ingroup avr_stdint
    largest value an uint32_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int64_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int64_t can hold. */
/** \ingroup avr_stdint
    largest value an uint64_t can hold. */
/*@}*/
/** \name Limits of minimum-width integer types */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an int_least8_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_least8_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_least8_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_least16_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_least16_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_least16_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_least32_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_least32_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_least32_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_least64_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_least64_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_least64_t can hold. */
/*@}*/
/** \name Limits of fastest minimum-width integer types */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an int_fast8_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_fast8_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_fast8_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_fast16_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_fast16_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_fast16_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_fast32_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_fast32_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_fast32_t can hold. */
/** \ingroup avr_stdint
    largest positive value an int_fast64_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an int_fast64_t can hold. */
/** \ingroup avr_stdint
    largest value an uint_fast64_t can hold. */
/*@}*/
/** \name Limits of integer types capable of holding object pointers */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an intptr_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an intptr_t can hold. */
/** \ingroup avr_stdint
    largest value an uintptr_t can hold. */
/*@}*/
/** \name Limits of greatest-width integer types */
/*@{*/
/** \ingroup avr_stdint
    largest positive value an intmax_t can hold. */
/** \ingroup avr_stdint
    smallest negative value an intmax_t can hold. */
/** \ingroup avr_stdint
    largest value an uintmax_t can hold. */
/*@}*/
/** \name Limits of other integer types
    C++ implementations should define these macros only when
    __STDC_LIMIT_MACROS is defined before <stdint.h> is included */
/*@{*/
/** \ingroup avr_stdint
    largest positive value a ptrdiff_t can hold. */
/** \ingroup avr_stdint
    smallest negative value a ptrdiff_t can hold. */
/* Limits of sig_atomic_t */
/* signal.h is currently not implemented (not avr/signal.h) */
/** \ingroup avr_stdint
    largest positive value a sig_atomic_t can hold. */
/** \ingroup avr_stdint
    smallest negative value a sig_atomic_t can hold. */
/** \ingroup avr_stdint
    largest value a size_t can hold. */
/* Limits of wchar_t */
/* wchar.h is currently not implemented */
/* #define WCHAR_MAX */
/* #define WCHAR_MIN */
/* Limits of wint_t */
/* wchar.h is currently not implemented */
/** \name Macros for integer constants
    C++ implementations should define these macros only when
    __STDC_CONSTANT_MACROS is defined before <stdint.h> is included.
    These definitions are valid for integer constants without suffix and
    for macros defined as integer constant without suffix */
/* The GNU C preprocessor defines special macros in the implementation
   namespace to allow a definition that works in #if expressions.  */
/*@}*/
/** \file */
/** \defgroup avr_inttypes <inttypes.h>: Integer Type conversions
    \code #include <inttypes.h> \endcode
    This header file includes the exact-width integer definitions from
    <tt><stdint.h></tt>, and extends them with additional facilities
    provided by the implementation.
    Currently, the extensions include two additional integer types
    that could hold a "far" pointer (i.e. a code pointer that can
    address more than 64 KB), as well as standard names for all printf
    and scanf formatting options that are supported by the \ref avr_stdio.
    As the library does not support the full range of conversion
    specifiers from ISO 9899:1999, only those conversions that are
    actually implemented will be listed here.
    The idea behind these conversion macros is that, for each of the
    types defined by <stdint.h>, a macro will be supplied that portably
    allows formatting an object of that type in printf() or scanf()
    operations.  Example:
    \code
    #include <inttypes.h>
    uint8_t smallval;
    int32_t longval;
    ...
    printf("The hexadecimal value of smallval is %" PRIx8
           ", the decimal value of longval is %" PRId32 ".\n",
	   smallval, longval);
    \endcode
*/
/** \name Far pointers for memory access >64K */
/*@{*/
/** \ingroup avr_inttypes
    signed integer type that can hold a pointer > 64 KB */
typedef int32_t int_farptr_t;
/** \ingroup avr_inttypes
    unsigned integer type that can hold a pointer > 64 KB */
typedef uint32_t uint_farptr_t;
/*@}*/
/** \name macros for printf and scanf format specifiers
    For C++, these are only included if __STDC_LIMIT_MACROS
    is defined before including <inttypes.h>.
 */
/*@{*/
/** \ingroup avr_inttypes
    decimal printf format for int8_t */
/** \ingroup avr_inttypes
    decimal printf format for int_least8_t */
/** \ingroup avr_inttypes
    decimal printf format for int_fast8_t */
/** \ingroup avr_inttypes
    integer printf format for int8_t */
/** \ingroup avr_inttypes
    integer printf format for int_least8_t */
/** \ingroup avr_inttypes
    integer printf format for int_fast8_t */
/** \ingroup avr_inttypes
    decimal printf format for int16_t */
/** \ingroup avr_inttypes
    decimal printf format for int_least16_t */
/** \ingroup avr_inttypes
    decimal printf format for int_fast16_t */
/** \ingroup avr_inttypes
    integer printf format for int16_t */
/** \ingroup avr_inttypes
    integer printf format for int_least16_t */
/** \ingroup avr_inttypes
    integer printf format for int_fast16_t */
/** \ingroup avr_inttypes
    decimal printf format for int32_t */
/** \ingroup avr_inttypes
    decimal printf format for int_least32_t */
/** \ingroup avr_inttypes
    decimal printf format for int_fast32_t */
/** \ingroup avr_inttypes
    integer printf format for int32_t */
/** \ingroup avr_inttypes
    integer printf format for int_least32_t */
/** \ingroup avr_inttypes
    integer printf format for int_fast32_t */
/** \ingroup avr_inttypes
    decimal printf format for intptr_t */
/** \ingroup avr_inttypes
    integer printf format for intptr_t */
/** \ingroup avr_inttypes
    octal printf format for uint8_t */
/** \ingroup avr_inttypes
    octal printf format for uint_least8_t */
/** \ingroup avr_inttypes
    octal printf format for uint_fast8_t */
/** \ingroup avr_inttypes
    decimal printf format for uint8_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_least8_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_fast8_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint8_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_least8_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_fast8_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint8_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_least8_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_fast8_t */
/** \ingroup avr_inttypes
    octal printf format for uint16_t */
/** \ingroup avr_inttypes
    octal printf format for uint_least16_t */
/** \ingroup avr_inttypes
    octal printf format for uint_fast16_t */
/** \ingroup avr_inttypes
    decimal printf format for uint16_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_least16_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_fast16_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint16_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_least16_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_fast16_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint16_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_least16_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_fast16_t */
/** \ingroup avr_inttypes
    octal printf format for uint32_t */
/** \ingroup avr_inttypes
    octal printf format for uint_least32_t */
/** \ingroup avr_inttypes
    octal printf format for uint_fast32_t */
/** \ingroup avr_inttypes
    decimal printf format for uint32_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_least32_t */
/** \ingroup avr_inttypes
    decimal printf format for uint_fast32_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint32_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_least32_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uint_fast32_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint32_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_least32_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uint_fast32_t */
/** \ingroup avr_inttypes
    octal printf format for uintptr_t */
/** \ingroup avr_inttypes
    decimal printf format for uintptr_t */
/** \ingroup avr_inttypes
    hexadecimal printf format for uintptr_t */
/** \ingroup avr_inttypes
    uppercase hexadecimal printf format for uintptr_t */
/** \ingroup avr_inttypes
    decimal scanf format for int8_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_least8_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_fast8_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int8_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_least8_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_fast8_t */
/** \ingroup avr_inttypes
    decimal scanf format for int16_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_least16_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_fast16_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int16_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_least16_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_fast16_t */
/** \ingroup avr_inttypes
    decimal scanf format for int32_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_least32_t */
/** \ingroup avr_inttypes
    decimal scanf format for int_fast32_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int32_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_least32_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for int_fast32_t */
/** \ingroup avr_inttypes
    decimal scanf format for intptr_t */
/** \ingroup avr_inttypes
    generic-integer scanf format for intptr_t */
/** \ingroup avr_inttypes
    octal scanf format for uint8_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_least8_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_fast8_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint8_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_least8_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_fast8_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint8_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_least8_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_fast8_t */
/** \ingroup avr_inttypes
    octal scanf format for uint16_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_least16_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_fast16_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint16_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_least16_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_fast16_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint16_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_least16_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_fast16_t */
/** \ingroup avr_inttypes
    octal scanf format for uint32_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_least32_t */
/** \ingroup avr_inttypes
    octal scanf format for uint_fast32_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint32_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_least32_t */
/** \ingroup avr_inttypes
    decimal scanf format for uint_fast32_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint32_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_least32_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uint_fast32_t */
/** \ingroup avr_inttypes
    octal scanf format for uintptr_t */
/** \ingroup avr_inttypes
    decimal scanf format for uintptr_t */
/** \ingroup avr_inttypes
    hexadecimal scanf format for uintptr_t */
/*@}*/
/** \name Bit manipulation */
/*@{*/
/** \def _BV
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Converts a bit number into a byte value.
    \note The bit shift is performed by the compiler which then inserts the
    result into the code. Thus, there is no run-time overhead when using
    _BV(). */
/*@}*/
/** \name IO register bit manipulation */
/*@{*/
/** \def bit_is_set
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Test whether bit \c bit in IO register \c sfr is set. 
    This will return a 0 if the bit is clear, and non-zero
    if the bit is set. */
/** \def bit_is_clear
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Test whether bit \c bit in IO register \c sfr is clear. 
    This will return non-zero if the bit is clear, and a 0
    if the bit is set. */
/** \def loop_until_bit_is_set
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Wait until bit \c bit in IO register \c sfr is set. */
/** \def loop_until_bit_is_clear
    \ingroup avr_sfr
    \code #include <avr/io.h>\endcode
    Wait until bit \c bit in IO register \c sfr is clear. */
/*@}*/
/*
 * Copyright (C) 2022, Microchip Technology Inc. and its subsidiaries ("Microchip")
 * All rights reserved.
 *
 * This software is developed by Microchip Technology Inc. and its subsidiaries ("Microchip").
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     1. Redistributions of source code must retain the above copyright notice, this list of
 *        conditions and the following disclaimer.
 *
 *     2. Redistributions in binary form must reproduce the above copyright notice, this list
 *        of conditions and the following disclaimer in the documentation and/or other
 *        materials provided with the distribution. Publication is not required when
 *        this file is used in an embedded application.
 *
 *     3. Microchip's name may not be used to endorse or promote products derived from this
 *        software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWSOEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* Ungrouped common registers */
/* Deprecated */
/* C Language Only */
typedef volatile uint8_t register8_t;
typedef volatile uint16_t register16_t;
typedef volatile uint32_t register32_t;
/*
==========================================================================
IO Module Structures
==========================================================================
*/
/*
--------------------------------------------------------------------------
AC - Analog Comparator
--------------------------------------------------------------------------
*/
/* Analog Comparator */
typedef struct AC_struct
{
    register8_t CTRLA; /* Control A */
    register8_t reserved_1[1];
    register8_t MUXCTRLA; /* Mux Control A */
    register8_t reserved_2[3];
    register8_t INTCTRL; /* Interrupt Control */
    register8_t STATUS; /* Status */
} AC_t;
/* Hysteresis Mode select */
typedef enum AC_HYSMODE_enum
{
    AC_HYSMODE_OFF_gc = (0x00<<1), /* No hysteresis */
    AC_HYSMODE_10mV_gc = (0x01<<1), /* 10mV hysteresis */
    AC_HYSMODE_25mV_gc = (0x02<<1), /* 25mV hysteresis */
    AC_HYSMODE_50mV_gc = (0x03<<1) /* 50mV hysteresis */
} AC_HYSMODE_t;
/* Interrupt Mode select */
typedef enum AC_INTMODE_enum
{
    AC_INTMODE_BOTHEDGE_gc = (0x00<<4), /* Any Edge */
    AC_INTMODE_NEGEDGE_gc = (0x02<<4), /* Negative Edge */
    AC_INTMODE_POSEDGE_gc = (0x03<<4) /* Positive Edge */
} AC_INTMODE_t;
/* Low Power Mode select */
typedef enum AC_LPMODE_enum
{
    AC_LPMODE_DIS_gc = (0x00<<3), /* Low power mode disabled */
    AC_LPMODE_EN_gc = (0x01<<3) /* Low power mode enabled */
} AC_LPMODE_t;
/* Negative Input MUX Selection */
typedef enum AC_MUXNEG_enum
{
    AC_MUXNEG_PIN0_gc = (0x00<<0), /* Negative Pin 0 */
    AC_MUXNEG_PIN1_gc = (0x01<<0), /* Negative Pin 1 */
    AC_MUXNEG_VREF_gc = (0x02<<0), /* Voltage Reference */
    AC_MUXNEG_DAC_gc = (0x03<<0) /* DAC output */
} AC_MUXNEG_t;
/* Positive Input MUX Selection */
typedef enum AC_MUXPOS_enum
{
    AC_MUXPOS_PIN0_gc = (0x00<<3), /* Positive Pin 0 */
    AC_MUXPOS_PIN1_gc = (0x01<<3), /* Positive Pin 1 */
    AC_MUXPOS_PIN2_gc = (0x02<<3), /* Positive Pin 2 */
    AC_MUXPOS_PIN3_gc = (0x03<<3) /* Positive Pin 3 */
} AC_MUXPOS_t;
/*
--------------------------------------------------------------------------
ADC - Analog to Digital Converter
--------------------------------------------------------------------------
*/
/* Analog to Digital Converter */
typedef struct ADC_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t CTRLC; /* Control C */
    register8_t CTRLD; /* Control D */
    register8_t CTRLE; /* Control E */
    register8_t SAMPCTRL; /* Sample Control */
    register8_t MUXPOS; /* Positive mux input */
    register8_t reserved_1[1];
    register8_t COMMAND; /* Command */
    register8_t EVCTRL; /* Event Control */
    register8_t INTCTRL; /* Interrupt Control */
    register8_t INTFLAGS; /* Interrupt Flags */
    register8_t DBGCTRL; /* Debug Control */
    register8_t TEMP; /* Temporary Data */
    register8_t reserved_2[2];
    __extension__ union { register16_t RES; struct { register8_t RESL; register8_t RESH; }; }; /* ADC Accumulator Result */
    __extension__ union { register16_t WINLT; struct { register8_t WINLTL; register8_t WINLTH; }; }; /* Window comparator low threshold */
    __extension__ union { register16_t WINHT; struct { register8_t WINHTL; register8_t WINHTH; }; }; /* Window comparator high threshold */
    register8_t CALIB; /* Calibration */
    register8_t reserved_3[1];
} ADC_t;
/* Automatic Sampling Delay Variation select */
typedef enum ADC_ASDV_enum
{
    ADC_ASDV_ASVOFF_gc = (0x00<<4), /* The Automatic Sampling Delay Variation is disabled */
    ADC_ASDV_ASVON_gc = (0x01<<4) /* The Automatic Sampling Delay Variation is enabled */
} ADC_ASDV_t;
/* Duty Cycle select */
typedef enum ADC_DUTYCYC_enum
{
    ADC_DUTYCYC_DUTY50_gc = (0x00<<0), /* 50% Duty cycle */
    ADC_DUTYCYC_DUTY25_gc = (0x01<<0) /* 25% Duty cycle */
} ADC_DUTYCYC_t;
/* Initial Delay Selection */
typedef enum ADC_INITDLY_enum
{
    ADC_INITDLY_DLY0_gc = (0x00<<5), /* Delay 0 CLK_ADC cycles */
    ADC_INITDLY_DLY16_gc = (0x01<<5), /* Delay 16 CLK_ADC cycles */
    ADC_INITDLY_DLY32_gc = (0x02<<5), /* Delay 32 CLK_ADC cycles */
    ADC_INITDLY_DLY64_gc = (0x03<<5), /* Delay 64 CLK_ADC cycles */
    ADC_INITDLY_DLY128_gc = (0x04<<5), /* Delay 128 CLK_ADC cycles */
    ADC_INITDLY_DLY256_gc = (0x05<<5) /* Delay 256 CLK_ADC cycles */
} ADC_INITDLY_t;
/* Analog Channel Selection Bits */
typedef enum ADC_MUXPOS_enum
{
    ADC_MUXPOS_AIN0_gc = (0x00<<0), /* ADC input pin 0 */
    ADC_MUXPOS_AIN1_gc = (0x01<<0), /* ADC input pin 1 */
    ADC_MUXPOS_AIN2_gc = (0x02<<0), /* ADC input pin 2 */
    ADC_MUXPOS_AIN3_gc = (0x03<<0), /* ADC input pin 3 */
    ADC_MUXPOS_AIN4_gc = (0x04<<0), /* ADC input pin 4 */
    ADC_MUXPOS_AIN5_gc = (0x05<<0), /* ADC input pin 5 */
    ADC_MUXPOS_AIN6_gc = (0x06<<0), /* ADC input pin 6 */
    ADC_MUXPOS_AIN7_gc = (0x07<<0), /* ADC input pin 7 */
    ADC_MUXPOS_AIN8_gc = (0x08<<0), /* ADC input pin 8 */
    ADC_MUXPOS_AIN9_gc = (0x09<<0), /* ADC input pin 9 */
    ADC_MUXPOS_AIN10_gc = (0x0A<<0), /* ADC input pin 10 */
    ADC_MUXPOS_AIN11_gc = (0x0B<<0), /* ADC input pin 11 */
    ADC_MUXPOS_PTC_gc = (0x1B<<0), /* PTC/DAC2 */
    ADC_MUXPOS_DAC0_gc = (0x1C<<0), /* DAC0/DAC0 */
    ADC_MUXPOS_INTREF_gc = (0x1D<<0), /* Internal Ref */
    ADC_MUXPOS_TEMPSENSE_gc = (0x1E<<0), /* Temp sensor/DAC1 */
    ADC_MUXPOS_GND_gc = (0x1F<<0) /* GND */
} ADC_MUXPOS_t;
/* Clock Pre-scaler select */
typedef enum ADC_PRESC_enum
{
    ADC_PRESC_DIV2_gc = (0x00<<0), /* CLK_PER divided by 2 */
    ADC_PRESC_DIV4_gc = (0x01<<0), /* CLK_PER divided by 4 */
    ADC_PRESC_DIV8_gc = (0x02<<0), /* CLK_PER divided by 8 */
    ADC_PRESC_DIV16_gc = (0x03<<0), /* CLK_PER divided by 16 */
    ADC_PRESC_DIV32_gc = (0x04<<0), /* CLK_PER divided by 32 */
    ADC_PRESC_DIV64_gc = (0x05<<0), /* CLK_PER divided by 64 */
    ADC_PRESC_DIV128_gc = (0x06<<0), /* CLK_PER divided by 128 */
    ADC_PRESC_DIV256_gc = (0x07<<0) /* CLK_PER divided by 256 */
} ADC_PRESC_t;
/* Reference Selection */
typedef enum ADC_REFSEL_enum
{
    ADC_REFSEL_INTREF_gc = (0x00<<4), /* Internal reference */
    ADC_REFSEL_VDDREF_gc = (0x01<<4), /* VDD */
    ADC_REFSEL_VREFA_gc = (0x02<<4) /* External reference */
} ADC_REFSEL_t;
/* ADC Resolution select */
typedef enum ADC_RESSEL_enum
{
    ADC_RESSEL_10BIT_gc = (0x00<<2), /* 10-bit mode */
    ADC_RESSEL_8BIT_gc = (0x01<<2) /* 8-bit mode */
} ADC_RESSEL_t;
/* Accumulation Samples select */
typedef enum ADC_SAMPNUM_enum
{
    ADC_SAMPNUM_ACC1_gc = (0x00<<0), /* 1 ADC sample */
    ADC_SAMPNUM_ACC2_gc = (0x01<<0), /* Accumulate 2 samples */
    ADC_SAMPNUM_ACC4_gc = (0x02<<0), /* Accumulate 4 samples */
    ADC_SAMPNUM_ACC8_gc = (0x03<<0), /* Accumulate 8 samples */
    ADC_SAMPNUM_ACC16_gc = (0x04<<0), /* Accumulate 16 samples */
    ADC_SAMPNUM_ACC32_gc = (0x05<<0), /* Accumulate 32 samples */
    ADC_SAMPNUM_ACC64_gc = (0x06<<0) /* Accumulate 64 samples */
} ADC_SAMPNUM_t;
/* Window Comparator Mode select */
typedef enum ADC_WINCM_enum
{
    ADC_WINCM_NONE_gc = (0x00<<0), /* No Window Comparison */
    ADC_WINCM_BELOW_gc = (0x01<<0), /* Below Window */
    ADC_WINCM_ABOVE_gc = (0x02<<0), /* Above Window */
    ADC_WINCM_INSIDE_gc = (0x03<<0), /* Inside Window */
    ADC_WINCM_OUTSIDE_gc = (0x04<<0) /* Outside Window */
} ADC_WINCM_t;
/*
--------------------------------------------------------------------------
BOD - Bod interface
--------------------------------------------------------------------------
*/
/* Bod interface */
typedef struct BOD_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t reserved_1[6];
    register8_t VLMCTRLA; /* Voltage level monitor Control */
    register8_t INTCTRL; /* Voltage level monitor interrupt Control */
    register8_t INTFLAGS; /* Voltage level monitor interrupt Flags */
    register8_t STATUS; /* Voltage level monitor status */
    register8_t reserved_2[4];
} BOD_t;
/* Operation in active mode select */
typedef enum BOD_ACTIVE_enum
{
    BOD_ACTIVE_DIS_gc = (0x00<<2), /* Disabled */
    BOD_ACTIVE_ENABLED_gc = (0x01<<2), /* Enabled */
    BOD_ACTIVE_SAMPLED_gc = (0x02<<2), /* Sampled */
    BOD_ACTIVE_ENWAKE_gc = (0x03<<2) /* Enabled with wake-up halted until BOD is ready */
} BOD_ACTIVE_t;
/* Bod level select */
typedef enum BOD_LVL_enum
{
    BOD_LVL_BODLEVEL0_gc = (0x00<<0), /* 1.8 V */
    BOD_LVL_BODLEVEL2_gc = (0x02<<0), /* 2.6 V */
    BOD_LVL_BODLEVEL7_gc = (0x07<<0) /* 4.2 V */
} BOD_LVL_t;
/* Sample frequency select */
typedef enum BOD_SAMPFREQ_enum
{
    BOD_SAMPFREQ_1KHZ_gc = (0x00<<4), /* 1kHz sampling frequency */
    BOD_SAMPFREQ_125HZ_gc = (0x01<<4) /* 125Hz sampling frequency */
} BOD_SAMPFREQ_t;
/* Operation in sleep mode select */
typedef enum BOD_SLEEP_enum
{
    BOD_SLEEP_DIS_gc = (0x00<<0), /* Disabled */
    BOD_SLEEP_ENABLED_gc = (0x01<<0), /* Enabled */
    BOD_SLEEP_SAMPLED_gc = (0x02<<0) /* Sampled */
} BOD_SLEEP_t;
/* Configuration select */
typedef enum BOD_VLMCFG_enum
{
    BOD_VLMCFG_BELOW_gc = (0x00<<1), /* Interrupt when supply goes below VLM level */
    BOD_VLMCFG_ABOVE_gc = (0x01<<1), /* Interrupt when supply goes above VLM level */
    BOD_VLMCFG_CROSS_gc = (0x02<<1) /* Interrupt when supply crosses VLM level */
} BOD_VLMCFG_t;
/* voltage level monitor level select */
typedef enum BOD_VLMLVL_enum
{
    BOD_VLMLVL_5ABOVE_gc = (0x00<<0), /* VLM threshold 5% above BOD level */
    BOD_VLMLVL_15ABOVE_gc = (0x01<<0), /* VLM threshold 15% above BOD level */
    BOD_VLMLVL_25ABOVE_gc = (0x02<<0) /* VLM threshold 25% above BOD level */
} BOD_VLMLVL_t;
/*
--------------------------------------------------------------------------
CCL - Configurable Custom Logic
--------------------------------------------------------------------------
*/
/* Configurable Custom Logic */
typedef struct CCL_struct
{
    register8_t CTRLA; /* Control Register A */
    register8_t SEQCTRL0; /* Sequential Control 0 */
    register8_t reserved_1[3];
    register8_t LUT0CTRLA; /* LUT Control 0 A */
    register8_t LUT0CTRLB; /* LUT Control 0 B */
    register8_t LUT0CTRLC; /* LUT Control 0 C */
    register8_t TRUTH0; /* Truth 0 */
    register8_t LUT1CTRLA; /* LUT Control 1 A */
    register8_t LUT1CTRLB; /* LUT Control 1 B */
    register8_t LUT1CTRLC; /* LUT Control 1 C */
    register8_t TRUTH1; /* Truth 1 */
    register8_t reserved_2[51];
} CCL_t;
/* Edge Detection Enable select */
typedef enum CCL_EDGEDET_enum
{
    CCL_EDGEDET_DIS_gc = (0x00<<7), /* Edge detector is disabled */
    CCL_EDGEDET_EN_gc = (0x01<<7) /* Edge detector is enabled */
} CCL_EDGEDET_t;
/* Filter Selection */
typedef enum CCL_FILTSEL_enum
{
    CCL_FILTSEL_DISABLE_gc = (0x00<<4), /* Filter disabled */
    CCL_FILTSEL_SYNCH_gc = (0x01<<4), /* Synchronizer enabled */
    CCL_FILTSEL_FILTER_gc = (0x02<<4) /* Filter enabled */
} CCL_FILTSEL_t;
/* LUT Input 0 Source Selection */
typedef enum CCL_INSEL0_enum
{
    CCL_INSEL0_MASK_gc = (0x00<<0), /* Masked input */
    CCL_INSEL0_FEEDBACK_gc = (0x01<<0), /* Feedback input source */
    CCL_INSEL0_LINK_gc = (0x02<<0), /* Linked LUT input source */
    CCL_INSEL0_EVENT0_gc = (0x03<<0), /* Event input source 0 */
    CCL_INSEL0_EVENT1_gc = (0x04<<0), /* Event input source 1 */
    CCL_INSEL0_IO_gc = (0x05<<0), /* IO pin LUTn-IN0 input source */
    CCL_INSEL0_AC0_gc = (0x06<<0), /* AC0 OUT input source */
    CCL_INSEL0_TCB0_gc = (0x07<<0), /* TCB0 WO input source */
    CCL_INSEL0_TCA0_gc = (0x08<<0), /* TCA0 WO0 input source */
    CCL_INSEL0_TCD0_gc = (0x09<<0), /* TCD0 WOA input source */
    CCL_INSEL0_USART0_gc = (0x0A<<0), /* USART0 XCK input source */
    CCL_INSEL0_SPI0_gc = (0x0B<<0), /* SPI0 SCK source */
    CCL_INSEL0_AC1_gc = (0x0C<<0), /* AC1 OUT input source */
    CCL_INSEL0_TCB1_gc = (0x0D<<0), /* TCB1 WO input source */
    CCL_INSEL0_AC2_gc = (0x0E<<0) /* AC2 OUT input source */
} CCL_INSEL0_t;
/* LUT Input 1 Source Selection */
typedef enum CCL_INSEL1_enum
{
    CCL_INSEL1_MASK_gc = (0x00<<4), /* Masked input */
    CCL_INSEL1_FEEDBACK_gc = (0x01<<4), /* Feedback input source */
    CCL_INSEL1_LINK_gc = (0x02<<4), /* Linked LUT input source */
    CCL_INSEL1_EVENT0_gc = (0x03<<4), /* Event input source 0 */
    CCL_INSEL1_EVENT1_gc = (0x04<<4), /* Event input source 1 */
    CCL_INSEL1_IO_gc = (0x05<<4), /* IO pin LUTn-N1 input source */
    CCL_INSEL1_AC0_gc = (0x06<<4), /* AC0 OUT input source */
    CCL_INSEL1_TCB0_gc = (0x07<<4), /* TCB0 WO input source */
    CCL_INSEL1_TCA0_gc = (0x08<<4), /* TCA0 WO1 input source */
    CCL_INSEL1_TCD0_gc = (0x09<<4), /* TCD0 WOB input source */
    CCL_INSEL1_USART0_gc = (0x0A<<4), /* USART0 TXD input source */
    CCL_INSEL1_SPI0_gc = (0x0B<<4), /* SPI0 MOSI input source */
    CCL_INSEL1_AC1_gc = (0x0C<<4), /* AC1 OUT input source */
    CCL_INSEL1_TCB1_gc = (0x0D<<4), /* TCB1WO input source */
    CCL_INSEL1_AC2_gc = (0x0E<<4) /* AC2 OUT input source */
} CCL_INSEL1_t;
/* LUT Input 2 Source Selection */
typedef enum CCL_INSEL2_enum
{
    CCL_INSEL2_MASK_gc = (0x00<<0), /* Masked input */
    CCL_INSEL2_FEEDBACK_gc = (0x01<<0), /* Feedback input source */
    CCL_INSEL2_LINK_gc = (0x02<<0), /* Linked LUT input source */
    CCL_INSEL2_EVENT0_gc = (0x03<<0), /* Event input source 0 */
    CCL_INSEL2_EVENT1_gc = (0x04<<0), /* Event input source 1 */
    CCL_INSEL2_IO_gc = (0x05<<0), /* IO pin LUTn-IN2 input source */
    CCL_INSEL2_AC0_gc = (0x06<<0), /* AC0 OUT input source */
    CCL_INSEL2_TCB0_gc = (0x07<<0), /* TCB0 WO input source */
    CCL_INSEL2_TCA0_gc = (0x08<<0), /* TCA0 WO2 input source */
    CCL_INSEL2_TCD0_gc = (0x09<<0), /* TCD0 WOA input source */
    CCL_INSEL2_SPI0_gc = (0x0B<<0), /* SPI0 MISO source */
    CCL_INSEL2_AC1_gc = (0x0C<<0), /* AC1 OUT input source */
    CCL_INSEL2_TCB1_gc = (0x0D<<0), /* TCB1 WO input source */
    CCL_INSEL2_AC2_gc = (0x0E<<0) /* AC2 OUT input source */
} CCL_INSEL2_t;
/* Sequential Selection */
typedef enum CCL_SEQSEL_enum
{
    CCL_SEQSEL_DISABLE_gc = (0x00<<0), /* Sequential logic disabled */
    CCL_SEQSEL_DFF_gc = (0x01<<0), /* D FlipFlop */
    CCL_SEQSEL_JK_gc = (0x02<<0), /* JK FlipFlop */
    CCL_SEQSEL_LATCH_gc = (0x03<<0), /* D Latch */
    CCL_SEQSEL_RS_gc = (0x04<<0) /* RS Latch */
} CCL_SEQSEL_t;
/*
--------------------------------------------------------------------------
CLKCTRL - Clock controller
--------------------------------------------------------------------------
*/
/* Clock controller */
typedef struct CLKCTRL_struct
{
    register8_t MCLKCTRLA; /* MCLK Control A */
    register8_t MCLKCTRLB; /* MCLK Control B */
    register8_t MCLKLOCK; /* MCLK Lock */
    register8_t MCLKSTATUS; /* MCLK Status */
    register8_t reserved_1[12];
    register8_t OSC20MCTRLA; /* OSC20M Control A */
    register8_t OSC20MCALIBA; /* OSC20M Calibration A */
    register8_t OSC20MCALIBB; /* OSC20M Calibration B */
    register8_t reserved_2[5];
    register8_t OSC32KCTRLA; /* OSC32K Control A */
    register8_t reserved_3[3];
    register8_t XOSC32KCTRLA; /* XOSC32K Control A */
    register8_t reserved_4[3];
} CLKCTRL_t;
/* Clock select */
typedef enum CLKCTRL_CLKSEL_enum
{
    CLKCTRL_CLKSEL_OSC20M_gc = (0x00<<0), /* 20MHz internal oscillator */
    CLKCTRL_CLKSEL_OSCULP32K_gc = (0x01<<0), /* 32KHz internal Ultra Low Power oscillator */
    CLKCTRL_CLKSEL_XOSC32K_gc = (0x02<<0), /* 32.768kHz external crystal oscillator */
    CLKCTRL_CLKSEL_EXTCLK_gc = (0x03<<0) /* External clock */
} CLKCTRL_CLKSEL_t;
/* Crystal startup time select */
typedef enum CLKCTRL_CSUT_enum
{
    CLKCTRL_CSUT_1K_gc = (0x00<<4), /* 1K cycles */
    CLKCTRL_CSUT_16K_gc = (0x01<<4), /* 16K cycles */
    CLKCTRL_CSUT_32K_gc = (0x02<<4), /* 32K cycles */
    CLKCTRL_CSUT_64K_gc = (0x03<<4) /* 64K cycles */
} CLKCTRL_CSUT_t;
/* Prescaler division select */
typedef enum CLKCTRL_PDIV_enum
{
    CLKCTRL_PDIV_2X_gc = (0x00<<1), /* 2X */
    CLKCTRL_PDIV_4X_gc = (0x01<<1), /* 4X */
    CLKCTRL_PDIV_8X_gc = (0x02<<1), /* 8X */
    CLKCTRL_PDIV_16X_gc = (0x03<<1), /* 16X */
    CLKCTRL_PDIV_32X_gc = (0x04<<1), /* 32X */
    CLKCTRL_PDIV_64X_gc = (0x05<<1), /* 64X */
    CLKCTRL_PDIV_6X_gc = (0x08<<1), /* 6X */
    CLKCTRL_PDIV_10X_gc = (0x09<<1), /* 10X */
    CLKCTRL_PDIV_12X_gc = (0x0A<<1), /* 12X */
    CLKCTRL_PDIV_24X_gc = (0x0B<<1), /* 24X */
    CLKCTRL_PDIV_48X_gc = (0x0C<<1) /* 48X */
} CLKCTRL_PDIV_t;
/*
--------------------------------------------------------------------------
CPU - CPU
--------------------------------------------------------------------------
*/
/* CCP signature select */
typedef enum CCP_enum
{
    CCP_SPM_gc = (0x9D<<0), /* SPM Instruction Protection */
    CCP_IOREG_gc = (0xD8<<0) /* IO Register Protection */
} CCP_t;
/*
--------------------------------------------------------------------------
CPUINT - Interrupt Controller
--------------------------------------------------------------------------
*/
/* Interrupt Controller */
typedef struct CPUINT_struct
{
    register8_t CTRLA; /* Control A */
    register8_t STATUS; /* Status */
    register8_t LVL0PRI; /* Interrupt Level 0 Priority */
    register8_t LVL1VEC; /* Interrupt Level 1 Priority Vector */
} CPUINT_t;
/*
--------------------------------------------------------------------------
CRCSCAN - CRCSCAN
--------------------------------------------------------------------------
*/
/* CRCSCAN */
typedef struct CRCSCAN_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t STATUS; /* Status */
    register8_t reserved_1[1];
} CRCSCAN_t;
/* CRC Flash Access Mode select */
typedef enum CRCSCAN_MODE_enum
{
    CRCSCAN_MODE_PRIORITY_gc = (0x00<<4) /* Priority to flash */
} CRCSCAN_MODE_t;
/* CRC Source select */
typedef enum CRCSCAN_SRC_enum
{
    CRCSCAN_SRC_FLASH_gc = (0x00<<0), /* CRC on entire flash */
    CRCSCAN_SRC_APPLICATION_gc = (0x01<<0), /* CRC on boot and appl section of flash */
    CRCSCAN_SRC_BOOT_gc = (0x02<<0) /* CRC on boot section of flash */
} CRCSCAN_SRC_t;
/*
--------------------------------------------------------------------------
DAC - Digital to Analog Converter
--------------------------------------------------------------------------
*/
/* Digital to Analog Converter */
typedef struct DAC_struct
{
    register8_t CTRLA; /* Control Register A */
    register8_t DATA; /* DATA Register */
    register8_t reserved_1[2];
} DAC_t;
/*
--------------------------------------------------------------------------
EVSYS - Event System
--------------------------------------------------------------------------
*/
/* Event System */
typedef struct EVSYS_struct
{
    register8_t ASYNCSTROBE; /* Asynchronous Channel Strobe */
    register8_t SYNCSTROBE; /* Synchronous Channel Strobe */
    register8_t ASYNCCH0; /* Asynchronous Channel 0 Generator Selection */
    register8_t ASYNCCH1; /* Asynchronous Channel 1 Generator Selection */
    register8_t ASYNCCH2; /* Asynchronous Channel 2 Generator Selection */
    register8_t ASYNCCH3; /* Asynchronous Channel 3 Generator Selection */
    register8_t reserved_1[4];
    register8_t SYNCCH0; /* Synchronous Channel 0 Generator Selection */
    register8_t SYNCCH1; /* Synchronous Channel 1 Generator Selection */
    register8_t reserved_2[6];
    register8_t ASYNCUSER0; /* Asynchronous User Ch 0 Input Selection - TCB0 */
    register8_t ASYNCUSER1; /* Asynchronous User Ch 1 Input Selection - ADC0 */
    register8_t ASYNCUSER2; /* Asynchronous User Ch 2 Input Selection - CCL LUT0 Event 0 */
    register8_t ASYNCUSER3; /* Asynchronous User Ch 3 Input Selection - CCL LUT1 Event 0 */
    register8_t ASYNCUSER4; /* Asynchronous User Ch 4 Input Selection - CCL LUT0 Event 1 */
    register8_t ASYNCUSER5; /* Asynchronous User Ch 5 Input Selection - CCL LUT1 Event 1 */
    register8_t ASYNCUSER6; /* Asynchronous User Ch 6 Input Selection - TCD0 Event 0 */
    register8_t ASYNCUSER7; /* Asynchronous User Ch 7 Input Selection - TCD0 Event 1 */
    register8_t ASYNCUSER8; /* Asynchronous User Ch 8 Input Selection - Event Out 0 */
    register8_t ASYNCUSER9; /* Asynchronous User Ch 9 Input Selection - Event Out 1 */
    register8_t ASYNCUSER10; /* Asynchronous User Ch 10 Input Selection - Event Out 2 */
    register8_t ASYNCUSER11; /* Asynchronous User Ch 11 Input Selection - TCB1 */
    register8_t ASYNCUSER12; /* Asynchronous User Ch 12 Input Selection - ADC1 */
    register8_t reserved_3[3];
    register8_t SYNCUSER0; /* Synchronous User Ch 0 - TCA0 */
    register8_t SYNCUSER1; /* Synchronous User Ch 1 - USART0 */
    register8_t reserved_4[28];
} EVSYS_t;
/* Asynchronous Channel 0 Generator Selection */
typedef enum EVSYS_ASYNCCH0_enum
{
    EVSYS_ASYNCCH0_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCCH0_CCL_LUT0_gc = (0x01<<0), /* Configurable Custom Logic LUT0 */
    EVSYS_ASYNCCH0_CCL_LUT1_gc = (0x02<<0), /* Configurable Custom Logic LUT1 */
    EVSYS_ASYNCCH0_AC0_OUT_gc = (0x03<<0), /* Analog Comparator 0 out */
    EVSYS_ASYNCCH0_TCD0_CMPBCLR_gc = (0x04<<0), /* Timer/Counter D0 compare B clear */
    EVSYS_ASYNCCH0_TCD0_CMPASET_gc = (0x05<<0), /* Timer/Counter D0 compare A set */
    EVSYS_ASYNCCH0_TCD0_CMPBSET_gc = (0x06<<0), /* Timer/Counter D0 compare B set */
    EVSYS_ASYNCCH0_TCD0_PROGEV_gc = (0x07<<0), /* Timer/Counter D0 program event */
    EVSYS_ASYNCCH0_RTC_OVF_gc = (0x08<<0), /* Real Time Counter overflow */
    EVSYS_ASYNCCH0_RTC_CMP_gc = (0x09<<0), /* Real Time Counter compare */
    EVSYS_ASYNCCH0_PORTA_PIN0_gc = (0x0A<<0), /* Asynchronous Event from Pin PA0 */
    EVSYS_ASYNCCH0_PORTA_PIN1_gc = (0x0B<<0), /* Asynchronous Event from Pin PA1 */
    EVSYS_ASYNCCH0_PORTA_PIN2_gc = (0x0C<<0), /* Asynchronous Event from Pin PA2 */
    EVSYS_ASYNCCH0_PORTA_PIN3_gc = (0x0D<<0), /* Asynchronous Event from Pin PA3 */
    EVSYS_ASYNCCH0_PORTA_PIN4_gc = (0x0E<<0), /* Asynchronous Event from Pin PA4 */
    EVSYS_ASYNCCH0_PORTA_PIN5_gc = (0x0F<<0), /* Asynchronous Event from Pin PA5 */
    EVSYS_ASYNCCH0_PORTA_PIN6_gc = (0x10<<0), /* Asynchronous Event from Pin PA6 */
    EVSYS_ASYNCCH0_PORTA_PIN7_gc = (0x11<<0), /* Asynchronous Event from Pin PA7 */
    EVSYS_ASYNCCH0_UPDI_gc = (0x12<<0), /* Unified Program and debug interface */
    EVSYS_ASYNCCH0_AC1_OUT_gc = (0x13<<0), /* Analog Comparator 1 out */
    EVSYS_ASYNCCH0_AC2_OUT_gc = (0x14<<0) /* Analog Comparator 2 out */
} EVSYS_ASYNCCH0_t;
/* Asynchronous Channel 1 Generator Selection */
typedef enum EVSYS_ASYNCCH1_enum
{
    EVSYS_ASYNCCH1_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCCH1_CCL_LUT0_gc = (0x01<<0), /* Configurable custom logic LUT0 */
    EVSYS_ASYNCCH1_CCL_LUT1_gc = (0x02<<0), /* Configurable custom logic LUT1 */
    EVSYS_ASYNCCH1_AC0_OUT_gc = (0x03<<0), /* Analog Comparator 0 out */
    EVSYS_ASYNCCH1_TCD0_CMPBCLR_gc = (0x04<<0), /* Timer/Counter D0 compare B clear */
    EVSYS_ASYNCCH1_TCD0_CMPASET_gc = (0x05<<0), /* Timer/Counter D0 compare A set */
    EVSYS_ASYNCCH1_TCD0_CMPBSET_gc = (0x06<<0), /* Timer/Counter D0 compare B set */
    EVSYS_ASYNCCH1_TCD0_PROGEV_gc = (0x07<<0), /* Timer/Counter D0 program event */
    EVSYS_ASYNCCH1_RTC_OVF_gc = (0x08<<0), /* Real Time Counter overflow */
    EVSYS_ASYNCCH1_RTC_CMP_gc = (0x09<<0), /* Real Time Counter compare */
    EVSYS_ASYNCCH1_PORTB_PIN0_gc = (0x0A<<0), /* Asynchronous Event from Pin PB0 */
    EVSYS_ASYNCCH1_PORTB_PIN1_gc = (0x0B<<0), /* Asynchronous Event from Pin PB1 */
    EVSYS_ASYNCCH1_PORTB_PIN2_gc = (0x0C<<0), /* Asynchronous Event from Pin PB2 */
    EVSYS_ASYNCCH1_PORTB_PIN3_gc = (0x0D<<0), /* Asynchronous Event from Pin PB3 */
    EVSYS_ASYNCCH1_PORTB_PIN4_gc = (0x0E<<0), /* Asynchronous Event from Pin PB4 */
    EVSYS_ASYNCCH1_PORTB_PIN5_gc = (0x0F<<0), /* Asynchronous Event from Pin PB5 */
    EVSYS_ASYNCCH1_PORTB_PIN6_gc = (0x10<<0), /* Asynchronous Event from Pin PB6 */
    EVSYS_ASYNCCH1_PORTB_PIN7_gc = (0x11<<0), /* Asynchronous Event from Pin PB7 */
    EVSYS_ASYNCCH1_AC1_OUT_gc = (0x12<<0), /* Analog Comparator 1 out */
    EVSYS_ASYNCCH1_AC2_OUT_gc = (0x13<<0) /* Analog Comparator 2 out */
} EVSYS_ASYNCCH1_t;
/* Asynchronous Channel 2 Generator Selection */
typedef enum EVSYS_ASYNCCH2_enum
{
    EVSYS_ASYNCCH2_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCCH2_CCL_LUT0_gc = (0x01<<0), /* Configurable Custom Logic LUT0 */
    EVSYS_ASYNCCH2_CCL_LUT1_gc = (0x02<<0), /* Configurable Custom Logic LUT1 */
    EVSYS_ASYNCCH2_AC0_OUT_gc = (0x03<<0), /* Analog Comparator 0 out */
    EVSYS_ASYNCCH2_TCD0_CMPBCLR_gc = (0x04<<0), /* Timer/Counter D0 compare B clear */
    EVSYS_ASYNCCH2_TCD0_CMPASET_gc = (0x05<<0), /* Timer/Counter D0 compare A set */
    EVSYS_ASYNCCH2_TCD0_CMPBSET_gc = (0x06<<0), /* Timer/Counter D0 compare B set */
    EVSYS_ASYNCCH2_TCD0_PROGEV_gc = (0x07<<0), /* Timer/Counter D0 program event */
    EVSYS_ASYNCCH2_RTC_OVF_gc = (0x08<<0), /* Real Time Counter overflow */
    EVSYS_ASYNCCH2_RTC_CMP_gc = (0x09<<0), /* Real Time Counter compare */
    EVSYS_ASYNCCH2_PORTC_PIN0_gc = (0x0A<<0), /* Asynchronous Event from Pin PC0 */
    EVSYS_ASYNCCH2_PORTC_PIN1_gc = (0x0B<<0), /* Asynchronous Event from Pin PC1 */
    EVSYS_ASYNCCH2_PORTC_PIN2_gc = (0x0C<<0), /* Asynchronous Event from Pin PC2 */
    EVSYS_ASYNCCH2_PORTC_PIN3_gc = (0x0D<<0), /* Asynchronous Event from Pin PC3 */
    EVSYS_ASYNCCH2_PORTC_PIN4_gc = (0x0E<<0), /* Asynchronous Event from Pin PC4 */
    EVSYS_ASYNCCH2_PORTC_PIN5_gc = (0x0F<<0), /* Asynchronous Event from Pin PC5 */
    EVSYS_ASYNCCH2_AC1_OUT_gc = (0x10<<0), /* Analog Comparator 1 out */
    EVSYS_ASYNCCH2_AC2_OUT_gc = (0x11<<0) /* Analog Comparator 2 out */
} EVSYS_ASYNCCH2_t;
/* Asynchronous Channel 3 Generator Selection */
typedef enum EVSYS_ASYNCCH3_enum
{
    EVSYS_ASYNCCH3_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCCH3_CCL_LUT0_gc = (0x01<<0), /* Configurable custom logic LUT0 */
    EVSYS_ASYNCCH3_CCL_LUT1_gc = (0x02<<0), /* Configurable custom logic LUT1 */
    EVSYS_ASYNCCH3_AC0_OUT_gc = (0x03<<0), /* Analog Comparator 0 out */
    EVSYS_ASYNCCH3_TCD0_CMPBCLR_gc = (0x04<<0), /* Timer/Counter type D compare B clear */
    EVSYS_ASYNCCH3_TCD0_CMPASET_gc = (0x05<<0), /* Timer/Counter type D compare A set */
    EVSYS_ASYNCCH3_TCD0_CMPBSET_gc = (0x06<<0), /* Timer/Counter type D compare B set */
    EVSYS_ASYNCCH3_TCD0_PROGEV_gc = (0x07<<0), /* Timer/Counter type D program event */
    EVSYS_ASYNCCH3_RTC_OVF_gc = (0x08<<0), /* Real Time Counter overflow */
    EVSYS_ASYNCCH3_RTC_CMP_gc = (0x09<<0), /* Real Time Counter compare */
    EVSYS_ASYNCCH3_PIT_DIV8192_gc = (0x0A<<0), /* Periodic Interrupt CLK_RTC div 8192 */
    EVSYS_ASYNCCH3_PIT_DIV4096_gc = (0x0B<<0), /* Periodic Interrupt CLK_RTC div 4096 */
    EVSYS_ASYNCCH3_PIT_DIV2048_gc = (0x0C<<0), /* Periodic Interrupt CLK_RTC div 2048 */
    EVSYS_ASYNCCH3_PIT_DIV1024_gc = (0x0D<<0), /* Periodic Interrupt CLK_RTC div 1024 */
    EVSYS_ASYNCCH3_PIT_DIV512_gc = (0x0E<<0), /* Periodic Interrupt CLK_RTC div 512 */
    EVSYS_ASYNCCH3_PIT_DIV256_gc = (0x0F<<0), /* Periodic Interrupt CLK_RTC div 256 */
    EVSYS_ASYNCCH3_PIT_DIV128_gc = (0x10<<0), /* Periodic Interrupt CLK_RTC div 128 */
    EVSYS_ASYNCCH3_PIT_DIV64_gc = (0x11<<0), /* Periodic Interrupt CLK_RTC div 64 */
    EVSYS_ASYNCCH3_AC1_OUT_gc = (0x12<<0), /* Analog Comparator 1 out */
    EVSYS_ASYNCCH3_AC2_OUT_gc = (0x13<<0) /* Analog Comparator 2 out */
} EVSYS_ASYNCCH3_t;
/* Asynchronous User Ch 0 Input Selection - TCB0 */
typedef enum EVSYS_ASYNCUSER0_enum
{
    EVSYS_ASYNCUSER0_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER0_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER0_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER0_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER0_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER0_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER0_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER0_t;
/* Asynchronous User Ch 1 Input Selection - ADC0 */
typedef enum EVSYS_ASYNCUSER1_enum
{
    EVSYS_ASYNCUSER1_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER1_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER1_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER1_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER1_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER1_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER1_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER1_t;
/* Asynchronous User Ch 10 Input Selection - Event Out 2 */
typedef enum EVSYS_ASYNCUSER10_enum
{
    EVSYS_ASYNCUSER10_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER10_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER10_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER10_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER10_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER10_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER10_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER10_t;
/* Asynchronous User Ch 11 Input Selection - TCB1 */
typedef enum EVSYS_ASYNCUSER11_enum
{
    EVSYS_ASYNCUSER11_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER11_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER11_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER11_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER11_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER11_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER11_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER11_t;
/* Asynchronous User Ch 12 Input Selection - ADC0 */
typedef enum EVSYS_ASYNCUSER12_enum
{
    EVSYS_ASYNCUSER12_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER12_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER12_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER12_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER12_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER12_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER12_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER12_t;
/* Asynchronous User Ch 2 Input Selection - CCL LUT0 Event 0 */
typedef enum EVSYS_ASYNCUSER2_enum
{
    EVSYS_ASYNCUSER2_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER2_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER2_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER2_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER2_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER2_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER2_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER2_t;
/* Asynchronous User Ch 3 Input Selection - CCL LUT1 Event 0 */
typedef enum EVSYS_ASYNCUSER3_enum
{
    EVSYS_ASYNCUSER3_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER3_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER3_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER3_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER3_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER3_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER3_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER3_t;
/* Asynchronous User Ch 4 Input Selection - CCL LUT0 Event 1 */
typedef enum EVSYS_ASYNCUSER4_enum
{
    EVSYS_ASYNCUSER4_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER4_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER4_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER4_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER4_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER4_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER4_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER4_t;
/* Asynchronous User Ch 5 Input Selection - CCL LUT1 Event 1 */
typedef enum EVSYS_ASYNCUSER5_enum
{
    EVSYS_ASYNCUSER5_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER5_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER5_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER5_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER5_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER5_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER5_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER5_t;
/* Asynchronous User Ch 6 Input Selection - TCD0 Event 0 */
typedef enum EVSYS_ASYNCUSER6_enum
{
    EVSYS_ASYNCUSER6_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER6_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER6_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER6_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER6_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER6_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER6_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER6_t;
/* Asynchronous User Ch 7 Input Selection - TCD0 Event 1 */
typedef enum EVSYS_ASYNCUSER7_enum
{
    EVSYS_ASYNCUSER7_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER7_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER7_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER7_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER7_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER7_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER7_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER7_t;
/* Asynchronous User Ch 8 Input Selection - Event Out 0 */
typedef enum EVSYS_ASYNCUSER8_enum
{
    EVSYS_ASYNCUSER8_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER8_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER8_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER8_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER8_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER8_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER8_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER8_t;
/* Asynchronous User Ch 9 Input Selection - Event Out 1 */
typedef enum EVSYS_ASYNCUSER9_enum
{
    EVSYS_ASYNCUSER9_OFF_gc = (0x00<<0), /* Off */
    EVSYS_ASYNCUSER9_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_ASYNCUSER9_SYNCCH1_gc = (0x02<<0), /* Synchronous Event Channel 1 */
    EVSYS_ASYNCUSER9_ASYNCCH0_gc = (0x03<<0), /* Asynchronous Event Channel 0 */
    EVSYS_ASYNCUSER9_ASYNCCH1_gc = (0x04<<0), /* Asynchronous Event Channel 1 */
    EVSYS_ASYNCUSER9_ASYNCCH2_gc = (0x05<<0), /* Asynchronous Event Channel 2 */
    EVSYS_ASYNCUSER9_ASYNCCH3_gc = (0x06<<0) /* Asynchronous Event Channel 3 */
} EVSYS_ASYNCUSER9_t;
/* Synchronous Channel 0 Generator Selection */
typedef enum EVSYS_SYNCCH0_enum
{
    EVSYS_SYNCCH0_OFF_gc = (0x00<<0), /* Off */
    EVSYS_SYNCCH0_TCB0_gc = (0x01<<0), /* Timer/Counter B0 */
    EVSYS_SYNCCH0_TCA0_OVF_LUNF_gc = (0x02<<0), /* Timer/Counter A0 overflow */
    EVSYS_SYNCCH0_TCA0_HUNF_gc = (0x03<<0), /* Timer/Counter A0 underflow high byte (split mode) */
    EVSYS_SYNCCH0_TCA0_CMP0_gc = (0x04<<0), /* Timer/Counter A0 compare 0 */
    EVSYS_SYNCCH0_TCA0_CMP1_gc = (0x05<<0), /* Timer/Counter A0 compare 1 */
    EVSYS_SYNCCH0_TCA0_CMP2_gc = (0x06<<0), /* Timer/Counter A0 compare 2 */
    EVSYS_SYNCCH0_PORTC_PIN0_gc = (0x07<<0), /* Synchronous Event from Pin PC0 */
    EVSYS_SYNCCH0_PORTC_PIN1_gc = (0x08<<0), /* Synchronous Event from Pin PC1 */
    EVSYS_SYNCCH0_PORTC_PIN2_gc = (0x09<<0), /* Synchronous Event from Pin PC2 */
    EVSYS_SYNCCH0_PORTC_PIN3_gc = (0x0A<<0), /* Synchronous Event from Pin PC3 */
    EVSYS_SYNCCH0_PORTC_PIN4_gc = (0x0B<<0), /* Synchronous Event from Pin PC4 */
    EVSYS_SYNCCH0_PORTC_PIN5_gc = (0x0C<<0), /* Synchronous Event from Pin PC5 */
    EVSYS_SYNCCH0_PORTA_PIN0_gc = (0x0D<<0), /* Synchronous Event from Pin PA0 */
    EVSYS_SYNCCH0_PORTA_PIN1_gc = (0x0E<<0), /* Synchronous Event from Pin PA1 */
    EVSYS_SYNCCH0_PORTA_PIN2_gc = (0x0F<<0), /* Synchronous Event from Pin PA2 */
    EVSYS_SYNCCH0_PORTA_PIN3_gc = (0x10<<0), /* Synchronous Event from Pin PA3 */
    EVSYS_SYNCCH0_PORTA_PIN4_gc = (0x11<<0), /* Synchronous Event from Pin PA4 */
    EVSYS_SYNCCH0_PORTA_PIN5_gc = (0x12<<0), /* Synchronous Event from Pin PA5 */
    EVSYS_SYNCCH0_PORTA_PIN6_gc = (0x13<<0), /* Synchronous Event from Pin PA6 */
    EVSYS_SYNCCH0_PORTA_PIN7_gc = (0x14<<0), /* Synchronous Event from Pin PA7 */
    EVSYS_SYNCCH0_TCB1_gc = (0x15<<0) /* Timer/Counter B1 */
} EVSYS_SYNCCH0_t;
/* Synchronous Channel 1 Generator Selection */
typedef enum EVSYS_SYNCCH1_enum
{
    EVSYS_SYNCCH1_OFF_gc = (0x00<<0), /* Off */
    EVSYS_SYNCCH1_TCB0_gc = (0x01<<0), /* Timer/Counter B0 */
    EVSYS_SYNCCH1_TCA0_OVF_LUNF_gc = (0x02<<0), /* Timer/Counter A0 overflow */
    EVSYS_SYNCCH1_TCA0_HUNF_gc = (0x03<<0), /* Timer/Counter A0 underflow high byte (split mode) */
    EVSYS_SYNCCH1_TCA0_CMP0_gc = (0x04<<0), /* Timer/Counter A0 compare 0 */
    EVSYS_SYNCCH1_TCA0_CMP1_gc = (0x05<<0), /* Timer/Counter A0 compare 1 */
    EVSYS_SYNCCH1_TCA0_CMP2_gc = (0x06<<0), /* Timer/Counter A0 compare 2 */
    EVSYS_SYNCCH1_PORTB_PIN0_gc = (0x08<<0), /* Synchronous Event from Pin PB0 */
    EVSYS_SYNCCH1_PORTB_PIN1_gc = (0x09<<0), /* Synchronous Event from Pin PB1 */
    EVSYS_SYNCCH1_PORTB_PIN2_gc = (0x0A<<0), /* Synchronous Event from Pin PB2 */
    EVSYS_SYNCCH1_PORTB_PIN3_gc = (0x0B<<0), /* Synchronous Event from Pin PB3 */
    EVSYS_SYNCCH1_PORTB_PIN4_gc = (0x0C<<0), /* Synchronous Event from Pin PB4 */
    EVSYS_SYNCCH1_PORTB_PIN5_gc = (0x0D<<0), /* Synchronous Event from Pin PB5 */
    EVSYS_SYNCCH1_PORTB_PIN6_gc = (0x0E<<0), /* Synchronous Event from Pin PB6 */
    EVSYS_SYNCCH1_PORTB_PIN7_gc = (0x0F<<0), /* Synchronous Event from Pin PB7 */
    EVSYS_SYNCCH1_TCB1_gc = (0x10<<0) /* Timer/Counter B1 */
} EVSYS_SYNCCH1_t;
/* Synchronous User Ch 0 - TCA0 select */
typedef enum EVSYS_SYNCUSER0_enum
{
    EVSYS_SYNCUSER0_OFF_gc = (0x00<<0), /* Off */
    EVSYS_SYNCUSER0_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_SYNCUSER0_SYNCCH1_gc = (0x02<<0) /* Synchronous Event Channel 1 */
} EVSYS_SYNCUSER0_t;
/* Synchronous User Ch 1 - USART0 select */
typedef enum EVSYS_SYNCUSER1_enum
{
    EVSYS_SYNCUSER1_OFF_gc = (0x00<<0), /* Off */
    EVSYS_SYNCUSER1_SYNCCH0_gc = (0x01<<0), /* Synchronous Event Channel 0 */
    EVSYS_SYNCUSER1_SYNCCH1_gc = (0x02<<0) /* Synchronous Event Channel 1 */
} EVSYS_SYNCUSER1_t;
/*
--------------------------------------------------------------------------
FUSE - Fuses
--------------------------------------------------------------------------
*/
/* Fuses */
typedef struct FUSE_struct
{
    register8_t WDTCFG; /* Watchdog Configuration */
    register8_t BODCFG; /* BOD Configuration */
    register8_t OSCCFG; /* Oscillator Configuration */
    register8_t reserved_1[1];
    register8_t TCD0CFG; /* TCD0 Configuration */
    register8_t SYSCFG0; /* System Configuration 0 */
    register8_t SYSCFG1; /* System Configuration 1 */
    register8_t APPEND; /* Application Code Section End */
    register8_t BOOTEND; /* Boot Section End */
} FUSE_t;
/* avr-libc typedef for avr/fuse.h */
typedef FUSE_t NVM_FUSES_t;
/* BOD Operation in Active Mode select */
typedef enum ACTIVE_enum
{
    ACTIVE_DIS_gc = (0x00<<2), /* Disabled */
    ACTIVE_ENABLED_gc = (0x01<<2), /* Enabled */
    ACTIVE_SAMPLED_gc = (0x02<<2), /* Sampled */
    ACTIVE_ENWAKE_gc = (0x03<<2) /* Enabled with wake-up halted until BOD is ready */
} ACTIVE_t;
/* CRC Source select */
typedef enum CRCSRC_enum
{
    CRCSRC_FLASH_gc = (0x00<<6), /* The CRC is performed on the entire Flash (boot, application code and application data section). */
    CRCSRC_BOOT_gc = (0x01<<6), /* The CRC is performed on the boot section of Flash */
    CRCSRC_BOOTAPP_gc = (0x02<<6), /* The CRC is performed on the boot and application code section of Flash */
    CRCSRC_NOCRC_gc = (0x03<<6) /* Disable CRC. */
} CRCSRC_t;
/* Frequency Select */
typedef enum FREQSEL_enum
{
    FREQSEL_16MHZ_gc = (0x01<<0), /* 16 MHz */
    FREQSEL_20MHZ_gc = (0x02<<0) /* 20 MHz */
} FREQSEL_t;
/* BOD Level select */
typedef enum LVL_enum
{
    LVL_BODLEVEL0_gc = (0x00<<5), /* 1.8 V */
    LVL_BODLEVEL2_gc = (0x02<<5), /* 2.6 V */
    LVL_BODLEVEL7_gc = (0x07<<5) /* 4.2 V */
} LVL_t;
/* Watchdog Timeout Period select */
typedef enum PERIOD_enum
{
    PERIOD_OFF_gc = (0x00<<0), /* Off */
    PERIOD_8CLK_gc = (0x01<<0), /* 8 cycles (8ms) */
    PERIOD_16CLK_gc = (0x02<<0), /* 16 cycles (16ms) */
    PERIOD_32CLK_gc = (0x03<<0), /* 32 cycles (32ms) */
    PERIOD_64CLK_gc = (0x04<<0), /* 64 cycles (64ms) */
    PERIOD_128CLK_gc = (0x05<<0), /* 128 cycles (0.128s) */
    PERIOD_256CLK_gc = (0x06<<0), /* 256 cycles (0.256s) */
    PERIOD_512CLK_gc = (0x07<<0), /* 512 cycles (0.512s) */
    PERIOD_1KCLK_gc = (0x08<<0), /* 1K cycles (1.0s) */
    PERIOD_2KCLK_gc = (0x09<<0), /* 2K cycles (2.0s) */
    PERIOD_4KCLK_gc = (0x0A<<0), /* 4K cycles (4.1s) */
    PERIOD_8KCLK_gc = (0x0B<<0) /* 8K cycles (8.2s) */
} PERIOD_t;
/* Reset Pin Configuration select */
typedef enum RSTPINCFG_enum
{
    RSTPINCFG_GPIO_gc = (0x00<<2), /* GPIO mode */
    RSTPINCFG_UPDI_gc = (0x01<<2), /* UPDI mode */
    RSTPINCFG_RST_gc = (0x02<<2) /* Reset mode */
} RSTPINCFG_t;
/* BOD Sample Frequency select */
typedef enum SAMPFREQ_enum
{
    SAMPFREQ_1KHZ_gc = (0x00<<4), /* 1kHz sampling frequency */
    SAMPFREQ_125HZ_gc = (0x01<<4) /* 125Hz sampling frequency */
} SAMPFREQ_t;
/* BOD Operation in Sleep Mode select */
typedef enum SLEEP_enum
{
    SLEEP_DIS_gc = (0x00<<0), /* Disabled */
    SLEEP_ENABLED_gc = (0x01<<0), /* Enabled */
    SLEEP_SAMPLED_gc = (0x02<<0) /* Sampled */
} SLEEP_t;
/* Startup Time select */
typedef enum SUT_enum
{
    SUT_0MS_gc = (0x00<<0), /* 0 ms */
    SUT_1MS_gc = (0x01<<0), /* 1 ms */
    SUT_2MS_gc = (0x02<<0), /* 2 ms */
    SUT_4MS_gc = (0x03<<0), /* 4 ms */
    SUT_8MS_gc = (0x04<<0), /* 8 ms */
    SUT_16MS_gc = (0x05<<0), /* 16 ms */
    SUT_32MS_gc = (0x06<<0), /* 32 ms */
    SUT_64MS_gc = (0x07<<0) /* 64 ms */
} SUT_t;
/* Watchdog Window Timeout Period select */
typedef enum WINDOW_enum
{
    WINDOW_OFF_gc = (0x00<<4), /* Off */
    WINDOW_8CLK_gc = (0x01<<4), /* 8 cycles (8ms) */
    WINDOW_16CLK_gc = (0x02<<4), /* 16 cycles (16ms) */
    WINDOW_32CLK_gc = (0x03<<4), /* 32 cycles (32ms) */
    WINDOW_64CLK_gc = (0x04<<4), /* 64 cycles (64ms) */
    WINDOW_128CLK_gc = (0x05<<4), /* 128 cycles (0.128s) */
    WINDOW_256CLK_gc = (0x06<<4), /* 256 cycles (0.256s) */
    WINDOW_512CLK_gc = (0x07<<4), /* 512 cycles (0.512s) */
    WINDOW_1KCLK_gc = (0x08<<4), /* 1K cycles (1.0s) */
    WINDOW_2KCLK_gc = (0x09<<4), /* 2K cycles (2.0s) */
    WINDOW_4KCLK_gc = (0x0A<<4), /* 4K cycles (4.1s) */
    WINDOW_8KCLK_gc = (0x0B<<4) /* 8K cycles (8.2s) */
} WINDOW_t;
/*
--------------------------------------------------------------------------
LOCKBIT - Lockbit
--------------------------------------------------------------------------
*/
/* Lockbit */
typedef struct LOCKBIT_struct
{
    register8_t LOCKBIT; /* Lock bits */
} LOCKBIT_t;
/* Lock Bits select */
typedef enum LB_enum
{
    LB_RWLOCK_gc = (0x3A<<0), /* Read and write lock */
    LB_NOLOCK_gc = (0xC5<<0) /* No locks */
} LB_t;
/*
--------------------------------------------------------------------------
NVMCTRL - Non-volatile Memory Controller
--------------------------------------------------------------------------
*/
/* Non-volatile Memory Controller */
typedef struct NVMCTRL_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t STATUS; /* Status */
    register8_t INTCTRL; /* Interrupt Control */
    register8_t INTFLAGS; /* Interrupt Flags */
    register8_t reserved_1[1];
    __extension__ union { register16_t DATA; struct { register8_t DATAL; register8_t DATAH; }; }; /* Data */
    __extension__ union { register16_t ADDR; struct { register8_t ADDRL; register8_t ADDRH; }; }; /* Address */
    register8_t reserved_2[6];
} NVMCTRL_t;
/* Command select */
typedef enum NVMCTRL_CMD_enum
{
    NVMCTRL_CMD_NONE_gc = (0x00<<0), /* No Command */
    NVMCTRL_CMD_PAGEWRITE_gc = (0x01<<0), /* Write page */
    NVMCTRL_CMD_PAGEERASE_gc = (0x02<<0), /* Erase page */
    NVMCTRL_CMD_PAGEERASEWRITE_gc = (0x03<<0), /* Erase and write page */
    NVMCTRL_CMD_PAGEBUFCLR_gc = (0x04<<0), /* Page buffer clear */
    NVMCTRL_CMD_CHIPERASE_gc = (0x05<<0), /* Chip erase */
    NVMCTRL_CMD_EEERASE_gc = (0x06<<0), /* EEPROM erase */
    NVMCTRL_CMD_FUSEWRITE_gc = (0x07<<0) /* Write fuse (PDI only) */
} NVMCTRL_CMD_t;
/*
--------------------------------------------------------------------------
PORT - I/O Ports
--------------------------------------------------------------------------
*/
/* I/O Ports */
typedef struct PORT_struct
{
    register8_t DIR; /* Data Direction */
    register8_t DIRSET; /* Data Direction Set */
    register8_t DIRCLR; /* Data Direction Clear */
    register8_t DIRTGL; /* Data Direction Toggle */
    register8_t OUT; /* Output Value */
    register8_t OUTSET; /* Output Value Set */
    register8_t OUTCLR; /* Output Value Clear */
    register8_t OUTTGL; /* Output Value Toggle */
    register8_t IN; /* Input Value */
    register8_t INTFLAGS; /* Interrupt Flags */
    register8_t reserved_1[6];
    register8_t PIN0CTRL; /* Pin 0 Control */
    register8_t PIN1CTRL; /* Pin 1 Control */
    register8_t PIN2CTRL; /* Pin 2 Control */
    register8_t PIN3CTRL; /* Pin 3 Control */
    register8_t PIN4CTRL; /* Pin 4 Control */
    register8_t PIN5CTRL; /* Pin 5 Control */
    register8_t PIN6CTRL; /* Pin 6 Control */
    register8_t PIN7CTRL; /* Pin 7 Control */
    register8_t reserved_2[8];
} PORT_t;
/* Input/Sense Configuration select */
typedef enum PORT_ISC_enum
{
    PORT_ISC_INTDISABLE_gc = (0x00<<0), /* Interrupt disabled but input buffer enabled */
    PORT_ISC_BOTHEDGES_gc = (0x01<<0), /* Sense Both Edges */
    PORT_ISC_RISING_gc = (0x02<<0), /* Sense Rising Edge */
    PORT_ISC_FALLING_gc = (0x03<<0), /* Sense Falling Edge */
    PORT_ISC_INPUT_DISABLE_gc = (0x04<<0), /* Digital Input Buffer disabled */
    PORT_ISC_LEVEL_gc = (0x05<<0) /* Sense low Level */
} PORT_ISC_t;
/*
--------------------------------------------------------------------------
PORTMUX - Port Multiplexer
--------------------------------------------------------------------------
*/
/* Port Multiplexer */
typedef struct PORTMUX_struct
{
    register8_t CTRLA; /* Port Multiplexer Control A */
    register8_t CTRLB; /* Port Multiplexer Control B */
    register8_t CTRLC; /* Port Multiplexer Control C */
    register8_t CTRLD; /* Port Multiplexer Control D */
    register8_t reserved_1[12];
} PORTMUX_t;
/* Configurable Custom Logic LUT0 select */
typedef enum PORTMUX_LUT0_enum
{
    PORTMUX_LUT0_DEFAULT_gc = (0x00<<4), /* Default pin */
    PORTMUX_LUT0_ALTERNATE_gc = (0x01<<4) /* Alternate pin */
} PORTMUX_LUT0_t;
/* Configurable Custom Logic LUT1 select */
typedef enum PORTMUX_LUT1_enum
{
    PORTMUX_LUT1_DEFAULT_gc = (0x00<<5), /* Default pin */
    PORTMUX_LUT1_ALTERNATE_gc = (0x01<<5) /* Alternate pin */
} PORTMUX_LUT1_t;
/* Port Multiplexer SPI0 select */
typedef enum PORTMUX_SPI0_enum
{
    PORTMUX_SPI0_DEFAULT_gc = (0x00<<2), /* Default pins */
    PORTMUX_SPI0_ALTERNATE_gc = (0x01<<2) /* Alternate pins */
} PORTMUX_SPI0_t;
/* Port Multiplexer TCA0 Output 0 select */
typedef enum PORTMUX_TCA00_enum
{
    PORTMUX_TCA00_DEFAULT_gc = (0x00<<0), /* Default pin */
    PORTMUX_TCA00_ALTERNATE_gc = (0x01<<0) /* Alternate pin */
} PORTMUX_TCA00_t;
/* Port Multiplexer TCA0 Output 1 select */
typedef enum PORTMUX_TCA01_enum
{
    PORTMUX_TCA01_DEFAULT_gc = (0x00<<1), /* Default pin */
    PORTMUX_TCA01_ALTERNATE_gc = (0x01<<1) /* Alternate pin */
} PORTMUX_TCA01_t;
/* Port Multiplexer TCA0 Output 2 select */
typedef enum PORTMUX_TCA02_enum
{
    PORTMUX_TCA02_DEFAULT_gc = (0x00<<2), /* Default pin */
    PORTMUX_TCA02_ALTERNATE_gc = (0x01<<2) /* Alternate pin */
} PORTMUX_TCA02_t;
/* Port Multiplexer TCA0 Output 3 select */
typedef enum PORTMUX_TCA03_enum
{
    PORTMUX_TCA03_DEFAULT_gc = (0x00<<3), /* Default pin */
    PORTMUX_TCA03_ALTERNATE_gc = (0x01<<3) /* Alternate pin */
} PORTMUX_TCA03_t;
/* Port Multiplexer TCA0 Output 4 select */
typedef enum PORTMUX_TCA04_enum
{
    PORTMUX_TCA04_DEFAULT_gc = (0x00<<4), /* Default pin */
    PORTMUX_TCA04_ALTERNATE_gc = (0x01<<4) /* Alternate pin */
} PORTMUX_TCA04_t;
/* Port Multiplexer TCA0 Output 5 select */
typedef enum PORTMUX_TCA05_enum
{
    PORTMUX_TCA05_DEFAULT_gc = (0x00<<5), /* Default pin */
    PORTMUX_TCA05_ALTERNATE_gc = (0x01<<5) /* Alternate pin */
} PORTMUX_TCA05_t;
/* Port Multiplexer TCB0 select */
typedef enum PORTMUX_TCB0_enum
{
    PORTMUX_TCB0_DEFAULT_gc = (0x00<<0), /* Default pin */
    PORTMUX_TCB0_ALTERNATE_gc = (0x01<<0) /* Alternate pin */
} PORTMUX_TCB0_t;
/* Port Multiplexer TCB1 select */
typedef enum PORTMUX_TCB1_enum
{
    PORTMUX_TCB1_DEFAULT_gc = (0x00<<1), /* Default pin */
    PORTMUX_TCB1_ALTERNATE_gc = (0x01<<1) /* Alternate pin */
} PORTMUX_TCB1_t;
/* Port Multiplexer TWI0 select */
typedef enum PORTMUX_TWI0_enum
{
    PORTMUX_TWI0_DEFAULT_gc = (0x00<<4), /* Default pins */
    PORTMUX_TWI0_ALTERNATE_gc = (0x01<<4) /* Alternate pins */
} PORTMUX_TWI0_t;
/* Port Multiplexer USART0 select */
typedef enum PORTMUX_USART0_enum
{
    PORTMUX_USART0_DEFAULT_gc = (0x00<<0), /* Default pins */
    PORTMUX_USART0_ALTERNATE_gc = (0x01<<0) /* Alternate pins */
} PORTMUX_USART0_t;
/*
--------------------------------------------------------------------------
RSTCTRL - Reset controller
--------------------------------------------------------------------------
*/
/* Reset controller */
typedef struct RSTCTRL_struct
{
    register8_t RSTFR; /* Reset Flags */
    register8_t SWRR; /* Software Reset */
    register8_t reserved_1[2];
} RSTCTRL_t;
/*
--------------------------------------------------------------------------
RTC - Real-Time Counter
--------------------------------------------------------------------------
*/
/* Real-Time Counter */
typedef struct RTC_struct
{
    register8_t CTRLA; /* Control A */
    register8_t STATUS; /* Status */
    register8_t INTCTRL; /* Interrupt Control */
    register8_t INTFLAGS; /* Interrupt Flags */
    register8_t TEMP; /* Temporary */
    register8_t DBGCTRL; /* Debug control */
    register8_t reserved_1[1];
    register8_t CLKSEL; /* Clock Select */
    __extension__ union { register16_t CNT; struct { register8_t CNTL; register8_t CNTH; }; }; /* Counter */
    __extension__ union { register16_t PER; struct { register8_t PERL; register8_t PERH; }; }; /* Period */
    __extension__ union { register16_t CMP; struct { register8_t CMPL; register8_t CMPH; }; }; /* Compare */
    register8_t reserved_2[2];
    register8_t PITCTRLA; /* PIT Control A */
    register8_t PITSTATUS; /* PIT Status */
    register8_t PITINTCTRL; /* PIT Interrupt Control */
    register8_t PITINTFLAGS; /* PIT Interrupt Flags */
    register8_t reserved_3[1];
    register8_t PITDBGCTRL; /* PIT Debug control */
    register8_t reserved_4[10];
} RTC_t;
/* Clock Select */
typedef enum RTC_CLKSEL_enum
{
    RTC_CLKSEL_INT32K_gc = (0x00<<0), /* Internal 32kHz OSC */
    RTC_CLKSEL_INT1K_gc = (0x01<<0), /* Internal 1kHz OSC */
    RTC_CLKSEL_TOSC32K_gc = (0x02<<0), /* 32KHz Crystal OSC */
    RTC_CLKSEL_EXTCLK_gc = (0x03<<0) /* External Clock */
} RTC_CLKSEL_t;
/* Period select */
typedef enum RTC_PERIOD_enum
{
    RTC_PERIOD_OFF_gc = (0x00<<3), /* Off */
    RTC_PERIOD_CYC4_gc = (0x01<<3), /* RTC Clock Cycles 4 */
    RTC_PERIOD_CYC8_gc = (0x02<<3), /* RTC Clock Cycles 8 */
    RTC_PERIOD_CYC16_gc = (0x03<<3), /* RTC Clock Cycles 16 */
    RTC_PERIOD_CYC32_gc = (0x04<<3), /* RTC Clock Cycles 32 */
    RTC_PERIOD_CYC64_gc = (0x05<<3), /* RTC Clock Cycles 64 */
    RTC_PERIOD_CYC128_gc = (0x06<<3), /* RTC Clock Cycles 128 */
    RTC_PERIOD_CYC256_gc = (0x07<<3), /* RTC Clock Cycles 256 */
    RTC_PERIOD_CYC512_gc = (0x08<<3), /* RTC Clock Cycles 512 */
    RTC_PERIOD_CYC1024_gc = (0x09<<3), /* RTC Clock Cycles 1024 */
    RTC_PERIOD_CYC2048_gc = (0x0A<<3), /* RTC Clock Cycles 2048 */
    RTC_PERIOD_CYC4096_gc = (0x0B<<3), /* RTC Clock Cycles 4096 */
    RTC_PERIOD_CYC8192_gc = (0x0C<<3), /* RTC Clock Cycles 8192 */
    RTC_PERIOD_CYC16384_gc = (0x0D<<3), /* RTC Clock Cycles 16384 */
    RTC_PERIOD_CYC32768_gc = (0x0E<<3) /* RTC Clock Cycles 32768 */
} RTC_PERIOD_t;
/* Prescaling Factor select */
typedef enum RTC_PRESCALER_enum
{
    RTC_PRESCALER_DIV1_gc = (0x00<<3), /* RTC Clock / 1 */
    RTC_PRESCALER_DIV2_gc = (0x01<<3), /* RTC Clock / 2 */
    RTC_PRESCALER_DIV4_gc = (0x02<<3), /* RTC Clock / 4 */
    RTC_PRESCALER_DIV8_gc = (0x03<<3), /* RTC Clock / 8 */
    RTC_PRESCALER_DIV16_gc = (0x04<<3), /* RTC Clock / 16 */
    RTC_PRESCALER_DIV32_gc = (0x05<<3), /* RTC Clock / 32 */
    RTC_PRESCALER_DIV64_gc = (0x06<<3), /* RTC Clock / 64 */
    RTC_PRESCALER_DIV128_gc = (0x07<<3), /* RTC Clock / 128 */
    RTC_PRESCALER_DIV256_gc = (0x08<<3), /* RTC Clock / 256 */
    RTC_PRESCALER_DIV512_gc = (0x09<<3), /* RTC Clock / 512 */
    RTC_PRESCALER_DIV1024_gc = (0x0A<<3), /* RTC Clock / 1024 */
    RTC_PRESCALER_DIV2048_gc = (0x0B<<3), /* RTC Clock / 2048 */
    RTC_PRESCALER_DIV4096_gc = (0x0C<<3), /* RTC Clock / 4096 */
    RTC_PRESCALER_DIV8192_gc = (0x0D<<3), /* RTC Clock / 8192 */
    RTC_PRESCALER_DIV16384_gc = (0x0E<<3), /* RTC Clock / 16384 */
    RTC_PRESCALER_DIV32768_gc = (0x0F<<3) /* RTC Clock / 32768 */
} RTC_PRESCALER_t;
/*
--------------------------------------------------------------------------
SIGROW - Signature row
--------------------------------------------------------------------------
*/
/* Signature row */
typedef struct SIGROW_struct
{
    register8_t DEVICEID0; /* Device ID Byte 0 */
    register8_t DEVICEID1; /* Device ID Byte 1 */
    register8_t DEVICEID2; /* Device ID Byte 2 */
    register8_t SERNUM0; /* Serial Number Byte 0 */
    register8_t SERNUM1; /* Serial Number Byte 1 */
    register8_t SERNUM2; /* Serial Number Byte 2 */
    register8_t SERNUM3; /* Serial Number Byte 3 */
    register8_t SERNUM4; /* Serial Number Byte 4 */
    register8_t SERNUM5; /* Serial Number Byte 5 */
    register8_t SERNUM6; /* Serial Number Byte 6 */
    register8_t SERNUM7; /* Serial Number Byte 7 */
    register8_t SERNUM8; /* Serial Number Byte 8 */
    register8_t SERNUM9; /* Serial Number Byte 9 */
    register8_t reserved_1[19];
    register8_t TEMPSENSE0; /* Temperature Sensor Calibration Byte 0 */
    register8_t TEMPSENSE1; /* Temperature Sensor Calibration Byte 1 */
    register8_t OSC16ERR3V; /* OSC16 error at 3V */
    register8_t OSC16ERR5V; /* OSC16 error at 5V */
    register8_t OSC20ERR3V; /* OSC20 error at 3V */
    register8_t OSC20ERR5V; /* OSC20 error at 5V */
    register8_t reserved_2[26];
} SIGROW_t;
/*
--------------------------------------------------------------------------
SLPCTRL - Sleep Controller
--------------------------------------------------------------------------
*/
/* Sleep Controller */
typedef struct SLPCTRL_struct
{
    register8_t CTRLA; /* Control */
    register8_t reserved_1[1];
} SLPCTRL_t;
/* Sleep mode select */
typedef enum SLPCTRL_SMODE_enum
{
    SLPCTRL_SMODE_IDLE_gc = (0x00<<1), /* Idle mode */
    SLPCTRL_SMODE_STDBY_gc = (0x01<<1), /* Standby Mode */
    SLPCTRL_SMODE_PDOWN_gc = (0x02<<1) /* Power-down Mode */
} SLPCTRL_SMODE_t;
/*
--------------------------------------------------------------------------
SPI - Serial Peripheral Interface
--------------------------------------------------------------------------
*/
/* Serial Peripheral Interface */
typedef struct SPI_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t INTCTRL; /* Interrupt Control */
    register8_t INTFLAGS; /* Interrupt Flags */
    register8_t DATA; /* Data */
    register8_t reserved_1[3];
} SPI_t;
/* SPI Mode select */
typedef enum SPI_MODE_enum
{
    SPI_MODE_0_gc = (0x00<<0), /* SPI Mode 0 */
    SPI_MODE_1_gc = (0x01<<0), /* SPI Mode 1 */
    SPI_MODE_2_gc = (0x02<<0), /* SPI Mode 2 */
    SPI_MODE_3_gc = (0x03<<0) /* SPI Mode 3 */
} SPI_MODE_t;
/* Prescaler select */
typedef enum SPI_PRESC_enum
{
    SPI_PRESC_DIV4_gc = (0x00<<1), /* System Clock / 4 */
    SPI_PRESC_DIV16_gc = (0x01<<1), /* System Clock / 16 */
    SPI_PRESC_DIV64_gc = (0x02<<1), /* System Clock / 64 */
    SPI_PRESC_DIV128_gc = (0x03<<1) /* System Clock / 128 */
} SPI_PRESC_t;
/*
--------------------------------------------------------------------------
SYSCFG - System Configuration Registers
--------------------------------------------------------------------------
*/
/* System Configuration Registers */
typedef struct SYSCFG_struct
{
    register8_t reserved_1[1];
    register8_t REVID; /* Revision ID */
    register8_t EXTBRK; /* External Break */
    register8_t reserved_2[29];
} SYSCFG_t;
/*
--------------------------------------------------------------------------
TCA - 16-bit Timer/Counter Type A
--------------------------------------------------------------------------
*/
/* 16-bit Timer/Counter Type A - Single Mode */
typedef struct TCA_SINGLE_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t CTRLC; /* Control C */
    register8_t CTRLD; /* Control D */
    register8_t CTRLECLR; /* Control E Clear */
    register8_t CTRLESET; /* Control E Set */
    register8_t CTRLFCLR; /* Control F Clear */
    register8_t CTRLFSET; /* Control F Set */
    register8_t reserved_1[1];
    register8_t EVCTRL; /* Event Control */
    register8_t INTCTRL; /* Interrupt Control */
    register8_t INTFLAGS; /* Interrupt Flags */
    register8_t reserved_2[2];
    register8_t DBGCTRL; /* Degbug Control */
    register8_t TEMP; /* Temporary data for 16-bit Access */
    register8_t reserved_3[16];
    __extension__ union { register16_t CNT; struct { register8_t CNTL; register8_t CNTH; }; }; /* Count */
    register8_t reserved_4[4];
    __extension__ union { register16_t PER; struct { register8_t PERL; register8_t PERH; }; }; /* Period */
    __extension__ union { register16_t CMP0; struct { register8_t CMP0L; register8_t CMP0H; }; }; /* Compare 0 */
    __extension__ union { register16_t CMP1; struct { register8_t CMP1L; register8_t CMP1H; }; }; /* Compare 1 */
    __extension__ union { register16_t CMP2; struct { register8_t CMP2L; register8_t CMP2H; }; }; /* Compare 2 */
    register8_t reserved_5[8];
    __extension__ union { register16_t PERBUF; struct { register8_t PERBUFL; register8_t PERBUFH; }; }; /* Period Buffer */
    __extension__ union { register16_t CMP0BUF; struct { register8_t CMP0BUFL; register8_t CMP0BUFH; }; }; /* Compare 0 Buffer */
    __extension__ union { register16_t CMP1BUF; struct { register8_t CMP1BUFL; register8_t CMP1BUFH; }; }; /* Compare 1 Buffer */
    __extension__ union { register16_t CMP2BUF; struct { register8_t CMP2BUFL; register8_t CMP2BUFH; }; }; /* Compare 2 Buffer */
    register8_t reserved_6[2];
} TCA_SINGLE_t;
/* 16-bit Timer/Counter Type A - Split Mode */
typedef struct TCA_SPLIT_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t CTRLC; /* Control C */
    register8_t CTRLD; /* Control D */
    register8_t CTRLECLR; /* Control E Clear */
    register8_t CTRLESET; /* Control E Set */
    register8_t reserved_1[4];
    register8_t INTCTRL; /* Interrupt Control */
    register8_t INTFLAGS; /* Interrupt Flags */
    register8_t reserved_2[2];
    register8_t DBGCTRL; /* Degbug Control */
    register8_t reserved_3[17];
    register8_t LCNT; /* Low Count */
    register8_t HCNT; /* High Count */
    register8_t reserved_4[4];
    register8_t LPER; /* Low Period */
    register8_t HPER; /* High Period */
    register8_t LCMP0; /* Low Compare */
    register8_t HCMP0; /* High Compare */
    register8_t LCMP1; /* Low Compare */
    register8_t HCMP1; /* High Compare */
    register8_t LCMP2; /* Low Compare */
    register8_t HCMP2; /* High Compare */
    register8_t reserved_5[18];
} TCA_SPLIT_t;
/* 16-bit Timer/Counter Type A */
typedef union TCA_union
{
    TCA_SINGLE_t SINGLE; /* Single Mode */
    TCA_SPLIT_t SPLIT; /* Split Mode */
} TCA_t;
/* Clock Selection */
typedef enum TCA_SINGLE_CLKSEL_enum
{
    TCA_SINGLE_CLKSEL_DIV1_gc = (0x00<<1), /* System Clock */
    TCA_SINGLE_CLKSEL_DIV2_gc = (0x01<<1), /* System Clock / 2 */
    TCA_SINGLE_CLKSEL_DIV4_gc = (0x02<<1), /* System Clock / 4 */
    TCA_SINGLE_CLKSEL_DIV8_gc = (0x03<<1), /* System Clock / 8 */
    TCA_SINGLE_CLKSEL_DIV16_gc = (0x04<<1), /* System Clock / 16 */
    TCA_SINGLE_CLKSEL_DIV64_gc = (0x05<<1), /* System Clock / 64 */
    TCA_SINGLE_CLKSEL_DIV256_gc = (0x06<<1), /* System Clock / 256 */
    TCA_SINGLE_CLKSEL_DIV1024_gc = (0x07<<1) /* System Clock / 1024 */
} TCA_SINGLE_CLKSEL_t;
/* Command select */
typedef enum TCA_SINGLE_CMD_enum
{
    TCA_SINGLE_CMD_NONE_gc = (0x00<<2), /* No Command */
    TCA_SINGLE_CMD_UPDATE_gc = (0x01<<2), /* Force Update */
    TCA_SINGLE_CMD_RESTART_gc = (0x02<<2), /* Force Restart */
    TCA_SINGLE_CMD_RESET_gc = (0x03<<2) /* Force Hard Reset */
} TCA_SINGLE_CMD_t;
/* Direction select */
typedef enum TCA_SINGLE_DIR_enum
{
    TCA_SINGLE_DIR_UP_gc = (0x00<<0), /* Count up */
    TCA_SINGLE_DIR_DOWN_gc = (0x01<<0) /* Count down */
} TCA_SINGLE_DIR_t;
/* Event Action select */
typedef enum TCA_SINGLE_EVACT_enum
{
    TCA_SINGLE_EVACT_POSEDGE_gc = (0x00<<1), /* Count on positive edge event */
    TCA_SINGLE_EVACT_ANYEDGE_gc = (0x01<<1), /* Count on any edge event */
    TCA_SINGLE_EVACT_HIGHLVL_gc = (0x02<<1), /* Count on prescaled clock while event line is 1. */
    TCA_SINGLE_EVACT_UPDOWN_gc = (0x03<<1) /* Count on prescaled clock. Event controls count direction. Up-count when event line is 0, down-count when event line is 1. */
} TCA_SINGLE_EVACT_t;
/* Waveform generation mode select */
typedef enum TCA_SINGLE_WGMODE_enum
{
    TCA_SINGLE_WGMODE_NORMAL_gc = (0x00<<0), /* Normal Mode */
    TCA_SINGLE_WGMODE_FRQ_gc = (0x01<<0), /* Frequency Generation Mode */
    TCA_SINGLE_WGMODE_SINGLESLOPE_gc = (0x03<<0), /* Single Slope PWM */
    TCA_SINGLE_WGMODE_DSTOP_gc = (0x05<<0), /* Dual Slope PWM, overflow on TOP */
    TCA_SINGLE_WGMODE_DSBOTH_gc = (0x06<<0), /* Dual Slope PWM, overflow on TOP and BOTTOM */
    TCA_SINGLE_WGMODE_DSBOTTOM_gc = (0x07<<0) /* Dual Slope PWM, overflow on BOTTOM */
} TCA_SINGLE_WGMODE_t;
/* Clock Selection */
typedef enum TCA_SPLIT_CLKSEL_enum
{
    TCA_SPLIT_CLKSEL_DIV1_gc = (0x00<<1), /* System Clock */
    TCA_SPLIT_CLKSEL_DIV2_gc = (0x01<<1), /* System Clock / 2 */
    TCA_SPLIT_CLKSEL_DIV4_gc = (0x02<<1), /* System Clock / 4 */
    TCA_SPLIT_CLKSEL_DIV8_gc = (0x03<<1), /* System Clock / 8 */
    TCA_SPLIT_CLKSEL_DIV16_gc = (0x04<<1), /* System Clock / 16 */
    TCA_SPLIT_CLKSEL_DIV64_gc = (0x05<<1), /* System Clock / 64 */
    TCA_SPLIT_CLKSEL_DIV256_gc = (0x06<<1), /* System Clock / 256 */
    TCA_SPLIT_CLKSEL_DIV1024_gc = (0x07<<1) /* System Clock / 1024 */
} TCA_SPLIT_CLKSEL_t;
/* Command select */
typedef enum TCA_SPLIT_CMD_enum
{
    TCA_SPLIT_CMD_NONE_gc = (0x00<<2), /* No Command */
    TCA_SPLIT_CMD_UPDATE_gc = (0x01<<2), /* Force Update */
    TCA_SPLIT_CMD_RESTART_gc = (0x02<<2), /* Force Restart */
    TCA_SPLIT_CMD_RESET_gc = (0x03<<2) /* Force Hard Reset */
} TCA_SPLIT_CMD_t;
/*
--------------------------------------------------------------------------
TCB - 16-bit Timer Type B
--------------------------------------------------------------------------
*/
/* 16-bit Timer Type B */
typedef struct TCB_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control Register B */
    register8_t reserved_1[2];
    register8_t EVCTRL; /* Event Control */
    register8_t INTCTRL; /* Interrupt Control */
    register8_t INTFLAGS; /* Interrupt Flags */
    register8_t STATUS; /* Status */
    register8_t DBGCTRL; /* Debug Control */
    register8_t TEMP; /* Temporary Value */
    __extension__ union { register16_t CNT; struct { register8_t CNTL; register8_t CNTH; }; }; /* Count */
    __extension__ union { register16_t CCMP; struct { register8_t CCMPL; register8_t CCMPH; }; }; /* Compare or Capture */
    register8_t reserved_2[2];
} TCB_t;
/* Clock Select */
typedef enum TCB_CLKSEL_enum
{
    TCB_CLKSEL_CLKDIV1_gc = (0x00<<1), /* CLK_PER (No Prescaling) */
    TCB_CLKSEL_CLKDIV2_gc = (0x01<<1), /* CLK_PER/2 (From Prescaler) */
    TCB_CLKSEL_CLKTCA_gc = (0x02<<1) /* Use Clock from TCA */
} TCB_CLKSEL_t;
/* Timer Mode select */
typedef enum TCB_CNTMODE_enum
{
    TCB_CNTMODE_INT_gc = (0x00<<0), /* Periodic Interrupt */
    TCB_CNTMODE_TIMEOUT_gc = (0x01<<0), /* Periodic Timeout */
    TCB_CNTMODE_CAPT_gc = (0x02<<0), /* Input Capture Event */
    TCB_CNTMODE_FRQ_gc = (0x03<<0), /* Input Capture Frequency measurement */
    TCB_CNTMODE_PW_gc = (0x04<<0), /* Input Capture Pulse-Width measurement */
    TCB_CNTMODE_FRQPW_gc = (0x05<<0), /* Input Capture Frequency and Pulse-Width measurement */
    TCB_CNTMODE_SINGLE_gc = (0x06<<0), /* Single Shot */
    TCB_CNTMODE_PWM8_gc = (0x07<<0) /* 8-bit PWM */
} TCB_CNTMODE_t;
/*
--------------------------------------------------------------------------
TCD - Timer Counter D
--------------------------------------------------------------------------
*/
/* Timer Counter D */
typedef struct TCD_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t CTRLC; /* Control C */
    register8_t CTRLD; /* Control D */
    register8_t CTRLE; /* Control E */
    register8_t reserved_1[3];
    register8_t EVCTRLA; /* EVCTRLA */
    register8_t EVCTRLB; /* EVCTRLB */
    register8_t reserved_2[2];
    register8_t INTCTRL; /* Interrupt Control */
    register8_t INTFLAGS; /* Interrupt Flags */
    register8_t STATUS; /* Status */
    register8_t reserved_3[1];
    register8_t INPUTCTRLA; /* Input Control A */
    register8_t INPUTCTRLB; /* Input Control B */
    register8_t FAULTCTRL; /* Fault Control */
    register8_t reserved_4[1];
    register8_t DLYCTRL; /* Delay Control */
    register8_t DLYVAL; /* Delay value */
    register8_t reserved_5[2];
    register8_t DITCTRL; /* Dither Control A */
    register8_t DITVAL; /* Dither value */
    register8_t reserved_6[4];
    register8_t DBGCTRL; /* Debug Control */
    register8_t reserved_7[3];
    __extension__ union { register16_t CAPTUREA; struct { register8_t CAPTUREAL; register8_t CAPTUREAH; }; }; /* Capture A */
    __extension__ union { register16_t CAPTUREB; struct { register8_t CAPTUREBL; register8_t CAPTUREBH; }; }; /* Capture B */
    register8_t reserved_8[2];
    __extension__ union { register16_t CMPASET; struct { register8_t CMPASETL; register8_t CMPASETH; }; }; /* Compare A Set */
    __extension__ union { register16_t CMPACLR; struct { register8_t CMPACLRL; register8_t CMPACLRH; }; }; /* Compare A Clear */
    __extension__ union { register16_t CMPBSET; struct { register8_t CMPBSETL; register8_t CMPBSETH; }; }; /* Compare B Set */
    __extension__ union { register16_t CMPBCLR; struct { register8_t CMPBCLRL; register8_t CMPBCLRH; }; }; /* Compare B Clear */
    register8_t reserved_9[16];
} TCD_t;
/* Event action select */
typedef enum TCD_ACTION_enum
{
    TCD_ACTION_FAULT_gc = (0x00<<2), /* Event trigger a fault */
    TCD_ACTION_CAPTURE_gc = (0x01<<2) /* Event trigger a fault and capture */
} TCD_ACTION_t;
/* Event config select */
typedef enum TCD_CFG_enum
{
    TCD_CFG_NEITHER_gc = (0x00<<6), /* Neither Filter nor Asynchronous Event is enabled */
    TCD_CFG_FILTER_gc = (0x01<<6), /* Input Capture Noise Cancellation Filter enabled */
    TCD_CFG_ASYNC_gc = (0x02<<6) /* Asynchronous Event output qualification enabled */
} TCD_CFG_t;
/* clock select */
typedef enum TCD_CLKSEL_enum
{
    TCD_CLKSEL_20MHZ_gc = (0x00<<5), /* 20 MHz oscillator */
    TCD_CLKSEL_EXTCLK_gc = (0x02<<5), /* External clock */
    TCD_CLKSEL_SYSCLK_gc = (0x03<<5) /* System clock */
} TCD_CLKSEL_t;
/* Compare C output select */
typedef enum TCD_CMPCSEL_enum
{
    TCD_CMPCSEL_PWMA_gc = (0x00<<6), /* PWM A output */
    TCD_CMPCSEL_PWMB_gc = (0x01<<6) /* PWM B output */
} TCD_CMPCSEL_t;
/* Compare D output select */
typedef enum TCD_CMPDSEL_enum
{
    TCD_CMPDSEL_PWMA_gc = (0x00<<7), /* PWM A output */
    TCD_CMPDSEL_PWMB_gc = (0x01<<7) /* PWM B output */
} TCD_CMPDSEL_t;
/* counter prescaler select */
typedef enum TCD_CNTPRES_enum
{
    TCD_CNTPRES_DIV1_gc = (0x00<<3), /* Sync clock divided by 1 */
    TCD_CNTPRES_DIV4_gc = (0x01<<3), /* Sync clock divided by 4 */
    TCD_CNTPRES_DIV32_gc = (0x02<<3) /* Sync clock divided by 32 */
} TCD_CNTPRES_t;
/* Dither select */
typedef enum TCD_DITHERSEL_enum
{
    TCD_DITHERSEL_ONTIMEB_gc = (0x00<<0), /* On-time ramp B */
    TCD_DITHERSEL_ONTIMEAB_gc = (0x01<<0), /* On-time ramp A and B */
    TCD_DITHERSEL_DEADTIMEB_gc = (0x02<<0), /* Dead-time rampB */
    TCD_DITHERSEL_DEADTIMEAB_gc = (0x03<<0) /* Dead-time ramp A and B */
} TCD_DITHERSEL_t;
/* Delay prescaler select */
typedef enum TCD_DLYPRESC_enum
{
    TCD_DLYPRESC_DIV1_gc = (0x00<<4), /* No prescaling */
    TCD_DLYPRESC_DIV2_gc = (0x01<<4), /* Prescale with 2 */
    TCD_DLYPRESC_DIV4_gc = (0x02<<4), /* Prescale with 4 */
    TCD_DLYPRESC_DIV8_gc = (0x03<<4) /* Prescale with 8 */
} TCD_DLYPRESC_t;
/* Delay select */
typedef enum TCD_DLYSEL_enum
{
    TCD_DLYSEL_OFF_gc = (0x00<<0), /* No delay */
    TCD_DLYSEL_INBLANK_gc = (0x01<<0), /* Input blanking enabled */
    TCD_DLYSEL_EVENT_gc = (0x02<<0) /* Event delay enabled */
} TCD_DLYSEL_t;
/* Delay trigger select */
typedef enum TCD_DLYTRIG_enum
{
    TCD_DLYTRIG_CMPASET_gc = (0x00<<2), /* Compare A set */
    TCD_DLYTRIG_CMPACLR_gc = (0x01<<2), /* Compare A clear */
    TCD_DLYTRIG_CMPBSET_gc = (0x02<<2), /* Compare B set */
    TCD_DLYTRIG_CMPBCLR_gc = (0x03<<2) /* Compare B clear */
} TCD_DLYTRIG_t;
/* Edge select */
typedef enum TCD_EDGE_enum
{
    TCD_EDGE_FALL_LOW_gc = (0x00<<4), /* The falling edge or low level of event generates retrigger or fault action */
    TCD_EDGE_RISE_HIGH_gc = (0x01<<4) /* The rising edge or high level of event generates retrigger or fault action */
} TCD_EDGE_t;
/* Input mode select */
typedef enum TCD_INPUTMODE_enum
{
    TCD_INPUTMODE_NONE_gc = (0x00<<0), /* Input has no actions */
    TCD_INPUTMODE_JMPWAIT_gc = (0x01<<0), /* Stop output, jump to opposite compare cycle and wait */
    TCD_INPUTMODE_EXECWAIT_gc = (0x02<<0), /* Stop output, execute opposite compare cycle and wait */
    TCD_INPUTMODE_EXECFAULT_gc = (0x03<<0), /* stop output, execute opposite compare cycle while fault active */
    TCD_INPUTMODE_FREQ_gc = (0x04<<0), /* Stop all outputs, maintain frequency */
    TCD_INPUTMODE_EXECDT_gc = (0x05<<0), /* Stop all outputs, execute dead time while fault active */
    TCD_INPUTMODE_WAIT_gc = (0x06<<0), /* Stop all outputs, jump to next compare cycle and wait */
    TCD_INPUTMODE_WAITSW_gc = (0x07<<0), /* Stop all outputs, wait for software action */
    TCD_INPUTMODE_EDGETRIG_gc = (0x08<<0), /* Stop output on edge, jump to next compare cycle */
    TCD_INPUTMODE_EDGETRIGFREQ_gc = (0x09<<0), /* Stop output on edge, maintain frequency */
    TCD_INPUTMODE_LVLTRIGFREQ_gc = (0x0A<<0) /* Stop output at level, maintain frequency */
} TCD_INPUTMODE_t;
/* Syncronization prescaler select */
typedef enum TCD_SYNCPRES_enum
{
    TCD_SYNCPRES_DIV1_gc = (0x00<<1), /* Selevted clock source divided by 1 */
    TCD_SYNCPRES_DIV2_gc = (0x01<<1), /* Selevted clock source divided by 2 */
    TCD_SYNCPRES_DIV4_gc = (0x02<<1), /* Selevted clock source divided by 4 */
    TCD_SYNCPRES_DIV8_gc = (0x03<<1) /* Selevted clock source divided by 8 */
} TCD_SYNCPRES_t;
/* Waveform generation mode select */
typedef enum TCD_WGMODE_enum
{
    TCD_WGMODE_ONERAMP_gc = (0x00<<0), /* One ramp mode */
    TCD_WGMODE_TWORAMP_gc = (0x01<<0), /* Two ramp mode */
    TCD_WGMODE_FOURRAMP_gc = (0x02<<0), /* Four ramp mode */
    TCD_WGMODE_DS_gc = (0x03<<0) /* Dual slope mode */
} TCD_WGMODE_t;
/*
--------------------------------------------------------------------------
TWI - Two-Wire Interface
--------------------------------------------------------------------------
*/
/* Two-Wire Interface */
typedef struct TWI_struct
{
    register8_t CTRLA; /* Control A */
    register8_t reserved_1[1];
    register8_t DBGCTRL; /* Debug Control Register */
    register8_t MCTRLA; /* Host Control A */
    register8_t MCTRLB; /* Host Control B */
    register8_t MSTATUS; /* Host Status */
    register8_t MBAUD; /* Host Baud Rate Control */
    register8_t MADDR; /* Host Address */
    register8_t MDATA; /* Host Data */
    register8_t SCTRLA; /* Client Control A */
    register8_t SCTRLB; /* Client Control B */
    register8_t SSTATUS; /* Client Status */
    register8_t SADDR; /* Client Address */
    register8_t SDATA; /* Client Data */
    register8_t SADDRMASK; /* Client Address Mask */
    register8_t reserved_2[1];
} TWI_t;
/* Acknowledge Action select */
typedef enum TWI_ACKACT_enum
{
    TWI_ACKACT_ACK_gc = (0x00<<2), /* Send ACK */
    TWI_ACKACT_NACK_gc = (0x01<<2) /* Send NACK */
} TWI_ACKACT_t;
/* Client Address or Stop select */
typedef enum TWI_AP_enum
{
    TWI_AP_STOP_gc = (0x00<<0), /* Stop condition generated APIF */
    TWI_AP_ADR_gc = (0x01<<0) /* Address detection generated APIF */
} TWI_AP_t;
/* Bus State select */
typedef enum TWI_BUSSTATE_enum
{
    TWI_BUSSTATE_UNKNOWN_gc = (0x00<<0), /* Unknown Bus State */
    TWI_BUSSTATE_IDLE_gc = (0x01<<0), /* Bus is Idle */
    TWI_BUSSTATE_OWNER_gc = (0x02<<0), /* This Module Controls The Bus */
    TWI_BUSSTATE_BUSY_gc = (0x03<<0) /* The Bus is Busy */
} TWI_BUSSTATE_t;
/* Command select */
typedef enum TWI_MCMD_enum
{
    TWI_MCMD_NOACT_gc = (0x00<<0), /* No Action */
    TWI_MCMD_REPSTART_gc = (0x01<<0), /* Issue Repeated Start Condition */
    TWI_MCMD_RECVTRANS_gc = (0x02<<0), /* Receive or Transmit Data, depending on DIR */
    TWI_MCMD_STOP_gc = (0x03<<0) /* Issue Stop Condition */
} TWI_MCMD_t;
/* Command select */
typedef enum TWI_SCMD_enum
{
    TWI_SCMD_NOACT_gc = (0x00<<0), /* No Action */
    TWI_SCMD_COMPTRANS_gc = (0x02<<0), /* Used To Complete a Transaction */
    TWI_SCMD_RESPONSE_gc = (0x03<<0) /* Used in Response to Address/Data Interrupt */
} TWI_SCMD_t;
/* SDA Hold Time select */
typedef enum TWI_SDAHOLD_enum
{
    TWI_SDAHOLD_OFF_gc = (0x00<<2), /* SDA hold time off */
    TWI_SDAHOLD_50NS_gc = (0x01<<2), /* Typical 50ns hold time */
    TWI_SDAHOLD_300NS_gc = (0x02<<2), /* Typical 300ns hold time */
    TWI_SDAHOLD_500NS_gc = (0x03<<2) /* Typical 500ns hold time */
} TWI_SDAHOLD_t;
/* SDA Setup Time select */
typedef enum TWI_SDASETUP_enum
{
    TWI_SDASETUP_4CYC_gc = (0x00<<4), /* SDA setup time is 4 clock cycles */
    TWI_SDASETUP_8CYC_gc = (0x01<<4) /* SDA setup time is 8 clock cycles */
} TWI_SDASETUP_t;
/* Inactive Bus Timeout select */
typedef enum TWI_TIMEOUT_enum
{
    TWI_TIMEOUT_DISABLED_gc = (0x00<<2), /* Bus Timeout Disabled */
    TWI_TIMEOUT_50US_gc = (0x01<<2), /* 50 Microseconds */
    TWI_TIMEOUT_100US_gc = (0x02<<2), /* 100 Microseconds */
    TWI_TIMEOUT_200US_gc = (0x03<<2) /* 200 Microseconds */
} TWI_TIMEOUT_t;
/*
--------------------------------------------------------------------------
USART - Universal Synchronous and Asynchronous Receiver and Transmitter
--------------------------------------------------------------------------
*/
/* Universal Synchronous and Asynchronous Receiver and Transmitter */
typedef struct USART_struct
{
    register8_t RXDATAL; /* Receive Data Low Byte */
    register8_t RXDATAH; /* Receive Data High Byte */
    register8_t TXDATAL; /* Transmit Data Low Byte */
    register8_t TXDATAH; /* Transmit Data High Byte */
    register8_t STATUS; /* Status */
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t CTRLC; /* Control C */
    __extension__ union { register16_t BAUD; struct { register8_t BAUDL; register8_t BAUDH; }; }; /* Baud Rate */
    register8_t reserved_1[1];
    register8_t DBGCTRL; /* Debug Control */
    register8_t EVCTRL; /* Event Control */
    register8_t TXPLCTRL; /* IRCOM Transmitter Pulse Length Control */
    register8_t RXPLCTRL; /* IRCOM Receiver Pulse Length Control */
    register8_t reserved_2[1];
} USART_t;
/* Character Size select */
typedef enum USART_CHSIZE_enum
{
    USART_CHSIZE_5BIT_gc = (0x00<<0), /* Character size: 5 bit */
    USART_CHSIZE_6BIT_gc = (0x01<<0), /* Character size: 6 bit */
    USART_CHSIZE_7BIT_gc = (0x02<<0), /* Character size: 7 bit */
    USART_CHSIZE_8BIT_gc = (0x03<<0), /* Character size: 8 bit */
    USART_CHSIZE_9BITL_gc = (0x06<<0), /* Character size: 9 bit read low byte first */
    USART_CHSIZE_9BITH_gc = (0x07<<0) /* Character size: 9 bit read high byte first */
} USART_CHSIZE_t;
/* Communication Mode select */
typedef enum USART_CMODE_enum
{
    USART_CMODE_ASYNCHRONOUS_gc = (0x00<<6), /* Asynchronous Mode */
    USART_CMODE_SYNCHRONOUS_gc = (0x01<<6), /* Synchronous Mode */
    USART_CMODE_IRCOM_gc = (0x02<<6), /* Infrared Communication */
    USART_CMODE_MSPI_gc = (0x03<<6) /* SPI Host Mode */
} USART_CMODE_t;
/* Parity Mode select */
typedef enum USART_PMODE_enum
{
    USART_PMODE_DISABLED_gc = (0x00<<4), /* No Parity */
    USART_PMODE_EVEN_gc = (0x02<<4), /* Even Parity */
    USART_PMODE_ODD_gc = (0x03<<4) /* Odd Parity */
} USART_PMODE_t;
/* RS485 Mode internal transmitter select */
typedef enum USART_RS485_enum
{
    USART_RS485_OFF_gc = (0x00<<0), /* RS485 Mode disabled */
    USART_RS485_EXT_gc = (0x01<<0), /* RS485 Mode External drive */
    USART_RS485_INT_gc = (0x02<<0) /* RS485 Mode Internal drive */
} USART_RS485_t;
/* Receiver Mode select */
typedef enum USART_RXMODE_enum
{
    USART_RXMODE_NORMAL_gc = (0x00<<1), /* Normal mode */
    USART_RXMODE_CLK2X_gc = (0x01<<1), /* CLK2x mode */
    USART_RXMODE_GENAUTO_gc = (0x02<<1), /* Generic autobaud mode */
    USART_RXMODE_LINAUTO_gc = (0x03<<1) /* LIN constrained autobaud mode */
} USART_RXMODE_t;
/* Stop Bit Mode select */
typedef enum USART_SBMODE_enum
{
    USART_SBMODE_1BIT_gc = (0x00<<3), /* 1 stop bit */
    USART_SBMODE_2BIT_gc = (0x01<<3) /* 2 stop bits */
} USART_SBMODE_t;
/*
--------------------------------------------------------------------------
USERROW - User Row
--------------------------------------------------------------------------
*/
/* User Row */
typedef struct USERROW_struct
{
    register8_t USERROW0; /* User Row Byte 0 */
    register8_t USERROW1; /* User Row Byte 1 */
    register8_t USERROW2; /* User Row Byte 2 */
    register8_t USERROW3; /* User Row Byte 3 */
    register8_t USERROW4; /* User Row Byte 4 */
    register8_t USERROW5; /* User Row Byte 5 */
    register8_t USERROW6; /* User Row Byte 6 */
    register8_t USERROW7; /* User Row Byte 7 */
    register8_t USERROW8; /* User Row Byte 8 */
    register8_t USERROW9; /* User Row Byte 9 */
    register8_t USERROW10; /* User Row Byte 10 */
    register8_t USERROW11; /* User Row Byte 11 */
    register8_t USERROW12; /* User Row Byte 12 */
    register8_t USERROW13; /* User Row Byte 13 */
    register8_t USERROW14; /* User Row Byte 14 */
    register8_t USERROW15; /* User Row Byte 15 */
    register8_t USERROW16; /* User Row Byte 16 */
    register8_t USERROW17; /* User Row Byte 17 */
    register8_t USERROW18; /* User Row Byte 18 */
    register8_t USERROW19; /* User Row Byte 19 */
    register8_t USERROW20; /* User Row Byte 20 */
    register8_t USERROW21; /* User Row Byte 21 */
    register8_t USERROW22; /* User Row Byte 22 */
    register8_t USERROW23; /* User Row Byte 23 */
    register8_t USERROW24; /* User Row Byte 24 */
    register8_t USERROW25; /* User Row Byte 25 */
    register8_t USERROW26; /* User Row Byte 26 */
    register8_t USERROW27; /* User Row Byte 27 */
    register8_t USERROW28; /* User Row Byte 28 */
    register8_t USERROW29; /* User Row Byte 29 */
    register8_t USERROW30; /* User Row Byte 30 */
    register8_t USERROW31; /* User Row Byte 31 */
} USERROW_t;
/*
--------------------------------------------------------------------------
VPORT - Virtual Ports
--------------------------------------------------------------------------
*/
/* Virtual Ports */
typedef struct VPORT_struct
{
    register8_t DIR; /* Data Direction */
    register8_t OUT; /* Output Value */
    register8_t IN; /* Input Value */
    register8_t INTFLAGS; /* Interrupt Flags */
} VPORT_t;
/*
--------------------------------------------------------------------------
VREF - Voltage reference
--------------------------------------------------------------------------
*/
/* Voltage reference */
typedef struct VREF_struct
{
    register8_t CTRLA; /* Control A */
    register8_t CTRLB; /* Control B */
    register8_t CTRLC; /* Control C */
    register8_t CTRLD; /* Control D */
} VREF_t;
/* ADC0 reference select */
typedef enum VREF_ADC0REFSEL_enum
{
    VREF_ADC0REFSEL_0V55_gc = (0x00<<4), /* Voltage reference at 0.55V */
    VREF_ADC0REFSEL_1V1_gc = (0x01<<4), /* Voltage reference at 1.1V */
    VREF_ADC0REFSEL_2V5_gc = (0x02<<4), /* Voltage reference at 2.5V */
    VREF_ADC0REFSEL_4V34_gc = (0x03<<4), /* Voltage reference at 4.34V */
    VREF_ADC0REFSEL_1V5_gc = (0x04<<4) /* Voltage reference at 1.5V */
} VREF_ADC0REFSEL_t;
/* ADC1 reference select */
typedef enum VREF_ADC1REFSEL_enum
{
    VREF_ADC1REFSEL_0V55_gc = (0x00<<4), /* Voltage reference at 0.55V */
    VREF_ADC1REFSEL_1V1_gc = (0x01<<4), /* Voltage reference at 1.1V */
    VREF_ADC1REFSEL_2V5_gc = (0x02<<4), /* Voltage reference at 2.5V */
    VREF_ADC1REFSEL_4V34_gc = (0x03<<4), /* Voltage reference at 4.34V */
    VREF_ADC1REFSEL_1V5_gc = (0x04<<4) /* Voltage reference at 1.5V */
} VREF_ADC1REFSEL_t;
/* DAC0/AC0 reference select */
typedef enum VREF_DAC0REFSEL_enum
{
    VREF_DAC0REFSEL_0V55_gc = (0x00<<0), /* Voltage reference at 0.55V */
    VREF_DAC0REFSEL_1V1_gc = (0x01<<0), /* Voltage reference at 1.1V */
    VREF_DAC0REFSEL_2V5_gc = (0x02<<0), /* Voltage reference at 2.5V */
    VREF_DAC0REFSEL_4V34_gc = (0x03<<0), /* Voltage reference at 4.34V */
    VREF_DAC0REFSEL_1V5_gc = (0x04<<0) /* Voltage reference at 1.5V */
} VREF_DAC0REFSEL_t;
/* DAC1/AC1 reference select */
typedef enum VREF_DAC1REFSEL_enum
{
    VREF_DAC1REFSEL_0V55_gc = (0x00<<0), /* Voltage reference at 0.55V */
    VREF_DAC1REFSEL_1V1_gc = (0x01<<0), /* Voltage reference at 1.1V */
    VREF_DAC1REFSEL_2V5_gc = (0x02<<0), /* Voltage reference at 2.5V */
    VREF_DAC1REFSEL_4V34_gc = (0x03<<0), /* Voltage reference at 4.34V */
    VREF_DAC1REFSEL_1V5_gc = (0x04<<0) /* Voltage reference at 1.5V */
} VREF_DAC1REFSEL_t;
/* DAC2/AC2 reference select */
typedef enum VREF_DAC2REFSEL_enum
{
    VREF_DAC2REFSEL_0V55_gc = (0x00<<0), /* Voltage reference at 0.55V */
    VREF_DAC2REFSEL_1V1_gc = (0x01<<0), /* Voltage reference at 1.1V */
    VREF_DAC2REFSEL_2V5_gc = (0x02<<0), /* Voltage reference at 2.5V */
    VREF_DAC2REFSEL_4V34_gc = (0x03<<0), /* Voltage reference at 4.34V */
    VREF_DAC2REFSEL_1V5_gc = (0x04<<0) /* Voltage reference at 1.5V */
} VREF_DAC2REFSEL_t;
/*
--------------------------------------------------------------------------
WDT - Watch-Dog Timer
--------------------------------------------------------------------------
*/
/* Watch-Dog Timer */
typedef struct WDT_struct
{
    register8_t CTRLA; /* Control A */
    register8_t STATUS; /* Status */
} WDT_t;
/* Period select */
typedef enum WDT_PERIOD_enum
{
    WDT_PERIOD_OFF_gc = (0x00<<0), /* Off */
    WDT_PERIOD_8CLK_gc = (0x01<<0), /* 8 cycles (8ms) */
    WDT_PERIOD_16CLK_gc = (0x02<<0), /* 16 cycles (16ms) */
    WDT_PERIOD_32CLK_gc = (0x03<<0), /* 32 cycles (32ms) */
    WDT_PERIOD_64CLK_gc = (0x04<<0), /* 64 cycles (64ms) */
    WDT_PERIOD_128CLK_gc = (0x05<<0), /* 128 cycles (0.128s) */
    WDT_PERIOD_256CLK_gc = (0x06<<0), /* 256 cycles (0.256s) */
    WDT_PERIOD_512CLK_gc = (0x07<<0), /* 512 cycles (0.512s) */
    WDT_PERIOD_1KCLK_gc = (0x08<<0), /* 1K cycles (1.0s) */
    WDT_PERIOD_2KCLK_gc = (0x09<<0), /* 2K cycles (2.0s) */
    WDT_PERIOD_4KCLK_gc = (0x0A<<0), /* 4K cycles (4.1s) */
    WDT_PERIOD_8KCLK_gc = (0x0B<<0) /* 8K cycles (8.2s) */
} WDT_PERIOD_t;
/* Window select */
typedef enum WDT_WINDOW_enum
{
    WDT_WINDOW_OFF_gc = (0x00<<4), /* Off */
    WDT_WINDOW_8CLK_gc = (0x01<<4), /* 8 cycles (8ms) */
    WDT_WINDOW_16CLK_gc = (0x02<<4), /* 16 cycles (16ms) */
    WDT_WINDOW_32CLK_gc = (0x03<<4), /* 32 cycles (32ms) */
    WDT_WINDOW_64CLK_gc = (0x04<<4), /* 64 cycles (64ms) */
    WDT_WINDOW_128CLK_gc = (0x05<<4), /* 128 cycles (0.128s) */
    WDT_WINDOW_256CLK_gc = (0x06<<4), /* 256 cycles (0.256s) */
    WDT_WINDOW_512CLK_gc = (0x07<<4), /* 512 cycles (0.512s) */
    WDT_WINDOW_1KCLK_gc = (0x08<<4), /* 1K cycles (1.0s) */
    WDT_WINDOW_2KCLK_gc = (0x09<<4), /* 2K cycles (2.0s) */
    WDT_WINDOW_4KCLK_gc = (0x0A<<4), /* 4K cycles (4.1s) */
    WDT_WINDOW_8KCLK_gc = (0x0B<<4) /* 8K cycles (8.2s) */
} WDT_WINDOW_t;
/*
==========================================================================
IO Module Instances. Mapped to memory.
==========================================================================
*/
/* ========== Flattened fully qualified IO register names ========== */
/* VPORT (VPORTA) - Virtual Ports */
/* VPORT (VPORTB) - Virtual Ports */
/* VPORT (VPORTC) - Virtual Ports */
/* GPIO - General Purpose IO */
/* Deprecated */
/* CPU - CPU */
/* RSTCTRL - Reset controller */
/* SLPCTRL - Sleep Controller */
/* CLKCTRL - Clock controller */
/* BOD - Bod interface */
/* VREF - Voltage reference */
/* WDT - Watch-Dog Timer */
/* CPUINT - Interrupt Controller */
/* CRCSCAN - CRCSCAN */
/* RTC - Real-Time Counter */
/* EVSYS - Event System */
/* CCL - Configurable Custom Logic */
/* PORTMUX - Port Multiplexer */
/* PORT (PORTA) - I/O Ports */
/* PORT (PORTB) - I/O Ports */
/* PORT (PORTC) - I/O Ports */
/* ADC (ADC0) - Analog to Digital Converter */
/* ADC (ADC1) - Analog to Digital Converter */
/* AC (AC0) - Analog Comparator */
/* AC (AC1) - Analog Comparator */
/* AC (AC2) - Analog Comparator */
/* DAC (DAC0) - Digital to Analog Converter */
/* DAC (DAC1) - Digital to Analog Converter */
/* DAC (DAC2) - Digital to Analog Converter */
/* USART (USART0) - Universal Synchronous and Asynchronous Receiver and Transmitter */
/* TWI (TWI0) - Two-Wire Interface */
/* SPI (SPI0) - Serial Peripheral Interface */
/* TCA (TCA0) - 16-bit Timer/Counter Type A - Single Mode */
/* TCA (TCA0) - 16-bit Timer/Counter Type A - Split Mode */
/* TCB (TCB0) - 16-bit Timer Type B */
/* TCB (TCB1) - 16-bit Timer Type B */
/* TCD (TCD0) - Timer Counter D */
/* SYSCFG - System Configuration Registers */
/* NVMCTRL - Non-volatile Memory Controller */
/* SIGROW - Signature row */
/* FUSE - Fuses */
/* LOCKBIT - Lockbit */
/* USERROW - User Row */
/*================== Bitfield Definitions ================== */
/* AC - Analog Comparator */
/* AC.CTRLA  bit masks and bit positions */
/* AC.MUXCTRLA  bit masks and bit positions */
/* AC.INTCTRL  bit masks and bit positions */
/* AC.STATUS  bit masks and bit positions */
/* AC_CMP  is already defined. */
/* ADC - Analog to Digital Converter */
/* ADC.CTRLA  bit masks and bit positions */
/* ADC.CTRLB  bit masks and bit positions */
/* ADC.CTRLC  bit masks and bit positions */
/* ADC.CTRLD  bit masks and bit positions */
/* ADC.CTRLE  bit masks and bit positions */
/* ADC.SAMPCTRL  bit masks and bit positions */
/* ADC.MUXPOS  bit masks and bit positions */
/* ADC.COMMAND  bit masks and bit positions */
/* ADC.EVCTRL  bit masks and bit positions */
/* ADC.INTCTRL  bit masks and bit positions */
/* ADC.INTFLAGS  bit masks and bit positions */
/* ADC_RESRDY  is already defined. */
/* ADC_WCMP  is already defined. */
/* ADC.DBGCTRL  bit masks and bit positions */
/* ADC.TEMP  bit masks and bit positions */
/* ADC.CALIB  bit masks and bit positions */
/* BOD - Bod interface */
/* BOD.CTRLA  bit masks and bit positions */
/* BOD.CTRLB  bit masks and bit positions */
/* BOD.VLMCTRLA  bit masks and bit positions */
/* BOD.INTCTRL  bit masks and bit positions */
/* BOD.INTFLAGS  bit masks and bit positions */
/* BOD.STATUS  bit masks and bit positions */
/* CCL - Configurable Custom Logic */
/* CCL.CTRLA  bit masks and bit positions */
/* CCL.SEQCTRL0  bit masks and bit positions */
/* CCL.LUT0CTRLA  bit masks and bit positions */
/* CCL_ENABLE  is already defined. */
/* CCL.LUT0CTRLB  bit masks and bit positions */
/* CCL.LUT0CTRLC  bit masks and bit positions */
/* CCL.LUT1CTRLA  bit masks and bit positions */
/* CCL_ENABLE  is already defined. */
/* CCL_OUTEN  is already defined. */
/* CCL_FILTSEL  is already defined. */
/* CCL_CLKSRC  is already defined. */
/* CCL_EDGEDET  is already defined. */
/* CCL.LUT1CTRLB  bit masks and bit positions */
/* CCL_INSEL0  is already defined. */
/* CCL_INSEL1  is already defined. */
/* CCL.LUT1CTRLC  bit masks and bit positions */
/* CCL_INSEL2  is already defined. */
/* CLKCTRL - Clock controller */
/* CLKCTRL.MCLKCTRLA  bit masks and bit positions */
/* CLKCTRL.MCLKCTRLB  bit masks and bit positions */
/* CLKCTRL.MCLKLOCK  bit masks and bit positions */
/* CLKCTRL.MCLKSTATUS  bit masks and bit positions */
/* CLKCTRL.OSC20MCTRLA  bit masks and bit positions */
/* CLKCTRL.OSC20MCALIBA  bit masks and bit positions */
/* CLKCTRL.OSC20MCALIBB  bit masks and bit positions */
/* CLKCTRL.OSC32KCTRLA  bit masks and bit positions */
/* CLKCTRL_RUNSTDBY  is already defined. */
/* CLKCTRL.XOSC32KCTRLA  bit masks and bit positions */
/* CLKCTRL_RUNSTDBY  is already defined. */
/* CPU - CPU */
/* CPU.CCP  bit masks and bit positions */
/* CPU.SREG  bit masks and bit positions */
/* CPUINT - Interrupt Controller */
/* CPUINT.CTRLA  bit masks and bit positions */
/* CPUINT.STATUS  bit masks and bit positions */
/* CPUINT.LVL0PRI  bit masks and bit positions */
/* CPUINT.LVL1VEC  bit masks and bit positions */
/* CRCSCAN - CRCSCAN */
/* CRCSCAN.CTRLA  bit masks and bit positions */
/* CRCSCAN.CTRLB  bit masks and bit positions */
/* CRCSCAN.STATUS  bit masks and bit positions */
/* DAC - Digital to Analog Converter */
/* DAC.CTRLA  bit masks and bit positions */
/* EVSYS - Event System */
/* EVSYS.ASYNCCH0  bit masks and bit positions */
/* EVSYS.ASYNCCH1  bit masks and bit positions */
/* EVSYS.ASYNCCH2  bit masks and bit positions */
/* EVSYS.ASYNCCH3  bit masks and bit positions */
/* EVSYS.SYNCCH0  bit masks and bit positions */
/* EVSYS.SYNCCH1  bit masks and bit positions */
/* EVSYS.ASYNCUSER0  bit masks and bit positions */
/* EVSYS.ASYNCUSER1  bit masks and bit positions */
/* EVSYS.ASYNCUSER2  bit masks and bit positions */
/* EVSYS.ASYNCUSER3  bit masks and bit positions */
/* EVSYS.ASYNCUSER4  bit masks and bit positions */
/* EVSYS.ASYNCUSER5  bit masks and bit positions */
/* EVSYS.ASYNCUSER6  bit masks and bit positions */
/* EVSYS.ASYNCUSER7  bit masks and bit positions */
/* EVSYS.ASYNCUSER8  bit masks and bit positions */
/* EVSYS.ASYNCUSER9  bit masks and bit positions */
/* EVSYS.ASYNCUSER10  bit masks and bit positions */
/* EVSYS.ASYNCUSER11  bit masks and bit positions */
/* EVSYS.ASYNCUSER12  bit masks and bit positions */
/* EVSYS.SYNCUSER0  bit masks and bit positions */
/* EVSYS.SYNCUSER1  bit masks and bit positions */
/* FUSE - Fuses */
/* FUSE.WDTCFG  bit masks and bit positions */
/* FUSE.BODCFG  bit masks and bit positions */
/* FUSE.OSCCFG  bit masks and bit positions */
/* FUSE.TCD0CFG  bit masks and bit positions */
/* FUSE.SYSCFG0  bit masks and bit positions */
/* FUSE.SYSCFG1  bit masks and bit positions */
/* LOCKBIT - Lockbit */
/* LOCKBIT.LOCKBIT  bit masks and bit positions */
/* NVMCTRL - Non-volatile Memory Controller */
/* NVMCTRL.CTRLA  bit masks and bit positions */
/* NVMCTRL.CTRLB  bit masks and bit positions */
/* NVMCTRL.STATUS  bit masks and bit positions */
/* NVMCTRL.INTCTRL  bit masks and bit positions */
/* NVMCTRL.INTFLAGS  bit masks and bit positions */
/* NVMCTRL_EEREADY  is already defined. */
/* PORT - I/O Ports */
/* PORT.INTFLAGS  bit masks and bit positions */
/* PORT.PIN0CTRL  bit masks and bit positions */
/* PORT.PIN1CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_PULLUPEN  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT.PIN2CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_PULLUPEN  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT.PIN3CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_PULLUPEN  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT.PIN4CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_PULLUPEN  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT.PIN5CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_PULLUPEN  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT.PIN6CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_PULLUPEN  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORT.PIN7CTRL  bit masks and bit positions */
/* PORT_ISC  is already defined. */
/* PORT_PULLUPEN  is already defined. */
/* PORT_INVEN  is already defined. */
/* PORTMUX - Port Multiplexer */
/* PORTMUX.CTRLA  bit masks and bit positions */
/* PORTMUX.CTRLB  bit masks and bit positions */
/* PORTMUX.CTRLC  bit masks and bit positions */
/* PORTMUX.CTRLD  bit masks and bit positions */
/* RSTCTRL - Reset controller */
/* RSTCTRL.RSTFR  bit masks and bit positions */
/* RSTCTRL.SWRR  bit masks and bit positions */
/* RTC - Real-Time Counter */
/* RTC.CTRLA  bit masks and bit positions */
/* RTC.STATUS  bit masks and bit positions */
/* RTC.INTCTRL  bit masks and bit positions */
/* RTC.INTFLAGS  bit masks and bit positions */
/* RTC_OVF  is already defined. */
/* RTC_CMP  is already defined. */
/* RTC.DBGCTRL  bit masks and bit positions */
/* RTC.CLKSEL  bit masks and bit positions */
/* RTC.PITCTRLA  bit masks and bit positions */
/* RTC.PITSTATUS  bit masks and bit positions */
/* RTC.PITINTCTRL  bit masks and bit positions */
/* RTC.PITINTFLAGS  bit masks and bit positions */
/* RTC_PI  is already defined. */
/* RTC.PITDBGCTRL  bit masks and bit positions */
/* RTC_DBGRUN  is already defined. */
/* SLPCTRL - Sleep Controller */
/* SLPCTRL.CTRLA  bit masks and bit positions */
/* SPI - Serial Peripheral Interface */
/* SPI.CTRLA  bit masks and bit positions */
/* SPI.CTRLB  bit masks and bit positions */
/* SPI.INTCTRL  bit masks and bit positions */
/* SPI.INTFLAGS  bit masks and bit positions */
/* SYSCFG - System Configuration Registers */
/* SYSCFG.EXTBRK  bit masks and bit positions */
/* TCA - 16-bit Timer/Counter Type A */
/* TCA_SINGLE.CTRLA  bit masks and bit positions */
/* TCA_SINGLE.CTRLB  bit masks and bit positions */
/* TCA_SINGLE.CTRLC  bit masks and bit positions */
/* TCA_SINGLE.CTRLD  bit masks and bit positions */
/* TCA_SINGLE.CTRLECLR  bit masks and bit positions */
/* TCA_SINGLE.CTRLESET  bit masks and bit positions */
/* TCA_SINGLE_DIR  is already defined. */
/* TCA_SINGLE_LUPD  is already defined. */
/* TCA_SINGLE_CMD  is already defined. */
/* TCA_SINGLE.CTRLFCLR  bit masks and bit positions */
/* TCA_SINGLE.CTRLFSET  bit masks and bit positions */
/* TCA_SINGLE_PERBV  is already defined. */
/* TCA_SINGLE_CMP0BV  is already defined. */
/* TCA_SINGLE_CMP1BV  is already defined. */
/* TCA_SINGLE_CMP2BV  is already defined. */
/* TCA_SINGLE.EVCTRL  bit masks and bit positions */
/* TCA_SINGLE.INTCTRL  bit masks and bit positions */
/* TCA_SINGLE.INTFLAGS  bit masks and bit positions */
/* TCA_SINGLE_OVF  is already defined. */
/* TCA_SINGLE_CMP0  is already defined. */
/* TCA_SINGLE_CMP1  is already defined. */
/* TCA_SINGLE_CMP2  is already defined. */
/* TCA_SINGLE.DBGCTRL  bit masks and bit positions */
/* TCA_SPLIT.CTRLA  bit masks and bit positions */
/* TCA_SPLIT.CTRLB  bit masks and bit positions */
/* TCA_SPLIT.CTRLC  bit masks and bit positions */
/* TCA_SPLIT.CTRLD  bit masks and bit positions */
/* TCA_SPLIT.CTRLECLR  bit masks and bit positions */
/* TCA_SPLIT.CTRLESET  bit masks and bit positions */
/* TCA_SPLIT_CMD  is already defined. */
/* TCA_SPLIT.INTCTRL  bit masks and bit positions */
/* TCA_SPLIT.INTFLAGS  bit masks and bit positions */
/* TCA_SPLIT_LUNF  is already defined. */
/* TCA_SPLIT_HUNF  is already defined. */
/* TCA_SPLIT_LCMP0  is already defined. */
/* TCA_SPLIT_LCMP1  is already defined. */
/* TCA_SPLIT_LCMP2  is already defined. */
/* TCA_SPLIT.DBGCTRL  bit masks and bit positions */
/* TCB - 16-bit Timer Type B */
/* TCB.CTRLA  bit masks and bit positions */
/* TCB.CTRLB  bit masks and bit positions */
/* TCB.EVCTRL  bit masks and bit positions */
/* TCB.INTCTRL  bit masks and bit positions */
/* TCB.INTFLAGS  bit masks and bit positions */
/* TCB_CAPT  is already defined. */
/* TCB.STATUS  bit masks and bit positions */
/* TCB.DBGCTRL  bit masks and bit positions */
/* TCD - Timer Counter D */
/* TCD.CTRLA  bit masks and bit positions */
/* TCD.CTRLB  bit masks and bit positions */
/* TCD.CTRLC  bit masks and bit positions */
/* TCD.CTRLD  bit masks and bit positions */
/* TCD.CTRLE  bit masks and bit positions */
/* TCD.EVCTRLA  bit masks and bit positions */
/* TCD.EVCTRLB  bit masks and bit positions */
/* TCD_TRIGEI  is already defined. */
/* TCD_ACTION  is already defined. */
/* TCD_EDGE  is already defined. */
/* TCD_CFG  is already defined. */
/* TCD.INTCTRL  bit masks and bit positions */
/* TCD.INTFLAGS  bit masks and bit positions */
/* TCD_OVF  is already defined. */
/* TCD_TRIGA  is already defined. */
/* TCD_TRIGB  is already defined. */
/* TCD.STATUS  bit masks and bit positions */
/* TCD.INPUTCTRLA  bit masks and bit positions */
/* TCD.INPUTCTRLB  bit masks and bit positions */
/* TCD_INPUTMODE  is already defined. */
/* TCD.FAULTCTRL  bit masks and bit positions */
/* TCD.DLYCTRL  bit masks and bit positions */
/* TCD.DLYVAL  bit masks and bit positions */
/* TCD.DITCTRL  bit masks and bit positions */
/* TCD.DITVAL  bit masks and bit positions */
/* TCD.DBGCTRL  bit masks and bit positions */
/* TCD.CMPASET  bit masks and bit positions */
/* TCD.CMPACLR  bit masks and bit positions */
/* TCD.CMPBSET  bit masks and bit positions */
/* TCD.CMPBCLR  bit masks and bit positions */
/* TWI - Two-Wire Interface */
/* TWI.CTRLA  bit masks and bit positions */
/* TWI.DBGCTRL  bit masks and bit positions */
/* TWI.MCTRLA  bit masks and bit positions */
/* TWI.MCTRLB  bit masks and bit positions */
/* TWI.MSTATUS  bit masks and bit positions */
/* TWI.SCTRLA  bit masks and bit positions */
/* TWI_ENABLE  is already defined. */
/* TWI_SMEN  is already defined. */
/* TWI.SCTRLB  bit masks and bit positions */
/* TWI_ACKACT  is already defined. */
/* TWI.SSTATUS  bit masks and bit positions */
/* TWI_BUSERR  is already defined. */
/* TWI_RXACK  is already defined. */
/* TWI_CLKHOLD  is already defined. */
/* TWI.SADDRMASK  bit masks and bit positions */
/* USART - Universal Synchronous and Asynchronous Receiver and Transmitter */
/* USART.RXDATAL  bit masks and bit positions */
/* USART.RXDATAH  bit masks and bit positions */
/* USART.TXDATAL  bit masks and bit positions */
/* USART_DATA  is already defined. */
/* USART.TXDATAH  bit masks and bit positions */
/* USART_DATA8  is already defined. */
/* USART.STATUS  bit masks and bit positions */
/* USART_RXCIF  is already defined. */
/* USART.CTRLA  bit masks and bit positions */
/* USART.CTRLB  bit masks and bit positions */
/* USART.CTRLC  bit masks and bit positions */
/* USART.DBGCTRL  bit masks and bit positions */
/* USART.EVCTRL  bit masks and bit positions */
/* USART.TXPLCTRL  bit masks and bit positions */
/* USART.RXPLCTRL  bit masks and bit positions */
/* VPORT - Virtual Ports */
/* VPORT.INTFLAGS  bit masks and bit positions */
/* VREF - Voltage reference */
/* VREF.CTRLA  bit masks and bit positions */
/* VREF.CTRLB  bit masks and bit positions */
/* VREF.CTRLC  bit masks and bit positions */
/* VREF.CTRLD  bit masks and bit positions */
/* WDT - Watch-Dog Timer */
/* WDT.CTRLA  bit masks and bit positions */
/* WDT.STATUS  bit masks and bit positions */
/* ========== Generic Port Pins ========== */
/* ========== Interrupt Vector Definitions ========== */
/* Vector 0 is the reset vector */
/* CRCSCAN interrupt vectors */
/* BOD interrupt vectors */
/* PORTA interrupt vectors */
/* PORTB interrupt vectors */
/* PORTC interrupt vectors */
/* RTC interrupt vectors */
/* TCA0 interrupt vectors */
/* TCB0 interrupt vectors */
/* TCB1 interrupt vectors */
/* TCD0 interrupt vectors */
/* AC0 interrupt vectors */
/* AC1 interrupt vectors */
/* AC2 interrupt vectors */
/* ADC0 interrupt vectors */
/* ADC1 interrupt vectors */
/* TWI0 interrupt vectors */
/* SPI0 interrupt vectors */
/* USART0 interrupt vectors */
/* NVMCTRL interrupt vectors */
/* ========== Constants ========== */
/* Added MAPPED_EEPROM segment names for avr-libc */
/* ========== Fuses ========== */
/* Fuse Byte 0 (WDTCFG) */
/* Fuse Byte 1 (BODCFG) */
/* Fuse Byte 2 (OSCCFG) */
/* Fuse Byte 3 Reserved */
/* Fuse Byte 4 (TCD0CFG) */
/* Fuse Byte 5 (SYSCFG0) */
/* Fuse Byte 6 (SYSCFG1) */
/* Fuse Byte 7 (APPEND) */
/* Fuse Byte 8 (BOOTEND) */
/* ========== Lock Bits ========== */
/* ========== Signature ========== */
/* Copyright (c) 2003  Theodore A. Roth
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* This file should only be included from <avr/io.h>, never directly. */
/* Define Generic PORTn, DDn, and PINn values. */
/* Port Data Register (generic) */
/* Port Data Direction Register (generic) */
/* Port Input Pins (generic) */
/* Define PORTxn an Pxn values for all possible port pins if not defined already by io.h. */
/* PORT A */
/* PORT B */
/* PORT C */
/* PORT D */
/* PORT E */
/* PORT F */
/* PORT G */
/* PORT H */
/* PORT J */
/* PORT K */
/* PORT L */
/* Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002, Marek Michalkiewicz <marekm@amelek.gda.pl>
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.  */
/* avr/sfr_defs.h - macros for accessing AVR special function registers */
/* $Id$ */
/* 
This purpose of this header is to define registers that have not been 
previously defined in the individual device IO header files, and to define 
other symbols that are common across AVR device families.
This file is designed to be included in <avr/io.h> after the individual
device IO header files, and after <avr/sfr_defs.h>
*/
/*------------ Registers Not Previously Defined ------------*/
/* 
These are registers that are not previously defined in the individual
IO header files, OR they are defined here because they are used in parts of
avr-libc even if a device is not selected but a general architecture has
been selected.
*/
/*
Stack pointer register.
AVR architecture 1 has no RAM, thus no stack pointer. 
All other architectures do have a stack pointer.  Some devices have only
less than 256 bytes of possible RAM locations (128 Bytes of SRAM
and no option for external RAM), thus SPH is officially "reserved"
for them.
*/
/* Status Register */
/* SREG bit definitions */
/*------------ Common Symbols ------------*/
/* 
Generic definitions for registers that are common across multiple AVR devices
and families.
*/
/* Pointer registers definitions */
/* Status Register */
/* Stack Pointer (combined) Register */
/* Stack Pointer High Register */
/* Stack Pointer Low Register */
/* RAMPD Register */
/* RAMPX Register */
/* RAMPY Register */
/* RAMPZ Register */
/* Extended Indirect Register */
/*------------ Workaround to old compilers (4.1.2 and earlier)  ------------*/
/* Copyright (c) 2005, Joerg Wunsch                               -*- c -*-
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \defgroup avr_version <avr/version.h>: avr-libc version macros
    \code #include <avr/version.h> \endcode
    This header file defines macros that contain version numbers and
    strings describing the current version of avr-libc.
    The version number itself basically consists of three pieces that
    are separated by a dot: the major number, the minor number, and
    the revision number.  For development versions (which use an odd
    minor number), the string representation additionally gets the
    date code (YYYYMMDD) appended.
    This file will also be included by \c <avr/io.h>.  That way,
    portable tests can be implemented using \c <avr/io.h> that can be
    used in code that wants to remain backwards-compatible to library
    versions prior to the date when the library version API had been
    added, as referenced but undefined C preprocessor macros
    automatically evaluate to 0.
*/
/** \ingroup avr_version
    String literal representation of the current library version. */
/** \ingroup avr_version
    Numerical representation of the current library version.
    In the numerical representation, the major number is multiplied by
    10000, the minor number by 100, and all three parts are then
    added.  It is intented to provide a monotonically increasing
    numerical value that can easily be used in numerical checks.
 */
/** \ingroup avr_version
    String literal representation of the release date. */
/** \ingroup avr_version
    Numerical representation of the release date. */
/** \ingroup avr_version
    Library major version number. */
/** \ingroup avr_version
    Library minor version number. */
/** \ingroup avr_version
    Library revision number. */
/* Copyright (c) 2012 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/*
 * This file is included by <avr/io.h> whenever compiling for an Xmega
 * device.  It abstracts certain features common to the Xmega device
 * families.
 */
/* Include fuse.h after individual IO header files. */
/* Copyright (c) 2007, Atmel Corporation
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* avr/fuse.h - Fuse API */
/* This file must be explicitly included by <avr/io.h>. */
/** \file */
/** \defgroup avr_fuse <avr/fuse.h>: Fuse Support
    \par Introduction
    The Fuse API allows a user to specify the fuse settings for the specific
    AVR device they are compiling for. These fuse settings will be placed
    in a special section in the ELF output file, after linking.
    Programming tools can take advantage of the fuse information embedded in
    the ELF file, by extracting this information and determining if the fuses
    need to be programmed before programming the Flash and EEPROM memories.
    This also allows a single ELF file to contain all the
    information needed to program an AVR. 
    To use the Fuse API, include the <avr/io.h> header file, which in turn
    automatically includes the individual I/O header file and the <avr/fuse.h>
    file. These other two files provides everything necessary to set the AVR
    fuses.
    
    \par Fuse API
    
    Each I/O header file must define the FUSE_MEMORY_SIZE macro which is
    defined to the number of fuse bytes that exist in the AVR device.
    
    A new type, __fuse_t, is defined as a structure. The number of fields in 
    this structure are determined by the number of fuse bytes in the 
    FUSE_MEMORY_SIZE macro.
    
    If FUSE_MEMORY_SIZE == 1, there is only a single field: byte, of type
    unsigned char.
    
    If FUSE_MEMORY_SIZE == 2, there are two fields: low, and high, of type
    unsigned char.
    
    If FUSE_MEMORY_SIZE == 3, there are three fields: low, high, and extended,
    of type unsigned char.
    
    If FUSE_MEMORY_SIZE > 3, there is a single field: byte, which is an array
    of unsigned char with the size of the array being FUSE_MEMORY_SIZE.
    
    A convenience macro, FUSEMEM, is defined as a GCC attribute for a 
    custom-named section of ".fuse".
    
    A convenience macro, FUSES, is defined that declares a variable, __fuse, of
    type __fuse_t with the attribute defined by FUSEMEM. This variable
    allows the end user to easily set the fuse data.
    \note If a device-specific I/O header file has previously defined FUSEMEM,
    then FUSEMEM is not redefined. If a device-specific I/O header file has
    previously defined FUSES, then FUSES is not redefined.
    Each AVR device I/O header file has a set of defined macros which specify the
    actual fuse bits available on that device. The AVR fuses have inverted
    values, logical 1 for an unprogrammed (disabled) bit and logical 0 for a
    programmed (enabled) bit. The defined macros for each individual fuse
    bit represent this in their definition by a bit-wise inversion of a mask.
    For example, the FUSE_EESAVE fuse in the ATmega128 is defined as:
    \code
    #define FUSE_EESAVE      ~_BV(3)
    \endcode
    \note The _BV macro creates a bit mask from a bit number. It is then 
    inverted to represent logical values for a fuse memory byte.
    
    To combine the fuse bits macros together to represent a whole fuse byte,
    use the bitwise AND operator, like so:
    \code
    (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN)
    \endcode
    
    Each device I/O header file also defines macros that provide default values
    for each fuse byte that is available. LFUSE_DEFAULT is defined for a Low
    Fuse byte. HFUSE_DEFAULT is defined for a High Fuse byte. EFUSE_DEFAULT
    is defined for an Extended Fuse byte.
    
    If FUSE_MEMORY_SIZE > 3, then the I/O header file defines macros that
    provide default values for each fuse byte like so:
    FUSE0_DEFAULT
    FUSE1_DEFAULT
    FUSE2_DEFAULT
    FUSE3_DEFAULT
    FUSE4_DEFAULT
    ....
    
    \par API Usage Example
    
    Putting all of this together is easy. Using C99's designated initializers:
    
    \code
    #include <avr/io.h>
    FUSES = 
    {
        .low = LFUSE_DEFAULT,
        .high = (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN),
        .extended = EFUSE_DEFAULT,
    };
    int main(void)
    {
        return 0;
    }
    \endcode
    
    Or, using the variable directly instead of the FUSES macro,
    
    \code
    #include <avr/io.h>
    __fuse_t __fuse __attribute__((section (".fuse"))) = 
    {
        .low = LFUSE_DEFAULT,
        .high = (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN),
        .extended = EFUSE_DEFAULT,
    };
    int main(void)
    {
        return 0;
    }
    \endcode
    
    If you are compiling in C++, you cannot use the designated intializers so
    you must do:
    \code
    #include <avr/io.h>
    FUSES = 
    {
        LFUSE_DEFAULT, // .low
        (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN), // .high
        EFUSE_DEFAULT, // .extended
    };
    int main(void)
    {
        return 0;
    }
    \endcode
    
    
    However there are a number of caveats that you need to be aware of to
    use this API properly.
    
    Be sure to include <avr/io.h> to get all of the definitions for the API.
    The FUSES macro defines a global variable to store the fuse data. This 
    variable is assigned to its own linker section. Assign the desired fuse 
    values immediately in the variable initialization.
    
    The .fuse section in the ELF file will get its values from the initial 
    variable assignment ONLY. This means that you can NOT assign values to 
    this variable in functions and the new values will not be put into the
    ELF .fuse section.
    
    The global variable is declared in the FUSES macro has two leading 
    underscores, which means that it is reserved for the "implementation",
    meaning the library, so it will not conflict with a user-named variable.
    
    You must initialize ALL fields in the __fuse_t structure. This is because
    the fuse bits in all bytes default to a logical 1, meaning unprogrammed. 
    Normal uninitialized data defaults to all locgial zeros. So it is vital that
    all fuse bytes are initialized, even with default data. If they are not,
    then the fuse bits may not programmed to the desired settings.
    
    Be sure to have the -mmcu=<em>device</em> flag in your compile command line and
    your linker command line to have the correct device selected and to have 
    the correct I/O header file included when you include <avr/io.h>.
    You can print out the contents of the .fuse section in the ELF file by
    using this command line:
    \code
    avr-objdump -s -j .fuse <ELF file>
    \endcode
    The section contents shows the address on the left, then the data going from
    lower address to a higher address, left to right.
*/
typedef struct
{
    unsigned char byte[10];
} __fuse_t;
/* Include lock.h after individual IO header files. */
/* Copyright (c) 2007, Atmel Corporation
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* avr/lock.h - Lock Bits API */
/** \file */
/** \defgroup avr_lock <avr/lock.h>: Lockbit Support
    \par Introduction
    The Lockbit API allows a user to specify the lockbit settings for the 
    specific AVR device they are compiling for. These lockbit settings will be 
    placed in a special section in the ELF output file, after linking.
    Programming tools can take advantage of the lockbit information embedded in
    the ELF file, by extracting this information and determining if the lockbits
    need to be programmed after programming the Flash and EEPROM memories.
    This also allows a single ELF file to contain all the
    information needed to program an AVR. 
    To use the Lockbit API, include the <avr/io.h> header file, which in turn
    automatically includes the individual I/O header file and the <avr/lock.h>
    file. These other two files provides everything necessary to set the AVR
    lockbits.
    
    \par Lockbit API
    
    Each I/O header file may define up to 3 macros that controls what kinds
    of lockbits are available to the user.
    
    If __LOCK_BITS_EXIST is defined, then two lock bits are available to the
    user and 3 mode settings are defined for these two bits.
    
    If __BOOT_LOCK_BITS_0_EXIST is defined, then the two BLB0 lock bits are
    available to the user and 4 mode settings are defined for these two bits.
    
    If __BOOT_LOCK_BITS_1_EXIST is defined, then the two BLB1 lock bits are
    available to the user and 4 mode settings are defined for these two bits.
    If __BOOT_LOCK_APPLICATION_TABLE_BITS_EXIST is defined then two lock bits
    are available to set the locking mode for the Application Table Section 
    (which is used in the XMEGA family).
    
    If __BOOT_LOCK_APPLICATION_BITS_EXIST is defined then two lock bits are
    available to set the locking mode for the Application Section (which is used
    in the XMEGA family).
    
    If __BOOT_LOCK_BOOT_BITS_EXIST is defined then two lock bits are available
    to set the locking mode for the Boot Loader Section (which is used in the
    XMEGA family).
    The AVR lockbit modes have inverted values, logical 1 for an unprogrammed 
    (disabled) bit and logical 0 for a programmed (enabled) bit. The defined 
    macros for each individual lock bit represent this in their definition by a 
    bit-wise inversion of a mask. For example, the LB_MODE_3 macro is defined 
    as:
    \code
    #define LB_MODE_3  (0xFC)
`   \endcode
    
    To combine the lockbit mode macros together to represent a whole byte,
    use the bitwise AND operator, like so:
    \code
    (LB_MODE_3 & BLB0_MODE_2)
    \endcode
    
    <avr/lock.h> also defines a macro that provides a default lockbit value:
    LOCKBITS_DEFAULT which is defined to be 0xFF.
    See the AVR device specific datasheet for more details about these
    lock bits and the available mode settings.
    
    A convenience macro, LOCKMEM, is defined as a GCC attribute for a 
    custom-named section of ".lock".
    
    A convenience macro, LOCKBITS, is defined that declares a variable, __lock, 
    of type unsigned char with the attribute defined by LOCKMEM. This variable
    allows the end user to easily set the lockbit data.
    \note If a device-specific I/O header file has previously defined LOCKMEM,
    then LOCKMEM is not redefined. If a device-specific I/O header file has
    previously defined LOCKBITS, then LOCKBITS is not redefined. LOCKBITS is
    currently known to be defined in the I/O header files for the XMEGA devices.
    \par API Usage Example
    
    Putting all of this together is easy:
    
    \code
    #include <avr/io.h>
    LOCKBITS = (LB_MODE_1 & BLB0_MODE_3 & BLB1_MODE_4);
    int main(void)
    {
        return 0;
    }
    \endcode
    
    Or:
    
    \code
    #include <avr/io.h>
    unsigned char __lock __attribute__((section (".lock"))) = 
        (LB_MODE_1 & BLB0_MODE_3 & BLB1_MODE_4);
    int main(void)
    {
        return 0;
    }
    \endcode
    
    
    
    However there are a number of caveats that you need to be aware of to
    use this API properly.
    
    Be sure to include <avr/io.h> to get all of the definitions for the API.
    The LOCKBITS macro defines a global variable to store the lockbit data. This 
    variable is assigned to its own linker section. Assign the desired lockbit 
    values immediately in the variable initialization.
    
    The .lock section in the ELF file will get its values from the initial 
    variable assignment ONLY. This means that you can NOT assign values to 
    this variable in functions and the new values will not be put into the
    ELF .lock section.
    
    The global variable is declared in the LOCKBITS macro has two leading 
    underscores, which means that it is reserved for the "implementation",
    meaning the library, so it will not conflict with a user-named variable.
    
    You must initialize the lockbit variable to some meaningful value, even
    if it is the default value. This is because the lockbits default to a 
    logical 1, meaning unprogrammed. Normal uninitialized data defaults to all 
    locgial zeros. So it is vital that all lockbits are initialized, even with 
    default data. If they are not, then the lockbits may not programmed to the 
    desired settings and can possibly put your device into an unrecoverable 
    state.
    
    Be sure to have the -mmcu=<em>device</em> flag in your compile command line and
    your linker command line to have the correct device selected and to have 
    the correct I/O header file included when you include <avr/io.h>.
    You can print out the contents of the .lock section in the ELF file by
    using this command line:
    \code
    avr-objdump -s -j .lock <ELF file>
    \endcode
*/
/* Lock Bit Modes */
/* Copyright (C) 1989-2015 Free Software Foundation, Inc.
This file is part of GCC.
GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.
GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.
You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */
/*
 * ISO C Standard:  7.17  Common definitions  <stddef.h>
 */
/* Any one of these symbols __need_* means that GNU libc
   wants us just to define one data type.  So don't define
   the symbols that indicate this file's entire job has been done.  */
/* snaroff@next.com says the NeXT needs this.  */
/* This avoids lossage on SunOS but only if stdtypes.h comes first.
   There's no way to win with the other order!  Sun lossage.  */
/* On 4.3bsd-net2, make sure ansi.h is included, so we have
   one less case to deal with in the following.  */
/* On FreeBSD 5, machine/ansi.h does not exist anymore... */
/* In 4.3bsd-net2, machine/ansi.h defines these symbols, which are
   defined if the corresponding type is *not* defined.
   FreeBSD-2.1 defines _MACHINE_ANSI_H_ instead of _ANSI_H_.
   NetBSD defines _I386_ANSI_H_ and _X86_64_ANSI_H_ instead of _ANSI_H_ */
/* Sequent's header files use _PTRDIFF_T_ in some conflicting way.
   Just ignore it.  */
/* On VxWorks, <type/vxTypesBase.h> may have defined macros like
   _TYPE_size_t which will typedef size_t.  fixincludes patched the
   vxTypesBase.h so that this macro is only defined if _GCC_SIZE_T is
   not defined, and so that defining this macro defines _GCC_SIZE_T.
   If we find that the macros are still defined at this point, we must
   invoke them so that the type is defined as expected.  */
/* In case nobody has defined these types, but we aren't running under
   GCC 2.00, make sure that __PTRDIFF_TYPE__, __SIZE_TYPE__, and
   __WCHAR_TYPE__ have reasonable values.  This can happen if the
   parts of GCC is compiled by an older compiler, that actually
   include gstddef.h, such as collect2.  */
/* Signed type of difference of two pointers.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
typedef int ptrdiff_t;
/* If this symbol has done its job, get rid of it.  */
/* Unsigned type of `sizeof' something.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
typedef unsigned int size_t;
/* Wide character type.
   Locale-writers should change this as necessary to
   be big enough to hold unique values not between 0 and 127,
   and not (wchar_t) -1, for each defined multibyte character.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
/* On BSD/386 1.1, at least, machine/ansi.h defines _BSD_WCHAR_T_
   instead of _WCHAR_T_, and _BSD_RUNE_T_ (which, unlike the other
   symbols in the _FOO_T_ family, stays defined even after its
   corresponding type is defined).  If we define wchar_t, then we
   must undef _WCHAR_T_; for BSD/386 1.1 (and perhaps others), if
   we undef _WCHAR_T_, then we must also define rune_t, since 
   headers like runetype.h assume that if machine/ansi.h is included,
   and _BSD_WCHAR_T_ is not defined, then rune_t is available.
   machine/ansi.h says, "Note that _WCHAR_T_ and _RUNE_T_ must be of
   the same type." */
/* FreeBSD 5 can't be handled well using "traditional" logic above
   since it no longer defines _BSD_RUNE_T_ yet still desires to export
   rune_t in some cases... */
typedef int wchar_t;
/*  In 4.3bsd-net2, leave these undefined to indicate that size_t, etc.
    are already defined.  */
/*  BSD/OS 3.1 and FreeBSD [23].x require the MACHINE_ANSI_H check here.  */
/*  NetBSD 5 requires the I386_ANSI_H and X86_64_ANSI_H checks here.  */
/* A null pointer constant.  */
/* Offset of member MEMBER in a struct of type TYPE. */
/** \defgroup avr_eeprom <avr/eeprom.h>: EEPROM handling
    \code #include <avr/eeprom.h> \endcode
    This header file declares the interface to some simple library
    routines suitable for handling the data EEPROM contained in the
    AVR microcontrollers.  The implementation uses a simple polled
    mode interface.  Applications that require interrupt-controlled
    EEPROM access to ensure that no time will be wasted in spinloops
    will have to deploy their own implementation.
    \par Notes:
    - In addition to the write functions there is a set of update ones.
    This functions read each byte first and skip the burning if the
    old value is the same with new.  The scaning direction is from
    high address to low, to obtain quick return in common cases.
    - All of the read/write functions first make sure the EEPROM is
    ready to be accessed.  Since this may cause long delays if a
    write operation is still pending, time-critical applications
    should first poll the EEPROM e. g. using eeprom_is_ready() before
    attempting any actual I/O.  But this functions are not wait until
    SELFPRGEN in SPMCSR becomes zero.  Do this manually, if your
    softwate contains the Flash burning.
    - As these functions modify IO registers, they are known to be
    non-reentrant.  If any of these functions are used from both,
    standard and interrupt context, the applications must ensure
    proper protection (e.g. by disabling interrupts before accessing
    them).
    - All write functions force erase_and_write programming mode.
    
    - For Xmega the EEPROM start address is 0, like other architectures.
    The reading functions add the 0x2000 value to use EEPROM mapping into
    data space.
 */
/** \def EEMEM
    \ingroup avr_eeprom
    Attribute expression causing a variable to be allocated within the
    .eeprom section.	*/
/** \def eeprom_is_ready
    \ingroup avr_eeprom
    \returns 1 if EEPROM is ready for a new read/write operation, 0 if not.
 */
/** \def eeprom_busy_wait
    \ingroup avr_eeprom
    Loops until the eeprom is no longer busy.
    \returns Nothing.
 */
/** \ingroup avr_eeprom
    Read one byte from EEPROM address \a __p.
 */
uint8_t eeprom_read_byte (const uint8_t *__p) __attribute__((__pure__));
/** \ingroup avr_eeprom
    Read one 16-bit word (little endian) from EEPROM address \a __p.
 */
uint16_t eeprom_read_word (const uint16_t *__p) __attribute__((__pure__));
/** \ingroup avr_eeprom
    Read one 32-bit double word (little endian) from EEPROM address \a __p.
 */
uint32_t eeprom_read_dword (const uint32_t *__p) __attribute__((__pure__));
/** \ingroup avr_eeprom
    Read one float value (little endian) from EEPROM address \a __p.
 */
float eeprom_read_float (const float *__p) __attribute__((__pure__));
/** \ingroup avr_eeprom
    Read a block of \a __n bytes from EEPROM address \a __src to SRAM
    \a __dst.
 */
void eeprom_read_block (void *__dst, const void *__src, size_t __n);
/** \ingroup avr_eeprom
    Write a byte \a __value to EEPROM address \a __p.
 */
void eeprom_write_byte (uint8_t *__p, uint8_t __value);
/** \ingroup avr_eeprom
    Write a word \a __value to EEPROM address \a __p.
 */
void eeprom_write_word (uint16_t *__p, uint16_t __value);
/** \ingroup avr_eeprom
    Write a 32-bit double word \a __value to EEPROM address \a __p.
 */
void eeprom_write_dword (uint32_t *__p, uint32_t __value);
/** \ingroup avr_eeprom
    Write a float \a __value to EEPROM address \a __p.
 */
void eeprom_write_float (float *__p, float __value);
/** \ingroup avr_eeprom
    Write a block of \a __n bytes to EEPROM address \a __dst from \a __src.
    \note The argument order is mismatch with common functions like strcpy().
 */
void eeprom_write_block (const void *__src, void *__dst, size_t __n);
/** \ingroup avr_eeprom
    Update a byte \a __value to EEPROM address \a __p.
 */
void eeprom_update_byte (uint8_t *__p, uint8_t __value);
/** \ingroup avr_eeprom
    Update a word \a __value to EEPROM address \a __p.
 */
void eeprom_update_word (uint16_t *__p, uint16_t __value);
/** \ingroup avr_eeprom
    Update a 32-bit double word \a __value to EEPROM address \a __p.
 */
void eeprom_update_dword (uint32_t *__p, uint32_t __value);
/** \ingroup avr_eeprom
    Update a float \a __value to EEPROM address \a __p.
 */
void eeprom_update_float (float *__p, float __value);
/** \ingroup avr_eeprom
    Update a block of \a __n bytes to EEPROM address \a __dst from \a __src.
    \note The argument order is mismatch with common functions like strcpy().
 */
void eeprom_update_block (const void *__src, void *__dst, size_t __n);
/** \name IAR C compatibility defines	*/
/*@{*/
/** \def _EEPUT
    \ingroup avr_eeprom
    Write a byte to EEPROM. Compatibility define for IAR C.	*/
/** \def __EEPUT
    \ingroup avr_eeprom
    Write a byte to EEPROM. Compatibility define for IAR C.	*/
/** \def _EEGET
    \ingroup avr_eeprom
    Read a byte from EEPROM. Compatibility define for IAR C.	*/
/** \def __EEGET
    \ingroup avr_eeprom
    Read a byte from EEPROM. Compatibility define for IAR C.	*/
/*@}*/
/* Copyright (c) 2002,2005,2007 Marek Michalkiewicz
   Copyright (c) 2007, Dean Camera
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/* Auxiliary macro for ISR_ALIAS(). */
/** 
\file 
\@{ 
*/
/** \name Global manipulation of the interrupt flag
    The global interrupt flag is maintained in the I bit of the status
    register (SREG).
    Handling interrupts frequently requires attention regarding atomic
    access to objects that could be altered by code running within an
    interrupt context, see <util/atomic.h>.
    Frequently, interrupts are being disabled for periods of time in
    order to perform certain operations without being disturbed; see
    \ref optim_code_reorder for things to be taken into account with
    respect to compiler optimizations.
*/
/** \name Macros for writing interrupt handler functions */
/** \name ISR attributes */
/* \@} */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/* Copyright (c) 2006, 2007, 2008  Eric B. Weddington
   Copyright (c) 2011 Frédéric Nadeau
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/** \file */
/** \defgroup avr_power <avr/power.h>: Power Reduction Management
\code #include <avr/power.h>\endcode
Many AVRs contain a Power Reduction Register (PRR) or Registers (PRRx) that 
allow you to reduce power consumption by disabling or enabling various on-board 
peripherals as needed. Some devices have the XTAL Divide Control Register
(XDIV) which offer similar functionality as System Clock Prescale
Register (CLKPR).
There are many macros in this header file that provide an easy interface
to enable or disable on-board peripherals to reduce power. See the table below.
\note Not all AVR devices have a Power Reduction Register (for example
the ATmega8). On those devices without a Power Reduction Register, the
power reduction macros are not available..
\note Not all AVR devices contain the same peripherals (for example, the LCD
interface), or they will be named differently (for example, USART and 
USART0). Please consult your device's datasheet, or the header file, to 
find out which macros are applicable to your device.
\note For device using the XTAL Divide Control Register (XDIV), when prescaler
is used, Timer/Counter0 can only be used in asynchronous mode. Keep in mind
that Timer/Counter0 source shall be less than ¼th of peripheral clock.
Therefore, when using a typical 32.768 kHz crystal, one shall not scale
the clock below 131.072 kHz.
*/
/** \addtogroup avr_power
\anchor avr_powermacros
<small>
<center>
<table border="3">
  <tr>
    <td width="10%"><strong>Power Macro</strong></td>
    <td width="15%"><strong>Description</strong></td>
  </tr>
  <tr>
    <td>power_aca_disable()</td>
    <td>Disable the Analog Comparator on PortA.</td>
  </tr>
  <tr>
    <td>power_aca_enable()</td>
    <td>Enable the Analog Comparator on PortA.</td>
  </tr>
  <tr>
    <td>power_adc_enable()</td>
    <td>Enable the Analog to Digital Converter module.</td>
  </tr>
  <tr>
    <td>power_adc_disable()</td>
    <td>Disable the Analog to Digital Converter module.</td>
  </tr>
  <tr>
    <td>power_adca_disable()</td>
    <td>Disable the Analog to Digital Converter module on PortA</td>
  </tr>
  <tr>
    <td>power_adca_enable()</td>
    <td>Enable the Analog to Digital Converter module on PortA</td>
  </tr>
  <tr>
    <td>power_evsys_disable()</td>
    <td>Disable the EVSYS module</td>
  </tr>
  <tr>
    <td>power_evsys_enable()</td>
    <td>Enable the EVSYS module</td>
  </tr>
  <tr>
    <td>power_hiresc_disable()</td>
    <td>Disable the HIRES module on PortC</td>
  </tr>
  <tr>
    <td>power_hiresc_enable()</td>
    <td>Enable the HIRES module on PortC</td>
  </tr>
   <tr>
    <td>power_lcd_enable()</td>
    <td>Enable the LCD module.</td>
  </tr>
  <tr>
    <td>power_lcd_disable().</td>
    <td>Disable the LCD module.</td>
  </tr>
  <tr>
    <td>power_pga_enable()</td>
    <td>Enable the Programmable Gain Amplifier module.</td>
  </tr>
  <tr>
    <td>power_pga_disable()</td>
    <td>Disable the Programmable Gain Amplifier module.</td>
  </tr>
  
  <tr>
    <td>power_pscr_enable()</td>
    <td>Enable the Reduced Power Stage Controller module.</td>
  </tr>
  <tr>
    <td>power_pscr_disable()</td>
    <td>Disable the Reduced Power Stage Controller module.</td>
  </tr>
  <tr>
    <td>power_psc0_enable()</td>
    <td>Enable the Power Stage Controller 0 module.</td>
  </tr>
  <tr>
    <td>power_psc0_disable()</td>
    <td>Disable the Power Stage Controller 0 module.</td>
  </tr>
  <tr>
    <td>power_psc1_enable()</td>
    <td>Enable the Power Stage Controller 1 module.</td>
  </tr>
  <tr>
    <td>power_psc1_disable()</td>
    <td>Disable the Power Stage Controller 1 module.</td>
  </tr>
  <tr>
    <td>power_psc2_enable()</td>
    <td>Enable the Power Stage Controller 2 module.</td>
  </tr>
  <tr>
    <td>power_psc2_disable()</td>
    <td>Disable the Power Stage Controller 2 module.</td>
  </tr>
  <tr>
    <td>power_ram0_enable()</td>
    <td>Enable the SRAM block 0 .</td>
  </tr>
  <tr>
    <td>power_ram0_disable()</td>
    <td>Disable the SRAM block 0. </td>
  </tr>
  <tr>
    <td>power_ram1_enable()</td>
    <td>Enable the SRAM block 1 .</td>
  </tr>
  <tr>
    <td>power_ram1_disable()</td>
    <td>Disable the SRAM block 1. </td>
  </tr>
  <tr>
    <td>power_ram2_enable()</td>
    <td>Enable the SRAM block 2 .</td>
  </tr>
  <tr>
    <td>power_ram2_disable()</td>
    <td>Disable the SRAM block 2. </td>
  </tr>
  <tr>
    <td>power_ram3_enable()</td>
    <td>Enable the SRAM block 3 .</td>
  </tr>
  <tr>
    <td>power_ram3_disable()</td>
    <td>Disable the SRAM block 3. </td>
  </tr>
  <tr>
    <td>power_rtc_disable()</td>
    <td>Disable the RTC module</td>
  </tr>
  <tr>
    <td>power_rtc_enable()</td>
    <td>Enable the RTC module</td>
  </tr>
  <tr>
    <td>power_spi_enable()</td>
    <td>Enable the Serial Peripheral Interface module.</td>
  </tr>
  <tr>
    <td>power_spi_disable()</td>
    <td>Disable the Serial Peripheral Interface module.</td>
  </tr>
  <tr>
    <td>power_spic_disable()</td>
    <td>Disable the SPI module on PortC</td>
  </tr>
  <tr>
    <td>power_spic_enable()</td>
    <td>Enable the SPI module on PortC</td>
  </tr>
  <tr>
    <td>power_spid_disable()</td>
    <td>Disable the SPI module on PortD</td>
  </tr>
  <tr>
    <td>power_spid_enable()</td>
    <td>Enable the SPI module on PortD</td>
  </tr>
  <tr>
    <td>power_tc0c_disable()</td>
    <td>Disable the TC0 module on PortC</td>
  </tr>
  <tr>
    <td>power_tc0c_enable()</td>
    <td>Enable the TC0 module on PortC</td>
  </tr>
  <tr>
    <td>power_tc0d_disable()</td>
    <td>Disable the TC0 module on PortD</td>
  </tr>
  <tr>
    <td>power_tc0d_enable()</td>
    <td>Enable the TC0 module on PortD</td>
  </tr>
  <tr>
    <td>power_tc0e_disable()</td>
    <td>Disable the TC0 module on PortE</td>
  </tr>
  <tr>
    <td>power_tc0e_enable()</td>
    <td>Enable the TC0 module on PortE</td>
  </tr>
  <tr>
    <td>power_tc0f_disable()</td>
    <td>Disable the TC0 module on PortF</td>
  </tr>
  <tr>
    <td>power_tc0f_enable()</td>
    <td>Enable the TC0 module on PortF</td>
  </tr>
  <tr>
    <td>power_tc1c_disable()</td>
    <td>Disable the TC1 module on PortC</td>
  </tr>
  <tr>
    <td>power_tc1c_enable()</td>
    <td>Enable the TC1 module on PortC</td>
  </tr>
  <tr>
    <td>power_twic_disable()</td>
    <td>Disable the Two Wire Interface module on PortC</td>
  </tr>
  <tr>
    <td>power_twic_enable()</td>
    <td>Enable the Two Wire Interface module on PortC</td>
  </tr>
  <tr>
    <td>power_twie_disable()</td>
    <td>Disable the Two Wire Interface module on PortE</td>
  </tr>
  <tr>
    <td>power_twie_enable()</td>
    <td>Enable the Two Wire Interface module on PortE</td>
  </tr>
  <tr>
    <td>power_timer0_enable()</td>
    <td>Enable the Timer 0 module.</td>
  </tr>
  <tr>
    <td>power_timer0_disable()</td>
    <td>Disable the Timer 0 module.</td>
  </tr>
  <tr>
    <td>power_timer1_enable()</td>
    <td>Enable the Timer 1 module.</td>
  </tr>
  <tr>
    <td>power_timer1_disable()</td>
    <td>Disable the Timer 1 module.</td>
  </tr>
  <tr>
    <td>power_timer2_enable()</td>
    <td>Enable the Timer 2 module.</td>
  </tr>
  <tr>
    <td>power_timer2_disable()</td>
    <td>Disable the Timer 2 module.</td>
  </tr>
  <tr>
    <td>power_timer3_enable()</td>
    <td>Enable the Timer 3 module.</td>
  </tr>
  <tr>
    <td>power_timer3_disable()</td>
    <td>Disable the Timer 3 module.</td>
  </tr>
  <tr>
    <td>power_timer4_enable()</td>
    <td>Enable the Timer 4 module.</td>
  </tr>
  <tr>
    <td>power_timer4_disable()</td>
    <td>Disable the Timer 4 module.</td>
  </tr>
  <tr>
    <td>power_timer5_enable()</td>
    <td>Enable the Timer 5 module.</td>
  </tr>
  <tr>
    <td>power_timer5_disable()</td>
    <td>Disable the Timer 5 module.</td>
  </tr>
  <tr>
    <td>power_twi_enable()</td>
    <td>Enable the Two Wire Interface module.</td>
  </tr>
  <tr>
    <td>power_twi_disable()</td>
    <td>Disable the Two Wire Interface module.</td>
  </tr>
  <tr>
    <td>power_usart_enable()</td>
    <td>Enable the USART module.</td>
  </tr>
  <tr>
    <td>power_usart_disable()</td>
    <td>Disable the USART module.</td>
  </tr>
  <tr>
    <td>power_usart0_enable()</td>
    <td>Enable the USART 0 module.</td>
  </tr>
  <tr>
    <td>power_usart0_disable()</td>
    <td>Disable the USART 0 module.</td>
  </tr>
  <tr>
    <td>power_usart1_enable()</td>
    <td>Enable the USART 1 module.</td>
  </tr>
  <tr>
    <td>power_usart1_disable()</td>
    <td>Disable the USART 1 module.</td>
  </tr>
  <tr>
    <td>power_usart2_enable()</td>
    <td>Enable the USART 2 module.</td>
  </tr>
  <tr>
    <td>power_usart2_disable()</td>
    <td>Disable the USART 2 module.</td>
  </tr>
  <tr>
    <td>power_usart3_enable()</td>
    <td>Enable the USART 3 module.</td>
  </tr>
  <tr>
    <td>power_usart3_disable()</td>
    <td>Disable the USART 3 module.</td>
  </tr>
  <tr>
    <td>power_usartc0_disable()</td>
    <td> Disable the USART0 module on PortC</td>
  </tr>
  <tr>
    <td>power_usartc0_enable()</td>
    <td> Enable the USART0 module on PortC</td>
  </tr>
  <tr>
    <td>power_usartd0_disable()</td>
    <td> Disable the USART0 module on PortD</td>
  </tr>
  <tr>
    <td>power_usartd0_enable()</td>
    <td> Enable the USART0 module on PortD</td>
  </tr>
  <tr>
    <td>power_usarte0_disable()</td>
    <td> Disable the USART0 module on PortE</td>
  </tr>
  <tr>
    <td>power_usarte0_enable()</td>
    <td> Enable the USART0 module on PortE</td>
  </tr>
  <tr>
    <td>power_usartf0_disable()</td>
    <td> Disable the USART0 module on PortF</td>
  </tr>
  <tr>
    <td>power_usartf0_enable()</td>
    <td> Enable the USART0 module on PortF</td>
  </tr>
  <tr>
    <td>power_usb_enable()</td>
    <td>Enable the USB module.</td>
  </tr>
  <tr>
    <td>power_usb_disable()</td>
    <td>Disable the USB module.</td>
  </tr>
  <tr>
    <td>power_usi_enable()</td>
    <td>Enable the Universal Serial Interface module.</td>
  </tr>
  <tr>
    <td>power_usi_disable()</td>
    <td>Disable the Universal Serial Interface module.</td>
  </tr>
  <tr>
    <td>power_vadc_enable()</td>
    <td>Enable the Voltage ADC module.</td>
  </tr>
  <tr>
    <td>power_vadc_disable()</td>
    <td>Disable the Voltage ADC module.</td>
  </tr>
  <tr>
    <td>power_all_enable()</td>
    <td>Enable all modules.</td>
  </tr>
  <tr>
    <td>power_all_disable()</td>
    <td>Disable all modules.</td>
  </tr>
</table>
</center>
</small>
@} */
static __inline void
__attribute__ ((__always_inline__))
__power_all_enable()
{
}
static __inline void
__attribute__ ((__always_inline__))
__power_all_disable()
{
}
/* Copyright (c) 2002, 2004 Theodore A. Roth
   Copyright (c) 2004, 2007, 2008 Eric B. Weddington
   Copyright (c) 2005, 2006, 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/** \file */
/** \defgroup avr_sleep <avr/sleep.h>: Power Management and Sleep Modes
    \code #include <avr/sleep.h>\endcode
    Use of the \c SLEEP instruction can allow an application to reduce its
    power comsumption considerably. AVR devices can be put into different
    sleep modes. Refer to the datasheet for the details relating to the device
    you are using.
    There are several macros provided in this header file to actually
    put the device into sleep mode.  The simplest way is to optionally
    set the desired sleep mode using \c set_sleep_mode() (it usually
    defaults to idle mode where the CPU is put on sleep but all
    peripheral clocks are still running), and then call
    \c sleep_mode(). This macro automatically sets the sleep enable bit, goes 
    to sleep, and clears the sleep enable bit.
    
    Example:
    \code
    #include <avr/sleep.h>
    ...
      set_sleep_mode(<mode>);
      sleep_mode();
    \endcode
    
    Note that unless your purpose is to completely lock the CPU (until a 
    hardware reset), interrupts need to be enabled before going to sleep.
    As the \c sleep_mode() macro might cause race conditions in some
    situations, the individual steps of manipulating the sleep enable
    (SE) bit, and actually issuing the \c SLEEP instruction, are provided
    in the macros \c sleep_enable(), \c sleep_disable(), and
    \c sleep_cpu().  This also allows for test-and-sleep scenarios that
    take care of not missing the interrupt that will awake the device
    from sleep.
    Example:
    \code
    #include <avr/interrupt.h>
    #include <avr/sleep.h>
    ...
      set_sleep_mode(<mode>);
      cli();
      if (some_condition)
      {
        sleep_enable();
        sei();
        sleep_cpu();
        sleep_disable();
      }
      sei();
    \endcode
    This sequence ensures an atomic test of \c some_condition with
    interrupts being disabled.  If the condition is met, sleep mode
    will be prepared, and the \c SLEEP instruction will be scheduled
    immediately after an \c SEI instruction.  As the intruction right
    after the \c SEI is guaranteed to be executed before an interrupt
    could trigger, it is sure the device will really be put to sleep.
    Some devices have the ability to disable the Brown Out Detector (BOD) before 
    going to sleep. This will also reduce power while sleeping. If the
    specific AVR device has this ability then an additional macro is defined:
    \c sleep_bod_disable(). This macro generates inlined assembly code
    that will correctly implement the timed sequence for disabling the BOD
    before sleeping. However, there is a limited number of cycles after the
    BOD has been disabled that the device can be put into sleep mode, otherwise
    the BOD will not truly be disabled. Recommended practice is to disable
    the BOD (\c sleep_bod_disable()), set the interrupts (\c sei()), and then
    put the device to sleep (\c sleep_cpu()), like so:
    \code
    #include <avr/interrupt.h>
    #include <avr/sleep.h>
    ...
      set_sleep_mode(<mode>);
      cli();
      if (some_condition)
      {
        sleep_enable();
        sleep_bod_disable();
        sei();
        sleep_cpu();
        sleep_disable();
      }
      sei();
    \endcode
*/
/* Define an internal sleep control register and an internal sleep enable bit mask. */
    /* New xmega devices */
/* Special casing these three devices - they are the
   only ones that need to write to more than one register. */
/* For everything else, check for presence of SM<n> and define set_sleep_mode accordingly. */
/** \ingroup avr_sleep
    Put the device in sleep mode. How the device is brought out of sleep mode
    depends on the specific mode selected with the set_sleep_mode() function.
    See the data sheet for your device for more details. */
/** \ingroup avr_sleep
    Put the device into sleep mode.  The SE bit must be set
    beforehand, and it is recommended to clear it afterwards.
*/
/*@}*/
/* Copyright (c) 2002, 2004 Marek Michalkiewicz
   Copyright (c) 2005, 2006, 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/*
   avr/wdt.h - macros for AVR watchdog timer
 */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/** \file */
/** \defgroup avr_watchdog <avr/wdt.h>: Watchdog timer handling
    \code #include <avr/wdt.h> \endcode
    This header file declares the interface to some inline macros
    handling the watchdog timer present in many AVR devices.  In order
    to prevent the watchdog timer configuration from being
    accidentally altered by a crashing application, a special timed
    sequence is required in order to change it.  The macros within
    this header file handle the required sequence automatically
    before changing any value.  Interrupts will be disabled during
    the manipulation.
    \note Depending on the fuse configuration of the particular
    device, further restrictions might apply, in particular it might
    be disallowed to turn off the watchdog timer.
    Note that for newer devices (ATmega88 and newer, effectively any
    AVR that has the option to also generate interrupts), the watchdog
    timer remains active even after a system reset (except a power-on
    condition), using the fastest prescaler value (approximately 15
    ms).  It is therefore required to turn off the watchdog early
    during program startup, the datasheet recommends a sequence like
    the following:
    \code
    #include <stdint.h>
    #include <avr/wdt.h>
    uint8_t mcusr_mirror __attribute__ ((section (".noinit")));
    void get_mcusr(void)       __attribute__((naked))       __attribute__((section(".init3")));
));
    void get_mcusr(void)
    {
      mcusr_mirror = MCUSR;
      MCUSR = 0;
      wdt_disable();
    }
    \endcode
    Saving the value of MCUSR in \c mcusr_mirror is only needed if the
    application later wants to examine the reset source, but in particular, 
    clearing the watchdog reset flag before disabling the
    watchdog is required, according to the datasheet.
*/
/**
   \ingroup avr_watchdog
   Reset the watchdog timer.  When the watchdog timer is enabled,
   a call to this instruction is required before the timer expires,
   otherwise a watchdog-initiated device reset will occur. 
*/
/**
   \ingroup avr_watchdog
   Enable the watchdog timer, configuring it for expiry after
   \c timeout (which is a combination of the \c WDP0 through
   \c WDP2 bits to write into the \c WDTCR register; For those devices 
   that have a \c WDTCSR register, it uses the combination of the \c WDP0 
   through \c WDP3 bits).
   See also the symbolic constants \c WDTO_15MS et al.
*/
/**
   \ingroup avr_watchdog
   Symbolic constants for the watchdog timeout.  Since the watchdog
   timer is based on a free-running RC oscillator, the times are
   approximate only and apply to a supply voltage of 5 V.  At lower
   supply voltages, the times will increase.  For older devices, the
   times will be as large as three times when operating at Vcc = 3 V,
   while the newer devices (e. g. ATmega128, ATmega8) only experience
   a negligible change.
   Possible timeout values are: 15 ms, 30 ms, 60 ms, 120 ms, 250 ms,
   500 ms, 1 s, 2 s.  (Some devices also allow for 4 s and 8 s.)
   Symbolic constants are formed by the prefix
   \c WDTO_, followed by the time.
   Example that would select a watchdog timer expiry of approximately
   500 ms:
   \code
   wdt_enable(WDTO_500MS);
   \endcode
*/
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
/** \ingroup avr_watchdog
    See \c WDTO_15MS */
// for consistency, ROM_SIZE + EEPROM_SIZE
// tk.h : misc handy stuff
// Copyright (C) 2015-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/////
// tk.h
// misc tricks which need to be available before other includes,
// but which don't need to be repeated in every source file
////
// AVR GCC has no boolean type by default
// (this isn't native bool, but it's mostly okay)
// create a way to include files defined at the command line,
// like with "gcc -DCONFIGFILE=foo.h"
// use it like this:
//#include incfile(CONFIGFILE)
// cause a build failure if `condition` is true
// (gcc compile trick taken from an old version of include/linux/kernel.h)
// more info here:
// https://scaryreasoner.wordpress.com/2009/02/28/checking-sizeof-at-compile-time/
// cause a build failure if `condition` is false
// arch/attiny1616.h: attiny1616 support header
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// FIXME: remove this
////////// clock speed / delay stuff //////////
inline void mcu_clock_speed();
///// clock dividers
// this should work, but needs further validation
inline void clock_prescale_set(uint8_t n);
// TODO: allow hwdef to define a base clock speed,
//       and adjust these values accordingly
typedef enum
{
    // Actual clock is 20 MHz, but assume that 10 MHz is the top speed and work from there
    // TODO: measure PWM speed and power use at 1.25/2.5/5/10 MHz, to determine which speeds are optimal
    clock_div_1 = (CLKCTRL_PDIV_2X_gc | 
                                          0x01
                                                        ), // 10 MHz
    clock_div_2 = (CLKCTRL_PDIV_4X_gc | 
                                          0x01
                                                        ), // 5 MHz
    clock_div_4 = (CLKCTRL_PDIV_8X_gc | 
                                          0x01
                                                        ), // 2.5 MHz
    clock_div_8 = (CLKCTRL_PDIV_16X_gc | 
                                          0x01
                                                        ), // 1.25 MHz
    clock_div_16 = (CLKCTRL_PDIV_32X_gc | 
                                          0x01
                                                        ), // 625 kHz
    clock_div_32 = (CLKCTRL_PDIV_64X_gc | 
                                          0x01
                                                        ), // 312 kHz, max without changing to the 32 kHz ULP
    clock_div_64 = (CLKCTRL_PDIV_64X_gc | 
                                          0x01
                                                        ), // 312 kHz
    clock_div_128 = (CLKCTRL_PDIV_64X_gc | 
                                          0x01
                                                        ), // 312 kHz
    clock_div_256 = (CLKCTRL_PDIV_64X_gc | 
                                          0x01
                                                        ) // 312 kHz
} clock_div_t;
////////// DAC controls //////////
// set only the relevant bits of the Vref register
// Vref values
// (for the DAC bits, not the ADC bits)
////////// ADC voltage / temperature //////////
// set only the relevant bits of the Vref register
inline void mcu_set_admux_therm();
inline void mcu_set_admux_voltage();
inline void mcu_adc_sleep_mode();
inline void mcu_adc_start_measurement();
//inline void mcu_adc_on();
inline void mcu_adc_off();
inline void mcu_adc_vect_clear();
//// both readings are left-aligned
//inline uint16_t mcu_adc_result();
// read ADC differently for temperature and voltage
inline uint16_t mcu_adc_result_temp();
inline uint16_t mcu_adc_result_volts();
// return Volts * 50, range 0 to 5.10V
inline uint8_t mcu_vdd_raw2cooked(uint16_t measurement);
inline uint8_t mcu_vdivider_raw2cooked(uint16_t measurement);
// return (temp in Kelvin << 6)
inline uint16_t mcu_temp_raw2cooked(uint16_t measurement);
inline uint8_t mcu_adc_lsb();
////////// WDT //////////
inline void mcu_wdt_active();
inline void mcu_wdt_standby();
inline void mcu_wdt_stop();
// *** Note for the AVRXMEGA3 (1-Series, eg 816 and 817), the WDT 
// is not used for time-based interrupts.  A new peripheral, the 
// Periodic Interrupt Timer ("PIT") is used for this purpose.
inline void mcu_wdt_vect_clear();
////////// PCINT - pin change interrupt (e-switch) //////////
// set these in hwdef
//#define SWITCH_PORT  PINA
//#define SWITCH_VECT  PCINT0_vect
inline void mcu_switch_vect_clear();
inline void mcu_pcint_on();
inline void mcu_pcint_off();
////////// misc //////////
void reboot();
inline void prevent_reboot_loop();
/********* User-configurable options *********/
// config-default.h: Default configuration for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/*
 * This file specifies the default settings for Anduril.
 *
 * These settings can be overridden per build target, in cfg-*.h files...
 * ... but most are not.  So changing one here will make it change in
 * almost every build target.
 *
 * Some configurable settings are also in other *.h files.
 */
/********* User-configurable options *********/
// low voltage protection (also required for battery check mode)
// overheat protection
// more accurate temperature sensor can regulate higher safely
// Comment out to disable automatic calibration on factory reset
//   - If so, be sure to set THERM_CAL_OFFSET to the correct calibration offset
//   - Calibration can still be overridden in temperature check mode
// Or uncomment to use the default auto-calibrate on factory reset
//
// To determine THERM_CAL_OFFSET, comment out USE_THERM_AUTOCALIBRATE to
// disable auto-calibration, compile and flash, let flashlight rest at a known
// temperature, then enter temp check mode (do NOT enter calibration mode).
//
// THERM_CAL_OFFSET = known_temperature - temp_check_blinks + THERM_CAL_OFFSET
//
// (include THERM_CAL_OFFSET in sum as it might already be a non-zero number)
// Include a simplified UI for non-enthusiasts?
///// Ramp mode options /////
// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
// default ramp style: 0 = smooth, 1 = stepped
// smooth ramp speed: 1, 2, 3, 4, ...  for 1X speed, 1/2, 1/3rd, 1/4th, ...
// after ramping, how long until the direction resets to "up"?
// add runtime option for whether hold-from-off should ramp or stay at moon
// short blip when crossing from "click" to "hold" from off
// (helps the user hit moon mode exactly, instead of holding too long
//  or too short)
// short blips while ramping
//#define BLINK_AT_RAMP_FLOOR
//#define BLINK_AT_STEPS  // whenever a discrete ramp mode is passed in smooth mode
// Uncomment for Anduril1 "Ramp 2C" behavior:
//   - Ramp 2C goes to turbo (advanced UI) or ceiling (simple UI), like in Anduril1
// Or comment out to use Anduril2 behavior instead:
//   - Ramp 2C goes to ceiling, unless already at ceiling or in simple UI.
//     (Advanced UI ceiling 2C goes to turbo)
//#define USE_2C_MAX_TURBO
// Or uncomment to let the user decide which style they want:
// 0 = no turbo
// 1 = A1 style: Off 2C = ceil, On 2C = turbo
// 2 = A2 style: Off 2C = ceil, On 2C = ceil, Ramped ceil 2C = turbo
// All styles allow momentary turbo in advanced UI
//#define DEFAULT_2C_STYLE 2  // default to Anduril 2 style
//#define DEFAULT_2C_STYLE_SIMPLE 0  // no turbo at all
// make the ramps configurable by the user
// adds a runtime option to switch between automatic memory (default)
// and manual memory (only available if compiled in)
// (manual memory makes 1-click-from-off start at the same level each time)
// (the level can be set explicitly with 10 clicks from on,
// or the user can go back to automatic with 10H)
// if enabled, user can use "hybrid memory"
// The light will use automatic or manual memory level, depending on how long
// the light was off.  Short off = automatic, long off = manual.
// This also remaps 10C/10H:
// - 10C toggles manual mem on/off at current level.
// - 10H configures the timer value.
// enable sunset timer (ramp-down and automatic shutoff)
// timer is available in regular ramp mode and candle mode
// optionally make gradual ticks happen faster
// Affects: thermal regulation speed, sunset mode, maybe other features
// (default is calibrated for 8-bit PWM,
//  but 10-bit should set this value to 4 instead of 1)
///// What to do when power is connected /////
// factory reset function erases user's runtime configuration in eeprom
//#define USE_SOFT_FACTORY_RESET  // only needed on models which can't use hold-button-at-boot
// dual-switch support (second switch is a tail clicky)
// (currently incompatible with factory reset)
//#define START_AT_MEMORIZED_LEVEL
///// extra modes (enable / disable / configure each mode) /////
// include a function to blink out the firmware version
// enable the battery check mode (shows remaining charge) (requires USE_LVP)
// battery readout style (pick one)
// TODO: allow VpT and 4-bar simultaneously,
//       so one can be in "simple mode" and the other in "advanced mode"
//#define BATTCHECK_8bars  // FIXME: breaks build
//#define BATTCHECK_4bars  // FIXME: breaks build
    // battcheck displays 1.25V instead of 1.2V
// allow the user to calibrate the voltage readings?
// (adjust in 0.05V increments from -0.30V to +0.30V)
// (1 = -0.30V, 2 = -0.25V, ... 7 = 0V, ... 13 = +0.30V)
// enable beacon mode
// enable/disable various strobe modes
// boring strobes nobody really likes, but sometimes flashlight companies want
// (these replace the fun strobe group,
//  so don't enable them at the same time as any of the above strobes)
//#define USE_POLICE_STROBE_MODE
//#define USE_SOS_MODE_IN_FF_GROUP  // put SOS in the "boring strobes" mode
// enable a mode for locking the light for safe carry
// should lockout mode function as a momentary moon mode?
// add an optional setting to lock the light after being off for a while
// enable momentary mode
// enable tactical mode
// enable a shortcut for +10 in number entry mode
// (click for +1, hold for +10)
// cut clock speed at very low modes for better efficiency
// (defined here so config files can override it)
// if the aux LEDs oscillate between "full battery" and "empty battery"
// while in "voltage" mode, enable this to reduce the amplitude of
// those oscillations
// if there's tint ramping, allow user to set it smooth or stepped
// Use "smooth steps" to soften on/off and step changes
// on MCUs with enough room for extra stuff like this
// 0 = none, 1 = smooth, 2+ = undefined
// by default, allow user to set the channel for each strobe-group mode
// (but allow disabling this feature per build)
/////////////////////////////////////////////////////////////
///   FOR SOFIRN UNITS THIS OPTIONS IS SUPPLEMENTED WITH
///   THE "/sofirn/anduril.h" FILE 
/********* ADDITIONAL User-configurable options *********/
///   2025-01-09 21:15:08
///   Rather than adding fav mods to every single
///   "anduril.h"  file, let's make an additional
///   "config-default" and put those fav mods in one place. 
///      #include "anduril/config-default-mods.h"
///   ADDITIONAL : 
///      "/sofirn/anduril.h"
/////////////////////////////////////////////////////////////
/********* specific settings for known driver types *********/
/// wurkkos-ts25/anduril.h  
// Wurkkos TS25, modelled after the TS10 but with RGB Aux
// Copyright (C) 2022-2023 (FIXME)
// SPDX-License-Identifier: GPL-3.0-or-later
       
/// //#include "wurkkos/ts25/hwdef.h"
/// #define HWDEF_H  wurkkos/ts25/hwdef.h
// Wurkkos TS25 driver layout
// Copyright (C) 2022-2023 (FIXME)
// SPDX-License-Identifier: GPL-3.0-or-later
       
/*  /// 
 */
/*  /// Driver layout
 * 
 * Driver pinout:
 * eSwitch:    PA5
 * PWM FET:    PB0 (TCA0 WO0)
 * PWM 1x7135: PB1 (TCA0 WO1)
 * Voltage:    VCC
 * Aux Red:    PC2
 * Aux Green:  PC3
 * Aux Blue:   PC1
 * 
 */
// allow using aux LEDs as extra channel modes
// channel modes for RGB aux LEDs
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// include / exclude field based on compile options
void set_level_auxred(uint8_t level);
void set_level_auxyel(uint8_t level);
void set_level_auxgrn(uint8_t level);
void set_level_auxcyn(uint8_t level);
void set_level_auxblu(uint8_t level);
void set_level_auxprp(uint8_t level);
void set_level_auxwht(uint8_t level);
uint8_t gradual_tick_null(uint8_t gt);
// channel modes:
// * 0. FET+7135 stacked
// * 1+. aux RGB
enum CHANNEL_MODES {
    CM_MAIN = 0,
    CM_AUXRED, CM_AUXYEL, CM_AUXGRN, CM_AUXCYN, CM_AUXBLU, CM_AUXPRP, CM_AUXWHT
};
// right-most bit first, modes are in fedcba9876543210 order
// PWM parameters of both channels are tied together because they share a counter
// not necessary when double-buffered "BUF" registers are used
// 1x7135 channel
// DD FET channel
// e-switch
// average drop across diode on this hardware
// this driver allows for aux LEDs under the optic
// this light has three aux LED channels: R, G, B
inline void hwdef_setup() {
    // set up the system clock to run at 10 MHz instead of the default 3.33 MHz
    
   __asm__ __volatile__("out %[ccp], %[ccp_ioreg]" "\n\t" "sts %[ioreg], %[val]" : : [ccp] "I" ((((uint16_t) &((*(volatile uint8_t *)(0x0034)))) - 0x00)), [ccp_ioreg] "d" ((uint8_t)CCP_IOREG_gc), [ioreg] "n" (((uint16_t) &((*(CLKCTRL_t *) 0x0060)
   .MCLKCTRLB
   ))), [val] "r" ((uint8_t)
   CLKCTRL_PDIV_2X_gc | 
   0x01))
                                                           
                                                          ;
    //VPORTA.DIR = ...;
    // Outputs: PWMs
    
   (*(VPORT_t *) 0x0004)
         .DIR = 
                0x01
               
              | 
                0x02
                       ;
    // RGB aux LEDs
    
   (*(VPORT_t *) 0x0008)
         .DIR = 
                0x02
               
              | 
                0x04
               
              | 
                0x08
                       ;
    // enable pullups on the unused pins to reduce power
    
   (*(PORT_t *) 0x0400)
        .PIN0CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0400)
        .PIN1CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0400)
        .PIN2CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0400)
        .PIN3CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0400)
        .PIN4CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0400)
        .PIN5CTRL = 
                    0x08 
                                     | PORT_ISC_BOTHEDGES_gc; // eSwitch
    
   (*(PORT_t *) 0x0400)
        .PIN6CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0400)
        .PIN7CTRL = 
                    0x08
                                    ;
    //PORTB.PIN0CTRL = PORT_PULLUPEN_bm; // FET channel
    //PORTB.PIN1CTRL = PORT_PULLUPEN_bm; // 7135 channel
    
   (*(PORT_t *) 0x0420)
        .PIN2CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0420)
        .PIN3CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0420)
        .PIN4CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0420)
        .PIN5CTRL = 
                    0x08
                                    ;
    
   (*(PORT_t *) 0x0440)
        .PIN0CTRL = 
                    0x08
                                    ;
    //PORTC.PIN1CTRL = PORT_PULLUPEN_bm; // RGB Aux
    //PORTC.PIN2CTRL = PORT_PULLUPEN_bm; // RGB Aux
    //PORTC.PIN3CTRL = PORT_PULLUPEN_bm; // RGB Aux
    // set up the PWM
    // https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny1614-16-17-DataSheet-DS40002204A.pdf
    // PB0 is TCA0:WO0, use TCA_SINGLE_CMP0EN_bm
    // PB1 is TCA0:WO1, use TCA_SINGLE_CMP1EN_bm
    // PB2 is TCA0:WO2, use TCA_SINGLE_CMP2EN_bm
    // For Fast (Single Slope) PWM use TCA_SINGLE_WGMODE_SINGLESLOPE_gc
    // For Phase Correct (Dual Slope) PWM use TCA_SINGLE_WGMODE_DSBOTTOM_gc
    // See the manual for other pins, clocks, configs, portmux, etc
    
   (*(TCA_t *) 0x0A00)
       .SINGLE.CTRLB = 
                       0x10
                      
                     | 
                       0x20
                      
                     | TCA_SINGLE_WGMODE_DSBOTTOM_gc;
    
   (*(TCA_t *) 0x0A00)
       .SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc
                      | 
                       0x01
                                           ;
    
   (*(TCA_t *) 0x0A00)
   .SINGLE.PERBUF = 255;
}
/// wurkkos/anduril.h 
/// fav config for all Wurkkos units
/// OG Wurkkos' anduril.h ,  plus tons of edits 
// Wurkkos config options for Anduril
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/*  /// OG Wurkkos' anduril.h 
// Wurkkos config options for Anduril
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
// allow Aux Config and Strobe Modes in Simple UI
// Allow 3C in Simple UI for switching between smooth and stepped ramping
// enable 2 click turbo (Anduril 1 style)
// enable SOS in the blinkies group
// enable factory reset on 13H without loosening tailcap
// only really needed on TS10, but doesn't hurt on other models
// higher temperature limit because attiny1616 is more accurate
 */
/*  /// 
 */
/*  /// USE_SIMPLE_UI, etc. etc. 
/// "USE_SIMPLE_UI" is defined in the  "anduril/config-default.h" 
// Include a simplified UI for non-enthusiasts?"
/// from "wurkkos/anduril.h" : 
// allow Aux Config and Strobe Modes in Simple UI 
// Allow 3C in Simple UI for switching between smooth and stepped ramping  
 */
/*  /// don't default to Simple UI 
/// from old "cfg-0631-sp10p-071.h" 
 */
/*  /// USE_SOFT_FACTORY_RESET 
/// "USE_FACTORY_RESET" is defined in the  "anduril/config-default.h" . 
/// "SOFT FACTORY RESET" : 
/// OFF, 13H = factory reset without loosening tailcap
/// only really needed on TS10, but doesn't hurt on other models
 */
/*  /// DEFAULT_2C_STYLE  2C = turbo
/// 0 = no turbo
/// 1 = A1 style: Off 2C = ceil, On 2C = turbo
/// 2 = A2 style: Off 2C = ceil, On 2C = ceil,
///                     Ramped ceil 2C = turbo 
/// in the user manual this setting is a part of 
/// Ramp Extra Config.
/// ON, 10H = Ramp Extra Config
 */
/*  /// set the default ramp style to Stepped 
/// from "sp10-pro/anduril.h" :
// ... set the default ramp style to Stepped
/// ramp style can be changed at runtime,
/// ON, 3C  or  ON, 6C 
 */
/*  /// undef BLINK_AT_RAMP
/// (The OG default is in the "anduril/config-default.h") 
/// from "sp10-pro/anduril.h" :
// don't blink during the ramp or at the ceiling
///   from old cfg file of sc21-pro:  
///    "don't blink during the ramp or at the ceiling" 
///   (The OG default is in the  "anduril/config-default.h") 
///   from OG blf-q8-t1616/anduril.h:
// don't blink during the ramp; the button LED brightness is sufficient
// to indicate which power channel(s) are being used
 */
/*  /// AUTO_REVERSE_TIME = 1 
/// AUTO_REVERSE_TIME timed out in 1 tick
/// effect: 1H= ramp up, no AUTO_REVERSE to ramp down. 2H= ramp down
 */
/*  /// MANUAL_MEMORY, MANUAL_MEMORY_TIMER, DEFAULT_MANUAL_MEMORY 
/// "USE_MANUAL_MEMORY"  and  "USE_MANUAL_MEMORY_TIMER" are
/// defined in the  "anduril/config-default.h" : 
/// The DEFAULT brightness LEVEL  is set individually in each 
    flashlight's "anduril.h" file, e.g.: 
/// "anduril/ramp-mode.c", "USE_MANUAL_MEMORY" : 
// turn on manual memory and save current brightness
/// Mod., use 5C instead of 10C
/// correlated mod. in "anduril/ramp-mode.c" : 
 ... (event == EV_5clicks) 
/// ALWAYS use MANUAL_MEMORY : 
 */
/*  /// SIMPLE BATTCHECK MODE 
/// config-default.h : 
    // battcheck displays 1.25V instead of 1.2V
    #define USE_EXTRA_BATTCHECK_DIGIT
/// SIMPLE BATTCHECK MODE, no extra digit : 
 */
/*  /// DISABLE POVD 
/// DISABLE POVD ? 
/// battcheck-mode-fsm.h:  
// battcheck-mode-fsm.h: FSM config for battery check mode in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
    // show voltage colors for a few seconds after going to standby
    #define USE_POST_OFF_VOLTAGE
    #ifndef DEFAULT_POST_OFF_VOLTAGE_SECONDS
        #define DEFAULT_POST_OFF_VOLTAGE_SECONDS  4
    #endif
=====   =====   =====   =====   =====   =====   =====
/// tested on TS25: NOT WORK? POVD still active? Why this doesn't work? Maybe it should be moved to target config file, after "#define USE_AUX_RGB_LEDS". Maybe? Maybe not ..
=====   =====   =====   =====   =====   =====   =====
/// a potential correction :
/// yup, I think that's gonna work, to disable POVD 
/// yup, 2025.02.01 tested on TS25: OK, no more POVD 
 */
/*  /// 
 */
/*  /// BLINKIES AND STROBES 
=====   =====   =====   =====   =====
/// ToyKeeper  "anduril/config-default.h" : 
// enable beacon mode
// enable various strobe modes
=====   =====   =====   =====   =====
/// starryalley  "anduril/config-default.h" :
// enable beacon mode
// enable various strobe modes
=====   =====   =====   =====   =====
/// ts25/anduril.h:
// use aux red + aux blue for police strobe
=====   =====   =====   =====   =====
///   ENABLE ADDITIONAL STROBE MODES
/// strobe modes can be disabled in each build target, 
/// as needed/preferred 
 */
/// ENABLE ADDITIONAL STROBES
/*  /// USE_TACTICAL_MODE, DISABLE MOMENTARY_MODE 
/// DISABLE MOMENTARY_MODE 
/// TACTICAL_MODE is defined in the "anduril/config-default.h" : 
// enable tactical mode
/// DISABLE TACTICAL_MODE ? 
 */
/*  /// Wurkkos DEFAULT_THERMAL_CEILING 50 
/// all wurkkos anduril units use attiny1616  
// higher temperature limit because attiny1616 is more accurate
 */
/*  /// AUTOLOCK 
/// config-default.h  Line 178 
// add an optional setting to lock the light after being off for a while
 */
/// FIXME: FIXED: move this config to each build target, adjust per each build target.
/// DO NOT ENABLE THIS CONFIG IN THIS GLOBAL CONFIG FILE
/*  /// INDICATOR_LED, EXTENDED_INDICATOR_PATTERNS, etc. 
=====   =====   =====   =====   =====
/// 2025.01.28.  
/// targets with rgb LEDS:  "ERROR: build failed" 
/// this line dont work as a global config,
/// this must be applied only for the compatible target,
///  i.e. : ts10, ts21  
=====   =====   =====   =====   =====
/// DO NOT ENABLE THIS CONFIG IN THIS GLOBAL CONFIG FILE,  ERROR for aux RGB targets :
// #define USE_INDICATOR_LED
/// THIS ONE SEEMS OK BUT IT'S BETTER TO BE APPLIED PER BUILD TARGEET, NOT GLOBALLY :
// #define USE_INDICATOR_LED_WHILE_RAMPING
=====   =====   =====   =====   =====
/// in the "aux-leds.h" : 
  . "USE_INDICATOR_LED" 
    "USE_INDICATOR_LED_WHILE_RAMPING" 
    "INDICATOR_LED_DEFAULT_MODE" . . . 
=====   =====   =====   =====   =====
/// targets with rgb LEDS have different config:
/// OG Wurkkos TS25 anduril.h:     /// RGB-AUX in the front 
// Wurkkos TS25, modelled after the TS10 but with RGB Aux
// this light has three aux LED channels: R, G, B
// don't turn on the aux LEDs while main LEDs are on
/// OG Wurkkos TS10-RGB-AUX anduril.h:     /// RGB-AUX in th front 
// Wurkkos TS10 (RGB aux version) config options for Anduril
// most things are the same as TS25
// this light has three aux LED channels: R, G, B
// don't turn on the aux LEDs while main LEDs are on
// OG Wurkkos TS11 anduril.h: 
// Wurkkos TS11, like a TS25  but with a RGB button and RGB front aux
// this light has three aux LED channels: R, G, B
// turn on the aux LEDs while main LEDs are on
// (but not until the main LEDs are bright enough to overpower the aux)
// (setting this lower makes an annoying effect on some levels)
/// OG Wurkkos FC13 anduril.h: 
// Wurkkos FC13, like a TS25 but with a RGB button and no front aux
// this light has three aux LED channels: R, G, B
// turn on the aux LEDs while main LEDs are on
=====   =====   =====   =====   =====
for target with single aux led, e.g. sigle color button LED, 
 e.g.: sc31-pro, ts10, ts21  :
for target with three aux LED channels: R, G, B, 
 e.g.: FC13, TS10-RGBAUX, TS25:
=====   =====   =====   =====   =====
=====   =====   =====   =====   =====
=====   =====   =====   =====   =====
/// EXTENDED_INDICATOR_PATTERNS
/// NEW MOD. more-aux-patterns. by SammysHP
/// "Works for classic and RGB aux LEDs."
/// using replacement files from SammysHP : 
/// "anduril/aux-leds.c"  and  "anduril/aux-leds.h" ,
/// also  "off-mode.c"  and  "lockout-mode.c" ! 
/// PATTERNS:
    // low nibble:  off state
    // high nibble: lockout state
    // modes are:
    //   0=off
    //   1=low
    //   2=high
    //   3=fancy blinking
    //   4=low blinking
    //   5=high blinking 
/// LOCKOUT: low (1) .  OFF-MODE: low blinking (4) 
 */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
/*  /// 
 */
/// wurkkos/anduril.h 
///   END   
/*  /// 
 */
/*  /// RAMP_SIZE, PWM_LEVELS
/// position this RAMP_SIZE and PWM_LEVELS etc. at the top of this config file ...
/// this is kinda fixed config, not customisable 
 */
/*  /// 
 */
// 7135 at 75/150
// level_calc.py 5.7895 2 150 7135 1 0.1 130 FET 1 10 3000 --pwm dyn:74:4096:255:3
// (with some manual tweaks)
// non-zero part of FET channel calculated with:
//   level_calc.py 3 1 75 7135 1 200 3000
//   (FIXME? there's a visible bump when the FET kicks in, even with just 1/255)
/*  /// TS25 STEPPED RAMP FLOOR, CEIL, STEPS 
/// OG blf-q8-t1616/anduril.h: 
// 20 38 56 [75] 93 111 130
/// OG ts25/anduril.h: 
// 20 38 56 [75] 93 111 130
/// CALC_INTERVAL = (ceiling - floor) / (steps - 1) 
/// calc and/or tested: 
///   STEPPED RAMP FLOOR, CEIL, STEPS 
///   1  38  75  112   
///   1  38  75  112   149 
///   1  42  83  124 
///   1  43  85  127 
///   1  44  87  130 
///   1  45  89  133 
/// 5 steps : 
///   1  34  67  100  133 
///   1  33  65  97   129 
///   1  32  63  94   125 
///   1  31  61  91   121 
 */
///   1  31  61  91   121 
/*  /// TS25 SMOOTH RAMP FLOOR AND CEIL 
/// OG ts25/anduril.h: 
 */
/*  /// TS25 Simple UI FLOOR, CEIL, STEPS 
/// OG ts25/anduril.h: 
// at Wurkkos's request, reduce the Simple UI ceiling a little bit
// 25 50 [75] 100 125
/// 
 */
/// SIMPLE_UI is disabled
/*  /// 
 */
/*  /// 
 */
/*  /// 
 */
/*  /// INDICATOR_LED, AUX_RGB_LEDS R, G, B
/// OG Wurkkos TS25 anduril.h:     /// RGB-AUX in the front 
// Wurkkos TS25, modelled after the TS10 but with RGB Aux
// this light has three aux LED channels: R, G, B
// don't turn on the aux LEDs while main LEDs are on
/// OG Wurkkos TS10-RGB-AUX anduril.h:     /// RGB-AUX in th front 
// Wurkkos TS10 (RGB aux version) config options for Anduril
// most things are the same as TS25
// this light has three aux LED channels: R, G, B
// don't turn on the aux LEDs while main LEDs are on
// OG Wurkkos TS11 anduril.h: 
// Wurkkos TS11, like a TS25  but with a RGB button and RGB front aux
// this light has three aux LED channels: R, G, B
// turn on the aux LEDs while main LEDs are on
// (but not until the main LEDs are bright enough to overpower the aux)
// (setting this lower makes an annoying effect on some levels)
/// OG Wurkkos FC13 anduril.h: 
// Wurkkos FC13, like a TS25 but with a RGB button and no front aux
// this light has three aux LED channels: R, G, B
// turn on the aux LEDs while main LEDs are on
 */
// don't turn on the aux LEDs while main LEDs are on
/*  /// EXTENDED_INDICATOR_PATTERNS
/// NEW MOD. more-aux-patterns. by SammysHP
/// "Works for classic and RGB aux LEDs."
/// PATTERNS:
    // low nibble:  off state
    // high nibble: lockout state
    // modes are:
    //   0=off
    //   1=low
    //   2=high
    //   3=fancy blinking
    //   4=low blinking
    //   5=high blinking 
///   ///   ///   ///   ///   ///   ///
/// INDICATOR_LED_DEFAULT_MODE. LOCKOUT= 1 = low. OFF = 5 = blinking high 
/// LOCKOUT= 1=low .  OFF-MODE= 4=low blinking 
   ///2025.01.30.. tested on TS25: NOT OK, ACTUAL DEFAULT: /// LOCKOUT= 3=fancy blinking .  OFF-MODE=  low (1)  
   /// whats the default color? BLUE? 
/// This line only Works for classic (non-RGB aux LEDs) ?
/// LOCKOUT= 1=low .  OFF-MODE= 4=low blinking 
/// #define INDICATOR_LED_DEFAULT_MODE ((1<<INDICATOR_LED_CFG_OFFSET) + 4)
/// This line only Works for classic (non-RGB aux LEDs) ?
/// #define INDICATOR_LED_DEFAULT_MODE ((1<<INDICATOR_LED_CFG_OFFSET) + 5)
 */
/*  /// AUX_RGB_LED_DEFAULT PATTERN and COLOR 
/// aux-leds.h : 
 * 0: R
 * 1: RG
 * 2:  G
 * 3:  GB
 * 4:   B
 * 5: R B
 * 6: RGB
 * 7: rainbow
 * 8: voltage
//#define RGB_LED_OFF_DEFAULT 0x18  // low, rainbow
//#define RGB_LED_LOCKOUT_DEFAULT 0x37  // blinking, disco
///   ///   ///   ///   ///   ///   ///
///   ///   ///   ///   ///   ///   ///
///   ///   ///   ///   ///   ///   ///
/// 1= ? 
/// 2= ? 
/// 3= ? 
/// 4= ? 
/// 5= ? 
/// 6= ? 
/// 7= disco 
/// 8= rainbow 
/// 9= voltage 
///   ///   ///   ///   ///   ///   ///
https://www.reddit.com/r/flashlight/comments/sxr1wu/help_with_modifying_anduril_2_hardcoding_default/
Getkong
3y ago
I think high red is probably 0x20 or 0x21. The order is defined on lines 30-40 in a comment, and you can back your way into each one based one whatâ€™s already there.
https://github.com/mkong1/anduril/pull/17/files is where I changed my defaults to high voltage for off, low voltage for locked.
///   ///   ///   ///   ///   ///   ///
zumlin
OP
So before I start doing some trial and error. Do you think that the first digit after 0x defines the pattern, where
1 = low 2 = high 3 = blinking
and the second digit defines the colour from 1 to 9?
///   ///   ///   ///   ///   ///   ///
zumlin
OP
After some trial and error, I can confirm that the codes for the aux leds' colours and patterns are as follows:
0x00 = off	Low	High	Blinking
R	0x10	0x20	0x30
R+G	0x11	0x21	0x31
G	0x12	0x22	0x32
G+B	0x13	0x23	0x33
B	0x14	0x24	0x34
R+B	0x15	0x25	0x35
R+G+B	0x16	0x26	0x36
Disco	0x17	0x27	0x37
Rainbow	0x18	0x28	0x38
Voltage	0x19	0x29	0x39
///   ///   ///   ///   ///   ///   ///
///   ///   ///   ///   ///   ///   ///
///   ///   ///   ///   ///   ///   ///
0x00 = OFF 
0x1* = low
0x2* = high 
0x3* = blinking  (fancy blinking) 
0x4* = blinking low ? 
0x5* = blinking high? 
Last digit : 
0 = R
1 = R+G
2 = G
3 = G+B
4 = B
5 = R+B
6 = R+G+B
/// 7= disco 
/// 8= rainbow 
/// 9= voltage 
///   ///   ///   ///   ///   ///   ///
/// 2025.02.01.. new mods: 
/// 0x54 = blinking high, blue 
/// 0x14 = low, blue 
/// yup, 2025.02.01 tested on TS25: OK, RGB_LED_DEFAULT PATTERN and COLOR work as intended 
 */
// voltage readings were a little high with the Q8 value
// stop panicking at ~50% power
// show each channel while it scroll by in the menu
/*  /// DEFAULT_BLINK_CHANNEL 
/// OG TS25:
// blink numbers on the main LEDs by default
// (so battcheck will be visible while charging)
// blink numbers on the aux LEDs by default
//#define DEFAULT_BLINK_CHANNEL  CM_AUXWHT
 */
// use aux red + aux blue for police strobe
/*  /// 
 */
/* /////    BLINKIES AND STROBES     /////  
///  from `config-default.h` : 
// enable various strobe modes
///  from  `sofirn/anduril.h` :  
 */
/* /// DISABLE SOME BLINKIES ? 
 */
/* /// DISABLE SOME STROBES ? 
 */
/// 2025-02-10: #define USE_BEACONN_MODE
/*  /// 2025-02-09: BEACONN_MODE in STROBE_GROUP 
/// 2025-02-07: BMISG
/// BEACON_MODE_ISG
/// USE_BEACON_MODE_IN_STROBE_GROUP 
/// #define USE_BEACON_MISG
/// 2025-02-09: BMISG
/// BEACON-MISG
/// USE_BEACON_MODE_ISG 
/// #define USE_BEACON_MODE_ISG
/// 2025-02-11: BEACONN_MODE
/// config integrated into strobe-modes files
/// works very well
/// 1H timing / interval adjustment works very well
 */
/*  /// "VER_CHECK_MODE" in the blinky group  
 * idea: "version-check"  in the blinky group? 
 * tested on the SC31 Pro t1616 
   additional line in the "sofirn/sc31-pro-t1616/anduril.h" :  
     #define USE_VER_CHECK_MODE		
 * additional lines in the "battcheck-mode.c" : 
     #elif defined(USE_VER_CHECK_MODE)
     set_state(ver_check_state, 0);
 */
/*  /// "USE_VER_CHECK_MODE" 
 * in "config-default.h" , for reference: 
     "include a function to blink out the firmware version" 
     "#define USE_VERSION_CHECK"
 * sc31-pro-t1616: "USE_VER_CHECK_MODE" 
 */
/* /// DEFAULT_DONT_RAMP_AFTER_MOON
/// some settings are applied per flashlight  
/// adjusted for each flashlight 
/// tested on the  sc31-pro-t1616 
/// 1H = floor (moon). stay at moon, don't ramp up 
 */
/* /// DEFAULT MANUAL MEMORY  
///   stepped ramp:   1  31  61  91   121 
 */
/* /// TACTICAL MODE LEVELS
///   1H,  2H , 3H : 
///   HIGH , TACTICAL STROBE , LOW  
///     150 = turbo
///     (RAMP_SIZE+1) = party strobe
///     (RAMP_SIZE+2) = tactical strobe
///     (RAMP_SIZE+3) = bike flasher  
///example:
 */
/* /// MORE MODS ? ..
 */
///   ///   ///   ///   ///   ///   ///
/*  /// 
 */
/// wurkkos-ts25/anduril.h  
///   END   
/********* Include headers which need to be before FSM *********/
// enable FSM features needed by basic ramping functions
// ramp-mode-fsm.h: FSM config for ramping functions in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// enable FSM's ramping features
// do smooth adjustments when compensating for temperature
// brightness to use when no memory is set
// FIXME: this is only here to stop an error in fsm-ramping.c,
//        which should be fixed by using a different symbol instead
//        (like BUTTON_LED_BRIGHT_LEVEL or RAMP_HALFWAY_LEVEL or something)
// requires the ability to measure time while "off"
// ensure the jump start feature gets compiled in if needed
// include an extra config mode for random stuff which doesn't fit elsewhere
// factory-reset-fsm.h: FSM config options to enable factory reset in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// battcheck-mode-fsm.h: FSM config for battery check mode in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
    // show voltage colors for a few seconds after going to standby
        // level at which to switch from low to high aux brightness
// lockout-mode-fsm.h: FSM config for lockout mode in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// autolock function requires the ability to measure time while "off"
// enable FSM features needed by strobe modes
// strobe-modes-fsm.h: FSM config for strobe modes in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
/*   /// 
 */
/*   /// starryalley Anduril2, New-repo. strobe-modes-fsm.h, 
/// with some edits on the code
 */
/*   /// strobe-modes, PSEUDO_RAND: 
/// LIGHTNING_MODE
/// CANDLE_MODE
/// FIREWORK_MODE
/// BROKEN_FLUORESCENT_MODE
 */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
// enable the random number generator if we need it
// party strobe uses really short pulses
// candle mode is basically a bunch of stacked random triangle waves
// the presence of strobe mode(s) affects how many eeprom bytes we need,
// so it's relevant for FSM configuration
// internal numbering for strobe modes
typedef enum {
    party_strobe_e,
    tactical_strobe_e,
    police_color_strobe_e,
    lightning_storm_e,
    firework_mode_e,
    lighthouse_mode_e,
    /// 2025-02-09
    /// 2025-02-10
    /// beaconn-mode-in-strobe-group 
    beaconn_mode_e,
    /// beacon-mode-in-strobe-group
    bike_flasher_e,
    strobe_mode_END
} strobe_mode_te;
//const int NUM_STROBES = strobe_mode_END;
/*   /// 
 */
/*   /// 
 */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///   END   
// figure out how many bytes of eeprom are needed,
// based on which UI features are enabled
// (include this one last)
// load-save-config-fsm.h: FSM config for eeprom configuration in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
// load into a custom RAM location instead of FSM's default byte array
// let FSM know this config struct exists
typedef struct Config {
    ///// ramp vars
    uint8_t ramp_style;
        uint8_t ramp_2c_style;
        uint8_t ramp_floors[2];
        uint8_t ramp_ceils [2];
        uint8_t ramp_stepss[2];
        uint8_t dont_ramp_after_moon;
        uint8_t manual_memory;
            uint8_t manual_memory_timer;
    ///// channel modes / color modes
        uint8_t channel_mode;
        uint16_t channel_modes_enabled;
            uint8_t manual_memory_channel_mode;
            uint8_t blink_channel;
    ///// Smooth animation between steps, and for on/off
        uint8_t smooth_steps_style;
    ///// strobe / blinky mode settings
        uint8_t strobe_type;
            uint8_t strobe_channels[strobe_mode_END];
        uint8_t strobe_delays[2];
        uint8_t bike_flasher_brightness;
        uint8_t beacon_seconds;
    /// 2025-02-10 
    /// beaconn-mode
        /// 2025-02-11
        uint8_t beaconn_brightness;
        uint8_t beaconn_seconds;
        uint8_t lightning_busy_factor;
        uint8_t firework_brightness;
        uint8_t lighthouse_delay;
/*   /// BEACON_MODE_ISG, FAILED
    /// 2025-02-09 
    /// beacon-mode-isg
    #ifdef USE_BEACON_MODE_ISG
        uint8_t beacon_isg_brightness;
        uint8_t beacon_isg_seconds;
    #endif
    /// beacon-mode-isg
 */
    ///// voltage and temperature
        uint8_t voltage_correction;
        uint8_t therm_ceil;
        int8_t therm_cal_offset;
    ///// aux LEDs
        uint8_t rgb_led_off_mode;
        uint8_t rgb_led_lockout_mode;
            uint8_t post_off_voltage;
    ///// misc other mode settings
        uint8_t tactical_levels[3];
    ///// hardware config / globals menu
} Config;
// auto-detect how many eeprom bytes
// declare this so FSM can see it,
// but define its values in a file which loads later
Config cfg;
/*   /// 
 */
/*   /// 
 */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///   END   
/********* bring in FSM / SpaghettiMonster *********/
// spaghetti-monster.h: UI toolkit / microkernel for e-switch flashlights.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/*
 * SpaghettiMonster: Generic foundation code for e-switch flashlights.
 * Other possible names:
 * - FSM
 * - RoundTable
 * - Mostly Harmless
 * - ...
 */
////////// include all the .h files //////////
// include project definitions to help with recognizing symbols
// fsm-events.h: Event-handling functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002-2007  Marek Michalkiewicz
   Copyright (c) 2006, Carlos Lamas
   Copyright (c) 2009-2010, Jan Waclawek
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/*
   pgmspace.h
   Contributors:
     Created by Marek Michalkiewicz <marekm@linux.org.pl>
     Eric B. Weddington <eric@ecentral.com>
     Wolfgang Haidinger <wh@vmars.tuwien.ac.at> (pgm_read_dword())
     Ivanov Anton <anton@arc.com.ru> (pgm_read_float())
 */
/** \file */
/** \defgroup avr_pgmspace <avr/pgmspace.h>: Program Space Utilities
    \code
    #include <avr/io.h>
    #include <avr/pgmspace.h>
    \endcode
    The functions in this module provide interfaces for a program to access
    data stored in program space (flash memory) of the device.  In order to
    use these functions, the target device must support either the \c LPM or
    \c ELPM instructions.
    \note These functions are an attempt to provide some compatibility with
    header files that come with IAR C, to make porting applications between
    different compilers easier.  This is not 100% compatibility though (GCC
    does not have full support for multiple address spaces yet).
    \note If you are working with strings which are completely based in ram,
    use the standard string functions described in \ref avr_string.
    \note If possible, put your constant tables in the lower 64 KB and use
    pgm_read_byte_near() or pgm_read_word_near() instead of
    pgm_read_byte_far() or pgm_read_word_far() since it is more efficient that
    way, and you can still use the upper 64K for executable code.
    All functions that are suffixed with a \c _P \e require their
    arguments to be in the lower 64 KB of the flash ROM, as they do
    not use ELPM instructions.  This is normally not a big concern as
    the linker setup arranges any program space constants declared
    using the macros from this header file so they are placed right after
    the interrupt vectors, and in front of any executable code.  However,
    it can become a problem if there are too many of these constants, or
    for bootloaders on devices with more than 64 KB of ROM.
    <em>All these functions will not work in that situation.</em>
    \note For <b>Xmega</b> devices, make sure the NVM controller
    command register (\c NVM.CMD or \c NVM_CMD) is set to 0x00 (NOP)
    before using any of these functions.
*/
/* Copyright (c) 2004,2005,2007,2012 Joerg Wunsch
   Copyright (c) 2005, Carlos Lamas
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (C) 1989-2015 Free Software Foundation, Inc.
This file is part of GCC.
GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.
GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.
You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */
/*
 * ISO C Standard:  7.17  Common definitions  <stddef.h>
 */
/* Any one of these symbols __need_* means that GNU libc
   wants us just to define one data type.  So don't define
   the symbols that indicate this file's entire job has been done.  */
/* This avoids lossage on SunOS but only if stdtypes.h comes first.
   There's no way to win with the other order!  Sun lossage.  */
/* On 4.3bsd-net2, make sure ansi.h is included, so we have
   one less case to deal with in the following.  */
/* On FreeBSD 5, machine/ansi.h does not exist anymore... */
/* In 4.3bsd-net2, machine/ansi.h defines these symbols, which are
   defined if the corresponding type is *not* defined.
   FreeBSD-2.1 defines _MACHINE_ANSI_H_ instead of _ANSI_H_.
   NetBSD defines _I386_ANSI_H_ and _X86_64_ANSI_H_ instead of _ANSI_H_ */
/* Sequent's header files use _PTRDIFF_T_ in some conflicting way.
   Just ignore it.  */
/* On VxWorks, <type/vxTypesBase.h> may have defined macros like
   _TYPE_size_t which will typedef size_t.  fixincludes patched the
   vxTypesBase.h so that this macro is only defined if _GCC_SIZE_T is
   not defined, and so that defining this macro defines _GCC_SIZE_T.
   If we find that the macros are still defined at this point, we must
   invoke them so that the type is defined as expected.  */
/* In case nobody has defined these types, but we aren't running under
   GCC 2.00, make sure that __PTRDIFF_TYPE__, __SIZE_TYPE__, and
   __WCHAR_TYPE__ have reasonable values.  This can happen if the
   parts of GCC is compiled by an older compiler, that actually
   include gstddef.h, such as collect2.  */
/* Signed type of difference of two pointers.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
/* If this symbol has done its job, get rid of it.  */
/* Unsigned type of `sizeof' something.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
/* Wide character type.
   Locale-writers should change this as necessary to
   be big enough to hold unique values not between 0 and 127,
   and not (wchar_t) -1, for each defined multibyte character.  */
/* Define this type if we are doing the whole job,
   or if we want this type in particular.  */
/*  In 4.3bsd-net2, leave these undefined to indicate that size_t, etc.
    are already defined.  */
/*  BSD/OS 3.1 and FreeBSD [23].x require the MACHINE_ANSI_H check here.  */
/*  NetBSD 5 requires the I386_ANSI_H and X86_64_ANSI_H checks here.  */
/* A null pointer constant.  */
/* Offset of member MEMBER in a struct of type TYPE. */
/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode
    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.
    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.
    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.
    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".
    Finally, the following macros are defined:
    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/
/**
   \ingroup avr_pgmspace
   \def PROGMEM
   Attribute to use in order to declare an object being located in
   flash ROM.
 */
/* Although in C, we can get away with just using __c, it does not work in
   C++. We need to use &__c[0] to avoid the compiler puking. Dave Hylands
   explaned it thusly,
     Let's suppose that we use PSTR("Test"). In this case, the type returned
     by __c is a prog_char[5] and not a prog_char *. While these are
     compatible, they aren't the same thing (especially in C++). The type
     returned by &__c[0] is a prog_char *, which explains why it works
     fine. */
/* The real thing. */
/*
Macro to read data from program memory for avr tiny parts(tiny 4/5/9/10/20/40).
why:
- LPM instruction is not available in AVR_TINY instruction set.
- Programs are executed starting from address 0x0000 in program memory.
But it must be addressed starting from 0x4000 when accessed via data memory.
Reference: TINY device (ATTiny 4,5,9,10,20 and 40) datasheets
Bug: avrtc-536
*/
/** \ingroup avr_pgmspace
    \def pgm_read_byte_near(address_short)
    Read a byte from the program space with a 16-bit (near) address. 
    \note The address is a byte address.
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_word_near(address_short)
    Read a word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_dword_near(address_short)
    Read a double word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_float_near(address_short)
    Read a float from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_ptr_near(address_short)
    Read a pointer from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_byte(address_short)
    Read a byte from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_word(address_short)
    Read a word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_dword(address_short)
    Read a double word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_float(address_short)
    Read a float from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_read_ptr(address_short)
    Read a pointer from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */
/** \ingroup avr_pgmspace
    \def pgm_get_far_address(var)
   This macro facilitates the obtention of a 32 bit "far" pointer (only 24 bits
   used) to data even passed the 64KB limit for the 16 bit ordinary pointer. It
   is similar to the '&' operator, with some limitations.
   Comments:
   - The overhead is minimal and it's mainly due to the 32 bit size operation.
   - 24 bit sizes guarantees the code compatibility for use in future devices.
   - hh8() is an undocumented feature but seems to give the third significant byte
     of a 32 bit data and accepts symbols, complementing the functionality of hi8()
     and lo8(). There is not an equivalent assembler function to get the high
     significant byte.
   - 'var' has to be resolved at linking time as an existing symbol, i.e, a simple
     type variable name, an array name (not an indexed element of the array, if the
     index is a constant the compiler does not complain but fails to get the address
     if optimization is enabled), a struct name or a struct field name, a function
     identifier, a linker defined identifier,...
   - The returned value is the identifier's VMA (virtual memory address) determined
     by the linker and falls in the corresponding memory region. The AVR Harvard
     architecture requires non overlapping VMA areas for the multiple address spaces
     in the processor: Flash ROM, RAM, and EEPROM. Typical offset for this are
     0x00000000, 0x00800xx0, and 0x00810000 respectively, derived from the linker
     script used and linker options. The value returned can be seen then as a
     universal pointer.
*/
/** \ingroup avr_pgmspace
    \fn const void * memchr_P(const void *s, int val, size_t len)
    \brief Scan flash memory for a character.
    The memchr_P() function scans the first \p len bytes of the flash
    memory area pointed to by \p s for the character \p val.  The first
    byte to match \p val (interpreted as an unsigned character) stops
    the operation.
    \return The memchr_P() function returns a pointer to the matching
    byte or \c NULL if the character does not occur in the given memory
    area.	*/
extern const void * memchr_P(const void *, int __val, size_t __len) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn int memcmp_P(const void *s1, const void *s2, size_t len)
    \brief Compare memory areas
    The memcmp_P() function compares the first \p len bytes of the memory
    areas \p s1 and flash \p s2. The comparision is performed using unsigned
    char operations.
    \returns The memcmp_P() function returns an integer less than, equal
    to, or greater than zero if the first \p len bytes of \p s1 is found,
    respectively, to be less than, to match, or be greater than the first
    \p len bytes of \p s2.	*/
extern int memcmp_P(const void *, const void *, size_t) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn void *memccpy_P (void *dest, const void *src, int val, size_t len)
    This function is similar to memccpy() except that \p src is pointer
    to a string in program space.	*/
extern void *memccpy_P(void *, const void *, int __val, size_t);
/** \ingroup avr_pgmspace
    \fn void *memcpy_P(void *dest, const void *src, size_t n)
    The memcpy_P() function is similar to memcpy(), except the src string
    resides in program space.
    \returns The memcpy_P() function returns a pointer to dest.  */
extern void *memcpy_P(void *, const void *, size_t);
/** \ingroup avr_pgmspace
    \fn void *memmem_P(const void *s1, size_t len1, const void *s2, size_t len2)
    The memmem_P() function is similar to memmem() except that \p s2 is
    pointer to a string in program space.	*/
extern void *memmem_P(const void *, size_t, const void *, size_t) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn const void +memrchr_P(const void *src, int val, size_t len)
    The memrchr_P() function is like the memchr_P() function, except
    that it searches backwards from the end of the \p len bytes pointed
    to by \p src instead of forwards from the front. (Glibc, GNU extension.)
    \return The memrchr_P() function returns a pointer to the matching
    byte or \c NULL if the character does not occur in the given memory
    area.	*/
extern const void * memrchr_P(const void *, int __val, size_t __len) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn char *strcat_P(char *dest, const char *src)
    The strcat_P() function is similar to strcat() except that the \e src
    string must be located in program space (flash).
    \returns The strcat() function returns a pointer to the resulting string
    \e dest. */
extern char *strcat_P(char *, const char *);
/** \ingroup avr_pgmspace
    \fn const char *strchr_P(const char *s, int val)
    \brief Locate character in program space string.
    The strchr_P() function locates the first occurrence of \p val
    (converted to a char) in the string pointed to by \p s in program
    space. The terminating null character is considered to be part of
    the string.
    The strchr_P() function is similar to strchr() except that \p s is
    pointer to a string in program space.
    \returns The strchr_P() function returns a pointer to the matched
    character or \c NULL if the character is not found. */
extern const char * strchr_P(const char *, int __val) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn const char *strchrnul_P(const char *s, int c)
    The strchrnul_P() function is like strchr_P() except that if \p c is
    not found in \p s, then it returns a pointer to the null byte at the
    end of \p s, rather than \c NULL. (Glibc, GNU extension.)
    \return The strchrnul_P() function returns a pointer to the matched
    character, or a pointer to the null byte at the end of \p s (i.e.,
    \c s+strlen(s)) if the character is not found.	*/
extern const char * strchrnul_P(const char *, int __val) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn int strcmp_P(const char *s1, const char *s2)
    The strcmp_P() function is similar to strcmp() except that \p s2 is
    pointer to a string in program space.
    \returns The strcmp_P() function returns an integer less than, equal
    to, or greater than zero if \p s1 is found, respectively, to be less
    than, to match, or be greater than \p s2. A consequence of the
    ordering used by strcmp_P() is that if \p s1 is an initial substring
    of \p s2, then \p s1 is considered to be "less than" \p s2. */
extern int strcmp_P(const char *, const char *) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strcpy_P(char *dest, const char *src)
    The strcpy_P() function is similar to strcpy() except that src is a
    pointer to a string in program space.
    \returns The strcpy_P() function returns a pointer to the destination
    string dest. */
extern char *strcpy_P(char *, const char *);
/** \ingroup avr_pgmspace
    \fn int strcasecmp_P(const char *s1, const char *s2)
    \brief Compare two strings ignoring case.
    The strcasecmp_P() function compares the two strings \p s1 and \p s2,
    ignoring the case of the characters.
    \param s1 A pointer to a string in the devices SRAM.
    \param s2 A pointer to a string in the devices Flash.
    \returns The strcasecmp_P() function returns an integer less than,
    equal to, or greater than zero if \p s1 is found, respectively, to
    be less than, to match, or be greater than \p s2. A consequence of
    the ordering used by strcasecmp_P() is that if \p s1 is an initial
    substring of \p s2, then \p s1 is considered to be "less than" \p s2. */
extern int strcasecmp_P(const char *, const char *) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strcasestr_P(const char *s1, const char *s2)
    This funtion is similar to strcasestr() except that \p s2 is pointer
    to a string in program space.	*/
extern char *strcasestr_P(const char *, const char *) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn size_t strcspn_P(const char *s, const char *reject)
    The strcspn_P() function calculates the length of the initial segment
    of \p s which consists entirely of characters not in \p reject. This
    function is similar to strcspn() except that \p reject is a pointer
    to a string in program space.
    \return The strcspn_P() function returns the number of characters in
    the initial segment of \p s which are not in the string \p reject.
    The terminating zero is not considered as a part of string.	*/
extern size_t strcspn_P(const char *__s, const char * __reject) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn size_t strlcat_P(char *dst, const char *src, size_t siz)
    \brief Concatenate two strings.
    The strlcat_P() function is similar to strlcat(), except that the \p src
    string must be located in program space (flash).
    Appends \p src to string \p dst of size \p siz (unlike strncat(),
    \p siz is the full size of \p dst, not space left).  At most \p siz-1
    characters will be copied.  Always NULL terminates (unless \p siz <=
    \p strlen(dst)).
    \returns The strlcat_P() function returns strlen(src) + MIN(siz,
    strlen(initial dst)).  If retval >= siz, truncation occurred.	*/
extern size_t strlcat_P (char *, const char *, size_t );
/** \ingroup avr_pgmspace
    \fn size_t strlcpy_P(char *dst, const char *src, size_t siz)
    \brief Copy a string from progmem to RAM.
    Copy \p src to string \p dst of size \p siz.  At most \p siz-1
    characters will be copied.  Always NULL terminates (unless \p siz == 0).
    The strlcpy_P() function is similar to strlcpy() except that the
    \p src is pointer to a string in memory space.
    \returns The strlcpy_P() function returns strlen(src). If
    retval >= siz, truncation occurred.  */
extern size_t strlcpy_P (char *, const char *, size_t );
/** \ingroup avr_pgmspace
    \fn size_t strnlen_P(const char *src, size_t len)
    \brief Determine the length of a fixed-size string.
    The strnlen_P() function is similar to strnlen(), except that \c src is a
    pointer to a string in program space.
    \returns The strnlen_P function returns strlen_P(src), if that is less than
    \c len, or \c len if there is no '\\0' character among the first \c len
    characters pointed to by \c src. */
extern size_t strnlen_P(const char *, size_t) __attribute__((__const__)); /* program memory can't change */
/** \ingroup avr_pgmspace
    \fn int strncmp_P(const char *s1, const char *s2, size_t n)
    The strncmp_P() function is similar to strcmp_P() except it only compares
    the first (at most) n characters of s1 and s2.
    \returns The strncmp_P() function returns an integer less than, equal to,
    or greater than zero if s1 (or the first n bytes thereof) is found,
    respectively, to be less than, to match, or be greater than s2.  */
extern int strncmp_P(const char *, const char *, size_t) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn int strncasecmp_P(const char *s1, const char *s2, size_t n)
    \brief Compare two strings ignoring case.
    The strncasecmp_P() function is similar to strcasecmp_P(), except it
    only compares the first \p n characters of \p s1.
    \param s1 A pointer to a string in the devices SRAM.
    \param s2 A pointer to a string in the devices Flash.
    \param n The maximum number of bytes to compare.
    \returns The strncasecmp_P() function returns an integer less than,
    equal to, or greater than zero if \p s1 (or the first \p n bytes
    thereof) is found, respectively, to be less than, to match, or be
    greater than \p s2. A consequence of the ordering used by
    strncasecmp_P() is that if \p s1 is an initial substring of \p s2,
    then \p s1 is considered to be "less than" \p s2.  */
extern int strncasecmp_P(const char *, const char *, size_t) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strncat_P(char *dest, const char *src, size_t len)
    \brief Concatenate two strings.
    The strncat_P() function is similar to strncat(), except that the \e src
    string must be located in program space (flash).
    \returns The strncat_P() function returns a pointer to the resulting string
    dest.  */
extern char *strncat_P(char *, const char *, size_t);
/** \ingroup avr_pgmspace
    \fn char *strncpy_P(char *dest, const char *src, size_t n)
    The strncpy_P() function is similar to strcpy_P() except that not more
    than n bytes of src are copied.  Thus, if there is no null byte among the
    first n bytes of src, the result will not be null-terminated.
    In the case where the length of src is less than that of n, the remainder
    of dest will be padded with nulls.
    \returns The strncpy_P() function returns a pointer to the destination
    string dest.  */
extern char *strncpy_P(char *, const char *, size_t);
/** \ingroup avr_pgmspace
    \fn char *strpbrk_P(const char *s, const char *accept)
    The strpbrk_P() function locates the first occurrence in the string
    \p s of any of the characters in the flash string \p accept. This
    function is similar to strpbrk() except that \p accept is a pointer
    to a string in program space.
    \return  The strpbrk_P() function returns a pointer to the character
    in \p s that matches one of the characters in \p accept, or \c NULL
    if no such character is found. The terminating zero is not considered
    as a part of string: if one or both args are empty, the result will
    \c NULL. */
extern char *strpbrk_P(const char *__s, const char * __accept) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn const char *strrchr_P(const char *s, int val)
    \brief Locate character in string.
    The strrchr_P() function returns a pointer to the last occurrence of
    the character \p val in the flash string \p s.
    \return The strrchr_P() function returns a pointer to the matched
    character or \c NULL if the character is not found. */
extern const char * strrchr_P(const char *, int __val) __attribute__((__const__));
/** \ingroup avr_pgmspace
    \fn char *strsep_P(char **sp, const char *delim)
    \brief Parse a string into tokens.
    The strsep_P() function locates, in the string referenced by \p *sp,
    the first occurrence of any character in the string \p delim (or the
    terminating '\\0' character) and replaces it with a '\\0'.  The
    location of the next character after the delimiter character (or \c
    NULL, if the end of the string was reached) is stored in \p *sp. An
    ``empty'' field, i.e. one caused by two adjacent delimiter
    characters, can be detected by comparing the location referenced by
    the pointer returned in \p *sp to '\\0'. This function is similar to
    strsep() except that \p delim is a pointer to a string in program
    space.
    \return The strsep_P() function returns a pointer to the original
    value of \p *sp. If \p *sp is initially \c NULL, strsep_P() returns
    \c NULL. */
extern char *strsep_P(char **__sp, const char * __delim);
/** \ingroup avr_pgmspace
    \fn size_t strspn_P(const char *s, const char *accept)
    The strspn_P() function calculates the length of the initial segment
    of \p s which consists entirely of characters in \p accept. This
    function is similar to strspn() except that \p accept is a pointer
    to a string in program space.
    \return  The strspn_P() function returns the number of characters in
    the initial segment of \p s which consist only of characters from \p
    accept. The terminating zero is not considered as a part of string.	*/
extern size_t strspn_P(const char *__s, const char * __accept) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strstr_P(const char *s1, const char *s2)
    \brief Locate a substring.
    The strstr_P() function finds the first occurrence of the substring
    \p s2 in the string \p s1.  The terminating '\\0' characters are not
    compared. The strstr_P() function is similar to strstr() except that
    \p s2 is pointer to a string in program space.
    \returns The strstr_P() function returns a pointer to the beginning
    of the substring, or NULL if the substring is not found. If \p s2
    points to a string of zero length, the function returns \p s1. */
extern char *strstr_P(const char *, const char *) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strtok_P(char *s, const char * delim)
    \brief Parses the string into tokens.
    strtok_P() parses the string \p s into tokens. The first call to
    strtok_P() should have \p s as its first argument. Subsequent calls
    should have the first argument set to NULL. If a token ends with a
    delimiter, this delimiting character is overwritten with a '\\0' and a
    pointer to the next character is saved for the next call to strtok_P().
    The delimiter string \p delim may be different for each call.
    The strtok_P() function is similar to strtok() except that \p delim
    is pointer to a string in program space.
    \returns The strtok_P() function returns a pointer to the next token or
    NULL when no more tokens are found.
    \note strtok_P() is NOT reentrant. For a reentrant version of this
    function see strtok_rP().
 */
extern char *strtok_P(char *__s, const char * __delim);
/** \ingroup avr_pgmspace
    \fn char *strtok_rP (char *string, const char *delim, char **last)
    \brief Parses string into tokens.
    The strtok_rP() function parses \p string into tokens. The first call to
    strtok_rP() should have string as its first argument. Subsequent calls
    should have the first argument set to NULL. If a token ends with a
    delimiter, this delimiting character is overwritten with a '\\0' and a
    pointer to the next character is saved for the next call to strtok_rP().
    The delimiter string \p delim may be different for each call. \p last is
    a user allocated char* pointer. It must be the same while parsing the
    same string. strtok_rP() is a reentrant version of strtok_P().
    The strtok_rP() function is similar to strtok_r() except that \p delim
    is pointer to a string in program space.
    \returns The strtok_rP() function returns a pointer to the next token or
    NULL when no more tokens are found. */
extern char *strtok_rP(char *__s, const char * __delim, char **__last);
/** \ingroup avr_pgmspace
    \fn size_t strlen_PF(uint_farptr_t s)
    \brief Obtain the length of a string
    The strlen_PF() function is similar to strlen(), except that \e s is a
    far pointer to a string in program space.
    \param s A far pointer to the string in flash
    \returns The strlen_PF() function returns the number of characters in
    \e s. The contents of RAMPZ SFR are undefined when the function returns. */
extern size_t strlen_PF(uint_farptr_t src) __attribute__((__const__)); /* program memory can't change */
/** \ingroup avr_pgmspace
    \fn size_t strnlen_PF(uint_farptr_t s, size_t len)
    \brief Determine the length of a fixed-size string
    The strnlen_PF() function is similar to strnlen(), except that \e s is a
    far pointer to a string in program space.
    \param s A far pointer to the string in Flash
    \param len The maximum number of length to return
    \returns The strnlen_PF function returns strlen_P(\e s), if that is less
    than \e len, or \e len if there is no '\\0' character among the first \e
    len characters pointed to by \e s. The contents of RAMPZ SFR are
    undefined when the function returns. */
extern size_t strnlen_PF(uint_farptr_t src, size_t len) __attribute__((__const__)); /* program memory can't change */
/** \ingroup avr_pgmspace
    \fn void *memcpy_PF(void *dest, uint_farptr_t src, size_t n)
    \brief Copy a memory block from flash to SRAM
    The memcpy_PF() function is similar to memcpy(), except the data
    is copied from the program space and is addressed using a far pointer.
    \param dest A pointer to the destination buffer
    \param src A far pointer to the origin of data in flash memory
    \param n The number of bytes to be copied
    \returns The memcpy_PF() function returns a pointer to \e dst. The contents
    of RAMPZ SFR are undefined when the function returns. */
extern void *memcpy_PF(void *dest, uint_farptr_t src, size_t len);
/** \ingroup avr_pgmspace
    \fn char *strcpy_PF(char *dst, uint_farptr_t src)
    \brief Duplicate a string
    The strcpy_PF() function is similar to strcpy() except that \e src is a far
    pointer to a string in program space.
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the source string in Flash
    \returns The strcpy_PF() function returns a pointer to the destination
    string \e dst. The contents of RAMPZ SFR are undefined when the funcion
    returns. */
extern char *strcpy_PF(char *dest, uint_farptr_t src);
/** \ingroup avr_pgmspace
    \fn char *strncpy_PF(char *dst, uint_farptr_t src, size_t n)
    \brief Duplicate a string until a limited length
    The strncpy_PF() function is similar to strcpy_PF() except that not more
    than \e n bytes of \e src are copied.  Thus, if there is no null byte among
    the first \e n bytes of \e src, the result will not be null-terminated.
    In the case where the length of \e src is less than that of \e n, the
    remainder of \e dst will be padded with nulls.
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the source string in Flash
    \param n The maximum number of bytes to copy
    \returns The strncpy_PF() function returns a pointer to the destination
    string \e dst. The contents of RAMPZ SFR are undefined when the function
    returns. */
extern char *strncpy_PF(char *dest, uint_farptr_t src, size_t len);
/** \ingroup avr_pgmspace
    \fn char *strcat_PF(char *dst, uint_farptr_t src)
    \brief Concatenates two strings
    The strcat_PF() function is similar to strcat() except that the \e src
    string must be located in program space (flash) and is addressed using
    a far pointer
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the string to be appended in Flash
    \returns The strcat_PF() function returns a pointer to the resulting
    string \e dst. The contents of RAMPZ SFR are undefined when the function
    returns */
extern char *strcat_PF(char *dest, uint_farptr_t src);
/** \ingroup avr_pgmspace
    \fn size_t strlcat_PF(char *dst, uint_farptr_t src, size_t n)
    \brief Concatenate two strings
    The strlcat_PF() function is similar to strlcat(), except that the \e src
    string must be located in program space (flash) and is addressed using
    a far pointer.
    Appends src to string dst of size \e n (unlike strncat(), \e n is the
    full size of \e dst, not space left).  At most \e n-1 characters
    will be copied.  Always NULL terminates (unless \e n <= strlen(\e dst)).
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the source string in Flash
    \param n The total number of bytes allocated to the destination string
    \returns The strlcat_PF() function returns strlen(\e src) + MIN(\e n,
    strlen(initial \e dst)).  If retval >= \e n, truncation occurred. The
    contents of RAMPZ SFR are undefined when the funcion returns. */
extern size_t strlcat_PF(char *dst, uint_farptr_t src, size_t siz);
/** \ingroup avr_pgmspace
    \fn char *strncat_PF(char *dst, uint_farptr_t src, size_t n)
    \brief Concatenate two strings
    The strncat_PF() function is similar to strncat(), except that the \e src
    string must be located in program space (flash) and is addressed using a
    far pointer.
    \param dst A pointer to the destination string in SRAM
    \param src A far pointer to the source string in Flash
    \param n The maximum number of bytes to append
    \returns The strncat_PF() function returns a pointer to the resulting
    string \e dst. The contents of RAMPZ SFR are undefined when the function
    returns. */
extern char *strncat_PF(char *dest, uint_farptr_t src, size_t len);
/** \ingroup avr_pgmspace
    \fn int strcmp_PF(const char *s1, uint_farptr_t s2)
    \brief Compares two strings
    The strcmp_PF() function is similar to strcmp() except that \e s2 is a far
    pointer to a string in program space.
    \param s1 A pointer to the first string in SRAM
    \param s2 A far pointer to the second string in Flash
    \returns The strcmp_PF() function returns an integer less than, equal to,
    or greater than zero if \e s1 is found, respectively, to be less than, to
    match, or be greater than \e s2. The contents of RAMPZ SFR are undefined
    when the function returns. */
extern int strcmp_PF(const char *s1, uint_farptr_t s2) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn int strncmp_PF(const char *s1, uint_farptr_t s2, size_t n)
    \brief Compare two strings with limited length
    The strncmp_PF() function is similar to strcmp_PF() except it only
    compares the first (at most) \e n characters of \e s1 and \e s2.
    \param s1 A pointer to the first string in SRAM
    \param s2 A far pointer to the second string in Flash
    \param n The maximum number of bytes to compare
    \returns The strncmp_PF() function returns an integer less than, equal
    to, or greater than zero if \e s1 (or the first \e n bytes thereof) is found,
    respectively, to be less than, to match, or be greater than \e s2. The
    contents of RAMPZ SFR are undefined when the function returns. */
extern int strncmp_PF(const char *s1, uint_farptr_t s2, size_t n) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn int strcasecmp_PF(const char *s1, uint_farptr_t s2)
    \brief Compare two strings ignoring case
    The strcasecmp_PF() function compares the two strings \e s1 and \e s2, ignoring
    the case of the characters.
    \param s1 A pointer to the first string in SRAM
    \param s2 A far pointer to the second string in Flash
    \returns The strcasecmp_PF() function returns an integer less than, equal
    to, or greater than zero if \e s1 is found, respectively, to be less than, to
    match, or be greater than \e s2. The contents of RAMPZ SFR are undefined
    when the function returns. */
extern int strcasecmp_PF(const char *s1, uint_farptr_t s2) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn int strncasecmp_PF(const char *s1, uint_farptr_t s2, size_t n)
    \brief Compare two strings ignoring case
    The strncasecmp_PF() function is similar to strcasecmp_PF(), except it
    only compares the first \e n characters of \e s1 and the string in flash is
    addressed using a far pointer.
    \param s1 A pointer to a string in SRAM
    \param s2 A far pointer to a string in Flash
    \param n The maximum number of bytes to compare
    \returns The strncasecmp_PF() function returns an integer less than, equal
    to, or greater than zero if \e s1 (or the first \e n bytes thereof) is found,
    respectively, to be less than, to match, or be greater than \e s2. The
    contents of RAMPZ SFR are undefined when the function returns.  */
extern int strncasecmp_PF(const char *s1, uint_farptr_t s2, size_t n) __attribute__((__pure__));
/** \ingroup avr_pgmspace
    \fn char *strstr_PF(const char *s1, uint_farptr_t s2)
    \brief Locate a substring.
    The strstr_PF() function finds the first occurrence of the substring \c s2
    in the string \c s1.  The terminating '\\0' characters are not
    compared.
    The strstr_PF() function is similar to strstr() except that \c s2 is a
    far pointer to a string in program space.
    \returns The strstr_PF() function returns a pointer to the beginning of the
    substring, or NULL if the substring is not found.
    If \c s2 points to a string of zero length, the function returns \c s1. The
    contents of RAMPZ SFR are undefined when the function returns. */
extern char *strstr_PF(const char *s1, uint_farptr_t s2);
/** \ingroup avr_pgmspace
    \fn size_t strlcpy_PF(char *dst, uint_farptr_t src, size_t siz)
    \brief Copy a string from progmem to RAM.
    Copy src to string dst of size siz.  At most siz-1 characters will be
    copied. Always NULL terminates (unless siz == 0).
    \returns The strlcpy_PF() function returns strlen(src). If retval >= siz,
    truncation occurred.  The contents of RAMPZ SFR are undefined when the
    function returns. */
extern size_t strlcpy_PF(char *dst, uint_farptr_t src, size_t siz);
/** \ingroup avr_pgmspace
    \fn int memcmp_PF(const void *s1, uint_farptr_t s2, size_t len)
    \brief Compare memory areas
    The memcmp_PF() function compares the first \p len bytes of the memory
    areas \p s1 and flash \p s2. The comparision is performed using unsigned
    char operations. It is an equivalent of memcmp_P() function, except
    that it is capable working on all FLASH including the exteded area
    above 64kB.
    \returns The memcmp_PF() function returns an integer less than, equal
    to, or greater than zero if the first \p len bytes of \p s1 is found,
    respectively, to be less than, to match, or be greater than the first
    \p len bytes of \p s2.  */
extern int memcmp_PF(const void *, uint_farptr_t, size_t) __attribute__((__pure__));
extern size_t __strlen_P(const char *) __attribute__((__const__)); /* internal helper function */
__attribute__((__always_inline__)) static __inline__ size_t strlen_P(const char * s);
static __inline__ size_t strlen_P(const char *s) {
  return __builtin_constant_p(__builtin_strlen(s))
     ? __builtin_strlen(s) : __strlen_P(s);
}
// timeout durations in ticks (each tick 1/62th s)
// return codes for Event handlers
// Indicates whether this handler consumed (handled) the Event, or
// if the Event should be sent to the next handler in the stack.
// typedefs
typedef uint8_t Event;
typedef struct Emission {
    Event event;
    uint16_t arg;
} Emission;
Event current_event;
// at 0.016 ms per tick, 255 ticks = 4.08 s
static volatile uint16_t ticks_since_last_event = 0;
// maximum number of events which can be waiting at one time
// (would probably be okay to reduce this to 4, but it's higher to be safe)
// was "volatile" before, changed to regular var since IRQ rewrites seem
// to have removed the need for it to be volatile
// no comment about "volatile emissions"
Emission emissions[16];
void append_emission(Event event, uint16_t arg);
void delete_first_emission();
void process_emissions();
uint8_t emit_now(Event event, uint16_t arg);
void emit(Event event, uint16_t arg);
void emit_current_event(uint16_t arg);
void empty_event_sequence();
uint8_t push_event(uint8_t ev_type); // only for use by PCINT_inner()
// TODO: Maybe move these to their own file...
// ... this probably isn't the right place for delays.
    // adjust the timing of delays, lower = shorter delays
    // 90 = 90% delay, 10% for other things
inline void interrupt_nice_delays();
uint8_t nice_delay_ms(uint16_t ms);
//uint8_t nice_delay_s();
void delay_4ms(uint8_t ms);
/* Event structure
 * Bit  7: 1 for a button input event, 0 for all others.
 * If bit 7 is 1:
 *     Bits 0,1,2,3:  Click counter.  Up to 15 clicks.
 *     Bit  4: 1 for a "press" event, 0 for a "release" event.
 *     Bit  5: 1 for a "hold" event, 0 otherwise.
 *     Bit  6: 1 for a "timeout" event, 0 otherwise.
 * If bit 7 is 0:
 *     Sort of ad-hoc, shown in #defines below.
 */
// event masks / bits
// Event types
// Events which aren't button presses
// Button press events
// shouldn't normally happen, but UI might empty_event_sequence() while button
// is down so a release with no recorded prior hold could be possible
// fsm-states.h: State-handling functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// fsm-adc.h: ADC (voltage, temperature) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// voltage is 0.00V to 5.10V in 0.02V steps, from 0 to 255
// so one deci-Volt is 5 steps
// use raw value instead of lowpassed value for the next N measurements
// (2 = 1 for voltage + 1 for temperature)
volatile uint8_t adc_reset = 2;
// default 5 seconds between low-voltage warning events
// low-battery threshold in volts * 50
// battery is low but not critical
// MCU sees voltage 0.X volts lower than actual, add X/2 to readings
void adc_voltage_mode();
volatile uint8_t adc_active_now = 0; // sleep LVP needs a different sleep mode
volatile uint8_t irq_adc = 0; // ADC interrupt happened?
uint8_t adc_sample_count = 0; // skip the first sample; it's junk
uint8_t adc_channel = 0; // 0=voltage, 1=temperature
uint16_t adc_raw[2]; // last ADC measurements (0=voltage, 1=temperature)
uint16_t adc_smooth[2]; // lowpassed ADC measurements (0=voltage, 1=temperature)
// ADC code is split into two parts:
// - ISR: runs immediately at each interrupt, does the bare minimum because time is critical here
// - deferred: the bulk of the logic runs later when time isn't so critical
uint8_t adc_deferred_enable = 0; // stop waiting and run the deferred code
void adc_deferred(); // do the actual ADC-related calculations
static void ADC_voltage_handler();
uint8_t voltage = 0;
void low_voltage();
void battcheck();
// try to keep temperature below 45 C
// don't allow user to set ceiling above 70 C
// Local per-MCU calibration value
// temperature now, in C (ish)
int16_t temperature;
static void ADC_temperature_handler();
//inline void ADC_on();
//inline void ADC_off();
//inline void ADC_start_measurement();
// needs a special sleep mode to get accurate measurements quickly 
// ... full power-down ends up using more power overall, and causes 
// some weird issues when the MCU doesn't stay awake enough cycles 
// to complete a reading
//inline void adc_sleep_mode();
// typedefs
typedef uint8_t State(Event event, uint16_t arg);
typedef State * StatePtr;
// top of the stack
volatile StatePtr current_state;
// stack for states, to allow shared utility states like "input a number"
// and such, which return to the previous state after finishing
StatePtr state_stack[8];
uint8_t state_stack_len = 0;
void _set_state(StatePtr new_state, uint16_t arg,
                Event exit_event, Event enter_event);
int8_t push_state(StatePtr new_state, uint16_t arg);
StatePtr pop_state();
uint8_t set_state(StatePtr new_state, uint16_t arg);
// if loop() needs to change state, use this instead of set_state()
// (because this avoids race conditions)
volatile StatePtr deferred_state;
volatile uint16_t deferred_state_arg;
void set_state_deferred(StatePtr new_state, uint16_t arg);
uint8_t default_state(Event event, uint16_t arg);
// fsm-wdt.h: WDT (Watch Dog Timer) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
//void WDT_on();
//inline void WDT_off();
volatile uint8_t irq_wdt = 0; // WDT interrupt happened?
  // measure battery charge while asleep
// fsm-pcint.h: PCINT (Pin Change Interrupt) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
volatile uint8_t irq_pcint = 0; // pin change interrupt happened?
//static volatile uint8_t button_was_pressed;
volatile uint8_t button_last_state;
uint8_t button_is_pressed();
//inline void PCINT_on();
//inline void PCINT_off();
void PCINT_inner(uint8_t pressed);
// fsm-standby.h: standby mode functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// deferred "off" so we won't suspend in a weird state
// (like...  during the middle of a strobe pulse)
// set this to nonzero to enter standby mode next time the system is idle
volatile uint8_t go_to_standby = 0;
/*
 * From the Attiny85 manual:
 * 0: 16 ms
 * 1: 32 ms
 * 2: 64 ms
 * 3: 0.128 s
 * 4: 0.256 s
 * 5: 0.512 s
 * 6: 1.0 s
 * 7: 2.0 s
 * 32: 4.0 s
 * 33: 8.0 s
 * (other values may have unexpected effects; not sure why the final bit is
 *  separated from the others, in the "32" position instead of "8", but that's
 *  how it is)
 */
void sleep_until_eswitch_pressed();
// stops processing until next click or timer tick
// (I think)
void idle_mode();
// fsm-channels.h: Channel mode functions for SpaghettiMonster.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// always enable channel modes, even if there is only one
// typedefs
typedef void SetLevelFunc(uint8_t level);
typedef SetLevelFunc * SetLevelFuncPtr;
typedef uint8_t GradualTickFunc(uint8_t gt);
typedef GradualTickFunc * GradualTickFuncPtr;
// TODO: implement custom 3H handlers
typedef void ChannelArgFunc();
typedef ChannelArgFunc * ChannelArgFuncPtr;
typedef struct Channel {
    SetLevelFuncPtr set_level;
        GradualTickFuncPtr gradual_tick;
} Channel;
Channel channels[]; // values are defined in the hwdef-*.c
// TODO: size-optimize the case with only 1 channel mode?
// (the arrays and stuff shouldn't be needed)
    // current multi-channel mode
    uint8_t channel_mode = CM_MAIN;
//#ifdef USE_CHANNEL_MODE_TOGGLES
// user can take unwanted modes out of the rotation
// bitmask
void set_channel_mode(uint8_t mode);
// fsm-ramping.h: Ramping functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// actual_level: last ramp level set by set_level()
uint8_t actual_level = 0;
// the level used before actual
uint8_t prev_level = 0;
void set_level(uint8_t level);
//void set_level_smooth(uint8_t level);
void set_level_zero(); // implement this in a hwdef
// adjust brightness very smoothly
uint8_t gradual_target;
inline void set_level_gradually(uint8_t lvl);
void gradual_tick();
// reduce repetition with macros
// tick to a specific value
// tick to a specific value, except when immediate 0 to 255 is needed
// tick the top layer of the stack
// tick a base level of the stack
// (with support for special DD FET behavior
//  like "low=0, high=255" --> "low=255, high=254")
// auto-detect the data type for PWM tables
// FIXME: PWM bits and data type should be per PWM table
// FIXME: this whole thing is a mess and should be removed
    // pointer plus 2*y bytes
    //#define PWM_GET(x,y) pgm_read_word(x+(2*y))
    // nope, the compiler was already doing the math correctly
// use UI-defined ramp tables if they exist
__attribute__((__progmem__)) 
       const uint8_t pwm1_levels[] = { 1,1,2,3,3,4,5,6,7,8,9,11,12,13,15,16,18,19,21,23,26,27,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,71,74,76,78,80,82,85,87,90,93,96,100,103,107,112,116,122,127,133,140,147,154,163,171,182,192,203,215,228,241,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0 };
__attribute__((__progmem__)) 
       const uint8_t pwm2_levels[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,10,11,13,14,16,17,19,21,22,24,26,28,30,32,34,37,39,41,44,46,48,51,54,56,59,62,65,68,71,74,77,81,84,87,91,94,98,102,106,110,114,118,122,126,130,135,139,144,148,153,158,163,168,173,178,184,189,195,200,206,212,218,224,230,236,242,248,255 };
// convenience defs for 1 LED with stacked channels
// FIXME: remove this, use pwm1/2/3 instead
// 2 channel CCT blending ramp
// pulse frequency modulation, a.k.a. dynamic PWM
// (different ceiling / frequency at each ramp level)
// FIXME: dynamic PWM should be a per-channel option, not global
__attribute__((__progmem__)) 
       const uint16_t pwm_tops[] = { 4095,2701,3200,3586,2518,2778,2834,2795,2705,2587,2455,2582,2412,2247,2256,2091,2062,1907,1860,1802,1737,1605,1542,1477,1412,1347,1284,1222,1162,1105,1050,997,946,898,853,810,768,730,693,658,625,594,564,536,503,485,462,439,418,398,384,366,353,340,327,319,307,298,292,284,280,273,269,266,263,260,258,256,256,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
// FIXME: jump start should be per channel / channel mode
// RAMP_SIZE / MAX_LVL
// cfg-*.h should define RAMP_SIZE
//#define RAMP_SIZE (sizeof(stacked_pwm1_levels)/sizeof(STACKED_PWM_DATATYPE))
// fsm-random.h: Random number generator for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t pseudo_rand();
// TODO: test without "volatile", in case it's not needed
volatile uint8_t pseudo_rand_seed = 0;
// fsm-eeprom.h: EEPROM API for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002, 2003, 2004, 2007 Marek Michalkiewicz
   Copyright (c) 2005, 2006 Bjoern Haase
   Copyright (c) 2008 Atmel Corporation
   Copyright (c) 2008 Wouter van Gulik
   Copyright (c) 2009 Dmitry Xmelkov
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
// set this higher to enable normal eeprom functions
// TODO: rename to EEPROM_BYTES_NEEDED or similar, to make purpose clearer
// set this higher to enable wear-levelled eeprom functions
// TODO: rename to EEPROM_WL_BYTES_NEEDED or similar, to make purpose clearer
        // use entire eeprom
        __attribute__((unused)) static void eep_data_fits() { ((void)sizeof(char[1 - 2*!(sizeof(Config) <= 
       (256U)
       )])); };
        uint8_t *eeprom;
    uint8_t load_eeprom(); // returns 1 for success, 0 for no data found
    void save_eeprom();
// if this marker isn't found, the eeprom is assumed to be blank
// wait a few ms before eeprom operations, to wait for power to stabilize
// (otherwise reads or writes can get corrupt data)
// (not necessary on some hardware,
//  but enabled by default when there's space)
// fsm-misc.h: Miscellaneous function for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void auto_clock_speed();
// shortest time (in ms) the light should blink for to indicate a zero
    uint8_t blink_digit(uint8_t num);
//#define USE_BLINK
uint8_t blink_num(uint8_t num);
/*
uint8_t blink(uint8_t num, uint8_t speed);
*/
// if any type of aux LEDs exist, define a shorthand flag for it
// value: 0b00BBGGRR
// each pair of bits: 0=off, 1=low, 2=high
void rgb_led_set(uint8_t value);
// fsm-main.h: main() function for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
int main();
// needs to run frequently to execute the logic for WDT and ADC and stuff
void handle_deferred_interrupts();
// delay.h: Smaller, more flexible _delay_ms() functions.
// Copyright (C) 2015-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002, Marek Michalkiewicz
   Copyright (c) 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2004,2005,2007,2012 Joerg Wunsch
   Copyright (c) 2005, Carlos Lamas
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
static __inline__ void _delay_loop_1(uint8_t __count) __attribute__((__always_inline__));
static __inline__ void _delay_loop_2(uint16_t __count) __attribute__((__always_inline__));
/** \file */
/** \defgroup util_delay_basic <util/delay_basic.h>: Basic busy-wait delay loops
    \code
    #include <util/delay_basic.h>
    \endcode
    The functions in this header file implement simple delay loops
    that perform a busy-waiting.  They are typically used to
    facilitate short delays in the program execution.  They are
    implemented as count-down loops with a well-known CPU cycle
    count per loop iteration.  As such, no other processing can
    occur simultaneously.  It should be kept in mind that the
    functions described here do not disable interrupts.
    In general, for long delays, the use of hardware timers is
    much preferrable, as they free the CPU, and allow for
    concurrent processing of other events while the timer is
    running.  However, in particular for very short delays, the
    overhead of setting up a hardware timer is too much compared
    to the overall delay time.
    Two inline functions are provided for the actual delay algorithms.
*/
/** \ingroup util_delay_basic
    Delay loop using an 8-bit counter \c __count, so up to 256
    iterations are possible.  (The value 256 would have to be passed
    as 0.)  The loop executes three CPU cycles per iteration, not
    including the overhead the compiler needs to setup the counter
    register.
    Thus, at a CPU speed of 1 MHz, delays of up to 768 microseconds
    can be achieved.
*/
void
_delay_loop_1(uint8_t __count)
{
 __asm__ volatile (
  "1: dec %0" "\n\t"
  "brne 1b"
  : "=r" (__count)
  : "0" (__count)
 );
}
/** \ingroup util_delay_basic
    Delay loop using a 16-bit counter \c __count, so up to 65536
    iterations are possible.  (The value 65536 would have to be
    passed as 0.)  The loop executes four CPU cycles per iteration,
    not including the overhead the compiler requires to setup the
    counter register pair.
    Thus, at a CPU speed of 1 MHz, delays of up to about 262.1
    milliseconds can be achieved.
 */
void
_delay_loop_2(uint16_t __count)
{
 __asm__ volatile (
  "1: sbiw %0,1" "\n\t"
  "brne 1b"
  : "=w" (__count)
  : "0" (__count)
 );
}
void _delay_zero() {
    //_delay_loop_2((BOGOMIPS/3) & 0xff00);
    _delay_loop_2(1020);
}
////////// include all the .c files //////////
// arch/mcu.c: Attiny portability header.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// arch/attiny1616.c: attiny1616 support functions
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
////////// clock speed / delay stuff //////////
inline void mcu_clock_speed() {
    // TODO: allow hwdef to define a base clock speed
    // set up the system clock to run at 10 MHz instead of the default 3.33 MHz
    
   __asm__ __volatile__("out %[ccp], %[ccp_ioreg]" "\n\t" "sts %[ioreg], %[val]" : : [ccp] "I" ((((uint16_t) &((*(volatile uint8_t *)(0x0034)))) - 0x00)), [ccp_ioreg] "d" ((uint8_t)CCP_IOREG_gc), [ioreg] "n" (((uint16_t) &((*(CLKCTRL_t *) 0x0060)
   .MCLKCTRLB
   ))), [val] "r" ((uint8_t)
   CLKCTRL_PDIV_2X_gc | 
   0x01))
                                                           
                                                          ;
}
///// clock dividers
// this should work, but needs further validation
inline void clock_prescale_set(uint8_t n) {
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    
   __asm__ __volatile__("out %[ccp], %[ccp_ioreg]" "\n\t" "sts %[ioreg], %[val]" : : [ccp] "I" ((((uint16_t) &((*(volatile uint8_t *)(0x0034)))) - 0x00)), [ccp_ioreg] "d" ((uint8_t)CCP_IOREG_gc), [ioreg] "n" (((uint16_t) &((*(CLKCTRL_t *) 0x0060)
   .MCLKCTRLB
   ))), [val] "r" ((uint8_t)
   n
   ))
                                         ; // Set the prescaler
    while (
          (*(CLKCTRL_t *) 0x0060)
                 .MCLKSTATUS & 
                               0x01
                                              ) {} // wait for clock change to finish
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
}
////////// ADC voltage / temperature //////////
inline void mcu_set_admux_therm() {
    // put the ADC in temperature mode
    // attiny1616 datasheet section 30.3.2.6
    
   (*(VREF_t *) 0x00A0)
   .CTRLA = VREF_ADC0REFSEL_1V1_gc | (
   (*(VREF_t *) 0x00A0)
   .CTRLA & (~
   0x70
   ));; // Set Vbg ref to 1.1V
    
   (*(ADC_t *) 0x0600)
       .MUXPOS = ADC_MUXPOS_TEMPSENSE_gc; // read temperature
    
   (*(ADC_t *) 0x0600)
       .CTRLB = ADC_SAMPNUM_ACC4_gc; // 10-bit result + 4x oversampling
    
   (*(ADC_t *) 0x0600)
       .CTRLC = 
                0x40
               
              | ADC_PRESC_DIV16_gc
               | ADC_REFSEL_INTREF_gc; // Internal ADC reference
}
inline void mcu_set_admux_voltage() {
    // Enabled, free-running (aka, auto-retrigger), run in standby
    
   (*(ADC_t *) 0x0600)
       .CTRLA = 
                0x01 
                              | 
                                0x02 
                                               | 
                                                 0x80
                                                               ;
    // set a INITDLY value because the AVR manual says so (section 30.3.5)
    // (delay 1st reading until Vref is stable)
    
   (*(ADC_t *) 0x0600)
       .CTRLD |= ADC_INITDLY_DLY16_gc;
        // result = resolution * 1.5V / Vbat
        
       (*(VREF_t *) 0x00A0)
       .CTRLA = VREF_ADC0REFSEL_1V5_gc | (
       (*(VREF_t *) 0x00A0)
       .CTRLA & (~
       0x70
       ));; // Set Vbg ref to 1.5V
        
       (*(ADC_t *) 0x0600)
           .MUXPOS = ADC_MUXPOS_INTREF_gc; // read internal reference
        
       (*(ADC_t *) 0x0600)
           .CTRLB = ADC_SAMPNUM_ACC4_gc; // 12-bit result, 4x oversampling
        
       (*(ADC_t *) 0x0600)
           .CTRLC = 
                    0x40
                   
                  | ADC_PRESC_DIV16_gc
                   | ADC_REFSEL_VDDREF_gc; // Vdd (Vcc) be ADC reference
}
inline void mcu_adc_sleep_mode() {
    
   do { (*(volatile uint8_t *)(0x0050)) = (((*(volatile uint8_t *)(0x0050)) & ~(0x06)) | ((0x01<<1))); } while(0)
                                     ;
}
inline void mcu_adc_start_measurement() {
    
   (*(ADC_t *) 0x0600)
       .INTCTRL |= 
                   0x01
                                ; // enable interrupt
    
   (*(ADC_t *) 0x0600)
       .COMMAND |= 
                   0x01
                                ; // actually start measuring
}
/*
inline void mcu_adc_on() {
    VREF.CTRLA |= VREF_ADC0REFSEL_1V1_gc; // Set Vbg ref to 1.1V
    // Enabled, free-running (aka, auto-retrigger), run in standby
    ADC0.CTRLA = ADC_ENABLE_bm | ADC_FREERUN_bm | ADC_RUNSTBY_bm;
    // set a INITDLY value because the AVR manual says so (section 30.3.5)
    // (delay 1st reading until Vref is stable)
    ADC0.CTRLD |= ADC_INITDLY_DLY16_gc;
    hwdef_set_admux_voltage();
}
*/
inline void mcu_adc_off() {
    
   (*(ADC_t *) 0x0600)
       .CTRLA &= ~(
                   0x01
                                ); // disable the ADC
}
inline void mcu_adc_vect_clear() {
    
   (*(ADC_t *) 0x0600)
       .INTFLAGS = 
                   0x01
                                ; // clear the interrupt
}
inline uint16_t mcu_adc_result_temp() {
    // just return left-aligned ADC result, don't convert to calibrated units
    //return ADC0.RES << 6;
    return 
          (*(ADC_t *) 0x0600)
              .RES << 4;
}
inline uint16_t mcu_adc_result_volts() {
    // ADC has no left-aligned mode, so left-align it manually
    return 
          (*(ADC_t *) 0x0600)
              .RES << 4;
}
inline uint8_t mcu_vdd_raw2cooked(uint16_t measurement) {
    // In : 65535 * 1.5 / Vbat
    // Out: uint8_t: Vbat * 50
    // 1.5 = ADC Vref
    // ... spend the extra 84 bytes of ROM for better precision
    // 4096 = how much ADC resolution we're using (12 bits)
    uint8_t vbat = (uint32_t)(10 * 5 * 1.5 * 4096) / (measurement >> 4);
    return vbat;
}
inline uint16_t mcu_temp_raw2cooked(uint16_t measurement) {
    // convert raw ADC values to calibrated temperature
    // In: ADC raw temperature (16-bit, or 12-bit left-aligned)
    // Out: Kelvin << 6
    // Precision: 1/64th Kelvin (but noisy)
    // attiny1616 datasheet section 30.3.2.6
    uint8_t sigrow_gain = 
                          (*(SIGROW_t *) 0x1100)
                                .TEMPSENSE0; // factory calibration data
    int8_t sigrow_offset = 
                          (*(SIGROW_t *) 0x1100)
                                .TEMPSENSE1;
    const uint32_t scaling_factor = 65536; // use all 16 bits of ADC data
    uint32_t temp = measurement - (sigrow_offset << 6);
    temp *= sigrow_gain; // 24-bit result
    temp += scaling_factor / 8; // Add 1/8th K to get correct rounding on later divisions
    temp = temp >> 8; // change (K << 14) to (K << 6)
    return temp; // left-aligned uint16_t, 0 to 1023.98 Kelvin
}
inline uint8_t mcu_adc_lsb() {
    //return (ADCL >> 6) + (ADCH << 2);
    return 
          (*(ADC_t *) 0x0600)
              .RESL; // right aligned, not left... so should be equivalent?
}
////////// WDT //////////
inline void mcu_wdt_active() {
    
   (*(RTC_t *) 0x0140)
      .PITINTCTRL = 
                    0x01
                             ; // enable the Periodic Interrupt
    while (
          (*(RTC_t *) 0x0140)
             .PITSTATUS > 0) {} // make sure the register is ready to be updated
    // Period = 16ms (64 Hz), enable the PI Timer
    
   (*(RTC_t *) 0x0140)
      .PITCTRLA = RTC_PERIOD_CYC512_gc | 
                                         0x01
                                                     ;
}
inline void mcu_wdt_standby() {
    
   (*(RTC_t *) 0x0140)
      .PITINTCTRL = 
                    0x01
                             ; // enable the Periodic Interrupt
    while (
          (*(RTC_t *) 0x0140)
             .PITSTATUS > 0) {} // make sure the register is ready to be updated
    // Set period (64 Hz / STANDBY_TICK_SPEED = 8 Hz), enable the PI Timer
    
   (*(RTC_t *) 0x0140)
      .PITCTRLA = (1<<6) | (3<<3) | 
                                                     0x01
                                                                 ;
}
inline void mcu_wdt_stop() {
    while (
          (*(RTC_t *) 0x0140)
             .PITSTATUS > 0) {} // make sure the register is ready to be updated
    
   (*(RTC_t *) 0x0140)
      .PITCTRLA = 0; // Disable the PI Timer
}
inline void mcu_wdt_vect_clear() {
    
   (*(RTC_t *) 0x0140)
      .PITINTFLAGS = 
                     0x01
                              ; // clear the PIT interrupt flag
}
////////// PCINT - pin change interrupt (e-switch) //////////
inline void mcu_switch_vect_clear() {
    // Write a '1' to clear the interrupt flag
    
   (*(VPORT_t *) 0x0000)
   .INTFLAGS |= (1 << 
                          5
                                    );
}
inline void mcu_pcint_on() {
    
   (*(PORT_t *) 0x0400)
   .PIN2CTRL |= PORT_ISC_BOTHEDGES_gc;
}
inline void mcu_pcint_off() {
    
   (*(PORT_t *) 0x0400)
   .PIN2CTRL &= ~(
                       0x07
                                  );
}
////////// misc //////////
void reboot() {
    // put the WDT in hard reset mode, then trigger it
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    // Enable, timeout 8ms
    
   __asm__ __volatile__("out %[ccp], %[ccp_ioreg]" "\n\t" "sts %[ioreg], %[val]" : : [ccp] "I" ((((uint16_t) &((*(volatile uint8_t *)(0x0034)))) - 0x00)), [ccp_ioreg] "d" ((uint8_t)CCP_IOREG_gc), [ioreg] "n" (((uint16_t) &((*(WDT_t *) 0x0100)
   .CTRLA
   ))), [val] "r" ((uint8_t)
   WDT_PERIOD_8CLK_gc
   ))
                                                  ;
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
    
   __asm__ __volatile__ ("wdr")
              ;
    while (1) {}
}
inline void prevent_reboot_loop() {
    // prevent WDT from rebooting MCU again
    
   (*(RSTCTRL_t *) 0x0040)
          .RSTFR &= ~(
                      0x08
                                     ); // reset status flag
    
   do { uint8_t temp; __asm__ __volatile__ ( "wdr" "\n\t" "out %[ccp_reg], %[ioreg_cen_mask]" "\n\t" "lds %[tmp], %[wdt_reg]" "\n\t" "cbr %[tmp], %[timeout_mask]" "\n\t" "sts %[wdt_reg], %[tmp]" "\n\t" : [tmp] "=r" (temp) : [ccp_reg] "I" ((((uint16_t) &((*(volatile uint8_t *)(0x0034)))) - 0x00)), [ioreg_cen_mask] "r" ((uint8_t)CCP_IOREG_gc), [wdt_reg] "n" (((uint16_t) &((*(volatile uint8_t *)(0x0100))))), [timeout_mask] "I" (0x0F) ); } while(0)
                ; // from avr/wdt.h
}
// Define these in your SpaghettiMonster recipe
// boot-time tasks
void setup();
// single loop iteration, runs continuously
void loop();
// include executable functions too, for easier compiling
// fsm-states.c: State-handling functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// TODO: if callback doesn't handle current event,
//       pass event to next state on stack?
//       Callback return values:
//       0: event handled normally
//       1: event not handled
//       255: error (not sure what this would even mean though, or what difference it would make)
// TODO: function to call stacked callbacks until one returns "handled"
void _set_state(StatePtr new_state, uint16_t arg,
                Event exit_event, Event enter_event) {
    // call old state-exit hook (don't use stack)
    if (current_state != 
                        ((void *)0)
                            ) current_state(exit_event, arg);
    // set new state
    current_state = new_state;
    // call new state-enter hook (don't use stack)
    if (new_state != 
                    ((void *)0)
                        ) current_state(enter_event, arg);
    // since state changed, stop any animation in progress
    interrupt_nice_delays();
}
int8_t push_state(StatePtr new_state, uint16_t arg) {
    if (state_stack_len < 8) {
        // TODO: call old state's exit hook?
        //       new hook for non-exit recursion into child?
        state_stack[state_stack_len] = new_state;
        state_stack_len ++;
        // FIXME: use EV_stacked_state?
        _set_state(new_state, arg, (0b00000000|0b00001001), (0b00000000|0b00001000));
        return state_stack_len;
    } else {
        // TODO: um...  how is a flashlight supposed to handle a recursion depth error?
        return -1;
    }
}
StatePtr pop_state() {
    // TODO: how to handle pop from empty stack?
    StatePtr old_state = 
                        ((void *)0)
                            ;
    StatePtr new_state = 
                        ((void *)0)
                            ;
    if (state_stack_len > 0) {
        state_stack_len --;
        old_state = state_stack[state_stack_len];
    }
    if (state_stack_len > 0) {
        new_state = state_stack[state_stack_len-1];
    }
    // FIXME: what should 'arg' be?  (maybe re-entry should be entry with arg+1?)
    _set_state(new_state, 0, (0b00000000|0b00001001), (0b00000000|0b00001010));
    return old_state;
}
uint8_t set_state(StatePtr new_state, uint16_t arg) {
    // FIXME: this calls exit/enter hooks it shouldn't
    //        (for the layer underneath the top)
    pop_state();
    return push_state(new_state, arg);
}
void set_state_deferred(StatePtr new_state, uint16_t arg) {
    deferred_state = new_state;
    deferred_state_arg = arg;
}
// bottom state on stack
// handles default actions for LVP, thermal regulation, etc
uint8_t default_state(Event event, uint16_t arg) {
    if (0) {} // this should get compiled out
    else if (event == (0b00000000|0b00000100)) {
        low_voltage();
        return 0;
    }
    // event not handled
    return 1;
}
// fsm-events.c: Event-handling functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002, Marek Michalkiewicz
   Copyright (c) 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
void append_emission(Event event, uint16_t arg) {
    uint8_t i;
    // find last entry
    for(i=0;
        (i<16) && (emissions[i].event != 0);
        i++) { }
    // add new entry
    if (i < 16) {
        emissions[i].event = event;
        emissions[i].arg = arg;
    } else {
        // TODO: if queue full, what should we do?
    }
}
void delete_first_emission() {
    uint8_t i;
    for(i=0; i<16 -1; i++) {
        emissions[i].event = emissions[i+1].event;
        emissions[i].arg = emissions[i+1].arg;
    }
    emissions[i].event = 0;
    emissions[i].arg = 0;
}
void process_emissions() {
    while (emissions[0].event != 0) {
        emit_now(emissions[0].event, emissions[0].arg);
        delete_first_emission();
    }
}
// Call stacked callbacks for the given event until one handles it.
uint8_t emit_now(Event event, uint16_t arg) {
    for(int8_t i=state_stack_len-1; i>=0; i--) {
        uint8_t err = state_stack[i](event, arg);
        if (! err) return 0;
    }
    return 1; // event not handled
}
void emit(Event event, uint16_t arg) {
    // add this event to the queue for later,
    // so we won't use too much time during an interrupt
    append_emission(event, arg);
}
void emit_current_event(uint16_t arg) {
    emit(current_event, arg);
}
void empty_event_sequence() {
    current_event = 0;
    ticks_since_last_event = 0;
    // when the user completes an input sequence, interrupt any running timers
    // to cancel any delays currently in progress
    // This eliminates a whole bunch of extra code:
    //   before: if (! nice_delay_ms(ms)) {break;}
    //   after: nice_delay_ms(ms);
    interrupt_nice_delays();
}
uint8_t push_event(uint8_t ev_type) { // only for use by PCINT_inner()
    // don't do this here; do it in PCINT_inner() instead
    //ticks_since_last_event = 0;  // something happened
    // only click events are sent to this function
    current_event |= 0b10000000;
    // handle button presses
    if (ev_type == 0b00010000) {
        // set press flag
        current_event |= 0b00010000;
        // increase click counter
        if ((current_event & 0b00001111) < (0b00001111)) {
            current_event ++;
        }
        return 1; // event pushed, even if max clicks already reached
                   // (will just repeat the max over and over)
    }
    // handle button releases
    else if (ev_type == 0b00000000) {
        // clear the press flag
        current_event &= (~0b00010000);
        // if a "hold" event just ended, set the timeout flag
        // to indicate that the event is done and can be cleared
        if (current_event & 0b00100000) { current_event |= 0b01000000; }
        return 1; // event pushed
    }
    return 0; // unexpected event type
}
// explicitly interrupt these "nice" delays
volatile uint8_t nice_delay_interrupt = 0;
inline void interrupt_nice_delays() { nice_delay_interrupt = 1; }
// like delay_ms, except it aborts on state change
// return value:
//   0: state changed
//   1: normal completion
uint8_t nice_delay_ms(uint16_t ms) {
    /*  // delay_zero() implementation
    if (ms == 0) {
        CLKPR = 1<<CLKPCE; CLKPR = 0;  // full speed
        _delay_loop_2(BOGOMIPS*95/100/3);
        return 1;
    }
    */
    while(ms-- > 0) {
        if (nice_delay_interrupt) {
            return 0;
        }
        uint8_t level = actual_level; // volatile, avoid repeat access
        if (level < 5) {
            clock_prescale_set(clock_div_4);
            _delay_loop_2((10000000UL/4350)*92/100/4);
        }
        //else if (level < HALFSPEED_LEVEL) {
        //    clock_prescale_set(clock_div_2);
        //    _delay_loop_2(BOGOMIPS*95/100/2);
        //}
        else {
            clock_prescale_set(clock_div_1);
            _delay_loop_2((10000000UL/4350)*92/100);
        }
        // restore regular clock speed
        clock_prescale_set(clock_div_1);
        // run pending system processes while we wait
        handle_deferred_interrupts();
        // handle events only afterward, so that any collapsed delays will
        // finish running the UI's loop() code before taking any further actions
        // (this helps make sure code runs in the correct order)
        // (otherwise, a new state's EV_enter runs before the old state's
        //  loop() has finished, and things can get weird)
        process_emissions();
    }
    return 1;
}
void delay_4ms(uint8_t ms) {
    while(ms-- > 0) {
        // underclock MCU to save power
        clock_prescale_set(clock_div_4);
        // wait
        _delay_loop_2((10000000UL/4350)*98/100);
        // restore regular clock speed
        clock_prescale_set(clock_div_1);
    }
}
/*
uint8_t nice_delay_4ms(uint8_t ms) {
    return nice_delay_ms((uint16_t)ms << 2);
}
*/
/*
uint8_t nice_delay_s() {
    return nice_delay_4ms(250);
}
*/
// fsm-adc.c: ADC (voltage, temperature) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// override onboard temperature sensor definition, if relevant
/* Copyright (c) 2002, 2004 Theodore A. Roth
   Copyright (c) 2004, 2007, 2008 Eric B. Weddington
   Copyright (c) 2005, 2006, 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
static inline void adc_therm_mode() {
    mcu_set_admux_therm();
    adc_channel = 1;
    adc_sample_count = 0; // first result is unstable
    mcu_adc_start_measurement();
}
void adc_voltage_mode() {
    mcu_set_admux_voltage();
    adc_channel = 0;
    adc_sample_count = 0; // first result is unstable
    mcu_adc_start_measurement();
}
// Each full cycle runs ~2X per second with just voltage enabled,
// or ~1X per second with voltage and temperature.
// happens every time the ADC sampler finishes a measurement
void __vector_20 (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_20 (void) 
             {
    // clear the interrupt flag
    mcu_adc_vect_clear();
    if (adc_sample_count) {
        uint16_t m; // latest measurement
        uint16_t s; // smoothed measurement
        uint8_t channel = adc_channel;
        // update the latest value
            if (channel) m = mcu_adc_result_temp();
            else m = mcu_adc_result_volts();
        adc_raw[channel] = m;
        // lowpass the value
        //s = adc_smooth[channel];  // easier to read
        uint16_t *v = adc_smooth + channel; // compiles smaller
        s = *v;
        if (m > s) { s++; }
        if (m < s) { s--; }
        //adc_smooth[channel] = s;
        *v = s;
        // track what woke us up, and enable deferred logic
        irq_adc = 1;
    }
    // the next measurement isn't the first
    adc_sample_count = 1;
    // rollover doesn't really matter
    //adc_sample_count ++;
}
void adc_deferred() {
    irq_adc = 0; // event handled
    // real-world entropy makes this a true random, not pseudo
    // Why here instead of the ISR?  Because it makes the time-critical ISR
    // code a few cycles faster and we don't need crypto-grade randomness.
    pseudo_rand_seed += mcu_adc_lsb();
    // the ADC triggers repeatedly when it's on, but we only need to run the
    // voltage and temperature regulation stuff once in a while...so disable
    // this after each activation, until it's manually enabled again
    if (! adc_deferred_enable) return;
    // disable after one iteration
    adc_deferred_enable = 0;
    // what is being measured? 0 = battery voltage, 1 = temperature
    uint8_t adc_step;
    // do whichever one is currently active
    adc_step = adc_channel;
        // in sleep mode, turn off after just one measurement
        // (having the ADC on raises standby power by about 250 uA)
        // (and the usual standby level is only ~20 uA)
        if (go_to_standby) {
            mcu_adc_off();
            // if any measurements were in progress, they're done now
            adc_active_now = 0;
            // also, only check the battery while asleep, not the temperature
            adc_channel = 0;
        }
    if (0) {} // placeholder for easier syntax
    else if (0 == adc_step) { // voltage
        ADC_voltage_handler();
        // set the correct type of measurement for next time
        if (! go_to_standby) adc_therm_mode();
    }
    else if (1 == adc_step) { // temperature
        ADC_temperature_handler();
        // set the correct type of measurement for next time
        adc_voltage_mode();
    }
    if (adc_reset) adc_reset --;
}
static void ADC_voltage_handler() {
    // rate-limit low-voltage warnings to a max of 1 per N seconds
    static uint8_t lvp_timer = 0;
    uint16_t measurement;
    // latest ADC value
    if (adc_reset) { // just after waking, don't lowpass
        measurement = adc_raw[0];
        adc_smooth[0] = measurement; // no lowpass, just use the latest value
    }
    else if (go_to_standby) { // weaker lowpass while asleep
        // occasionally the aux LED color can oscillate during standby,
        // while using "voltage" mode ... so try to reduce the oscillation
        uint16_t r = adc_raw[0];
        uint16_t s = adc_smooth[0];
        // 1/8th proportional lowpass, faster but less stable
        int16_t diff = (r/8) - (s/8);
        s += diff;
        adc_smooth[0] = s;
        measurement = s;
    }
    else measurement = adc_smooth[0];
    // convert raw ADC value to FSM voltage units: Volts * 50
    // 0 .. 250 = 0.0V .. 5.0V
    voltage = mcu_vdd_raw2cooked(measurement)
              + (5 << 1)
                 + ((cfg.voltage_correction - 7) << 1)
              ;
    // if low, callback EV_voltage_low / EV_voltage_critical
    //         (but only if it has been more than N seconds since last call)
    if (lvp_timer) {
        lvp_timer --;
    } else { // it has been long enough since the last warning
        if (voltage < (29*5)) {
            // send out a warning
            emit((0b00000000|0b00000100), 0);
            // reset rate-limit counter
            lvp_timer = (5*1);
        }
    }
}
// generally happens once per second while awake
static void ADC_temperature_handler() {
    // coarse adjustment
    // reduce frequency of minor warnings
    // fine-grained adjustment
    // how proportional should the adjustments be?
    // acceptable temperature window size in C
    // TODO? make this configurable per build target?
    //       (shorter time for hosts with a lower power-to-mass ratio)
    //       (because then it'll have smaller responses)
    static uint8_t history_step = 0;
    static uint16_t temperature_history[8];
    static int8_t warning_threshold = 0;
    if (adc_reset) adc_smooth[1] = adc_raw[1];
    // latest 16-bit ADC reading
    // convert raw ADC value to Kelvin << 6
    // 0 .. 65535 = 0 K .. 1024 K
    uint16_t measurement = mcu_temp_raw2cooked(adc_smooth[1]);
    // let the UI see the current temperature in C
    // (Kelvin << 6) to Celsius
    // Why 275?  Because Atmel's docs use 275 instead of 273.
    temperature = (measurement>>6) + 0 + (int16_t)cfg.therm_cal_offset - 275;
    // instead of (K << 6), use (K << 1) now
    // TODO: use more precision, if it can be done without overflow in 16 bits
    //       (and still work on attiny85 without increasing ROM size)
    measurement = measurement >> 5;
    if (adc_reset) { // wipe out old data after waking up
        // forget any past measurements
        for(uint8_t i=0; i<8; i++)
            temperature_history[i] = measurement;
    }
    // how much has the temperature changed between now and a few seconds ago?
    int16_t diff;
    diff = measurement - temperature_history[history_step];
    // update / rotate the temperature history
    temperature_history[history_step] = measurement;
    history_step = (history_step + 1) & (8 -1);
    // PI[D]: guess what the temperature will be in a few seconds
    uint16_t pt; // predicted temperature
    pt = measurement + (diff * 4);
    // convert temperature limit from C to raw 16-bit ADC units
    // C = (ADC>>6) - 275 + THERM_CAL_OFFSET + TH_CAL;
    // ... so ...
    // (C + 275 - THERM_CAL_OFFSET - TH_CAL) << 6 = ADC;
    uint16_t ceil = (cfg.therm_ceil + 275 - cfg.therm_cal_offset - 0) << 1;
    int16_t offset = pt - ceil;
    // bias small errors toward zero, while leaving large errors mostly unaffected
    // (a diff of 1 C is 2 ADC units, * 4 for therm lookahead, so it becomes 8)
    // (but a diff of 1 C should only send a warning of magnitude 1)
    // (this also makes it only respond to small errors at the time the error
    // happened, not after the temperature has stabilized)
    for(uint8_t foo=0; foo<3; foo++) {
        if (offset > 0) {
            offset --;
        } else if (offset < 0) {
            offset ++;
        }
    }
    // Too hot?
    // (if it's too hot and not getting cooler...)
    if ((offset > 0) && (diff > -1)) {
        // accumulated error isn't big enough yet to send a warning
        if (warning_threshold > 0) {
            warning_threshold -= offset;
        } else { // error is big enough; send a warning
            // how far above the ceiling?
            // original method works, but is too slow on some small hosts:
            // (and typically has a minimum response magnitude of 2 instead of 1)
            //   int16_t howmuch = offset;
            // ... so increase the amount, except for small values
            // (for example, 1:1, 2:1, 3:3, 4:5, 6:9, 8:13, 10:17, 40:77)
            // ... and let us tune the response per build target if desired
            int16_t howmuch = (offset + offset - 3) * 64 / 128;
            if (howmuch < 1) howmuch = 1;
            warning_threshold = 24 - (uint8_t)howmuch;
            // send a warning
            emit((0b00000000|0b00000101), howmuch);
        }
    }
    // Too cold?
    // (if it's too cold and still getting colder...)
    // the temperature is this far below the floor:
    else if (((offset + (2<<1)) < 0) && (diff < 0)) {
        // accumulated error isn't big enough yet to send a warning
        if (warning_threshold < 0) {
            warning_threshold -= (offset + (2<<1));
        } else { // error is big enough; send a warning
            warning_threshold = (-24) - (offset + (2<<1));
            // how far below the floor?
            // int16_t howmuch = ((-BELOW) >> 1) * THERM_RESPONSE_MAGNITUDE / 128;
            int16_t howmuch = (-(offset + (2<<1))) >> 1;
            // send a notification (unless voltage is low)
            // (LVP and underheat warnings fight each other)
            if (voltage > ((29*5) + 1))
                emit((0b00000000|0b00000110), howmuch);
        }
    }
    // Goldilocks?
    // (temperature is within target window, or at least heading toward it)
    else {
        // send a notification (unless voltage is low)
        // (LVP and temp-okay events fight each other)
        if (voltage > (29*5))
            emit((0b00000000|0b00000111), 0);
    }
}
void battcheck() {
        blink_num(voltage / 5);
}
// fsm-wdt.c: WDT (Watch Dog Timer) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002,2005,2007 Marek Michalkiewicz
   Copyright (c) 2007, Dean Camera
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002, 2004 Marek Michalkiewicz
   Copyright (c) 2005, 2006, 2007 Eric B. Weddington
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/*
   avr/wdt.h - macros for AVR watchdog timer
 */
// clock tick -- this runs every 16ms (62.5 fps)
void __vector_7 (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_7 (void) 
             {
    mcu_wdt_vect_clear();
    irq_wdt = 1; // WDT event happened
}
void WDT_inner() {
    irq_wdt = 0; // WDT event handled; reset flag
    static uint8_t adc_trigger = 0;
    // cache this here to reduce ROM size, because it's volatile
    uint16_t ticks_since_last = ticks_since_last_event;
    // increment, but loop from max back to half
    ticks_since_last = (ticks_since_last + 1)
                     | (ticks_since_last & 0x8000);
    // copy back to the original
    ticks_since_last_event = ticks_since_last;
    // detect and emit button change events (even during standby)
    uint8_t was_pressed = button_last_state;
    uint8_t pressed = button_is_pressed();
    if (was_pressed != pressed) {
        go_to_standby = 0;
        PCINT_inner(pressed);
    }
    // cache again, in case the value changed
    ticks_since_last = ticks_since_last_event;
    // handle standby mode specially
    if (go_to_standby) {
        // emit a sleep tick, and process it
        emit((0b00000000|0b00000011), ticks_since_last);
        process_emissions();
        // stop here, usually...  except during the first few seconds asleep, 
        // and once in a while afterward for sleep LVP
        if ((ticks_since_last > (8 * 8))
            && (0 != (ticks_since_last & 0x0f))) return;
        adc_trigger = 0; // make sure a measurement will happen
        adc_active_now = 1; // use ADC noise reduction sleep mode
        adc_voltage_mode(); // enable ADC voltage measurement functions temporarily
    }
    else { // button handling should only happen while awake
    // if time since last event exceeds timeout,
    // append timeout to current event sequence, then
    // send event to current state callback
    // callback on each timer tick
    if ((current_event & 0b11110000) == (0b10000000 | 0b00100000 | 0b00010000)) {
        emit((0b00000000|0b00000001), 0); // override tick counter while holding button
    }
    else {
        emit((0b00000000|0b00000001), ticks_since_last);
    }
    // user held button long enough to count as a long click?
    if (current_event & 0b00010000) {
        // during a "hold", send a hold event each tick, with a timer
        if (current_event & 0b00100000) {
            emit_current_event(ticks_since_last);
        }
        // has button been down long enough to become a "hold"?
        // (first frame of a "hold" event)
        else {
            if (ticks_since_last >= 24) {
                ticks_since_last_event = 0;
                current_event |= 0b00100000;
                emit_current_event(0);
            }
        }
    }
    // event in progress, but button not currently down
    else if (current_event) {
        // "hold" event just ended
        // no timeout required when releasing a long-press
        if (current_event & 0b00100000) {
            //emit_current_event(ticks_since_last);  // should have been emitted by PCINT_inner()
            empty_event_sequence();
        }
        // end and clear event after release timeout
        else if (ticks_since_last >= 18) {
            current_event |= 0b01000000;
            emit_current_event(0);
            empty_event_sequence();
        }
    }
    }
    // enable the deferred ADC handler once in a while
    if (! adc_trigger) {
        mcu_adc_start_measurement();
        adc_deferred_enable = 1;
    }
    // timing for the ADC handler is every 32 ticks (~2Hz)
    adc_trigger = (adc_trigger + 1) & 31;
}
// fsm-pcint.c: PCINT (Pin Change Interrupt) functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002,2005,2007 Marek Michalkiewicz
   Copyright (c) 2007, Dean Camera
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002, Marek Michalkiewicz
   Copyright (c) 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
uint8_t button_is_pressed() {
    uint8_t value = ((
                     (*(VPORT_t *) 0x0000)
                     .IN & (1<<
                                       5
                                                 )) == 0);
    button_last_state = value;
    return value;
}
void __vector_3 (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_3 (void) 
                {
    mcu_switch_vect_clear();
    irq_pcint = 1; // let deferred code know an interrupt happened
    //DEBUG_FLASH;
    // as it turns out, it's more reliable to detect pin changes from WDT
    // because PCINT itself tends to double-tap when connected to a
    // noisy / bouncy switch (so the content of this function has been
    // moved to a separate function, called from WDT only)
    // PCINT_inner(button_is_pressed());
}
// should only be called from PCINT and/or WDT
// (is a separate function to reduce code duplication)
void PCINT_inner(uint8_t pressed) {
    button_last_state = pressed;
    // register the change, and send event to the current state callback
    if (pressed) { // user pressed button
        push_event(0b00010000);
        emit_current_event(0);
    } else { // user released button
        // how long was the button held?
        push_event(0b00000000);
        emit_current_event(ticks_since_last_event);
    }
    ticks_since_last_event = 0;
}
// fsm-standby.c: standby mode functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* Copyright (c) 2002,2005,2007 Marek Michalkiewicz
   Copyright (c) 2007, Dean Camera
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
/* Copyright (c) 2002, 2004 Theodore A. Roth
   Copyright (c) 2004, 2007, 2008 Eric B. Weddington
   Copyright (c) 2005, 2006, 2007 Joerg Wunsch
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */
/* $Id$ */
// low-power standby mode used while off but power still connected
void sleep_until_eswitch_pressed()
{
    mcu_wdt_standby();
    mcu_adc_off();
    // make sure switch isn't currently pressed
    while (button_is_pressed()) {}
    empty_event_sequence(); // cancel pending input on suspend
    mcu_pcint_on(); // wake on e-switch event
    // detect which type of event caused a wake-up
    irq_adc = 0;
    irq_wdt = 0;
    irq_pcint = 0;
    while (go_to_standby) {
        // configure sleep mode
            // needs a special sleep mode during measurements
            if (adc_active_now) mcu_adc_sleep_mode();
            else
        
       do { (*(volatile uint8_t *)(0x0050)) = (((*(volatile uint8_t *)(0x0050)) & ~(0x06)) | ((0x02<<1))); } while(0)
                                          ;
        
       do { (*(volatile uint8_t *)(0x0050)) |= (uint8_t)0x01; } while(0)
                     ;
        
       do { __asm__ __volatile__ ( "sleep" "\n\t" :: ); } while(0)
                  ; // wait here
        // something happened; wake up
        
       do { (*(volatile uint8_t *)(0x0050)) &= (uint8_t)(~0x01); } while(0)
                      ;
        // determine what woke us up...
        if (irq_pcint) { // button pressed; wake up
            go_to_standby = 0;
        }
        if (irq_adc) { // ADC done measuring
            adc_deferred_enable = 1;
            adc_deferred();
            //ADC_off();  // takes care of itself
            //irq_adc = 0;  // takes care of itself
        }
        if (irq_wdt) { // generate a sleep tick
            WDT_inner();
        }
    }
    // don't lowpass immediately after waking
    // also, reset thermal history
    adc_reset = 2;
    // go back to normal running mode
    // PCINT not needed any more, and can cause problems if on
    // (occasional reboots on wakeup-by-button-press)
    mcu_pcint_off();
    // restore normal awake-mode interrupts
    adc_voltage_mode();
    mcu_wdt_active();
}
void idle_mode()
{
    // configure sleep mode
    
   do { (*(volatile uint8_t *)(0x0050)) = (((*(volatile uint8_t *)(0x0050)) & ~(0x06)) | ((0x00<<1))); } while(0)
                                  ;
    
   do { (*(volatile uint8_t *)(0x0050)) |= (uint8_t)0x01; } while(0)
                 ;
    
   do { __asm__ __volatile__ ( "sleep" "\n\t" :: ); } while(0)
              ; // wait here
    // something happened; wake up
    
   do { (*(volatile uint8_t *)(0x0050)) &= (uint8_t)(~0x01); } while(0)
                  ;
}
// fsm-channels.c: Channel mode functions for SpaghettiMonster.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void set_channel_mode(uint8_t mode) {
    if (mode == channel_mode) return; // abort if nothing to do
    uint8_t cur_level = actual_level;
    // turn off old LEDs before changing channel
    set_level(0);
    // change the channel
    channel_mode = mode;
    // update the LEDs
    set_level(cur_level);
}
///// Common set_level_*() functions shared by multiple lights /////
// (unique lights should use their own,
//  but these common versions cover most of the common hardware designs)
// TODO: upgrade some older lights to dynamic PWM
// TODO: 1ch w/ dynamic PWM
// TODO: 1ch w/ dynamic PWM and opamp enable pins?
// TODO: 2ch stacked w/ dynamic PWM
// TODO: 2ch stacked w/ dynamic PWM and opamp enable pins?
// fsm-ramping.c: Ramping functions for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
inline void set_level_aux_leds(uint8_t level) {
        if (! go_to_standby) {
                rgb_led_set(0);
        }
}
void set_level(uint8_t level) {
    set_level_aux_leds(level);
    if (0 == level) {
        set_level_zero();
    } else {
        // call the relevant hardware-specific set_level_*()
        SetLevelFuncPtr set_level_func = channels[channel_mode].set_level;
        set_level_func(level - 1);
    }
    if (actual_level != level) prev_level = actual_level;
    actual_level = level;
    gradual_target = level;
    auto_clock_speed();
}
inline void set_level_gradually(uint8_t lvl) {
    gradual_target = lvl;
}
// call this every frame or every few frames to change brightness very smoothly
void gradual_tick() {
    uint8_t gt = gradual_target;
    if (gt < actual_level) gt = actual_level - 1;
    else if (gt > actual_level) gt = actual_level + 1;
    // call the relevant hardware-specific function
    GradualTickFuncPtr gradual_tick_func = channels[channel_mode].gradual_tick;
    uint8_t done = gradual_tick_func(gt - 1);
    if (done) {
        uint8_t orig = gradual_target;
        set_level(gt);
        gradual_target = orig;
    }
}
// fsm-random.c: Random number generator for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t pseudo_rand() {
    static uint16_t offset = 1024;
    // loop from 1024 to 4095
    offset = ((offset + 1) & 0x0fff) | 0x0400;
    pseudo_rand_seed += 0b01010101; // 85
    return 
          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
          offset
          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; })) 
                                + pseudo_rand_seed;
}
// fsm-eeprom.c: EEPROM API for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t *eeprom;
uint8_t load_eeprom() {
    delay_4ms(2); // wait for power to stabilize
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    // check if eeprom has been initialized; abort if it hasn't
    uint8_t marker = eeprom_read_byte((uint8_t *)0);
    if (marker != 0b10100101) { 
                               __asm__ __volatile__ ("sei" ::: "memory")
                                    ; return 0; }
    // load the actual data
    for(uint8_t i=0; i<sizeof(Config); i++) {
        eeprom[i] = eeprom_read_byte((uint8_t *)(0 +1+i));
    }
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
    return 1;
}
void save_eeprom() {
    delay_4ms(2); // wait for power to stabilize
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    // save the actual data
    for(uint8_t i=0; i<sizeof(Config); i++) {
        eeprom_update_byte((uint8_t *)(0 +1+i), eeprom[i]);
    }
    // save the marker last, to indicate the transaction is complete
    eeprom_update_byte((uint8_t *)0, 0b10100101);
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
}
// fsm-misc.c: Miscellaneous function for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void auto_clock_speed() {
    uint8_t level = actual_level; // volatile, avoid repeat access
    if (level < 5) {
        // run at quarter speed
        // note: this only works when executed as two consecutive instructions
        // (don't try to combine them or put other stuff between)
        clock_prescale_set(clock_div_4);
    }
    else if (level < 20) {
        // run at half speed
        clock_prescale_set(clock_div_2);
    } else {
        // run at full speed
        clock_prescale_set(clock_div_1);
    }
}
uint8_t blink_digit(uint8_t num) {
    //StatePtr old_state = current_state;
    // "zero" digit gets a single short blink
    uint8_t ontime = 1000 * 2 / 12;
    if (!num) { ontime = 10; num ++; }
    // channel is set per blink, to prevent issues
    // if another mode interrupts us (like a config menu)
    uint8_t old_channel = channel_mode;
    for (; num>0; num--) {
        // TODO: allow setting a blink channel mode per build target
            set_channel_mode(cfg.blink_channel);
        set_level((150/6));
            channel_mode = old_channel;
        nice_delay_ms(ontime);
            set_channel_mode(cfg.blink_channel);
        set_level(0);
            channel_mode = old_channel;
        nice_delay_ms(1000 * 3 / 12);
    }
    set_channel_mode(old_channel);
    return nice_delay_ms(1000 * 8 / 12);
}
uint8_t blink_num(uint8_t num) {
    uint8_t hundreds = num / 100;
    num = num % 100;
    uint8_t tens = num / 10;
    num = num % 10;
    if (hundreds) blink_digit(hundreds);
    if (hundreds || tens) blink_digit(tens);
    return blink_digit(num);
}
void rgb_led_set(uint8_t value) {
    // value: 0b00BBGGRR
    uint8_t pins[] = { 
                      2
                                  , 
                                    3
                                                , 
                                                  1 
                                                               };
    for (uint8_t i=0; i<3; i++) {
        uint8_t lvl = (value >> (i<<1)) & 0x03;
        uint8_t pin = pins[i];
        switch (lvl) {
            // FIXME: move this logic to arch/*
            case 0: // LED off
                
               (*(PORT_t *) 0x0440)
                              .DIRSET = (1 << pin); // set as output
                
               (*(PORT_t *) 0x0440)
                              .OUTCLR = (1 << pin); // set output low
                break;
            case 1: // LED low
                
               (*(PORT_t *) 0x0440)
                              .DIRCLR = (1 << pin); // set as input
                // this resolves to PORTx.PINxCTRL = PORT_PULLUPEN_bm;
                *((uint8_t *)&
                             (*(PORT_t *) 0x0440) 
                                             + 0x10 + pin) = 
                                                             0x08
                                                                             ; // enable internal pull-up
                break;
            default: // LED high
                
               (*(PORT_t *) 0x0440)
                              .DIRSET = (1 << pin); // set as output
                
               (*(PORT_t *) 0x0440)
                              .OUTSET = (1 << pin); // set as high
                break;
        }
    }
}
// fsm-main.c: main() function for SpaghettiMonster.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
int main() {
    // Don't allow interrupts while booting
    
   __asm__ __volatile__ ("cli" ::: "memory")
        ;
    // prevents cycling after a crash,
    // whether intentional (like factory reset) or not (bugs)
    prevent_reboot_loop();
    hwdef_setup();
    // all booted -- turn interrupts back on
    mcu_pcint_on();
    // FIXME: support both WDT *and* RTC PIT on newer devices
    // (WDT to recover from crashes, PIT for task scheduling)
    // (old AVR had only WDT, newer ones split it into WDT, RTC, and PIT)
    mcu_wdt_active();
    adc_voltage_mode();
    
   __asm__ __volatile__ ("sei" ::: "memory")
        ;
    // in case any spurious button presses were detected at boot
    delay_4ms(1);
    // fallback for handling a few things
    push_state(default_state, 0);
    nice_delay_interrupt = 0;
    // call recipe's setup
    setup();
    // main loop
    while (1) {
        // if event queue not empty, empty it
        process_emissions();
        // if loop() tried to change state, process that now
        StatePtr df = deferred_state;
        if (df) {
            set_state(df, deferred_state_arg);
            deferred_state = 
                            ((void *)0)
                                ;
            //deferred_state_arg = 0;  // unnecessary
        }
        // enter standby mode if requested
        // (works better if deferred like this)
        if (go_to_standby) {
            set_level(0);
            sleep_until_eswitch_pressed();
        }
        // catch up on interrupts
        handle_deferred_interrupts();
        // turn delays back on, if they were off
        nice_delay_interrupt = 0;
        // give the recipe some time slices
        loop();
    }
}
void handle_deferred_interrupts() {
    /*
    if (irq_pcint) {  // button pressed or released
        // nothing to do here
        // (PCINT only matters during standby)
    }
    */
    if (irq_adc) { // ADC done measuring
        adc_deferred();
        // irq_adc = 0;  // takes care of itself
    }
    if (irq_wdt) { // the clock ticked
        WDT_inner();
        // irq_wdt = 0;  // takes care of itself
    }
}
/********* does this build target have special code to include? *********/
// Wurkkos TS25 PWM helper functions
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// channel modes for RGB aux LEDs
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void set_level_auxred(uint8_t level) {
    rgb_led_set(0b000001 << !(!(level))); // red, high (level > 0) or low
}
void set_level_auxyel(uint8_t level) {
    rgb_led_set(0b000101 << !(!(level))); // red+green, high (level > 0) or low
}
void set_level_auxgrn(uint8_t level) {
    rgb_led_set(0b000100 << !(!(level))); // green, high (level > 0) or low
}
void set_level_auxcyn(uint8_t level) {
    rgb_led_set(0b010100 << !(!(level))); // green+blue, high (level > 0) or low
}
void set_level_auxblu(uint8_t level) {
    rgb_led_set(0b010000 << !(!(level))); // blue, high (level > 0) or low
}
void set_level_auxprp(uint8_t level) {
    rgb_led_set(0b010001 << !(!(level))); // red+blue, high (level > 0) or low
}
void set_level_auxwht(uint8_t level) {
    rgb_led_set(0b010101 << !(!(level))); // red+green+blue, high (level > 0) or low
}
uint8_t gradual_tick_null(uint8_t gt) { return 1; } // do nothing
void set_level_zero();
void set_level_main(uint8_t level);
uint8_t gradual_tick_main(uint8_t gt);
Channel channels[] = {
    { // channel 1 only
        .set_level = set_level_main,
        .gradual_tick = gradual_tick_main
    },
    { .set_level = set_level_auxred, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxyel, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxgrn, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxcyn, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxblu, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxprp, .gradual_tick = gradual_tick_null }, { .set_level = set_level_auxwht, .gradual_tick = gradual_tick_null }
};
void set_level_zero() {
    
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP1BUF = 0;
    
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP0BUF = 0;
    
   (*(TCA_t *) 0x0A00)
   .SINGLE.CNT = 0; // reset phase
}
// single set of LEDs with 2 stacked power channels, DDFET+1 or DDFET+linear
void set_level_main(uint8_t level) {
    uint16_t ch1_pwm = 
                          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                          pwm1_levels+level
                          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                     ;
    uint16_t ch2_pwm = 
                          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                          pwm2_levels+level
                          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                     ;
    // pulse frequency modulation, a.k.a. dynamic PWM
    uint16_t top = 
                  (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                  pwm_tops+level
                  )); uint16_t __result; __asm__ __volatile__ ( "lpm %A0, Z+" "\n\t" "lpm %B0, Z" "\n\t" : "=r" (__result), "=z" (__addr16) : "1" (__addr16) ); __result; }))
                                            ;
    
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP1BUF = ch1_pwm;
    
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP0BUF = ch2_pwm;
    // wait to sync the counter and avoid flashes
    // (unnecessary w/ buffered registers)
    //while(actual_level && (PWM_CNT > (top - 32))) {}
    
   (*(TCA_t *) 0x0A00)
   .SINGLE.PERBUF = top;
    // force reset phase when turning on from zero
    // (because otherwise the initial response is inconsistent)
    if (! actual_level) 
                       (*(TCA_t *) 0x0A00)
                       .SINGLE.CNT = 0;
}
uint8_t gradual_tick_main(uint8_t gt) {
    uint16_t pwm1 = 
                       (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                       pwm1_levels+gt
                       )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                               ;
    uint16_t pwm2 = 
                       (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                       pwm2_levels+gt
                       )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                               ;
    if ( ((
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP1BUF == 0) && (pwm1 == 255)) || ((
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP1BUF == 255) && (pwm1 == 0))) 
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP1BUF = pwm1; else if (
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP1BUF < pwm1) 
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP1BUF ++; else if (
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP1BUF > pwm1) 
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP1BUF --;;
    if (
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP0BUF < pwm2) 
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP0BUF ++; else if (
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP0BUF > pwm2) 
   (*(TCA_t *) 0x0A00)
   .SINGLE.CMP0BUF --;;
    if ( (pwm1 == 
                   (*(TCA_t *) 0x0A00)
                   .SINGLE.CMP1BUF)
        && (pwm2 == 
                   (*(TCA_t *) 0x0A00)
                   .SINGLE.CMP0BUF)
       ) {
        return 1; // done
    }
    return 0; // not done yet
}
/********* Include all the regular app headers *********/
// off-mode.h: "Off" mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// was the light in an "on" mode within the past second or so?
uint8_t ticks_since_on = 0;
// when the light is "off" or in standby
uint8_t off_state(Event event, uint16_t arg);
// ramp-mode.h: Ramping functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// TODO: Replace MAX_Xx7135 with MAX_CH1, MAX_CH2, MAX_REGULATED, etc
// thermal properties, if not defined per-driver
// configure the timing of turning on/off in regular ramp mode
// press: react as soon as the button is pressed
// release: react as soon as the button is released
// timeout: react as soon as we're sure the user isn't doing a double-click
// defaults are release on, timeout off
// default ramp options if not overridden earlier per-driver
// mile marker(s) partway up the ramp
// default: blink only at border between regulated and FET
// ramping mode and its related config mode
uint8_t steady_state(Event event, uint16_t arg);
uint8_t ramp_config_state(Event event, uint16_t arg);
void ramp_config_save(uint8_t step, uint8_t value);
uint8_t ramp_extras_config_state(Event event, uint16_t arg);
// calculate the nearest ramp level which would be valid at the moment
// (is a no-op for smooth ramp, but limits discrete ramp to only the
// correct levels for the user's config)
uint8_t nearest_level(int16_t target);
// ensure ramp globals are correct
void ramp_update_config();
// brightness before thermal step-down
uint8_t target_level = 0;
void set_level_and_therm_target(uint8_t level);
// brightness control
uint8_t memorized_level = 31;
    void manual_memory_restore();
    void manual_memory_save();
// current values, regardless of style
uint8_t ramp_floor = 1;
uint8_t ramp_ceil = 121;
uint8_t ramp_discrete_step_size; // don't set this
uint8_t sunset_timer_orig_level = 0;
void reset_sunset_timer();
typedef enum {
    ramp_extras_cfg_zero = 0,
    manual_memory_config_step,
    manual_memory_timer_config_step,
    dont_ramp_after_moon_config_step,
    ramp_2c_style_config_step,
    smooth_steps_style_config_step,
    ramp_extras_config_num_steps
} ramp_extras_config_steps_e;
// config-mode.h: Config mode base functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// menus can use 2 colors
// when true, changes the channel mode for each config step
uint8_t config_color_per_step = 0;
// config menu
uint8_t config_state_base(
    Event event,
    uint16_t arg,
    uint8_t num_config_steps,
    void (*savefunc)(uint8_t step, uint8_t value)
    );
// aux-leds.h: Aux LED functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t setting_rgb_mode_now = 0;
void rgb_led_update(uint8_t mode, uint16_t arg);
void rgb_led_voltage_readout(uint8_t bright);
/*
 * 0: R
 * 1: RG
 * 2:  G
 * 3:  GB
 * 4:   B
 * 5: R B
 * 6: RGB
 * 7: rainbow
 * 8: voltage
 */
const 
     __attribute__((__progmem__)) 
             uint8_t rgb_led_colors[] = {
    0b00000000, // 0: black
    0b00000001, // 1: red
    0b00000101, // 2: yellow
    0b00000100, // 3: green
    0b00010100, // 4: cyan
    0b00010000, // 5: blue
    0b00010001, // 6: purple
    0b00010101, // 7: white
};
// intentionally 1 higher than total modes, to make "voltage" easier to reach
// (at Hank's request)
const uint8_t RGB_LED_NUM_COLORS = 11
    ;
// misc.h: Misc extra functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
//void blink_confirm(uint8_t num);  // no longer used
void blink_once();
void blip();
// sunset-timer.h: Sunset / candle auto-shutoff functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// how many minutes to add each time the user "bumps" the timer?
// automatic shutoff timer
uint8_t sunset_timer = 0; // minutes remaining in countdown
uint8_t sunset_timer_peak = 0; // total minutes in countdown
uint16_t sunset_ticks = 0; // counts from 0 to TICKS_PER_MINUTE, then repeats
uint8_t sunset_timer_state(Event event, uint16_t arg);
/// version-check-mode.h   
// version-check-mode.h: Version check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
/////////////////////////////////////////////////////////////
       
/// OG: 
///  #include "anduril/version.h"   
///   Mod : 
/// const PROGMEM uint8_t version_number[] = MODEL_NUMBER "." VERSION_NUMBER;
const 
     __attribute__((__progmem__)) 
             uint8_t version_number[] = ".." "0715" ".." "25.02.11..02.12" "..." ;
uint8_t version_check_state(Event event, uint16_t arg);
inline void version_check_iter();
///   END   
// battcheck-mode.h: Battery check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t battcheck_state(Event event, uint16_t arg);
void voltage_config_save(uint8_t step, uint8_t value);
uint8_t voltage_config_state(Event event, uint16_t arg);
// beacon-mode.h: Beacon mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// beacon mode
uint8_t beacon_state(Event event, uint16_t arg);
inline void beacon_mode_iter();
// tempcheck-mode.h: Temperature check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t tempcheck_state(Event event, uint16_t arg);
uint8_t thermal_config_state(Event event, uint16_t arg);
void thermal_config_save(uint8_t step, uint8_t value);
/*   /// BEACON_MODE_ISG,FAILED
/// BEACON_MODE_ISG
 */
/*  /// VER_CHECK_MODE
        /// VERSION_CHECK_MODE in blinky group  
        /// WIP: compile and test on the SC31 Pro t1616 
        /// additional line in the "sofirn/sc31-pro-t1616/anduril.h" :  
        /// #define USE_VER_CHECK_MODE
         */
/// ver-check-mode.h
/// based on "version-check-mode.h"
// version-check-mode.h: Version check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
/////////////////////////////////////////////////////////////
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
/// OG: 
///  #include "anduril/version.h"   
///   Mod : 
/// const PROGMEM uint8_t version_number[] = MODEL_NUMBER "." VERSION_NUMBER;
/// const PROGMEM uint8_t ver_number[] = MODEL_NUMBER "." VERSION_NUMBER;
const 
     __attribute__((__progmem__)) 
             uint8_t ver_number[] = ".." "0715" ".." "25.02.11..02.12" "..." ;
/*  /// VERSION_NUMBER
2025-01-25 13:56:58
2025.01.25     
3131                
 "25-01-25__13-42"
__3131__25-01-25__13-42___
..3131..25-01-25..13-42...
..3131..25.01.25..13.42...
--3131--25-01-25--13-42---
 */
/// uint8_t version_check_state(Event event, uint16_t arg);
uint8_t ver_check_state(Event event, uint16_t arg);
inline void ver_check_iter();
///   END   
// lockout-mode.h: Lockout mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// soft lockout
uint8_t lockout_state(Event event, uint16_t arg);
// momentary-mode.h: Momentary mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// momentary / signalling mode
uint8_t momentary_state(Event event, uint16_t arg);
uint8_t momentary_mode = 0; // 0 = ramping, 1 = strobe
uint8_t momentary_active = 0; // boolean, true if active *right now*
// tactical-mode.h: Tactical mode for Anduril.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// tactical(ish) mode
uint8_t tactical_state(Event event, uint16_t arg);
uint8_t tactical_config_state(Event event, uint16_t arg);
// allow the channel mode handler even when only 1 mode
// (so a tint ramp light could still use 3H even if there's no other mode)
// channel-modes.h: Multi-channel functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// not actually a mode, more of a fallback under other modes
uint8_t channel_mode_state(Event event, uint16_t arg);
uint8_t channel_mode_config_state(Event event, uint16_t arg);
// factory-reset.h: Factory reset functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void factory_reset();
// this one detects its own enable/disable settings
// strobe-modes.h: Strobe modes for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
/*   /// 
 */
/*   /// starryalley Anduril2, New-repo. strobe-modes.h, 
/// no edit on the code, only EFC, adding new lines etc., for ease of reading
 */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
strobe_mode_te current_strobe_type;
// which strobe mode is active?
/// #ifdef USE_CANDLE_MODE
// full FET strobe can be a bit much...  use max regulated level instead,
// if there's a bright enough regulated level
// some drivers need to keep the regulator chip on between pulses,
// so set this to 1 to keep the light on at moon mode between pulses,
// and thus keep the regulator powered up for the next flash
// party and tactical strobes
uint8_t strobe_state(Event event, uint16_t arg);
inline void strobe_state_iter();
inline void party_tactical_strobe_mode_iter(uint8_t st);
inline void police_color_strobe_iter();
inline void lightning_storm_iter();
// bike mode config options
    inline void bike_flasher_iter();
inline void firework_iter();
uint8_t lighthouse_phase = 0;
inline void lighthouse_iter();
/// 2025-02-10
/// 2025-02-11:
/// #define DEFAULT_BIKING_LEVEL  (RAMP_SIZE/3)
uint8_t beaconn_seconds = 2;
inline void beaconn_mode_iter();
/*   ///  USE_BEACON_MODE_ISG, didnt work.
 */
/*   /// 
 */
/*   /// 
 */
/*   /// 
 */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///   END   
// smooth-steps.h: Smooth step adjustments for Anduril.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t smooth_steps_start;
uint8_t smooth_steps_target;
uint8_t smooth_steps_in_progress;
uint8_t smooth_steps_speed;
void smooth_steps_iter();
void set_level_smooth(uint8_t level, uint8_t speed);
// this should be last, so other headers have a chance to declare values
// load-save-config.h: Load/save/eeprom functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
// remember stuff even after battery was changed
void load_config();
void save_config();
// a struct to hold config values
Config cfg = {
    ///// ramp vars
    // smooth vs discrete ramping
    .ramp_style = 1, // 0 = smooth, 1 = discrete
        // 1 = A1 style, 2 = A2 style
        .ramp_2c_style = 1,
    // settings for each ramp (smooth, stepped, simple UI)
        .ramp_floors = {
            1,
            1,
            },
        .ramp_ceils = {
            121,
            121,
            },
        .ramp_stepss = {
            1,
            5,
            },
        .dont_ramp_after_moon = 1,
        .manual_memory = 31,
            .manual_memory_timer = 0,
    ///// channel modes / color modes
        // current multi-channel mode
        .channel_mode = CM_MAIN,
        // user can take unwanted modes out of the rotation (bitmask)
        .channel_modes_enabled = 0b0000000000000001,
            // reset w/ manual memory
            .manual_memory_channel_mode = CM_MAIN,
            // blink numbers in a specific channel (user configurable)
            .blink_channel = CM_AUXRED,
    ///// Smooth animation between steps, and for on/off
        .smooth_steps_style = 1,
    ///// strobe / blinky mode settings
        .strobe_type = bike_flasher_e,
            // channel mode saved per strobe-group mode
        // party / tactical strobe timing
        // party strobe 24 Hz, tactical strobe 10 Hz
        .strobe_delays = { 41, 67 },
        .bike_flasher_brightness = (150/3),
        // beacon timing
        .beacon_seconds = 2,
    /// 2025-02-10 
    /// beaconn-mode
        /// beaconn_brightness
        .beaconn_brightness = (150/3),
        // beaconn timing
        .beaconn_seconds = 2,
        .lightning_busy_factor = 14,
        .firework_brightness = 121,
        .lighthouse_delay = 5,
    /// 2025-02-09 
    /// beacon-mode-isg
    /// beacon-mode-isg
    ///// voltage and temperature
        // same 0.05V units as fudge factor,
        // but 7 is neutral, and the expected range is from 1 to 13
        .voltage_correction = 7,
        .therm_ceil = 50,
        .therm_cal_offset = 0,
    ///// aux LEDs
        .rgb_led_off_mode = 0x54,
        .rgb_led_lockout_mode = 0x14,
            // display voltage readout for a while after turning off?
            .post_off_voltage = 0,
    ///// misc other mode settings
        .tactical_levels = { 121,(150 +2),31 },
    ///// hardware config / globals menu
};
/// a struct to hold config values
/*   /// 
 */
/*   /// 
 */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///   END   
/********* Include all the app logic source files *********/
// (is a bit weird to do things this way,
//  but it saves a lot of space by letting us use the -fwhole-program flag)
// off-mode.c: "Off" mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
/// **off-mode.c** 
/// Mod. : more aux patterns by SammysHP . 
///  2025-01-17   Mods. 5C = BATTCHECK . 3C = STROBE MODES . 
///  also mod  "ramp-mode.c"  to work accordingly, 
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
       
// set level smooth maybe
void off_state_set_level(uint8_t level);
uint8_t off_state(Event event, uint16_t arg) {
    // turn emitter off when entering state
    if (event == (0b00000000|0b00001000)) {
        // turn off
        off_state_set_level(0);
            // don't go to sleep while animating
            arg |= smooth_steps_in_progress;
        ticks_since_on = 0;
            // reset to ramp mode's channel when light turns off
            channel_mode = cfg.channel_mode;
        // redundant, sleep tick does the same thing
        //rgb_led_update(cfg.rgb_led_off_mode, 0);
        sunset_timer = 0; // needs a reset in case previous timer was aborted
        // sleep while off  (lower power use)
        // (unless delay requested; give the ADC some time to catch up)
        if (! arg) { go_to_standby = 1; }
        return 0;
    }
    // go back to sleep eventually if we got bumped but didn't leave "off" state
    else if (event == (0b00000000|0b00000001)) {
        if (arg > 24
                && (! smooth_steps_in_progress)
            ) {
            go_to_standby = 1;
            // redundant, sleep tick does the same thing
            //rgb_led_update(cfg.rgb_led_off_mode, arg);
        }
        return 0;
    }
    // blink the indicator LED, maybe
    else if (event == (0b00000000|0b00000011)) {
        if (ticks_since_on < 255) ticks_since_on ++;
        // reset to manual memory level when timer expires
        if (cfg.manual_memory &&
                (arg >= (cfg.manual_memory_timer * 450))) {
            manual_memory_restore();
        }
        rgb_led_update(cfg.rgb_led_off_mode, arg);
        return 0;
    }
/// 1H = floor 
    // hold: go to lowest level
    else if (event == (0b10000000|0b00100000|0b00010000|1)) {
        off_state_set_level(nearest_level(1));
///  RAMP AFTER MOON ?   
///  DON'T RAMP AFTER MOON   
///  add this into the  anduril.h  file  :  
///   #define DEFAULT_DONT_RAMP_AFTER_MOON 1   
/*
///  ramp-mode.h  Line 176   :   
 */
        if (cfg.dont_ramp_after_moon) {
            return 0;
        }
        // don't start ramping immediately;
        // give the user time to release at moon level
        //if (arg >= HOLD_TIMEOUT) {  // smaller
        if (arg >= (!cfg.ramp_style) * 24) { // more consistent
            set_state(steady_state, 1);
        }
        return 0;
    }
    // hold, release quickly: go to lowest level (floor)
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|1)) {
        set_state(steady_state, 1);
        return 0;
    }
    // 1 click (before timeout): go to memorized level, but allow abort for double click
    else if (event == (0b10000000|0b00000000|1)) {
        off_state_set_level(nearest_level(memorized_level));
        return 0;
    }
    // 1 click: regular mode
    else if (event == (0b10000000|0b01000000|1)) {
        set_state(steady_state, memorized_level);
        return 0;
    }
///  2H = momentary turbo 
    // click, hold: momentary at ceiling or turbo
    else if (event == (0b10000000|0b00100000|0b00010000|2)) {
        ticks_since_on = 0; // momentary turbo is definitely "on"
        uint8_t turbo_level; // how bright is "turbo"?
            uint8_t style_2c = cfg.ramp_2c_style;
            // 0  = ceiling
            // 1+ = full power
            if (0 == style_2c) turbo_level = nearest_level(150);
            else turbo_level = 150;
        off_state_set_level(turbo_level);
        return 0;
    }
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|2)) {
        off_state_set_level(0);
        return 0;
    }
    // 2 clicks: highest mode (ceiling)
    else if (event == (0b10000000|0b01000000|2)) {
        set_state(steady_state, 150);
        return 0;
    }
    // 3 clicks (initial press): off, to prep for later events
    else if (event == (0b10000000|0b00010000|3)) {
            // immediately cancel any animations in progress
            smooth_steps_in_progress = 0;
        off_state_set_level(0);
        return 0;
    }
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
///  mod. 5C = BATTCHECK MODE ( OG :  3C) . 
    // 5 clicks: battcheck mode / blinky mode group 1
    else if (event == (0b10000000|0b01000000|5)) {
        set_state(battcheck_state, 0);
        return 0;
    }
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///
    // 4 clicks: soft lockout
    else if (event == (0b10000000|0b01000000|4)) {
        blink_once();
        set_state(lockout_state, 0);
        return 0;
    }
///  13H = FACTORY RESET  (OG) 
    // 13 clicks and hold the last click: invoke factory reset (reboot)
    else if (event == (0b10000000|0b00100000|0b00010000|13)) {
        reboot();
        return 0;
    }
    // 15+ clicks: show the version number
    else if (event == (0b10000000|0b01000000|15)) {
        set_state(version_check_state, 0);
        return 0;
    }
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///  mod 3C = STROBE MODES  (OG :  3H) 
    // 3C: strobe mode
    else if (event == (0b10000000|0b01000000|3)) {
        set_state(strobe_state, 0);
        return 0;
    }
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///
    // 7 clicks: change RGB aux LED pattern
    else if (event == (0b10000000|0b01000000|7)) {
        uint8_t mode = (cfg.rgb_led_off_mode >> 4) + 1;
        mode = mode % 6;
        cfg.rgb_led_off_mode = (mode << 4) | (cfg.rgb_led_off_mode & 0x0f);
        rgb_led_update(cfg.rgb_led_off_mode, 0);
        save_config();
        blink_once();
        return 0;
    }
    // 7 clicks (hold last): change RGB aux LED color
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        setting_rgb_mode_now = 1;
        if (0 == (arg & 0x3f)) {
            uint8_t mode = (cfg.rgb_led_off_mode & 0x0f) + 1;
            mode = mode % RGB_LED_NUM_COLORS;
            cfg.rgb_led_off_mode = mode | (cfg.rgb_led_off_mode & 0xf0);
            //save_config();
        }
        rgb_led_update(cfg.rgb_led_off_mode, arg);
        return 0;
    }
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|7)) {
        setting_rgb_mode_now = 0;
        save_config();
        return 0;
    }
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
    ////////// Every action below here is blocked in the Extended Simple UI //////////
    // 6 clicks: tactical mode
    else if (event == (0b10000000|0b01000000|6)) {
        blink_once();
        set_state(tactical_state, 0);
        return 0;
    }
///  9H = Misc Config menu (varies per light)  
    return 1;
}
void off_state_set_level(uint8_t level) {
    // this pattern gets used a few times, so reduce duplication
        if (cfg.smooth_steps_style) set_level_smooth(level, 8);
        else
    set_level(level);
}
/// **off-mode.c** 
///   END   
// ramp-mode.c: Ramping functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
    /*  RAMP-MODE  Mods 
///  RAMP-MODE  Mods 
///    2025/01/17 
///  3C = STROBE MODES  
///  4C = LOCKOUT-MODE  (OG)  
///  5C = . . . SAVE CURRENT BRIGHTNESS  
///  6C = toggle smooth vs discrete ramping   
/// NOTE from user manual : 
///   OG single-channel :
///    3C = Change ramp style (smooth / stepped)
///
///   OG multi-channel :
///    3C = Next channel mode (i.e. next color mode)
///    6C = Change ramp style (smooth / stepped)
/// Mods? : 
///   single-channel : 
///    3C = STROBE MODES 
///    6C = Change ramp style (smooth / stepped)
///  
///   multi-channel : 
///    3C = STROBE MODES 
///    6C = Change ramp style (smooth / stepped)
///    7C = Next channel mode (i.e. next color mode) (WIP) 
///  TODO : momentary turbo  and  tint ramping ? 
///  3H = momentary turbo .   4H = tint ramping . 
    */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///    
       
uint8_t steady_state(Event event, uint16_t arg) {
    static int8_t ramp_direction = 1;
        channel_mode = cfg.channel_mode;
    // make sure ramp globals are correct...
    // ... but they already are; no need to do it here
    //ramp_update_config();
    //nearest_level(1);  // same effect, takes less space
    uint8_t mode_min = ramp_floor;
    uint8_t mode_max = ramp_ceil;
    uint8_t step_size;
    if (cfg.ramp_style) { step_size = ramp_discrete_step_size; }
    else { step_size = 1; }
    // how bright is "turbo"?
    uint8_t turbo_level;
        uint8_t style_2c = cfg.ramp_2c_style;
        // 0 = no turbo
        // 1 = Anduril 1 direct to turbo
        // 2 = Anduril 2 direct to ceiling, or turbo if already at ceiling
        if (0 == style_2c) turbo_level = mode_max;
        else if (1 == style_2c) turbo_level = 150;
        else {
            if (memorized_level < mode_max) { turbo_level = mode_max; }
            else { turbo_level = 150; }
        }
    // handle the shutoff timer first
    uint8_t sunset_active = sunset_timer; // save for comparison
    // clock tick
    sunset_timer_state(event, arg);
    // if the timer was just turned on
    if (sunset_timer && (! sunset_active)) {
        sunset_timer_orig_level = actual_level;
    }
    // if the timer just expired, shut off
    else if (sunset_active && (! sunset_timer)) {
        set_state(off_state, 0);
        return 0;
    }
    // turn LED on when we first enter the mode
    if ((event == (0b00000000|0b00001000)) || (event == (0b00000000|0b00001010))) {
        // if we just got back from config mode, go back to memorized level
        if (event == (0b00000000|0b00001010)) {
            arg = memorized_level;
        }
        // remember this level, unless it's moon or turbo
        if ((arg > mode_min) && (arg < mode_max))
            memorized_level = arg;
        // use the requested level even if not memorized
        arg = nearest_level(arg);
        set_level_and_therm_target(arg);
        ramp_direction = 1;
        return 0;
    }
    // 1 click: off
    else if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // 2 clicks: go to/from highest level
    else if (event == (0b10000000|0b01000000|2)) {
        if (actual_level < turbo_level) {
            set_level_and_therm_target(turbo_level);
        }
        else {
            set_level_and_therm_target(memorized_level);
        }
        reset_sunset_timer();
        return 0;
    }
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///  Mod, new in ramp-mode , 3C = STROBE-MODES
    ///   3C = STROBE-MODES
    else if (event == (0b10000000|0b01000000|3)) {
        set_state(strobe_state, 0);
        return 0;
    }
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///   4C = LOCKOUT-MODE   
    // 4 clicks: shortcut to lockout mode
    else if (event == (0b10000000|0b01000000|4)) {
        set_level(0);
        set_state(lockout_state, 0);
        return 0;
    }
///   1H = CHANGE BRIGHTNESS (BRIGHTER)
///   2H = CHANGE BRIGHTNESS (DIMMER)
    // hold: change brightness (brighter, dimmer)
    // click, hold: change brightness (dimmer)
    else if ((event == (0b10000000|0b00100000|0b00010000|1)) || (event == (0b10000000|0b00100000|0b00010000|2))) {
        // ramp infrequently in stepped mode
        if (cfg.ramp_style && (arg % 24 != 0))
            return 0;
            // ramp slower if user configured things that way
            if ((! cfg.ramp_style) && (arg % (cfg.ramp_stepss[0])))
                return 0;
            // if a brightness transition is already happening,
            // don't interrupt it
            // (like 2C for full turbo then 1H to smooth ramp down
            //  ... without this clause, it flickers because it trips
            //  the "blink at ramp ceil" clause below, over and over)
            if (smooth_steps_in_progress) return 0;
        // fix ramp direction on first frame if necessary
        if (!arg) {
            // click, hold should always go down if possible
            if (event == (0b10000000|0b00100000|0b00010000|2)) { ramp_direction = -1; }
            // make it ramp down instead, if already at max
            else if (actual_level >= mode_max) { ramp_direction = -1; }
            // make it ramp up if already at min
            // (off->hold->stepped_min->release causes this state)
            else if (actual_level <= mode_min) { ramp_direction = 1; }
        }
        // if the button is stuck, err on the side of safety and ramp down
        else if ((arg > 62 * 5
                    // FIXME: count from time actual_level hits mode_max,
                    //   not from beginning of button hold
                    * (cfg.ramp_stepss[0])
                    ) && (actual_level >= mode_max)) {
            ramp_direction = -1;
        }
        // if the button is still stuck, lock the light
        else if ((arg > 62 * 10
                    // FIXME: count from time actual_level hits mode_min,
                    //   not from beginning of button hold
                    * (cfg.ramp_stepss[0])
                    ) && (actual_level <= mode_min)) {
            blink_once();
            set_state(lockout_state, 0);
        }
        memorized_level = nearest_level((int16_t)actual_level
                          + (step_size * ramp_direction));
        set_level_and_therm_target(memorized_level);
        reset_sunset_timer();
        return 0;
    }
    // reverse ramp direction on hold release
    else if ((event == (0b10000000|0b00100000|0b00000000|0b01000000|1))
             || (event == (0b10000000|0b00100000|0b00000000|0b01000000|2))) {
        ramp_direction = -ramp_direction;
        return 0;
    }
    else if (event == (0b00000000|0b00000001)) {
        // un-reverse after 1 second
        if (arg == 1) ramp_direction = 1;
        // reduce output if shutoff timer is active
        if (sunset_timer) {
            uint8_t dimmed_level = sunset_timer_orig_level * sunset_timer / sunset_timer_peak;
            uint8_t dimmed_level_next = sunset_timer_orig_level * (sunset_timer-1) / sunset_timer_peak;
            uint8_t dimmed_level_delta = dimmed_level - dimmed_level_next;
            dimmed_level -= dimmed_level_delta * (sunset_ticks/62) / 60;
            if (dimmed_level < 1) dimmed_level = 1;
            set_level_gradually(dimmed_level);
            target_level = dimmed_level;
        }
        int16_t diff = gradual_target - actual_level;
        static uint16_t ticks_since_adjust = 0;
        ticks_since_adjust++;
        if (diff) {
            uint16_t ticks_per_adjust = 256 / 1;
            if (diff < 0) {
                //diff = -diff;
                if (actual_level > 120) {
                    ticks_per_adjust >>= 2;
                }
            } else {
                // rise at half speed
                ticks_per_adjust <<= 1;
            }
            while (diff) {
                ticks_per_adjust >>= 1;
                //diff >>= 1;
                diff /= 2; // because shifting produces weird behavior
            }
            if (ticks_since_adjust > ticks_per_adjust)
            {
                gradual_tick();
                ticks_since_adjust = 0;
            }
        }
        return 0;
    }
    // overheating: drop by an amount proportional to how far we are above the ceiling
    else if (event == (0b00000000|0b00000101)) {
        if (actual_level > 60) {
            int16_t stepdown = actual_level - arg;
            if (stepdown < 60) stepdown = 60;
            else if (stepdown > 150) stepdown = 150;
            set_level_gradually(stepdown);
        }
        return 0;
    }
    // underheating: increase slowly if we're lower than the target
    //               (proportional to how low we are)
    else if (event == (0b00000000|0b00000110)) {
        if (actual_level < target_level) {
            //int16_t stepup = actual_level + (arg>>1);
            int16_t stepup = actual_level + arg;
            if (stepup > target_level) stepup = target_level;
            else if (stepup < 60) stepup = 60;
            set_level_gradually(stepup);
        }
        return 0;
    }
    // temperature is within target window
    // (so stop trying to adjust output)
    else if (event == (0b00000000|0b00000111)) {
        // if we're still adjusting output...  stop after the current step
        if (gradual_target > actual_level)
            gradual_target = actual_level + 1;
        else if (gradual_target < actual_level)
            gradual_target = actual_level - 1;
        return 0;
    }
    ////////// Every action below here is blocked in the simple UI //////////
    // That is, unless we specifically want to enable 3C for smooth/stepped selection in Simple UI
    /*  OG.  3C = toggle smooth vs discrete ramping
     *  OG :  
    // 3 clicks: toggle smooth vs discrete ramping
    // (and/or 6 clicks when there are multiple channel modes)
    // (handle 3C here anyway, when all but 1 mode is disabled)
    else if ((event == EV_3clicks)
        #if NUM_CHANNEL_MODES > 1
             || (event == EV_6clicks)
        ) {
            // detect if > 1 channel mode is enabled,
            // and if so, fall through so channel mode code can handle it
            // otherwise, change the ramp style
            if (event == EV_3clicks) {
                uint8_t enabled = 0;
                for (uint8_t m=0; m<NUM_CHANNEL_MODES; m++)
                    enabled += channel_mode_enabled(m);
                if (enabled > 1)
                    return EVENT_NOT_HANDLED;
            }
        #else
        ) {
        #endif
        cfg.ramp_style = !cfg.ramp_style;
        save_config();
        #ifdef START_AT_MEMORIZED_LEVEL
        save_config_wl();
        #endif
        blip();
        memorized_level = nearest_level(actual_level);
        set_level_and_therm_target(memorized_level);
        #ifdef USE_SUNSET_TIMER
        reset_sunset_timer();
        #endif
        return EVENT_HANDLED;
    }
    */
    /// /// ///   
    /*  Mod. 6C = toggle smooth vs discrete ramping. it's great.
     *  This Mod is done and tested works great :  
    // 6 clicks: toggle smooth vs discrete ramping
    */
    else if (event == (0b10000000|0b01000000|6)) {
        cfg.ramp_style = !cfg.ramp_style;
        save_config();
        blip();
        memorized_level = nearest_level(actual_level);
        set_level_and_therm_target(memorized_level);
        reset_sunset_timer();
        return 0;
    }
    /*  7C : next channel mode  (e.g. next color mode) . untested.  WIP. 
     *  Mod
    // 7C : next channel mode  (e.g. next color mode)
     *  untested.
     *  WIP 
     *  testing  . . .  ? 
     */
    else if (event == (0b10000000|0b01000000|7)) {
        uint8_t enabled = 0;
        for (uint8_t m=0; m<(1 + 7); m++)
        enabled += ((cfg.channel_modes_enabled >> m) & 1);
            if (enabled > 1)
        return 0;
    }
    // If we allowed 3C in Simple UI, now block further actions
    /*  Mods  3H  and/or  4H.  Mods? Not yet. Not now. 
     *  3H  and/or  4H.  multi-channel with tint ramping,  
     *  OG   : 3H = tint ramping, 4H = momentary turbo. 
     *  Mods?  3H = momentary turbo, 4H = tint ramping. 
    OG : 
    // 3H: momentary turbo (on lights with no tint ramping)
    // (or 4H when tint ramping is available)
    else if ((event == EV_click3_hold)
            #ifdef USE_CHANNEL_MODE_ARGS
            || (event == EV_click4_hold)
            #endif
        ) {
        #ifdef USE_CHANNEL_MODE_ARGS
            // ramp tint if tint exists in this mode
            if ((event == EV_click3_hold)
                && (channel_has_args(channel_mode)))
                return EVENT_NOT_HANDLED;
        #endif
        if (! arg) {  // first frame only, to allow thermal regulation to work
            #ifdef USE_2C_STYLE_CONFIG
            uint8_t tl = style_2c ? MAX_LEVEL : turbo_level;
            set_level_and_therm_target(tl);
            #else
            set_level_and_therm_target(turbo_level);
            #endif
        }
        return EVENT_HANDLED;
    }
    else if ((event == EV_click3_hold_release)
            #ifdef USE_CHANNEL_MODE_ARGS
            || (event == EV_click4_hold_release)
            #endif
        ) {
        #ifdef USE_CHANNEL_MODE_ARGS
            // ramp tint if tint exists in this mode
            if ((event == EV_click3_hold_release)
                && (channel_has_args(channel_mode)))
                return EVENT_NOT_HANDLED;
        #endif
        set_level_and_therm_target(memorized_level);
        return EVENT_HANDLED;
    }
 */
    // 3H: momentary turbo (on lights with no tint ramping)
    // (or 4H when tint ramping is available)
    else if ((event == (0b10000000|0b00100000|0b00010000|3))
        ) {
        if (! arg) { // first frame only, to allow thermal regulation to work
            uint8_t tl = style_2c ? 150 : turbo_level;
            set_level_and_therm_target(tl);
        }
        return 0;
    }
    else if ((event == (0b10000000|0b00100000|0b00000000|0b01000000|3))
        ) {
        set_level_and_therm_target(memorized_level);
        return 0;
    } ///   ///   ///   ///   ///   ///   ///   
///  "#undef USE_MOMENTARY_MODE" in "anduril.h" . These lines be]ow are OG, no mod. :   ///   
    // 7H: configure this ramp mode
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        push_state(ramp_config_state, 0);
        return 0;
    }
    /*  OG : 10C .  Mod : 5C  
    OG :   
    #ifdef USE_MANUAL_MEMORY
    else if (event == EV_10clicks) {
        // turn on manual memory and save current brightness
        manual_memory_save();
        save_config();
        blink_once();
        return EVENT_HANDLED;
    }
    */
    ///   ///   ///  OG : 10C .  Mod : 5C   ///   ///   ///   
    else if (event == (0b10000000|0b01000000|5)) {
        // turn on manual memory and save current brightness
        manual_memory_save();
        save_config();
        blink_once();
        return 0;
    } ///   ///   ///   ///   ///   
    else if (event == (0b10000000|0b00100000|0b00010000|10)) {
        // let user configure a bunch of extra ramp options
        push_state(ramp_extras_config_state, 0);
        return 0;
    }
    return 1;
}
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///    
void ramp_config_save(uint8_t step, uint8_t value) {
    // 0 = smooth ramp, 1 = stepped ramp, 2 = simple UI's ramp
    uint8_t style = cfg.ramp_style;
    // save adjusted value to the correct slot
    if (value) {
        // ceiling value is inverted
        if (step == 2) value = 150 + 1 - value;
        // which option are we configuring?
        // TODO? maybe rearrange definitions to avoid the need for this table
        //       (move all ramp values into a single array?)
        uint8_t *steps[] = { cfg.ramp_floors, cfg.ramp_ceils, cfg.ramp_stepss };
        uint8_t *option;
        option = steps[step-1];
        option[style] = value;
    }
}
uint8_t ramp_config_state(Event event, uint16_t arg) {
    const uint8_t num_config_steps = 3;
    return config_state_base(event, arg,
                             num_config_steps, ramp_config_save);
}
void ramp_extras_config_save(uint8_t step, uint8_t value) {
    if (0) {}
    // item 1: disable manual memory, go back to automatic
    else if (manual_memory_config_step == step) {
        cfg.manual_memory = 0;
    }
    // item 2: set manual memory timer duration
    // FIXME: should be limited to (65535 / SLEEP_TICKS_PER_MINUTE)
    //   to avoid overflows or impossibly long timeouts
    //   (by default, the effective limit is 145, but it allows up to 255)
    else if (manual_memory_timer_config_step == step) {
        cfg.manual_memory_timer = value;
    }
///   RAMP AFTER MOON   
    // item 3: ramp up after hold-from-off for moon?
    // 0 = yes, ramp after moon
    // 1+ = no, stay at moon
    else if (dont_ramp_after_moon_config_step == step) {
        cfg.dont_ramp_after_moon = value;
    }
    // item 4: Anduril 1 2C turbo, or Anduril 2 2C ceiling?
    // 1 = Anduril 1, 2C turbo
    // 2+ = Anduril 2, 2C ceiling
    else if (ramp_2c_style_config_step == step) {
        cfg.ramp_2c_style = value;
    }
    else if (smooth_steps_style_config_step == step) {
        cfg.smooth_steps_style = value;
    }
}
uint8_t ramp_extras_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
        ramp_extras_config_num_steps - 1,
        ramp_extras_config_save);
}
// find the ramp level closest to the target,
// using only the levels which are allowed in the current state
uint8_t nearest_level(int16_t target) {
    // using int16_t here saves us a bunch of logic elsewhere,
    // by allowing us to correct for numbers < 0 or > 255 in one central place
    // ensure all globals are correct
    ramp_update_config();
    // bounds check
    uint8_t mode_min = ramp_floor;
    uint8_t mode_max = ramp_ceil;
    uint8_t num_steps = cfg.ramp_stepss[1
        ];
    // special case for 1-step ramp... use halfway point between floor and ceiling
    if (cfg.ramp_style && (1 == num_steps)) {
        uint8_t mid = (mode_max + mode_min) >> 1;
        return mid;
    }
    if (target < mode_min) return mode_min;
    if (target > mode_max) return mode_max;
    // the rest isn't relevant for smooth ramping
    if (! cfg.ramp_style) return target;
    uint8_t ramp_range = mode_max - mode_min;
    ramp_discrete_step_size = ramp_range / (num_steps-1);
    uint8_t this_level = mode_min;
    for(uint8_t i=0; i<num_steps; i++) {
        this_level = mode_min + (i * (uint16_t)ramp_range / (num_steps-1));
        int16_t diff = target - this_level;
        if (diff < 0) diff = -diff;
        if (diff <= (ramp_discrete_step_size>>1))
            return this_level;
    }
    return this_level;
}
// ensure ramp globals are correct
void ramp_update_config() {
    uint8_t which = cfg.ramp_style;
    ramp_floor = cfg.ramp_floors[which];
    ramp_ceil = cfg.ramp_ceils[which];
}
void set_level_and_therm_target(uint8_t level) {
    target_level = level;
        // if adjusting by more than 1 ramp level,
        // animate the step change (if smooth steps enabled)
        uint8_t diff = (level > actual_level)
            ? (level - actual_level) : (actual_level - level);
        if (smooth_steps_in_progress
            || (cfg.smooth_steps_style && (diff > 1)))
            set_level_smooth(level, 4);
        else
    set_level(level);
}
void manual_memory_restore() {
    memorized_level = cfg.manual_memory;
        channel_mode = cfg.channel_mode = cfg.manual_memory_channel_mode;
}
void manual_memory_save() {
    cfg.manual_memory = actual_level;
        cfg.manual_memory_channel_mode = channel_mode;
}
void reset_sunset_timer() {
    if (sunset_timer) {
        sunset_timer_orig_level = actual_level;
        sunset_timer_peak = sunset_timer;
        sunset_ticks = 0;
    }
}
///   END  
// load-save-config.c: Load/save/eeprom functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
void load_config() {
    eeprom = (uint8_t *)&cfg;
    if (! load_eeprom()) return;
}
void save_config() {
    eeprom = (uint8_t *)&cfg;
    save_eeprom();
}
// config-mode.c: Config mode base functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// general helper function for config modes
uint8_t number_entry_state(Event event, uint16_t arg);
// return value from number_entry_state()
volatile uint8_t number_entry_value;
// TODO: promote this to fsm-channels.c ?
void set_chan_if(uint8_t cond, uint8_t chan) {
    if ((cond) && (chan != channel_mode))
        set_channel_mode(chan);
}
// allow the user to set a new value for a config option
// can be called two ways:
//   - with a "click" action: Configures first menu item only.
//   - with a "hold" action: Sets user select a menu item and then
//     choose a new value for it.  User should hold button until light
//     blinks N times, to choose menu item N.  Then let go, and light
//     should give a buzzing prompt to enter a number.  Click N times
//     at the prompt to set the new value to N.
// after completing this process, config state calls the savefunc callback
// and then returns to caller/parent state
uint8_t config_state_base(
        Event event,
        uint16_t arg,
        uint8_t num_config_steps,
        void (*savefunc)(uint8_t step, uint8_t value)) {
    static uint8_t config_step;
    static uint8_t orig_channel;
    if (event == (0b00000000|0b00001000)) {
        orig_channel = channel_mode;
        config_step = 0;
        set_level(0);
        // if button isn't held, configure first menu item
        if (! button_last_state) {
            config_step ++;
            push_state(number_entry_state, 0);
        }
    }
    // if initial "hold" event still active
    // blink while holding to indicate option number
    else if ((event & (0b10000000|0b00100000|0b00010000|0b00000000|0b01000000)) == (0b10000000|0b00100000|0b00010000)) {
        if (config_step <= num_config_steps) {
                uint8_t chan = config_step - 1;
                if (chan < (1 + 7))
                    set_chan_if(config_color_per_step, chan);
            if ((62/10) == (arg % (62*3/2))) {
                config_step ++;
                // blink when config step advances
                if (config_step <= num_config_steps) {
                    set_level(150 * 3 / 8);
                }
            }
            else {
                // stay on at a low level to indicate menu is active
                set_level(150 * 1 / 8);
            }
        } else {
            // turn off when end of menu is reached
            set_level(0);
        }
    }
    // button release: activate number entry for one menu item
    else if ((event & (0b10000000|0b00100000|0b00010000|0b00000000|0b01000000)) == (0b10000000|0b00100000|0b00000000|0b01000000)) {
        // ask the user for a number, if they selected a menu item
        if (config_step && config_step <= num_config_steps) {
                // put the colors back how they were
                set_channel_mode(orig_channel);
            push_state(number_entry_state, 0);
        }
        // exit after falling out of end of menu
        else {
            pop_state();
        }
    }
    // an option was set (return from number_entry_state)
    else if (event == (0b00000000|0b00001010)) {
        // process value with parent's callback
        savefunc(config_step, number_entry_value);
        // make changes persist in eeprom
        save_config();
        pop_state();
    }
    else if (event == (0b00000000|0b00001001)) {
        // put the colors back how they were
        set_channel_mode(orig_channel);
    }
    // eat all other events; don't pass any through to parent
    return 0;
}
uint8_t number_entry_state(Event event, uint16_t arg) {
    static uint8_t entry_step;
    if (event == (0b00000000|0b00001000)) {
        number_entry_value = 0;
        entry_step = 0;
        set_level(0); // initial pause should be dark
    }
    // advance through the process:
    // 0: wait a moment
    // 1: "buzz" while counting clicks
    // 2: save and exit
    else if (event == (0b00000000|0b00000001)) {
        // wait a moment
        if (entry_step == 0) {
            if (arg > 62/2) {
                entry_step ++;
                empty_event_sequence(); // reset tick counter to 0
            }
        }
        // buzz while waiting for a number to be entered
        else if (entry_step == 1) {
            // time out and exit after 3 seconds
            if (arg > 62*3) {
                entry_step ++;
                set_level(0);
            }
            // buzz for N seconds after last event
            // (flicker every other frame,
            //  except first frame (so we can see flashes after each click))
            else if (arg) {
                set_level( (150/8)
                           + ((arg&2)<<2) );
            }
        }
        // all done, save result and return to parent state
        else {
            pop_state();
        }
        return 0;
    }
    // count clicks: click = +1, hold = +10
    else if ((event == (0b10000000|0b00000000|1))
            || (event == (0b10000000|0b00100000|0b00000000|0b01000000|1))
            ) {
        entry_step = 1; // in case user clicked during initial delay
            if (event == (0b10000000|0b00100000|0b00000000|0b01000000|1)) number_entry_value += 10;
            else
        number_entry_value ++; // update the result
        empty_event_sequence(); // reset FSM's click count
        set_level(150/2); // flash briefly
        return 0;
    }
    // eat all other events; don't pass any through to parent
    return 0;
}
// aux-leds.c: Aux LED functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t voltage_to_rgb() {
    static const uint8_t levels[] = {
    // voltage, color
            0, 0, // black
        // li-ion voltages
        29*5, 1, // R
        33*5, 2, // R+G
        35*5, 3, //   G
        37*5, 4, //   G+B
        39*5, 5, //     B
        41*5, 6, // R + B
        44*5, 7, // R+G+B  // skip; looks too similar to G+B
          255, 7, // R+G+B
    };
    uint8_t volts = voltage;
    //if (volts < VOLTAGE_LOW) return 0;
    uint8_t i;
    for (i = 0; volts >= levels[i]; i += 2) {}
    uint8_t color_num = levels[(i - 2) + 1];
    return 
          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
          rgb_led_colors + color_num
          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                   ;
}
// do fancy stuff with the RGB aux LEDs
// mode: 0bPPPPCCCC where PPPP is the pattern and CCCC is the color
// arg: time slice number
void rgb_led_update(uint8_t mode, uint16_t arg) {
    static uint8_t rainbow = 0; // track state of rainbow mode
    static uint8_t frame = 0; // track state of animation mode
    // turn off aux LEDs when battery is empty
    // (but if voltage==0, that means we just booted and don't know yet)
    uint8_t volts = voltage; // save a few bytes by caching volatile value
    if ((volts) && (volts < (29*5))) {
        rgb_led_set(0);
        return;
    }
    uint8_t pattern = (mode>>4); // off, low, high, blinking, ... more?
    uint8_t color = mode & 0x0f;
    // always preview in high mode
    if (setting_rgb_mode_now) { pattern = 2; }
    // use voltage high mode for a few seconds after initial poweroff
    // (but not after changing aux LED settings and other similar actions)
    else if ((arg < (cfg.post_off_voltage * 8))
          && (ticks_since_on < (cfg.post_off_voltage * 8))
          && (ticks_since_on > 0) // don't blink red on 1st frame
        ) {
        // use high mode if regular aux level is high or prev level was high
        pattern = 1 + ((2 == pattern) | (prev_level >= (150/10)));
        // voltage mode
        color = RGB_LED_NUM_COLORS - 1
            ;
    }
    const uint8_t *colors = rgb_led_colors + 1;
    uint8_t actual_color = 0;
    if (color < 7) { // normal color
        actual_color = 
                      (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                      colors + color
                      )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                   ;
    }
    else if (color == 7) { // disco
        rainbow = (rainbow + 1 + pseudo_rand() % 5) % 6;
        actual_color = 
                      (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                      colors + rainbow
                      )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                     ;
    }
    else if (color == 8) { // rainbow
        uint8_t speed = 0x03; // awake speed
        if (go_to_standby) speed = 0x0f; // asleep speed
        if (0 == (arg & speed)) {
            rainbow = (rainbow + 1) % 6;
        }
        actual_color = 
                      (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                      colors + rainbow
                      )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                     ;
    }
    else { // voltage
        // show actual voltage while asleep...
        if (go_to_standby) {
            // choose a color based on battery voltage
            actual_color = voltage_to_rgb();
        }
        // ... but during preview, cycle colors quickly
        else {
            actual_color = 
                          (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                          colors + (((arg>>1) % 3) << 1)
                          )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; }))
                                                                       ;
        }
    }
    // uses an odd length to avoid lining up with rainbow loop
    static const uint8_t animation[] = {2, 1, 0, 0, 0, 0, 0, 0, 0,
                                        1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    switch (pattern) {
        case 3:
            frame = (frame + 1) % sizeof(animation);
            pattern = animation[frame];
            break;
        case 4:
        case 5:
            // low or high blink, 1/8th duty cycle
            pattern = (arg & 7) ? 0 : pattern - 3;
            break;
    }
    uint8_t result;
    switch (pattern) {
        case 0: // off
            result = 0;
            break;
        case 1: // low
            result = actual_color;
            break;
        default: // high
            result = (actual_color << 1);
            break;
    }
    rgb_led_set(result);
}
void rgb_led_voltage_readout(uint8_t bright) {
    uint8_t color = voltage_to_rgb();
    if (bright) color = color << 1;
    rgb_led_set(color);
}
// misc.c: Misc extra functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
/* no longer used
void blink_confirm(uint8_t num) {
    uint8_t brightness = actual_level;
    uint8_t bump = actual_level + BLINK_BRIGHTNESS;
    if (bump > MAX_LEVEL) bump = 0;
    for (; num>0; num--) {
        set_level(bump);
        delay_4ms(10/4);
        set_level(brightness);
        if (num > 1) { delay_4ms(100/4); }
    }
}
*/
// make a short, visible pulse
// (either brighter or darker, depending on current brightness)
void blink_once() {
    uint8_t brightness = actual_level;
    uint8_t bump = brightness + (150/6);
    if (bump > 150) bump = 0;
    set_level(bump);
    delay_4ms(10/4);
    set_level(brightness);
}
// Just go dark for a moment to indicate to user that something happened
void blip() {
    uint8_t temp = actual_level;
    set_level(0);
    delay_4ms(3);
    set_level(temp);
}
// sunset-timer.c: Sunset / candle auto-shutoff functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t sunset_timer_state(Event event, uint16_t arg) {
    // reset on start
    if (event == (0b00000000|0b00001000)) {
        sunset_timer = 0;
        sunset_ticks = 0;
        return 0;
    }
    // hold: maybe "bump" the timer if it's active and almost expired
    else if (event == (0b10000000|0b00100000|0b00010000|1)) {
        // ramping up should "bump" the timer to extend the deadline a bit
        if ((sunset_timer > 0) && (sunset_timer < 4)) {
            sunset_timer = 3; // 3 minutes
            sunset_timer_peak = 3;
            sunset_ticks = 0; // re-start current "minute"
        }
    }
    // 5H: add 5m to timer, per second, until released
    else if (event == (0b10000000|0b00100000|0b00010000|5)) {
        if (0 == (arg % 62)) {
            if (sunset_timer < (255 - 5)) {
                // add a few minutes to the timer
                sunset_timer += 5;
                sunset_timer_peak = sunset_timer; // reset ceiling
                sunset_ticks = 0; // reset phase
                // let the user know something happened
                blink_once();
            }
        }
        return 0;
    }
    // tick: count down until time expires
    else if (event == (0b00000000|0b00000001)) {
        // time passed
        sunset_ticks ++;
        // did we reach a minute mark?
        if (sunset_ticks >= (62*60)) {
            sunset_ticks = 0;
            if (sunset_timer > 0) {
                sunset_timer --;
            }
        }
        return 0;
    }
    return 1;
}
/// version-check-mode.c   
// version-check-mode.c: Version check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
/////////////////////////////////////////////////////////////
       
// empty state; logic is handled in FSM loop() instead
uint8_t version_check_state(Event event, uint16_t arg) {
    return 1;
}
// this happens in FSM loop()
inline void version_check_iter() {
    for (uint8_t i=0; i<sizeof(version_number)-1; i++) {
        uint8_t digit = 
                       (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                       version_number + i
                       )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; })) 
                                                         - '0';
        //       digits: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
        //   hex digits: 0 1 2 3 4 5 6 7 8 9  a  b  c  d  e  f
        // 'model' file: 0 1 2 3 4 5 6 7 8 9  :  ;  <  =  >  ?
        if (digit < 16) blink_digit(digit);
        else { // "buzz" for non-numeric characters
            for(uint8_t frame=0; frame<25; frame++) {
                set_level((frame&1) << 5);
                nice_delay_ms(16);
            }
            nice_delay_ms(1000 * 8 / 12);
        }
        nice_delay_ms(300);
    }
    set_state_deferred(off_state, 0);
}
///   END   
// battcheck-mode.c: Battery check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
uint8_t battcheck_state(Event event, uint16_t arg) {
    ////////// Every action below here is blocked in the simple UI //////////
    // 1 click: off
    if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // 2 clicks: next blinky mode
    else if (event == (0b10000000|0b01000000|2)) {
        set_state(tempcheck_state, 0);
        /*  /// VER_CHECK_MODE
        /// tested on the SC31 Pro t1616 
        /// additional line in the "sofirn/sc31-pro-t1616/anduril.h" :  
            #define USE_VER_CHECK_MODE
         */
        return 0;
    }
    // 3 clicks: next channel mode (specific to number blinky modes)
    else if (event == (0b10000000|0b01000000|3)) {
        cfg.blink_channel = (cfg.blink_channel + 1) % (1 + 7);
        save_config();
        return 0;
    }
    // 7H: voltage config mode
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        push_state(voltage_config_state, 0);
        return 0;
    }
    return 1;
}
// the user can adjust the battery measurements... on a scale of 1 to 13
// 1 = subtract 0.30V
// 2 = subtract 0.25V
// ...
// 7 = no effect (add 0V)
// 8 = add 0.05V
// ...
// 13 = add 0.30V
void voltage_config_save(uint8_t step, uint8_t value) {
        if (2 == step) cfg.post_off_voltage = value;
        else
    if (value) cfg.voltage_correction = value;
}
uint8_t voltage_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
                             2,
                             voltage_config_save);
}
///   END   
// beacon-mode.c: Beacon mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
/// beacon_mode_iter
inline void beacon_mode_iter() {
    // one iteration of main loop()
    if (! button_last_state) {
        set_level(memorized_level);
        nice_delay_ms(100);
        set_level(0);
        nice_delay_ms(((cfg.beacon_seconds) * 1000) - 100);
    }
}
/// beacon_mode_iter
   /// beacon_state
uint8_t beacon_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // TODO: use sleep ticks to measure time between pulses,
    //       to save power
    // 2 clicks: next blinky mode
    else if (event == (0b10000000|0b01000000|2)) {
        set_state(battcheck_state, 0);
        return 0;
    }
    /// 1H
    // hold: configure beacon timing
    else if (event == (0b10000000|0b00100000|0b00010000|1)) {
        if (0 == (arg % 62)) {
            blink_once();
        }
        return 0;
    }
    /// 1H
    /// 1H RELEASE 
    // release hold: save new timing
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|1)) {
        cfg.beacon_seconds = 1 + (arg / 62);
        save_config();
        return 0;
    }
    /// 1H RELEASE 
    return 1;
}
   /// beacon_state
///   END   
// tempcheck-mode.c: Temperature check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
uint8_t tempcheck_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // 2 clicks: next blinky mode
    else if (event == (0b10000000|0b01000000|2)) {
        /*  /// VER_CHECK_MODE
        /// tested on the SC31 Pro t1616 
        /// additional line in the "sofirn/sc31-pro-t1616/anduril.h" :  
            #define USE_VER_CHECK_MODE
         */
        set_state(ver_check_state, 0); ///   ///   ///   ///   ///   ///   ///
        return 0;
    }
    // 7H: thermal config mode
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        push_state(thermal_config_state, 0);
        return 0;
    }
    return 1;
}
void thermal_config_save(uint8_t step, uint8_t value) {
    if (value) {
        // item 1: calibrate room temperature
        if (step == 1) {
            int8_t rawtemp = temperature - cfg.therm_cal_offset;
            cfg.therm_cal_offset = value - rawtemp;
            adc_reset = 2; // invalidate all recent temperature data
        }
        // item 2: set maximum heat limit
        else {
            cfg.therm_ceil = 30 + value - 1;
        }
    }
    if (cfg.therm_ceil > 70) cfg.therm_ceil = 70;
}
uint8_t thermal_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg,
                             2, thermal_config_save);
}
///   END   
/*   /// BEACON_MODE_ISG , FAILED
/// BEACON_MODE_ISG
 */
/*  /// VER_CHECK_MODE
        /// VERSION_CHECK_MODE in blinky group  
        /// WIP: compile and test on the SC31 Pro t1616 
        /// additional line in the "sofirn/sc31-pro-t1616/anduril.h" :  
        /// #define USE_VER_CHECK_MODE
         */
/// ver-check-mode.c
/// based on "version-check-mode.c"
// version-check-mode.c: Version check mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
uint8_t ver_check_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    }
    // 2 clicks: next blinky mode
    else if (event == (0b10000000|0b01000000|2)) {
        set_state(beacon_state, 0);
        return 0;
    }
    return 1;
}
/*  OG: 
// this happens in FSM loop()
inline void ver_check_iter() {
    for (uint8_t i=0; i<sizeof(version_number)-1; i++) {
        uint8_t digit = pgm_read_byte(version_number + i) - '0';
        //       digits: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
        //   hex digits: 0 1 2 3 4 5 6 7 8 9  a  b  c  d  e  f
        // 'model' file: 0 1 2 3 4 5 6 7 8 9  :  ;  <  =  >  ?
        if (digit < 16) blink_digit(digit);
        else {  // "buzz" for non-numeric characters
            for(uint8_t frame=0; frame<25; frame++) {
                set_level((frame&1) << 5);
                nice_delay_ms(16);
            }
            nice_delay_ms(BLINK_SPEED * 8 / 12);
        }
        nice_delay_ms(300);
    }
    set_state_deferred(off_state, 0);
}
 */
/*  Mods: 
 */
inline void ver_check_iter() {
    for (uint8_t i=0; i<sizeof(ver_number)-1; i++) {
        uint8_t digit = 
                       (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
                       ver_number + i
                       )); uint8_t __result; __asm__ __volatile__ ( "lpm %0, Z" "\n\t" : "=r" (__result) : "z" (__addr16) ); __result; })) 
                                                     - '0';
        //       digits: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
        //   hex digits: 0 1 2 3 4 5 6 7 8 9  a  b  c  d  e  f
        // 'model' file: 0 1 2 3 4 5 6 7 8 9  :  ;  <  =  >  ?
        if (digit < 16) blink_digit(digit);
        else { // "buzz" for non-numeric characters
            for(uint8_t frame=0; frame<25; frame++) {
                set_level((frame&1) << 5);
                nice_delay_ms(16);
            }
            nice_delay_ms(1000 * 8 / 12);
        }
        nice_delay_ms(700);
    }
    /* commented: VER_CHECK_MODE repeats
	 * un-commented: VER_CHECK_MODE runs once 
       set_state_deferred(off_state, 0);
     */
    /* "nice_delay" after each VER_CHECK_MODE run, 
     * (spacer/separator between VER_CHECK_MODE runs) 
     */
    nice_delay_ms(1400); ///
}
///   END   
// lockout-mode.c: Lockout mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
/// **lockout-mode.c** 
/// Mod. : more aux patterns by SammysHP . 
/// 2025-01-19 16:17  Mod. : disable Lockout-Modes  4H and 5C .   3C and 4C same as stock. 
///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   
       
uint8_t lockout_state(Event event, uint16_t arg) {
    // momentary(ish) moon mode during lockout
    // button is being held
    // don't turn on during RGB aux LED configuration
    if (event == (0b10000000|0b00100000|0b00010000|7)) { set_level(0); } else
    if ((event & (0b10000000 | 0b00010000)) == (0b10000000 | 0b00010000)) {
        // hold: lowest floor
        // click, hold: highest floor (or manual mem level)
        uint8_t lvl = cfg.ramp_floors[0];
        if (1 == (event & 0x0f)) { // first click
            if (cfg.ramp_floors[1] < lvl) lvl = cfg.ramp_floors[1];
        } else { // 2nd click or later
            if (cfg.ramp_floors[1] > lvl) lvl = cfg.ramp_floors[1];
            if (cfg.manual_memory) lvl = cfg.manual_memory;
        }
        off_state_set_level(lvl);
    }
    // button was released
    else if ((event & (0b10000000 | 0b00010000)) == (0b10000000)) {
        off_state_set_level(0);
    }
    // regular event handling
    // conserve power while locked out
    // (allow staying awake long enough to exit, but otherwise
    //  be persistent about going back to sleep every few seconds
    //  even if the user keeps pressing the button)
    if (event == (0b00000000|0b00001000)) {
        ticks_since_on = 0;
            rgb_led_update(cfg.rgb_led_lockout_mode, 0);
    }
    else if (event == (0b00000000|0b00000001)) {
        if (arg > 24) {
            go_to_standby = 1;
            rgb_led_update(cfg.rgb_led_lockout_mode, arg);
        }
        return 0;
    }
    else if (event == (0b00000000|0b00000011)) {
        if (ticks_since_on < 255) ticks_since_on ++;
        // reset to manual memory level when timer expires
        if (cfg.manual_memory &&
                (arg >= (cfg.manual_memory_timer * 450))) {
            manual_memory_restore();
        }
        rgb_led_update(cfg.rgb_led_lockout_mode, arg);
        return 0;
    }
    // 3 clicks: exit and turn off
    else if (event == (0b10000000|0b01000000|3)) {
        blink_once();
        set_state(off_state, 0);
        return 0;
    }
    // 4 clicks: exit and turn on
    else if (event == (0b10000000|0b01000000|4)) {
        set_state(steady_state, memorized_level);
        return 0;
    }
/// 2025/01/19 16:17   
/// Mod. : disable LOCKOUT-MODE's 4H and 5C   
/*
    // 4 clicks, but hold last: exit and start at floor
    else if (event == EV_click4_hold) {
        //blink_once();
        blip();
        // reset button sequence to avoid activating anything in ramp mode
        current_event = 0;
        // ... and back to ramp mode
        set_state(steady_state, 1);
        return EVENT_HANDLED;
    }
    // 5 clicks: exit and turn on at ceiling level
    else if (event == EV_5clicks) {
        set_state(steady_state, MAX_LEVEL);
        return EVENT_HANDLED;
    }
 */
    // 3H: next channel mode
    else if (event == (0b10000000|0b00100000|0b00010000|3)) {
        if (0 == (arg % 62)) {
            // pretend the user clicked 3 times to change channels
            return channel_mode_state((0b10000000|0b01000000|3), 0);
        }
    }
    ////////// Every action below here is blocked in the (non-Extended) Simple UI //////////
    // 7 clicks: change RGB aux LED pattern
    else if (event == (0b10000000|0b01000000|7)) {
        uint8_t mode = (cfg.rgb_led_lockout_mode >> 4) + 1;
        mode = mode % 6;
        cfg.rgb_led_lockout_mode = (mode << 4) | (cfg.rgb_led_lockout_mode & 0x0f);
        rgb_led_update(cfg.rgb_led_lockout_mode, 0);
        save_config();
        blink_once();
        return 0;
    }
    // 7H: change RGB aux LED color
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        setting_rgb_mode_now = 1;
        if (0 == (arg & 0x3f)) {
            uint8_t mode = (cfg.rgb_led_lockout_mode & 0x0f) + 1;
            mode = mode % RGB_LED_NUM_COLORS;
            cfg.rgb_led_lockout_mode = mode | (cfg.rgb_led_lockout_mode & 0xf0);
            //save_config();
        }
        rgb_led_update(cfg.rgb_led_lockout_mode, arg);
        return 0;
    }
    // 7H, release: save new color
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|7)) {
        setting_rgb_mode_now = 0;
        save_config();
        return 0;
    }
/// AUTOLOCK has a flag  "#ifdef USE_AUTOLOCK"  
/// easy to  #undef  in  anduril.h    
    return 1;
}
/// **lockout-mode.c** 
///   END   
// momentary-mode.c: Momentary mode for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t momentary_state(Event event, uint16_t arg) {
    // init strobe mode, if relevant
    if ((event == (0b00000000|0b00001000)) && (momentary_mode != 0)) {
        strobe_state(event, arg);
    }
    // light up when the button is pressed; go dark otherwise
    // button is being held
    if ((event & (0b10000000 | 0b00010000)) == (0b10000000 | 0b00010000)) {
        momentary_active = 1;
        // 0 = ramping, 1 = strobes
        if (momentary_mode == 0) {
            set_level(memorized_level);
        }
        return 0;
    }
    // button was released
    else if ((event & (0b10000000 | 0b00010000)) == (0b10000000)) {
        momentary_active = 0;
        set_level(0);
        //go_to_standby = 1;  // sleep while light is off
        return 0;
    }
    // Sleep, dammit!  (but wait a few seconds first)
    // (because standby mode uses such little power that it can interfere
    //  with exiting via tailcap loosen+tighten unless you leave power
    //  disconnected for several seconds, so we want to be awake when that
    //  happens to speed up the process)
    else if (event == (0b00000000|0b00000001)) {
        if (momentary_active) {
            // 0 = ramping, non-zero = strobes
            if (momentary_mode != 0) {
                return strobe_state(event, arg);
            }
        }
        else {
            // turn off lighted button
                rgb_led_set(0);
            if (arg > 62*5) { // sleep after 5 seconds
                go_to_standby = 1; // sleep while light is off
            }
        }
        return 0;
    }
    return 1;
}
// tactical-mode.c: Tactical (ish) mode for Anduril.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t tactical_state(Event event, uint16_t arg) {
    // momentary(ish) tactical mode
    uint8_t mem_lvl = memorized_level; // save this to restore it later
    uint8_t ret = 1;
    // button is being held
    if ((event & (0b10000000 | 0b00010000)) == (0b10000000 | 0b00010000)) {
        // 1H: 1st level
        // 2H: 2nd level
        // 3H: 3rd level
        // 4+: nothing
        momentary_active = 0;
        ret = 0;
        uint8_t click = event & 0x0f; // click number
        if (click <= 3) {
            momentary_active = 1;
            uint8_t lvl;
            lvl = cfg.tactical_levels[click-1];
            if ((1 <= lvl) && (lvl <= 150)) { // steady output
                memorized_level = lvl;
                momentary_mode = 0;
                    // use ramp mode's channel
                    channel_mode = cfg.channel_mode;
            } else { // momentary strobe mode
                momentary_mode = 1;
                if (lvl > 150) {
                    current_strobe_type = (lvl - 150 - 1) % strobe_mode_END;
                }
            }
        }
    }
    // button was released
    else if ((event & (0b10000000 | 0b00010000)) == (0b10000000)) {
        momentary_active = 0;
        set_level(0);
        interrupt_nice_delays(); // stop animations in progress
    }
    // delegate to momentary mode while button is pressed
    if (momentary_active) {
        momentary_state(event, arg);
    }
    memorized_level = mem_lvl; // restore temporarily overridden mem level
    // copy lockout mode's aux LED and sleep behaviors
    if (event == (0b00000000|0b00001000)) {
        lockout_state(event, arg);
    }
    else if (event == (0b00000000|0b00000001)) {
        if (! momentary_active) {
            return lockout_state(event, arg);
        }
        return 0;
    }
    else if (event == (0b00000000|0b00000011)) {
        return lockout_state(event, arg);
    }
    // handle 3C here to prevent changing channel modes unintentionally
    if (event == (0b10000000|0b01000000|3)) {
        return 0;
    }
    // 6 clicks: exit and turn off
    else if (event == (0b10000000|0b01000000|6)) {
        blink_once();
        set_state(off_state, 0);
        return 0;
    }
    ////////// Every action below here is blocked in the simple UI //////////
    // (unnecessary since this entire mode is blocked in simple UI)
    /*
    #ifdef USE_SIMPLE_UI
    if (cfg.simple_ui_active) {
        return EVENT_NOT_HANDLED;
    }
    #endif
    */
    // 7H: configure tactical mode
    else if (event == (0b10000000|0b00100000|0b00010000|7)) {
        push_state(tactical_config_state, 0);
        return 0;
    }
    return ret;
}
void tactical_config_save(uint8_t step, uint8_t value) {
    // update tac mode values
    // 3 values
    // each value is 1 to 150, or other:
    // - 1..150 is a ramp level
    // - other means "strobe mode"
    cfg.tactical_levels[step - 1] = value;
}
uint8_t tactical_config_state(Event event, uint16_t arg) {
    return config_state_base(event, arg, 3, tactical_config_save);
}
// channel-modes.c: Multi-channel functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
uint8_t channel_mode_state(Event event, uint16_t arg) {
    if (0) {}
    // it's possible that a light may need 3H but not 3C,
    // so try to detect if 3C is needed
    // 3 clicks: next channel mode
    else if (event == (0b10000000|0b01000000|3)) {
        uint8_t next = channel_mode;
        // go to next channel mode until we find one which is enabled
        // (and don't do any infinite loops if the user disabled them all)
        uint8_t count = 0;
        do {
            count ++;
            next = (next + 1) % (1 + 7);
        } while ((! ((cfg.channel_modes_enabled >> next) & 1)) && count < (1 + 7));
        //} while ((! channel_modes_enabled[next]) && count < NUM_CHANNEL_MODES);
        // undo change if infinite loop detected (redundant?)
        //if (NUM_CHANNEL_MODES == count) next = channel_mode;
        // if mode hasn't changed, abort
        if (channel_mode == next)
            return 1;
        set_channel_mode(next);
        // remember after battery changes
        cfg.channel_mode = channel_mode;
        save_config();
        return 0;
    }
    // channel toggle menu on ... 9H?
    else if (event == (0b10000000|0b00100000|0b00010000|9)) {
        push_state(channel_mode_config_state, 0);
        return 0;
    }
    return 1;
}
void channel_mode_config_save(uint8_t step, uint8_t value) {
    // 1 menu item per channel mode, to enable or disable that mode
    step --; // step is 1-based, channel modes are 0-based
    if (value) cfg.channel_modes_enabled |= (1 << step);
    else cfg.channel_modes_enabled &= ((1 << step) ^ 0xff);
}
uint8_t channel_mode_config_state(Event event, uint16_t arg) {
    uint8_t ret;
    // make config steps match channel modes
    config_color_per_step = 1;
    // 1 menu item per channel mode, to enable or disable that mode
    ret = config_state_base(
        event, arg,
        (1 + 7),
        channel_mode_config_save
        );
    // no other menu needs this
    config_color_per_step = 0;
    return ret;
}
// factory-reset.c: Factory reset functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// allows setting channel mode per animation stage,
// so it can ramp up in red then explode in white (as one example)
void factory_reset() {
    // display a warning for a few seconds before doing the actual reset,
    // so the user has time to abort if they want
    uint8_t bright;
    uint8_t reset = 1;
    // wind up to an explosion
    for (bright=0; bright<64; bright++) {
        set_level(bright);
        nice_delay_ms((2500/64)/2);
        set_level(bright>>1);
        nice_delay_ms((2500/64)/2);
        if (! button_is_pressed()) {
            reset = 0;
            break;
        }
    }
    // explode, if button pressed long enough
    if (reset) {
        // auto-calibrate temperature
        // AVR 1-Series has factory calibrated thermal sensor, always remove the offset on reset
        // this will cancel out the offset
        thermal_config_save(1, temperature - cfg.therm_cal_offset);
        // save all settings to eeprom
        // (assuming they're all at default because we haven't loaded them yet)
        save_config();
        // explosion animation
        bright = 150;
        for (; bright > 0; bright--) {
            set_level(bright);
            nice_delay_ms((2500/64)/8);
        }
    }
    // explosion cancelled, fade away
    else {
        for (; bright > 0; bright--) {
            set_level(bright);
            nice_delay_ms((2500/64)/3);
        }
    }
}
// strobe-modes.c: Strobe modes for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
/*   /// 
 */
/*   /// BUTTON CLICKS, HOLD, etc
/// starryalley OG BUTTON CLICKS, HOLD, etc
    /// 1C: off
    /// 2C: rotate through strobe/flasher modes
    /// 3C: rotate through channel modes for the current strobe
    /// 4C: rotate backward through strobe/flasher modes
    /// 1H: change speed (go faster)  or change brightness (brighter)
        // party / tactical strobe faster
        // biking mode brighter
        /// broken fluorescent mode brighter
    /// 2H: change speed (go slower)  or change brightness (dimmer)
        // party / tactical strobe slower
        // biking mode dimmer
        /// broken fluorescent dimmer
    /// 5C: go to momentary mode (momentary strobe)
    /// 6C: turning down busy factor (less busy) of lightning mode,
    //  or turning down firework brightness by 12,
    //  or decrease lighthouse delay by 1 sec
    /// 7C: turning up busy factor (busier) of lightning mode,
    //  or turning up firework brightness by 12,
    //  or increasing lighthouse delay by 1 sec
    /// 8C: reset lightning busy factor to default,
    //  or reset firework brightness to default
    //  or reset lighthouse delay to default
 */
/*   /// BUTTON CLICKS, HOLD, etc. WITH REMAP 
/// starryalley Anduril2, New-repo. strobe-modes.c,
/// WITH REMAP BUTTON CLICKS, HOLD, etc.
    /// 1C: off
    /// 2C: rotate through strobe/flasher modes
    /// 3C: rotate backward through strobe/flasher modes
    /// 1H: // party / tactical strobe faster
            // biking mode brighter
            /// broken fluorescent mode brighter
    /// 2H: // party / tactical strobe slower
            // biking mode dimmer
            /// broken fluorescent dimmer
    /// 4C: turning down busy factor (less busy) of lightning mode,
    //  or turning down firework brightness by 12,
    //  or decrease lighthouse delay by 1 sec
    /// 5C: turning up busy factor (busier) of lightning mode,
    //  or turning up firework brightness by 12,
    //  or increasing lighthouse delay by 1 sec
    /// 6C: reset lightning busy factor to default,
    //  or reset firework brightness to default
    //  or reset lighthouse delay to default
    /// 7C: rotate through channel modes for the current strobe
    /// 8C: go to momentary mode (momentary strobe)
 */
/*   /// strobe-modes, PSEUDO_RAND users: 
/// LIGHTNING_MODE
/// CANDLE_MODE
/// FIREWORK_MODE
/// BROKEN_FLUORESCENT_MODE
 */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
uint8_t strobe_state(Event event, uint16_t arg) {
    static int8_t ramp_direction = 1;
    // 'st' reduces ROM size slightly
    strobe_mode_te st = current_strobe_type;
    momentary_mode = 1; // 0 = ramping, 1 = strobes
    /// beacon-mode-isg
    /// beacon-mode-isg
    if (0) {} // placeholder
    // init anything which needs to be initialized
    else if (event == (0b00000000|0b00001000)) {
        current_strobe_type = cfg.strobe_type;
        ramp_direction = 1;
        return 0;
    }
    ///   ///   ///   ///   ///   ///   ///   ///   ///
    /// BUTTON CLICKS, HOLD, etc
    /// 1C
    // 1 click: off
    else if (event == (0b10000000|0b01000000|1)) {
        set_state(off_state, 0);
        return 0;
    } /// 1C
    /// 1C
    /// 2C 
    // 2 clicks: rotate through strobe/flasher modes
    else if (event == (0b10000000|0b01000000|2)) {
        current_strobe_type = cfg.strobe_type = (st + 1) % strobe_mode_END;
        save_config();
        return 0;
    } /// 2C 
    /// 2C 
    /// 7C 
    /// 7C: rotate through channel modes for the current strobe
    // OG: 3 clicks: rotate through channel modes for the current strobe
    /// Mod 7C: rotate through channel modes for the current strobe
    else if (event == (0b10000000|0b01000000|7)) {
        // TODO: maybe skip aux modes?
        set_channel_mode((channel_mode + 1) % (1 + 7));
        cfg.strobe_channels[st] = channel_mode;
        save_config();
        return 0;
    }
    /// 7C
    /// 3C
    /// 3C: rotate back through strobe/flasher modes 
    // OG: 4 clicks: rotate backward through strobe/flasher modes
    else if (event == (0b10000000|0b01000000|3)) {
        current_strobe_type = cfg.strobe_type = (st - 1 + strobe_mode_END) % strobe_mode_END;
        save_config();
        return 0;
    } /// 3C
    /// 3C
    /// 1H
    // hold: change speed (go faster)
    //       or change brightness (brighter)
    else if (event == (0b10000000|0b00100000|0b00010000|1)) {
        if (0) {} // placeholder
        // party / tactical strobe faster
        else if (st <= tactical_strobe_e) {
            if ((arg & 1) == 0) {
                uint8_t d = cfg.strobe_delays[st];
                d -= ramp_direction;
                if (d < 8) d = 8;
                else if (d > 254) d = 254;
                cfg.strobe_delays[st] = d;
            }
        }
        /// party / tactical strobe faster
        // lightning has no adjustments
        //else if (st == lightning_storm_e) {}
        // biking mode brighter
        else if (st == bike_flasher_e) {
            cfg.bike_flasher_brightness += ramp_direction;
            if (cfg.bike_flasher_brightness < 2) cfg.bike_flasher_brightness = 2;
            else if (cfg.bike_flasher_brightness > 120) cfg.bike_flasher_brightness = 120;
            set_level(cfg.bike_flasher_brightness);
        }
        // biking mode brighter
        /// broken fluorescent mode brighter
        /// broken fluorescent mode brighter
        /// 2025-02-10
        /// BEACONN_MODE
        /// 1H: configure beacon timing
        else if (st == beaconn_mode_e) {
            cfg.beaconn_seconds = 1 + (arg / 62);
            if (0 == (arg % 62)) {
                blink_once();
            }
        }
        return 0;
    }
    /// 1H RELEASE
    // reverse ramp direction on hold release
    // ... and save new strobe settings
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|1)) {
        ramp_direction = -ramp_direction;
        save_config();
        return 0;
    } /// 1H RELEASE
    /// 1H RELEASE
    /// 2H 
    // click, hold: change speed (go slower)
    //       or change brightness (dimmer)
    else if (event == (0b10000000|0b00100000|0b00010000|2)) {
        ramp_direction = 1;
        if (0) {} // placeholder
        // party / tactical strobe slower
        else if (st <= tactical_strobe_e) {
            if ((arg & 1) == 0) {
                if (cfg.strobe_delays[st] < 255) cfg.strobe_delays[st] ++;
            }
        }
        /// #ifdef USE_TACTICAL_STROBE_MODE 
        /// party / tactical strobe slower
        // lightning has no adjustments
        //else if (st == lightning_storm_e) {}
        // biking mode dimmer
        else if (st == bike_flasher_e) {
            if (cfg.bike_flasher_brightness > 2)
                cfg.bike_flasher_brightness --;
            set_level(cfg.bike_flasher_brightness);
        }
        /// biking mode dimmer
        /// broken fluorescent dimmer
        /// broken fluorescent dimmer
        return 0;
    }
    /// 2H 
    /// 2H RELEASE
    // release hold: save new strobe settings
    else if (event == (0b10000000|0b00100000|0b00000000|0b01000000|2)) {
        save_config();
        return 0;
    }
    /// 2H RELEASE
    /// 8C 
    /// 8C: go to momentary mode (momentary strobe)
    // OG: 5 clicks: go to momentary mode (momentary strobe)
    /// 8C    /// momentary mode is DISABLED in most target configs
    // clock tick: bump the random seed
    else if (event == (0b00000000|0b00000001)) {
        // un-reverse after 1 second
        if (arg == 1) ramp_direction = 1;
        pseudo_rand_seed += arg;
        return 0;
    }
    /// else if (event == EV_tick) {
    /// 4C: turning down busy factor (less busy) of LIGHTNING mode,
    //  or turning down FIREWORK brightness by 12,
    //  or decrease LIGHTHOUSE delay by 1 sec
    else if (event == (0b10000000|0b01000000|4)) {
        if (0) {} // placeholder
        else if (st == lightning_storm_e) {
            cfg.lightning_busy_factor++;
            if (cfg.lightning_busy_factor > 16)
                cfg.lightning_busy_factor = 16;
            save_config();
            blink_once();
        }
        else if (st == firework_mode_e) {
            cfg.firework_brightness -= 12;
            if (cfg.firework_brightness < 31)
                cfg.firework_brightness = 31;
            save_config();
            blink_once();
        }
        else if (st == lighthouse_mode_e) {
            if (cfg.lighthouse_delay > 0)
                cfg.lighthouse_delay--;
            save_config();
            blink_once();
        }
        return 0;
    } /// 4C 
    /// 4C 
    /// 5C
    // 5C: turning up busy factor (busier) of LIGHTNING mode,
    //  or turning up FIREWORK brightness by 12,
    //  or increasing LIGHTHOUSE delay by 1 sec
    else if (event == (0b10000000|0b01000000|5)) {
        if (0) {} // placeholder
        else if (st == lightning_storm_e) {
            cfg.lightning_busy_factor--;
            if (cfg.lightning_busy_factor < 12)
                cfg.lightning_busy_factor = 12;
            save_config();
            blink_once();
        }
        else if (st == firework_mode_e) {
            cfg.firework_brightness += 12;
            if (cfg.firework_brightness > 150)
                cfg.firework_brightness = 150;
            save_config();
            blink_once();
        }
        else if (st == lighthouse_mode_e) {
            if (cfg.lighthouse_delay < 30)
                cfg.lighthouse_delay++;
            save_config();
            blink_once();
        }
        return 0;
    } /// 5C
    /// 5C
    /// 6C
    // 6C: reset LIGHTNING busy factor to default,
    //  or reset FIREWORK brightness to default
    //  or reset LIGHTHOUSE delay to default
    else if (event == (0b10000000|0b01000000|6)) {
        if (0) {} // placeholder
        else if (st == lightning_storm_e) {
            cfg.lightning_busy_factor = 14;
            save_config();
            blink_once();
        }
        else if (st == firework_mode_e) {
            cfg.firework_brightness = 121;
        }
        else if (st == lighthouse_mode_e) {
            cfg.lighthouse_delay = 5;
        }
        /// return MISCHIEF_MANAGED;
        return 0;
    } /// 6C
    /// 6C
    /// #if defined(USE_LIGHTNING_MODE) || defined(USE_CANDLE_MODE)
    return 1; /// 
} ///   ///   /// 
   ///   ///   /// 
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
/// FSM LOOP
/// STROBE_STATE_ITER
// runs repeatedly in FSM loop() whenever UI is in strobe_state or momentary strobe
inline void strobe_state_iter() {
    uint8_t st = current_strobe_type; // can't use switch() on an enum
        // remember channel mode for each strobe
        channel_mode = cfg.strobe_channels[st];
    /// THE SWITCH 
    switch(st) {
        case party_strobe_e:
        case tactical_strobe_e:
            party_tactical_strobe_mode_iter(st);
            break;
        case police_color_strobe_e:
            police_color_strobe_iter();
            break;
        case lightning_storm_e:
            lightning_storm_iter();
            break;
        /// 2025-02-11
        /// BEACONN_MODE
        case beaconn_mode_e:
            beaconn_mode_iter();
            break;
        case bike_flasher_e:
            bike_flasher_iter();
            break;
        case firework_mode_e:
            firework_iter();
            break;
        case lighthouse_mode_e:
            lighthouse_iter();
            break;
    }
    /// THE SWITCH 
}
/// STROBE_STATE_ITER
/// ifdef USE_STROBE_STATE ???
/// VARIOUS STROBE MODES ITER
/// party_tactical_strobe_mode_iter
inline void party_tactical_strobe_mode_iter(uint8_t st) {
    // one iteration of main loop()
    uint8_t del = cfg.strobe_delays[st];
    // TODO: make tac strobe brightness configurable?
    set_level(150);
    if (0) {} // placeholder
    else if (st == party_strobe_e) { // party strobe
        if (del < 42) _delay_zero();
        else nice_delay_ms(1);
    }
    else { //tactical strobe
        nice_delay_ms(del >> 1);
    }
    set_level(0);
    nice_delay_ms(del); // no return check necessary on final delay
}
/// party_tactical_strobe_mode_iter
/// police_color_strobe_iter
inline void police_color_strobe_iter() {
    // one iteration of main loop()
    uint8_t del = 66;
    // TODO: make police strobe brightness configurable
    uint8_t bright = memorized_level;
    //uint8_t channel = channel_mode;
    for (uint8_t i=0; i<10; i++) {
        if (0 == i) set_channel_mode(CM_AUXRED);
        else if (5 == i) set_channel_mode(CM_AUXBLU);
        set_level(bright);
        nice_delay_ms(del >> 1);
        set_level(0);
        nice_delay_ms(del);
    }
    // restore the channel when done
    //set_channel_mode(channel);
    channel_mode = cfg.channel_mode;
}
/// police_color_strobe_iter
/// lightning_storm_iter
inline void lightning_storm_iter() {
    // one iteration of main loop()
    int16_t brightness;
    uint16_t rand_time;
    // turn the emitter on at a random level,
    // for a random amount of time between 1ms and 32ms
    //rand_time = 1 << (pseudo_rand() % 7);
    rand_time = pseudo_rand() & 63;
    brightness = 1 << (pseudo_rand() % 7); // 1, 2, 4, 8, 16, 32, 64
    brightness += 1 << (pseudo_rand() % 5); // 2 to 80 now
    brightness += pseudo_rand() % brightness; // 2 to 159 now (w/ low bias)
    if (brightness > 150) brightness = 150;
    set_level(brightness);
    nice_delay_ms(rand_time);
    // decrease the brightness somewhat more gradually, like lightning
    uint8_t stepdown = brightness >> 3;
    if (stepdown < 1) stepdown = 1;
    while(brightness > 1) {
        nice_delay_ms(rand_time);
        brightness -= stepdown;
        if (brightness < 0) brightness = 0;
        set_level(brightness);
        /*
           if ((brightness < MAX_LEVEL/2) && (! (pseudo_rand() & 15))) {
           brightness <<= 1;
           set_level(brightness);
           }
           */
        if (! (pseudo_rand() & 3)) {
            nice_delay_ms(rand_time);
            set_level(brightness>>1);
        }
    }
    // turn the emitter off,
    // for a random amount of time between 1ms and 8192ms (default busy factor)
    // (with a low bias)
    rand_time = 1 << (pseudo_rand() % cfg.lightning_busy_factor);
    rand_time += pseudo_rand() % rand_time;
    set_level(0);
    nice_delay_ms(rand_time); // no return check necessary on final delay
}
/// lightning_storm_iter
/// bike_flasher_iter
inline void bike_flasher_iter() {
    // one iteration of main loop()
    uint8_t burst = cfg.bike_flasher_brightness << 1;
    if (burst > 150) burst = 150;
    for(uint8_t i=0; i<4; i++) {
        set_level(burst);
        nice_delay_ms(5 + 0);
        set_level(cfg.bike_flasher_brightness);
        nice_delay_ms(65);
    }
    nice_delay_ms(720); // no return check necessary on final delay
    set_level(0);
}
/// bike_flasher_iter
/// FIREWORK_MODE
/// firework_iter
uint8_t firework_stage = 0;
uint8_t firework_stage_count = 64;
uint8_t step_interval = (2500/64);
// code is copied and modified from factory-reset.c
inline void firework_iter() {
    if (firework_stage == firework_stage_count) {
        // explode, and reset stage
        firework_stage = 0;
        for (uint8_t brightness = cfg.firework_brightness; brightness > 0; brightness--) {
            set_level(brightness);
            nice_delay_ms(step_interval/4);
            set_level((uint16_t)brightness*7/8);
            nice_delay_ms(step_interval/(1+(pseudo_rand()%5)));
        }
        // off for 1 to 5 seconds
        set_level(0);
        nice_delay_ms(1000 + (pseudo_rand() % 5) * 1000);
        // set next stage count (16 to 64 in increment of 8)
        firework_stage_count = 16 + 8 * (pseudo_rand() % 7);
        return;
    }
    // wind up to explode
    set_level(firework_stage);
    nice_delay_ms(step_interval/3);
    set_level((uint16_t)firework_stage*2/3);
    nice_delay_ms(step_interval/3);
    firework_stage++;
    // we've reached our max brightness for firework mode, let's explode in the next iteration
    if (firework_stage > cfg.firework_brightness)
        firework_stage = firework_stage_count;
}
/// firework_iter
/// LIGHTHOUSE_MODE
/// lighthouse_iter
// phase is between 0~255, returns MAX_LEVEL at 128 and 1 at both ends
uint8_t lighthouse_intensity(uint8_t phase) {
    if (phase > 127)
        phase = 256 - phase;
    const uint64_t maxOutput = 150 - 1;
    // power of 4 (quartic function)
    return (uint8_t)(maxOutput * phase / 128 * phase / 128 * phase / 128 * phase / 128) + 1;
}
inline void lighthouse_iter() {
    uint8_t brightness = lighthouse_intensity(lighthouse_phase++);
    set_level(brightness);
    if (lighthouse_phase == 0) {
        set_level(0);
        nice_delay_ms(1000 * cfg.lighthouse_delay);
    } else
        nice_delay_ms(10 + cfg.lighthouse_delay);
}
/// lighthouse_iter
/// BROKEN_FLUORESCENT_MODE
/// bad_fluorescent_iter
/// bad_fluorescent_iter
/// 2025-02-11
/// BEACONN_MODE works very well
inline void beaconn_mode_iter() {
    // one iteration of main loop()
    if (! button_last_state) {
        /// set_level(memorized_level);
        set_level(cfg.beaconn_brightness);
        nice_delay_ms(100);
        set_level(0);
        nice_delay_ms(((cfg.beaconn_seconds) * 1000) - 100);
    }
}
/// beaconn_mode_iter
/*   /// 
 */
/*   /// 
 */
///   ///   ///   ///   ///   ///   ///   ///   ///   ///
///   END   
// smooth-steps.c: Smooth step adjustments for Anduril.
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
       
// one iteration of main loop()
void smooth_steps_iter() {
    if (actual_level == smooth_steps_target) {
        set_level(smooth_steps_target);
        smooth_steps_in_progress = 0;
        // restore prev_level when animation ends
        prev_level = smooth_steps_start;
    }
    else if (smooth_steps_target > actual_level) {
        // power-linear(ish) ascent
        // (jump by ~20% of remaining distance on each frame)
        uint8_t diff = smooth_steps_target - actual_level;
        uint8_t this = diff / smooth_steps_speed;
        if (!this) this = 1;
        set_level(actual_level + this);
        nice_delay_ms(10);
    } else {
        // ramp-linear descent
        // (jump by 1 on each frame, frame rate gives constant total time)
        uint8_t diff = smooth_steps_start - smooth_steps_target;
        uint16_t delay = 1 + (30 * smooth_steps_speed / diff);
        set_level(actual_level - 1);
        // TODO? if delay < one PWM cycle, this can look a little weird
        nice_delay_ms(delay);
    }
}
void set_level_smooth(uint8_t level, uint8_t speed) {
    smooth_steps_target = level;
    smooth_steps_speed = speed; // higher = slower
    smooth_steps_in_progress = 1;
    // for setting prev_level after animation ends
    smooth_steps_start = actual_level;
}
// runs one time at boot, when power is connected
void setup() {
        // regular e-switch light, no hard clicky power button
            // blink at power-on to let user know power is connected
            blink_once();
        if (button_is_pressed())
            factory_reset();
        load_config();
        // without this, initial boot-up brightness is wrong
        // when manual mem is enabled with a non-zero timer
        if (cfg.manual_memory) manual_memory_restore();
        // add channel mode functions underneath every other state
        push_state(channel_mode_state, 0);
        push_state(off_state, 1);
}
// runs repeatedly whenever light is "on" (not in standby)
void loop() {
    // "current_state" is volatile, so cache it to reduce code size
    StatePtr state = current_state;
    if (0) {} // placeholder
    else if (state == version_check_state) {
        version_check_iter();
    }
    else if ((state == strobe_state)
         // also handle momentary strobes
         || ((0
              || (state == tactical_state)
             )
             && (momentary_mode == 1) && (momentary_active))
         ) {
        strobe_state_iter();
    }
    else if (state == battcheck_state) {
        nice_delay_ms(1000); // wait a moment for a more accurate reading
        battcheck();
    }
    // TODO: blink out therm_ceil during thermal_config_state?
    else if (state == tempcheck_state) {
        blink_num(temperature);
        nice_delay_ms(1000);
    }
    else if (state == beacon_state) {
        beacon_mode_iter();
    }
/*   /// BEACON_MODE_ISG didnt work
    /// 2025-02-10 
    /// BEACON_MODE_ISG
    #ifdef USE_BEACON_MODE_ISG
    else if (state == beacon_mode_isg_state) {
        beacon_mode_isg_iter();
    }
    #endif
 */
    /*  /// VER_CHECK_MODE
        /// VERSION_CHECK_MODE in blinky group  
        /// WIP: compile and test on the SC31 Pro t1616 
        /// additional line in the "sofirn/sc31-pro-t1616/anduril.h" :  
        /// #define USE_VER_CHECK_MODE
     */
    else if (state == ver_check_state) {
        ver_check_iter();
    }
    else if (cfg.smooth_steps_style && smooth_steps_in_progress) {
        smooth_steps_iter();
    }
    else {
        // doze until next clock tick
        idle_mode();
    }
}
// instead of handling EV_low_voltage in each mode,
// it's handled globally here to make the code smaller and simpler
void low_voltage() {
    // "current_state" is volatile, so cache it to reduce code size
    StatePtr state = current_state;
    // TODO: turn off aux LED(s) when power is really low
    if (0) {} // placeholder
    // "step down" from strobe to something low
    else if (state == strobe_state) {
        set_state(steady_state, 150/6);
    }
    // in normal mode, step down or turn off
    else if (state == steady_state) {
        if (actual_level > 1) {
            uint8_t lvl = (actual_level >> 1) + (actual_level >> 2);
            set_level_and_therm_target(lvl);
        }
        else {
            set_state(off_state, 0);
        }
    }
    // all other modes, just turn off when voltage is low
    else {
        set_state(off_state, 0);
    }
}
///   END   
