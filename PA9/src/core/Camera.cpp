#include "Camera.h"
#include "GlutProgram.h"

using namespace glm;
using namespace std;

Camera::Camera(vec3 position, float speed)
{
    // Get game instance
    GlutProgram *game = GlutProgram::GetInstance();

    // Initialize variables
    direction = vec3(0, 0, 0);
    right     = vec3(0, 0, 0);
    up        = vec3(0, 1, 0);

    initialFOV       = 45.0f;
    curFOV           = initialFOV;
    this->speed      = speed;
    pitchSensitivity = 0.005f;
    yawSensitivity   = 0.005f;

    mouseX = game->GetScreenWidth() / 2;
    mouseY = game->GetScreenHeight() / 2;

    forward = false;

    inputEnabled = false;

    SetPosition(position);

}

Camera::~Camera()
{
}

void Camera::Update()
{
    if(!inputEnabled)
        return;

    projectionMatrix = mat4(1.0f);
    viewMatrix       = mat4(1.0f);

    // Grab the game instance
    GlutProgram *game = GlutProgram::GetInstance();

    // Hide the mouse
    glutSetCursor(GLUT_CURSOR_NONE);

    // If the mouse moved
    int mouseX = game->GetMousePosition().x;
    int mouseY = game->GetMousePosition().y;

    // Update angles
    horizontalAngle += yawSensitivity  * float((game->GetScreenWidth() / 2) - mouseX);
    verticalAngle   += pitchSensitivity* float((game->GetScreenHeight() / 2) - mouseY);

    // 1.55f radians is 89 degrees, which is a reasonable vertical constraint
    if(verticalAngle > 1.55f)
        verticalAngle = 1.55f;
    else if(verticalAngle < -1.55f)
        verticalAngle = -1.55f;

    // Set new direction by converting spherical coordinates to cartesian
    direction = vec3(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
            );

    // Calculate right vector
    right = vec3(
            sin(horizontalAngle - pi<float>() / 2),
            0,
            cos(horizontalAngle - pi<float>() / 2)
            );

    // Calculate up vector
    up = cross(right, direction);

    // Move forward if 'W' is pressed
    // Move backward if 'S' is pressed
    // Strafe left if 'D' is pressed
    // Strafe right if 'A' is pressed

    projectionMatrix = perspective(initialFOV, game->GetAspectRatio(), 0.1f, 1000.0f);
    viewMatrix       = lookAt(position, position + direction, up);

    // Reset mouse to center of the screen
    glutWarpPointer(game->GetScreenWidth()/2, game->GetScreenHeight()/2);

}

float Camera::GetPitchSensitivity()
{
    return pitchSensitivity;
}

float Camera::GetYawSensitivity()
{
    return yawSensitivity;
}

void Camera::SetPitchSensitivity(float newSens)
{
    pitchSensitivity = newSens;
}

void Camera::SetYawSensitivity(float newSens)
{
    yawSensitivity = newSens;
}

glm::mat4 Camera::GetMVP(glm::mat4 modelMatrix)
{
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    return mvpMatrix;
}
void Camera::EnableInput(bool enabled)
{
    inputEnabled = enabled;
}

void Camera::SetPosition(glm::vec3 position, float horizontalAngle, float verticalAngle)
{
    GlutProgram* game = GlutProgram::GetInstance();

    this->horizontalAngle  = horizontalAngle;
    this->verticalAngle    = verticalAngle;
    this->position         = position;

    // 1.55f radians is 89 degrees, which is a reasonable vertical constraint
    if(verticalAngle > 1.55f)
        verticalAngle = 1.55f;
    else if(verticalAngle < -1.55f)
        verticalAngle = -1.55f;

    // Set new direction by converting spherical coordinates to cartesian
    direction = vec3(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
            );

    // Calculate right vector
    right = vec3(
            sin(horizontalAngle - pi<float>() / 2),
            0,
            cos(horizontalAngle - pi<float>() / 2)
            );

    // Calculate up vector
    up = cross(right, direction);

    projectionMatrix = perspective(initialFOV, game->GetAspectRatio(), 0.1f, 1000.0f);
    viewMatrix       = lookAt(position, position + direction, up);
}

void Camera::LookAt(glm::vec3 position, glm::vec3 focusPoint, glm::vec3 up)
{
    this->position = position;
    this->viewMatrix = glm::lookAt(position, focusPoint, up);
}

