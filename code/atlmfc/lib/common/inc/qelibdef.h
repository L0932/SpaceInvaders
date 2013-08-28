// Copyright (C) 2004-2010 Joe Linhoff - All Rights Reserved
// qelibdef.h -- public interface to library
#ifndef QELIBDEF_H
#define QELIBDEF_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifndef GPUNO_H
#include "gpuno.h"
#endif // ndef GPUNO_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// 

/// non-numbered types for game created types
#define C4TYPE_MAT  C4('m','a','t','_') ///< game matrix
#define C4TYPE_ERR  C4('e','r','r','_') ///< game error
#define C4TYPE_ANI  C4('a','n','i','_') ///< game animation
#define C4TYPE_SKL  C4('s','k','l','_') ///< game skeleton
#define C4TYPE_SKN  C4('s','k','n','_') ///< game skin
#define C4TYPE_CAM  C4('c','a','m','_') ///< game camera
#define C4TYPE_LIT  C4('l','i','t','_') ///< game light
#define C4TYPE_OBJ  C4('o','b','j','_') ///< game object (generic)
#define C4TYPE_NODE C4('n','o','d','e') ///< game node
#define C4TYPE_MARK C4('m','a','r','k') ///< game mark
/// numbered types for lib types
#define C4TYPE_GEO1 C4('g','e','o','1') ///< lib geometry
#define C4TYPE_GEO2 C4('g','e','o','2') ///< lib geometry
#define C4TYPE_GEO3 C4('g','e','o','3') ///< lib geometry
#define C4TYPE_GEO4 C4('g','e','o','4') ///< lib geometry
#define C4TYPE_MAT1 C4('m','a','t','1') ///< lib matrix
#define C4TYPE_IMG1 C4('i','m','g','1') ///< lib image
#define C4TYPE_ANI1 C4('a','n','i','1') ///< lib animation
#define C4TYPE_ANI2 C4('a','n','i','2') ///< lib animation
#define C4TYPE_CAM1 C4('c','a','m','1') ///< lib camera
#define C4TYPE_SKL1 C4('s','k','l','1') ///< lib skeleton
#define C4TYPE_SKN1 C4('s','k','n','1') ///< lib skin
#define C4TYPE_TAG1 C4('t','a','g','1') ///< lib tag
#define C4TYPE_POS1 C4('p','o','s','1') ///< lib position
#define C4TYPE_MTR1 C4('m','t','r','1') ///< lib material
#define C4TYPE_LIT1 C4('l','i','t','1') ///< lib light
#define C4TYPE_COL1 C4('c','o','l','1') ///< lib collision

/// light properties
typedef struct {
   float posdir[4]; // position or direction
   float ambient[4]; // color of ambient light
   float diffuse[4]; // colorof light hitting
   float specular[4]; // color reflected light
} qeLight1;

/// material properties
typedef struct {
   float ambient[4]; // color percent of ambient light is given off
   float diffuse[4]; // color percent of light hitting the surface
   float specular[4]; // color percent of reflected light
   float shininess; // shininess exponent
} qeMaterial1;

/// simple geometry definition
typedef struct {
   int numv; // number of vertices
   int numf; // number of faces
   float *verts; // pointer to verts
   int *faces; // pointer to faces
} qeGeo1;

/// simple geometry definition for image mapped geometry
typedef struct {
   int numv; // number of vertices
   int numf; // number of faces
   float *verts; // pointer to verts
   float *normals; // pointer to vertex normals
   int *faces; // pointer to faces
   float *uvs; // pointer to face texture coords
} qeGeo2;

/// flags for qeLibGeo3
#define M_QELIBGEO3_NOTVISIBLE       0x0001 ///< not visible
#define M_QELIBGEO3_DONTLIGHT        0x0002 ///< don't light
#define M_QELIBGEO3_FACEVERTNORMALS  0x0004 ///< one normal for each face-vert
#define M_QELIBGEO3_VERTNORMALS      0x0008 ///< one normal for each vert (non-standard)
#define M_QELIBGEO3_TANGENTS         0x0010 ///< tangents follow normals, same format
#define M_QELIBGEO3_COLGEO           0x0020 ///< colgeo
#define M_QELIBGEO3_ALTGEO           0x0040 ///< altgeo
#define M_QELIBGEO3_DONTSHADOW       0x0080 ///< dont include in shadow pass
#define M_QELIBGEO3_MULTCOLOR        0x0100 ///< has multiple images
/// standard geometry library definition
typedef struct {
   uns32 libType; ///< C4
   uns16 libFlags; ///< library flags
   uns16 libSize; ///< size of this record
   int32 numv; ///< number of verts
   int32 numf; ///< number of faces
   int32 numfv; ///< number of face-verts
   float *verts; ///< pointer to verts
   float *normals; ///< pointer to normals
   int   *faces; ///< pointer to face data
   float *uvs; ///< pointer to uv data
   chr   *imgname; ///< image name
   flt32 xyzrCull[4]; ///< culling xyzr
   chr* note; ///< note field
} qeLibGeo3;

