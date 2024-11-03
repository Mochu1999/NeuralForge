#shader vertex 
#version 330 core

layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 pos2D;


uniform mat4 u_OrthoProjection;




void main() {

    gl_Position = u_OrthoProjection * vec4(pos2D, 0.0, 1.0);

    
}




#shader fragment
#version 330 core


out vec4 FragColor;




uniform vec4 u_Color;

void main()
{

    FragColor = u_Color;

}



