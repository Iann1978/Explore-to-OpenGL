using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Test : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        //int version = RenderPlugin.GetVersion();
        //Debug.Log("Version of RenderPlugin: " + version);


    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnGUI()
    {
        if (GUILayout.Button("GetVersion()"))
        {
            int version = RenderPlugin.GetVersion();
            Debug.Log("Version of RenderPlugin: " + version);
        }

        if (GUILayout.Button("GetRenderEventFunc"))
        {
            RenderPlugin.GetRenderEventFunc();
        }

        if (GUILayout.Button("IssuePluginEvent"))
        {

            GL.IssuePluginEvent(RenderPlugin.GetRenderEventFunc(), 1);
        }

    }
}
