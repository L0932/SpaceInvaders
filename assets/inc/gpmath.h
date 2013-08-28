// Copyright (C) 2004-2009 Joe Linhoff - All Rights Reserved
// gpmath.h -- public interface to library
#ifndef GPMATH_H
#define GPMATH_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++ wrapper
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpmathInit();
GP_API void gpmathFinal();

///////////////////////////////////////////////////////////////////////////////

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
#define SET16(_d_,_s1_,_s2_,_s3_,_s4_,_s5_,_s6_,_s7_,_s8_,_s9_,_s10_,_s11_,_s12_,_s13_,_s14_,_s15_,_s16_) \
   (_d_)[0]=(_s1_),(_d_)[1]=(_s2_),(_d_)[2]=(_s3_), \
   (_d_)[3]=(_s4_),(_d_)[4]=(_s5_),(_d_)[5]=(_s6_), \
   (_d_)[6]=(_s7_),(_d_)[7]=(_s8_),(_d_)[8]=(_s9_), \
   (_d_)[9]=(_s10_),(_d_)[10]=(_s11_),(_d_)[11]=(_s12_), \
   (_d_)[12]=(_s13_),(_d_)[13]=(_s14_),(_d_)[14]=(_s15_),(_d_)[15]=(_s16_)

#define CPY2(_d_,_s_) (_d_)[0]=(_s_)[0],(_d_)[1]=(_s_)[1]
#define CPY3(_d_,_s_) (_d_)[0]=(_s_)[0],(_d_)[1]=(_s_)[1],(_d_)[2]=(_s_)[2]
#define CPY4(_d_,_s_) (_d_)[0]=(_s_)[0],(_d_)[1]=(_s_)[1],(_d_)[2]=(_s_)[2],(_d_)[3]=(_s_)[3]

//
// VECTORS, MATRICES, MATH
//

enum {
   // on paper, the matrix is:
   //  11 21 31
   //  12 22 32
   //  13 23 33
   // in memory, the matrix order is:
   //  11 12 13 21 22 23 31 32 33
   M9_11,
   M9_12,
   M9_13,
   M9_21,
   M9_22,
   M9_23,
   M9_31,
   M9_32,
   M9_33,
   M9_SIZE
};

enum {
   // on paper, the matrix is:
   //  11 21 31 41
   //  12 22 32 42
   //  13 23 33 43
   //  14 24 34 44
   // in memory, the matrix order is:
   //  11 12 13 14 21 22 23 24 31 32 33 34 41 42 43 44
   M16_11,
   M16_12,
   M16_13,
   M16_14,
   M16_21,
   M16_22,
   M16_23,
   M16_24,
   M16_31,
   M16_32,
   M16_33,
   M16_34,
   M16_41, // X
   M16_42, // Y
   M16_43, // Z
   M16_44,
   M16_SIZE
};

#define M16_X M16_41
#define M16_Y M16_42
#define M16_Z M16_43

enum {
   // on paper:
   //  X 11 21 31
   //  Y 12 22 32
   //  Z 13 23 33
   // in memory:
   //  X Y Z 11 12 13 21 22 23 31 32 33
   M12_X,
   M12_Y,
   M12_Z,
   M12_11,
   M12_12,
   M12_13,
   M12_21,
   M12_22,
   M12_23,
   M12_31,
   M12_32,
   M12_33,
   M12_SIZE
};

#define M12_M9 M12_11

