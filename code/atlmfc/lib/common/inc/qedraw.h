// Copyright (C) 2004-2009 Joe Linhoff - All Rights Reserved
// qedraw.h -- public interface to library
#ifndef QEDRAW_H
#define QEDRAW_H

#if BUILD_MSVC
#include <windows.h> // included b/c GL needs it.. bummer
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif // BUILD_MSVC

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpdrawInit();
GP_API void gpdrawFinal();
GP_API int gpdrawOpen(); // after RC setup
GP_API void gpdrawClose();

///////////////////////////////////////////////////////////////////////////////
//

//
// COMMON DATA
//
GP_API float qefnVec0000[]; ///< 0,0,0,0
GP_API float qefnBlack4f[]; ///< 0,0,0,1
GP_API float qefnWhite4f[]; ///< 1,1,1,1
GP_API float qefnDarkBlue4f[]; ///< dark blue color
GP_API float qefnDarkGray4f[]; ///< dark gray color
GP_API float qefnRed4f[]; ///< 1,0,0,1
GP_API float qefnGreen4f[]; ///< 0,1,0,1
GP_API float qefnBlue4f[]; ///< 0,0,1,1
GP_API float qefnYellow4f[]; ///< 1,1,0,1
GP_API float qefnM12Identity[]; ///< mat12 identity

//
// CAMERAS
//

GP_API int qefnSysCam3D(float fovyRadians,float zNear,float zFar); ///< perps
GP_API int qefnSysCam2D(void); ///< ortho: (0,0) left top (1,1) right bottom
GP_API int qefnSysCamBitmap(void); ///< ortho:(0,0)..(winwidth-1,winheight-1)
GP_API int qefnSysCamAuto(void); ///< default trackball cam
// qefnSysCamAutoSP sp:
//  n (float *dstNearPlaneDist) - get near plane dist
//  f (float *dstFarPlaneDist) - get far plane dist
//  v (float *dstHalfFieldOfViewYRadians) - get FOVY
//  N (float nearPlaneDist) - set near plane dist
//  F (float farPlaneDist) - set far plane dist
//  V (float halfFOVYRad) - set fovy
GP_API int qefnSysCamAutoSP(chr *sp,...); ///< get info

//
// LIGHTS, MATERIALS
//

GP_API int qefnSysLight(void); ///< set system light
GP_API int qefnSysMaterial(void); ///< set system material

enum {
   QELIGHTOP_NEXT, // get next dynamic light
   QELIGHTOP_CURRENT, // get current dynamic light
   QELIGHTOP_NEXTAMBIENT, // get next ambient light
   QELIGHTOP_CURRENTAMBIENT, // get current ambient light
   QELIGHTOP_TESTANDSETFIRST, // system function
};

GP_API int qeLightOp(uns op,...); ///< light operation

//
// DRAW
//

/// draw faces
GP_API int qeDrawFaces(float *verts,int *faces,int numf);
/// draw UV mapped faces
GP_API int qeDrawUVFaces(float *verts,int *faces,float *uvs,int numf);
/// draw UV mapped faces with per-face normals
GP_API int qeDrawUVFNrmfv(float *verts,float *nrmperfvert,int *faces,float *uvs,int numf);
/// draw UV mapped faces with per-face-vert normals
GP_API int qeDrawUVFNrmv(float *verts,float *nrmpervert,int *faces,float *uvs,int numf);
/// draw UV mapped faces with per-face-vert normals and tangents
GP_API int qeDrawUVFNrmfvT(float *verts,float *nrmperfvert,int *faces,float *uvs,int numf,
   float *tangents,int tangentloc); ///< for use with shader
/// draw calculated normals
GP_API int qeDrawNormals(float *verts,int *faces,int numf);
/// draw per-face normals from pool
GP_API int qeDrawNrmfv(float *verts,float *nrmperfvert,int *faces,int numf,float size);
/// draw per-vert normals from pool
GP_API int qeDrawNrmv(float *verts,float *nrmpervert,int *faces,int numf,float size);

