//
// Created by l4zy9uy on 2/17/24.
//

#ifndef ENGINE2_MODELCLASS_H
#define ENGINE2_MODELCLASS_H


#include "OpenGLClass.h"

class ModelClass {
private:
    struct VertexType
    {
        float x, y, z;
        float r, g, b;
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
