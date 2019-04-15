using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class RenderPlugin : MonoBehaviour
{
    [DllImport("RenderPlugin")]
    public static extern int GetVersion();
}
