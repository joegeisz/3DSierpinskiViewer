//
//  Cube Iterator Class
//  inherits from object, represents the cubes
//  that cover the fractal at a given iteration
//


#ifndef CUBEITERATOR_H
#define CUBEITERATOR_H

#include <QQueue>
#include <QVector>
#include "Object.h"
#include "structs.h"


class CubeIterator : public Object
{
private:
    int params[8];
    int numits;
    int numcubes;
    int colormode;
    QQueue<int> usedcubes;
    QQueue<affine*> transforms;
    QQueue<point*> pointcloud;
public:
    CubeIterator();
    CubeIterator( int numpts, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
    void generatePoints();
    void setNumits(int num);
    void setColormode(int mode);
    void changeParameters(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8 );
    void fillTransformQueue();
    void display();
    void displayCube(point c, float e);
    color* cubecolor(int cube);
    color* averagecolor(color* c1, color* c2);
    affine* symmetrytransform(int sym, int cube);
    point* applytransform(point* p, affine* T);

};


#endif // CUBEITERATOR_H
