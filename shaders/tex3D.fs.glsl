#version 330 core

in vec3 vFragPosition;
in vec3 vFragNormal;
in vec2 vFragTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main(){
        fFragColor = texture(uTexture,vFragTexCoords).xyz;
}
