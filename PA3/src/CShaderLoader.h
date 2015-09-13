#ifndef CSHADERLOADER_H
#define CSHADERLOADER_H

#include "global.h"

#include <string>
#include <fstream>
#include <sstream>

class Shader
{
	public:
		Shader();
		~Shader();

		// Load and compile a shader program
		///  path: file path to the shader file
		///  sType: the type of shader being loaded
		///  return: success/failure flag
		bool Load( std::string path, GLuint sType );

		// Delete a shader program
		bool Delete();

		// Whether loading & compiling was successful
		bool IsLoaded()
		{
			return loaded;
		}

		// Returns shader type
		GLuint GetType()
		{
			return type;
		}

		// Returns shader id
		GLuint GetID()
		{
			return id;
		}
		
	private:
		GLuint id;
		GLuint type;
		bool loaded;
};

#endif

