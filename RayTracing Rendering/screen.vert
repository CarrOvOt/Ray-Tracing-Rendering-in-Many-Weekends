#version 330 core

layout (location = 0) in vec3 aPos;

out vec2 TexCoord;


void main(){

    gl_Position = vec4(aPos, 1.0f);

    TexCoord=aPos.xy;
    TexCoord=(TexCoord+1.0f)/2;
}
