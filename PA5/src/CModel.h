#ifndef CMODEL_H
#define CMODEL_H

#include "global.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/** Data types **/
struct Vertex
{
    GLfloat position[3];
    GLfloat color[3];
};

class Model
{
	public:
		Model();
		~Model();

		void Draw();

        void LoadModel( std::string path );

		// Orbit around a given staring point
		///  origin: matrix origin to translate around
		///  dt: delta time, calculate angle of orbit
		///  clockwise: which direction the object is rotating around
		///  speed: orbiting speed multiplier (defaulted to 1)
		void Orbit( glm::mat4 origin, float dt, bool clockwise, float speed = 1.0f );

		// Model spin around the Y-axis
		///  dt: delta time, calculate angle of spin
		void Spin( float dt );

		// Switch the direction of spin
		void SwitchSpinDirection();

		// Switch the direcion of spin to clockwise(true) or counter-clockwise(false)
		void SwitchSpinDirection( bool clockwise );

		// Toggle whether the object is spinning
		bool ToggleSpin();

		// Scale the object to a uniform size
		void Scale( float scale );

		/** Getters & Setters **/
		// Set the orbit for the object
		///  latitude: orbit around the latitudinal axis
		///  longitude: orbit around the longitudinal axis
		void SetOrbit( float latitude, float longitude );

		// Set whether the object is spinning
		void SetSpinning(bool);

		// Return the model associated with the object
		glm::mat4 GetModel() { return model; }

		// Returns whether the object should be spinning
		bool IsSpinning() { return isSpinning; }

        // Returns a string denoting spin direction
        std::string GetSpinDirection() { return (spinDirection) ? "clockwise" : "counterclockwise"; };

        // Return the vertices of the model loaded
        std::vector<Vertex> GetVertices() { return vertices; }

	private:
		glm::mat4 model;

		float lat_radius;
		float long_radius;

		bool spinDirection; /// true=clockwise, false=counter-clockwise
		bool isSpinning;

		float angleTranslation;
		float angleRotation;

        std::vector<Vertex> vertices;
};

#endif
