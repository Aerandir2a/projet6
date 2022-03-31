
#include "../gc_3d_defs.hpp"
#include "../header/controls.hpp"
#include <SDL.h>

using namespace glm;

mat4 ViewMatrix = glm::lookAt(
	glm::vec3(0, 0, 5),		// Camera is here
	glm::vec3(0, 0, 0),		// and looks here : at the same position, plus "direction"
	glm::vec3(0, -1, 0)		// Head is up (set to 0,-1,0 to look upside-down)
);
mat4 ProjectionMatrix;

mat4 getViewMatrix() 
{
	return ViewMatrix;
}
mat4 getProjectionMatrix() 
{
	return ProjectionMatrix;
}

// Initial position : on +Z
glm::vec3 position = glm::vec3(0, 0, 10);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 20.0f; // 3 units / second
float mouseSpeed = 0.10f;

auto prevTime = GC_3D::Clock::now();

glm::vec3 direction;
//Droite/gauche
glm::vec3 right;
//Haut/Bas
glm::vec3 height = glm::vec3(
	0,
	sin(10 - 3.14f / 2.0f),
	0
);

void moveCamera(Dirs const& iDirs) 
{
	auto mcurTime = GC_3D::Clock::now();
	GC_3D::Duration mdeltaTime = mcurTime - prevTime;

	//Input de deplacement de la camera
	if (iDirs.front) {
		position += direction * GC_3D::Seconds(mdeltaTime) * speed; //Front
	}
	if (iDirs.back) {
		position -= direction * GC_3D::Seconds(mdeltaTime) * speed; //Back
	}
	if (iDirs.right) {
		position += right * GC_3D::Seconds(mdeltaTime) * speed; //Right
	}
	if (iDirs.left) {
		position -= right * GC_3D::Seconds(mdeltaTime) * speed; //Left
	}
	if (iDirs.up) {
		position += height * GC_3D::Seconds(mdeltaTime) * speed; //Up
	}
	if (iDirs.down) {
		position -= height * GC_3D::Seconds(mdeltaTime) * speed; //Down
	}

	computeMatricesFromInputs();

	//prevTime = mcurTime;
}

void iPosMouse(int xpos, int ypos)
{
	auto scurTime = GC_3D::Clock::now();
	GC_3D::Duration sdeltaTime = scurTime - prevTime;

	horizontalAngle += mouseSpeed * GC_3D::Seconds(sdeltaTime) * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * GC_3D::Seconds(sdeltaTime) * float(768 / 2 - ypos);
}

void computeMatricesFromInputs()
{
	auto curTime = GC_3D::Clock::now();
	GC_3D::Duration deltaTime = curTime - prevTime;

	//Direction ou la camera pointe
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 500.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	prevTime = curTime;
}