#define M_QELIBGEO4_NOTVISIBLE   0x0001
#define M_QELIBGEO4_DONTLIGHT    0x0002
#define M_QELIBGEO4_EXTRAFACES   0x0004
#define M_QELIBGEO4_DONTSHADOW   0x0008
#define M_QELIBGEO4_ALTGEO       0x0010 ///< altgeo

enum {
   QELIBGEO4_PRIMTYPE_UNVMIX=1, // stride=32:2xfloat,3xfloat,3xfloat
   QELIBGEO4_PRIMTYPE_UNVBLK, //  all: 2xfloat 3xfloat 3xfloat
};

/// experimental libarary definition
typedef struct {
   uns32 libType; ///< C4
   uns16 libFlags; ///< library flags
   uns16 libSize; ///< size of this record
   uns8* prims; ///< primitive data
   int32 primCount; ///< count
   int32 primglBuf; ///< primitive gl buffer (mapped)
   uns16 primType; //< QELIBGEO4_PRIMTYPE_
   uns16 numimgnames; ///< image names
   flt32 xyzrCull[4]; ///< culling sphere
   chr* imgnames; ///< image names
   chr *note; ///< notes
   uns32 b; ///< undefined
} qeLibGeo4;

// dynamic geometry structure, rebuilt
typedef struct {
   uns flags;
   int numf;
   int numv;
   int *faces;
   float *verts;
   float *normals;
   float *uvs;
   int n1;
   int n2;
   ptr memAlloc;
   uns memAllocSize;
   uns memUsed;
} qeGeo9;

#define M_QELIBMAT1_DONTSTART   0x1000
#define M_QELIBMAT1_TRANSFORMED 0x2000

/// lib matrix definition
typedef struct {
   uns32 libType;
   uns16 libFlags;
   uns16 libSize;
   chr   *name;
   flt32 trans[3];
   flt32 rot[3]; // radians
   flt32 scale[3];
   flt32 mat12[12];
} qeLibMat1;

/// lib image
typedef struct {
   uns32 libType;
   uns16 libFlags;
   uns16 libSize;
   chr   *name;
   chr   *path;
   uns8  imgType; // c=color n=normal
   uns8  bytesPerPixel;
   uns16 texFlags;
   uns32 width;
   uns32 height;
   uns32 rowBytes;
   uns32 glFmt;
   uns32 glBind;
   uns8  *pix;
} qeLibImg1;

/// lib position
typedef struct {
   uns32 libType;
   uns16 libFlags;
   uns16 libSize;
   chr   *name;
   chr   *copyofName;
   flt32 trans[3];
   flt32 rot[3];
   flt32 scale[3];
} qeLibPos1;

/// lib material - phong
typedef struct {
   float diffuse;
   float transparency[3];
   float ambientColor[3];
   float incandescence[3];
} qeMtrPhong;

#define QELIBMTRTYPE_PHONG C4('p','h','n','g') ///< phong mtrType

/// lib material record
typedef struct {
   uns32 libType;
   uns16 libFlags;
   uns16 libSize;
   off32 name;
   uns32 mtrType;
   union {
      qeMtrPhong phong;
   } u;
} qeLibMtr1;

typedef struct {
   flt32 ambientShade;
} qeLibLitAmb;

typedef struct {
   flt32 rot[3];
} qeLibLitDir;

typedef struct {
   flt32 trans[3];
   chr decay; // '0'=none 'L'=linear 'Q'=quadratic 'C'=cubic
   chr xx1[3]; // reserved
} qeLibLitPnt;

typedef struct {
   flt32 rot[3];
   flt32 trans[3];
   chr decay; // '0'=none 'L'=linear 'Q'=quadratic 'C'=cubic
   chr xx1[3]; // reserved
   flt32 coneAng;
   flt32 penumbraAng;
   flt32 dropoff;
} qeLibLitSpt;

#define M_QELIBLIT1_DONTSTART 0x0001
#define M_QELIBLIT1_AMBIENT   0x0010
#define M_QELIBLIT1_DIFFUSE   0x0020
#define M_QELIBLIT1_SPECULAR  0x0040

/// lib light
typedef struct {
   uns32 libType;
   uns16 libFlags;
   uns16 libSize;
   chr*  name;
   chr type; // 'a'=ambient 'd'=directional 'p'=point 's'=spot
   chr xx1[3];
   flt32 color4[4];
   flt32 intensity;
   union {
      qeLibLitAmb amb;
      qeLibLitDir dir;
      qeLibLitPnt pnt;
      qeLibLitSpt spt;
   } u;
} qeLibLit1;

