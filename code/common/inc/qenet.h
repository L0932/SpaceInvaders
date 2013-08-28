// Copyright (C) 2007-2009 Joe Linhoff, All Rights Reserved
// qenet.h
#ifndef QENET_H
#define QENET_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpnetInit();
GP_API void gpnetFinal();
GP_API int gpnetService();

///////////////////////////////////////////////////////////////////////////////

#define M_NETSOCKETCLOSE_FREE 0x0001

GP_API int qeSocketNewSP(chr *name,chr *sp,...); // register a socket
GP_API int qeSocketOpen(chr *name,uns flags); // open the socket
GP_API int qeSocketClose(chr *name,uns flags); // close the socket
GP_API int qeSocketSendSP(chr *name,chr *sp,...); // send a message
GP_API qeObj* qeSocketObj(chr *name); // get socket object

typedef int (*qeNetCallback)(qeObj* netObj,uns op,...);
#define M_NETCALLBACK 0xff
enum {
   NETCALLBACK_NONE,
   NETCALLBACK_PACKET_RECEIVED, // uns8* buf,int len
   NETCALLBACK_NOP,
   NETCALLBACK_CLIENT_WANTS_CONNECTION, // chr *addr
};

enum {
   NETPROTOCOL_UDP=1,
   NETPROTOCOL_TCP,
};

enum {
   QENETOP_NETOBJ_SENDERNAME=1, // qeObj *netObj,chr *buf,uns bufSize
   QENETOP_NETOBJ_SENDERIP4, // qeObj *netObj,uns32 *ip
   QENETOP_STRING_TO_IP4, // uns32 *dstip,chr *srcadr,chr *srcadrx
   QENETOP_SOCKET_NAME, // chr *socket,chr *buf,uns bufSize
   QENETOP_LOCALHOST_NAME, // chr *buf,uns bufSize
   QENETOP_LOCALHOST_IP4, // uns32 *dstip
   QENETOP_GETLISTENINGFLAG, // qeObj *netObj
   QENETOP_GETPROTOCOL, // qeObj *netObj
   QENETOP_GETCONNECTEDIP, // qeObj *netObj,chr *buf,uns bufSize
   QENETOP_GETSOCKET, // qeObj *netObj
};

GP_API int qeNetOp(uns op,...);

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // QENET_H
