//
// Created by l4zy9uy on 2/15/24.
//

#include "ApplicationClass.h"

ApplicationClass::ApplicationClass()
= default;

ApplicationClass::ApplicationClass(const ApplicationClass &other) {
}

ApplicationClass::~ApplicationClass()
= default;

bool ApplicationClass::Initialize(Display *display, Window win, int screenWidth, int screenHeight) {
    bool result;


    // Create and initialize the OpenGL object.
    m_OpenGL = std::make_shared<OpenGLClass>();

    result = m_OpenGL->Initialize(display, win, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH, VSYNC_ENABLED);
    if (!result) {
        return false;
    }
    // Create and initialize the color shader object.
    m_ColorShader = std::make_unique<ColorShaderClass>();

    result = m_ColorShader->Initialize(m_OpenGL);
    if (!result) {
        return false;
    }

    // Create and initialize the camera object.
    m_Camera = std::make_unique<CameraClass>();

    m_Camera->SetPosition(0.0f, 0.0f, -5.0f);
    m_Camera->Render();

    // Create and initialize the model object.
    m_Model = std::make_unique<ModelClass>();

    result = m_Model->Initialize(m_OpenGL);
    if (!result) {
        return false;
    }

    return true;
}

void ApplicationClass::Shutdown() {
    // Release the model object.
    if (m_Model) {
        m_Model->Shutdown();
    }
    // Release the color shader object.
    if (m_ColorShader) {
        m_ColorShader->Shutdown();
    }
    // Release the OpenGL object.
    if (m_OpenGL) {
        m_OpenGL->Shutdown();
    }
}

bool ApplicationClass::Frame(std::unique_ptr<InputClass> &Input) {
    bool result;


    // Check if the escape key has been pressed, if so quit.
    if (Input->IsEscapePressed()) {
        return false;
    }

    // Render the graphics scene.
    result = Render();
    if (!result) {
        return false;
    }

    return true;
}

bool ApplicationClass::Render() {
    float worldMatrix[16], viewMatrix[16], projectionMatrix[16];
    bool result;

    // Clear the buffers to begin the scene.
    m_OpenGL->BeginScene(1.0f, 1.0f, 1.0f, 1.0f);

    // Get the world, view, and projection matrices from the opengl and camera objects.
    m_OpenGL->GetWorldMatrix(worldMatrix);
    m_Camera->GetViewMatrix(viewMatrix);
    m_OpenGL->GetProjectionMatrix(projectionMatrix);

    // Set the color shader as the current shader program and set the matrices that it will use for rendering.
    result = m_ColorShader->SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix);
    if (!result) {
        return false;
    }

    // Render the model.
    m_Model->Render();

    // Present the rendered scene to the screen.
    m_OpenGL->EndScene();

    return true;
}
