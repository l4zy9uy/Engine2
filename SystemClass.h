//
// Created by l4zy9uy on 2/15/24.
//

#ifndef ENGINE2_SYSTEMCLASS_H
#define ENGINE2_SYSTEMCLASS_H

#include <X11/Xlib.h>
#include "ApplicationClass.h"
#include "InputClass.h"
#include <GL/glx.h>
#include <GL/gl.h>
#include <unistd.h>
#include <cstring>
#include <memory>
////////////////////////////////////////////////////////////////////////////////
// Class Name: SystemClass
////////////////////////////////////////////////////////////////////////////////
class SystemClass
{
public:
    SystemClass();
    SystemClass(const SystemClass&);
    ~SystemClass();

    bool Initialize();
    void Shutdown();
    void Frame();

private:
    bool InitializeWindow(int&, int&);
    void ShutdownWindow();
    void ReadInput();

private:
    std::unique_ptr<ApplicationClass> m_Application;
    std::unique_ptr<InputClass> m_Input;
    Display* m_videoDisplay;
    Window m_hwnd;
    GLXContext m_renderingContext;
};

#endif //ENGINE2_SYSTEMCLASS_H
