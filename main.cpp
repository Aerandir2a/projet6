#include<iostream>
#include<SDL.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include"gc_3d_defs.hpp"
#include"shader/shader.hpp"
//#define STB_IMAGE_IMPLEMENTATION
#include "header/stb_image.h"
#include "header/buffer.hpp"
#include "header/controls.hpp"
#include "header/camera.hpp"
#include "dep/imgui/imgui.h"
#include "dep/imgui/backends/imgui_impl_opengl3.h"
#include "dep/imgui/backends/imgui_impl_sdl.h"

#include "stb.h"
#include "Texture.hpp"

#include <filesystem>
#include "header/directorySnippet.hpp"
#include "header/model.h"
#include "header/shader_.h"





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

	std::filesystem::path appPath(GetAppPath());
	auto appDir = appPath.parent_path();
	auto shaderPath = appDir / "shader";
	auto vShaderPath = shaderPath / "TranformVertexShader.vertexshader.txt";
	auto fShaderPath = shaderPath / "SimpleFragmentShader.fragmentshader.txt";
	auto fGShaderPath = shaderPath / "SimpleFragmentShader.fragmentshaderGif.txt";
	auto vsShaderPath = shaderPath / "1.model_loading.vs";
	auto fsShaderPath = shaderPath / "1.model_loading.fs";

	auto ObjetPath = appDir / "objets3D";
	auto Objet3DPath_Shiba = ObjetPath / "shibaUV.fbx";
	auto Objet3DPath_Frog = ObjetPath / "FrogUV.fbx";
	auto Objet3DPath_Banana = ObjetPath / "Banana.obj";
	auto Objet3DPath_Snake = ObjetPath / "Snake_angry.fbx";

	auto Objet3DPath_Crab = ObjetPath / "crab.obj";
	auto Objet3DPath_Deer = ObjetPath / "deer.obj";
	auto Objet3DPath_Pub = ObjetPath / "cube.obj";

	auto imagePath = appDir / "images";
	auto image_PathGif = imagePath / "Mmmh_sun.gif";
	auto image_PathGif2 = imagePath / "UwU3.gif";
	auto image_Path = imagePath / "Crab_Texture.png";
	auto image_PathDeer = imagePath / "Deer_Texture.png";

	std::string path_stringImage{ image_Path.u8string() };
	std::string path_stringImageDeer{ image_PathDeer.u8string() };
	std::string path_stringGif{ image_PathGif.u8string() };
	std::string path_stringGif2{ image_PathGif2.u8string() };

	std::string path_stringV{ vShaderPath.u8string() };
	std::string path_stringF{ fShaderPath.u8string() };
	std::string path_stringFG{ fGShaderPath.u8string() };
	std::string path_stringVS{ vShaderPath.u8string() };
	std::string path_stringFS{ fShaderPath.u8string() };

	std::string path_stringObjet_Shiba{ Objet3DPath_Shiba.u8string() };
	std::string path_stringObjet_Frog{ Objet3DPath_Frog.u8string() };
	std::string path_stringObjet_Banana{ Objet3DPath_Banana.u8string() };
	std::string path_stringObjet_Snake{ Objet3DPath_Snake.u8string() };
	std::string path_stringObjet_Crab{ Objet3DPath_Crab.u8string() };
	std::string path_stringObjet_Deer{ Objet3DPath_Deer.u8string() };
	std::string path_stringObjet_Pub{ Objet3DPath_Pub.u8string() };

	GLuint programID = LoadShaders(path_stringV.c_str(), path_stringF.c_str());
	GLuint programIDGif = LoadShaders(path_stringV.c_str(), path_stringFG.c_str());

	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	GLuint TextureIDGif = glGetUniformLocation(programIDGif, "myTextureSampler");
	GLuint LayerIDGif = glGetUniformLocation(programIDGif, "layer");

	Texture t2;
	t2.LoadTexture2D(path_stringImage.c_str());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, t2.texture);

	Texture t3;
	t2.LoadTexture2D(path_stringImageDeer.c_str());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, t3.texture);

	Texture t1;
	t1.LoadTextureGif(path_stringGif.c_str());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D_ARRAY, t1.texture);
	
	Texture t4;
	t4.LoadTextureGif(path_stringGif2.c_str());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D_ARRAY, t4.texture);

	

	// Read our .obj file
	std::vector<unsigned short> indices;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // Won't be used at the moment.
	Model ourModel_Shiba(path_stringObjet_Shiba.c_str());
	Model ourModel_Frog(path_stringObjet_Frog.c_str());
	Model ourModel_Banana(path_stringObjet_Banana.c_str());
	Model ourModel_Snake(path_stringObjet_Snake.c_str());
	Model ourModel_Crab(path_stringObjet_Crab.c_str());
	Model ourModel_Deer(path_stringObjet_Deer.c_str());
	Model ourModel_Pub(path_stringObjet_Pub.c_str());


	// build and compile shaders
	// -------------------------
	Shader ourShader(path_stringVS.c_str(), path_stringFS.c_str());

	// Generate a buffer for the indices
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//BUFFER---------------------------------------------------------------------------------------------------------------------------//
	// Init Buffer
	Buffer* Vbuffer = new Buffer();
	Buffer* Cbuffer = new Buffer();
	Buffer* UVbuffer = new Buffer();

	//Create Buffer
	Vbuffer->CreateBuffer(vertices.data(), vertices.size() * sizeof(glm::vec3));
	Cbuffer->CreateBuffer(vertices.data(), vertices.size() * sizeof(glm::vec3));
	UVbuffer->CreateBuffer(uvs.data(), uvs.size() * sizeof(glm::vec2));

	//VARIABLE------------------------------------------------------------------------------------------------------------------------//
	//Interaction avec la souris
	int MousePosX = 1024 / 2;
	int MousePosY = 768 / 2;
	bool focus = true;
	bool mouseClicRight = false;

	int slidertest = 1;

	// Variable pour changer de Mesh
	bool ChangeMesh = false;
	bool ChangeGif = false;

	//Variables pour calcule des ms/frame
	int nbFrames = 0;
	double msFrames = 0;
	double FPS = 0;
	auto lastTime = Clock::now();
	auto time = Clock::now();
	auto DebutFrame = Clock::now();

	if (win != nullptr) {
		SDL_WarpMouseInWindow(win, 1024 / 2, 768 / 2);
	}

	Camera* camera = new Camera();
	camera->CreateCamera();

	//TABLE---------------------------------------------------------------------------------------------------------------------------//

	// Tableau de position des objets
	std::vector<mat4> ModelMatrix;
	//Tableau de Model
	std::vector<Model*> ModelMesh;
	std::vector<Model*> ModelMeshGif;
	int IndexTexture[2] = {0, 1};

	// Create number objects in box (64 000 objects 40x40x40)
	int nMax = 40;
	float scale = 5.0f; // Distance entre les objets
	for (int i = 0; i < nMax; i++) { // Axe X
		for (int j = 0; j < nMax; j++) { // Axe Y
			for (int k = 0; k < nMax; k++) { // Axe Z
				glm::vec3 pos =
					i * scale * vec3(1.0f, 0.0f, 0.0f) +
					j * scale * vec3(0.0f, 1.0f, 0.0f) +
					k * scale * vec3(0.0f, 0.0f, -1.0f);
				ModelMatrix.push_back(glm::translate(mat4(1.0f), pos));
			}
		}
	}

	const char* name = "Advert";
		
	// Create Table Mesh
	for (int i = 0; i < ModelMatrix.size(); i++) 
	{
		
		if (!ChangeMesh)
		{
			ModelMesh.push_back(&ourModel_Crab);
			ChangeMesh = true;
			
		}
		else if (ChangeMesh)
		{
			ModelMesh.push_back(&ourModel_Deer);
			ChangeMesh = false;
			
		}
	}

	//Create Cube Mesh for GIF
	for (int i = 0; i < ModelMatrix.size(); i++)
	{
		ModelMeshGif.push_back(&ourModel_Pub);
	}

	//-----------------------------------------------------------------------------------------------------------------------//
	int frame = 0;
	int frame2 = 0;
	bool test = false;
	bool appRunning = true;
	glUseProgram(programID);
	while (appRunning) {

		Dirs curDirs;
		SDL_Event curEvent;
		while (SDL_PollEvent(&curEvent))
		{
			if (curEvent.type == SDL_QUIT && curEvent.key.keysym.sym == SDLK_ESCAPE) {
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
				if (mouseClicRight) {
					SDL_GetMouseState(&MousePosX, &MousePosY);
				}
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
			// Fenetre Performance 
			ImGui::Begin("Perfs");

			ImGui::LabelText("", "Time (s) : %f", elapsedSeconds * 1e-0);
			ImGui::LabelText("", "ms/frame : %f", msFrames);
			ImGui::LabelText("", "FPS : %f", FPS);

			ImGui::End();
			
			// Changement de Mesh
			ImGui::Begin("Mesh");

			if (ImGui::Button("Change")) {
				if (test)
				{
					glUseProgram(programID);
					test = !test;
				}
				else if (!test) 
				{
					glUseProgram(programIDGif);
					test = !test;
				}

				if (ChangeGif)
				{
					ChangeGif = !ChangeGif;
				}
				else if (!ChangeGif)
				{
					ChangeGif = !ChangeGif;
				}

			}

			ImGui::End();

			// Fenetre Modif
			ImGui::Begin("Modif Scene");

			ImGui::LabelText("", "Object number : %i", ModelMatrix.size());

			ImGui::SliderInt("Number object", &slidertest, 1, 64000);

			if (ImGui::Button("+ 1")) {
				slidertest++;
				printf("Objet + 1 ");
			}

			ImGui::SameLine();

			if (ImGui::Button("- 1")) {
				if (slidertest > 1)
				{
					slidertest--;
					printf("Objet - 1 ");
				}

			}

			

			if (ImGui::Button("+ 10")) {
				slidertest = slidertest + 10;
			}

			ImGui::SameLine();

			if (ImGui::Button("- 10")) {
				if (slidertest > 10)
				{
					slidertest = slidertest - 10;
				}

			}


			if (ImGui::Button("+ 100")) {
				slidertest = slidertest + 100;
			}

			ImGui::SameLine();

			if (ImGui::Button("- 100")) {
				if (slidertest > 100)
				{
					slidertest = slidertest - 100;
				}

			}

			if (ImGui::Button("+ 1000")) {
				slidertest = slidertest + 1000;
			}

			ImGui::SameLine();

			if (ImGui::Button("- 1000")) {
				if (slidertest > 1000)
				{
					slidertest = slidertest - 1000;
				}

			}

			ImGui::End();

			// Bind Buffer
			Vbuffer->BindBuffer(0, 3);
			Cbuffer->BindBuffer(1, 3);
			UVbuffer->BindBuffer(1, 2);

			//CAMERA
			camera->UpdateCamera(win, curDirs, MousePosX, MousePosY, mouseClicRight);

			// Matrix mvp
			glm::mat4 mvp;
			
			// Afficher le nombre d'objet correspondant à la taille du tableau ModelMatrix
			GLuint MatrixID;

			if (test) {
				MatrixID = glGetUniformLocation(programIDGif, "MVP");
			}
			else if (!test) {
				MatrixID = glGetUniformLocation(programID, "MVP");
			}

			for (int i = 0; i < slidertest; i++) {

				mvp = camera->ProjectionMatrix * camera->ViewMatrix * ModelMatrix[i];
				
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
			
				if (test) {
					glUniform1i(TextureIDGif, 2 + i % 2);
				}
				else if (!test) {
					glUniform1i(TextureID, i % 2);
				}

				ourShader.setMat4("model", ModelMatrix[i]);

				if (!ChangeGif)
				{
					ModelMesh[i]->Draw(ourShader);
				}
				else if (ChangeGif)
				{
					ModelMeshGif[i]->Draw(ourShader);
				}

				// Index buffer
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
			}
				
			if (test) {
				Texture::GifTick(t1, LayerIDGif, &frame);
				Texture::GifTick(t4, LayerIDGif, &frame2);
			}

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