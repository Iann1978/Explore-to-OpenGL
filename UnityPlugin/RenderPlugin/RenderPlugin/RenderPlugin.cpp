#include "Unity/IUnityGraphics.h"
#include "Unity/IUnityInterface.h"
#include <stdio.h>
#include <OpenGL/gl3.h>

extern "C" int GetVersion() { return 10; }



extern "C" void    UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    int a = 0;
    int b = 0;

}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
    int a = 0;
    int b = 0;
}



static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
    //glCompileShader(0);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    int b = 0;
    printf("RenderPlugin: OnRenderEvent()\n");
}


extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
{
    printf("RenderPlugin: GetRenderEventFunc()\n");
    return OnRenderEvent;
}

