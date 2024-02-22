//
// Created by l4zy9uy on 2/17/24.
//

#include "ModelClass.h"

ModelClass::ModelClass()
= default;


ModelClass::ModelClass(const ModelClass& other)
{
}

ModelClass::~ModelClass()
= default;

bool ModelClass::Initialize(std::shared_ptr<OpenGLClass> & OpenGL)
{
    // Store a pointer to the OpenGL object.
    m_OpenGLPtr = OpenGL;
    // Initialize the vertex and index buffer that hold the geometry for the triangle.
    return InitializeBuffers() ? true : false;
}

void ModelClass::Shutdown()
{
    // Release the vertex and index buffers.
    ShutdownBuffers();
}

void ModelClass::Render()
{
    // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
    RenderBuffers();
}

bool ModelClass::InitializeBuffers() {
    // Set the number of vertices in the vertex array.
    m_vertexCount = 3;
    // Set the number of indices in the index array.
    m_indexCount = 3;
    auto indices = std::make_unique<unsigned int[]>(m_indexCount);
    auto vertices = std::make_unique<VertexType[]>(m_vertexCount);
    // Load the vertex array with data.
    vertices[0].position = glm::vec3(-1.0f, -1.0f, 0.0f);
    vertices[0].color = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices[1].position = glm::vec3(1.0f, 1.0f, 0.0f);
    vertices[1].color = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices[2].position = glm::vec3(2.0f, -2.0f, 0.0f);
    vertices[2].color = glm::vec3(1.0f, 1.0f, 0.0f);
    /*vertices[3].position = glm::vec3(-1.0f, 1.0f, 0.0f);
    vertices[3].color = glm::vec3(1.0f, 0.0f, 0.0f);*/

    // Load the index array with data.
    indices[0] = 0;  // Bottom left.
    indices[1] = 2;  // Top middle.
    indices[2] = 1;  // Bottom right.
    /*indices[3] = 0;  // Bottom right.
    indices[4] = 3;  // Bottom right.
    indices[5] = 1;  // Bottom right.*/

    // Allocate an OpenGL vertex array object.
    m_OpenGLPtr->glGenVertexArrays(1, &m_vertexArrayId);
    // Bind the vertex array object to store all the buffers and vertex attributes we create here.
    m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);
    // Generate an ID for the vertex buffer.
    m_OpenGLPtr->glGenBuffers(1, &m_vertexBufferId);
    // Bind the vertex buffer and load the vertex (position and color) data into the vertex buffer.
    m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    m_OpenGLPtr->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType), vertices.get(), GL_STATIC_DRAW);
    // Enable the two vertex array attributes.
    m_OpenGLPtr->glEnableVertexAttribArray(0);  // Vertex position.
    m_OpenGLPtr->glEnableVertexAttribArray(1);  // Vertex color.
    // Specify the location and format of the position portion of the vertex buffer.
    m_OpenGLPtr->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), nullptr);
    // Specify the location and format of the color portion of the vertex buffer.
    m_OpenGLPtr->glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(VertexType), (unsigned char*)nullptr + (sizeof(glm::vec3)));
    // Generate an ID for the index buffer.
    m_OpenGLPtr->glGenBuffers(1, &m_indexBufferId);
    // Bind the index buffer and load the index data into it.
    m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    m_OpenGLPtr->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount* sizeof(unsigned int), indices.get(), GL_STATIC_DRAW);

    return true;
}

void ModelClass::ShutdownBuffers()
{
    // Disable the two vertex array attributes.
    m_OpenGLPtr->glDisableVertexAttribArray(0);
    m_OpenGLPtr->glDisableVertexAttribArray(1);

    // Release the vertex buffer.
    m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_OpenGLPtr->glDeleteBuffers(1, &m_vertexBufferId);

    // Release the index buffer.
    m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    m_OpenGLPtr->glDeleteBuffers(1, &m_indexBufferId);

    // Release the vertex array object.
    m_OpenGLPtr->glBindVertexArray(0);
    m_OpenGLPtr->glDeleteVertexArrays(1, &m_vertexArrayId);
}

void ModelClass::RenderBuffers()
{
    // Bind the vertex array object that stored all the information about the vertex and index buffers.
    m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);
    // Render the vertex buffer using the index buffer.
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
}

