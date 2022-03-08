#include<iostream>
#include<chrono>
#include<SDL.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include<gl/GL.h>

int	main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);

	uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_Window* win = SDL_CreateWindow("moteur",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1024,768,windowFlags);

	SDL_GLContext context = SDL_GL_CreateContext(win);
	SDL_GL_MakeCurrent(win, context);

	auto time = std::chrono::steady_clock::now();

	bool appRunning = true;
	while (appRunning) {

		SDL_Event curEvent;
		while (SDL_PollEvent(&curEvent)) {
		}
		glm::vec3 cameraPos = glm::vec3(0.0, 1.0, 1.0);
		
		float radius = 0.01f;
		auto endTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> fTime = endTime - time;
		float camX = glm::sin(fTime.count()) * radius;
		float camZ = glm::cos(fTime.count()) * radius;
		cameraPos = glm::vec3(camX, 0.005, camZ);
		
		glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 camFrustum = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(&camFrustum[0][0]);
		//glLoadMatrixf(&view[0][0]);

		glViewport(0.0, 0.0, 1024, 768);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor4f(0.0, 0.0, 1.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, 0.0, -10.0);
		glVertex3f(0.0, 1.0, -10.0);
		glVertex3f(1.0, 0.0, -10.0);

		/*glColor4f(1.0, 0.0, 0.0, 0.5);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);*/

		glEnd();

		SDL_GL_SwapWindow(win);
		
	}

	//printf("All hail Samug!! \nUwU!");
	return 0;
}