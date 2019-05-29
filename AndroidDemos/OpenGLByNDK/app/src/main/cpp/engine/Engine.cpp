//
// Created by Iann on 2019/5/28.
//

#include "Engine.h"
#include "Shader.h"
#include "Image.h"
#include <android/log.h>

#include <jni.h>
#include <string>
#include <jni.h>
#include <android/log.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/quaternion.hpp"
#include "../glm/gtc/matrix_transform.hpp"

void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
                                                    = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}


auto gVertexShader =
        "#version 300 es\n"
        "layout(location = 0) in vec4 vPosition;\n"
        "void main() {\n"
        "  gl_Position = vPosition;\n"
        "}\n";

auto gFragmentShader =
        "#version 300 es\n"
        "precision mediump float;\n"
        "out vec4 outColor;\n"
        "void main() {\n"
        "    outColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
        "}\n";



GLuint gProgram;
GLuint gvPositionHandle;

bool setupGraphics(int w, int h) {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = Shader::createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
         gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
                                      0.5f, -0.5f };

void renderFrame() {
    static float grey;
    grey += 0.01f;
    if (grey > 1.0f) {
        grey = 0.0f;
    }
    glClearColor(grey, grey, grey, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
}

Engine::Engine()
{

}
Image *image;
void Engine::init(int w, int h)
{

    glm::vec3 eye(0,0,0);
    glm::vec3 center(0,-3,-2);
    glm::vec3 wantup(0,1,0);
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    front = glm::normalize(center - eye);
    right = glm::cross(front, wantup);
    up = glm::cross(right, front);
    center = eye + front;

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(75.0f), 1.0f * 4 / 3, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 viewMatrix = glm::lookAt(eye, center, up);

    image = new Image("", 0,0,100,100);
    setupGraphics(w, h);
}

void Engine::RenderOneFrame()
{
    image->Render();
    //renderFrame();
}