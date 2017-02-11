#include <CameraManager.h>


camera::Camera* managers::CameraManager::player_camera;
glm::mat4 managers::CameraManager::projection_matrix;
glm::mat4 managers::CameraManager::view_matrix;

unsigned int managers::CameraManager::frameTime;
unsigned int managers::CameraManager::previousTime;

int managers::CameraManager::precision_factor = 100;
float managers::CameraManager::speed_by_precision = 0;

float managers::CameraManager::aspectRatio;
float managers::CameraManager::FoV;
float managers::CameraManager::zFar;
float managers::CameraManager::zNear;
float managers::CameraManager::orthoBottom;
float managers::CameraManager::orthoTop;
float managers::CameraManager::orthoLeft;
float managers::CameraManager::orthoRight;

managers::CameraState managers::CameraManager::camera_state = managers::CameraState::PLAYER_FOCUS;
float managers::CameraManager::rotation_angle = 0.0f;





glm::vec3 managers::CameraManager::L_light_position;
glm::vec3 managers::CameraManager::L_eye_position;
unsigned int managers::CameraManager::L_material_shininess;
float managers::CameraManager::L_material_kd;
float managers::CameraManager::L_material_ks;

glm::mat4 managers::CameraManager::L_model_matrix;
glm::mat4 managers::CameraManager::L_view_matrix;
glm::mat4 managers::CameraManager::L_projection_matrix;




void managers::CameraManager::init()
{
	player_camera = new camera::Camera();

	player_camera->set(glm::vec3(0, 0, 2.0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//player_camera->translateUpword(-60.0f);

	//player_camera->translateRight(-60.0f);

	//player_camera->translateForward(-100.0f);

	//player_camera->rotateTPS_OY(-1.57079633f);


	zNear = 0.01f;
	zFar = 500.0f;
	FoV = 90.0f;
	aspectRatio = 800 / 600.0f;
	orthoLeft = -25;
	orthoRight = 25;
	orthoBottom = -25;
	orthoTop = 25;

	projection_matrix = glm::perspective(FoV, aspectRatio, zNear, zFar);
	view_matrix = player_camera->getViewMatrix();


	L_eye_position = glm::vec3(0, 20, 50);
	L_light_position = glm::vec3(25, 100, 25);
	L_material_shininess = 30;
	L_material_kd = 0.5;
	L_material_ks = 0.5;

	L_model_matrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	L_view_matrix = glm::lookAt(L_eye_position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

float managers::CameraManager::getFrameTimeSeconds()
{
	return frameTime / 1000.0f;
}

void managers::CameraManager::computePerspectiveProjection()
{
	projection_matrix = glm::perspective(FoV, aspectRatio, zNear, zFar);
}

void managers::CameraManager::computeOrthograhicProjection()
{
	projection_matrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, 0.1f, 500.0f);
}

void managers::CameraManager::setProjectionMatrix(glm::mat4 &matrix)
{
	projection_matrix = matrix;
}

void managers::CameraManager::setViewMatrix(glm::mat4 &matrix)
{
	view_matrix = matrix;
}

glm::mat4 managers::CameraManager::getViewMatrix()
{
	return view_matrix;
}

glm::mat4 managers::CameraManager::getProjectionMatrix()
{
	return projection_matrix;
}
