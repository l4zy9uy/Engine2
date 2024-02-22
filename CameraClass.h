//
// Created by l4zy9uy on 2/17/24.
//

#ifndef ENGINE2_CAMERACLASS_H
#define ENGINE2_CAMERACLASS_H
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
class CameraClass {
public:
    CameraClass();
    CameraClass(const CameraClass&);
    ~CameraClass();
    void setMViewMatrix(const glm::mat4 &mViewMatrix2);
    const glm::mat4 &getMViewMatrix() const;
    void Render();
private:
    void MatrixRotationYawPitchRoll(glm::mat3 &, float, float, float);
    void TransformCoord(glm::vec3 &, glm::mat3 &);
    void BuildViewMatrix(glm::vec3 &, glm::vec3 &, glm::vec3 &);

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::mat4 m_viewMatrix;
public:
    const glm::vec3 &getMPosition() const;
    void setMPosition(const glm::vec3 &mPosition);
    const glm::vec3 &getMRotation() const;
    void setMRotation(const glm::vec3 &mRotation);
};
#endif //ENGINE2_CAMERACLASS_H
