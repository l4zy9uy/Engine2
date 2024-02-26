//
// Created by l4zy9uy on 2/15/24.
//

#ifndef ENGINE2_INPUTCLASS_H
#define ENGINE2_INPUTCLASS_H


/////////////
// DEFINES //
/////////////
const int KEY_ESCAPE = 0;


////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
    InputClass();
    InputClass(const InputClass&);
    ~InputClass();

    void Initialize();

    void KeyDown(int);
    void KeyUp(int);

    bool IsEscapePressed();

private:
    bool m_keyboardState[256];
};

#endif //ENGINE2_INPUTCLASS_H
