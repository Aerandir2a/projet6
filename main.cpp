#include<iostream>
#include<SDL.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include"gc_3d_defs.hpp"
#include"shader/shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "header/stb_image.h"
//#include "header/buffer.hpp"
#include "header/controls.hpp"
#include "header/camera.hpp"
#include "dep/imgui/imgui.h"
#include "dep/imgui/backends/imgui_impl_opengl3.h"
#include "dep/imgui/backends/imgui_impl_sdl.h"

#include "header/objloader.hpp"





using namespace GC_3D;

int	main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);

	uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_Window* win = SDL_CreateWindow("moteur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, windowFlags);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext context = SDL_GL_CreateContext(win);
	SDL_GL_MakeCurrent(win, context);
	glClearColor(0.0, 0.0, 0.4, 0.0);
	glViewport(0, 0, 1024, 768);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glewInit();



	//init ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplSDL2_InitForOpenGL(win, context);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();





	//GLuint programID = LoadShaders("C:/Users/lnicolas/Documents/GitHub/projet6/shader/TranformVertexShader.vertexshader.txt", "C:/Users/lnicolas/Documents/GitHub/projet6/shader/SimpleFragmentShader.fragmentshader.txt");
	GLuint programID = LoadShaders("D:/LapendryFlorian/GitHub/projet6/shader/TranformVertexShader.vertexshader.txt", "D:/LapendryFlorian/GitHub/projet6/shader/SimpleFragmentShader.fragmentshader.txt");

	//permet d'afficher la face avant mais pas la face derrière
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);


	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	//GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");


	/*

	GLuint Texture;
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("C:/Users/lnicolas/Documents/GitHub/projet6/images/portal.png", &width, &height, &nrChannels, 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	*/




	// fill "indices" as needed


	/*
	// Read our .obj file
	std::vector<unsigned short> indices;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // Won't be used at the moment.
	bool res = loadAssImp("C:/Users/lnicolas/Documents/GitHub/projet6/objets3D/FrogUV.fbx", indices, vertices, uvs, normals);
	*/



	// Read our .obj file
	std::vector<unsigned short> indices;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // Won't be used at the moment.
	bool res = loadAssImp("D:/LapendryFlorian/GitHub/projet6/objets3D/FrogUV.fbx", indices, vertices, uvs, normals);

	// Generate a buffer for the indices
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);




	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	/*
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	mat4 View = lookAt(
		vec3(4, 2, 4), // Camera is at (4,3,3), in World Space
		vec3(0, 0, 0), // and looks at the origin
		vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	mat4 Model = mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
	*/



	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);


	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);


	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);

	//Interaction avec la souris
	int MousePosX = 0;
	int MousePosY = 0;
	bool focus = true;
	bool mouseClicRight = false;

	float slidertest = 0.0f;

	//Variables pour calcule des ms/frame
	int nbFrames = 0;
	double msFrames = 0;
	double FPS = 0;
	auto lastTime = Clock::now();
	auto time = Clock::now();
	auto DebutFrame = Clock::now();

	if (win != nullptr) {
		SDL_WarpMouseInWindow(win, 1024 / 2, 768 / 2);
		//computeMatricesFromInputs(curDirs, MousePosX, MousePosY);
	}

	startPosCamera();

	Camera* camera = new Camera();

	bool appRunning = true;
	while (appRunning) {

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

			//glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(programID);

			//CAMERA
			camera->CreateCamera(win, programID, curDirs, MousePosX, MousePosY, mouseClicRight);

			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			auto curTime = Clock::now();
			std::chrono::duration<float> elapsedSeconds = curTime - time;

			//ms lisser
			Duration deltaTime = curTime - lastTime;
			nbFrames++;

			//FPS
			auto FinFrame = Clock::now();
			Duration FPSTime = FinFrame - DebutFrame;
			//FPS = 1.0f / GC_3D::Seconds(FPSTime);
			DebutFrame = FinFrame;

			//Render Loop
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame(win);

			ImGui::NewFrame();

			//Calcule ms/frame
			float const curSamplingTime = GC_3D::Seconds(deltaTime);
			if (curSamplingTime >= 1.0)
			{
				msFrames = curSamplingTime * 1000.0 / double(nbFrames);
				nbFrames = 0;
				lastTime = Clock::now();
				FPS = 1.0f / GC_3D::Seconds(FPSTime);
			}

			// Draw some widgets ImGui
			ImGui::Begin("Perfs");

			ImGui::LabelText("", "Time (s) : %f", elapsedSeconds * 1e-0);
			ImGui::LabelText("", "ms/frame : %f", msFrames);
			ImGui::LabelText("", "FPS : %f", FPS);
			ImGui::LabelText("", "Valeur Slider : Test : %f", slidertest);

			ImGui::End();

			ImGui::Begin("Modif Scene");

			ImGui::LabelText("", "Object number : ");

			if (ImGui::Button("Click Button!")) {
				printf("Button clicked ");
			}

			ImGui::SliderFloat("Test", &slidertest, 0.0f, 100.0f);

			ImGui::End();



			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			// 2nd attribute buffer : colors
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);


			// 3nd attribute buffer : UVs
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				2,                                // size : U+V => 2
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);

			// Draw the triangle !
			//glDrawArrays(GL_TRIANGLES, 0, indices.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
			//glDisableVertexAttribArray(0);



			// Index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

			// Draw the triangles !
			glDrawElements(
				GL_TRIANGLES,      // mode
				indices.size(),    // count
				GL_UNSIGNED_SHORT,   // type
				(void*)0           // element array buffer offset
			);

			// Enable depth test
			glEnable(GL_DEPTH_TEST);
			// Accept fragment if it closer to the camera than the former one
			glDepthFunc(GL_LESS);

			//Render ImGui
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			//Swap window as usual
			SDL_GL_SwapWindow(win);
	}

	return 0;
}