GP_API int qefnDrawCube(float scale); ///< draw a cube
GP_API int qefnDrawAxes(float scale); ///< draw XYZ axes
GP_API int qefnDrawRoot(float scale); ///< draw XYZ root
GP_API int qefnDrawGrid(uns num,float size); ///< draw num x num grid
GP_API int qefnDrawGroundRect(float xsize,float zsize); ///< flat rect on gnd
GP_API int qefnDrawRay(float x,float y,float z); ///< draw ray to xyz
GP_API int qefnDrawBox(float sx,float sy,float sz); ///< draw box
GP_API int qefnDrawBoxOnGnd(float sx,float sy,float sz); ///< draw box on ground
GP_API int qefnDrawPyramid(float sx,float sy,float sz); ///< draw pyaramid
GP_API int qefnDraw2DImage(chr *name); ///< fullscreen, assumes qefnSysCam2D

// sp: 
//     t (chr *texname)
//     m set OpenGL modes
//     u (float *uv) array:u0,v0,u1,v1
//     x (float *xy) array:x0,y0,x1,y1
//     z (float z)
GP_API int qefnDraw2DSP(chr *sp,...);

// sp: 6 (chr **texNameArray) array of tex names: front,right,back,left,top,bottom
//     d (float *dir3) points to dir vector
//     u (float *up3) points to up vector
GP_API int qefnDrawSkyBoxSP(chr *sp,...);

//
// OPENGL MATRICES
//

GP_API void qeCamM12f(float *m12,float *rot,float *xyz); ///< create camera matrix
GP_API int qeCamLookAtM12f(float *m12,float *xyzPos,float *xyzLookAt,float *xyzUp);
GP_API void qeGLM9f(float *m9); ///< concatenate with current OpenGL matrix
GP_API void qeGLM12f(float *m12); ///< concatenate with current OpenGL matrix
GP_API void qeGLXYZM9f(float *xyz,float *m9); ///< concat w/current OpenGL matrix
GP_API void qeGLM9GetFacingf(float *m9); ///< get flat-to-view rotation matrix
GP_API void qeGLM12GetFacingf(float *m12); ///< get flat-to-view rotation matrix
GP_API void qeGLPerspective(float fovyHalfRad,float wDivH,
   float nearClip,float farClip); ///< same as gluPerspective

#define M_QEGLSUPPORT_BASICSHADERS  0x00000100 ///< basic shaders supported
#define M_QEGLSUPPORT_VERTEXBUFFERS 0x00000200 ///< vertex buffers supported

GP_API uns qeGLSupport(void); ///< get support bits

//
// BUFFERS
//

GP_API int qefnClearScreenRGBADepth(float r,float g,float b,float a,float d);
GP_API int qefnClearScreen(void); ///< swap buffers, clear, reset lighting

//
// SHADOW VOLUMES
//

// allocate shadow
GP_API int qeShadowCreateSP(qeObj **dstp,chr *sp,...);
GP_API int qeShadowDrawSP(qeObj *shadowObj,chr *sp,...);

//
// SHADOW MAPS
//

// sp: w (uns width)
//     h (uns height)
//     n (int num) num of shadow maps, 1..4 for now, clamped, default=1
GP_API int qeShadowMapCreateSP(qeObj **dstp,chr *sp,...);
GP_API int qeShadowMapZap(qeObj *shadowObj);

// sp: 0 frame start
//     1 before shadow pass
//     2 after shadow pass
//     3 before camera pass
//     4 after camera pass
//     c (float *mat16CamModelView) set camera modelview matrix
//     C (float *mat16CamProjection) set camera projection matrix
//     l (float *mat16LitModelView) set light modelview matrix
//     L (float *mat16LitProjection) set light projection matrix
//     s skip (inc) shadow pass
GP_API int qeShadowMapDrawSP(qeObj *shadowObj,chr *sp,...);

//
// FRAME BUFFER OBJECTS
//

// sp: w (uns width)
//     h (uns height)
GP_API int qeFrameBufferCreateSP(qeObj **dstp,chr *sp,...);
GP_API int qeFrameBufferZap(qeObj *fbObj);

enum {
   QEFRAMEBUFFEROP_NONE,
   QEFRAMEBUFFEROP_BIND, // bind
   QEFRAMEBUFFEROP_UNBIND, // unbind
};
GP_API int qeFrameBufferOp(qeObj *fbo,uns op,...);

