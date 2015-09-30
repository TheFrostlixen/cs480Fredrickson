# Assimp Model Loading

## Authors
Matthew Berger and Matt Fredrickson.

## Objective
In this project, my partner and I had to utilize assimp to import a model and display it on the screen.

## Extra Credit
Since textures were not strictly required for this class, we used the values of the vertices for color, resulting in some interesting color for the model overall.

## Code

The model that we decided to load in was a model of a house. In the LoadModel function of our Model class, we load a model using Assimp.

First we create the importer and load the file into a scene object:

    Assimp::Importer importer;
    vector<GLuint> indices;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

Then we check if the scene contains any data and then the first mesh is parsed face by face:

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

Finally we go through all of the indices and create a vertex to push onto the stack by grabbing data from the mesh offset by the value stored in the indices array at a particular value:

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

## Notes
This implementation only allows the first mesh in the scene to be loaded, but for our purposes this is fine. We just have to ensure a single mesh per object file and we can always change this in future implementations.
