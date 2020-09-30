#ifndef SIERPINSKI3DV_H
#define SIERPINSKI3DV_H

#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QSpinBox>

class Sierpinski3dviewer : public QWidget
{
Q_OBJECT
public:
    Sierpinski3dviewer();
};


/*
 * *******************
 * Tutorial Class
 * *******************
 * contains the options for displaying a fractal using an Iterated Function System
 * Options:
 *      example = number of example
 *
 *
 */

class Tutorialoptions : public QWidget
{
Q_OBJECT
public:
    Tutorialoptions();
private:
    int example;
    int iterate;
public slots:
    void setExample(int num);
    void setIterate(int on);
signals:
    void changeExample(int num);
    void changeIterate(int on);
};


/*
 * *******************
 * IFSoptions Class
 * *******************
 * contains the options for displaying a fractal using an Iterated Function System
 * Options:
 *      numpts = number of points in orbit
 *      colormode = how to color the points
 *
 *
 */

class IFSoptions : public QWidget
{
Q_OBJECT
public:
    IFSoptions();
private:
    int numpts;
    int colormode;
    int raster;
public slots:
    void setNumpts(int num);
    void setColormode(int mode);
    void setRaster(int on);
signals:
    void changeNumpts(int num);
    void changeColormode(int mode);
    void changeRaster(int on);
};


/*
 * *******************
 * CUBEoptions Class
 * *******************
 * contains the options for displaying a fractal using iterated cubes
 * Options:
 *      numits = number of iterations
 *
 *
 */
class CUBEoptions : public QWidget
{
Q_OBJECT
public:
    CUBEoptions();
private:
    int numits;
    int colormode;
public slots:
    void setNumits(int num);
    void setColormode(int mode);
signals:
    void changeNumits(int num);
    void changeColormode(int mode);
};

/*
 * *******************
 * settings Class
 * *******************
 * contains the general settings for viewing
 * settings:
 *      pojection = perspective or orthogonal
 *
 *
 */

class settings : public QWidget
{
Q_OBJECT
public:
    settings();
private:
    int projection;
    int object;
    int boxframe;
    int shader;
    int lighting;
    int rotate;
    int background;
public slots:
    void setProjection(int proj);
    void setObject(int obj);
    void setBoxframe(int on);
    void setShader(int shdr);
    void setLighting(int lite);
    void setAutorotate(int on);
    void setBackground(int col);
signals:
    void changeProjection(int proj);
    void changeObject(int obj);
    void changeBoxframe(int on);
    void changeShader(int shdr);
    void changeLighting(int lite);
    void changeAutorotate(int on);
    void changeBackground(int col);
};

/*
 * *******************
 * SelectParameters Class
 * *******************
 * contains the general settings for viewing
 * settings:
 *      parameters = -1 thru 47 for which symmetry per cube
 *
 *
 */

class selectparameters : public QWidget
{
Q_OBJECT
public:
    selectparameters();
private:
    int params[8];
    QSpinBox* parambox[8];
    void randomparameters(int i);
public slots:
    void setParam1(int sym);
    void setParam2(int sym);
    void setParam3(int sym);
    void setParam4(int sym);
    void setParam5(int sym);
    void setParam6(int sym);
    void setParam7(int sym);
    void setParam8(int sym);



    void setRand2();
    void setRand3();
    void setRand4();
    void setRand5();
    void setRand6();
    void setRand7();

signals:

    void changeParam1(int sym);
    void changeParam2(int sym);
    void changeParam3(int sym);
    void changeParam4(int sym);
    void changeParam5(int sym);
    void changeParam6(int sym);
    void changeParam7(int sym);
    void changeParam8(int sym);

   };


#endif