GP_API void M9SetRotXd(double *mat,double rad);
GP_API void M9SetRotYd(double *mat,double rad);
GP_API void M9SetRotZd(double *mat,double rad);
GP_API void M9SetRotXf(float *mat,float rad);
GP_API void M9SetRotYf(float *mat,float rad);
GP_API void M9SetRotZf(float *mat,float rad);
GP_API void M9Mulf(float *dst,float *cur,float *cat);
GP_API void M9Muld(double *dst,double *cur,double *cat);
GP_API int M9TestOnef(float *m9);
GP_API int M9DirUpf(float *dst,float *dir,float *up); // dir invariant
GP_API int M9DirUp2f(float *dst,float *dir,float *up); // up invariant
GP_API void M12Mulf(float *dst,float *cur,float *cat);
GP_API void M12Muld(double *dst,double *cur,double *cat);
GP_API void M16Mulf(float *dst,float *cur,float *cat);
GP_API float MathAbsf(float val);
GP_API float MathSqrtf(float b);
GP_API double MathSqrtd(double b);
GP_API float MathSqrtFastf(float b);
GP_API float MathInvSqrtf(float b);
GP_API double MathInvSqrtd(double b);
GP_API float MathInvSqrtFastf(float b);
GP_API float MathATanf(float x);
GP_API float MathACosf(float x);
GP_API float MathASinf(float x);
GP_API float MathATan2f(float x,float z); ///< angle from adjacent, opposite
GP_API double MathATan2d(double y,double x);
GP_API float MathPowf(float x,float y);
GP_API float MathExpf(float x);
GP_API double MathTand(double x);
GP_API float MathTanf(float x);
GP_API int M9Invf(float *dst,float *src);
GP_API int M9Invd(double *dst,double *src);
GP_API int M12Invf(float *dst,float *src);
GP_API int M12Invd(double *dst,double *src);
GP_API int M16Invf(float *dst,float *src);
GP_API int VecNormalized(double *vec); // <0 err
GP_API int VecNormalizef(float *vec); // <0 err
GP_API int VecSetLenf(float *vec,float len); // <0 on error
GP_API void M12BuildTf(float *mat,float x,float y,float z);
GP_API void M12BuildRTf(float *mat,float xa,float ya,float za,
   float x,float y,float z);
GP_API void M12BuildRTSf(float *mat,float xa,float ya,float za,
   float x,float y,float z,float sx,float sy,float sz);
GP_API void M9SetInteriaTensorf(float *dst,float ix,float iy,float iz,
   float ixy,float ixz,float iyz);
GP_API void M9SetBlockInteriaTensorf(float *dst9,float hx,
   float hy,float hz,float mass);
GP_API int M9Interpf(float *dst9,float *a,float *b,float frac);
GP_API int M9BuildOrthoVec(float *dst9,float *vec);
GP_API void M9BuildSkewSymmetricf(float *dst9,float *vec);
GP_API float M9TransformBoxToAxis(float *mat9,float *axis,float *halfSize);
GP_API int MathQuadraticRoots(float a,float b,float c,float *loRootp,float *hiRootp);
GP_API int MathPointInPoly(float *pt,int numv,float *verts);

// OpenGL format
GP_API void M9Buildf(float *m9,float *scale,float *rot);
GP_API void M12Buildf(float *m12,float *scale,float *rot,float *trans);
GP_API void M9BuildAroundf(float *m9,float rad,float *xyz);

GP_API float MathCosSinf(float rad,float *sinp);
GP_API double MathCosSind(double rad,double *sinp);
GP_API float MathDistFastf(float *xyz0,float *xyz1);
GP_API float MathDistf(float *xyz0,float *xyz1);
GP_API float VecLenf(float *xyz);
GP_API float VecLenFastf(float *xyz);
GP_API float MathLineMinDist(float *xyzA1,float *xyzA2,
   float *xyzB1,float *xyzB2);
GP_API int MathComparef(float *a,float *b,int n,float epsilon);

// find dst given parameter t (0..1) between fr and to
// pass pointers to 4 xyz: bf=before, fr=from, to=to, af=after
GP_API int MathSplineCatmullRom(float *dst,float t,
   float *bf,float *fr,float *to,float *af);

GP_API void M9FromQuatf(float *dst,float *quat);
GP_API void M16FromQuatf(float *dst,float *quat);

