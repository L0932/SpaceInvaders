

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Camera

Camera::Camera()
{
	// set camera parameters
	this->fovyHalfRad = DEGTORAD(45);
	this->nearClip = 1;
	this->farClip = 60;
	this->nearHeight = MathTanf(this->fovyHalfRad)*this->nearClip;

	// cam
	this->pos=Vec3(0, 0, 9);
	this->lookat=Vec3(0,0,0);
	this->up=Vec3(0,1,0);

	this->mat.identity();

} // Camera::Camera()

int Camera::apply()
{
	int r;

	//openGL states
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	// current window size & aspect ratio
	if (qeGetWindowSize(&this->winWidth, &this->winHeight)<0)
		bret(-2);
	this->winWDivH=this->winWidth/this->winHeight;

	// set projection -- lens
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-this->nearHeight*this->winWDivH, this->nearHeight*this->winWDivH,
		-this->nearHeight, this->nearHeight, this->nearClip,this->farClip);

	// set modelview -- position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// calculate and set camera matrix
	qeCamLookAtM12f(this->mat.adr(), this->pos.adr(),
		this->lookat.adr(), this->up.adr()); // cam mat
	qeGLM12f(this->mat.adr()); // set matrix

	r=0;

BAIL:
	return r;

} // Camera::apply()

void Camera::zap()
{
	delete this;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Player

Player::Player()
{
	this->pos.identity();
}

//RB 5/10/2011 Simple Player Geometry
//6 vertices
float PlayerVerts[] = 
{
	 0, 0, 0,    -1, 0, 0,//lower-left vert
	 0, 0, 0,
	-0.5,  2, 0, //top vert
};

//4 faces
int PlayerFaces[] =
{
	3, 3, 1, 4, 3,
}; // PlayerFaces

//Player geometry
qeGeo1 PlayerGeo = 
{
	4, //numv
	1, //numf
	PlayerVerts, //verts
	PlayerFaces, //faces
}; //PlayerGeo

int Player::update()
{
	float t;
	uns b;
	float a;
	Mat9 rvel;
	this->acc = Vec3(0,0,0);
	 // update time
   t=this->timeOfLastUpdate;
   this->timeOfLastUpdate=qeTimeFrame();
   t=this->timeOfLastUpdate-t;

    b=qeInpButton(QEINPBUTTON_UP);

	//this->vel = Vec3(1,1,0);
   if(b&1) //&& (b!=Game.btnDown))
   {
	   //Game.btnDown = b;
	   this->vel = this->pos.rot.rotate(Vec3(0,0,0)*t);
	   //this->pos.xyz.x += MathACosf(this->vel.x)*t;
	   //this->pos.xyz.y += MathASinf(this->vel.y)*t;

   }

   //add thrust vector in direction of Player 
   //Player is 000ZY -- z forward -- rotate thrust to match Player's rot
   b=qeInpButton(QEINPBUTTON_DOWN);
   if(b&1) //&& (b!=Game.btnDown))
   {
	   //Game.btnDown = b;
	   this->vel += this->pos.rot.rotate(Vec3(0,10,0)*t);
   }

   //rotate Player
   a=0; //default, no rotation
   b=qeInpButton(QEINPBUTTON_LEFT);
   if(b&1)
   {
	   a=(PI/0.5)*t; //angular velocity (1 rotation per 1/2 second);

   }

   b=qeInpButton(QEINPBUTTON_RIGHT);
   if(b&1)
   {
	   a=-(PI/0.5)*t; //angular velocity (1 rotation per 1/2 second);
	   //this->vel *= Vec3(-1,0,0);
   }

   rvel.buildRotAxis(a,Vec3(0,0,1)); //rotational velocity
   this->pos.rot*=rvel; // add rotational velocity for frame


   if (this->pos.xyz.y > MAX_Y || this->pos.xyz.y < -MAX_Y || this->pos.xyz.x > MAX_X || this->pos.xyz.x < -MAX_X)
   {
	   this->vel *= -1;
   }

   this->pos.xyz += this->vel*t;
  
	return 0;
};

int Player::draw()
{
	// draw the base
      //glTranslatef(this->xyz.x,this->xyz.y,this->xyz.z); // position
      //deg = (this->yaBaseRad*180.0)/PI; // radians -> degrees
      //glRotatef(deg,0,1,0); // rotate the base
	//glPolygonMode(GL_FRONT,GL_LINE);
	float deg;
	deg = (this->rad*360.0)/PI;


	glPushMatrix();
	qeGLM12f(this->pos.adr());
	glRotatef(deg,0,0,1);
	glTranslatef(0,-1,0);

    qeGeo1 *geo=&PlayerGeo; // pointer to tank base geometry
    qeDrawFaces(geo->verts,geo->faces,geo->numf);
	//glTranslatef(1.5,1.5,1.5);

	
	glPopMatrix();


	return 0;
}

void Player::zap()
{
	delete this;
}
///////////////////////////////////////////////////////////////////////////////
// Bullet

