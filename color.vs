#version 400

in vec3 inputPosition;
in vec3 inputColor;

out vec3 color;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
    // Calculate the position of the vertex against the world, view, and projection matrices.
    gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(inputPosition, 1.0f);
    // Store the input color for the pixel shader to use.
    color = inputColor;
}