/// animation flags
#define M_QELIBKEY_TRS 0x0007 // trscode
#define M_QELIBKEY_V   0x8000
#define M_QELIBKEY_TX  0x0010
#define M_QELIBKEY_TY  0x0020
#define M_QELIBKEY_TZ  0x0040
#define M_QELIBKEY_T   (M_QELIBKEY_TX|M_QELIBKEY_TY|M_QELIBKEY_TZ)
#define M_QELIBKEY_RX  0x0100
#define M_QELIBKEY_RY  0x0200
#define M_QELIBKEY_RZ  0x0400
#define M_QELIBKEY_R   (M_QELIBKEY_RX|M_QELIBKEY_RY|M_QELIBKEY_RZ)
#define M_QELIBKEY_SX  0x1000
#define M_QELIBKEY_SY  0x2000
#define M_QELIBKEY_SZ  0x4000
#define M_QELIBKEY_S   (M_QELIBKEY_SX|M_QELIBKEY_SY|M_QELIBKEY_SZ)

 // trscode: 0, 1 t, 2 r, 3 tr, 4 s, 5 ts, 6 rs, 7 trs

/// lib ani keyframe head
typedef struct {
   flt32 time; // time of key
} qeLibKeyHead;

/// lib ani keyframe A
typedef struct {
   flt32 a[3]; // key data
} qeLibKeyFA;

/// lib ani keyframe B
typedef struct {
   flt32 a[3]; // key data
   flt32 b[3]; // key data
} qeLibKeyFB;

/// lib ani keyframe C
typedef struct {
   flt32 a[3]; // key data
   flt32 b[3]; // key data
   flt32 c[3]; // key data
} qeLibKeyFC;

#define M_QELIBANI1_LOOP      0x0001 // loop the animation
#define M_QELIBANI1_DONTLOOP  0x0002 // dont loop the animation
#define M_QELIBANI1_FIRSTLAST 0x0004 // last==first frame of animation

/// lib ani keyframe record
typedef struct {
   uns32 libType; // system type
   uns16 libFlags; // system flags
   uns16 libSize; // system size
   chr   *name; // name (of individual)
   chr   *jname; // joint name
   uns32 numk; // number of keyframes
   uns16 keyFlags; // M_QELIBKEY_
   uns16 xx1; // padding
   qeLibKeyHead *keys; // first valid
   qeLibKeyHead *keyx; // first invalid
} qeLibAni1;

/// lib ani group
typedef struct {
   uns32 libType; // system
   uns16 libFlags; // system
   uns16 libSize; // system
   chr *name; // name (of group)
   uns32 num; // number of anims
   chr **animNames; // points to an array of anim-name pointers
} qeLibAni2;

#define M_QELIBCAM1_ORTHO     0x0001
#define M_QELIBCAM1_DONTSTART 0x0002

/// lib camera
typedef struct {
   uns32 libType; // type of this record
   uns16 libFlags; // M_QELIBCAM1_ flags
   uns16 libSize; // size of this record
   chr*  name; // name of camera
   flt32 orthoWidth; // orthographic width
   flt32 clipNear; // near clipping plane
   flt32 clipFar; // far clipping plane
   flt32 fovy; // field of view in vertical, radians
   flt32 hdivw; // aspect ratio, width dividedy by height
   flt32 centerOfInterest; // distance to center of interest
   flt32 trans[3]; // translation
   flt32 rot[3]; // rotation
} qeLibCam1;

#define M_QELIBJOINT1_DONTPLAY 0x01 // don't play animation
 
/// lib joint
typedef struct {
   chr* name;
   uns16 parentNum;
   uns8 flags;
   uns8 xx2;
   uns32 parentM12Off;
   flt32 m12Bind[12];
   flt32 orient[3];
   flt32 trans[3];
   flt32 rot[3];
   flt32 scale[3];
} qeLibJoint1;

/// lib skeleton
typedef struct {
   uns32 libType;
   uns16 libFlags;
   uns16 libSize;
   chr* name;
   uns32 numj;
   qeLibJoint1 *joints;
   chr* notes;
} qeLibSkl1;

/// lib bind info
typedef struct {
   chr *name; // joint name -- match with skel
   uns16 matIndex; // skeleton matrix index
   uns16 xx1;
   flt32 m12BindPre[12];
} qeLibBind1;

/// lib skin
typedef struct {
   uns32 libType;
   uns16 libFlags;
   uns16 libSize;
   chr* name;
   uns32 numb; // number of binds
   uns32 numv; // number of verts
   qeLibBind1 *binds;
   flt32 *weights;
} qeLibSkn1;

/// lib collision
typedef struct {
   flt32 nrmk[4];
   int32 numv;
   // followed by numv offsets into verts
} qeLibCol1Face;

/// lib collision -- min max volume
typedef struct {
   flt32 xyzMin[3];
   flt32 xyzMax[3];
   int32 numColFaceOffs;
   // followed by num uns32 offsets into colFaces (in qeLibCol1)
} qeLibCol1MMVol;

/// lib collision
typedef struct {
   uns32 libType;
   uns16 libFlags;
   uns16 libSize;
   uns32 endian;
   int32 numf;
   qeLibCol1Face *colFaces; // qeLibCol1Face
   int32 numv;
   flt32 *verts; // vertices
   int32 numvol;
   qeLibCol1MMVol *mmvol; // qeLibCol1MMVol
} qeLibCol1;

/// lib tag
typedef struct {
   uns32 libType;
   uns16 libFlags;
   uns16 libSize;
   chr* name;
   uns32 type;
   chr* tags;
} qeLibTag1;

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // QELIBDEF_H
