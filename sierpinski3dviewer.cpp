//
//  Sierpinski3dviewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QList>
#include <QSpinBox>
#include <QGridLayout>
#include "sierpinski3dviewer.h"
#include "sierpinski3dopengl.h"
#include <stdio.h>

//
//  Constructor
//
Sierpinski3dviewer::Sierpinski3dviewer()
{
   //  Set window title
   setWindowTitle(tr("The 3D Sierpinski Relatives"));

   //  Create new OpenGL widget
   Sierpinski3dopengl* ogl = new Sierpinski3dopengl;

    // Set tab options layout
   Tutorialoptions* Tutorialpage = new Tutorialoptions();
   IFSoptions* IFSpage = new IFSoptions();
   CUBEoptions* CUBEpage = new CUBEoptions();


     QTabWidget* OptionsLayout = new QTabWidget();
     OptionsLayout->addTab(Tutorialpage,tr("Tutorial"));
     OptionsLayout->addTab(IFSpage, tr("IFS View"));
     OptionsLayout->addTab(CUBEpage, tr("Cube Iteration View"));


     //  Set layout of child widgets
     QGridLayout* FullLayout = new QGridLayout;

     // Settings
     settings* generalsettings = new settings();

     // Parameters
     selectparameters* parameters = new selectparameters();

     //quit button
     QPushButton* quit = new QPushButton("QUIT");

     FullLayout->addWidget(ogl,0,0,2,1);
     FullLayout->addWidget(generalsettings,0,1);
     FullLayout->addWidget(OptionsLayout,1,1);
     FullLayout->addWidget(parameters,2,0);
     FullLayout->addWidget(quit,2,1);

     FullLayout->setColumnStretch(0,1);
     FullLayout->setRowStretch(1,1);
     FullLayout->setColumnMinimumWidth(0,100);
     FullLayout->setRowMinimumHeight(0,100);
     setLayout(FullLayout);

     connect(generalsettings,SIGNAL(changeProjection(int)),ogl, SLOT(setPerspective(int)));
     connect(generalsettings,SIGNAL(changeObject(int)),ogl, SLOT(setObject(int)));
     connect(generalsettings,SIGNAL(changeBoxframe(int)),ogl,SLOT(setBoxframe(int)));
     connect(generalsettings,SIGNAL(changeShader(int)),ogl,SLOT(setShader(int)));
     connect(generalsettings,SIGNAL(changeLighting(int)),ogl,SLOT(setLighting(int)));
     connect(generalsettings,SIGNAL(changeAutorotate(int)),ogl,SLOT(setAutorotate(int)));
     connect(generalsettings,SIGNAL(changeBackground(int)),ogl,SLOT(setBackground(int)));


     connect(parameters, SIGNAL(changeParam1(int)),ogl,SLOT(setParam1(int)));
     connect(parameters, SIGNAL(changeParam2(int)),ogl,SLOT(setParam2(int)));
     connect(parameters, SIGNAL(changeParam3(int)),ogl,SLOT(setParam3(int)));
     connect(parameters, SIGNAL(changeParam4(int)),ogl,SLOT(setParam4(int)));
     connect(parameters, SIGNAL(changeParam5(int)),ogl,SLOT(setParam5(int)));
     connect(parameters, SIGNAL(changeParam6(int)),ogl,SLOT(setParam6(int)));
     connect(parameters, SIGNAL(changeParam7(int)),ogl,SLOT(setParam7(int)));
     connect(parameters, SIGNAL(changeParam8(int)),ogl,SLOT(setParam8(int)));

     connect(ogl,SIGNAL(changedParam1(int)),parameters,SLOT(setParam1(int)));
     connect(ogl,SIGNAL(changedParam2(int)),parameters,SLOT(setParam2(int)));
     connect(ogl,SIGNAL(changedParam3(int)),parameters,SLOT(setParam3(int)));
     connect(ogl,SIGNAL(changedParam4(int)),parameters,SLOT(setParam4(int)));
     connect(ogl,SIGNAL(changedParam5(int)),parameters,SLOT(setParam5(int)));
     connect(ogl,SIGNAL(changedParam6(int)),parameters,SLOT(setParam6(int)));
     connect(ogl,SIGNAL(changedParam7(int)),parameters,SLOT(setParam7(int)));
     connect(ogl,SIGNAL(changedParam8(int)),parameters,SLOT(setParam8(int)));


     connect(OptionsLayout,SIGNAL(currentChanged(int)),ogl,SLOT(setDisplaymode(int)));

     connect(Tutorialpage, SIGNAL(changeExample(int)),ogl,SLOT(setExample(int)));
     connect(Tutorialpage, SIGNAL(changeIterate(int)),ogl,SLOT(setIterate(int)));


     connect(IFSpage, SIGNAL(changeNumpts(int)),ogl,SLOT(setIFSnumpts(int)));
     connect(IFSpage, SIGNAL(changeColormode(int)),ogl,SLOT(setIFScolormode(int)));
     connect(IFSpage, SIGNAL(changeRaster(int)),ogl,SLOT(setIFSraster(int)));


     connect(CUBEpage,SIGNAL(changeNumits(int)),ogl,SLOT(setCUBEnumits(int)));
     connect(CUBEpage,SIGNAL(changeColormode(int)),ogl,SLOT(setCUBEcolormode(int)));


     connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));



}



