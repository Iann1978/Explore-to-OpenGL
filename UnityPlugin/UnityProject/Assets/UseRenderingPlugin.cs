using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;


public class UseRenderingPlugin : MonoBehaviour
{
	
	[DllImport ("RenderPlugin")]
	private static extern void SetTimeFromUnity(float t);

    [DllImport("RenderPlugin")]
    private static extern int GetDllVersion();

    [DllImport("RenderPlugin")]
    private static extern int CreateCustomWindow();


    [DllImport("RenderPlugin")]
    private static extern int DestroyCustomWindow();




    [DllImport ("RenderPlugin")]
	private static extern void SetTextureFromUnity(System.IntPtr texture, int w, int h);


	[DllImport ("RenderPlugin")]
	private static extern void SetMeshBuffersFromUnity (IntPtr vertexBuffer, int vertexCount, IntPtr sourceVertices, IntPtr sourceNormals, IntPtr sourceUVs);


	[DllImport("RenderPlugin")]
	private static extern IntPtr GetRenderEventFunc();


    public delegate void FunctionLogout(string str);
    [DllImport("RenderPlugin")]
    private static extern int SetLogoutFunction(FunctionLogout logfun);
    [DllImport("RenderPlugin")]
    private static extern int TestLog();
    FunctionLogout Logout;

    IEnumerator Start()
	{
        int version = GetDllVersion();
        Debug.Log("dll version:" + version);
        CreateTextureAndPassToPlugin();
		SendMeshBuffersToPlugin();
		yield return StartCoroutine("CallPluginAtEndOfFrames");
	}

	private void CreateTextureAndPassToPlugin()
	{
		// Create a texture
		Texture2D tex = new Texture2D(256,256,TextureFormat.ARGB32,false);
		// Set point filtering just so we can see the pixels clearly
		tex.filterMode = FilterMode.Point;
		// Call Apply() so it's actually uploaded to the GPU
		tex.Apply();

		// Set texture onto our material
		GetComponent<Renderer>().material.mainTexture = tex;

		// Pass texture pointer to the plugin
		SetTextureFromUnity (tex.GetNativeTexturePtr(), tex.width, tex.height);
	}

	private void SendMeshBuffersToPlugin ()
	{
		var filter = GetComponent<MeshFilter> ();
		var mesh = filter.mesh;
		// The plugin will want to modify the vertex buffer -- on many platforms
		// for that to work we have to mark mesh as "dynamic" (which makes the buffers CPU writable --
		// by default they are immutable and only GPU-readable).
		mesh.MarkDynamic ();

		// However, mesh being dynamic also means that the CPU on most platforms can not
		// read from the vertex buffer. Our plugin also wants original mesh data,
		// so let's pass it as pointers to regular C# arrays.
		// This bit shows how to pass array pointers to native plugins without doing an expensive
		// copy: you have to get a GCHandle, and get raw address of that.
		var vertices = mesh.vertices;
		var normals = mesh.normals;
		var uvs = mesh.uv;
		GCHandle gcVertices = GCHandle.Alloc (vertices, GCHandleType.Pinned);
		GCHandle gcNormals = GCHandle.Alloc (normals, GCHandleType.Pinned);
		GCHandle gcUV = GCHandle.Alloc (uvs, GCHandleType.Pinned);

		SetMeshBuffersFromUnity (mesh.GetNativeVertexBufferPtr (0), mesh.vertexCount, gcVertices.AddrOfPinnedObject (), gcNormals.AddrOfPinnedObject (), gcUV.AddrOfPinnedObject ());

		gcVertices.Free ();
		gcNormals.Free ();
		gcUV.Free ();
	}


	private IEnumerator CallPluginAtEndOfFrames()
	{
		while (true) {
			// Wait until all frame rendering is done
			yield return new WaitForEndOfFrame();

			// Set time for the plugin
			SetTimeFromUnity (Time.timeSinceLevelLoad);

			// Issue a plugin event with arbitrary integer identifier.
			// The plugin can distinguish between different
			// things it needs to do based on this ID.
			// For our simple plugin, it does not matter which ID we pass here.
			GL.IssuePluginEvent(GetRenderEventFunc(), 1);
		}
	}



    private void OnGUI()
    {
        if (GUILayout.Button("CreateCustomWindow"))
        {
            int a = CreateCustomWindow();
            //Debug.Log("a=" + a);
        }

        if (GUILayout.Button("DestroyCustomWindow"))
        {
            int a = DestroyCustomWindow();
            //Debug.Log("a=" + a);
        }
    

        if (GUILayout.Button("SetLogoutFunction"))
        {
            Logout = (string str) => { Debug.Log(str); };
            SetLogoutFunction(Logout);
            TestLog();
            //Debug.Log("a=" + a);
        }

        if (GUILayout.Button("TestLog"))
        {
       
            TestLog();
            //Debug.Log("a=" + a);
        }


    }
}
