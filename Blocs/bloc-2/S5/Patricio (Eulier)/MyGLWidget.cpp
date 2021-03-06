#include "MyGLWidget.h"

#include <iostream>
using namespace std;

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
  m.load ("/home2/users/alumnes/1193805/dades/Q1/IDI/models/Patricio.obj");
  scale = 1.0f;
  rotate = 0.0f;
  alpha_ini = (float)M_PI/4.0f;
  FOV = (float)M_PI/2.0f;
  rav = float (width ()) / float (height ());
  psi = (float)M_PI/2.0f;
  theta = (float)M_PI/2.0f;
  rho = (float)M_PI/2.0f;
  computeContainerBox();
  computeCenterAndRadi();
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
  
  glBindVertexArray (0);
}

void MyGLWidget::resizeGL (int w, int h) 
{
  rav = float(w)/float(h);
  raw = rav;
  if (rav < 1){ 
    float alpha = float(atan(tan(alpha_ini)/rav));
    FOV = 2.0 * alpha;
  }
  glViewport(0, 0, w, h);
}

void MyGLWidget::createBuffers () 
{
  
  //Inicialitzem VAO i VBO de l'objecte i el VBO  del color de l'objecte
  glGenVertexArrays(1, &VAO_Obj);
  glBindVertexArray(VAO_Obj);
  
  glGenBuffers(1, &VBO_Obj);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Obj);
  glBufferData (GL_ARRAY_BUFFER,sizeof(GLfloat) * m.faces().size () * 3 * 3,m.VBO_vertices (), GL_STATIC_DRAW); // posició
  
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
    glm::vec3(1,-1,1)
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

void MyGLWidget::modelTransformObject () 
{
  // Matriu de transformació de model
  glm::mat4 TG (1.0f);
  TG = TG * glm::translate(TG,-centre);
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
  float znear = (float)dist-radi;
  float zfar = (float)dist+radi;
  //FOV = 2.0f*asin(radi/dist);
  glm::mat4 trans = glm::perspective (FOV, raw, znear, zfar);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &trans[0][0]);

}

void MyGLWidget::viewTransform () 
{
  // glm::lookAt (OBS, VRP, UP)
  
  dist = 2.0f*radi;

  glm::vec3 UP = glm::vec3(0,1,0);
  glm::vec3 v = glm::vec3(0,0,dist);
  glm::vec3 OBS = v;
  glm::vec3 VRP = glm::vec3(0,0,0);
  glm::mat4 VM = glm::lookAt(OBS,VRP,UP);

//  glm::mat4 VM;
 /* VM = glm::translate(VM,glm::vec3(0.0f,0.0f,-dist));
  VM = VM * glm::rotate(VM,-rho,glm::vec3(0.0f,0.0f,1.0f));
  VM = VM * glm::rotate(VM,theta,glm::vec3(1.0f,0.0f,0.0f));
  VM = VM * glm::rotate(VM,-psi,glm::vec3(0.0f,1.0f,0.0f));
 */ glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &VM[0][0]);
}

float distances(glm::vec3 p_min, glm::vec3 p_max)
{
  float x = (float) p_min[0] - p_max[0];
  float y = (float) p_min[1] - p_max[1];
  float z = (float) p_min[2] - p_max[2];
  return sqrt(x*x+y*y+z*z)/2.0f;
}

void MyGLWidget::computeCenterAndRadi ()
{
    centre = (p_min + p_max);
    centre /= 2.0f;
    radi = distances(p_min,p_max);
}

void MyGLWidget::computeContainerBox(){
    glm::vec3 gt(m.vertices()[0],m.vertices()[1],m.vertices()[2]);
    p_min = p_max = gt;
    for (unsigned int i = 3; i < m.vertices().size(); i +=3){
      gt = glm::vec3(m.vertices()[i],m.vertices()[i+1],m.vertices()[i+2]);
      p_min = glm::min(p_min,gt);
      p_max = glm::max(p_max,gt);
    }
}