/*
 * *******************
 * Tutorial Class
 * *******************
 * contains the options for displaying a fractal using an Iterated Function System
 * Options:
 *      example = number of example
 *      Iterate = turn on or off iteration
 *
 *
 */

 Tutorialoptions::Tutorialoptions(){
     // Choose Color mode for display of points
      QComboBox* examplemode = new QComboBox();
      examplemode->addItem("EX01: 1 Cube");
      examplemode->addItem("EX02: Different Cube");
      examplemode->addItem("EX03: Different Symmetry");
      examplemode->addItem("EX04: 2 Cubes");
      examplemode->addItem("EX05: 2 Cubes, 2 Symmetries");
      examplemode->addItem("EX06: Sierpisnki Tetrahedron");
      examplemode->addItem("EX07: Holey Fractal");
      examplemode->addItem("EX08: 2D Gasket");

      //  Lighting
      QCheckBox* iterate = new QCheckBox("");


      // Set up list of options
      QGridLayout* tutorialoptions = new QGridLayout;
      tutorialoptions->addWidget( new QLabel("Tutorial"),0,0,1,2);
      tutorialoptions->addWidget( new QLabel("Example:"),1,0);
      tutorialoptions->addWidget(examplemode,1,1);
      tutorialoptions->addWidget( new QLabel("Iterate:"),2,0);
      tutorialoptions->addWidget(iterate,2,1);
      tutorialoptions->setRowStretch(3,1);
      setLayout(tutorialoptions);

      connect(examplemode,SIGNAL(currentIndexChanged(int)),this, SLOT(setExample(int)));
      connect(iterate,SIGNAL(stateChanged(int)),this, SLOT(setIterate(int)));



 }

void Tutorialoptions::setExample(int num){

    example = num;
    emit changeExample(example);

}

void Tutorialoptions::setIterate(int on){

    iterate = on;
    emit changeIterate(iterate);

}


/*
 * *******************
 * IFSoptions Class
 * *******************
 * contains the options for displaying a fractal using an Iterated Function System
 * Options:
 *      numpts = number of points in orbit
 *
 *
 */

IFSoptions::IFSoptions()
{

    // Choose number of points to display in IFS mode
     QSpinBox* IFSnpts = new QSpinBox();
     IFSnpts->setMinimum(1);
     IFSnpts->setMaximum(1000000);
     IFSnpts->setValue(100000);

     // Choose Color mode for display of points
      QComboBox* IFSColormode = new QComboBox();
      IFSColormode->addItem("Sub-Cube Coloring");
      IFSColormode->addItem("Trajectory Coloring");
      IFSColormode->addItem("XYZ Space Coloring");

      //  Raster
      QCheckBox* IFSrasterbox = new QCheckBox("");



     // Set up list of options
     QGridLayout* IFSoptions = new QGridLayout;
     IFSoptions->addWidget( new QLabel("IFS Options"),0,0,1,2);
     IFSoptions->addWidget( new QLabel("Number of points:"),1,0);
     IFSoptions->addWidget(IFSnpts,1,1);
     IFSoptions->addWidget( new QLabel("Coloring:"),2,0);
     IFSoptions->addWidget(IFSColormode,2,1);
     IFSoptions->addWidget( new QLabel("Raster:"),3,0);
     IFSoptions->addWidget(IFSrasterbox,3,1);
     IFSoptions->setRowStretch(4,1);
     setLayout(IFSoptions);
     connect(IFSnpts,SIGNAL(valueChanged(int)),this, SLOT(setNumpts(int)));
     connect(IFSColormode,SIGNAL(currentIndexChanged(int)),this,SLOT(setColormode(int)));
     connect(IFSrasterbox,SIGNAL(stateChanged(int)),this,SLOT(setRaster(int)));

}

