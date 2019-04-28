#include "Unity/IUnityGraphics.h"

extern "C" int GetVersion() { return 5; }


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
