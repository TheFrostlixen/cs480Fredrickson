#ifndef CMODEL_H
#define CMODEL_H

#include "global.h"

class Model
{
	public:
		Model();
		~Model();

		glm::mat4 Orbit(glm::mat4, float);
		glm::mat4 Spin();
		void SwitchSpin();

		/** Getters & Setters **/
		void SetOrbit(float, float);
		
		glm::mat4 GetModel() { return model; }
		void SetModel( glm::mat4 m ) { model = m; }

	private:
		glm::mat4 model;

		float lat_radius;
		float long_radius;
		//float angleRotation;
		bool spinDirection;
		bool isSpinning;
};

#endif
