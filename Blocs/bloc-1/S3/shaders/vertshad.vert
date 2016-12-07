#version 330 core

in vec3 vertex;
uniform float scl,scl_x, scl_y;
uniform float keyPress,mousePress;

void main()  {
    if (keyPress > 0.5)
      gl_Position = vec4 (vertex*scl, 1.0);
    else if (mousePress > 0.5)
      gl_Position = vec4 (vertex*vec3(scl_x, scl_y, 1.0), 1.0);
}