GP_API void VecRotXAf(float *dst,float rad,float *src);
GP_API void VecRotXAd(double *dst,double rad,double *src);
GP_API void VecRotYAf(float *dst,float rad,float *src);
GP_API void VecRotYAd(double *dst,double rad,double *src);
GP_API void VecRotZAf(float *dst,float rad,float *src);
GP_API void VecRotZAd(double *dst,double rad,double *src);
GP_API void VecRotM12T(float *dst,float *vec,float *mat);
GP_API int VecComplementBasis(float *u,float *v,float *dir);
GP_API int VecBuildOrthoVec(float *dst3,float *vec);

GP_API int PlaneEqf(float *nrmk,float *xyz0,float *xyz1,float *xyz2);
GP_API int VertNormalf(float *nrm,float *xyz0,float *xyz1,float *xyz2);

GP_API int qeMathCalcPlaneEqs(float *dstPlaneEqs,float *verts,int *faces,int numf);

#define VecIsNonZerof(_v_) (*((int*)(&(_v_)[0]))|*((int*)(&(_v_)[1]))|*((int*)(&(_v_)[2])))

#define QuatId(_d_) (_d_)[0]=(_d_)[1]=(_d_)[2]=0,(_d_)[3]=1
GP_API void QuatMulf(float *dst,float *qCur,float *qCat);
GP_API void QuatVecAddf(float *dst,float *cur,float *vec);
GP_API void QuatVecAddScaledf(float *dst,float *cur,float *vec,float scale);
GP_API void QuatNormalizef(float *dst);
GP_API void QuatBuildAroundAxisf(float *dst,float rad,float x,float y,float z);
GP_API void QuatBuildAngf(float *dst,float xa,float ya,float za);
GP_API void QuatSlerpf(float *dst,float *from, float *to, float t);
GP_API void QuatFromM9f(float *dst,float *mat9);
 
/// copy the negative vector
#define VecNeg(_d_,_v_) (_d_)[0]=-(_v_)[0],(_d_)[1]=-(_v_)[1],(_d_)[2]=-(_v_)[2]

/// rotate vector by matrix
#define VecRotM9(_d_,_v_,_m_) \
   (_d_)[0]=(_v_)[0]*(_m_)[M9_11]+(_v_)[1]*(_m_)[M9_21] \
   +(_v_)[2]*(_m_)[M9_31], \
   (_d_)[1]=(_v_)[0]*(_m_)[M9_12]+(_v_)[1]*(_m_)[M9_22] \
   +(_v_)[2]*(_m_)[M9_32], \
   (_d_)[2]=(_v_)[0]*(_m_)[M9_13]+(_v_)[1]*(_m_)[M9_23] \
   +(_v_)[2]*(_m_)[M9_33]

/// rotate vector by transpose of matrix
#define VecRotM9T(_d_,_v_,_m_) \
   (_d_)[0]=(_v_)[0]*(_m_)[M9_11]+(_v_)[1]*(_m_)[M9_12] \
   +(_v_)[2]*(_m_)[M9_13], \
   (_d_)[1]=(_v_)[0]*(_m_)[M9_21]+(_v_)[1]*(_m_)[M9_22] \
   +(_v_)[2]*(_m_)[M9_23], \
   (_d_)[2]=(_v_)[0]*(_m_)[M9_31]+(_v_)[1]*(_m_)[M9_32] \
   +(_v_)[2]*(_m_)[M9_33]

/// rotate vector by matrix
#define VecRotM12(_d_,_v_,_m_) \
   (_d_)[0]=(_v_)[0]*(_m_)[M12_11]+(_v_)[1]*(_m_)[M12_21] \
   +(_v_)[2]*(_m_)[M12_31], \
   (_d_)[1]=(_v_)[0]*(_m_)[M12_12]+(_v_)[1]*(_m_)[M12_22] \
   +(_v_)[2]*(_m_)[M12_32], \
   (_d_)[2]=(_v_)[0]*(_m_)[M12_13]+(_v_)[1]*(_m_)[M12_23] \
   +(_v_)[2]*(_m_)[M12_33]

