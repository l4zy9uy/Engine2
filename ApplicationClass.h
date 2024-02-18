//
// Created by l4zy9uy on 2/15/24.
//

#ifndef ENGINE2_APPLICATIONCLASS_H
#define ENGINE2_APPLICATIONCLASS_H

#include "InputClass.h"
#include "OpenGLClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"
#include <memory>
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_NEAR = 0.3f;
const float SCREEN_DEPTH = 1000.0f;


////////////////////////////////////////////////////////////////////////////////
// Class Name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
    ApplicationClass();
    ApplicationClass(const ApplicationClass&);
    ~ApplicationClass();

    bool Initialize(Display*, Window, int, int);
    void Shutdown();
    bool Frame(std::unique_ptr<InputClass> &);

private:
    bool Render();

private:
    std::shared_ptr<OpenGLClass> m_OpenGL;
    std::unique_ptr<ColorShaderClass> m_ColorShader;
    std::unique_ptr<ModelClass> m_Model;
    std::unique_ptr<CameraClass> m_Camera;
};

#endif //ENGINE2_APPLICATIONCLASS_H
