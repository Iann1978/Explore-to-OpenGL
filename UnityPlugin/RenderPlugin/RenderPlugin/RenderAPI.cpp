
#include "RenderAPI.h"
//#include "PlatformBase.h"

// OpenGL Core profile (desktop) or OpenGL ES (mobile) implementation of RenderAPI.
// Supports several flavors: Core, ES2, ES3
#include <assert.h>
#include <OpenGL/gl3.h>



enum VertexInputs
{
	kVertexInputPosition = 0,
	kVertexInputColor = 1
};




static const char *vertexSource =
R"SHADER(
#version 150
in highp vec3 pos;
in lowp vec4 color;

out lowp vec4 ocolor;

uniform highp mat4 worldMatrix;
uniform highp mat4 projMatrix;

void main()
{
    gl_Position = (projMatrix * worldMatrix) * vec4(pos,1);
    ocolor = color;
}
)SHADER";



static const char *fragmentSource =
R"SHADER(
#version 150
out lowp vec4 fragColor;
in lowp vec4 ocolor;

void main()
{
    fragColor = ocolor;
}
)SHADER";


static GLuint CreateShader(GLenum type, const char* sourceText)
{
	GLuint ret = glCreateShader(type);
	glShaderSource(ret, 1, &sourceText, NULL);
	glCompileShader(ret);
	return ret;
}


void RenderAPI::CreateResources()
{

    //m_VertexShader = CreateShader(GL_VERTEX_SHADER, kGlesVProgTextGLCore);
    //m_FragmentShader = CreateShader(GL_FRAGMENT_SHADER, kGlesFShaderTextGLCore);
    m_VertexShader = CreateShader(GL_VERTEX_SHADER, vertexSource);
    m_FragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentSource);
    

	// Link shaders into a program and find uniform locations
	m_Program = glCreateProgram();
	glBindAttribLocation(m_Program, kVertexInputPosition, "pos");
	glBindAttribLocation(m_Program, kVertexInputColor, "color");
	glAttachShader(m_Program, m_VertexShader);
	glAttachShader(m_Program, m_FragmentShader);
#	if SUPPORT_OPENGL_CORE
	if (m_APIType == kUnityGfxRendererOpenGLCore)
		glBindFragDataLocation(m_Program, 0, "fragColor");
#	endif // if SUPPORT_OPENGL_CORE
	glLinkProgram(m_Program);

	GLint status = 0;
	glGetProgramiv(m_Program, GL_LINK_STATUS, &status);
	assert(status == GL_TRUE);

	m_UniformWorldMatrix = glGetUniformLocation(m_Program, "worldMatrix");
	m_UniformProjMatrix = glGetUniformLocation(m_Program, "projMatrix");

	// Create vertex buffer
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 1024, NULL, GL_STREAM_DRAW);

	assert(glGetError() == GL_NO_ERROR);
}


RenderAPI::RenderAPI(UnityGfxRenderer apiType)
	: m_APIType(apiType)
{
}


void RenderAPI::ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces)
{
	if (type == kUnityGfxDeviceEventInitialize)
	{
		CreateResources();
	}
	else if (type == kUnityGfxDeviceEventShutdown)
	{
		//@TODO: release resources
	}
}


void RenderAPI::DrawSimpleTriangles(const float worldMatrix[16], int triangleCount, const void* verticesFloat3Byte4)
{
	// Set basic render state
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	// Tweak the projection matrix a bit to make it match what identity projection would do in D3D case.
	float projectionMatrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,2,0,
		0,0,-1,1,
	};

	// Setup shader program to use, and the matrices
	glUseProgram(m_Program);
	glUniformMatrix4fv(m_UniformWorldMatrix, 1, GL_FALSE, worldMatrix);
	glUniformMatrix4fv(m_UniformProjMatrix, 1, GL_FALSE, projectionMatrix);

	// Core profile needs VAOs, setup one
#	if SUPPORT_OPENGL_CORE
	if (m_APIType == kUnityGfxRendererOpenGLCore)
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
	}
#	endif // if SUPPORT_OPENGL_CORE

	// Bind a vertex buffer, and update data in it
	const int kVertexSize = 12 + 4;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, kVertexSize * triangleCount * 3, verticesFloat3Byte4);

	// Setup vertex layout
	glEnableVertexAttribArray(kVertexInputPosition);
	glVertexAttribPointer(kVertexInputPosition, 3, GL_FLOAT, GL_FALSE, kVertexSize, (char*)NULL + 0);
	glEnableVertexAttribArray(kVertexInputColor);
	glVertexAttribPointer(kVertexInputColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, kVertexSize, (char*)NULL + 12);

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, triangleCount * 3);

	// Cleanup VAO
#	if SUPPORT_OPENGL_CORE
	if (m_APIType == kUnityGfxRendererOpenGLCore)
	{
		glDeleteVertexArrays(1, &m_VertexArray);
	}
#	endif
}