#define VecRotM16(_d_,_v_,_m_) \
   (_d_)[0]=(_v_)[0]*(_m_)[M16_11]+(_v_)[1]*(_m_)[M16_21] \
   +(_v_)[2]*(_m_)[M16_31], \
   (_d_)[1]=(_v_)[0]*(_m_)[M16_12]+(_v_)[1]*(_m_)[M16_22] \
   +(_v_)[2]*(_m_)[M16_32], \
   (_d_)[2]=(_v_)[0]*(_m_)[M16_13]+(_v_)[1]*(_m_)[M16_23] \
   +(_v_)[2]*(_m_)[M16_33]

#define VecTransformM12(_d_,_v_,_m_) \
   (_d_)[0]=(_v_)[0]*(_m_)[M12_11]+(_v_)[1]*(_m_)[M12_21] \
   +(_v_)[2]*(_m_)[M12_31]+(_m_)[M12_X], \
   (_d_)[1]=(_v_)[0]*(_m_)[M12_12]+(_v_)[1]*(_m_)[M12_22] \
   +(_v_)[2]*(_m_)[M12_32]+(_m_)[M12_Y], \
   (_d_)[2]=(_v_)[0]*(_m_)[M12_13]+(_v_)[1]*(_m_)[M12_23] \
   +(_v_)[2]*(_m_)[M12_33]+(_m_)[M12_Z]

#define VecTransformM16(_d_,_v_,_m_) \
   (_d_)[0]=(_v_)[0]*(_m_)[M16_11]+(_v_)[1]*(_m_)[M16_21] \
   +(_v_)[2]*(_m_)[M16_31]+(_m_)[M16_X], \
   (_d_)[1]=(_v_)[0]*(_m_)[M16_12]+(_v_)[1]*(_m_)[M16_22] \
   +(_v_)[2]*(_m_)[M16_32]+(_m_)[M16_Y], \
   (_d_)[2]=(_v_)[0]*(_m_)[M16_13]+(_v_)[1]*(_m_)[M16_23] \
   +(_v_)[2]*(_m_)[M16_33]+(_m_)[M16_Z]

/// find cross product of two vectors
#define VecCross(_d_,_a_,_b_) \
   (_d_)[0]=(_a_)[1]*(_b_)[2]-(_a_)[2]*(_b_)[1], \
   (_d_)[1]=(_a_)[2]*(_b_)[0]-(_a_)[0]*(_b_)[2], \
   (_d_)[2]=(_a_)[0]*(_b_)[1]-(_a_)[1]*(_b_)[0]

/// find dot product of two vectors
#define VecDot(_a_,_b_) \
   ((_a_)[0]*(_b_)[0]+(_a_)[1]*(_b_)[1]+(_a_)[2]*(_b_)[2])

/// subtract two vetors: d=a-b
#define VecSub(_d_,_a_,_b_) \
   (_d_)[0]=(_a_)[0]-(_b_)[0],(_d_)[1]=(_a_)[1]-(_b_)[1],(_d_)[2]=(_a_)[2]-(_b_)[2]

#define VecSubScaled(_d_,_a_,_b_,_mul_) \
   (_d_)[0]=(_a_)[0]-(_mul_)*(_b_)[0],(_d_)[1]=(_a_)[1]-(_mul_)*(_b_)[1],(_d_)[2]=(_a_)[2]-(_mul_)*(_b_)[2]

#define VecSquared(_v_) ((_v_)[0]*(_v_)[0]+(_v_)[1]*(_v_)[1]+(_v_)[2]*(_v_)[2])

/// subtract two: d=a-b
#define XYSub(_d_,_a_,_b_) \
   (_d_)[0]=(_a_)[0]-(_b_)[0],(_d_)[1]=(_a_)[1]-(_b_)[1]

/// add two vectors: d=a+b
#define VecAdd(_d_,_a_,_b_) \
   (_d_)[0]=(_a_)[0]+(_b_)[0],(_d_)[1]=(_a_)[1]+(_b_)[1],(_d_)[2]=(_a_)[2]+(_b_)[2]

