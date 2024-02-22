//
// Created by l4zy9uy on 2/17/24.
//

#ifndef ENGINE2_MODELCLASS_H
#define ENGINE2_MODELCLASS_H


#include "OpenGLClass.h"
#include <glm/vec3.hpp>
class ModelClass {
private:
    struct VertexType
    {
        glm::vec3 position;
        glm::vec3 color;
    };
public:
    ModelClass();
    ModelClass(const ModelClass&);
    ~ModelClass();

    bool Initialize(std::shared_ptr<OpenGLClass> &);
    void Shutdown();
    void Render();

private:
    bool InitializeBuffers();
    void ShutdownBuffers();
    void RenderBuffers();

private:
    std::shared_ptr<OpenGLClass> m_OpenGLPtr;
    unsigned long m_vertexCount, m_indexCount;
    unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;
};


#endif //ENGINE2_MODELCLASS_H
