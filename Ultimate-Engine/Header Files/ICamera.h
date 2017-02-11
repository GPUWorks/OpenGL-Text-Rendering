#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>


namespace camera {
	class ICamera {
		public:
			virtual ~ICamera() = 0;

			virtual void set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up) = 0;

			virtual void moveForwardKeepOY(float distance) = 0;

			virtual void translateForward(float distance) = 0;
			virtual void translateUpword(float distance) = 0;
			virtual void translateRight(float distance) = 0;

			virtual glm::vec3 rotateOY(const glm::vec3 P, float radians) = 0;

			virtual void rotateFPS_OX(float angle) = 0;
			virtual void rotateFPS_OY(float angle) = 0;
			virtual void rotateFPS_OZ(float angle) = 0;

			virtual void rotateTPS_OX(float angle) = 0;
			virtual void rotateTPS_OY(float angle) = 0;
			virtual void rotateTPS_OZ(float angle) = 0;

			virtual glm::mat4 getViewMatrix() = 0;
			virtual glm::vec3 getTargetPosition() = 0;
			virtual glm::vec3 getPosition() = 0;
			virtual glm::vec3 getForward() = 0;
	};

	inline ICamera::~ICamera() { }
}