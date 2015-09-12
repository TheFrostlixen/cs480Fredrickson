#include "CModel.h"

Model::Model()
{
	lat_radius = 0.0f;
	long_radius = 0.0f;
	isSpinning = true;
	spinDirection = false;
	angleRotation = 0.0f;
	angleTranslation = 0.0f;
}

Model::~Model()
{
	lat_radius = 0.0f;
	long_radius = 0.0f;
	isSpinning = false;
	spinDirection = false;
}

void Model::Spin(float dt)
{
    // Check spinning flag
    if (isSpinning)
    {
        // Check which direction it's spinning
        if (spinDirection)
            angleRotation -= dt * M_PI/2;
        else
            angleRotation += dt * M_PI/2;
    }

    // Update the model matrix
    model = glm::rotate(model, 2*angleRotation, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Model::SwitchSpinDirection()
{
	spinDirection = !spinDirection;
}

void Model::SwitchSpinDirection( bool ccw )
{
	spinDirection = ccw;
}

bool Model::ToggleSpin()
{
	isSpinning = !isSpinning;
	return isSpinning;
}

void Model::Orbit( glm::mat4 origin, float dt, bool clockwise, float speed)
{
    if(clockwise)
        angleTranslation += dt * M_PI/2.0; // Move through 90 degrees a second
    else
        angleTranslation -= dt * M_PI/2.0; // Move through 90 degrees a second

	// Update the model matrix
	model = glm::translate( origin,
						    glm::vec3( lat_radius * sin(angleTranslation),
									   0.0f,
									   long_radius * cos(angleTranslation)
								     )
						   );
}

/** Getters & Setters **/
void Model::SetOrbit( float latitude, float longitude )
{
	lat_radius = latitude;
	long_radius = longitude;
}

void Model::SetSpinning( bool spin )
{
	isSpinning = spin;
}

void Model::Scale(const glm::vec3 &scaleMat)
{
    model = glm::scale(model, scaleMat);
}

