#pragma once 

#include "glad/glad.h"
#include "Math.hpp"

#include <string>

namespace Graphics {
	void createGraphics();
	void destroyGraphics();
	
	class Texture {
	public:
		Texture();
		~Texture();

		void load(std::string filename);

		unsigned int getId();

		void set();

		std::string getName();

	private:
		std::string mName;
		GLuint mId;
	};
	
		
	class Shader {
	public:
		typedef unsigned int Location;

		void load(const char *vertCode, const char *fragCode);

		Location addMatrixInput(std::string name);
		void setMatrixInput(Location loc, math::Matrix4f mat);

		Location addTextureInput(std::string name);

		void addBufferInput(std::string name, unsigned int index);

		void set();

		void unload();

	private:
		GLuint shaderProgram;

		void printShaderInfoLog(GLuint obj);
		void printProgramInfoLog(GLuint obj);
		const char *getTypeName(GLenum type);
	};
	
	class SubMesh
	{
	public:
		enum Primitives
		{
			TRIANGLES = GL_TRIANGLES,
			LINES = GL_LINES
		};
		
		void beginLoad();
		
		void addBuffer(Graphics::Shader::Location loc, const float* data, unsigned int dataSize, unsigned int size);
		
		void endLoad(Primitives primitives, unsigned int count);
		
		void endLoadWithIndex(Primitives primitives, unsigned int count, const unsigned int* data);
		
		void draw();

		void unload();
		
	private:
		GLuint mId;
		Primitives mPrimitives;
		unsigned int mCount;
		bool mWithIndex;
	};
}
