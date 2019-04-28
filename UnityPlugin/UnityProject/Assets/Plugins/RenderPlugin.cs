using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class RenderPlugin : MonoBehaviour
{
    [DllImport("RenderPlugin")]
    public static extern int GetVersion();

    [DllImport("RenderPlugin")]
    public static extern IntPtr GetRenderEventFunc();
}
