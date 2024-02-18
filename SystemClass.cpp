//
// Created by l4zy9uy on 2/15/24.
//

#include <GL/glu.h>
#include "SystemClass.h"

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

// Helper to check for extension string presence.  Adapted from:
//   http://www.opengl.org/resources/features/OGLextensions/
static bool isExtensionSupported(const char *extList, const char *extension)
{
    const char *start;
    const char *where, *terminator;

    /* Extension names should not have spaces. */
    where = strchr(extension, ' ');
    if (where || *extension == '\0')
        return false;

    /* It takes a bit of care to be fool-proof about parsing the
       OpenGL extensions string. Don't be fooled by sub-strings,
       etc. */
    for (start=extList;;) {
        where = strstr(start, extension);

        if (!where)
            break;

        terminator = where + strlen(extension);

        if ( where == start || *(where - 1) == ' ' )
            if ( *terminator == ' ' || *terminator == '\0' )
                return true;

        start = terminator;
    }

    return false;
}

static bool ctxErrorOccurred = false;
static int ctxErrorHandler( Display *dpy, XErrorEvent *ev )
{
    ctxErrorOccurred = true;
    return 0;
}

SystemClass::SystemClass()
= default;

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
= default;

bool SystemClass::Initialize()
{
    int screenWidth, screenHeight;
    bool result;


    // Create and initialize the input object.
    m_Input = std::make_unique<InputClass>();

    m_Input->Initialize();

    // Initialize the screen size.
    screenWidth = 0;
    screenHeight = 0;

    // Initialize the X11 window.
    result = InitializeWindow(screenWidth, screenHeight);
    if(!result)
    {
        return false;
    }

    // Create and initialize the application object.
    m_Application = std::make_unique<ApplicationClass>();

    result = m_Application->Initialize(m_videoDisplay, m_hwnd, screenWidth, screenHeight);
    if(!result)
    {
        return false;
    }

    return true;
}


void SystemClass::Shutdown()
{
    // Release the application object.
    if(m_Application)
    {
        m_Application->Shutdown();
    }

    // Release the X11 window.
    ShutdownWindow();
    }


void SystemClass::Frame()
{
    bool done, result;


    // Loop until the application is finished running.
    done = false;
    while(!done)
    {
        // Read the X11 input.
        ReadInput();

        // Do the frame processing for the application object.
        result = m_Application->Frame(m_Input);
        if(!result)
        {
            done = true;
        }
    }

    }