/// add a scaled vector to another vector: d=a+b*mul
#define VecAddScaled(_d_,_a_,_b_,_mul_) \
   (_d_)[0]=(_a_)[0]+(_mul_)*(_b_)[0],(_d_)[1]=(_a_)[1]+(_mul_)*(_b_)[1],(_d_)[2]=(_a_)[2]+(_mul_)*(_b_)[2]

/// scale vector: d=a*mul
#define VecScale(_d_,_a_,_mul_) \
   (_d_)[0]=(_mul_)*(_a_)[0],(_d_)[1]=(_mul_)*(_a_)[1],(_d_)[2]=(_mul_)*(_a_)[2]

#define ZERO2(_d_) (_d_)[0]=(_d_)[1]=0
#define ZERO3(_d_) (_d_)[0]=(_d_)[1]=(_d_)[2]=0

#define XYAdd(_d_,_a_,_b_) \
   (_d_)[0]=(_a_)[0]+(_b_)[0],(_d_)[1]=(_a_)[1]+(_b_)[1]

#define M9SetAcross(_dst_,_a_,_b_,_c_,_d_,_e_,_f_,_g_,_h_,_i_) \
   (_dst_)[M9_11]=(_a_),(_dst_)[M9_21]=(_b_),(_dst_)[M9_31]=(_c_), \
   (_dst_)[M9_12]=(_d_),(_dst_)[M9_22]=(_e_),(_dst_)[M9_32]=(_f_), \
   (_dst_)[M9_13]=(_g_),(_dst_)[M9_23]=(_h_),(_dst_)[M9_33]=(_i_)

/// build M16 from M12
#define M16FromM12(_dst_,_m12_) (_dst_)[M16_14]=(_dst_)[M16_24]= \
   (_dst_)[M16_34]=0,(_dst_)[M16_44]=1,(_dst_)[M16_11]=(_m12_)[M12_11], \
   (_dst_)[M16_21]=(_m12_)[M12_21],(_dst_)[M16_31]=(_m12_)[M12_31], \
   (_dst_)[M16_12]=(_m12_)[M12_12],(_dst_)[M16_22]=(_m12_)[M12_22], \
   (_dst_)[M16_32]=(_m12_)[M12_32],(_dst_)[M16_13]=(_m12_)[M12_13], \
   (_dst_)[M16_23]=(_m12_)[M12_23],(_dst_)[M16_33]=(_m12_)[M12_33], \
   (_dst_)[M16_X]=(_m12_)[M12_X],(_dst_)[M16_Y]=(_m12_)[M12_Y], \
   (_dst_)[M16_Z]=(_m12_)[M12_Z]

/// build M16 from M9
#define M16FromM9(_dst_,_src_) (_dst_)[M16_14]=(_dst_)[M16_24]= \
   (_dst_)[M16_34]=0,(_dst_)[M16_44]=1,(_dst_)[M16_11]=(_src_)[M9_11], \
   (_dst_)[M16_21]=(_src_)[M9_21],(_dst_)[M16_31]=(_src_)[M9_31], \
   (_dst_)[M16_12]=(_src_)[M9_12],(_dst_)[M16_22]=(_src_)[M9_22], \
   (_dst_)[M16_32]=(_src_)[M9_32],(_dst_)[M16_13]=(_src_)[M9_13], \
   (_dst_)[M16_23]=(_src_)[M9_23],(_dst_)[M16_33]=(_src_)[M9_33], \
   (_dst_)[M16_X]=(_dst_)[M16_Y]=(_dst_)[M16_Z]=0

/// set M16's rotation parts from M9
#define M16PartM9(_dst_,_src_) \
   (_dst_)[M16_11]=(_src_)[M9_11], \
   (_dst_)[M16_21]=(_src_)[M9_21],(_dst_)[M16_31]=(_src_)[M9_31], \
   (_dst_)[M16_12]=(_src_)[M9_12],(_dst_)[M16_22]=(_src_)[M9_22], \
   (_dst_)[M16_32]=(_src_)[M9_32],(_dst_)[M16_13]=(_src_)[M9_13], \
   (_dst_)[M16_23]=(_src_)[M9_23],(_dst_)[M16_33]=(_src_)[M9_33]

