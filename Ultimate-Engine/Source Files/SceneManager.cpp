/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "SceneManager.h"
#include <CameraManager.h>


managers::SceneManager* managers::SceneManager::scene_manager;
int managers::SceneManager::height = 0;
int managers::SceneManager::width = 0;
char managers::SceneManager::keyPressed = 0;
glm::vec2 managers::SceneManager::mouseScrool;

managers::SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	shader_manager = new ShaderManager();
	models_manager = new ModelManager();

	memset(keyState, 0, 256);
	memset(specialKeyState, 0, 256);
}

managers::SceneManager::~SceneManager()
{
	delete shader_manager;
	delete models_manager;
}

void managers::SceneManager::notifyBeginFrame()
{
	models_manager->update();
	/*float angle = 0.01f;
	glm::vec3 lp = managers::CameraManager::L_light_position;

	managers::CameraManager::L_light_position.y = lp.y*cos(-angle) - lp.x*sin(-angle);
	managers::CameraManager::L_light_position.x = lp.y*sin(-angle) + lp.x*cos(-angle);*/
}

void managers::SceneManager::notifyDisplayFrame()
{
	treatInput();

	
	//managers::CollisionManager::swap(managers::CollisionManager::swap_name);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.9f, 1.0f, 0.0f);

	CameraManager::setViewMatrix(CameraManager::player_camera->getViewMatrix());
	CameraManager::computePerspectiveProjection();
	setTPSCameraViewport();
	models_manager->draw();

	unsigned int time = glutGet(GLUT_ELAPSED_TIME);
	managers::CameraManager::frameTime = time - managers::CameraManager::previousTime;
	managers::CameraManager::previousTime = time;

	managers::CameraManager::L_projection_matrix = glm::perspective(90.0f, (float)width / (float)height, 0.1f, 10000.0f);
}

void managers::SceneManager::notifyEndFrame() { }

void managers::SceneManager::notifyReshape(int width, int height,
	int previos_width, int previous_height) { 

	SceneManager::width = width;
	SceneManager::height = height;

	managers::CameraManager::aspectRatio = width / (float)height;
}

void managers::SceneManager::setTPSCameraViewport() {
	glViewport(0, 0, SceneManager::width, SceneManager::height);
}

void managers::SceneManager::setFPSCameraViewport() {
	glViewport((SceneManager::width / 4) * 3, (SceneManager::height / 4) * 3, SceneManager::width / 4, SceneManager::height / 4);
}

managers::ShaderManager* managers::SceneManager::getShaderManager()
{
	return shader_manager;
}

managers::ModelManager* managers::SceneManager::getModelManager()
{
	return models_manager;
}

static bool editing = false;

void managers::SceneManager::notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y)
{
	//printf("Key Pressed\n");

	keyState[key_pressed] = 1;
	keyPressed = key_pressed;

	if (keyPressed == 13) {
		if (editing)
			editing = false;
		else
			editing = true;
	}
}

void managers::SceneManager::notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y)
{
	//printf("Key Released\n");

	keyState[key_released] = 0;
}

void managers::SceneManager::notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y)
{
	//printf("Special Key Pressed\n");

	specialKeyState[key_pressed] = 1;
}

void managers::SceneManager::notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y)
{
	//printf("Special Key Released\n");

	specialKeyState[key_released] = 0;
}

void managers::SceneManager::notifyMouseDrag(int mouse_x, int mouse_y)
{
	//printf("%d Mouse Drag\n", mouse_x);
}

void managers::SceneManager::notifyMouseMove(int mouse_x, int mouse_y)
{
	//printf("Mouse Move\n");
}

void managers::SceneManager::notifyMouseClick(int button, int state, int mouse_x, int mouse_y)
{
	//printf("Mouse Click\n");
}

void managers::SceneManager::notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y)
{
	//printf("Mouse Scroll\n");
	mouseScrool.x = wheel;
	mouseScrool.y = direction;
}


