// Copyright (C) 2007-2009 Joe Linhoff, All Rights Reserved
// qeinst.h
#ifndef QEINST_H
#define QEINST_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpinstInit();
GP_API void gpinstFinal();
GP_API int gpinstStart();

///////////////////////////////////////////////////////////////////////////////

typedef struct {
   float rot[3];
   float trans[3];
   float scale[3];
} qeRTS;

// structure note:
// the structures in this file may change with future implementations

//
// INST
//

//#define M_QEINSTVISIT_POPVISIT 0x0001
typedef struct {
   uns32 type;
   int (*visit)(ptr inst,chr *sp,...); // P=popvisit
} qeInstVisitRec;

GP_API int qeInstLoad(ptr adr,uns type);
GP_API int qeInstStartSP(ptr adr,uns type,chr *sp,...);
#define qeInstStart(_a_,_t_) qeInstStartSP(_a_,_t_,NUL)
GP_API int qeInstVisitTableSet(qeInstVisitRec *vr);

//
// C4TYPE_NODE
//

#define M_QEINSTNODE1_PUSHMAT 0x0001
#define M_QEINSTNODE1_POPMAT  0x0002

typedef struct { // see structure note at top of file
   uns flags;
} qeInstNode1;

//
// C4TYPE_MAT
//

typedef struct { // see structure note at top of file
   uns libType;
   ptr libData;
   float trans[3];
   float rot[3];
   float scale[3];
   float mat12[12];
} qeInstNodeMat;

//
// C4TYPE_ANI
//

// flags for qeInstNodeAni
#define M_QEINSTANI_AUTODRIVE   0x000001 // search siblings for first drivable
#define M_QEINSTANI_DRIVERTSF   0x000002 // qeRTS follows
#define M_QEINSTANI_DRIVEM12F   0x000004 // qeM12f follows
#define M_QEINSTANI_LOOP        0x000008 // loop this animation (override anim)
#define M_QEINSTANI_DONTLOOP    0x000010 // dont loop this anim (override anim)
#define M_QEINSTANI_LINEAR      0x000020 // linear interpolation
#define M_QEINSTANI_FIXEDVEL    0x000040 // fixed velocity
#define M_QEINSTANI_DONTSCALE   0x000080 // don't scale
#define M_QEINSTANI_FIRSTLAST   0x000100 // first==last frame
#define M_QEINSTANI_DONE        0x001000 // anim finished, cleared on start
#define M_QEINSTANI_LOOPED      0x002000 // anim looped, sys doesn't clear
#define M_QEINSTANI_ISROOT      0x004000 // ani is root
#define M_QEINSTANI_PAUSE       0x008000 // pause is on
#define M_QEINSTANI_SYSTEM      0xff0000 // reserved for system
#define M_QEINSTANI_RESTART     0x100000 // restart
#define M_QEINSTANI_INTERPTO    0x200000 // interp

typedef struct { // see structure note at top of file
   ptr lib0Data; // key0
   ptr lib1Data; // key1
   uns flags; // flags
   int16 keyCurrent; // current keyframe
   int16 keyCount; // total keys run through
   float timeStart; // last key-frame-zero start
   float timeMul; // multiplier to change speed of animation
   float time0; // start of key0
   float time1; // end of key1
   float timeDiv; // 1/(end-start)
   ptr kh0; // key0
   ptr kh1; // key1
   float frac;
   uns priv[10];
} qeInstNodeAni;

//
// C4TYPE_SKL
//

typedef struct { // see structure note at top of file
   uns libType;
   ptr libData;
   qeObj *oSelf;
   uns numMats;
   float *m12Inputs; // input transform matrix
   float *m12User; // user matrix (0 for no anim, m12 space is allocated)
   float *m12Outputs; // output total transform for joint
   float *m12Joints; // output partial (orientation only) transform
} qeInstNodeSkl;

//
// C4TYPE_SKN
//

#define M_QEINSTSKN_DONTVISIT        0x0001
#define M_QEINSTSKN_DONTDRAW         0x0002
#define M_QEINSTSKN_FACEVERTNORMALS  0x0004
#define M_QEINSTSKN_VERTNORMALS      0x0008
typedef struct { // see structure note at top of file
   uns libType;
   ptr libData;
   uns geoType;
   ptr geoLib;
   uns flags;
   float *verts;
   float *normals;
} qeInstNodeSkn;

