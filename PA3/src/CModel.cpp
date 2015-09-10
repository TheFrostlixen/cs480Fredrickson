#include "CModel.h"

Model::Model()
{
	lat_radius = 0.0f;
	long_radius = 0.0f;
}

Model::~Model()
{
	lat_radius = 0.0f;
	long_radius = 0.0f;
	model = NULL;
}

glm::mat4 Model::Spin()
{
	//total time
	static float angleRotation = 0.0; // rotation
	float dt = getDT();// if you have anything moving, use dt.

	// check spinning flag
	if (isSpinning)
	{
		// check which direction it's spinning
		if (spinDirection)
			angleRotation -= dt * M_PI/2;
		else
			angleRotation += dt * M_PI/2;
	}
	// update the model matrix
	model = glm::rotate(model, 2*angleRotation, glm::vec3(0.0f, 1.0f, 0.0f));
	return model;
}

void Model::SwitchSpin()
{
	spinDirection = !spinDirection;
}

glm::mat4 Model::Orbit( glm::mat4 view, float theta )
{
	model = glm::translate( view,
						    glm::vec3( lat_radius * sin(theta),
									   0.0f,
									   long_radius * cos(theta)
								     )
						   );
	return model;
}

/** Getters & Setters **/
void Model::SetOrbit( float latitude, float longitude )
{
	lat_radius = latitude;
	long_radius = longitude;
}
