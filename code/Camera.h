#include "qec.h"
#include "demoncore.h"

class Camera: public qe {

	chr name[16];
public:
	float fovyHalfRad; //half field of view angle in y direction in radians
	float nearClip; 
	float farClip;
	float winWidth;
	float winHeight;
	float winWDivH;// Width divided by Height
	float nearHeight;
	Camera(); //constructor
	void zap();
	int apply();
	Vec3 pos;
	Vec3 lookat;
	Vec3 up;
	Mat12 mat;

}; //class Camera 

