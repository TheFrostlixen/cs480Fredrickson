#include "CModel.h"

Model::Model()
{
	lat_radius = 0.0f;
	long_radius = 0.0f;
	isSpinning = true;
	spinDirection = false;
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
	// Rotation
	static float angleRotation = 0.0;

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
	spinDirection = dir;
}

bool Model::ToggleSpin()
{
	isSpinning = !isSpinning;
	return isSpinning;
}

void Model::Orbit( glm::mat4 origin, float dt )
{
	// Translation angle
	static float angleTranslation = 0.0f;
	
	// Move through 90 degrees a second
	angleTranslation += dt * M_PI/2.0;

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

