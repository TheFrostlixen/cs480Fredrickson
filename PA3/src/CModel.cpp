#include "CModel.h"

Model::Model()
{
	lat_radius = 9.0f;
}

Model::~Model()
{
}



glm::mat4 Model::Orbit( glm::mat4 view, float theta )
{
	return glm::translate( view,
						   glm::vec3( lat_radius * sin(theta),
									  0.0f,
									  long_radius * cos(theta)
								    )
						 );
}

/** Getters & Setters **/
void Model::SetOrbit( float latitude, float longitude )
{
	lat_radius = latitude;
	long_radius = longitude;
}


