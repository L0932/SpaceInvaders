// Copyright (C) 2004-2009 Joe Linhoff - All Rights Reserved
// gptypes.h -- public interface to library
#ifndef GPTYPES_H
#define GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //
   
// notes:
// - tab size 3, spaces
// - add int main_nobrk=0; in your code
// - defines:
//   BUILD_MSVC or BUILD_GCC to set build environment
//   BUILD_LIB -- build static .lib v. .dll
//   GP_EXPORTS -- when building .dll, build exports
//   _CRT_SECURE_NO_DEPRECATE -- use standard C
//   DEBUG=1 or 0 --
//   WIN32_LEAN_AND_MEAN
// - with linking errors and warnings involving main_nobrk, consider 
//   setting BUILD_LIB to prevent GP_API expanding into a dll import/export

#if !(BUILD_MSVC|BUILD_GCC)
#error -- define BUILD_MSVC or other in proprocessor
#endif // BUILD_

//#pragma once

///////////////////////////////////////////////////////////////////////////////
// BASE TYPES

// base types
typedef signed char int8; // 8 bit signed int
typedef unsigned char uns8; // 8 bit unsigned int
typedef uns8 bit; // 1 or 0; 8 bit unsigned
typedef char chr; // character for internal strings; 8 bit unsigned
typedef signed short int16; // 16 bit signed int
typedef unsigned short uns16; // 16 bit unsigned int
typedef signed int int32; // 32 bit signed int
typedef int32 off32; // all offsets are from their adr base
typedef unsigned int uns32; // 32 bit unsigned bit
typedef unsigned int uns; // unsigned natural int
typedef float flt32; // 32 bit float
typedef double flt64; // 64 bit float
typedef void* ptr; // pointer
typedef signed long long int64; // 64 bit signed int
typedef unsigned long long uns64; // 64 bit unsigned int

typedef uns qeObj; // reflective type

// macros
#define ret(_r_) if((r=(_r_))||1) goto BAIL
#define bret(_r_) if(((r=(_r_))||1)&&BRK()) goto BAIL
#define bbail() if(BRK()) goto BAIL
#define NUM(_a_) (sizeof(_a_)/sizeof(_a_[0])) ///< number of entries
#define NUL 0L
#define PI 3.14159265358979323846264338327950288419716939937510
#define TWOPI (2.0*PI)
#define ALIGN(_n_,_m_) ((((uns)_n_)+(_m_))&~(_m_))
#define M_ALIGN_DEFAULT 7

#define DEGTORAD(_deg_) (((_deg_)*PI)/180.0)
#define RADTODEG(_rad_) (((_rad_)*180.0)/PI)

#define PTR_ADD(_p_,_i_) (void*)(((uns8*)(_p_))+(_i_))
#define PTR_SUB(_p_,_i_) (void*)(((uns8*)(_p_))-(_i_))
#define PTR_DIFF(_p1_,_p2_) ((uns8*)(_p1_)-(uns8*)(_p2_))
#define PTR_ALIGN(_p_,_m_) (((uns8*)0)+(((uns)(_p_)+(_m_))&~(_m_)))

#define S_SZCHR_SIZE 0 // shift for character size
#define FLOATS_PASSED_AS double

#define MIN_INT8 (-128) // min int8
#define MAX_INT8 0x7f // max int8
#define MAX_UNS8 0xff // max uns8
#define MIN_INT16 (-32768) // min int16
#define MAX_INT16 0x7fff // max int16
#define MAX_UNS16 0xffff // max uns16
#define MIN_INT32 (-((int)2147483648)) // min int32
#define MAX_INT32 0x7fffffff // max int32
#define MAX_UNS32 0xffffffff // max uns32
#define MAX_UNS ((uns)~0) // max uns
#define MAX_INT 0x7fffffff // max int
#define MIN_INT (-((int)2147483648)) // min int
#define FLT_NAN 0x7FFFFFFF // not a number
#define DBL_NAN 0x7FFFFFFFE0000000 // not a number
#define FLT_INF 0x7F800000 // infinity
#define FLT_NINF 0xFF800000 // negative infinity
#define SET_FLT(_f_,_i_) (*((uns*)&(_f_))=(_i_))
#define IS_FLT(_f_,_i_) (*((uns*)&(_f_))==(_i_))
#define DBL_INF 0x000000007FF00000 // infinity
#define DBL_NINF 0x00000000FFF00000 // negative infinity
#define IS_FLT_NAN(_f_) (*((uns*)&(_f_))==FLT_NAN) // test float
#define IS_DBL_NAN(_f_) (*((uns64*)&(_f_))==DBL_NAN) // test double
#define EPSILON 0.00001
#define EPSILOW 0.000001
#define EPSILONE (EPSILON+1)

