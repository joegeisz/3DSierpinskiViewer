//
//  Attractor Class
//  inherits from object, represents the set of points
//  making up the trajectory of the IFS which approximates
//  the fractal
//

#ifndef ATTRACTOR_H
#define ATTRACTOR_H

#include <QQueue>
#include <QVector>
#include "Object.h"
#include "structs.h"

class Attractor : public Object
{
private:
    int params[8];
    int numpts;
    int numcubes;
    int colormode;
    QQueue<int> usedcubes;
    QQueue<affine*> transforms;
    QVector<point*> pointcloud;
public:
    Attractor();
    Attractor( int numpts, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
    void generatePoints();
    void setNumpts(int num);
    void setColormode(int mode);
    void changeParameters(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8 );
    void fillTransformQueue();
    void display();
    affine* symmetrytransform(int sym, int cube);
    point* applytransform(point* p, affine* T);
    color* cubecolor(int cube);
    color* averagecolor(color* c1, color* c2);

};


#endif // ATTRACTOR_H
