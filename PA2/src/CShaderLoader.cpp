#include "CShaderLoader.h"

// Default constructor, set up vars to default values
Shader::Shader()
{
	loaded = false;
	id = -1;
	type = -1;
}

// Default destructor, handled in Delete member function
Shader::~Shader()
{
	Delete();
}

bool Shader::Load( std::string path, GLuint sType )
{
	// Flag for shader compiled successfully
	GLint compiled = GL_FALSE;
	
	// Create a shader of the given type
	id = glCreateShader(sType);
	
	// Source of the shader; this is what will be read into
	std::string shader = "";
	
	// Set up file I/O ops
	std::ifstream fin(path.c_str());
	std::stringstream stream;
	
	// Clear any file/stream flags
	fin.clear();
	stream.flush();
	
	// Read file
	if ( fin.good() )
	{
		// Load input shader file
		stream << fin.rdbuf(); // read buffer into stream
		shader = stream.str(); // take in the string from stream
	}
	else
	{
		// Reading file failed somehow, print error message and quit
		printf( "File %s could not be read...\n", path.c_str() );
		return false;
	}
	
	// Close file stream
	fin.close();
	
	// Set shader source
	glShaderSource( id, 1, (const GLchar**)&shader, NULL );
	
	// Compile shader
	glCompileShader( id );
	glGetShaderiv( id, GL_COMPILE_STATUS, &compiled );
	
	// Check compilation status for failure
    if (compiled != GL_TRUE)
    {
        // Print an error message
        printf("Couldn't compile shader %d...\n", id);

        // Delete the shader
        glDeleteShader(id);

        return false;
    }

	// Shader is successfully loaded, finish setting vars and return success
    type = sType;
    loaded = true;

    return loaded;
}

bool Shader::Delete()
{
	// if the shader exists, it is allowed to delete
	if (loaded)
	{
		glDeleteShader(id);
		id = 0;
		loaded = false;
		
		return true;
	}
	// if the shader doesn't exist, return failure
	else
		return false;
}

