#include<iostream>
#include<SDL.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include"gc_3d_defs.hpp"
#include<gl/GL.h>

using namespace GC_3D;

int	main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);

	uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_Window* win = SDL_CreateWindow("moteur",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1024,768,windowFlags);

	SDL_GLContext context = SDL_GL_CreateContext(win);
	SDL_GL_MakeCurrent(win, context);

	auto time = Clock::now();

	bool appRunning = true;
	while (appRunning) {

		SDL_Event curEvent;
		while (SDL_PollEvent(&curEvent))
		{
		}

		glViewport(0, 0, 1024, 768);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		GLfloat ambientLightFull[] = { 1.0f, 0.25f, 0.20f, 0.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLightFull);
		float gray[] = {0.75f, 0.75f, 0.75f, 1.0f};
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

		/*test.m_Indices = {

		};*/

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

		SDL_GL_SwapWindow(win);

		

	}

	return 0;
}