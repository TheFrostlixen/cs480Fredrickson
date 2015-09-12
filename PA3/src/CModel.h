#ifndef CMODEL_H
#define CMODEL_H

#include "global.h"

class Model
{
	public:
		Model();
		~Model();

		void Orbit(glm::mat4, float, bool, float speed = 1.0f);
		void Spin(float);
		void SwitchSpinDirection();
		void SwitchSpinDirection(bool);
		bool ToggleSpin();
		void Scale(const glm::vec3 &scaleMat);

		/** Getters & Setters **/
		void SetOrbit(float, float);
		void SetSpinning(bool);

		glm::mat4 GetModel() { return model; }

		bool IsSpinning() { return isSpinning; }

	private:
		glm::mat4 model;

		float lat_radius;
		float long_radius;
		//float angleRotation;
		bool spinDirection;
		bool isSpinning;
		float angleTranslation;
		float angleRotation;
};

#endif
