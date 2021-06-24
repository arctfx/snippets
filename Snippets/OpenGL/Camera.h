#pragma once

#include <gui.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ctype.h>
#include <iostream>

using namespace glm;

class Camera
{
public:
	Camera(const vec3& eye = vec3(0.f, 0.f, 0.f), const vec3& dir = vec3(0.f, 0.f, -1.f));

	void handleMouse(int button, int state, int x, int y);
	bool handleKey(unsigned char key, int x, int y, float speed = 50.0f);
	void handleMotion(int x, int y);
	void handleAnalogMove(float x, float y);

	void update();

	vec3 getEye() const;
	vec3 getDir() const;
	//physx::PxTransform getTransform() const;
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();

private:
	vec3 mEye;
	vec3 mDir;
	int mMouseX;
	int mMouseY;
	float FoV = 45.0f;
	mat4 mViewMatrix;
	mat4 mProjectionMatrix;

	sf::Clock deltaClock;
	float dt;
	// Initial horizontal angle : toward -Z 
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = -1.5f;
	
	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;
};
