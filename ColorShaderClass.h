//
// Created by l4zy9uy on 2/17/24.
//

#ifndef ENGINE2_COLORSHADERCLASS_H
#define ENGINE2_COLORSHADERCLASS_H
#include "OpenGLClass.h"
#include <iostream>
class ColorShaderClass {
public:
    ColorShaderClass();
    ColorShaderClass(const ColorShaderClass&);
    ~ColorShaderClass();

    bool Initialize(std::shared_ptr<OpenGLClass> &);
    void Shutdown();

    bool SetShaderParameters(float*, float*, float*);

private:
    bool InitializeShader(char*, char*);
    void ShutdownShader();
    char* LoadShaderSourceFile(char*);
    void OutputShaderErrorMessage(unsigned int, char*);
    void OutputLinkerErrorMessage(unsigned int);

private:
    std::shared_ptr<OpenGLClass> m_OpenGLPtr;
    unsigned int m_vertexShader;
    unsigned int m_fragmentShader;
    unsigned int m_shaderProgram;
};


#endif //ENGINE2_COLORSHADERCLASS_H
