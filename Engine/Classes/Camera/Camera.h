#ifndef CAMERA_INCLUDED
#define CAMERA_INCLUDED

class Camera
{
public:
    static Camera CameraControl;

    Camera();

    float CameraX;
    float CameraY;

    void MoveCamera(float IncreaseX, float IncreaseY);
    void SetCamera(float X, float Y);
};

#endif // CAMERA_INCLUDED
