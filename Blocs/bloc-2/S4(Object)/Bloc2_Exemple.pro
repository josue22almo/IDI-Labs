TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH +=  /home2/users/alumnes/1193805/dades/Q1/IDI/Model/

FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \
        MyGLWidget.cpp 
        
SOURCES += /home2/users/alumnes/1193805/dades/Q1/IDI/Model/model.cpp
