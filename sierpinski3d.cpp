//
//  Ex01:  Basic Shader
//  Willem A. (Vlakkies) Schreuder
//  CSCI 4239/5239 Spring 2020
//

#include <QApplication>
#include "sierpinski3dviewer.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show view widget
   Sierpinski3dviewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
