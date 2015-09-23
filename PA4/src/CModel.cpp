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

int Model::LoadModel( std::string path )
{
    // This is what the data will be read in to
    string line = "";

    // Set up file IO ops
    ifstream fin(path.c_str());

    // Clear any file/stream flags
    fin.clear();

    vector<unsigned int> iVertices, iTextures, iNormals;
    vector<glm::vec3> tempVertices;
    vector<glm::vec2> tempTextures;
    vector<glm::vec3> tempNormals;

    string txName = "";

    while ( getline( fin, line, '\n' ) )
    {
        string firstChar;
        istringstream stream(line);

        stream >> firstChar;

        if (firstChar == "v")
        {
            glm::vec3 vertex;
            stream >> vertex.x >> vertex.y >> vertex.z;
            tempVertices.push_back(vertex);
        }
        // Texture
        else if (firstChar == "vt")
        {
            glm::vec2 texture;
            stream >> texture.x >> texture.y;
            tempTextures.push_back(texture);
        }
        // Normal
        else if (firstChar == "vn")
        {
            glm::vec3 normal;
            stream >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        }
        // Face
        else if (firstChar == "f")
        {
            string a, b, c = "";
            string read;
            stream >> a >> b >> c;

            vector<string> items;

            // parse the numbers in a
            istringstream ssA(a);
            for(string each; getline(ssA, each, '/'); items.push_back(each));

            // parse the numbers in b
            istringstream ssB(b);
            for(string each; getline(ssB, each, '/'); items.push_back(each));

            // parse the numbers in c
            istringstream ssC(c);
            for(string each; getline(ssC, each, '/'); items.push_back(each));

            // convert & push vertices
            iVertices.push_back( (unsigned)stoi(items[0]) );
            iVertices.push_back( (unsigned)stoi(items[3]) );
            iVertices.push_back( (unsigned)stoi(items[6]) );

            // convert & push texture coordinates
            if(items[1] != "")
                iTextures.push_back( (unsigned)stoi(items[1]) );
            if(items[4] != "")
                iTextures.push_back( (unsigned)stoi(items[4]) );
            if(items[7] != "")
                iTextures.push_back( (unsigned)stoi(items[7]) );

            // convert & push normals
            iNormals.push_back( (unsigned)stoi(items[2]) );
            iNormals.push_back( (unsigned)stoi(items[5]) );
            iNormals.push_back( (unsigned)stoi(items[8]) );
        }
        // Material
        else if (firstChar == "usemtl")
        {
            stream >> txName;
        }
    }

    /*
    cout << "Loaded Vertices: " << endl;
    for(unsigned int i = 0; i < tempVertices.size(); i++)
    {
        cout << tempVertices[i].x << " " << tempVertices[i].y << " " << tempVertices[i].z << endl;
    }
    cout << endl;

    cout << "Loaded Texture Coordinates: " << endl;
    for(unsigned int i = 0; i < tempTextures.size(); i++)
    {
        cout << tempTextures[i].x << " " << tempTextures[i].y << endl;;
    }
    cout << endl;

    cout << "Loaded Normals: " << endl;
    for(unsigned int i = 0; i < tempNormals.size(); i++)
    {
        cout << tempNormals[i].x << " " << tempNormals[i].y << " " << tempNormals[i].z << endl;
    }
    cout << endl;
    */

    // push back vertices to member variable
    for (unsigned int i = 0; i < iVertices.size(); i++)
    {
        unsigned int index = iVertices[i];
        glm::vec3 v = tempVertices[index-1];
        vertices.push_back(v);
    }

    // push back textures to member variable
    for (unsigned int i = 0; i < iTextures.size(); i++)
    {
        unsigned int index = iTextures[i];
        glm::vec2 coords = tempTextures[index-1];
        txPoints.push_back(coords);
    }

    // push back normals to member variable
    for (unsigned int i = 0; i < iNormals.size(); i++)
    {
        unsigned int index = iNormals[i];
        glm::vec3 norms = tempNormals[index-1];
        normals.push_back(norms);
    }

    return GetVertices().size();
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