//
// C4TYPE_CAM
//

#define M_QEINSTCAM_ARCBALL 0x0001
#define M_QEINSTCAM1_ORTHO  0x0002
typedef struct { // see structure note at top of file
   uns libType;
   ptr libData;
   uns flags;
   float rot[3];
   float trans[3];
   ptr p1;
} qeInstNodeCam;

typedef struct { // see structure note at top of file
   uns libType;
   ptr libData;
   uns flags;
} qeInstNodeLit;

//#define M_QEINSTVISITSKN_DONTDRAW 0x0001

GP_API int qeInstVisitGEO1(ptr inst,chr *sp,...);
GP_API int qeInstVisitGEO2(ptr inst,chr *sp,...);
GP_API int qeInstVisitGEO3(ptr inst,chr *sp,...); // M=nodrawmodes
GP_API int qeInstVisitGEO4(ptr inst,chr *sp,...); // M=nodrawmodes
GP_API int qeInstVisit_MAT(ptr inst,chr *sp,...);
GP_API int qeInstVisit_NODE(ptr inst,chr *sp,...); // P=popvisit
GP_API int qeInstVisit_ANI(ptr inst,chr *sp,...);
GP_API int qeInstVisit_SKL(ptr inst,chr *sp,...);
GP_API int qeInstVisit_SKN(ptr inst,chr *sp,...); // S=dontdrawskin
GP_API int qeInstVisit_CAM(ptr inst,chr *sp,...);
GP_API int qeInstVisit_LIT(ptr inst,chr *sp,...);

//
// ANIMATION
//

// use these flags with qeObjAniOp() -- these are 'safe' flags
#define M_QEOBJANI_LOOP      M_QEINSTANI_LOOP // loop this animation
#define M_QEOBJANI_DONTLOOP  M_QEINSTANI_DONTLOOP // dont loop
#define M_QEOBJANI_DRIVERTS  M_QEINSTANI_DRIVERTSF // qeRTS imm following
#define M_QEOBJANI_DRIVEM12  M_QEINSTANI_DRIVEM12F // qeM12 imm following
#define M_QEOBJANI_HASLOOPED M_QEINSTANI_LOOPED // looped / ended, not cleared
#define M_QEOBJANI_DONE      M_QEINSTANI_DONE // ended, cleared on start
#define M_QEOBJANI_FIXEDVEL  M_QEINSTANI_FIXEDVEL // fixed velocity spline
#define M_QEOBJANI_DONTSCALE M_QEINSTANI_DONTSCALE // dont scale
#define M_QEOBJANI_PAUSE     M_QEINSTANI_PAUSE // pause is on

enum {
   QEOBJANIOP_NONE,
   QEOBJANIOP_SETFLAGS, // uns M_QEOBJANI_
   QEOBJANIOP_CLEARFLAGS, // uns M_QEOBJANI_
   QEOBJANIOP_GETFLAGS, // get flags
   QEOBJANIOP_GETKEYCOUNT, // total keys animated
   QEOBJANIOP_SETKEYCOUNT, // int count
   QEOBJANIOP_GETKEYCURRENT, // current key in animation
   QEOBJANIOP_GETSTARTTIME, // float *resultp
   QEOBJANIOP_GETTIMEMUL, // float *resultp
   QEOBJANIOP_SETTIMEMUL, // float timemul
   QEOBJANIOP_GETVEL, // float *resultp
   QEOBJANIOP_SETVEL, // float vel
   QEOBJANIOP_GETTOTALKEYS, // total keys in animation
   QEOBJANIOP_GETTOTALTIME, // float *resultp
   QEOBJANIOP_GETDIST, // float *resultp
   QEOBJANIOP_SETDIST, // dist
   QEOBJANIOP_GETDISTTOTAL, // float *resultp
   QEOBJANIOP_SNAPTOKEYNUM, // int keynum
};

// animation instances
GP_API qeInstNodeAni* qeObjAni(qeObj *o);
#define qeObjAniVisit(_oani_,_ignored_) qeObjAniVisitSP(_oani_,0)
GP_API int qeObjAniVisitSP(qeObj *o,chr *sp,...); // t=deltatime,T=time
#define qeObjAniStart(_oani_,_libAni_) \
   qeObjAniStartSP(_oani_,_libAni_,NUL)