//bool SystemClass::InitializeWindow(int& screenWidth, int& screenHeight)
//{
//    Window rootWindow;
//    GLint attributeList[15];
//    Colormap colorMap;
//    XSetWindowAttributes setWindowAttributes;
//    XWindowAttributes windowAttributes;
//    Screen* defaultScreen;
//    bool result, windowSet;
//    int majorVersion, status, defaultScreenWidth, defaultScreenHeight, posX, posY;
//    Atom wmState, fullScreenState, motifHints;
//    XEvent fullScreenEvent;
//    long motifHintList[5];
//
//
//    // Open a connection to the X server on the local computer.
//    m_videoDisplay = XOpenDisplay(nullptr);
//    if(m_videoDisplay == nullptr)
//    {
//        return false;
//    }
//
//    // Get a handle to the root window.
//    rootWindow = DefaultRootWindow(m_videoDisplay);
//
//    // Setup the OpenGL attributes for the window.
//    attributeList[0]  = GLX_RGBA;  // Support for 24 bit color and an alpha channel.
//    attributeList[1]  = GLX_DEPTH_SIZE;  // Support for 24 bit depth buffer.
//    attributeList[2]  = 24;
//    attributeList[3]  = GLX_STENCIL_SIZE;  // Support for 8 bit stencil buffer.
//    attributeList[4]  = 8;
//    attributeList[5]  = GLX_DOUBLEBUFFER;  // Support for double buffering.
//    attributeList[6]  = GLX_RED_SIZE;  // 8 bits for each channel.
//    attributeList[7]  = 8;
//    attributeList[8]  = GLX_GREEN_SIZE;
//    attributeList[9]  = 8;
//    attributeList[10] = GLX_BLUE_SIZE;
//    attributeList[11] = 8;
//    attributeList[12] = GLX_ALPHA_SIZE;
//    attributeList[13] = 8;
//    attributeList[14] = None;  // Null terminate the attribute list.
//
//    // Query for a visual format that fits the attributes we want.
//    std::unique_ptr<XVisualInfo, decltype(&XFree)> visualInfo(glXChooseVisual(m_videoDisplay, 0, attributeList), XFree);
//    if(visualInfo == nullptr)
//    {
//        return false;
//    }
//
//    // Create a color map for the window for the specified visual type.
//    colorMap = XCreateColormap(m_videoDisplay, rootWindow, visualInfo->visual, AllocNone);
//
//    // Fill out the structure for setting the window attributes.
//    setWindowAttributes.colormap = colorMap;
//    setWindowAttributes.event_mask = KeyPressMask | KeyReleaseMask;
//
//    // Get the size of the default screen.
//    if(FULL_SCREEN)
//    {
//        defaultScreen = XDefaultScreenOfDisplay(m_videoDisplay);
//        screenWidth = XWidthOfScreen(defaultScreen);
//        screenHeight = XHeightOfScreen(defaultScreen);
//    }
//    else
//    {
//        screenWidth = 1024;
//        screenHeight = 768;
//    }
//
//    // Create the window with the desired settings.
//    m_hwnd = XCreateWindow(m_videoDisplay, rootWindow, 0, 0, screenWidth, screenHeight, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWColormap | CWEventMask, &setWindowAttributes);
//    // Map the newly created regular window to the video display.
//    XMapWindow(m_videoDisplay, m_hwnd);
//
//    // Set the name of the window.
//    XStoreName(m_videoDisplay, m_hwnd, "Client");
//
//    // If full screen mode then we send the full screen event and remove the border decoration.
//    if(FULL_SCREEN)
//    {
//        // Setup the full screen states.
//        wmState = XInternAtom(m_videoDisplay, "_NET_WM_STATE", False);
//        fullScreenState = XInternAtom(m_videoDisplay, "_NET_WM_STATE_FULLSCREEN", False);
//
//        // Setup the X11 event message that we need to send to make the screen go full screen mode.
//        memset(&fullScreenEvent, 0, sizeof(fullScreenEvent));
//
//        fullScreenEvent.type = ClientMessage;
//        fullScreenEvent.xclient.window = m_hwnd;
//        fullScreenEvent.xclient.message_type = wmState;
//        fullScreenEvent.xclient.format = 32;
//        fullScreenEvent.xclient.data.l[0] = 2;
//        fullScreenEvent.xclient.data.l[1] = fullScreenState;
//        fullScreenEvent.xclient.data.l[2] = 0;
//        fullScreenEvent.xclient.data.l[3] = 1;
//        fullScreenEvent.xclient.data.l[4] = 0;
//
//        // Send the full screen event message to the X11 server.
//        status = XSendEvent(m_videoDisplay, DefaultRootWindow(m_videoDisplay), False, SubstructureRedirectMask | SubstructureNotifyMask, &fullScreenEvent);
//        if(status != 1)
//        {
//            return false;
//        }
//
//        // Setup the motif hints to remove the border in full screen mode.
//        motifHints = XInternAtom(m_videoDisplay, "_MOTIF_WM_HINTS", False);
//
//        motifHintList[0] = 2;  // Remove border.
//        motifHintList[1] = 0;
//        motifHintList[2] = 0;
//        motifHintList[3] = 0;
//        motifHintList[4] = 0;
//
//        // Change the window property and remove the border.
//        status = XChangeProperty(m_videoDisplay, m_hwnd, motifHints, motifHints, 32, PropModeReplace, (unsigned char*)&motifHintList, 5);
//        if(status != 1)
//        {
//            return false;
//        }
//
//        // Flush the display to apply all the full screen settings.
//        status = XFlush(m_videoDisplay);
//        if(status != 1)
//        {
//            return false;
//        }
//
//        // Now sleep for one second for the flush to occur before making a gl context, or if too early the screen gets squished in full screen sometimes.
//        sleep(1);
//    }
//    int context_attribs[] = {
//            GLX_CONTEXT_MAJOR_VERSION_ARB, 4, // Request OpenGL version 4.x
//            GLX_CONTEXT_MINOR_VERSION_ARB, 6, // Request OpenGL version x.6
//            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB, // Request a core profile
//            0 // Zero-terminate the attribute list
//    };
//    // Create an OpenGL rendering context.
//    m_renderingContext = glXCreateContext(m_videoDisplay, visualInfo.get(), nullptr, GL_TRUE);
//
//    if(m_renderingContext == nullptr)
//    {
//        return false;
//    }
//
//    // Attach the OpenGL rendering context to the newly created window.
//    result = glXMakeCurrent(m_videoDisplay, m_hwnd, m_renderingContext);
//
//    GLXContext currentContext = glXGetCurrentContext();
//
//    if (currentContext != NULL) {
//        // There is a current context
//        // You can print or do something with the current context
//        std::cout << "Current OpenGL Context: " << currentContext << std::endl;
//    } else {
//        // No current context
//        // Example: std::cout << "No current OpenGL context." << std::endl;
//    }
//
//    if(!result)
//    {
//        return false;
//    }
//
//    // Check that OpenGL 4.0 is supported at a minimum.
//    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
//    if(majorVersion < 4)
//    {
//        return false;
//    }
//
//    // Confirm that we have a direct rendering context.
//    result = glXIsDirect(m_videoDisplay, m_renderingContext);
//    if(!result)
//    {
//        return false;
//    }
//
//    // If windowed then move the window to the middle of the screen.
//    if(!FULL_SCREEN)
//    {
//        defaultScreen = XDefaultScreenOfDisplay(m_videoDisplay);
//        defaultScreenWidth = XWidthOfScreen(defaultScreen);
//        defaultScreenHeight = XHeightOfScreen(defaultScreen);
//
//        posX = (defaultScreenWidth - screenWidth) / 2;
//        posY = (defaultScreenHeight - screenHeight) / 2;
//
//        status = XMoveWindow(m_videoDisplay, m_hwnd, posX, posY);
//        if(status != 1)
//        {
//            return false;
//        }
//    }
//    return true;
//}