//SLOT definitions
void IFSoptions::setNumpts(int num)
{
    numpts = num;
    emit changeNumpts(numpts);

}

void IFSoptions::setColormode(int mode)
{
    colormode = mode;
    emit changeColormode(colormode);

}

void IFSoptions::setRaster(int on)
{
    raster = on;
    emit changeRaster(raster);

}


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
CUBEoptions::CUBEoptions()
{

    // Choose number of iterations apply to the cubes
     QSpinBox* CUBEnits = new QSpinBox();
     CUBEnits->setMinimum(1);
     CUBEnits->setMaximum(8);
     CUBEnits->setValue(3);

     // Choose Color mode for display of points
      QComboBox* CUBEColormode = new QComboBox();
      CUBEColormode->addItem("Sub-Cube Coloring");
      CUBEColormode->addItem("Trajectory Coloring");
      CUBEColormode->addItem("XYZ Space Coloring");

     // Set up list of options
     QGridLayout* CUBEoptions = new QGridLayout;
     CUBEoptions->addWidget( new QLabel("Cube Iteration Options"),0,0,1,2);
     CUBEoptions->addWidget( new QLabel("Number of iterations:"),1,0);
     CUBEoptions->addWidget(CUBEnits,1,1);
     CUBEoptions->addWidget( new QLabel("Color Mode:"),2,0);
     CUBEoptions->addWidget(CUBEColormode,2,1);
     CUBEoptions->setRowStretch(3,1);
     setLayout(CUBEoptions);
     connect(CUBEnits,SIGNAL(valueChanged(int)),this,SLOT(setNumits(int)));
     connect(CUBEColormode,SIGNAL(currentIndexChanged(int)),this,SLOT(setColormode(int)));

}



void CUBEoptions::setNumits(int num)
{
    numits = num;
    emit changeNumits(numits);

}

void CUBEoptions::setColormode(int mode)
{
    colormode = mode;
    emit changeColormode(colormode);

}


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
settings::settings()
{

    //  Select shader
    QComboBox* shader = new QComboBox();
    shader->addItem("None");
    shader->addItem("Wood");
    shader->addItem("Random");
    shader->addItem("Perlin Noise");

    //Background colors
    QComboBox* bg = new QComboBox();
    bg->addItem("Gray");
    bg->addItem("Black");
    bg->addItem("White");
    bg->addItem("Red");
    bg->addItem("Green");
    bg->addItem("Blue");



    //  Select projection
    QComboBox* projection = new QComboBox();
    projection->addItem("Orthogonal");
    projection->addItem("Perspective");

    /*
    //  Select object
    QComboBox* object = new QComboBox();
    object->addItem("Attractor");
    object->addItem("Cube Iterator");
    */
    //  Lighting
    QCheckBox* lighting = new QCheckBox("");


    //  Boxframe
    QCheckBox* boxframe = new QCheckBox("");
    boxframe->click();

    //  Autorotate
    QCheckBox* autorotate = new QCheckBox("");



    //  Set layout of child widgets
    QGridLayout* layout = new QGridLayout;

    layout->addWidget(new QLabel("General Settings"),0,0,1,2);
    layout->addWidget(new QLabel("Shader"),1,0);
    layout->addWidget(shader,1,1);
    layout->addWidget(new QLabel("Background"),2,0);
    layout->addWidget(bg,2,1);
    layout->addWidget(new QLabel("Projection"),3,0);
    layout->addWidget(projection,3,1);
    layout->addWidget(new QLabel("Lighting"),4,0);
    layout->addWidget(lighting,4,1);
    layout->addWidget(new QLabel("Frame"),5,0);
    layout->addWidget(boxframe ,5,1);
    layout->addWidget(new QLabel("AutoRotate"),6,0);
    layout->addWidget(autorotate ,6,1);
    layout->setRowStretch(7,1);
    setLayout(layout);

    connect(projection,SIGNAL(currentIndexChanged(int)) , this ,SLOT(setProjection(int)));
    //connect(object,SIGNAL(currentIndexChanged(int)) , this ,SLOT(setObject(int)));
    connect(boxframe,SIGNAL(stateChanged(int)),this,SLOT(setBoxframe(int)));
    connect(shader,SIGNAL(currentIndexChanged(int)) , this ,SLOT(setShader(int)));
    connect(lighting,SIGNAL(stateChanged(int)),this,SLOT(setLighting(int)));
    connect(autorotate,SIGNAL(stateChanged(int)),this,SLOT(setAutorotate(int)));
    connect(bg,SIGNAL(currentIndexChanged(int)),this,SLOT(setBackground(int)));


}