#define C_BLANK  0x01 // blank
#define C_SELALL 0x01 // select all
#define C_SPEC   0x02 // special character
#define C_COPY   0x03 // ctl-c copy
#define C_BS     0x08 // backspace
#define C_TAB    0x09 // tab
#define C_LF     0x0A // line feed
#define C_CR     0x0D // carriage return
#define C_PASTE  0x16 // ctl-v paste
#define C_CUT    0x18 // ctl-x cut
#define C_ESC    0x1b // escape
#define C_DEL    0x7f // delete
#define M_C_ENC  0x80 // encoded bit
#define C_HOME   0x81 // home
#define C_END    0x82 // end
#define C_LEFT   0x83 // left arrow
#define C_RIGHT  0x84 // right arrow
#define C_UP     0x85 // up arrow
#define C_DOWN   0x86 // down arrow

#define C_IS_PRINTABLE(_c_) (((_c_)>=0x20)&&((_c_)<=0xff))

#ifndef GP_API
// define BUILD_LIB to build/use static .libs, otherwise .dll will build
// w/dlls, define GP_EXPORTS to def, ndef GP_EXPORTS to ref 
#if BUILD_LIB
   #define GP_API extern
#elif BUILD_MSVC
   #ifdef GP_EXPORTS
      #define GP_API __declspec(dllexport)
   #else // ndef GP_EXPORTS
      #define GP_API __declspec(dllimport)
   #endif // ndef GP_EXPORTS
#else // !BUILD_MSVC
   #define GP_API extern
#endif // !BUILD_MSVC
#endif // ndef GP_API

GP_API int main_nobrk;

#if DEBUG
   #if BUILD_MSVC
   #define BRK() (main_nobrk?1:__debugbreak(),1)
   #else // !BUILD_MSVC
   #define BRK() (1)
   #endif // !BUILD_MSVC
#else // !DEBUG
   #define BRK() (1)
#endif // !DEBUG

#if BUILD_MSVC
   #if _MSC_FULL_VER >= 140050320
   #define DEPRECATED __declspec(deprecated("Depricated."))
   #else // old MSVC
   #define DEPRECATED __declspec(deprecated())
   #endif // old MSVC
#else // !BUILD_MSVC
   #define DEPRECATED
#endif // !BUILD_MSVC

// nonsense to get the filename & line -- not portable
// use: #pragma message(__FILELINE__ " : warning: fix this")
#define PREPROC2(x) #x
#define PREPROC1(xx) PREPROC2(xx)
#define __FILELINE__ __FILE__ "(" PREPROC1(__LINE__) ")"

// simple, inline clear
#define MEMZ(x) {int i=0;uns8 *d=(uns8*)&(x);for(;i<sizeof(x);i++)*d++=0;}

// function types
// void int uns flt ptr
typedef void (*fnc_v)(void);
typedef void (*fnc_vv)(void);
typedef void (*fnc_viiii)(int,int,int,int);
typedef void (*fnc_vp)(void*);
typedef void (*fnc_vpp)(void*,void*);
typedef void (*fnc_vpu)(void*,uns);
typedef void (*fnc_vpup)(void*,uns,void*);
typedef void (*fnc_vppu)(void*,void*,uns);
typedef void (*fnc_vpuu)(void*,uns,uns);
typedef void (*fnc_vppp)(void*,void*,void*);

typedef int (*fnc_iiiii)(int,int,int,int);

typedef int (*fnc_iv)(void);
typedef int (*fnc_ip)(void*);
typedef int (*fnc_iu)(uns);
typedef int (*fnc_ii)(int);
typedef int (*fnc_ipp)(void*,void*);
typedef int (*fnc_ippi)(void*,void*,int);
typedef int (*fnc_ippp)(void*,void*,void*);
typedef int (*fnc_ipppp)(void*,void*,void*,void*);

typedef int (*fnc_ipppi)(void*,void*,void*,int);
typedef int (*fnc_ipppu)(void*,void*,void*,uns);
typedef int (*fnc_ipppuu)(void*,void*,void*,uns,uns);

typedef int (*fnc_ipi)(void*,int);
typedef int (*fnc_ipia)(void*,int,...);

typedef int (*fnc_ippu)(void*,void*,uns);
typedef int (*fnc_ippa)(void*,void*,...);
typedef int (*fnc_iipa)(int,void*,...);

typedef int (*fnc_ipa)(void*,...);
typedef int (*fnc_ipu)(void*,uns);
typedef int (*fnc_ipua)(void*,uns,...);
typedef int (*fnc_ipup)(void*,uns,void*);
typedef int (*fnc_ipupp)(void*,uns,void*,void*);
typedef int (*fnc_ipuuu)(void*,uns,uns,uns);
typedef int (*fnc_ipuuup)(void*,uns,uns,uns,void*);

typedef int (*fnc_ipipp)(void*,int,void*,void*);
typedef int (*fnc_ipipa)(void*,int,void*,...);
typedef int (*fnc_ipipppp)(void*,int,void*,void*,void*,void*);

typedef int (*fnc_iia)(int,...);
typedef int (*fnc_iii)(int,int);
typedef int (*fnc_iip)(int,void*);
typedef int (*fnc_iiip)(int,int,void*);
typedef int (*fnc_iipp)(int,void*,void*);
typedef int (*fnc_iua)(uns,...);

typedef void* (*fnc_pu)(uns);

