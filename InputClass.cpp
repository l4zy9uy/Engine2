//
// Created by l4zy9uy on 2/15/24.
//

#include "InputClass.h"
#include <iostream>

InputClass::InputClass()
= default;


InputClass::InputClass(const InputClass& other)
{
}


InputClass::~InputClass()
= default;


void InputClass::Initialize()
{
    // Initialize the keyboard state.
    for(bool & i : m_keyboardState)
    {
        i = false;
    }

    }


void InputClass::KeyDown(int keySymbol)
{
    if(keySymbol == 65307) { std::cout << "escape pressed!\n"; m_keyboardState[KEY_ESCAPE] = true; }

    }


void InputClass::KeyUp(int keySymbol)
{
    if(keySymbol == 65307) { std::cout << "escape released!\n"; m_keyboardState[KEY_ESCAPE] = false; }

    }


bool InputClass::IsEscapePressed()
{
    return m_keyboardState[KEY_ESCAPE];
}
