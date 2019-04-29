#pragma once

#include "Unity/IUnityGraphics.h"
#include <OpenGL/gl3.h>
#include <stddef.h>

struct IUnityInterfaces;


// Super-simple "graphics abstraction". This is nothing like how a proper platform abstraction layer would look like;
// all this does is a base interface for whatever our plugin sample needs. Which is only "draw some triangles"
// and "modify a texture" at this point.
//
// There are implementations of this base class for D3D9, D3D11, OpenGL etc.; see individual RenderAPI_* files.
class RenderAPI
{
public:
    RenderAPI(UnityGfxRenderer apiType);
    virtual ~RenderAPI() { }
    
    virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces);
    
    virtual bool GetUsesReverseZ() { return false; }
    
    virtual void DrawSimpleTriangles(const float worldMatrix[16], int triangleCount, const void* verticesFloat3Byte4);
    
private:
    void CreateResources();
    
private:
    UnityGfxRenderer m_APIType;
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_Program;
    GLuint m_VertexArray;
    GLuint m_VertexBuffer;
    int m_UniformWorldMatrix;
    int m_UniformProjMatrix;

};


// Create a graphics API implementation instance for the given API type.
RenderAPI* CreateRenderAPI(UnityGfxRenderer apiType);

