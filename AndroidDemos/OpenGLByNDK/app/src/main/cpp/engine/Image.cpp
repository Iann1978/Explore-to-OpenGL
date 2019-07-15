//
// Created by Iann on 2019/5/29.
//

#include "Image.h"
#include "Shader.h"

#include <EGL/egl.h>
#include <GLES3/gl32.h>



auto gVertexShader1 =
        "#version 300 es\n"
        "layout(location = 0) in vec4 vPosition;\n"
        "layout(location = 1) in vec2 input_uv;\n"
        "out vec2 uv;\n"
        "void main() {\n"
        "  gl_Position = vPosition;\n"
        "  uv = input_uv;\n"
        "}\n";

auto gFragmentShader1 =
        "#version 300 es\n"
        "precision mediump float;\n"
        "uniform sampler2D myTextureSampler;\n"
        "in vec2 uv;\n"
        "out vec4 outColor;\n"
        "void main() {\n"
        "    outColor = texture(myTextureSampler, uv);\n"
        "}\n";

Image::Image(const char* path, float x, float y, float w, float h)
{

    //this->status = 0.7 * (rand() %5)/5;
    this->status = 0;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    static const GLfloat g_vertex_buffer_data_image[] = {
            0.0f+0.1f, 0.5f+0.1f, -0.5f+0.1f, -0.5f+0.1f,
            0.5f+0.1f, -0.5f+0.1f
    };



    x = y = 0.0f;
    w = h = 0.5f;
    //texture = loadDDS("uvtemplate.DDS");
    //texture = loadDDS(path);
    //texture = loadDDS("1.dds");
    programID_image = Shader::createProgram(gVertexShader1, gFragmentShader1);
    textureID = glGetUniformLocation(programID_image, "myTextureSampler");
    //rectID = glGetUniformLocation(programID_image, "rect");
    //screenWidthID = glGetUniformLocation(programID_image, "screenWidth");
    //screenHeightID = glGetUniformLocation(programID_image, "screenHeight");
//    statusID = glGetUniformLocation(programID_image, "status");
//
    glGenBuffers(1, &vertexbuffer_image);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_image);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_image), g_vertex_buffer_data_image, GL_STATIC_DRAW);


    glGenBuffers(1, &uvbuffer_image);
    // Two UV coordinatesfor each vertex. They were created with Blender.
    static const GLfloat g_uv_buffer_data_image[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
    };
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data_image), g_uv_buffer_data_image, GL_STATIC_DRAW);
}


//Image::~Image()
//{
//    glDeleteBuffers(1, &uvbuffer_image);
//    glDeleteBuffers(1, &vertexbuffer_image);
//    glDeleteProgram(programID_image);
//    glDeleteTextures(1, &texture);
//}
//
//void Image::SetTexture(const char* path)
//{
//    if (texture)
//    {
//        glDeleteTextures(1, &texture);
//        texture = 0;
//    }
//
//    texture = loadDDS(path);
//}
//
//bool Image::RayCast(float x, float y)
//{
//    return  (x >= this->x && x <= (this->x + this->w) &&
//             y >= this->y && y <= (this->y + this->h));
//}
void Image::Render()
{
    static float grey;
    grey += 0.01f;
    if (grey > 1.0f) {
        grey = 0.0f;
    }
    glClearColor(grey, grey, grey, 1.0f);
    //checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    //checkGlError("glClear");

    glUseProgram(programID_image);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
//    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(textureID, 0);
//
//    glUniform4fv(rectID, 1, &x);
//
//    glUniform1f(screenWidthID, Screen::width);
//    glUniform1f(screenHeightID, Screen::height);
//    glUniform1f(statusID, status);
//
//
//    //glUniform4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//
//    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_image);
    glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size : U+V => 2
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 12*3 indices starting at 0 -> 12 triangles
//
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
//
}
//
//void Image::Update()
//{
//    if (Input::GetMouseButtonUp(Input::LeftButton) && RayCast(Input::mousePosX, Input::mousePosY))
//    {
//        //printf("click a image.\n");
//        if (onClick)
//        {
//            onClick();
//        }
//    }
//}