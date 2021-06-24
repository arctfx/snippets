#include "Camera.h"

Camera::Camera(const vec3& eye, const vec3& dir)
{
	mEye = eye;
	mDir = normalize(dir);
	//mMouseX = 0;
	//mMouseY = 0;
}

void Camera::handleMouse(int button, int state, int x, int y)
{
	//PX_UNUSED(state);
	//PX_UNUSED(button);

	//mMouseX = x;
	//mMouseY = y;
}

bool Camera::handleKey(unsigned char key, int x, int y, float speed)
{
	//PX_UNUSED(x);
	//PX_UNUSED(y);
	dt = deltaClock.restart().asSeconds();

	vec3 viewY = normalize(cross(vec3(0, 1, 0), mDir));
	switch(toupper(key))
	{
	case 'W':	mEye += mDir*dt*speed;		break;
	case 'S':	mEye -= mDir*dt*speed;		break;
	case 'A':	mEye += viewY*dt*speed;		break;
	case 'D':	mEye -= viewY*dt*speed;		break;
	default:							return false;
	}
	return true;
}

void Camera::handleAnalogMove(float x, float y)
{
	vec3 viewY = normalize(cross(vec3(0, 1, 0), mDir));
	mEye += mDir*y;
	mEye += viewY*x;
}

void Camera::handleMotion(int x, int y)
{
	int dx = mMouseX - x;
	int dy = mMouseY - y;

	vec3 viewY = normalize(cross(vec3(0, 1, 0), mDir));

	//PxQuat qx(PxPi * dx / 180.0f, PxVec3(0,1,0));
	//mDir = qx.rotate(mDir);
	//PxQuat qy(PxPi * dy / 180.0f, viewY);
	//mDir = qy.rotate(mDir);

	//mDir.normalize();

	//mMouseX = x;
	//mMouseY = y;
}


void Camera::update()
{
	//dt = deltaClock.restart().asSeconds();

	mMouseX = sf::Mouse::getPosition().x;
	mMouseY = sf::Mouse::getPosition().y;

	// Reset mouse position for next frame
	sf::Mouse::setPosition(sf::Vector2i(WIDTH / 2, HEIGHT / 2), MainWindow); //<-- !!!!!!!!!!!!!!!!!!!!!!!!!!

	// Compute new orientation
	horizontalAngle == mouseSpeed * float(WIDTH / 2 - mMouseX);
	verticalAngle == mouseSpeed * float(HEIGHT / 2 - mMouseY);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	vec3 direction = vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	vec3 right = vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	vec3 up = cross(right, direction);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mProjectionMatrix = perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera matrix
	mViewMatrix = lookAt(
		mEye,           // Camera is here
		mEye + mDir, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}


/*PxTransform Camera::getTransform() const {
	PxVec3 viewY = mDir.cross(PxVec3(0,1,0));

	if(viewY.normalize()<1e-6f) return PxTransform(mEye);

	PxMat33 m(mDir.cross(viewY), viewY, -mDir);
	return PxTransform(mEye, PxQuat(m)); 
}*/

vec3 Camera::getEye() const
{ 
	return mEye; 
}

vec3 Camera::getDir() const
{ 
	return mDir; 
}

mat4 Camera::getProjectionMatrix()
{
	return mProjectionMatrix;
}

mat4 Camera::getViewMatrix() 
{
	return mViewMatrix;
}