void managers::SceneManager::treatInput()
{

	float frameTime = managers::CameraManager::getFrameTimeSeconds();
	float moveSpeed = frameTime * 5;
	float rotateSpeed = frameTime;

	if (specialKeyState[GLUT_KEY_SHIFT_L])
	{
		rotateSpeed *= 2;
		moveSpeed *= 2;
	}

	// Camera Translation
	if (keyState['w'] && !editing)
	{
		
			CameraManager::player_camera->translateForward(moveSpeed);
			
	}
	if (keyState['a'] && !editing)
	{
		
			CameraManager::player_camera->translateRight(-moveSpeed);
		

	}
	if (keyState['s'] && !editing)
	{
		
			CameraManager::player_camera->translateForward(-moveSpeed);

	}
	if (keyState['d'] && !editing)
	{
		
			CameraManager::player_camera->translateRight(moveSpeed);

	}
	if (keyState['e'] && !editing)
	{
			CameraManager::player_camera->translateUpword(moveSpeed);
	}
	if (keyState['q'] && !editing)
	{
			CameraManager::player_camera->translateUpword(-moveSpeed);
	}

	// Camera Rotate FPS
	if (specialKeyState[GLUT_KEY_LEFT])
	{
		CameraManager::player_camera->rotateFPS_OY(rotateSpeed);
	}
	if (specialKeyState[GLUT_KEY_RIGHT])
	{
		CameraManager::player_camera->rotateFPS_OY(-rotateSpeed);
		
	}

	if (specialKeyState[GLUT_KEY_UP])
	{
		CameraManager::player_camera->rotateFPS_OX(rotateSpeed);
	}
	if (specialKeyState[GLUT_KEY_DOWN])
	{
		CameraManager::player_camera->rotateFPS_OX(-rotateSpeed);
	}

	if (keyState['r'] && !editing)
	{
		CameraManager::player_camera->rotateFPS_OZ(-rotateSpeed);
	}
	if (keyState['f'] && !editing)
	{
		CameraManager::player_camera->rotateFPS_OZ(rotateSpeed);
	}

	if (keyState['p'] && !editing)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	

	// Camera Rotate TPS
	if (keyState['5'] && !editing)
	{
		CameraManager::L_light_position.z += 1.5;
	}
	if (keyState['8'] && !editing)
	{
		CameraManager::L_light_position.z -= 1.5;
	}
	if (keyState['4'] && !editing)
	{
		CameraManager::L_light_position.x -= 1.5;
	}
	if (keyState['6'] && !editing)
	{
		CameraManager::L_light_position.x += 1.5;
	}
	if (keyState['7'] && !editing)
	{
		float angle = 0.05f;
		glm::vec3 lp = managers::CameraManager::L_light_position;

		managers::CameraManager::L_light_position.y = lp.y*cos(-angle) - lp.x*sin(-angle);
		managers::CameraManager::L_light_position.x = lp.y*sin(-angle) + lp.x*cos(-angle);
	}
	if (keyState['9'] && !editing)
	{
		float angle = 0.05f;
		glm::vec3 lp = managers::CameraManager::L_light_position;

		managers::CameraManager::L_light_position.y = lp.y*cos(angle) - lp.x*sin(angle);
		managers::CameraManager::L_light_position.x = lp.y*sin(angle) + lp.x*cos(angle);
	}
	if (keyState['1'] && !editing)
	{
		float angle = 0.05f;
		glm::vec3 lp = managers::CameraManager::L_light_position;

		managers::CameraManager::L_light_position.y = lp.y*cos(-angle) - lp.z*sin(-angle);
		managers::CameraManager::L_light_position.z = lp.y*sin(-angle) + lp.z*cos(-angle);
	}
	if (keyState['3'] && !editing)
	{
		float angle = 0.05f;
		glm::vec3 lp = managers::CameraManager::L_light_position;

		managers::CameraManager::L_light_position.y = lp.y*cos(angle) - lp.z*sin(angle);
		managers::CameraManager::L_light_position.z = lp.y*sin(angle) + lp.z*cos(angle);
	}

}