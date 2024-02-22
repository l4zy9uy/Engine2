////////////////////////////////////////////////////////////////////////////////
// Filename: openglclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "OpenGLClass.h"
#include <glm/gtx/string_cast.hpp>

OpenGLClass::OpenGLClass()
= default;


OpenGLClass::OpenGLClass(const OpenGLClass& other)
{
}


OpenGLClass::~OpenGLClass()
= default;


bool OpenGLClass::Initialize(Display* display, Window win, int screenWidth, int screenHeight, float screenNear, float screenDepth, bool vsync)
{
    GLXDrawable drawable;
    float fieldOfView, screenAspect;
    bool result;


    // Store the screen size.
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    // Load the OpenGL extensions that will be used by this program.
    result = LoadExtensionList();
    if(!result)
    {
        return false;
    }

    // Store copies of the display and window pointers.
    m_display = display;
    m_hwnd = win;

    // Set the depth buffer to be entirely cleared to 1.0 values.
    glClearDepth(1.0f);

    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);

    // Set the polygon winding to clockwise front facing for the left handed system.
    glFrontFace(GL_CW);

    // Enable back face culling.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Get the current drawable so we can modify the vertical sync swapping.
    drawable = glXGetCurrentDrawable();

    // Turn on or off the vertical sync depending on the input bool value.
    if(vsync)
    {
        glXSwapIntervalEXT(m_display, drawable, 1);
    }
    else
    {
        glXSwapIntervalEXT(m_display, drawable, 0);
    }

    // Initialize the world/model matrix to the identity matrix.
    BuildIdentityMatrix(m_worldMatrix);
    // Set the field of view and screen aspect ratio.
    fieldOfView = 3.14159265358979323846f / 4.0f;
    screenAspect = (float)screenWidth / (float)screenHeight;

    // Build the perspective projection matrix.
    BuildPerspectiveFovMatrix(m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);
    // Create an orthographic projection matrix for 2D rendering.
    BuildOrthoMatrix(m_orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);

    return true;
}


void OpenGLClass::Shutdown()
{
}


