#ifdef USE_OPENGL
#ifndef _GL_ASSETS_H
#define _GL_ASSETS_H
#include <vector>
#include <string>
#include <GL/glew.h>
using std::vector;
using std::string;

GLenum _glCheckError(const char* file, int line);
#ifdef _DEBUG
#define glCheckError() _glCheckError(__FILE__, __LINE__)
#else
#define glCheckError()
#endif

class CModelLoader
{

};

// a class of shader manager, for loading shaders, compile, link and use program for rendering
class CShaderGL
{
protected:
	GLuint m_programID = -1;
	vector<GLuint> m_shadersID;

public:
	CShaderGL();
	CShaderGL(string vertPath, string fragPath, string geometryPath = "");
	void addShaderFile(string path, GLenum shaderType);
	void addShaderSource(string& source, GLenum shaderType);
	void linkProgram();
	GLuint getProgram();

	// get, set uniform, return location
	GLint getUniformLocation(string uniformName);
	GLint getUniformBlockIndex(string uniformName);
	GLint setUniform4fv(string uniformName, const GLfloat* data);
	GLint setUniform4fv(string uniformName, GLsizei i, const GLfloat* data);
	GLint setUniform4fv(string uniformName, GLsizei i, GLsizei count, const GLfloat* data);
	GLint setUniformMat4fv(string uniformName, const GLfloat* data);
	GLint setUniformBlock(string uniformName,
		GLintptr offset, GLsizei size, const void* data);
	void use();
	virtual ~CShaderGL();
};

// a class of texture manager, for filling texture of reading from texture
class CTextureGL
{
protected:
	GLuint m_texture = -1;
	GLenum m_target = GL_TEXTURE_2D;
	GLenum m_aciveIndex = GL_TEXTURE0;

public:
	CTextureGL(GLenum target);
	GLuint getTexture();
	GLenum getTarget();
	GLenum getActiveIndex();
	void getTexImage(GLint level, GLenum format, GLenum type, void* pixels);
	GLenum active(GLenum aciveIndex); // < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS -1
	GLenum active(); // return the previous activeIndex
	void bind();
	virtual ~CTextureGL();
};

class CTexture2DGL : public CTextureGL
{
public:
	CTexture2DGL();
	void texImage2D(GLint level, GLint internalFormat,
		GLsizei width, GLsizei height, GLint border,
		GLenum format, GLenum type, const GLvoid* data);
	void texSubImage2D(GLint level, GLint xoffset, GLint yoffset,
		GLsizei width, GLsizei height,
		GLenum format, GLenum type, const GLvoid* data);
	virtual ~CTexture2DGL();
};

class CTexture3DGL :public CTextureGL
{
public:
	CTexture3DGL(GLenum target);
	void texImage3D(GLint level, GLint internalFormat,
		GLsizei width, GLsizei height, GLsizei depth,
		GLint border, GLenum format, GLenum type, const GLvoid* data);
	void texSubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
		GLsizei width, GLsizei height, GLsizei depth,
		GLenum format, GLenum type, const GLvoid* data);
	virtual ~CTexture3DGL();
};

class CTextureCubeGL : public CTextureGL
{
public:
	CTextureCubeGL(GLsizei width, GLsizei height,
		GLint internalFormat = GL_RGBA);
	void texImage2DI(GLenum i, GLint level, GLint internalFormat,
		GLsizei width, GLsizei height, GLint border,
		GLenum format, GLenum type, const GLvoid* data);
	virtual ~CTextureCubeGL();
};

#endif
#endif