//
// Created by l4zy9uy on 2/17/24.
//

#include <iostream>
#include "../include/CameraClass.h"
#include <glm/gtx/string_cast.hpp>

CameraClass::CameraClass() : m_position(0), m_rotation(0), m_viewMatrix(0) { }

CameraClass::CameraClass(const CameraClass& other) { }

CameraClass::~CameraClass()
= default;

void CameraClass::Render()
{
    glm::vec3 up(0.0f, 1.0f, 0.0f), position(m_position), lookAt(0.0f, 0.0f, 1.0f);
    glm::mat3 rotationMatrix;
    float yaw, pitch, roll;

    pitch = m_rotation.x * 0.0174532925f;
    yaw   = m_rotation.y * 0.0174532925f;
    roll  = m_rotation.z * 0.0174532925f;
    // Create the rotation matrix from the yaw, pitch, and roll values.
    MatrixRotationYawPitchRoll(rotationMatrix, yaw, pitch, roll);
    // Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
    TransformCoord(lookAt, rotationMatrix);
    TransformCoord(up, rotationMatrix);

    // Translate the rotated camera position to the location of the viewer.
    lookAt += position;
    // Finally create the view matrix from the three updated vectors.
    BuildViewMatrix(position, lookAt, up);
}

void CameraClass::TransformCoord(glm::vec3 & vector, glm::mat3 & matrix) {
    // Transform the vector by the 3x3 matrix.
    vector.x = (vector.x * matrix[0][0]) + (vector.y * matrix[1][0]) + (vector.z * matrix[2][0]);
    vector.y = (vector.x * matrix[0][1]) + (vector.y * matrix[1][1]) + (vector.z * matrix[2][1]);
    vector.z = (vector.x * matrix[0][2]) + (vector.y * matrix[1][2]) + (vector.z * matrix[2][2]);
}

void CameraClass::BuildViewMatrix(glm::vec3 &position, glm::vec3 &lookAt, glm::vec3 &up)
{
    //m_viewMatrix = glm::lookAtLH(position, lookAt, up);
    m_viewMatrix = glm::lookAt(position, lookAt, up);
}
const glm::mat4 &CameraClass::getMViewMatrix() const
{
    return m_viewMatrix;
}

void CameraClass::setMViewMatrix(const glm::mat4 &mViewMatrix2)
{
    m_viewMatrix = mViewMatrix2;
}

const glm::vec3 &CameraClass::getMPosition() const {
    return m_position;
}

void CameraClass::setMPosition(const glm::vec3 &mPosition) {
    m_position = mPosition;
}

const glm::vec3 &CameraClass::getMRotation() const {
    return m_rotation;
}

void CameraClass::setMRotation(const glm::vec3 &mRotation) {
    m_rotation = mRotation;
}

void CameraClass::MatrixRotationYawPitchRoll(glm::mat3 &mat, float yaw, float pitch, float roll)
{
    float cYaw, cPitch, cRoll, sYaw, sPitch, sRoll;

    // Get the cosine and sin of the yaw, pitch, and roll.
    cYaw = cosf(yaw);
    cPitch = cosf(pitch);
    cRoll = cosf(roll);

    sYaw = sinf(yaw);
    sPitch = sinf(pitch);
    sRoll = sinf(roll);

    // Calculate the yaw, pitch, roll rotation matrix.
    mat[0][0] = (cRoll * cYaw) + (sRoll * sPitch * sYaw);
    mat[0][1] = (sRoll * cPitch);
    mat[0][2] = (cRoll * -sYaw) + (sRoll * sPitch * cYaw);

    mat[1][0] = (-sRoll * cYaw) + (cRoll * sPitch * sYaw);
    mat[1][1] = (cRoll * cPitch);
    mat[1][2] = (sRoll * sYaw) + (cRoll * sPitch * cYaw);

    mat[2][0] = (cPitch * sYaw);
    mat[2][1] = -sPitch;
    mat[2][2] = (cPitch * cYaw);
}