bool SystemClass::InitializeWindow(int& screenWidth, int& screenHeight)
{
    m_videoDisplay = XOpenDisplay(nullptr);

    if (!m_videoDisplay)
    {
        printf("Failed to open X display\n");
        return false;
    }

    // Get a matching FB config
    static int visual_attribs[] =
            {
                    GLX_X_RENDERABLE    , True,
                    GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
                    GLX_RENDER_TYPE     , GLX_RGBA_BIT,
                    GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
                    GLX_RED_SIZE        , 8,
                    GLX_GREEN_SIZE      , 8,
                    GLX_BLUE_SIZE       , 8,
                    GLX_ALPHA_SIZE      , 8,
                    GLX_DEPTH_SIZE      , 24,
                    GLX_STENCIL_SIZE    , 8,
                    GLX_DOUBLEBUFFER    , True,
                    //GLX_SAMPLE_BUFFERS  , 1,
                    //GLX_SAMPLES         , 4,
                    None
            };

    int glx_major, glx_minor;

    // FBConfigs were added in GLX version 1.4.
    if ( !glXQueryVersion( m_videoDisplay, &glx_major, &glx_minor ) ||
         ( ( glx_major == 1 ) && ( glx_minor < 4 ) ) || ( glx_major < 1 ) )
    {
        printf("Invalid GLX version");
        exit(1);
    }

    printf( "Getting matching framebuffer configs\n" );
    int fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(m_videoDisplay, XDefaultScreen(m_videoDisplay), visual_attribs, &fbcount);
    if (!fbc)
    {
        printf( "Failed to retrieve a framebuffer config\n" );
        return false;
    }
    printf( "Found %d matching FB configs.\n", fbcount );

    // Pick the FB config/visual with the most samples per pixel
    printf( "Getting XVisualInfos\n" );
    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

    int i;
    for (i=0; i<fbcount; ++i)
    {
        XVisualInfo *vi = glXGetVisualFromFBConfig( m_videoDisplay, fbc[i] );
        if ( vi )
        {
            int samp_buf, samples;
            glXGetFBConfigAttrib( m_videoDisplay, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
            glXGetFBConfigAttrib( m_videoDisplay, fbc[i], GLX_SAMPLES       , &samples  );

            printf( "  Matching fbconfig %d, visual ID 0x%2lx: SAMPLE_BUFFERS = %d,"
                    " SAMPLES = %d\n",
                    i, vi -> visualid, samp_buf, samples );

            if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
                best_fbc = i, best_num_samp = samples;
            if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
                worst_fbc = i, worst_num_samp = samples;
        }
        XFree( vi );
    }

    GLXFBConfig bestFbc = fbc[ best_fbc ];

    // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
    XFree( fbc );

    // Get a visual
    XVisualInfo *vi = glXGetVisualFromFBConfig( m_videoDisplay, bestFbc );
    printf( "Chosen visual ID = 0x%lx\n", vi->visualid );

    printf( "Creating colormap\n" );
    XSetWindowAttributes swa;
    Colormap cmap;
    swa.colormap =  XCreateColormap( m_videoDisplay,
                                           RootWindow( m_videoDisplay, vi->screen ),
                                           vi->visual, AllocNone );
    swa.background_pixmap = None ;
    swa.border_pixel      = 0;
    swa.event_mask        = StructureNotifyMask;

    printf( "Creating window\n" );
    screenHeight = 768;
    screenWidth = 1024;
    m_hwnd = XCreateWindow( m_videoDisplay, RootWindow( m_videoDisplay, vi->screen ),
                                0, 0, screenWidth, screenHeight, 0, vi->depth, InputOutput,
                                vi->visual,
                                CWBorderPixel|CWColormap|CWEventMask, &swa );
    if ( !m_hwnd )
    {
        printf( "Failed to create window.\n" );
        return false;
    }

    // Done with the visual info data
    XFree( vi );
    XStoreName( m_videoDisplay, m_hwnd, "GL 4.6 Window" );
    printf( "Mapping window\n" );
    XMapWindow( m_videoDisplay, m_hwnd );

    XSelectInput(m_videoDisplay, m_hwnd, KeyPressMask | KeyReleaseMask);
    // Get the default screen's GLX extension list
    const char *glxExts = glXQueryExtensionsString( m_videoDisplay,
                                                    XDefaultScreen( m_videoDisplay ) );
    // NOTE: It is not necessary to create or make current to a context before
    // calling glXGetProcAddressARB
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
            glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
    // Install an X error handler so the application won't exit if GL 3.0
    // context allocation fails.
    //
    // Note this error handler is global.  All display connections in all threads
    // of a process use the same error handler, so be sure to guard against other
    // threads issuing X commands while this code is running.
    ctxErrorOccurred = false;
    int (*oldHandler)(Display*, XErrorEvent*) =
    XSetErrorHandler(&ctxErrorHandler);
    // Check for the GLX_ARB_create_context extension string and the function.
    // If either is not present, use GLX 1.4 context creation method.
    if ( !isExtensionSupported( glxExts, "GLX_ARB_create_context" ) ||
         !glXCreateContextAttribsARB )
    {
        printf( "glXCreateContextAttribsARB() not found"
                " ... using old-style GLX context\n" );
        m_renderingContext = glXCreateNewContext( m_videoDisplay, bestFbc, GLX_RGBA_TYPE, nullptr, True );
    }
    // If it does, try to get a GL 4.6 context!
    else
    {
        int context_attribs[] =
                {
                        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
                        GLX_CONTEXT_MINOR_VERSION_ARB, 6,
                        //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                        None
                };

        printf( "Creating context\n" );
        m_renderingContext = glXCreateContextAttribsARB( m_videoDisplay, bestFbc, 0,
                                          True, context_attribs );

        // Sync to ensure any errors generated are processed.
        XSync( m_videoDisplay, False );
        if ( !ctxErrorOccurred && m_renderingContext )
            printf( "Created GL 4.6 context\n" );
        else
        {
            // Couldn't create GL 3.0 context.  Fall back to old-style 2.x context.
            // When a context version below 3.0 is requested, implementations will
            // return the newest context version compatible with OpenGL versions less
            // than version 3.0.
            // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
            context_attribs[1] = 1;
            // GLX_CONTEXT_MINOR_VERSION_ARB = 0
            context_attribs[3] = 0;

            ctxErrorOccurred = false;

            printf( "Failed to create GL 4.6 context"
                    " ... using old-style GLX context\n" );
            m_renderingContext = glXCreateContextAttribsARB( m_videoDisplay, bestFbc, nullptr,
                                              True, context_attribs );
        }
    }

    // Sync to ensure any errors generated are processed.
    XSync( m_videoDisplay, False );
    // Restore the original error handler
    XSetErrorHandler( oldHandler );

    if ( ctxErrorOccurred || !m_renderingContext )
    {
        printf( "Failed to create an OpenGL context\n" );
        return false;
    }
    // Verifying that context is a direct context
    if ( ! glXIsDirect ( m_videoDisplay, m_renderingContext ) )
    {
        printf( "Indirect GLX rendering context obtained\n" );
    }
    else
    {
        printf( "Direct GLX rendering context obtained\n" );
    }

    printf( "Making context current\n" );
    glXMakeCurrent( m_videoDisplay, m_hwnd, m_renderingContext );
    return true;
}

void SystemClass::ShutdownWindow()
{
    // Shutdown and close the window.
    glXMakeCurrent(m_videoDisplay, None, nullptr);
    glXDestroyContext(m_videoDisplay, m_renderingContext);
    XUnmapWindow(m_videoDisplay, m_hwnd);
    XDestroyWindow(m_videoDisplay, m_hwnd);
    XCloseDisplay(m_videoDisplay);
}


void SystemClass::ReadInput()
{
    XEvent event;
    long eventMask;
    bool foundEvent;
    char keyBuffer[32];
    KeySym keySymbol;


    // Set the event mask to the types of events we are interested in.
    eventMask = KeyPressMask | KeyReleaseMask;

    // Perform the frame processing for the application.
    foundEvent = XCheckWindowEvent(m_videoDisplay, m_hwnd, eventMask, &event);
    if(foundEvent)
    {
        std::cout << "Found event!\n";
        // Key press.
        if(event.type == KeyPress)
        {
            XLookupString(&event.xkey, keyBuffer, sizeof(keyBuffer), &keySymbol, nullptr);
            m_Input->KeyDown((int)keySymbol);
        }

        // Key release.
        if(event.type == KeyRelease)
        {
            XLookupString(&event.xkey, keyBuffer, sizeof(keyBuffer), &keySymbol, nullptr);
            m_Input->KeyUp((int)keySymbol);
        }
    }

    }
