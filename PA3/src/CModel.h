#ifndef CMODEL_H
#define CMODEL_H

#include "global.h"

class Model
{
	public:
		Model();
		~Model();

		glm::mat4 Spin(float);
		glm::mat4 Orbit(glm::mat4, float);
		//glm::mat4 Translate( glm::mat4, glm::vec3 ); /* deprecated */

		/** Getters & Setters **/
		void SetOrbit(float, float);

	private:
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 mvp;

		float lat_radius;
		float long_radius;
		float vert_radius;
};

#endif

