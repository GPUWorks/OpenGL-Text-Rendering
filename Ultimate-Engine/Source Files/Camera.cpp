#include <Camera.h>
#include <CameraManager.h>



camera::Camera::Camera()
{
	position = glm::vec3(0, 0, 1);
	forward = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(1, 0, 0);
	distanceToTarget = 0.8f;
}

camera::Camera::Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
{
	set(position, center, up);
}

void camera::Camera::set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
{
	this->position = position;
	forward = glm::normalize(center - position);
	right = glm::cross(forward, up);
	this->up = glm::cross(right, forward);
}

void camera::Camera::moveForwardKeepOY(float distance)
{
	glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	position = position + glm::normalize(dir) * distance;
}

void camera::Camera::translateForward(float distance)
{
	position = position + glm::normalize(forward) * distance;
}

void camera::Camera::translateUpword(float distance)
{
	position = position + glm::normalize(up) * distance;
}

void camera::Camera::translateRight(float distance)
{
	position = position + glm::normalize(right) * distance;
}

glm::vec3 camera::Camera::rotateOY(const glm::vec3 P, float radians)
{
	glm::vec3 R;
	R.x = P.x * cos(radians) - P.z * sin(radians);
	R.y = P.y;
	R.z = P.x * sin(radians) + P.z * cos(radians);

	return R;
}

void camera::Camera::rotateFPS_OX(float angle)
{
	glm::vec4 forward_aux = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1, 0, 0)) * glm::vec4(forward, 1.0);
	forward = glm::normalize(glm::vec3(forward_aux));
	up = glm::normalize(glm::cross(right, forward));
}

void camera::Camera::rotateFPS_OY(float angle)
{
	glm::vec4 forward_aux = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1.0);
	forward = glm::normalize(glm::vec3(forward_aux));

	glm::vec4 right_aux = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1.0);
	right = glm::normalize(glm::vec3(right_aux));

	up = glm::normalize(glm::cross(right, forward));
}

void camera::Camera::rotateFPS_OZ(float angle)
{
	glm::vec4 right_aux = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)) * glm::vec4(right, 1.0);
	right = glm::normalize(glm::vec3(right_aux));

	up = glm::normalize(glm::cross(right, forward));
}

void camera::Camera::rotateTPS_OX(float angle)
{
	translateForward(distanceToTarget);
	rotateFPS_OX(angle);
	translateForward(-distanceToTarget);
}

void camera::Camera::rotateTPS_OY(float angle)
{
	translateForward(distanceToTarget);
	rotateFPS_OY(angle);
	translateForward(-distanceToTarget);
}

void camera::Camera::rotateTPS_OZ(float angle)
{
	translateForward(distanceToTarget);
	rotateFPS_OZ(angle);
	translateForward(-distanceToTarget);
}

glm::mat4 camera::Camera::getViewMatrix()
{
	return glm::lookAt(position, position + forward, up);
}

glm::vec3 camera::Camera::getTargetPosition()
{
	glm::vec3 target_pos = position + forward * distanceToTarget;

	return target_pos;
}

glm::vec3 camera::Camera::getPosition()
{
	return position;
}

glm::vec3 camera::Camera::getForward()
{
	return forward;
}