// Copyright (C) 2004-2009 Joe Linhoff, All Rights Reserved
// gpsz.h
#ifndef GPSZ_H
#define GPSZ_H
// JFL 15 Aug 04
// JFL 23 Jul 06

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpszInit();
GP_API void gpszFinal();

///////////////////////////////////////////////////////////////////////////////
// SZ STRINGS

// string routines follow these rules:
// - buffer building functions guarantee a zero-terminator (size > 0)
//
// parameter naming conventions
// - 'ss' points to the string start, i.e. the first chr in the string
// - 'sx' points to the string terminator, i.e. one past the last chr
//   a null pointer can always be passed in for zero-terminated strings
// - 'ts' and 'tx' are used for the second string
// - pass the byte size of the whole buffer
//
// flag table:
// uns32 flagtable[0] = number of entries in table
//       flagtable[1] = flags for character 1 ..

// reserve top 8 bits for system use
#define M_SZF_RESERVED       0xff000000 // not in table -- system use
#define M_SZF_RSVDFORAPP     0x000ff000 // not in table -- app use
#define S_SZF_RSVDFORAPP     12         // shift
#define M_SZF_NEST           0x01000000 // ({[<
#define M_SZF_DEEPNEST       0x02000000 // not in table -- system use
#define M_SZF_ONENEST        0x04000000 // not in table -- system use
#define M_SZF_PREINC         0x10000000 // not in table -- signals pre inc
#define M_SZF_DSTSIZE_NOTERM 0x20000000 // not in table -- system use
#define M_SZF_DSTSIZE_LEN    0x40000000 // not in table -- system use

// default flag table bits -- bottom 24 bits
#define M_SZF_ALPHA     0x00000001 // a-zA-Z
#define M_SZF_NUM       0x00000002 // 0-9
#define M_SZF_WHITE     0x00000004 // space \t
#define M_SZF_EOL       0x00000008 // \r\n
#define M_SZF_ID        0x00000010 // a-zA-Z0-9_
#define M_SZF_SYMBOLS   0x00000020 // _=~`!@#$%^&*:?|\/ 
#define M_SZF_BRACKETS  0x00000040 // (){}[]<> 
#define M_SZF_MODNUM    0x00000080 // -.+
#define M_SZF_SLASHMETA 0x00000100 // e.g. \a 
#define M_SZF_QUOTE     0x00000200 // '"
#define M_SZF_SLASH     0x00000400 // \/

typedef struct {
	chr *sz;
	ptr val;
} szpairrec; 

typedef struct {
	int i;
	chr *sz;
	ptr val;
} szpairisrec; 

// SAFE STRINGS
// guaranteed 0 to terminate string
// pass in buffer size
// string start & stop or 0 terminated

