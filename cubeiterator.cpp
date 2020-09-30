#include "cubeiterator.h"
#include <stdlib.h>

/************
 * Attractor constructor.
 *       Default Sierpinski Tetrahedron with 1000 points.
 ************
 */
CubeIterator::CubeIterator()
{
    numits = 3;
    colormode = 0;
    changeParameters(-1,0,0,-1,0,-1,-1,0);
    fillTransformQueue();
    generatePoints();

};



/* ***********
 * Attractor constructor.
 * ***********
 *      num = number of points in orbit
 *      p1-p8 = parameters
 *
 */
CubeIterator::CubeIterator(int num, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
    numits = num;
    colormode = 0;
    changeParameters(p1,p2,p3,p4,p5,p6,p7,p8);
    fillTransformQueue();
    generatePoints();

}



/* ***********
 * Generate the orbit of points
 * ***********
 *      fills in pointcloud
 *
 */
void CubeIterator::generatePoints()
{

    pointcloud.clear();

    point* ic = new point;
    ic->x = 0.0;
    ic->y = 0.0;
    ic->z = 0.0;

    point* next;
    for(int i = 0; i < numcubes; i++){
        next = applytransform(ic, transforms.at(i));
        next->cube = *cubecolor(usedcubes.at(i));
        next->past = *cubecolor(usedcubes.at(i));
        pointcloud.enqueue(next);
    }

    for(int k = 1; k < numits; k++){
        for(int j = 0; j < pow(numcubes,k); j++){
            for(int i = 0; i < numcubes; i++){
                next = applytransform(pointcloud.at(0), transforms.at(i));
                next->cube = *cubecolor(usedcubes.at(i));
                next->past = *averagecolor(&pointcloud.at(0)->past,&next->cube);
                pointcloud.enqueue(next);
            }
            pointcloud.dequeue();
        }
    }
}



/* ***********
 * OpenGL display
 * ***********
 */
void CubeIterator::display()
{
    if (!show) return;
    //  Save transformation
    glPushMatrix();
    //  Texture on
    EnableTex();
    //  Front
    double e = pow(.5,numits);

    if(colormode == 0){
        for(int i = 0; i < pow(numcubes,numits); i++)
        {
            useColor(Color(pointcloud[i]->cube.r,pointcloud[i]->cube.g,pointcloud[i]->cube.b));
            displayCube(*pointcloud[i], e);

        }
    }


    if(colormode == 1){
        for(int i = 0; i < pow(numcubes,numits); i++)
        {

            useColor(Color(pointcloud[i]->past.r,pointcloud[i]->past.g,pointcloud[i]->past.b));
            displayCube(*pointcloud[i], e);

        }
    }


    if(colormode == 2){
        for(int i = 0; i < pow(numcubes,numits); i++)
        {

            useColor(Color(pointcloud[i]->x,pointcloud[i]->y,pointcloud[i]->z));
            displayCube(*pointcloud[i], e);

        }
    }


    //  Texture off
    DisableTex();
    //  Undo transofrmations
    glPopMatrix();

}



/* ***********
 * display the Cube
 * ***********
 *     display a cube with center c and sidelength e
 */
void CubeIterator::displayCube(point c, float e)
{
    float x = c.x;
    float y = c.y;
    float z = c.z;

    glBegin(GL_QUADS);
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0,0); glVertex3f(x-e,y-e, z+e);
    glTexCoord2f(1,0); glVertex3f(x+e,y-e, z+e);
    glTexCoord2f(1,1); glVertex3f(x+e,y+e, z+e);
    glTexCoord2f(0,1); glVertex3f(x-e,y+e, z+e);
    glEnd();
    //  Back
    glBegin(GL_QUADS);
    glNormal3f( 0, 0,-1);
    glTexCoord2f(0,0); glVertex3f(x+e,y-e,z-e);
    glTexCoord2f(1,0); glVertex3f(x-e,y-e,z-e);
    glTexCoord2f(1,1); glVertex3f(x-e,y+e,z-e);
    glTexCoord2f(0,1); glVertex3f(x+e,y+e,z-e);
    glEnd();
    //  Right
    glBegin(GL_QUADS);
    glNormal3f(+1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(x+e,y-e,z+e);
    glTexCoord2f(1,0); glVertex3f(x+e,y-e,z-e);
    glTexCoord2f(1,1); glVertex3f(x+e,y+e,z-e);
    glTexCoord2f(0,1); glVertex3f(x+e,y+e,z+e);
    glEnd();
    //  Left
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(x-e,y-e,z-e);
    glTexCoord2f(1,0); glVertex3f(x-e,y-e,z+e);
    glTexCoord2f(1,1); glVertex3f(x-e,y+e,z+e);
    glTexCoord2f(0,1); glVertex3f(x-e,y+e,z-e);
    glEnd();
    //  Top
    glBegin(GL_QUADS);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(x-e,y+e,z+e);
    glTexCoord2f(1,0); glVertex3f(x+e,y+e,z+e);
    glTexCoord2f(1,1); glVertex3f(x+e,y+e,z-e);
    glTexCoord2f(0,1); glVertex3f(x-e,y+e,z-e);
    glEnd();
    //  Bottom
    glBegin(GL_QUADS);
    glNormal3f( 0,-1, 0);
    glTexCoord2f(0,0); glVertex3f(x-e,y-e,z-e);
    glTexCoord2f(1,0); glVertex3f(x+e,y-e,z-e);
    glTexCoord2f(1,1); glVertex3f(x+e,y-e,z+e);
    glTexCoord2f(0,1); glVertex3f(x-e,y-e,z+e);
    glEnd();
}


