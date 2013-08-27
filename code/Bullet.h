#include "GameObject.h"
#include "qec.h"
#include "demoncore.h"


class Bullet : public qeListBase, public GameObject {
public:
   Bullet::Bullet(); // ctor
   chr name[16]; // name of object
   float lastUpdateTime; // time of last update
   float timeToExpire; // time to remove from system
   Vec3 xyzOld; // previous position
   Vec3 vel; // velocity
   bit col;

   int update(); // update
   int draw(); // draw
   void zap(); // controlled delete
}; // class Bullet