/// build an M16 matrix from an M9 and XYZ
#define M16FromXYZM9(_dst_,_xyz_,_src_) (_dst_)[M16_14]=(_dst_)[M16_24]= \
   (_dst_)[M16_34]=0,(_dst_)[M16_44]=1,(_dst_)[M16_11]=(_src_)[M9_11], \
   (_dst_)[M16_21]=(_src_)[M9_21],(_dst_)[M16_31]=(_src_)[M9_31], \
   (_dst_)[M16_12]=(_src_)[M9_12],(_dst_)[M16_22]=(_src_)[M9_22], \
   (_dst_)[M16_32]=(_src_)[M9_32],(_dst_)[M16_13]=(_src_)[M9_13], \
   (_dst_)[M16_23]=(_src_)[M9_23],(_dst_)[M16_33]=(_src_)[M9_33], \
   (_dst_)[M16_X]=(_xyz_)[0],(_dst_)[M16_Y]=(_xyz_)[1],(_dst_)[M16_Z]=(_xyz_)[2]

#define M9FromM16(_dst_,_src_) \
   (_dst_)[M9_11]=(_src_)[M16_11], \
   (_dst_)[M9_21]=(_src_)[M16_21],(_dst_)[M9_31]=(_src_)[M16_31], \
   (_dst_)[M9_12]=(_src_)[M16_12],(_dst_)[M9_22]=(_src_)[M16_22], \
   (_dst_)[M9_32]=(_src_)[M16_32],(_dst_)[M9_13]=(_src_)[M16_13], \
   (_dst_)[M9_23]=(_src_)[M16_23],(_dst_)[M9_33]=(_src_)[M16_33]

#define M12FromM16(_vm_,_m_) (_vm_)[M12_X]=(_m_)[M16_X], \
   (_vm_)[M12_Y]=(_m_)[M16_Y],(_vm_)[M12_Z]=(_m_)[M16_Z], \
   (_vm_)[M12_11]=(_m_)[M16_11],(_vm_)[M12_21]=(_m_)[M16_21], \
   (_vm_)[M12_31]=(_m_)[M16_31],(_vm_)[M12_12]=(_m_)[M16_12], \
   (_vm_)[M12_22]=(_m_)[M16_22],(_vm_)[M12_32]=(_m_)[M16_32], \
   (_vm_)[M12_13]=(_m_)[M16_13],(_vm_)[M12_23]=(_m_)[M16_23], \
   (_vm_)[M12_33]=(_m_)[M16_33]

#define M9Id(_m_) (_m_)[M9_11]=(_m_)[M9_22]= \
   (_m_)[M9_33]=1,(_m_)[M9_21]=(_m_)[M9_31]= \
   (_m_)[M9_12]=(_m_)[M9_32]=(_m_)[M9_13]=(_m_)[M9_23]=0

#define M12Id(_m_) (_m_)[M12_11]=(_m_)[M12_22]= \
   (_m_)[M12_33]=1,(_m_)[M12_21]=(_m_)[M12_31]= \
   (_m_)[M12_12]=(_m_)[M12_32]=(_m_)[M12_13]=(_m_)[M12_23]= \
   (_m_)[M12_X]=(_m_)[M12_Y]=(_m_)[M12_Z]=0

#define M12SetScale(_m_,_sx_,_sy_,_sz_) (_m_)[M12_11]=(_sx_), \
   (_m_)[M12_22]=(_sy_),(_m_)[M12_33]=(_sz_),(_m_)[M12_21]=(_m_)[M12_31]= \
   (_m_)[M12_12]=(_m_)[M12_32]=(_m_)[M12_13]=(_m_)[M12_23]= \
   (_m_)[M12_X]=(_m_)[M12_Y]=(_m_)[M12_Z]=0

