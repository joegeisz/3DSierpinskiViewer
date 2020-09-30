//
//  OpenGL widget
//
#include "sierpinski3dopengl.h"
#include <QtOpenGL>
#include <QMessageBox>
#include <math.h>
#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))

//
//  Constructor
//
Sierpinski3dopengl::Sierpinski3dopengl(QWidget* parent)
    : QOpenGLWidget(parent)
{
    params[0] = 0;
    params[1] = -1;
    params[2] = -1;
    params[3] = -1;
    params[4] = -1;
    params[5] = -1;
    params[6] = -1;
    params[7] = -1;

    displaymode = 0;

    IFSnumpts = 1000;
    IFScolormode = 0;
    IFSraster = 0;

    CUBEnumits = 3;


   mode = 0;
   boxframe = true;
   backgroundColor = 0;
   light = false;
   mouse = false;
   autorotate = false;
   asp = 1;
   dim = 3;
   fov = 0;
   th = ph = 0;
   shaders.clear();
}

//
//  Set shader
//
void Sierpinski3dopengl::setShader(int on)
{
   mode = on;
   //  Request redisplay
   update();
}

//
//  Set lighting
//
void Sierpinski3dopengl::setLighting(int on)
{
   light = on;
   //  Request redisplay
   update();
}

//
//  Set Box Frame
//
void Sierpinski3dopengl::setBoxframe(int on)
{
   boxframe = on;
   //  Request redisplay
   update();
}


//
//  Set Autorotate
//
void Sierpinski3dopengl::setAutorotate(int on)
{
   autorotate = on;
   //  Request redisplay
   update();
}

//
//  Set Background
//
void Sierpinski3dopengl::setBackground(int col)
{
   backgroundColor = col;
   //  Request redisplay
   update();
}


//
//  Set projection
//
void Sierpinski3dopengl::setPerspective(int on)
{
   fov = on ? 55 : 0;
   Projection();
   //  Request redisplay
   update();
}

//
//  Set object
//
void Sierpinski3dopengl::setObject(int type)
{
   obj = objects[type];
   //  Request redisplay
   update();
}

//
//  Make sure we dont set all parameters to -1
//
void Sierpinski3dopengl::assert_not_all_zeros()
{
   if(params[0] == -1
      && params[1] == -1
      && params[2] == -1
      && params[3] == -1
      && params[4] == -1
      && params[5] == -1
      && params[6] == -1
      && params[7] == -1){

       params[0] = 0;
       emit changedParam1(0);
   }

}

//
//  Set Display Mode
//
void Sierpinski3dopengl::setDisplaymode(int mode)
{
   displaymode = mode;

   if(mode == 0){
       obj = tut;
   }

   if(mode == 1){
       obj = att;
   }

   if(mode == 2){
       obj = cubes;
   }

   update();

}

//
//  Set params
//
void Sierpinski3dopengl::setParam1(int sym)   //  Slot to set parameter
{
    params[0] = sym;
    assert_not_all_zeros();
    tut->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    tut->generatePoints();
    att->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    att->generatePoints();
    cubes->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    cubes->generatePoints();
    emit changedParam1(params[0]);
   update();

}

void Sierpinski3dopengl::setParam2(int sym)   //  Slot to set parameter
{
    params[1] = sym;
    assert_not_all_zeros();
    tut->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    tut->generatePoints();
    att->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    att->generatePoints();
    cubes->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    cubes->generatePoints();
    emit changedParam2(params[1]);
   update();

}

void Sierpinski3dopengl::setParam3(int sym)   //  Slot to set parameter
{
    params[2] = sym;
    assert_not_all_zeros();
    tut->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    tut->generatePoints();
    att->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    att->generatePoints();
    cubes->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    cubes->generatePoints();
    emit changedParam3(params[2]);
   update();

}

void Sierpinski3dopengl::setParam4(int sym)   //  Slot to set parameter
{
    params[3] = sym;
    assert_not_all_zeros();
    tut->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    tut->generatePoints();
    att->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    att->generatePoints();
    cubes->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    cubes->generatePoints();
    emit changedParam4(params[3]);
   update();

}

void Sierpinski3dopengl::setParam5(int sym)   //  Slot to set parameter
{
    params[4] = sym;
    assert_not_all_zeros();
    tut->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    tut->generatePoints();
    att->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    att->generatePoints();
    cubes->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    cubes->generatePoints();
    emit changedParam5(params[4]);
   update();

}