//Slots definitions
void settings::setProjection(int proj)
{
    projection = proj;
    emit changeProjection( projection );

}

void settings::setObject(int obj)
{
    object = obj;
    emit changeObject(obj);

}

void settings::setBoxframe(int on)
{
    boxframe = on;
    emit changeBoxframe(boxframe);

}

void settings::setShader(int shdr)
{
    shader = shdr;
    emit changeShader(shader);

}

void settings::setLighting(int lite)
{
    lighting = lite;
    emit changeLighting(lighting);

}

void settings::setAutorotate(int on)
{
    rotate = on;
    emit changeAutorotate(rotate);

}

void settings::setBackground(int col)
{
    background = col;
    emit changeBackground(background);

}



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
selectparameters::selectparameters()
{
    //   Select Each sub-cubes' symmetry
    parambox[0] = new QSpinBox;
    parambox[1] = new QSpinBox;
    parambox[2] = new QSpinBox;
    parambox[3] = new QSpinBox;
    parambox[4] = new QSpinBox;
    parambox[5] = new QSpinBox;
    parambox[6] = new QSpinBox;
    parambox[7] = new QSpinBox;


    QHBoxLayout* paramrow = new QHBoxLayout();
    paramrow->addWidget(new QLabel("Parameters: "));
    for(int i = 0; i < 8; i++){
        parambox[i]->setMinimum(-1);
        parambox[i]->setMaximum(47);
        paramrow->addWidget(parambox[i]);
    }
    parambox[0]->setValue(0);
    parambox[1]->setValue(-1);
    parambox[2]->setValue(-1);
    parambox[3]->setValue(-1);
    parambox[4]->setValue(-1);
    parambox[5]->setValue(-1);
    parambox[6]->setValue(-1);
    parambox[7]->setValue(-1);


    // Select a random Symmetry
    QPushButton* randbutton[6] = { new QPushButton("2"),new QPushButton("3"),new QPushButton("4"),new QPushButton("5"),new QPushButton("6"),new QPushButton("7")};


    QHBoxLayout* randrow = new QHBoxLayout();
    randrow->addWidget(new QLabel("Random: "));
    randrow->addWidget(randbutton[0]);
    randrow->addWidget(randbutton[1]);
    randrow->addWidget(randbutton[2]);
    randrow->addWidget(randbutton[3]);
    randrow->addWidget(randbutton[4]);
    randrow->addWidget(randbutton[5]);

    QVBoxLayout* stackrows = new QVBoxLayout();
    stackrows->addLayout(paramrow);
    stackrows->addLayout(randrow);

     setLayout(stackrows);

    connect(parambox[0],SIGNAL(valueChanged(int)),this,SLOT(setParam1(int)));
    connect(parambox[1],SIGNAL(valueChanged(int)),this,SLOT(setParam2(int)));
    connect(parambox[2],SIGNAL(valueChanged(int)),this,SLOT(setParam3(int)));
    connect(parambox[3],SIGNAL(valueChanged(int)),this,SLOT(setParam4(int)));
    connect(parambox[4],SIGNAL(valueChanged(int)),this,SLOT(setParam5(int)));
    connect(parambox[5],SIGNAL(valueChanged(int)),this,SLOT(setParam6(int)));
    connect(parambox[6],SIGNAL(valueChanged(int)),this,SLOT(setParam7(int)));
    connect(parambox[7],SIGNAL(valueChanged(int)),this,SLOT(setParam8(int)));

    connect(randbutton[5],SIGNAL(pressed()),this,SLOT(setRand7()));
    connect(randbutton[4],SIGNAL(pressed()),this,SLOT(setRand6()));
    connect(randbutton[3],SIGNAL(pressed()),this,SLOT(setRand5()));
    connect(randbutton[2],SIGNAL(pressed()),this,SLOT(setRand4()));
    connect(randbutton[1],SIGNAL(pressed()),this,SLOT(setRand3()));
    connect(randbutton[0],SIGNAL(pressed()),this,SLOT(setRand2()));


}

