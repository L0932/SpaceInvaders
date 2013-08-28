// Copyright (C) 2008-2009 Joe Linhoff, All Rights Reserved
// demoncore.h
#ifndef DEMONCORE_H
#define DEMONCORE_H

#define DEMONCORE_VERS 0x0002

// build notes
// _CRT_SECURE_NO_DEPRECATE;DEBUG=1;WIN32_LEAN_AND_MEAN;NOCOMM;BUILD_MSVC=1
// link (all configurations) with Multi-threaded DLL (/MD)

// JFL 08 Dec 07
class Vec3 : public qe 
{
public:
   float x; ///< must land in memory: x y z
   float y;
   float z;
public:
   Vec3() {}
   Vec3(const float *xyz);
   Vec3(float x,float y,float z);
   float *adr() const;
   void clear();
   void set(float x,float y,float z);
   void set(const float *xyz);
   void get(float *dst3) const;
   Vec3 get(void) const;

   Vec3 operator+(const Vec3 &v) const;
   Vec3 operator+(const float *v) const;
   void operator+=(const Vec3 &v);
   void operator+=(const float *v);
   Vec3 operator-() const;
   Vec3 operator-(const Vec3 &v) const;
   Vec3 operator-(const float *v) const;
   void operator-=(const Vec3 &v);
   void operator-=(const float *v);
   void operator*=(float mul);
   void operator*=(const Vec3 &v);
   void operator*=(const float *v);
   Vec3 operator*(float mul) const;
   Vec3 operator/(float div) const;
   float operator[](int index) const;
   float len() const;
   float lenSquared() const;
   float dist(const Vec3 &v) const;
   bit lenIsZero() const;
   Vec3 normal() const; ///< return normal vector
   int normalize(); ///< normalize in place, return -1 if not normalizable
   float dot(const Vec3 &v) const;
   Vec3 cross(const Vec3 &v) const;
   void updateMin(const Vec3 &v);
   void updateMax(const Vec3 &v);
   static Vec3 calcNormal(const Vec3 &v0,const Vec3 &v1,const Vec3 &v2);
   static Vec3 randMinMax(float xMin,float xMax,
      float yMin,float yMax,float zMin,float zMax);
}; // class Vec3

class Vec4 : public Vec3
{
public:
   float w;
public:
   Vec4() {}
   Vec4(const float *xyzw);
   Vec4(float x,float y,float z,float w);
   Vec4(const Vec3 &xyz,float w);
   Vec4(const Vec3 &xyz);
   float *adr() const;
   void set(float x,float y,float z,float w);
   static Vec4 planeEq(const Vec3 &v0,const Vec3 &v1,const Vec3 &v2);
}; // class Vec4

// JFL 05 Feb 08
class Mat9 : public qe
{
   // on paper:
   //  a d g
   //  b e h
   //  c f i
   // in memory: a b c d e f g h i
public:
   float a;
   float b;
   float c;
   float d;
   float e;
   float f;
   float g;
   float h;
   float i;
public:
   Mat9() {}
   Mat9(float a,float b,float c,float d,float e,float f,
      float g,float h,float i); // down, then right
   float *adr() const;
   void set(const float *src9);
   void set(float a,float b,float c,float d,float e,float f,
      float g,float h,float i); // down, then right
   void setAcross(float a,float d,float g,float b,float e,float h,
      float c,float f,float i); // right, then down
   void get(float *dst9) const;
   void identity(); // set the identity
   void clear(); // zero all elements
   void operator*=(const Mat9 &cat);
   void operator*=(const float *cat);
   Mat9 operator*(const Mat9 &cat) const;
   Mat9 operator*(const float *cat) const;
   void transpose();
   Vec3 column(int n); // get column of matrix
   int invert(); // return -1 if not invertible
   Mat9 inverse() const; // return identity if not invertible
   Vec3 rotate(const Vec3 &v) const;
   Vec3 rotateInverse(const Vec3 &v) const; // rotate v by inverse mat
   Vec3 rotateTranspose(const Vec3 &v) const; // rotate v by transposed mat
   void buildRotRad(const Vec3 &rad3);
   void buildRotRad(const float *rad3);
   void buildRotAxis(const float rad,const Vec3 &v); // build CCW rotation mat
   void buildRotAxis(const float rad,const float *v); // build CCW rotation mat
   void buildScale(float sx,float sy,float sz); // build scale mat
   void buildScale(const Vec3 &v); // build scale mat
   float scaleRadius(float radius);
}; // class Mat9

// JFL 05 Feb 08
class Mat12 : public qe
{
   // on paper:
   //  x y z
   //  a d g
   //  b e h
   //  c f i
   // in memory: x y z a b c d e f g h i
public:
   Vec3 xyz;
   Mat9 rot;
public:
   Mat12() {}
   float* adr() const;
   void setVec(const Vec3 &v);
   void setMat(const Mat9 &m);
   void set(float *src12);
   void set(float x,float y,float z,
      float a,float b,float c,float d,float e,float f,
      float g,float h,float i); // down, then right
   void setAcross(float x,float y,float z,
      float a,float d,float g,float b,float e,float h,
      float c,float f,float i); // right, then down
   void get(float *dst12); // copy elements out
   void identity(); // set to identity
   void build(float *xyz,float *rot,float *scale); // build
   void build(const Vec3 *xyz,const Vec3 *rot,const Vec3 *scale); // build
   Vec3 transform(const Vec3 &v) const; // transform v by mat
   Vec3 transform(const float *) const; // transform v by mat
   Vec3 transformInverse(const Vec3 &v) const; // transform v by inverse mat
   Vec3 transformTranspose(const Vec3 &v) const; // transform by transposed mat
   void operator*=(const Mat12 &cat); // concatenate / multiply
   Mat12 operator*(const Mat12 &cat); // concatenate / multiply
   int invert(); // return -1 if not invertible
   Mat12 inverse() const; // return identity if not invertible
}; // class Mat12

// JFL 19 Feb 08
class Quat : public qe {
public:
   float x;
   float y;
   float z;
   float w;
public:
   Quat::Quat() {}
   float* adr() const;
   void set(float x,float y,float z,float w);
   void set(float *xyzw);
   void identity();
   Quat operator*(const Quat &cat) const;
   void operator*=(const Quat &cat);
   Quat operator+(const Vec3 &vec) const;
   void operator+=(const Vec3 &vec);
   void buildRotRad(const float *rad3);
   void buildRotRad(const Vec3 &rad3);
   void buildRotRad(float xa,float ya,float za);
   void buildRotAxis(float rad,const Vec3 &vec);
   Mat9 Quat::toMat9() const;
   static Quat Quat::fromMat9(const Mat9& mat9);
   void normalize();
}; // class Quat

extern int DemonCoreInit(); // initialize the library
extern void DemonCoreFinal(); // finalize the library

#endif // BUILD_DEMONCORE
