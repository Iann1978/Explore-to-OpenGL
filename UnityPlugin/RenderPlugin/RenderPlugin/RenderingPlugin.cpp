// Example low level rendering Unity plugin

#include "PlatformBase.h"
#include "RenderAPI.h"

#include <assert.h>
#include <math.h>
#include <vector>

extern "C" int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetDllVersion()
{
    return 12;
}
// --------------------------------------------------------------------------
// SetTimeFromUnity, an example function we export which is called by one of the scripts.

static float g_Time;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetTimeFromUnity (float t) { g_Time = t; }



RenderAPI* CreateRenderAPI(UnityGfxRenderer apiType)
{
    
    
    if (apiType == kUnityGfxRendererOpenGLCore || apiType == kUnityGfxRendererOpenGLES20 || apiType == kUnityGfxRendererOpenGLES30)
    {
        extern RenderAPI* CreateRenderAPI_OpenGLCoreES(UnityGfxRenderer apiType);
        return CreateRenderAPI_OpenGLCoreES(apiType);
    }
    
    // Unknown or unsupported graphics API
    return NULL;
}

// --------------------------------------------------------------------------
// SetTextureFromUnity, an example function we export which is called by one of the scripts.

static void* g_TextureHandle = NULL;
static int   g_TextureWidth  = 0;
static int   g_TextureHeight = 0;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetTextureFromUnity(void* textureHandle, int w, int h)
{
	// A script calls this at initialization time; just remember the texture pointer here.
	// Will update texture pixels each frame from the plugin rendering event (texture update
	// needs to happen on the rendering thread).
	g_TextureHandle = textureHandle;
	g_TextureWidth = w;
	g_TextureHeight = h;
}


// --------------------------------------------------------------------------
// SetMeshBuffersFromUnity, an example function we export which is called by one of the scripts.

static void* g_VertexBufferHandle = NULL;
static int g_VertexBufferVertexCount;

struct MeshVertex
{
	float pos[3];
	float normal[3];
	float uv[2];
};
static std::vector<MeshVertex> g_VertexSource;


extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMeshBuffersFromUnity(void* vertexBufferHandle, int vertexCount, float* sourceVertices, float* sourceNormals, float* sourceUV)
{
	// A script calls this at initialization time; just remember the pointer here.
	// Will update buffer data each frame from the plugin rendering event (buffer update
	// needs to happen on the rendering thread).
	g_VertexBufferHandle = vertexBufferHandle;
	g_VertexBufferVertexCount = vertexCount;

	// The script also passes original source mesh data. The reason is that the vertex buffer we'll be modifying
	// will be marked as "dynamic", and on many platforms this means we can only write into it, but not read its previous
	// contents. In this example we're not creating meshes from scratch, but are just altering original mesh data --
	// so remember it. The script just passes pointers to regular C# array contents.
	g_VertexSource.resize(vertexCount);
	for (int i = 0; i < vertexCount; ++i)
	{
		MeshVertex& v = g_VertexSource[i];
		v.pos[0] = sourceVertices[0];
		v.pos[1] = sourceVertices[1];
		v.pos[2] = sourceVertices[2];
		v.normal[0] = sourceNormals[0];
		v.normal[1] = sourceNormals[1];
		v.normal[2] = sourceNormals[2];
		v.uv[0] = sourceUV[0];
		v.uv[1] = sourceUV[1];
		sourceVertices += 3;
		sourceNormals += 3;
		sourceUV += 2;
	}
}



// --------------------------------------------------------------------------
// UnitySetInterfaces

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);

static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;

extern "C" void	UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
	s_UnityInterfaces = unityInterfaces;
	s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);
	
#if SUPPORT_VULKAN
	if (s_Graphics->GetRenderer() == kUnityGfxRendererNull)
	{
		extern void RenderAPI_Vulkan_OnPluginLoad(IUnityInterfaces*);
		RenderAPI_Vulkan_OnPluginLoad(unityInterfaces);
	}
#endif // SUPPORT_VULKAN

	// Run OnGraphicsDeviceEvent(initialize) manually on plugin load
	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
}

#if UNITY_WEBGL
typedef void	(UNITY_INTERFACE_API * PluginLoadFunc)(IUnityInterfaces* unityInterfaces);
typedef void	(UNITY_INTERFACE_API * PluginUnloadFunc)();

extern "C" void	UnityRegisterRenderingPlugin(PluginLoadFunc loadPlugin, PluginUnloadFunc unloadPlugin);

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API RegisterPlugin()
{
	UnityRegisterRenderingPlugin(UnityPluginLoad, UnityPluginUnload);
}
#endif

// --------------------------------------------------------------------------
// GraphicsDeviceEvent


static RenderAPI* s_CurrentAPI = NULL;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;


static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	// Create graphics API implementation upon initialization
	if (eventType == kUnityGfxDeviceEventInitialize)
	{
		assert(s_CurrentAPI == NULL);
		s_DeviceType = s_Graphics->GetRenderer();
		s_CurrentAPI = CreateRenderAPI(s_DeviceType);
	}

	// Let the implementation process the device related events
	if (s_CurrentAPI)
	{
		s_CurrentAPI->ProcessDeviceEvent(eventType, s_UnityInterfaces);
	}

	// Cleanup graphics API implementation upon shutdown
	if (eventType == kUnityGfxDeviceEventShutdown)
	{
		delete s_CurrentAPI;
		s_CurrentAPI = NULL;
		s_DeviceType = kUnityGfxRendererNull;
	}
}



// --------------------------------------------------------------------------
// OnRenderEvent
// This will be called for GL.IssuePluginEvent script calls; eventID will
// be the integer passed to IssuePluginEvent. In this example, we just ignore
// that value.


static void DrawColoredTriangle()
{
	// Draw a colored triangle. Note that colors will come out differently
	// in D3D and OpenGL, for example, since they expect color bytes
	// in different ordering.
	struct MyVertex
	{
		float x, y, z;
		unsigned int color;
	};
	MyVertex verts[3] =
	{
		{ -0.5f, -0.25f,  0, 0xFFff0000 },
		{ 0.5f, -0.25f,  0, 0xFF00ff00 },
		{ 0,     0.5f ,  0, 0xFF0000ff },
	};

	// Transformation matrix: rotate around Z axis based on time.
	float phi = g_Time; // time set externally from Unity script
	float cosPhi = cosf(phi);
	float sinPhi = sinf(phi);
	float depth = 0.7f;
	float finalDepth = s_CurrentAPI->GetUsesReverseZ() ? 1.0f - depth : depth;
	float worldMatrix[16] = {
		cosPhi,-sinPhi,0,0,
		sinPhi,cosPhi,0,0,
		0,0,1,0,
		0,0,finalDepth,1,
	};

	s_CurrentAPI->DrawSimpleTriangles(worldMatrix, 1, verts);
}



static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	// Unknown / unsupported graphics device type? Do nothing
	if (s_CurrentAPI == NULL)
		return;

	DrawColoredTriangle();
	//ModifyTexturePixels();
	//ModifyVertexBuffer();
}


// --------------------------------------------------------------------------
// GetRenderEventFunc, an example function we export which is used to get a rendering event callback function.

extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
{
	return OnRenderEvent;
}