void OpenGLClass::BeginScene(float red, float green, float blue, float alpha)
{
    // Set the color to clear the screen to.
    glClearColor(red, green, blue, alpha);

    // Clear the screen and depth buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void OpenGLClass::EndScene()
{
    // Present the back buffer to the screen since rendering is complete.
    glXSwapBuffers(m_display, m_hwnd);
}

bool OpenGLClass::LoadExtensionList()
{
    glCreateShader = (PFNGLCREATESHADERPROC)glXGetProcAddress((unsigned char*)"glCreateShader");
    if(!glCreateShader)
    {
        return false;
    }

    glShaderSource = (PFNGLSHADERSOURCEPROC)glXGetProcAddress((unsigned char*)"glShaderSource");
    if(!glShaderSource)
    {
        return false;
    }

    glCompileShader = (PFNGLCOMPILESHADERPROC)glXGetProcAddress((unsigned char*)"glCompileShader");
    if(!glCompileShader)
    {
        return false;
    }

    glGetShaderiv = (PFNGLGETSHADERIVPROC)glXGetProcAddress((unsigned char*)"glGetShaderiv");
    if(!glGetShaderiv)
    {
        return false;
    }

    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glXGetProcAddress((unsigned char*)"glGetShaderInfoLog");
    if(!glGetShaderInfoLog)
    {
        return false;
    }

    glCreateProgram = (PFNGLCREATEPROGRAMPROC)glXGetProcAddress((unsigned char*)"glCreateProgram");
    if(!glCreateProgram)
    {
        return false;
    }

    glAttachShader = (PFNGLATTACHSHADERPROC)glXGetProcAddress((unsigned char*)"glAttachShader");
    if(!glAttachShader)
    {
        return false;
    }

    glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glXGetProcAddress((unsigned char*)"glBindAttribLocation");
    if(!glBindAttribLocation)
    {
        return false;
    }

    glLinkProgram = (PFNGLLINKPROGRAMPROC)glXGetProcAddress((unsigned char*)"glLinkProgram");
    if(!glLinkProgram)
    {
        return false;
    }

    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glXGetProcAddress((unsigned char*)"glGetProgramiv");
    if(!glGetProgramiv)
    {
        return false;
    }

    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glXGetProcAddress((unsigned char*)"glGetProgramInfoLog");
    if(!glGetProgramInfoLog)
    {
        return false;
    }

    glDetachShader = (PFNGLDETACHSHADERPROC)glXGetProcAddress((unsigned char*)"glDetachShader");
    if(!glDetachShader)
    {
        return false;
    }

    glDeleteShader = (PFNGLDELETESHADERPROC)glXGetProcAddress((unsigned char*)"glDeleteShader");
    if(!glDeleteShader)
    {
        return false;
    }

    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glXGetProcAddress((unsigned char*)"glDeleteProgram");
    if(!glDeleteProgram)
    {
        return false;
    }

    glUseProgram = (PFNGLUSEPROGRAMPROC)glXGetProcAddress((unsigned char*)"glUseProgram");
    if(!glUseProgram)
    {
        return false;
    }

    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glXGetProcAddress((unsigned char*)"glGetUniformLocation");
    if(!glGetUniformLocation)
    {
        return false;
    }

    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glXGetProcAddress((unsigned char*)"glUniformMatrix4fv");
    if(!glUniformMatrix4fv)
    {
        return false;
    }

    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glXGetProcAddress((unsigned char*)"glGenVertexArrays");
    if(!glGenVertexArrays)
    {
        return false;
    }

    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glXGetProcAddress((unsigned char*)"glBindVertexArray");
    if(!glBindVertexArray)
    {
        return false;
    }

    glGenBuffers = (PFNGLGENBUFFERSPROC)glXGetProcAddress((unsigned char*)"glGenBuffers");
    if(!glGenBuffers)
    {
        return false;
    }

    glBindBuffer = (PFNGLBINDBUFFERPROC)glXGetProcAddress((unsigned char*)"glBindBuffer");
    if(!glBindBuffer)
    {
        return false;
    }

    glBufferData = (PFNGLBUFFERDATAPROC)glXGetProcAddress((unsigned char*)"glBufferData");
    if(!glBufferData)
    {
        return false;
    }

    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glXGetProcAddress((unsigned char*)"glEnableVertexAttribArray");
    if(!glEnableVertexAttribArray)
    {
        return false;
    }

    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glXGetProcAddress((unsigned char*)"glVertexAttribPointer");
    if(!glVertexAttribPointer)
    {
        return false;
    }

    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glXGetProcAddress((unsigned char*)"glDisableVertexAttribArray");
    if(!glDisableVertexAttribArray)
    {
        return false;
    }

    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glXGetProcAddress((unsigned char*)"glDeleteBuffers");
    if(!glDeleteBuffers)
    {
        return false;
    }

    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glXGetProcAddress((unsigned char*)"glDeleteVertexArrays");
    if(!glDeleteVertexArrays)
    {
        return false;
    }

    glUniform1i = (PFNGLUNIFORM1IPROC)glXGetProcAddress((unsigned char*)"glUniform1i");
    if(!glUniform1i)
    {
        return false;
    }

    glActiveTexture = (PFNGLACTIVETEXTUREPROC)glXGetProcAddress((unsigned char*)"glActiveTexture");
    if(!glActiveTexture)
    {
        return false;
    }

    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glXGetProcAddress((unsigned char*)"glGenerateMipmap");
    if(!glGenerateMipmap)
    {
        return false;
    }

    glUniform2fv = (PFNGLUNIFORM2FVPROC)glXGetProcAddress((unsigned char*)"glUniform2fv");
    if(!glUniform2fv)
    {
        return false;
    }

    glUniform3fv = (PFNGLUNIFORM3FVPROC)glXGetProcAddress((unsigned char*)"glUniform3fv");
    if(!glUniform3fv)
    {
        return false;
    }

    glUniform4fv = (PFNGLUNIFORM4FVPROC)glXGetProcAddress((unsigned char*)"glUniform4fv");
    if(!glUniform4fv)
    {
        return false;
    }

    glMapBuffer = (PFNGLMAPBUFFERPROC)glXGetProcAddress((unsigned char*)"glMapBuffer");
    if(!glMapBuffer)
    {
        return false;
    }

    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)glXGetProcAddress((unsigned char*)"glUnmapBuffer");
    if(!glUnmapBuffer)
    {
        return false;
    }

    glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((unsigned char*)"glXSwapIntervalEXT");
    if(!glXSwapIntervalEXT)
    {
        return false;
    }

    glUniform1f = (PFNGLUNIFORM1FPROC)glXGetProcAddress((unsigned char*)"glUniform1f");
    if(!glUniform1f)
    {
        return false;
    }

    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char*)"glGenFramebuffers");
    if(!glGenFramebuffers)
    {
        return false;
    }

    glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char*)"glDeleteFramebuffers");
    if(!glDeleteFramebuffers)
    {
        return false;
    }

    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glXGetProcAddress((unsigned char*)"glBindFramebuffer");
    if(!glBindFramebuffer)
    {
        return false;
    }

    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)glXGetProcAddress((unsigned char*)"glFramebufferTexture2D");
    if(!glFramebufferTexture2D)
    {
        return false;
    }

    glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)glXGetProcAddress((unsigned char*)"glGenRenderbuffers");
    if(!glGenRenderbuffers)
    {
        return false;
    }

    glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)glXGetProcAddress((unsigned char*)"glBindRenderbuffer");
    if(!glBindRenderbuffer)
    {
        return false;
    }

    glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)glXGetProcAddress((unsigned char*)"glRenderbufferStorage");
    if(!glRenderbufferStorage)
    {
        return false;
    }

    glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glXGetProcAddress((unsigned char*)"glFramebufferRenderbuffer");
    if(!glFramebufferRenderbuffer)
    {
        return false;
    }

    glDrawBuffers = (PFNGLDRAWBUFFERSARBPROC)glXGetProcAddress((unsigned char*)"glDrawBuffers");
    if(!glDrawBuffers)
    {
        return false;
    }

    glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)glXGetProcAddress((unsigned char*)"glDeleteRenderbuffers");
    if(!glDeleteRenderbuffers)
    {
        return false;
    }

    glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)glXGetProcAddress((unsigned char*)"glBlendFuncSeparate");
    if(!glBlendFuncSeparate)
    {
        return false;
    }

    return true;
}