void Sierpinski3dopengl::setParam6(int sym)   //  Slot to set parameter
{
    params[5] = sym;
    assert_not_all_zeros();
    tut->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    tut->generatePoints();
    att->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    att->generatePoints();
    cubes->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    cubes->generatePoints();
    emit changedParam6(params[5]);
   update();
}

void Sierpinski3dopengl::setParam7(int sym)   //  Slot to set parameter
{
    params[6] = sym;
    assert_not_all_zeros();
    tut->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    tut->generatePoints();
    att->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    att->generatePoints();
    cubes->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    cubes->generatePoints();
    emit changedParam7(params[6]);
   update();
}

void Sierpinski3dopengl::setParam8(int sym)   //  Slot to set parameter
{
    params[7] = sym;
    assert_not_all_zeros();
    tut->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    tut->generatePoints();
    att->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    att->generatePoints();
    cubes->changeParameters(params[0],params[1],params[2],params[3],params[4],params[5],params[6],params[7]);
    cubes->generatePoints();
    emit changedParam8(params[7]);
   update();

}

//
//  Set Tutorial Example
//
void Sierpinski3dopengl::setExample(int ex)
{
   TutorialExample = ex;

   if(ex == 0){

       setParam1(0);
       setParam2(-1);
       setParam3(-1);
       setParam4(-1);
       setParam5(-1);
       setParam6(-1);
       setParam7(-1);
       setParam8(-1);

   }

   if(ex == 1){

       setParam3(0);
       setParam1(-1);
       setParam2(-1);
       setParam4(-1);
       setParam5(-1);
       setParam6(-1);
       setParam7(-1);
       setParam8(-1);

   }

   if(ex == 2){

       setParam3(29);
       setParam1(-1);
       setParam2(-1);
       setParam4(-1);
       setParam5(-1);
       setParam6(-1);
       setParam7(-1);
       setParam8(-1);

   }

   if(ex == 3){

       setParam1(0);
       setParam2(-1);
       setParam3(-1);
       setParam4(-1);
       setParam5(-1);
       setParam6(-1);
       setParam7(-1);
       setParam8(0);

   }

   if(ex == 4){

       setParam1(0);
       setParam2(-1);
       setParam3(-1);
       setParam4(-1);
       setParam5(-1);
       setParam6(-1);
       setParam7(-1);
       setParam8(5);

   }


   if(ex == 5){

       setParam2(0);
       setParam1(-1);
       setParam3(0);
       setParam4(-1);
       setParam5(0);
       setParam6(-1);
       setParam7(-1);
       setParam8(0);

   }

   if(ex == 6){

       setParam1(0);
       setParam2(0);
       setParam3(0);
       setParam4(0);
       setParam5(0);
       setParam6(-1);
       setParam7(0);
       setParam8(0);

   }

   if(ex == 7){

       setParam1(0);
       setParam2(-1);
       setParam3(0);
       setParam4(0);
       setParam5(-1);
       setParam6(-1);
       setParam7(-1);
       setParam8(-1);

   }

   update();
}

//
//  Set Iterate for tutorial object
//
void Sierpinski3dopengl::setIterate(int on)
{
   TutorialIterate = on;
   tut->setIterate(on);

   update();
}

//
//  Set IFS number of points
//
void Sierpinski3dopengl::setIFSnumpts(int npts)
{
   IFSnumpts = npts;
   att->setNumpts(IFSnumpts);
   att->generatePoints();

   update();
}

//
//  Set IFS colormode
//
void Sierpinski3dopengl::setIFScolormode(int mode)
{
   IFScolormode = mode;
   att->setColormode(IFScolormode);

   update();
}

//
//  Set IFS number of points
//
void Sierpinski3dopengl::setIFSraster(int on)
{
   IFSraster = on;

   update();
}

//
//  Set Cube colormode
//
void Sierpinski3dopengl::setCUBEcolormode(int mode)
{
   CUBEcolormode = mode;
   cubes->setColormode(CUBEcolormode);

   update();
}


//
//  Set number of cube iterations
//
void Sierpinski3dopengl::setCUBEnumits(int nits)
{
   CUBEnumits = nits;
   cubes->setNumits(nits);
   cubes->generatePoints();

   update();
}


