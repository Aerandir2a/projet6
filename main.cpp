#include <GL/glew.h>
#include<iostream>
#include<SDL.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "Texture.hpp"
#include"shader/shader.hpp"
#include "dep/imgui/imgui.h"
#include "dep/imgui/backends/imgui_impl_opengl3.h"
#include "dep/imgui/backends/imgui_impl_sdl.h"
#include "stb.h"
#include "gc_3d_defs.hpp"

using namespace GC_3D;

int	main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);

	uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_Window* win = SDL_CreateWindow("moteur",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1024,768,windowFlags);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext context = SDL_GL_CreateContext(win);
	SDL_GL_MakeCurrent(win, context);
	glClearColor(0.0, 0.0, 0.4, 0.0);
	glViewport(0, 0, 1024, 768);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glewInit();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	ImGui_ImplSDL2_InitForOpenGL(win, context);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();

	GLuint programID = LoadShaders("D:/Users/ppiglioni/projet6/shader/TranformVertexShader.vertexshader.txt", "D:/Users/ppiglioni/projet6/shader/SimpleFragmentShader.fragmentshader.txt");
	
	//permet d'afficher la face avant mais pas la face derrière
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	
	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
	GLuint LayerID = glGetUniformLocation(programID, "layer");

	Texture t1;
	t1.LoadTextureGif("D:/users/ppiglioni/projet6/images/Mmmh_sun.gif");
	//t1.LoadTexture2D("D:/users/ppiglioni/projet6/images/UwU2.jpg");
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D_ARRAY, t1.texture);
	glUniform1i(TextureID, 0);

	Texture t2;
	t2.LoadTextureGif("D:/users/ppiglioni/projet6/images/fanta.gif");
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D_ARRAY, t2.texture);
	glUniform1i(TextureID, 0);

	Texture t3;
	t3.LoadTextureGif("D:/users/ppiglioni/projet6/images/rickroll_roll.gif");
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D_ARRAY, t3.texture);
	glUniform1i(TextureID, 0);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

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

	GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,1.0f, -1.0f, 1.0f,-1.0f, -1.0f, 1.0f, // face avant

		-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, // face gauche

		1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, // face derrière

		1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, // face droite

		 -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, // face dessus

		 -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // face dessous
	};

	// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
	static const GLfloat g_uv_buffer_data[] = {
		0.0f, 1.0f,// face avant
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,// face gauche
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,// face derrière
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,// face droite
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,// face dessus
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,// face dessous
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
	};

	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	auto time = Clock::now();
	auto timergif = Clock::now();

	bool appRunning = true;
	int frameOfGif = t1.frames;
	int frame = 0;
	int inAnimation = 1;
	glUniform1i(TextureID, 0);
	while (appRunning) {
		
		SDL_Event curEvent;
		while (SDL_PollEvent(&curEvent))
		{
			/*if (curEvent.type == SDL_QUIT || curEvent.key.keysym.sym == SDLK_ESCAPE) {
				SDL_Quit();
			}*/

			ImGui_ImplSDL2_ProcessEvent(&curEvent);
			if (!io.WantCaptureMouse)
			{
				//use mouse events not already used by ImGui
			}
			if (!io.WantCaptureKeyboard)
			{
				//use keyboard events not already used by ImGui
			}
			//... app processing other events;
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(programID);	
		
		// Send our transformation to the currently bound shader, in the "MVP" uniform
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, value_ptr(MVP));

		// Bind our texture in Texture Unit 0
		
		//glUniform1i(TextureID, 1);
		//Set our "myTextureSampler" sampler to use Texture Unit 1

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(win);

		ImGui::NewFrame();
		
		auto curTime = Clock::now();
		Duration elapsedSeconds = curTime - time;
		float elapsedSecondsf = GC_3D::Seconds(elapsedSeconds);

		ImGui::Begin("Perfs");
		/*ImGui::LabelText("Time from the beginning : ", "%f", elapsedSecondsf * 1e-0);
		ImGui::LabelText("Frame from the beginning : ", "%f", elapsedSecondsf * 6e-2);
		ImGui::LabelText("FPS : ", "%f",  1 / elapsedSecondsf);*/
		ImGui::LabelText("Time : ", "%f", elapsedSecondsf);
		ImGui::LabelText("frame : ", "%i", frame);
		
		if (ImGui::Button("Surprise!")) {
			//printf("\nsurprise!");
			timergif = Clock::now();
			//glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, x3, y3, frames3, 0, GL_RGBA, GL_UNSIGNED_BYTE, data3);
			frameOfGif = t3.frames;
			frame = 0;
			glUniform1i(TextureID, 2);
		}
		ImGui::End();
		
		/*if (frame >= frameOfGif && inAnimation == 1) {
			frame = 0;
			glUniform1i(TextureID, 1);
			//glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, x, y, frames, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
			frameOfGif = t2.frames;
			inAnimation = 2;
			timergif = Clock::now();
		}
		else if (frame >= frameOfGif && inAnimation == 2) {
			frame = 0;
			glUniform1i(TextureID, 0);
			//glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, x, y, frames, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			frameOfGif = t1.frames;
			inAnimation = 1;
			timergif = Clock::now();
		}
		
		auto endTimerGif = Clock::now();
		Duration timeForGif = endTimerGif - timergif;
		frame = Seconds(timeForGif) / 0.06;
		glUniform1i(LayerID, frame);*/
		//Texture::GifTick(&frame, &frameOfGif, &inAnimation, TextureID, LayerID,t1,t2);
		Texture::GifTick(t1, LayerID, &frame);
		

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

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
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
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		/*for (int j = 0; j < 20; j++) {
			if (j == 0) {
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

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

				// 2nd attribute buffer : UVs
				glEnableVertexAttribArray(1);
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
				glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
			}
			else {

			}
		}

		/*for (int i = 0; i < sizeof(g_vertex_buffer_data) / 4; i++) {
			if (0 == (i + 1) % 3) {
				g_vertex_buffer_data[i] = g_vertex_buffer_data[i] - 3.0;
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data2), g_vertex_buffer_data2, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
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
		glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle*/
		glDisableVertexAttribArray(0);	

		//Rendering end

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Swap window as usual
		SDL_GL_SwapWindow(win);
	}

	return 0;
}