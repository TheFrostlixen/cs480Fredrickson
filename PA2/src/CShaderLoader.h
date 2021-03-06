#ifndef CSHADERLOADER_H
#define CSHADERLOADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
	public:
		Shader();
		~Shader();

		// load and compile a shader program
		//  returns success/failure flag
		bool Load(std::string path, GLuint sType);

		// delete a shader program
		bool Delete();

		// whether loading & compiling was successful
		bool IsLoaded()
		{
			return loaded;
		}

		// return shader type
		GLuint GetType()
		{
			return type;
		}

		// return shader id
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

