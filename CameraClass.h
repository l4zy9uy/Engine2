//
// Created by l4zy9uy on 2/17/24.
//

#ifndef ENGINE2_CAMERACLASS_H
#define ENGINE2_CAMERACLASS_H

#include <cmath>

class CameraClass {
private:
    struct VectorType
    {
        float x, y, z;
    };

public:
    CameraClass();
    CameraClass(const CameraClass&);
    ~CameraClass();
    void SetPosition(float, float, float);
    void SetRotation(float, float, float);

    void GetPosition(float*);
    void GetRotation(float*);

    void Render();
    void GetViewMatrix(float*);

private:
    void MatrixRotationYawPitchRoll(float*, float, float, float);
    void TransformCoord(VectorType&, float*);
    void BuildViewMatrix(VectorType, VectorType, VectorType);

private:
    float m_positionX, m_positionY, m_positionZ;
    float m_rotationX, m_rotationY, m_rotationZ;
    float m_viewMatrix[16];
};


#endif //ENGINE2_CAMERACLASS_H
