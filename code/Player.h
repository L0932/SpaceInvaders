#include "GameObject.h"

class Player : public GameObject //: public qeListBase
{
public:
	Player::Player();
	
	virtual int draw();
	virtual int update();
	//int inputUpdate();
	virtual void zap();
    int shoot();

}; // class Ship
