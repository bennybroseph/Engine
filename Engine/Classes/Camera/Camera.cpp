#include "Camera.h"

Camera Camera::CameraControl;

Camera::Camera()
{
    CameraX = 0;
    CameraY = 0;
}

void Camera::MoveCamera(float IncreaseX, float IncreaseY)
{
    CameraX += IncreaseX;
    CameraY += IncreaseY;
}

void Camera::SetCamera(float X, float Y)
{
    CameraX = X;
    CameraY = Y;
}