#define M12BuildT(_m_,_x_,_y_,_z_) (_m_)[M12_11]=(_m_)[M12_22]= \
   (_m_)[M12_33]=1,(_m_)[M12_21]=(_m_)[M12_31]= \
   (_m_)[M12_12]=(_m_)[M12_32]=(_m_)[M12_13]=(_m_)[M12_23]= \
   (_m_)[M12_X]=(_x_),(_m_)[M12_Y]=(_y_),(_m_)[M12_Z]=(_z_)

#define M16Id(_m_) (_m_)[M16_11]=(_m_)[M16_22]= \
   (_m_)[M16_33]=(_m_)[M16_44]=1,(_m_)[M16_21]=(_m_)[M16_31]= \
   (_m_)[M16_14]=(_m_)[M16_12]=(_m_)[M16_32]=(_m_)[M16_24]= \
   (_m_)[M16_13]=(_m_)[M16_23]=(_m_)[M16_34]=(_m_)[M16_41]= \
   (_m_)[M16_42]=(_m_)[M16_43]=0

#define M9Scale(_dst_,_src_,_s_) \
   (_dst_)[M9_11]=(_src_)[M9_11]*(_s_),(_dst_)[M9_12]=(_src_)[M9_12]*(_s_), \
   (_dst_)[M9_13]=(_src_)[M9_13]*(_s_), \
   (_dst_)[M9_21]=(_src_)[M9_21]*(_s_),(_dst_)[M9_22]=(_src_)[M9_22]*(_s_), \
   (_dst_)[M9_23]=(_src_)[M9_23]*(_s_), \
   (_dst_)[M9_31]=(_src_)[M9_31]*(_s_),(_dst_)[M9_32]=(_src_)[M9_32]*(_s_), \
   (_dst_)[M9_33]=(_src_)[M9_33]*(_s_)

#define M9Neg(_dst_,_src_) \
   (_dst_)[M9_11]=-(_src_)[M9_11],(_dst_)[M9_12]=-(_src_)[M9_12], \
   (_dst_)[M9_13]=-(_src_)[M9_13], \
   (_dst_)[M9_21]=-(_src_)[M9_21],(_dst_)[M9_22]=-(_src_)[M9_22], \
   (_dst_)[M9_23]=-(_src_)[M9_23], \
   (_dst_)[M9_31]=-(_src_)[M9_31],(_dst_)[M9_32]=-(_src_)[M9_32], \
   (_dst_)[M9_33]=-(_src_)[M9_33]

#define M9SetScale(_m_,_sx_,_sy_,_sz_) (_m_)[M9_11]=(_sx_), \
   (_m_)[M9_22]=(_sy_),(_m_)[M9_33]=(_sz_),(_m_)[M9_21]=(_m_)[M9_31]= \
   (_m_)[M9_12]=(_m_)[M9_32]=(_m_)[M9_13]=(_m_)[M9_23]=0

// JFL 06 Sep 06
#define SWAPT(_a_,_b_,_t_) (_t_)=(_a_),(_a_)=(_b_),(_b_)=(_t_)

// transpose in place, use a temp var
#define M9TransposeTmp(_m_,_t_) \
   SWAPT((_m_)[M9_21],(_m_)[M9_12],_t_), \
   SWAPT((_m_)[M9_32],(_m_)[M9_23],_t_), \
   SWAPT((_m_)[M9_31],(_m_)[M9_13],_t_)

/// transpose in place, use temp var
#define M12TransposeTmp(_m_,_t_) \
   SWAPT((_m_)[M12_21],(_m_)[M12_12],_t_), \
   SWAPT((_m_)[M12_32],(_m_)[M12_23],_t_), \
   SWAPT((_m_)[M12_31],(_m_)[M12_13],_t_)

// column of M12
#define M12Column(_m_,_col_) ((_m_)+M12_11+3*(_col_))