GP_API int qeObjAniStartSP(qeObj *o,qeObj *libAni,chr *sp,...);
#define qeObjAniInterp(_oani_,_libani_,_time_) \
   qeObjAniStartSP(_oani_,_libani_,"i",((float)_time_))
GP_API int qeObjAniRestart(qeObj *o);
GP_API int qeObjAniSnapFrac(qeObj *o,float keyFrameFrac);
GP_API int qeObjAniSnapTime(qeObj *o,float timeFromAnimStart);
GP_API qeRTS* qeObjAniRTS(qeObj *o);
GP_API float* qeObjAniM12f(qeObj *o);
GP_API int qeObjAniOp(qeObj *o,uns op,...);

// macros
#define qeObjAniSetFlags(_oani_,_flags_) \
   qeObjAniOp(_oani_,QEOBJANIOP_SETFLAGS,_flags_)
#define qeObjAniClearFlags(_oani_,_flags_) \
   qeObjAniOp(_oani_,QEOBJANIOP_CLEARFLAGS,_flags_)
#define qeObjAniKeyCountGet(_oani_) \
   qeObjAniOp(_oani_,QEOBJANIOP_GETKEYCOUNT)
#define qeObjAniKeyCountSet(_oani_,_n_) \
   qeObjAniOp(_oani_,QEOBJANIOP_SETKEYCOUNT,_n_)
#define qeObjAniKeyCurrentGet(_oani_) \
   qeObjAniOp(_oani_,QEOBJANIOP_GETKEYCURRENT)
#define qeObjAniSetVel(_oani_,_vel_) \
   qeObjAniOp(_oani_,QEOBJANIOP_SETVEL,((float)(_vel_)))

GP_API int qeLibScaleAnims(qeObj *olib,float sx,float sy,float sz);

GP_API int qeObjAniJointSP(qeObj *o,chr *sp,...);

// sp: m=create & drive a mat12 internally, l=loop, s=start
GP_API int qeObjAniCreateSP(qeObj **objp,qeObj *libani1,chr *name,chr *sp,...);

//
// SKELETON ANIMATIONS
//

enum {
   QEJOINTEDOP_NONE,
   QEJOINTEDOP_DRAW,
   QEJOINTEDOP_DONTDRAW,
   QEJOINTEDOP_VISIT,
   QEJOINTEDOP_DONTVISIT,
   QEJOINTEDOP_SERVICE,
};

GP_API qeObj* qeObjJointedAddSP(ptr libSkl,chr *sp,...);
GP_API void qeObjJointedFree(qeObj *job);
GP_API qeObj* qeObjJointedSkel(qeObj *job);
GP_API int qeObjJointedOp(qeObj *job,uns op,...);
GP_API int qeObjJointedCreateSP(qeObj **dstjobp,chr *sp,...);
#define qeObjJointedCreate(_dstjobp_,_dstmobp_,_libName_,_name_) \
   qeObjJointedCreateSP(_dstjobp_,"lnM",_libName_,_name_,_dstmobp_)
#define qeObjJointedUpdate(_job_,_ignored_) qeObjJointedOp(_job_,QEJOINTEDOP_SERVICE)

// qeObjDrawSP()
//  sp: uses the same sp codes as qeDrawSP()
//     # (uns c4type,ptr data)
//     0 resets object data -- don't use, added by qeObjDrawSP()
GP_API int qeObjDrawSP(qeObj *ob,chr *sp,...);

enum {
   QEOBJOP_COPYTOGEO3=1, // qeLibGeo3 *geo3
   QEOBJOP_SETIMGNAME_POINTER, // chr* -- must remain valid (not copied in)
   QEOBJOP_GETIMGNAME_POINTER, // chr**
   QEOBJOP_COPY_FROM_NAMEDJOINT_TO_M12, // chr* jointname,float *dstm12
   QEOBJOP_COPY_FROM_JOINTBIND_TO_M12, // chr* jointname,float *dstm12
   QEOBJOP_COPY_M12_TO_JOINTUSER, // chr* jointname,float *srcm12
   QEOBJOP_NAMEDJOINT_ANIONOFF, // chr* jointname,int onoff -- onoff:0=off,1=on
};

GP_API int qeObjOpSP(qeObj *o,uns op,...);

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // QEINST_H
