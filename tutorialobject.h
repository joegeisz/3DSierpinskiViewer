//
//  Tutorial Class
//  inherits from object, creates an object that shows
//  how the processes of iterating cubes works
//

#ifndef TUTORIALOBJECT_H
#define TUTORIALOBJECT_H

#include <QQueue>
#include <QVector>
#include "Object.h"
#include "structs.h"


class TutorialObject : public Object
{
private:
    int params[8];
    int numcubes;
    int colormode;
    int iterate;

    QQueue<int> usedcubes;
    QQueue<affine*> transforms;

    QQueue<point*>* pointcloud;

    QQueue<point*> pointcloud0;
    QQueue<point*> pointcloud1;
    QQueue<point*> pointcloud2;
    QQueue<point*> pointcloud3;

public:
    TutorialObject();
    TutorialObject( int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
    void generatePoints();
    void setColormode(int mode);
    void setIterate(int on);
    void changeParameters(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8 );
    void fillTransformQueue();
    void display();
    void display3DL();
    void displayCube(point c, float e);
    color* cubecolor(int cube);
    color* averagecolor(color* c1, color* c2);
    affine* symmetrytransform(int sym, int cube);
    point* applytransform(point* p, affine* T);

};


#endif // TUTORIALOBJECT_H