void OpenGLClass::TurnZBufferOn()
{
    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);
}


void OpenGLClass::TurnZBufferOff()
{
    // Disable depth testing.
    glDisable(GL_DEPTH_TEST);
}


void OpenGLClass::EnableAlphaBlending()
{
    // Enable alpha blending.
    glEnable(GL_BLEND);

    // Set the blending equation.
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
}


void OpenGLClass::DisableAlphaBlending()
{
    // Disable alpha blending.
    glDisable(GL_BLEND);
}


void OpenGLClass::SetBackBufferRenderTarget()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void OpenGLClass::ResetViewport()
{
    glViewport(0, 0, m_screenWidth, m_screenHeight);
}


void OpenGLClass::EnableClipping()
{
    // Enable clip plane 0.
    glEnable(GL_CLIP_DISTANCE0);
}


void OpenGLClass::DisableClipping()
{
    // Disable clip plane 0.
    glDisable(GL_CLIP_DISTANCE0);
}

void OpenGLClass::BuildIdentityMatrix(glm::mat4 &matrix) {
    matrix = glm::mat4(1);
}

void OpenGLClass::BuildPerspectiveFovMatrix(glm::mat4 &mat, float fieldOfView, float screenAspect, float screenNear, float screenDepth) {
    //mat = glm::perspectiveLH(fieldOfView, screenAspect, screenNear, screenDepth);
    mat = glm::perspective(fieldOfView, screenAspect, screenNear, screenDepth);
}

void OpenGLClass::BuildOrthoMatrix(glm::mat4 &mat, float screenWidth,  float screenHeight, float screenNear, float screenDepth) {
    //mat = glm::orthoLH_ZO(0.0f, screenWidth, 0.0f, screenHeight, screenNear, screenDepth);
    mat = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, screenNear, screenDepth);
}

const glm::mat4 &OpenGLClass::getMWorldMatrix() const {
    return m_worldMatrix;
}

const glm::mat4 &OpenGLClass::getMProjectionMatrix() const {
    return m_projectionMatrix;
}

const glm::mat4 &OpenGLClass::getMOrthoMatrix() const {
    return m_orthoMatrix;
}

void OpenGLClass::MatrixTranspose(glm::mat4 &result, glm::mat4 &matrix) {
    result = glm::transpose(matrix);
}