void selectparameters::setParam1(int sym)
{
    if (params[0] != sym){
        params[0] = sym;
        parambox[0]->setValue(sym);
        emit changeParam1( sym );
    }

}

void selectparameters::setParam2(int sym)
{
    if (params[1] != sym){
        params[1] = sym;
        parambox[1]->setValue(sym);
        emit changeParam2( sym );
    }

}

void selectparameters::setParam3(int sym)
{
    if (params[2] != sym){
        params[2] = sym;
        parambox[2]->setValue(sym);
        emit changeParam3( sym );
    }

}

void selectparameters::setParam4(int sym)
{
    if (params[3] != sym){
        params[3] = sym;
        parambox[3]->setValue(sym);
        emit changeParam4( sym );
    }

}

void selectparameters::setParam5(int sym)
{
    if (params[4] != sym){
        params[4] = sym;
        parambox[4]->setValue(sym);
        emit changeParam5( sym );
    }

}

void selectparameters::setParam6(int sym)
{
    if (params[5] != sym){
        params[5] = sym;
        parambox[5]->setValue(sym);
        emit changeParam6( sym );
    }

}

void selectparameters::setParam7(int sym)
{
    if (params[6] != sym){
        params[6] = sym;
        parambox[6]->setValue(sym);
        emit changeParam7( sym );
    }

}

void selectparameters::setParam8(int sym)
{
    if (params[7] != sym){
        params[7] = sym;
        parambox[7]->setValue(sym);
        emit changeParam8( sym );
    }

}

void selectparameters::setRand7(){
    randomparameters(7);
}

void selectparameters::setRand6(){
    randomparameters(6);
}

void selectparameters::setRand5(){
    randomparameters(5);
}

void selectparameters::setRand4(){
    randomparameters(4);
}

void selectparameters::setRand3(){
    randomparameters(3);
}

void selectparameters::setRand2(){
    randomparameters(2);
}



void selectparameters::randomparameters(int i){
    int randparams[8] = {-1, -1, -1, -1, -1, -1, -1, -1 };
    int choices[i+1];
    choices[i+1] = rand() % 8;
    for(int j = 1; j < i+1; j++)
    {
        choices[i] = -1;
    }
    int pick, isunique;
    int count = 1;
    while(choices[i] == -1){
        isunique = 1;
        pick = rand() % 8;
        for(int i = 0; i < count; i++){
            if(choices[i] == pick)
                isunique = 0;
        }
        if(isunique == 1){
            choices[count] = pick;
            count = count + 1;
            randparams[pick] = rand() % 48;
        }
    }
    for(int i = 0; i < 8; i++){
        params[i] = randparams[i];
        parambox[i]->setValue(randparams[i]);
    }
    changeParam1(randparams[0]);
    changeParam2(randparams[1]);
    changeParam3(randparams[2]);
    changeParam4(randparams[3]);
    changeParam5(randparams[4]);
    changeParam6(randparams[5]);
    changeParam7(randparams[6]);
    changeParam8(randparams[7]);
}
