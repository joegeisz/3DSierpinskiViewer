#include "tutorialobject.h"
#include <stdlib.h>

/************
 * Attractor constructor.
 *       Default Sierpinski Tetrahedron with 1000 points.
 ************
 */
TutorialObject::TutorialObject()
{

    colormode = 0;
    changeParameters(-1,0,0,-1,0,-1,-1,0);
    fillTransformQueue();
    generatePoints();
    pointcloud = new QQueue<point*>;
    iterate = 0;

};



/* ***********
 * Attractor constructor.
 * ***********
 *      num = number of points in orbit
 *      p1-p8 = parameters
 *
 */
TutorialObject::TutorialObject( int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{

    colormode = 0;
    changeParameters(p1,p2,p3,p4,p5,p6,p7,p8);
    fillTransformQueue();
    generatePoints();
    pointcloud = new QQueue<point*>;
    iterate = 0;

}



/* ***********
 * Generate the orbit of points
 * ***********
 *      fills in pointcloud
 *
 */
void TutorialObject::generatePoints()
{

    pointcloud0.clear();
    pointcloud1.clear();
    pointcloud2.clear();
    pointcloud3.clear();

    point* ic = new point;
    ic->x = 0.0;
    ic->y = 0.0;
    ic->z = 0.0;

    point* next;
    for(int i = 0; i < numcubes; i++){
        next = applytransform(ic, transforms.at(i));
        next->cube = *cubecolor(usedcubes.at(i));
        next->past = *cubecolor(usedcubes.at(i));
        pointcloud0.enqueue(next);
    }

        for(int j = 0; j < numcubes; j++){
            for(int i = 0; i < numcubes; i++){
                next = applytransform(pointcloud0.at(j), transforms.at(i));
                //next->cube = *cubecolor(usedcubes.at(i));
                next->cube = pointcloud0.at(j)->cube;
                next->past = *averagecolor(&pointcloud0.at(0)->past,&next->cube);
                pointcloud1.enqueue(next);
            }
        }


        for(int j = 0; j < pow(numcubes,2); j++){
            for(int i = 0; i < numcubes; i++){
                next = applytransform(pointcloud1.at(j), transforms.at(i));
                //next->cube = *cubecolor(usedcubes.at(i));
                next->cube = pointcloud1.at(j)->cube;
                next->past = *averagecolor(&pointcloud1.at(0)->past,&next->cube);
                pointcloud2.enqueue(next);
            }
        }

        for(int j = 0; j < pow(numcubes,3); j++){
            for(int i = 0; i < numcubes; i++){
                next = applytransform(pointcloud2.at(j), transforms.at(i));
                //next->cube = *cubecolor(usedcubes.at(i));
                next->cube = pointcloud2.at(j)->cube;
                next->past = *averagecolor(&pointcloud2.at(0)->past,&next->cube);
                pointcloud3.enqueue(next);
            }
        }

}



/* ***********
 * OpenGL display
 * ***********
 */
void TutorialObject::display()
{
    if (!show) return;
    //  Save transformation
    glPushMatrix();
    //  Texture on
    EnableTex();
    //  Front

    int sec = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    int numits = 0;
    float alpha = 1;

    if(iterate != 0){
         numits = floor(sec % 4);
    }

    if (numits == 0){
        pointcloud = &pointcloud0;
        display3DL();
        alpha = 0.5;
        glEnable(GL_BLEND);
        glDepthMask( GL_FALSE );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }

    if (numits == 1){
        pointcloud = &pointcloud1;
        alpha = 1;
    }

    if (numits == 2){
        pointcloud = &pointcloud2;
        alpha = 1;
    }

    if (numits == 3){
        pointcloud = &pointcloud3;
        alpha = 1;
    }

    double e = pow(.5,numits+1);


    if(colormode == 0){
        for(int i = 0; i < pointcloud->count(); i++)
        {
            useColor(Color(pointcloud->at(i)->cube.r,pointcloud->at(i)->cube.g,pointcloud->at(i)->cube.b, alpha));
            displayCube(*pointcloud->at(i), e);
        }
    }

    if(numits == 0){
        glDepthMask( GL_TRUE );
        glDisable( GL_BLEND );
    }

    if(colormode == 1){
        for(int i = 0; i < pointcloud->count(); i++)
        {
            useColor(Color(pointcloud->at(i)->past.r,pointcloud->at(i)->past.g,pointcloud->at(i)->past.b));
            displayCube(*pointcloud->at(i), e);

        }
    }

    if(colormode == 2){
        for(int i = 0; i < pointcloud->count(); i++)
        {
            useColor(Color(pointcloud->at(i)->x,pointcloud->at(i)->y,pointcloud->at(i)->z));
            displayCube(*pointcloud->at(i), e);

        }
    }


    //  Texture off
    DisableTex();
    //  Undo transofrmations
    glPopMatrix();

}


/* ***********
 * fill Transform Queue
 * ***********
 *      Fills in transforms, the IFS affine contratction maps which describe the attractor
 *      Also calculates numcubes
 */
void TutorialObject::fillTransformQueue()
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
void TutorialObject::changeParameters(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
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
 * display the Cube
 * ***********
 *     display a cube with center c and sidelength e
 */
void TutorialObject::displayCube(point c, float e)
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
 * display the 3d L shape
 * ***********
 *     display a 3d L in the box representing the symmetry of the cube
 */
void TutorialObject::display3DL()
{
    point center = {0,0,0,{0,0,0},{0,0,0}};

    point x1 = {0.25, 0, 0, {0,0,0},{0,0,0}};

    point y1 = {0, 0.25, 0,{0,0,0},{0,0,0}};
    point y2 = {0, 0.5, 0,{0,0,0},{0,0,0}};

    point z1 = {0, 0, 0.25,{0,0,0},{0,0,0}};
    point z2 = {0, 0, 0.5,{0,0,0},{0,0,0}};
    point z3 = {0, 0, 0.75,{0,0,0},{0,0,0}};

    float sidelength = 0.0625;
    for(int i = 0; i < numcubes; i++){
        useColor(Color(0,0,0));
        displayCube( *applytransform( &center, transforms.at(i)), sidelength);
        useColor(Color(1,0,0));
        displayCube( *applytransform( &x1, transforms.at(i)),  sidelength);
        useColor(Color(0,1,0));
        displayCube( *applytransform( &y1, transforms.at(i)),  sidelength);
        displayCube( *applytransform( &y2, transforms.at(i)),  sidelength);
        useColor(Color(0,0,1));
        displayCube( *applytransform( &z1, transforms.at(i)),  sidelength);
        displayCube( *applytransform( &z2, transforms.at(i)),  sidelength);
        displayCube( *applytransform( &z3, transforms.at(i)),  sidelength);
    }


}



/* ***********
 * Set Colormode
 * ***********
 *     Sets the colormode
 */
void TutorialObject::setColormode(int mode)
{
    colormode = mode;

}

/* ***********
 * Set Iterate
 * ***********
 *     Turn on/off iteration
 */
void TutorialObject::setIterate(int on)
{
    iterate = on;

}

/* ***********
 * Color Cube
 * ***********
 *     gives the color associated with each cube
 */
color* TutorialObject::cubecolor(int cube)
{
    color* c = new color;

    switch (cube) {

        case 1: c->r = 0; c->g = 1; c->b = 0; break;
        case 2: c->r = 0; c->g = 0; c->b = 0; break;
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
color* TutorialObject::averagecolor(color *c1, color *c2){
    color* cnew = new color;
    cnew->r = (c1->r + c2->r)*.5;
    cnew->g = (c1->g + c2->g)*.5;
    cnew->b = (c1->b + c2->b)*.5;

    return cnew;
}



point* TutorialObject::applytransform(point* p, affine* T){
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
affine* TutorialObject::symmetrytransform(int sym, int cube){

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





