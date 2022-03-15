#include<iostream>
#include<SDL.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include"gc_3d_defs.hpp"
#include"shader/shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "dep/imgui/imgui.h"
#include "dep/imgui/backends/imgui_impl_opengl3.h"
#include "dep/imgui/backends/imgui_impl_sdl.h"
#include "stb.c"




using namespace GC_3D;

int	main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);

	uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_Window* win = SDL_CreateWindow("moteur",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1024,768,windowFlags);

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

	GLuint Texture;
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
	

	int width, height, nrChannels;
	unsigned char* data = stbi_load("D:/users/ppiglioni/projet6/images/UwU3.gif", &width, &height, &nrChannels, 0);

	//unsigned char* data = stbi_xload_file("D:/users/ppiglioni/projet6/images/UwU3.gif",);

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

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

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

	static const GLfloat g_vertex_buffer_data[] = {
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

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	auto time = Clock::now();

	bool appRunning = true;
	while (appRunning) {
		
		SDL_Event curEvent;
		while (SDL_PollEvent(&curEvent))
		{
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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(win);

		ImGui::NewFrame();
		
		auto curTime = Clock::now();
		std::chrono::duration<float> elapsedSeconds = curTime - time;

		ImGui::Begin("Perfs");
		ImGui::LabelText("Frame Time (s) : ", "%f", elapsedSeconds * 1e-0);
		ImGui::LabelText("FPS : ", "%f",  1 / elapsedSeconds.count());
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
		glDisableVertexAttribArray(0);	

		//... App rendering

		//Rendering end

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Swap window as usual
		SDL_GL_SwapWindow(win);
	}

	return 0;
}

void old() {
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

	/*glBegin(GL_TRIANGLES);
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

	glEnd();*/
}