GP_API int szlen(chr *s1); // character length
GP_API int szlen2(chr *s1,chr *s1x); // character length
GP_API int szsize(chr *s1); // byte size of buffer needed
GP_API int szsize2(chr *s1,chr *s1x); // byte size of buffer needed
GP_API int szrev(chr *s1,chr *s1x); // reverse a string
GP_API int szcpy(chr *dst,int dstsize,chr *s1,chr *s1x); // copy
GP_API int szcat(chr *dst,int dstsize,chr *s1,chr *s1x); // concatenate
GP_API int szcpycat(chr *dst,int dstsize,chr *s1,chr *s1x,chr *s2,chr *s2x);
GP_API int szcmp(chr *s1,chr *s2,chr *s2x); ///< compare (mismatch is non-zero)
GP_API int szcmp2(chr *s1,chr *s1x,chr *s2,chr *s2x); ///< compare s1 to s2
GP_API int szrcmp(chr *s1,chr *s2,chr *s2x); ///< compare s1 to s2, end..start
GP_API int szricmp(chr *s1,chr *s2,chr *s2x); ///< compare s1 to s2, end..start
GP_API int szncmp(chr *s1,chr *s2,chr *s2x,int n); ///< compare s1 to s2
GP_API int szncmpx(chr *s1,chr *s1x,chr *s2,chr *s2x,int n);
GP_API int szicmp(chr *s1,chr *s2,chr *s2x); // case insensitive compare
GP_API int szicmp2(chr *s1,chr *s1x,chr *s2,chr *s2x);
GP_API int sznicmp(chr *s1,chr *s2,chr *s2x,int n);
GP_API int szrecmp(chr *s1,chr *s1x,chr *s2,chr *s2x); // simple, reg expr cmp
GP_API int szstart(chr *start,chr *s2,chr *s2x); // test if s2 starts with start
GP_API int szstart2(chr *start,chr *startx,chr *s2,chr *s2x); // starts w/start?
GP_API int szistart(chr *start,chr *s2,chr *s2x); // if s2 starts with start
GP_API chr* szadv(chr *s1,chr *s1x,int add); // advance s1 by add chrs
GP_API int szeos(chr *s1,chr *s1x); // return non-zero if end-of-string
GP_API int szmap(chr *table[],chr *s1,chr *s1x); // return index of tbl match
GP_API int szimap(chr *table[],chr *s1,chr *s1x); // return index of tbl match
GP_API ptr szipair(szpairrec *sm,chr *s1,chr *s1x);
GP_API ptr szipairis(szpairisrec *sm,int i,chr *s1,chr *s1x);
GP_API chr *szvpair(szpairrec *sm,ptr v);
GP_API chr* szchr(chr *s1,chr *s1x,chr c); // find first c or return 0
GP_API chr* szrchr(chr *s1,chr *s1x,chr c); // reverse scan, first c or 0
GP_API chr* szchrsz(chr *s1,chr *s1x,chr *s2,chr *s2x); // first of any in sz
GP_API chr* szchrnoslash(chr *s1,chr *s1x,chr c); // ignore escaped chrs
GP_API chr* szskip(chr *s1,chr *s1x,chr *skip);
GP_API chr* sztill(chr *s1,chr *s1x,chr *till);
GP_API chr* szsub(chr *sub,chr *subx,chr *s2,chr *s2x);
GP_API chr *sznextline(chr *s1,chr *s1x,int *countp);
GP_API chr* szisub(chr *sub,chr *subx,chr *s2,chr *s2x);
GP_API chr* szfncskip(chr *s1,int (*func)(chr c));
GP_API chr* szfncskipr(chr *s1,int (*func)(chr c),chr *rstr,chr rchr);
GP_API chr* sztskip(chr *s1,chr *s1x,uns32 flags);
GP_API chr* szttill(chr *s1,chr *s1x,uns32 flags);
GP_API chr* szfskip(int *ftable,chr *s1,chr *s1x,int flags);
GP_API chr* szftill(int *ftable,chr *s1,chr *s1x,int flags);
GP_API uns32* szflagtable(uns32 *flagtable); // swap current table, return old
GP_API uns32* szgetflagtable(); // get current flag table
GP_API uns32 sztand(chr c,uns32 flags);
GP_API chr sznestend(chr c);
GP_API chr* sztnest(chr *s1,chr *s1x,uns unnestop);
GP_API chr* szc4(uns *u1p,chr *s1,chr *s1x);
GP_API chr* sztobin(chr *s1,chr *s1x,int base,chr dsttype,void *dst);
GP_API int szbinto(chr *dst,int dstsize,int base,chr srctype,void *src);
GP_API int sztocol(chr *dst,int dstsize,int vali);
GP_API chr* szcoltobin(chr *s1,chr *s1x,chr dsttype,void *dst);
GP_API int szfmt(chr *dst,int dstsize,chr *fmt,...);
GP_API int szfmt_v(chr *dst,int dstsize,chr *fmt,chr *fmtx,chr **fmtp,...);

#define SZLN(_s1_,_s1x_) ((_s1x_)?PTR_DIFF((_s1x_),(_s1_)):szlen(_s1_))
#define SZSIZE(_s1_,_s1x_) 1+((_s1x_)?PTR_DIFF((_s1x_),(_s1_)):szlen(_s1_))

#define SZFMT_DSTSIZE_SZSTREAM -99
typedef struct {
   chr *buf;
   uns bufSize;
   int (*output)(chr *buf,uns len);
} szStream;

enum {
   ERR_SZ=-1449, // system-wide define -- joeco.h
	ERR_SZ_UNDEF,
};

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // GPSZ_H