typedef void* (*fnc_pp)(void*);
typedef uns  (*fnc_up)(void*);

///////////////////////////////////////////////////////////////////////////////
// SYSTEM MACROS & DEFINES

#define C1(_a_) (_a_)
#define C2(_a_,_b_) ((_b_)<<8|(_a_))
#define C3(_a_,_b_,_c_) ((_c_)<<16|(_b_)<<8|(_a_))
#define C4(_a_,_b_,_c_,_d_) ((_d_)<<24|(_c_)<<16|(_b_)<<8|(_a_))
#define C4_0(_n_) ((_n_)&0xff)
#define C4_1(_n_) (((_n_)>>8)&0xff)
#define C4_2(_n_) (((_n_)>>16)&0xff)
#define C4_3(_n_) (((_n_)>>24)&0xff)

#define C4_CHR0(_c4_) ((_c4_)&0xff)
#define C4_CHR1(_c4_) (((_c4_)>>8)&0xff)
#define C4_CHR2(_c4_) (((_c4_)>>16)&0xff)
#define C4_CHR3(_c4_) (((_c4_)>>24)&0xff)

#define SET2(_d_,_s1_,_s2_) (_d_)[0]=(_s1_),(_d_)[1]=(_s2_)
#define SET3(_d_,_s1_,_s2_,_s3_) (_d_)[0]=(_s1_), \
   (_d_)[1]=(_s2_),(_d_)[2]=(_s3_)
#define SET4(_d_,_s1_,_s2_,_s3_,_s4_) (_d_)[0]=(_s1_), \
   (_d_)[1]=(_s2_),(_d_)[2]=(_s3_),(_d_)[3]=(_s4_)
#define SET9(_d_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_,_s7_,_s8_,_s9_) \
   (_d_)[0]=(_s1_),(_d_)[1]=(_s2_),(_d_)[2]=(_s3_), \
   (_d_)[3]=(_s4_),(_d_)[4]=(_s5_),(_d_)[5]=(_s6_), \
   (_d_)[6]=(_s7_),(_d_)[7]=(_s8_),(_d_)[8]=(_s9_)
#define SET12(_d_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_,_s7_,_s8_,_s9_,_s10_,_s11_,_s12_) \
   (_d_)[0]=(_s1_),(_d_)[1]=(_s2_),(_d_)[2]=(_s3_), \
   (_d_)[3]=(_s4_),(_d_)[4]=(_s5_),(_d_)[5]=(_s6_), \
   (_d_)[6]=(_s7_),(_d_)[7]=(_s8_),(_d_)[8]=(_s9_), \
   (_d_)[9]=(_s10_),(_d_)[10]=(_s11_),(_d_)[11]=(_s12_)

#define CPY2(_d_,_s_) (_d_)[0]=(_s_)[0],(_d_)[1]=(_s_)[1]
#define CPY3(_d_,_s_) (_d_)[0]=(_s_)[0],(_d_)[1]=(_s_)[1],(_d_)[2]=(_s_)[2]
#define CPY4(_d_,_s_) (_d_)[0]=(_s_)[0],(_d_)[1]=(_s_)[1],(_d_)[2]=(_s_)[2],(_d_)[3]=(_s_)[3]

///////////////////////////////////////////////////////////////////////////////
// VARIABLE ARGUMENT

typedef uns8 *vargs;
#define VARG_SIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define varg_start(ap,v) (ap = (vargs)&v + VARG_SIZEOF(v))
#define varg_next(ap,t) (*(t *)((ap += VARG_SIZEOF(t)) - VARG_SIZEOF(t)))
#define varg_prev(argp,type) (*(type *)((argp -= VARG_SIZEOF(type)) - VARG_SIZEOF(type)))
#define varg_end(x)

///////////////////////////////////////////////////////////////////////////////

#if BUILD_MSVC
#pragma warning(disable:4018) // '==' : signed/unsigned mismatch
#pragma warning(disable:4047) // differs in levels of indirection
#pragma warning(disable:4133) // incompatible types - from 'uno *__w64 ' to 'xx *'
#pragma warning(disable:4244) // '=' : conversion from '__w64 int' to 'int', possible loss of data
#pragma warning(disable:4305) // '=' : truncation from 'double' to
#pragma warning(disable:4311) // 'type cast' : pointer truncation from 'vpt' to 'int'
#pragma warning(disable:4761) // integral size mismatch in argument; conversion supplied
#endif // BUILD_MSVC

///////////////////////////////////////////////////////////////////////////////

GP_API int C4Cmp(uns match,uns test);

///////////////////////////////////////////////////////////////////////////////
// LINKED LIST

// linked list
typedef struct _llnode {
   struct _llnode *n;
   struct _llnode *p;
   int t; // type: listhead=0, others=non-zero
} LLNode;

GP_API void gpLLMakeHead(void *head);
GP_API void gpLLMakeNode(void *node,int t);
GP_API void gpLLLinkAfter(void *head,void *node);
GP_API void gpLLLinkBefore(void *head,void *node);
GP_API void gpLLUnlink(void *node);

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // GPTYPES_H