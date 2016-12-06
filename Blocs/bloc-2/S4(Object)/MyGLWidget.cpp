#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
  scale = 1.0f;
  rotate = 0.0f;
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  
  glEnable (GL_DEPTH_TEST);
  m.load ("/home2/users/alumnes/1193805/dades/Tercer/Q1/IDI/models/HomerProves.obj");
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  createBuffers();
}

void MyGLWidget::paintGL () 
{
  // Esborrem el frame-buffer
//   glClear (GL_COLOR_BUFFER_BIT);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransformObject ();
  projectTransform();
  viewTransform ();
  // Activem el VAO per a pintar la l'objecte 
  glBindVertexArray (VAO_Obj);
  // pintem
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);

  //Activem i pintem el VAO del terra
  modelTransformTerra ();
  glBindVertexArray (VAO_Terra);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glBindVertexArray (0);
}

void MyGLWidget::modelTransformObject () 
{
  // Matriu de transformació de model
  glm::mat4 TG (1.0f);
  TG = glm::rotate(TG,rotate, glm::vec3(0,1,0));
  TG = TG * glm::scale(TG, glm::vec3(scale));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTerra () 
{
  // Matriu de transformació de model
  glm::mat4 TG (1.0f);
  TG = TG * glm::scale(TG, glm::vec3(scale));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}




void MyGLWidget::projectTransform () 
{
  // glm::perspective (FOV en radians, ra window, znear, zfar)
  glm::mat4 trans = glm::perspective ((float)M_PI/2.0f, 1.0f, 0.4f, 3.0f);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &trans[0][0]);

}

void MyGLWidget::viewTransform () {
  // glm::lookAt (OBS, VRP, UP)
  glm::mat4 View = glm::lookAt (glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0));
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::resizeGL (int w, int h) 
{
  glViewport(0, 0, w, h);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  switch (event->key()) {
    makeCurrent();
    case Qt::Key_S: { // escalar a més gran
      scale += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scale -= 0.05;
      break;
    }
    case Qt::Key_R: {//gir 45 graus eix Y
      rotate += (float)M_PI/4.0;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::createBuffers () 
{
  // Dades de la caseta
  // Dos VBOs, un amb posició i l'altre amb color
//   glm::vec3 posicio[5] = {
// 	glm::vec3(-0.5, -1.0, -0.5),
// 	glm::vec3( 0.5, -1.0, -0.5),
// 	glm::vec3(-0.5,  0.0, -0.5),
// 	glm::vec3( 0.5,  0.0, -0.5),
// 	glm::vec3( 0.0,  0.6, -0.5)
//   }; 
//   glm::vec3 color[5] = {
// 	glm::vec3(1,0,0),
// 	glm::vec3(0,1,0),
// 	glm::vec3(0,0,1),
// 	glm::vec3(1,0,0),
// 	glm::vec3(0,1,0)
//   };
// 
//   // Creació del Vertex Array Object per pintar
//   glGenVertexArrays(1, &VAO_Casa);
//   glBindVertexArray(VAO_Casa);
// 
//   glGenBuffers(1, &VBO_CasaPos);
//   glBindBuffer(GL_ARRAY_BUFFER, VBO_CasaPos);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(posicio), posicio, GL_STATIC_DRAW);
// 
//   // Activem l'atribut vertexLoc
//    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(vertexLoc);
// 
//   glGenBuffers(1, &VBO_CasaCol);
//   glBindBuffer(GL_ARRAY_BUFFER, VBO_CasaCol);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
// 
//   // Activem l'atribut colorLoc
//   glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
//   glEnableVertexAttribArray(colorLoc);

  
  
  //Inicialitzem VAO i VBO de l'objecte i el VBO  del color de l'objecte
  glGenVertexArrays(1, &VAO_Obj);
  glBindVertexArray(VAO_Obj);
  
  glGenBuffers(1, &VBO_Obj);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Obj);
  glBufferData (GL_ARRAY_BUFFER,sizeof(GLfloat) * m.faces ().size () * 3 * 3,m.VBO_vertices (), GL_STATIC_DRAW); // posició
  
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);
  
  
  glGenBuffers(1, &VBO_ObjColor);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_ObjColor);
  glBufferData (GL_ARRAY_BUFFER,sizeof(GLfloat) * m.faces ().size () * 3 * 3,m.VBO_matdiff (), GL_STATIC_DRAW); // color

  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
  
  //Inicialitzem VAO i VBOs del terra i del color del terra.
  glm::vec3 terra[4] = {
    glm::vec3(-1,-1,-1),
    glm::vec3(1,-1,-1),
    glm::vec3(-1,-1,1),
    glm::vec3(1,-1,1),
  };
  
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);
  
  glGenBuffers(1, &VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra);
  glBufferData(GL_ARRAY_BUFFER, sizeof(terra), terra, GL_STATIC_DRAW);
  
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);
  
  glBindVertexArray (0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/fragshad.frag");
  vs.compileSourceFile("shaders/vertshad.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc = glGetUniformLocation(program->programId(), "proj");
  viewLoc = glGetUniformLocation (program->programId(), "view");

}

