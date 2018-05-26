#ifndef GARUDA_ENGINE
#define GARUDA_ENGINE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "opengl32.lib")
#include "IO/Mouse.h"
#include "IO/Keyboard.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

class Engine
{
public:

	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static float GetDT();

	void CheckShaderErrors(GLuint shader, string type);
	GLuint BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void Err(string error);


	//constructor
	Engine();
	~Engine();

	bool Initialize(char* windowTitle);

	void Update();
	void BeginRender();
	void EndRender();
	void Tutup();
	GLFWwindow* GetWindow();
	GLuint program;
private:
	static GLFWwindow* window;

	static float dt;
	float lastTime;
};

#endif // !1