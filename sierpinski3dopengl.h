//
//  OpenGL Sierpinski3dopengl Widget
//

#ifndef SIERPINSKI3DOPENGL_H
#define SIERPINSKI3DOPENGL_H

#include <QtOpenGL>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QElapsedTimer>
#include "Object.h"
#include "cubeiterator.h"
#include "attractor.h"
#include "tutorialobject.h"
#include "structs.h"

class Sierpinski3dopengl : public QOpenGLWidget
{
Q_OBJECT
private:

   int params[8];     //  3D Sierpinski Parameters
   int displaymode; //  0 for IFS, 1 for cube iteration

   int TutorialExample;  //which example in the tutorial
   int TutorialIterate;

   int IFSnumpts;     //  number of points to display while in IFS mode
   int IFScolormode;    // colormode for displaying IFS points
   int IFSraster;       //turn on or off raster points

   int CUBEnumits;    //  number of iterations to display in cube mode
   int CUBEcolormode;    // colormode for displaying IFS points


   bool    light;     //  Lighting
   bool    boxframe;   //  display the boxframe
   bool    autorotate;  // rotate automatically
   int     backgroundColor; // change the background
   int     mode;      //  Display mode
   int     th,ph;     //  Display angles
   bool    mouse;     //  Mouse pressed
   QPoint  pos;       //  Mouse position
   int     fov;       //  Field of view
   double  dim;       //  Display size
   double  asp;       //  Sceen aspect ratio
   Object* obj;       //  Object
   QTimer           timer;       //  Timer for animations
   QElapsedTimer    time;        //  Track elapsed time
   QVector<QOpenGLShaderProgram*> shaders;  //  Shader
   QVector<Object*> objects;     //  Objects

   Attractor* att;
   CubeIterator* cubes;
   TutorialObject* tut;

public:
   Sierpinski3dopengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
   void assert_not_all_zeros();
   void addshader(QOpenGLShaderProgram* shdr, QString vert, QString frag );
public slots:
   void setDisplaymode(int on);            //  Slot to set Display Mode

   void setExample(int ex);                 // Slot to set the example in the tutorial mode
   void setIterate(int on);                 // Slot to set the example in the tutorial mode

   void setIFSnumpts(int on);              //  Slot to set number of IFS points
   void setIFScolormode(int mode);              //  Slot to set the IFS color mode
   void setIFSraster(int on);              //  Slot to set the IFS raster


   void setCUBEnumits(int type);           //  Slot to set number of iterations in cube mode
   void setCUBEcolormode(int mode);              //  Slot to set the CUBE color mode

   void setParam1(int sym);             //Slots to set the 8 parameters
   void setParam2(int sym);
   void setParam3(int sym);
   void setParam4(int sym);
   void setParam5(int sym);
   void setParam6(int sym);
   void setParam7(int sym);
   void setParam8(int sym);

    void setShader(int on);                //  Slot to set shader
    void setPerspective(int on);           //  Slot to set projection type
    void setObject(int type);              //  Slot to set displayed object
    void setLighting(int on);              //  Slot to set lighting
    void setBoxframe(int on);              //  Slot to set lighting
    void setAutorotate(int on);            // Slot to set the rotation
    void setBackground(int col);            // Slot to set the background color
signals:
    void angles(QString text);             //  Signal for view angles

    void changedParam1(int sym);        // Tell parameter bar that parameters were changed by the tutorial function
    void changedParam2(int sym);
    void changedParam3(int sym);
    void changedParam4(int sym);
    void changedParam5(int sym);
    void changedParam6(int sym);
    void changedParam7(int sym);
    void changedParam8(int sym);

protected:
    void initializeGL();                   //  Initialize widget
    void resizeGL(int width, int height);  //  Resize widget
    void paintGL();                        //  Draw widget
    void mousePressEvent(QMouseEvent*);    //  Mouse pressed
    void mouseReleaseEvent(QMouseEvent*);  //  Mouse released
    void mouseMoveEvent(QMouseEvent*);     //  Mouse moved
    void wheelEvent(QWheelEvent*);         //  Mouse wheel
private:
   void Fatal(QString message);            //  Error handler
   void Projection();                      //  Update projection


};

#endif