//
//  Initialize
//
void Sierpinski3dopengl::initializeGL()
{
   //  Enable Z-buffer depth testing
   glEnable(GL_DEPTH_TEST);

   //  Build shaders
   QOpenGLShaderProgram* wood = new QOpenGLShaderProgram;
   addshader(wood,":/wood.vert",":/wood.frag");
   QOpenGLShaderProgram* rand = new QOpenGLShaderProgram;
   addshader(rand,":/rand.vert",":/rand.frag");
   QOpenGLShaderProgram* perlin = new QOpenGLShaderProgram;
   addshader(perlin,":/PerlinNoise.vert",":/PerlinNoise.frag");
   QOpenGLShaderProgram* move = new QOpenGLShaderProgram;
   addshader(move,":/sierpinski3d.vert",":/sierpinski3d.frag");


   //CubeIterator
   tut = new TutorialObject(0,-1,-1,-1,-1,-1,-1,-1);
   objects.push_back(tut);

   //Attractor
   att = new Attractor(100000,0,-1,-1,-1,-1,-1,-1,-1);
   objects.push_back(att);

   //CubeIterator
   cubes = new CubeIterator(3,0,-1,-1,-1,-1,-1,-1,-1);
   objects.push_back(cubes);


   //  Set initial object
   obj = objects[0];

   //  Start 100 fps timer connected to update
   timer.setInterval(10);
   connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
   timer.start();
   time.start();
}

//
//  Set projection when window is resized
//
void Sierpinski3dopengl::resizeGL(int width, int height)
{
   //  Window aspect ration
   asp = height ? width / (float)height : 1;
   //  Viewport is whole screen
   glViewport(0,0,width,height);
   //  Set projection
   Projection();
}

//
//  Draw vertex in polar coordinates
//
static void Vertex(double th,double ph)
{
   glVertex3d(Sin(th)*Cos(ph),Cos(th)*Cos(ph),Sin(ph));
}

//
//  Draw a ball at (x,y,z) radius r
//
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=10)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=20)
      {
         Vertex(th,ph);
         Vertex(th,ph+10);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

//
//  Draw the window
//
void Sierpinski3dopengl::paintGL()
{
   //  Wall time (seconds)
   float t = 0.001*time.elapsed();

   if(autorotate){
    th = int(t*20) % 360;
   }

   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   if(backgroundColor == 0){
         glClearColor(.5,.5,.5,1);}
   if(backgroundColor == 1){
         glClearColor(0,0,0,1);}
   if(backgroundColor == 2){
         glClearColor(1,1,1,1);}
   if(backgroundColor == 3){
         glClearColor(1,0,0,1);}
   if(backgroundColor == 4){
         glClearColor(0,1,0,1);}
   if(backgroundColor == 5){
         glClearColor(0,0,1,1);}

   //  Set view
   glLoadIdentity();
   if (fov) glTranslated(0,0,-2*dim);
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);

   //  Enable lighting
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]  = {0.3,0.3,0.3,1.0};
      float Diffuse[]  = {0.8,0.8,0.8,1.0};
      float Specular[] = {1.0,1.0,1.0,1.0};
      float Position[] = {(float)(3*Cos(90*t)),3.0,(float)(3*Sin(90*t)),1.0};
      //  Draw light position (no lighting yet)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }

   glDisable(GL_PROGRAM_POINT_SIZE);
   if(displaymode == 1 && IFSraster ){
       glEnable(GL_PROGRAM_POINT_SIZE);
   }

   //  Apply shader
   if (mode)
   {
      shaders.at(mode-1)->bind();
      shaders.at(mode-1)->setUniformValue("time",t);
   }

   //  Draw scene
   if (obj) obj->display();

   //  Release shader
   if (mode) shaders.at(mode-1)->release();

   //  Disable lighting
   glDisable(GL_LIGHTING);
   
   //  Draw Axes boxes
    if(boxframe){
       glColor3f(1,1,1);
       glBegin(GL_LINES);
       glVertex3d(-1,0,0);
       glVertex3d(1,0,0);
       glVertex3d(0,-1,0);
       glVertex3d(0,1,0);
       glVertex3d(0,0,-1);
       glVertex3d(0,0,1);
       glVertex3d(1,1,1);
       glVertex3d(1,1,-1);
       glVertex3d(-1,-1,1);
       glVertex3d(-1,-1,-1);
       glVertex3d(1,1,-1);
       glVertex3d(1,1,1);
       glVertex3d(1,-1,-1);
       glVertex3d(1,-1,1);
       glVertex3d(-1,1,-1);
       glVertex3d(-1,1,1);
       glVertex3d(-1,1,1);
       glVertex3d(1,1,1);
       glVertex3d(-1,-1,1);
       glVertex3d(1,-1,1);
       glVertex3d(-1,1,1);
       glVertex3d(1,1,1);
       glVertex3d(-1,-1,-1);
       glVertex3d(1,-1,-1);
       glVertex3d(-1,1,-1);
       glVertex3d(1,1,-1);
       glVertex3d(1,-1,1);
       glVertex3d(1,1,1);
       glVertex3d(-1,-1,1);
       glVertex3d(-1,1,1);
       glVertex3d(-1,-1,-1);
       glVertex3d(-1,1,-1);
       glVertex3d(1,-1,-1);
       glVertex3d(1,1,-1);
       glVertex3d(0,-1,1);
       glVertex3d(0,1,1);
       glVertex3d(0,-1,-1);
       glVertex3d(0,1,-1);
       glVertex3d(-1,-1,0);
       glVertex3d(-1,1,0);
       glVertex3d(1,-1,0);
       glVertex3d(1,1,-0);
       glVertex3d(0,1,-1);
       glVertex3d(0,1,1);
       glVertex3d(0,-1,-1);
       glVertex3d(0,-1,1);
       glVertex3d(1,0,-1);
       glVertex3d(1,0,1);
       glVertex3d(-1,0,-1);
       glVertex3d(-1,0,1);
       glVertex3d(-1,1,0);
       glVertex3d(1,1,0);
       glVertex3d(-1,-1,0);
       glVertex3d(1,-1,0);
       glVertex3d(-1,0,1);
       glVertex3d(1,0,1);
       glVertex3d(-1,0,-1);
       glVertex3d(1,0,-1);
       glEnd();
    }

   //  Emit angles to display
   emit angles(QString::number(th)+","+QString::number(ph));
}