/* ***********
 * fill Transform Queue
 * ***********
 *      Fills in transforms, the IFS affine contratction maps which describe the attractor
 *      Also calculates numcubes
 */
void CubeIterator::fillTransformQueue()
{
    transforms.clear();
    usedcubes.clear();

    numcubes = 0;

    for(int i = 0; i < 8; i++){
        if(params[i] != -1){
            numcubes = numcubes+1;
            transforms.enqueue(symmetrytransform(params[i], i+1));
            usedcubes.enqueue(i+1);
        }
    }
}

/* ***********
 * Change Parameters
 * ***********
 *     Sets the parameters of the attractor
 */
void CubeIterator::changeParameters(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
    params[0] = p1;
    params[1] = p2;
    params[2] = p3;
    params[3] = p4;
    params[4] = p5;
    params[5] = p6;
    params[6] = p7;
    params[7] = p8;

    fillTransformQueue();
}


/* ***********
 * Set Number of points
 * ***********
 *     Sets the parameters of the attractor
 */
void CubeIterator::setNumits(int num)
{
    numits = num;

}

/* ***********
 * Set Colormode
 * ***********
 *     Sets the colormode
 */
void CubeIterator::setColormode(int mode)
{
    colormode = mode;

}

/* ***********
 * Color Cube
 * ***********
 *     gives the color associated with each cube
 */
color* CubeIterator::cubecolor(int cube)
{
    color* c = new color;

    switch (cube) {

        case 1: c->r = 0; c->g = 1; c->b = 0; break;
        case 2: c->r = 0.2; c->g = 0.2; c->b = 0.2; break;
        case 3: c->r = 1; c->g = 0; c->b = 0; break;
        case 4: c->r = 1; c->g = 1; c->b = 0; break;
        case 5: c->r = 1; c->g = 0; c->b = 1; break;
        case 6: c->r = 1; c->g = 1; c->b = 1; break;
        case 7: c->r = 0; c->g = 0; c->b = 1; break;
        case 8: c->r = 1; c->g = .5; c->b = 1; break;
    }

    return c;

}


/* ***********
 * average color
 * ***********
 *     gives the average of two colors
 */
color* CubeIterator::averagecolor(color *c1, color *c2){
    color* cnew = new color;
    cnew->r = (c1->r + c2->r)*.5;
    cnew->g = (c1->g + c2->g)*.5;
    cnew->b = (c1->b + c2->b)*.5;

    return cnew;
}



point* CubeIterator::applytransform(point* p, affine* T){
    point* newp = new point;

    newp->x = p->x*T->mat[0][0] + p->y*T->mat[0][1] + p->z*T->mat[0][2] +T->vec[0];
    newp->y = p->x*T->mat[1][0] + p->y*T->mat[1][1] + p->z*T->mat[1][2] +T->vec[1];
    newp->z = p->x*T->mat[2][0] + p->y*T->mat[2][1] + p->z*T->mat[2][2] +T->vec[2];

    return newp;
}

/* ***********
 * symmetrytransform
 * ***********
 *      gives a symmetry transform.
 *      sym = octahedral symmetry element index
 *      cube = which subcube
 *      T = affine transform to fill in
 *
 */
