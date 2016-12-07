#include "MyGLWidget.h"

#include <iostream>
using namespace std;

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
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
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  createBuffers();
  //inicialitzar les variable old_x, old_y

  old_x = 400;
  old_y = 400;
  scl_x = 0.5;
  glUniform1f (scl_xLoc, scl_x);
  scl_y = 0.5;
  glUniform1f (scl_yLoc, scl_y);

  keyPress = 1;
  glUniform1f (keyLoc, keyPress);
  
  mousePress = 0;
  glUniform1f (mouseLoc, mousePress);
}

void MyGLWidget::paintGL ()
{
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // Activem l'Array a pintar 
  glBindVertexArray(VAO);
 
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);
  
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  glViewport (0, 0, w, h);
}

void MyGLWidget::createBuffers ()
{
  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices[1] = glm::vec3(1.0, -1.0, 0.0);
  Vertices[2] = glm::vec3(0.0, 1.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  // Creació del buffer amb les dades dels vèrtexs
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);
  
//   TG = glm::mat4(1.0);
//   modelTransform ();
//   glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  
  
  scl = 0.5;
  glUniform1f (varLoc, scl);
  
  


  // Desactivem el VAO
  glBindVertexArray(0);
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
  varLoc = glGetUniformLocation (program->programId(), "scl");
  scl_xLoc = glGetUniformLocation (program->programId(), "scl_x");
  scl_yLoc = glGetUniformLocation (program->programId(), "scl_y");
  keyLoc = glGetUniformLocation (program->programId(), "keyPress");
  mouseLoc = glGetUniformLocation (program->programId(), "mousePress");
}

void MyGLWidget::modelTransform (){
  TG = glm::translate (TG, glm::vec3 (-0.5, 0.5, 0.0));
  TG = glm::scale(TG, glm::vec3 (0.5,0.5,0.0)) ;
}


void MyGLWidget::keyPressEvent (QKeyEvent *e) {
  makeCurrent ();
  switch ( e->key() ) {
    case Qt::Key_S :
      scl += 0.1;
      glUniform1f (varLoc, scl);
      break;
    case Qt::Key_D :
      scl -= 0.1;
      glUniform1f (varLoc, scl);
      break;
    default: e->ignore (); // propagar al pare
  }
  keyPress = 1;
  glUniform1f (keyLoc, keyPress);
  mousePress = 0;
  glUniform1f (mouseLoc, mousePress);
  cout << "key press " << keyPress << " " << mousePress << endl;
  update ();
}

void MyGLWidget::mouseMoveEvent( QMouseEvent * e ){
  makeCurrent();
  int x = e->pos().rx();
  int y = e->pos().ry();
  
  if (x > old_x){
    scl_x += 0.1;
    glUniform1f (scl_xLoc, scl_x);
    old_x = x;
  }
  if (y > old_y){
    scl_y += 0.1;
    glUniform1f (scl_yLoc, scl_y);
    old_y = y;
  }
  if (x < old_x){
    scl_x -= 0.1;
    glUniform1f (scl_xLoc, scl_x);
    old_x = x;
  }
  if (y < old_y){
    scl_y -= 0.1;
    glUniform1f (scl_yLoc, scl_y);
    old_y = y;
  }
  keyPress = 0;
  glUniform1f (keyLoc, keyPress);
  mousePress = 1;
  glUniform1f (mouseLoc, mousePress);
  cout << "mouse press " << keyPress << " " << mousePress << endl;
  update();
}