//
// FRUSTUM
//

// qeBuildCamFrustumPoints
//             far
//          7-------4
//          |       |
// near     |       |
//  3--0    6-------5
//  |  |
//  2--1
GP_API int qeBuildCamFrustumPoints(float *xyzEightDst,
   float *invCamMat,float wDivH,float fovyHalfRad,float zNear,float zFar);

//
// SHADERS
//

#define M_QESHADERNEW_PREDEFINED 0x0001
#define M_QESHADERNEW_COMPILE    0x0002
#define M_QESHADERNEW_STRING     0x0004

GP_API int qeShaderNew(chr *name,uns flags,chr *path); ///< register shader
GP_API int qeShaderDelete(chr *name); ///< delete shader
GP_API int qeShaderCompile(chr *name); ///< compile shader
GP_API int qeShaderUse(chr *name); ///< use shader, pass 0 to detach

// build tangents
#define M_QEFNCREATETANGENTS_NRMV 0x01 // normal is nrmfv
#define M_QEFNCREATETANGENTS_NOGRAMSCHMIDT 0x02 // skip orthonormalization
GP_API int qefnCreateTangents(float **tangentsp,uns flags, // allocated
   float *verts,float *nrmperfvert,int *faces,float *uvs,int numf,int numv);
GP_API int qefnCountFaceVerts(int *faces,int numf); // numfv

// flags cleared every object
#define M_QEDRAWREC_DONTLIGHT   0x0001 // no light
#define M_QEDRAWREC_PERFACEVERT 0x0002 // normals & tangets
#define M_QEDRAWREC_PERVERT     0x0004 // normals & tangets (non-standard)
#define M_QEDRAWREC_POLYGONS    0x0008 // polygons only (no uvs,normals,..)
#define M_QEDRAWREC_NOMODES     0x0010 // don't change modes
#define M_QEDRAWREC_NOSHADER    0x0020 // don't use shader
#define M_QEDRAWREC_WIREFRAME   0x0040 // wireframe
#define M_QEDRAWREC_DONTSHADOW  0x0080 // no shadow
#define M_QEDRAWREC_DRAWREADY   0x0100 // d_ vars setup
#define M_QEDRAWREC_DEBUG       0x1000 // debug this object

typedef struct {

   // this whole record is zerod every object

   uns flags; // M_QEDRAWREC_

   uns numf; // number of faces 
   uns numv; // number of verts
   int *faces; // faces
   float *verts; // verts
   float *uvs; // uvs
   float *normals; // normals (per vert or per face-vert)
   float *tangents; // tangents (per vert or per face-vert)

   uns lightMask; // bit0=light0 active (enable & use it)
   uns numShadowMaps; // 0..4

   chr *imgName0; // image for primary texture
} qeDrawRec;

#define M_QEDRAWSP_LIGHT        0x00fff // valid light mask bits
#define M_QEDRAWSP_LIGHT_ENABLE 0x10000 // enable w/o an individual light

// sp: 
//     B call 'before' function
//     A call 'after' function
//     l (uns lightMask) bit0=light0 active; draw enables & uses indiv lights
//     s (uns numShadowMaps)
//     F fixed OpenGL draw pipeline; don't run shader
//     M don't change any OpenGL modes
//     P draw polygons only; no uvs, normals, tangents
//     W wireframe
//     0 start a new object, set for each obj
//     # (uns c4type,ptr data) eg: (uns C4TYPE_GEO3,qeLibGeo3 *geo)
//       supported: C4TYPE_GEO1-4
//     v (float *verts) set/override verts
//     n (float *normals) set/override normals
//     t (float *tangents) set/override normals
//     i (chr *name) set/override image name
//     ",init 1" initialize built in shader -- must be done b/f setba
//     ",setba" (fnc_ipi beforeAfterFnc) set function
//      int beforeAfterFnc(qeDrawRec *dr,int op) op: 0=before 1=after
//     * debug this object
//     < old modes on, default
//     > new modes on, resets beforeAfterFnc
//    ' ' (space) skip, NOP
GP_API int qeDrawSP(chr *sp,...); // uber-draw

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // QEDRAW_H