/// transpose from one matrix to another -- make sure _d_ is not _s_
#define M9TransposeCpy(_d_,_s_) \
   (_d_)[M9_11]=(_s_)[M9_11],(_d_)[M9_22]=(_s_)[M9_22],(_d_)[M9_33]=(_s_)[M9_33], \
   (_d_)[M9_12]=(_s_)[M9_21],(_d_)[M9_13]=(_s_)[M9_31],(_d_)[M9_21]=(_s_)[M9_12], \
   (_d_)[M9_23]=(_s_)[M9_32],(_d_)[M9_31]=(_s_)[M9_13],(_d_)[M9_32]=(_s_)[M9_23]

/// transpose from one matrix to another -- make sure _d_ is not _s_
#define M12TransposeCpy(_d_,_s_) \
   (_d_)[M12_X]=(_s_)[M12_X],(_d_)[M12_Y]=(_s_)[M12_Y],(_d_)[M12_Z]=(_s_)[M12_Z], \
   (_d_)[M12_11]=(_s_)[M12_11],(_d_)[M12_22]=(_s_)[M12_22],(_d_)[M12_33]=(_s_)[M12_33], \
   (_d_)[M12_12]=(_s_)[M12_21],(_d_)[M12_13]=(_s_)[M12_31],(_d_)[M12_21]=(_s_)[M12_12], \
   (_d_)[M12_23]=(_s_)[M12_32],(_d_)[M12_31]=(_s_)[M12_13],(_d_)[M12_32]=(_s_)[M12_23]

///< M12InvXYZ() set XYZ after the rot part of inv mat is calculated
#define M12InvXYZ(_dst_,_src_) \
	(_dst_)[M12_X] = -((_dst_)[M12_11]*(_src_)[M12_X] \
      +(_dst_)[M12_21]*(_src_)[M12_Y]+(_dst_)[M12_31]*(_src_)[M12_Z]), \
	(_dst_)[M12_Y] = -((_dst_)[M12_12]*(_src_)[M12_X] \
		+(_dst_)[M12_22]*(_src_)[M12_Y]+(_dst_)[M12_32]*(_src_)[M12_Z]), \
	(_dst_)[M12_Z] = -((_dst_)[M12_13]*(_src_)[M12_X] \
      +(_dst_)[M12_23]*(_src_)[M12_Y]+(_dst_)[M12_33]*(_src_)[M12_Z])

typedef struct {float m[9];} qeM9f;
#define M9Cpyf(_d_,_s_) *((qeM9f*)(_d_))=*((qeM9f*)(_s_))

typedef struct {double m[9];} qeM9d;
#define M9Cpyd(_d_,_s_) *((qeM9d*)(_d_))=*((qeM9d*)(_s_))

typedef struct {float m[12];} qeM12f;
#define M12Cpyf(_d_,_s_) *((qeM12f*)(_d_))=*((qeM12f*)(_s_))

typedef struct {double m[12];} qeM12d;
#define M12Cpyd(_d_,_s_) *((qeM12d*)(_d_))=*((qeM12d*)(_s_))

typedef struct {float m[16];} qeM16f;
#define M16Cpyf(_d_,_s_) *((qeM16f*)(_d_))=*((qeM16f*)(_s_))

typedef struct {double m[16];} qeM16d;
#define M16Cpyd(_d_,_s_) *((qeM16d*)(_d_))=*((qeM16d*)(_s_))

typedef struct {float m[3];} qeVecf;
#define VecCpyf(_d_,_s_) *((qeVecf*)(_d_))=*((qeVecf*)(_s_))

typedef struct {double m[3];} qeVecd;
#define VecCpyd(_d_,_s_) *((qeVecd*)(_d_))=*((qeVecd*)(_s_))

typedef struct {float m[4];} qeQuatf;
#define QuatCpyf(_d_,_s_) *((qeQuatf*)(_d_))=*((qeQuatf*)(_s_))

typedef struct {double m[4];} qeQuatd;
#define QuatCpyd(_d_,_s_) *((qeQuatd*)(_d_))=*((qeQuatd*)(_s_))

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++ wrapper
}                   //
#endif              //

#endif // GPMATH_H