affine* CubeIterator::symmetrytransform(int sym, int cube){

    double m1,m2,m3,m4,m5,m6,m7,m8,m9;
    double t1, t2, t3;

    switch (sym) {
    case 0: m1 = 1; m2 = 0; m3 = 0; m4 = 0; m5 = 1; m6 = 0; m7 = 0; m8 = 0; m9 = 1; break;
    case 1: m1 = 0; m2 = 1; m3 = 0; m4 = 1; m5 = 0; m6 = 0; m7 = 0; m8 = 0; m9 = 1; break;
    case 2: m1 = 1; m2 = 0; m3 = 0; m4 = 0; m5 = 0; m6 = 1; m7 = 0; m8 = 1; m9 = 0; break;
    case 3: m1 = 0; m2 = 1; m3 = 0; m4 = 0; m5 = 0; m6 = 1; m7 = 1; m8 = 0; m9 = 0; break;
    case 4: m1 = 0; m2 = 0; m3 = 1; m4 = 1; m5 = 0; m6 = 0; m7 = 0; m8 = 1; m9 = 0; break;
    case 5: m1 = 0; m2 = 0; m3 = 1; m4 = 0; m5 = 1; m6 = 0; m7 = 1; m8 = 0; m9 = 0; break;
    case 6: m1 = 0; m2 = -1; m3 = 0; m4 = -1; m5 = 0; m6 = 0; m7 = 0; m8 = 0; m9 = 1; break;
    case 7: m1 = -1; m2 = 0; m3 = 0; m4 = 0; m5 = -1; m6 = 0; m7 = 0; m8 = 0; m9 = 1; break;
    case 8: m1 = 0; m2 = 0; m3 = -1; m4 = -1; m5 = 0; m6 = 0; m7 = 0; m8 = 1; m9 = 0; break;
    case 9: m1 = 0; m2 = 0; m3 = -1; m4 = 0; m5 = -1; m6 = 0; m7 = 1; m8 = 0; m9 = 0; break;
    case 10: m1 = -1; m2 = 0; m3 = 0; m4 = 0; m5 = 0; m6 = -1; m7 = 0; m8 = 1; m9 = 0; break;
    case 11: m1 = 0; m2 = -1; m3 = 0; m4 = 0; m5 = 0; m6 = -1; m7 = 1; m8 = 0; m9 = 0; break;
    case 12: m1 = 0; m2 = -1; m3 = 0; m4 = 0; m5 = 0; m6 = 1; m7 = -1; m8 = 0; m9 = 0; break;
    case 13: m1 = -1; m2 = 0; m3 = 0; m4 = 0; m5 = 0; m6 = 1; m7 = 0; m8 = -1; m9 = 0; break;
    case 14: m1 = 0; m2 = 0; m3 = -1; m4 = 0; m5 = 1; m6 = 0; m7 = -1; m8 = 0; m9 = 0; break;
    case 15: m1 = 0; m2 = 0; m3 = -1; m4 = 1; m5 = 0; m6 = 0; m7 = 0; m8 = -1; m9 = 0; break;
    case 16: m1 = -1; m2 = 0; m3 = 0; m4 = 0; m5 = 1; m6 = 0; m7 = 0; m8 = 0; m9 = -1; break;
    case 17: m1 = 0; m2 = -1; m3 = 0; m4 = 1; m5 = 0; m6 = 0; m7 = 0; m8 = 0; m9 = -1; break;
    case 18: m1 = 0; m2 = 0; m3 = 1; m4 = 0; m5 = -1; m6 = 0; m7 = -1; m8 = 0; m9 = 0; break;
    case 19: m1 = 0; m2 = 0; m3 = 1; m4 = -1; m5 = 0; m6 = 0; m7 = 0; m8 = -1; m9 = 0; break;
    case 20: m1 = 0; m2 = 1; m3 = 0; m4 = 0; m5 = 0; m6 = -1; m7 = -1; m8 = 0; m9 = 0; break;
    case 21: m1 = 1; m2 = 0; m3 = 0; m4 = 0; m5 = 0; m6 = -1; m7 = 0; m8 = -1; m9 = 0; break;
    case 22: m1 = 0; m2 = 1; m3 = 0; m4 = -1; m5 = 0; m6 = 0; m7 = 0; m8 = 0; m9 = -1; break;
    case 23: m1 = 1; m2 = 0; m3 = 0; m4 = 0; m5 = -1; m6 = 0; m7 = 0; m8 = 0; m9 = -1; break;
    case 24: m1 = -1; m2 = 0; m3 = 0; m4 = 0; m5 = -1; m6 = 0; m7 = 0; m8 = 0; m9 = -1; break;
    case 25: m1 = 0; m2 = -1; m3 = 0; m4 = -1; m5 = 0; m6 = 0; m7 = 0; m8 = 0; m9 = -1; break;
    case 26: m1 = -1; m2 = 0; m3 = 0; m4 = 0; m5 = 0; m6 = -1; m7 = 0; m8 = -1; m9 = 0; break;
    case 27: m1 = 0; m2 = -1; m3 = 0; m4 = 0; m5 = 0; m6 = -1; m7 = -1; m8 = 0; m9 = 0; break;
    case 28: m1 = 0; m2 = 0; m3 = -1; m4 = -1; m5 = 0; m6 = 0; m7 = 0; m8 = -1; m9 = 0; break;
    case 29: m1 = 0; m2 = 0; m3 = -1; m4 = 0; m5 = -1; m6 = 0; m7 = -1; m8 = 0; m9 = 0; break;
    case 30: m1 = 0; m2 = 1; m3 = 0; m4 = 1; m5 = 0; m6 = 0; m7 = 0; m8 = 0; m9 = -1; break;
    case 31: m1 = 1; m2 = 0; m3 = 0; m4 = 0; m5 = 1; m6 = 0; m7 = 0; m8 = 0; m9 = -1; break;
    case 32: m1 = 0; m2 = 0; m3 = 1; m4 = 1; m5 = 0; m6 = 0; m7 = 0; m8 = -1; m9 = 0; break;
    case 33: m1 = 0; m2 = 0; m3 = 1; m4 = 0; m5 = 1; m6 = 0; m7 = -1; m8 = 0; m9 = 0; break;
    case 34: m1 = 1; m2 = 0; m3 = 0; m4 = 0; m5 = 0; m6 = 1; m7 = 0; m8 = -1; m9 = 0; break;
    case 35: m1 = 0; m2 = 1; m3 = 0; m4 = 0; m5 = 0; m6 = 1; m7 = -1; m8 = 0; m9 = 0; break;
    case 36: m1 = 0; m2 = 1; m3 = 0; m4 = 0; m5 = 0; m6 = -1; m7 = 1; m8 = 0; m9 = 0; break;
    case 37: m1 = 1; m2 = 0; m3 = 0; m4 = 0; m5 = 0; m6 = -1; m7 = 0; m8 = 1; m9 = 0; break;
    case 38: m1 = 0; m2 = 0; m3 = 1; m4 = 0; m5 = -1; m6 = 0; m7 = 1; m8 = 0; m9 = 0; break;
    case 39: m1 = 0; m2 = 0; m3 = 1; m4 = -1; m5 = 0; m6 = 0; m7 = 0; m8 = 1; m9 = 0; break;
    case 40: m1 = 1; m2 = 0; m3 = 0; m4 = 0; m5 = -1; m6 = 0; m7 = 0; m8 = 0; m9 = 1; break;
    case 41: m1 = 0; m2 = 1; m3 = 0; m4 = -1; m5 = 0; m6 = 0; m7 = 0; m8 = 0; m9 = 1; break;
    case 42: m1 = 0; m2 = 0; m3 = -1; m4 = 0; m5 = 1; m6 = 0; m7 = 1; m8 = 0; m9 = 0; break;
    case 43: m1 = 0; m2 = 0; m3 = -1; m4 = 1; m5 = 0; m6 = 0; m7 = 0; m8 = 1; m9 = 0; break;
    case 44: m1 = 0; m2 = -1; m3 = 0; m4 = 0; m5 = 0; m6 = 1; m7 = 1; m8 = 0; m9 = 0; break;
    case 45: m1 = -1; m2 = 0; m3 = 0; m4 = 0; m5 = 0; m6 = 1; m7 = 0; m8 = 1; m9 = 0; break;
    case 46: m1 = 0; m2 = -1; m3 = 0; m4 = 1; m5 = 0; m6 = 0; m7 = 0; m8 = 0; m9 = 1; break;
    case 47: m1 = -1; m2 = 0; m3 = 0; m4 = 0; m5 = 1; m6 = 0; m7 = 0; m8 = 0; m9 = 1; break;

    }


    switch (cube) {
    case 1: t1 = -1; t2 = -1, t3 = 1; break;
    case 2: t1 = 1; t2 = -1; t3 = 1; break;
    case 3: t1 = -1; t2 = -1; t3 = -1; break;
    case 4: t1 = 1; t2 = -1; t3 = -1; break;
    case 5: t1 = -1; t2 = 1; t3 = 1; break;
    case 6: t1 = 1; t2 = 1; t3 = 1; break;
    case 7: t1 = -1; t2 = 1; t3 = -1; break;
    case 8: t1 = 1; t2 = 1; t3 = -1; break;

    }

    affine* T = new affine;

    T->mat[0][0] = .5*m1;
    T->mat[0][1] = .5*m2;
    T->mat[0][2] = .5*m3;
    T->mat[1][0] = .5*m4;
    T->mat[1][1] = .5*m5;
    T->mat[1][2] = .5*m6;
    T->mat[2][0] = .5*m7;
    T->mat[2][1] = .5*m8;
    T->mat[2][2] = .5*m9;

    T->vec[0] = .5*t1;
    T->vec[1] = .5*t2;
    T->vec[2] = .5*t3;

    return T;

}


/*
void printtransform(affine* T){
    std::printf("%f %f %f \t %f \n %f %f %f \t %f \n %f %f %f\t %f \n\n",
          T->mat[0][0],T->mat[0][1],T->mat[0][2], T->vec[0],
          T->mat[1][0],T->mat[1][1],T->mat[1][2], T->vec[1],
          T->mat[2][0],T->mat[2][1],T->mat[2][2], T->vec[2]);
}
*/






