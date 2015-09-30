#include "CModel.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

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
	angleRotation = 0.0f;
	angleTranslation = 0.0f;
}

void Model::LoadModel( std::string path )
{
    Assimp::Importer importer;
    vector<GLuint> indices;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    if(scene)
    {
        const aiMesh* mesh = scene->mMeshes[0];

        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace& face = mesh->mFaces[i];
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        for(unsigned int i = 0; i < indices.size(); i++)
        {
            const aiVector3D* temp = &(mesh->mVertices[indices[i]]);
            Vertex v;
            v.position[0] = temp->x;
            v.position[1] = temp->y;
            v.position[2] = temp->z;

            v.color[0] = 0.0;
            v.color[0] = 0.0;
            v.color[0] = 0.0;

            vertices.push_back(v);
        }
    }
}

void Model::Orbit( glm::mat4 origin, float dt, bool ccw, float speed )
{
    if (ccw)
        angleTranslation += dt * M_PI/2.0; // Move through 90 degrees a second
    else
        angleTranslation -= dt * M_PI/2.0; // Move through 90 degrees a second

	// Update the model matrix
	model = glm::translate( origin,
						    glm::vec3( lat_radius * sin(angleTranslation * speed),
									   0.0f,
									   long_radius * cos(angleTranslation * speed)
								     )
						   );
}

void Model::Spin( float dt )
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

void Model::Scale( float scale )
{
    model = glm::scale( model, glm::vec3(scale,scale,scale) );
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

void Model::Draw()
{
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
}
