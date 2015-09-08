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
		
		bool Load(std::string path, GLuint sType);
		bool Delete();
		bool IsLoaded();
		GLuint GetType();
		GLuint GetID();
		
	private:
		GLuint id;
		GLuint type;
		bool loaded;
};
#endif
