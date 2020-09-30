HEADERS = sierpinski3dviewer.h sierpinski3dopengl.h Type.h Object.h \
    attractor.h \
    cubeiterator.h \
    structs.h \
    tutorialobject.h
SOURCES = sierpinski3d.cpp sierpinski3dviewer.cpp sierpinski3dopengl.cpp Object.cpp \
    attractor.cpp \
    cubeiterator.cpp \
    tutorialobject.cpp
QT += opengl
RESOURCES = sierpinski3d.qrc
win32:{LIBS += -lopengl32}
