#version 330 core

in vec4 out_color;
out vec4 FragColor;

void main() {
 
    FragColor = out_color;
    
//     if (int(gl_FragCoord.y / 10) % 2 == 0)
//       discard;
//     
//     if (int(gl_FragCoord.x / 10) % 2 == 1)
//       discard;  
//       
//     if (gl_FragCoord.x < 358. && gl_FragCoord.y > 347.)
//       FragColor = vec4(1.,.0,.0,.0);
//     if (gl_FragCoord.x > 358. && gl_FragCoord.y < 347.)
//       FragColor = vec4(0.,1.,0.,0.);
//     if (gl_FragCoord.x > 358. && gl_FragCoord.y > 347.)
//       FragColor = vec4(0.,0.,1.,0.);   
//     if (gl_FragCoord.x < 358. && gl_FragCoord.y < 347.)
//       FragColor = vec4(1.,1.,0.,0.);   
    
 
}

