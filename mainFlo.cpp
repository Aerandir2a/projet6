#include<cstdio>
#include<iostream>
#ifdef _WIN32
	#include <windows.h>
#endif

#include <SDL.h>
#include "gc_3d_defs.hpp"
//#include "header/shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "header/stb_image.h"
#include "header/buffer.hpp"
#include "header/controls.hpp"
#include "header/camera.hpp"

#include "dep/imgui/imgui.h"
#include "dep/imgui/backends/imgui_impl_opengl3.h"
#include "dep/imgui/backends/imgui_impl_sdl.h"

using namespace GC_3D;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_Window* win = SDL_CreateWindow("Moteur",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024,
		768,
		windowFlags);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	SDL_GLContext context = SDL_GL_CreateContext(win);
	SDL_GL_MakeCurrent(win, context);

	//Imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	ImGui_ImplSDL2_InitForOpenGL(win, context);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();

	auto prevTime = Clock::now();

	//Initialization Glew
	glewInit();
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);

	//GLuint programID = LoadShaders("D:/LapendryFlorian/Projet_Moteur/Shader/SimpleVertexShader.vertexshader", "D:/LapendryFlorian/Projet_Moteur/Shader/SimpleFragmentShader.fragmentshader");
	//GLuint programID = LoadShaders("E:/G.TECH3/Project/CMake/Projet_Moteur/Shader/SimpleVertexShader.vertexshader", "E:/G.TECH3/Project/CMake/Projet_Moteur/Shader/SimpleFragmentShader.fragmentshader");
	const char* imgPath = "D:/LapendryFlorian/Projet_Moteur/Sprite/woodplank.png";
	//const char* imgPath = "E:/G.TECH3/Project/CMake/Projet_Moteur/Sprite/woodplank.png";

	int xwidth = 1;
	int yheight = 1;
	int nbit = 8;
	unsigned char* imgdata = stbi_load(imgPath, &xwidth, &yheight, &nbit, 3);

	GLuint idontknow;
	glGenTextures(1, &idontknow);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, idontknow);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xwidth, yheight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);

	glGenerateMipmap(GL_TEXTURE_2D);

	//Background color
	glClearColor(0.0, 0.0, 0.2, 0.1);

	//Interaction avec la souris
	int MousePosX = 0;
	int MousePosY = 0;
	bool focus = true;
	bool mouseClicRight = false;

	//Variables pour calcule des ms/frame
	int nbFrames = 0;
	double msFrames = 0;
	auto lastTime = Clock::now();

	if (win != nullptr) {
		SDL_WarpMouseInWindow(win, 1024 / 2, 768 / 2); 
		//computeMatricesFromInputs(curDirs, MousePosX, MousePosY);
	}

	startPosCamera();

	Camera* camera = new Camera();
	Buffer* Vbuffer = new Buffer();
	Buffer* Cbuffer = new Buffer();

	bool appRunning = true;
	while (appRunning)
	{
		Dirs curDirs;
		SDL_Event curEvent;
		while (SDL_PollEvent(&curEvent))
		{
			if (curEvent.type == SDL_QUIT || curEvent.key.keysym.sym == SDLK_ESCAPE) {
				return 0;
			}

			if (curEvent.type == SDL_WINDOWEVENT)
			{
				if (curEvent.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
				{
					focus = true;
				}
				if (curEvent.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				{
					focus = false;
				}
			}

			if (curEvent.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&MousePosX, &MousePosY);
				//computeMatricesFromInputs(MousePosX, MousePosY);
			}

			if (curEvent.type == SDL_MOUSEBUTTONDOWN) {
				if (curEvent.button.button == SDL_BUTTON_RIGHT) {
					SDL_WarpMouseInWindow(win, 1024 / 2, 768 / 2);
					mouseClicRight = true;
				}
			}
			if (curEvent.type == SDL_MOUSEBUTTONUP) {
				if (curEvent.button.button == SDL_BUTTON_RIGHT) {
					mouseClicRight = false;
				}
			}
			if (curEvent.type == SDL_MOUSEWHEEL) {
				if (curEvent.wheel.preciseY > 0) {
					curDirs.front = 1;
				}
				if (curEvent.wheel.preciseY < 0) {
					curDirs.back = 1;
				}
			}
			if (curEvent.type == SDL_KEYDOWN)
			{

				if (curEvent.key.keysym.sym == SDLK_SPACE) {
					SDL_WarpMouseInWindow(win, 1024 / 2, 768 / 2);
				}
				if (curEvent.key.keysym.sym == SDLK_d) {
					//printf("RIGHT!");
					curDirs.right = 1;
				}
				if (curEvent.key.keysym.sym == SDLK_q) {
					//printf("LEFT!");
					curDirs.left = 1;
				}
				if (curEvent.key.keysym.sym == SDLK_z) {
					curDirs.up = 1;
				}
				if (curEvent.key.keysym.sym == SDLK_s) {
					curDirs.down = 1;
				}
			}

			ImGui_ImplSDL2_ProcessEvent(&curEvent);
			if (!io.WantCaptureMouse)
			{
				//use mouse events not already used by ImGui
			}
			if (!io.WantCaptureKeyboard)
			{
				//use keyboard events not already used by ImGui
			}
		}

		glUseProgram(programID);

		//CAMERA
		camera->CreateCamera(win, programID, curDirs, MousePosX, MousePosY, mouseClicRight);
		/*glm::mat4 ViewMatrix = getViewMatrix();
		if (mouseClicRight) {
			SDL_WarpMouseInWindow(win, 1024 / 2, 768 / 2);
			iPosMouse(MousePosX, MousePosY);
		}
		moveCamera(curDirs);
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Get a handle for our "MVP" uniform
		// Only during the initialisation
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		// Send our transformation to the currently bound shader, in the "MVP" uniform
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		static const GLfloat g_vertex_buffer_data[] = {
			-1.0, -1.0, 1.0,  -1.0, 1.0, 1.0,  1.0, 1.0, 1.0, // Front
			1.0, 1.0, 1.0,  1.0, -1.0, 1.0,  -1.0, -1.0, 1.0,

			1.0, -1.0, 1.0,  1.0, 1.0, 1.0,  1.0, 1.0, -1.0, //Right
			1.0, 1.0, -1.0,  1.0, -1.0, -1.0,  1.0, -1.0, 1.0,

			1.0, -1.0, -1.0,  1.0, 1.0, -1.0,  -1.0, 1.0, -1.0, // Back
			-1.0, 1.0, -1.0,  -1.0, -1.0, -1.0,  1.0, -1.0, -1.0,

			-1.0, -1.0, -1.0,  -1.0, 1.0, -1.0,  -1.0, 1.0, 1.0, //Left
			-1.0, 1.0, 1.0,  -1.0, -1.0, 1.0,  -1.0, -1.0, -1.0,

			-1.0, 1.0, 1.0,  -1.0, 1.0, -1.0,  1.0, 1.0, -1.0, //Up
			1.0, 1.0, -1.0,  1.0, 1.0, 1.0, -1.0, 1.0, 1.0,

			-1.0, -1.0, 1.0,  -1.0, -1.0, -1.0,  1.0, -1.0, -1.0, //Down
			1.0, -1.0, -1.0,  1.0, -1.0, 1.0, -1.0, -1.0, 1.0,

		};

		static const GLfloat g_color_buffer_data[] = {
			0.583f,  0.771f,  0.014f,
			0.609f,  0.115f,  0.436f,
			0.327f,  0.483f,  0.844f,
			0.822f,  0.569f,  0.201f,
			0.435f,  0.602f,  0.223f,
			0.310f,  0.747f,  0.185f,
			0.597f,  0.770f,  0.761f,
			0.559f,  0.436f,  0.730f,
			0.359f,  0.583f,  0.152f,
			0.483f,  0.596f,  0.789f,
			0.559f,  0.861f,  0.639f,
			0.195f,  0.548f,  0.859f,
			0.014f,  0.184f,  0.576f,
			0.771f,  0.328f,  0.970f,
			0.406f,  0.615f,  0.116f,
			0.676f,  0.977f,  0.133f,
			0.971f,  0.572f,  0.833f,
			0.140f,  0.616f,  0.489f,
			0.997f,  0.513f,  0.064f,
			0.945f,  0.719f,  0.592f,
			0.543f,  0.021f,  0.978f,
			0.279f,  0.317f,  0.505f,
			0.167f,  0.620f,  0.077f,
			0.347f,  0.857f,  0.137f,
			0.055f,  0.953f,  0.042f,
			0.714f,  0.505f,  0.345f,
			0.783f,  0.290f,  0.734f,
			0.722f,  0.645f,  0.174f,
			0.302f,  0.455f,  0.848f,
			0.225f,  0.587f,  0.040f,
			0.517f,  0.713f,  0.338f,
			0.053f,  0.959f,  0.120f,
			0.393f,  0.621f,  0.362f,
			0.673f,  0.211f,  0.457f,
			0.820f,  0.883f,  0.371f,
			0.982f,  0.099f,  0.879f
		};

		static const GLfloat g_uv_buffer_data[] = {
			0.0, 1.0,  0.0, 0.0,  1.0, 0.0, // Front
			1.0, 0.0,  1.0, 1.0,  0.0, 1.0,

			0.0, 1.0,  0.0, 0.0,  1.0, 0.0, // Right
			1.0, 0.0,  1.0, 1.0,  0.0, 1.0,

			0.0, 1.0,  0.0, 0.0,  1.0, 0.0, // Back
			1.0, 0.0,  1.0, 1.0,  0.0, 1.0,

			0.0, 1.0,  0.0, 0.0,  1.0, 0.0, // Left
			1.0, 0.0,  1.0, 1.0,  0.0, 1.0,
			
			0.0, 1.0,  0.0, 0.0,  1.0, 0.0, // Up
			1.0, 0.0,  1.0, 1.0,  0.0, 1.0,

			0.0, 1.0,  0.0, 0.0,  1.0, 0.0, // Down
			1.0, 0.0,  1.0, 1.0,  0.0, 1.0,
		};

		auto curTime = Clock::now();
		Duration elapsedSeconds = curTime - prevTime;

		//ms lisser
		Duration deltaTime = curTime - lastTime;
		nbFrames++;

		//Render Loop
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(win);

		ImGui::NewFrame();

		// Draw some widgets
		
		//Calcule ms/frame
		float const curSamplingTime = GC_3D::Seconds(deltaTime);
		if (curSamplingTime >= 1.0) 
		{
			msFrames = curSamplingTime * 1000.0 / double(nbFrames);
			nbFrames = 0;
			lastTime = Clock::now();
		}

		ImGui::Begin("Perfs");
		ImGui::LabelText("ms/frame", "%f", msFrames);
		ImGui::End();

		Vbuffer->CreateBuffer(g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
		Vbuffer->BindBuffer(0, 3);
		Cbuffer->CreateBuffer(g_uv_buffer_data, sizeof(g_uv_buffer_data));
		Cbuffer->BindBuffer(1, 2);
		

		glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(2);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		//Rendering end
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		SDL_GL_SwapWindow(win);
	}

	//printf("\nHello World !\n");
	return 0;
}