//
//  add a new shader
//
void Sierpinski3dopengl::addshader(QOpenGLShaderProgram* shdr, QString vert, QString frag )
{
    if (!shdr->addShaderFromSourceFile(QOpenGLShader::Vertex,vert))
       Fatal("Error compiling sierpinski3d.vert\n"+shdr->log());
    if (!shdr->addShaderFromSourceFile(QOpenGLShader::Fragment,frag))
       Fatal("Error compiling sierpinski3d.frag\n"+shdr->log());
    if (!shdr->link())
       Fatal("Error linking shader\n"+shdr->log());
    shaders.append(shdr);

}


//
//  Throw a fatal error and die
//
void Sierpinski3dopengl::Fatal(QString message)
{
   QMessageBox::critical(this,"Sierpinski3dopengl",message);
   QApplication::quit();
}

//
//  Set OpenGL projection
//
void Sierpinski3dopengl::Projection()
{
   makeCurrent(); //  This is a a kludge because this may be called out of order
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (fov)
   {
      float zmin = dim/4;
      float zmax = 4*dim;
      float ydim = zmin*tan(fov*M_PI/360);
      float xdim = ydim*asp;
      glFrustum(-xdim,+xdim,-ydim,+ydim,zmin,zmax);
   }
   else
      glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/******************************************************************/
/*************************  Mouse Events  *************************/
/******************************************************************/
//
//  Mouse pressed
//
void Sierpinski3dopengl::mousePressEvent(QMouseEvent* e)
{
   mouse = true;
   pos = e->pos();  //  Remember mouse location
}

//
//  Mouse released
//
void Sierpinski3dopengl::mouseReleaseEvent(QMouseEvent*)
{
    mouse = false;
}

//
//  Mouse moved
//
void Sierpinski3dopengl::mouseMoveEvent(QMouseEvent* e)
{
   if (mouse)
   {
      QPoint d = e->pos()-pos;  //  Change in mouse location
      th = (th+d.x())%360;      //  Translate x movement to azimuth
      ph = (ph+d.y())%360;      //  Translate y movement to elevation
      pos = e->pos();           //  Remember new location
      update();               //  Request redisplay
   }
}

//
//  Mouse wheel
//
void Sierpinski3dopengl::wheelEvent(QWheelEvent* e)
{
   //  Zoom out
   if (e->delta()<0)
      dim += 0.1;
   //  Zoom in
   else if (dim>1)
      dim -= 0.1;
   //  Request redisplay
   Projection();
   update();
}