/*void old() {
	auto time = Clock::now(); // à mettre avant le double while
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat ambientLightFull[] = { 1.0f, 0.25f, 0.20f, 0.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLightFull);
	float gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

	const float radius = 0.5;

	auto curTime = Clock::now();
	std::chrono::duration<float> fTime = curTime - time;
	float camX = sin(fTime.count()) * radius;
	float camZ = cos(fTime.count()) * radius;

	vec3 cameraTarget = vec3(0.0, 0.0, -2.0);

	vec3 cameraPos = cameraTarget - 4.0f * vec3(camX, -0.5, camZ);

	// Creation de la camera
	mat4 view;
	view = lookAt(cameraPos, //Position de la camera
		cameraTarget, //Cible à regarder
		vec3(0.0, 1.0, 0.0)); //position vertical
	mat4 camFrustum = frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&camFrustum[0][0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&view[0][0]);

	glTranslatef(0.0, 0.0, -2.0);

	vec3 p0 = vec3(-1.0, -1.0, 1.0);
	vec3 p1 = vec3(-1.0, 1.0, 1.0);
	vec3 p2 = vec3(1.0, 1.0, 1.0);
	vec3 p3 = vec3(1.0, -1.0, 1.0);
	vec3 p4 = vec3(-1.0, -1.0, -1.0);
	vec3 p5 = vec3(-1.0, 1.0, -1.0);
	vec3 p6 = vec3(1.0, 1.0, -1.0);
	vec3 p7 = vec3(1.0, -1.0, -1.0);

	Geometry test;


	test.m_Pos = {
		p0,p1,p2,p3,
		p0,p1,p4,p5,
		p4,p5,p6,p7,
		p7,p6,p2,p3,
		p0,p3,p4,p7,
		p1,p2,p5,p6
	};

	test.m_Normals = {
		vec3(0.0,0.0,1.0),vec3(0.0,0.0,1.0),vec3(0.0,0.0,1.0),vec3(0.0,0.0,1.0),
		vec3(-1.0,0.0,0.0),vec3(-1.0,0.0,0.0),vec3(-1.0,0.0,0.0),vec3(-1.0,0.0,0.0),
		vec3(0.0,0.0,-1.0),vec3(0.0,0.0,-1.0),vec3(0.0,0.0,-1.0),vec3(0.0,0.0,-1.0),
		vec3(1.0,0.0,0.0),vec3(1.0,0.0,0.0),vec3(1.0,0.0,0.0),vec3(1.0,0.0,0.0),
		vec3(0.0,-1.0,0.0),vec3(0.0,-1.0,0.0),vec3(0.0,-1.0,0.0),vec3(0.0,-1.0,0.0),
		vec3(0.0,1.0,0.0),vec3(0.0,1.0,0.0),vec3(0.0,1.0,0.0),vec3(0.0,1.0,0.0),
	};

	test.m_Indices = {
		0,1,2,0,2,3,
		4,5,6,5,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,21,22,23
	};

	test.Bind();
	test.Draw();

	glBegin(GL_TRIANGLES);
	//Front
	glColor4f(0.0, 1.0, 0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	//left
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	//right
	glColor4f(0.0, 1.0, 1.0, 1.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	//back
	glColor4f(1.0, 0.0, 0.0, -1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	//top
	glColor4f(1.0, 0.0, 1.0, -1.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	//bot
	glColor4f(1.0, 1.0, 0.0, -1.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glEnd();
}*/