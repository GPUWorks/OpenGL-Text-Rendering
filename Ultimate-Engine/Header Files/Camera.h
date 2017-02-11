#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>

#include <ICamera.h>


namespace camera {
	class Camera : public camera::ICamera
	{
		public:
			float distanceToTarget;
			glm::vec3 position;
			glm::vec3 forward;
			glm::vec3 right;
			glm::vec3 up;

		public:
			Camera();

			Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up);

			virtual ~Camera();

			virtual void set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up) override;

			virtual void moveForwardKeepOY(float distance) override;

			virtual void translateForward(float distance) override;
			virtual void translateUpword(float distance) override;
			virtual void translateRight(float distance) override;

			virtual glm::vec3 rotateOY(const glm::vec3 P, float radians);

			virtual void rotateTPS_OX(float angle);
			virtual void rotateTPS_OY(float angle);
			virtual void rotateTPS_OZ(float angle);

			virtual void rotateFPS_OX(float angle);
			virtual void rotateFPS_OY(float angle);
			virtual void rotateFPS_OZ(float angle);

			virtual glm::mat4 getViewMatrix() override;
			virtual glm::vec3 getTargetPosition() override;
			virtual glm::vec3 getPosition() override;
			virtual glm::vec3 getForward() override;
	};

	inline Camera::~Camera() { }
}