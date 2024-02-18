///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "SystemClass.h"
#include <memory>

//////////////////
// MAIN PROGRAM //
//////////////////
int main()
{
    std::unique_ptr<SystemClass> System;
    bool result;


    // Create and initialize the system object.
    System = std::make_unique<SystemClass>();

    result = System->Initialize();
    if(!result)
    {
        return -1;
    }

    // Perform the frame processing for the system object.
    System->Frame();

    // Release the system object.
    System->Shutdown();

    return 0;
}