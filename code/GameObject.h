#include "qec.h"
#include "demoncore.h"

#ifndef OBJECT_H
#define OBJECT_H

class GameObject: public qe
{
public:
	Mat12 pos;
	Vec3 vel;
	Vec3 acc;
	float rad;

	int dead;
	float dir;
	float timeOfLastUpdate;

	//Vec3 acc;
	virtual int draw()=0;
	virtual int update()=0;
	virtual void zap()=0;

};

#endif