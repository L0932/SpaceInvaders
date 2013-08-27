#include "GameObject.h"

// HeadsUp -- heads up display class
class HeadsUp : public qe {
public:
   chr name[16]; // internal name
   HeadsUp::HeadsUp(); // ctor

   int setUVTexCoord(chr *name, int number, float &u0, float &u1, float &v0, float &v1, int iconW, int iconH);
   int update(); // update score
   void zap(); // controlled delete
   int drawTimer();// draw function
   int drawScore();
   int drawAmmo();
   void drawHUD();
}; // class HeadsUp