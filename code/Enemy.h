#include "GameObject.h"

class Enemy : public GameObject, public qeListBase
{
public:
	chr name[16];
	//qeGeo2 *geo_Alien1;
	Vec3 xyzOld;

	Enemy::Enemy();

	int type;
	int shoot();
	qeGeo2 *geo;
	Vec3 xyzCol;
	Vec3 nrmCol;
	Vec3 offToTarget;

	int update(); // update
    int draw(); // draw
    void zap(); // controlled delete
};