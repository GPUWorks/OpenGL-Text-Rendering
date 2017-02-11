#pragma once

#include <Camera.h>



namespace managers
{
	class CameraManager
	{
		public:
			static camera::Camera* player_camera;

			static unsigned int frameTime;
			static unsigned int previousTime;

			static glm::mat4 projection_matrix;
			static glm::mat4 view_matrix;
			static float FoV, zNear, zFar, aspectRatio;
			static float orthoLeft, orthoRight, orthoTop, orthoBottom;


			static void init();
			static float getFrameTimeSeconds();

			static void computePerspectiveProjection();
			static void computeOrthograhicProjection();

			static void setProjectionMatrix(glm::mat4 &matrix);
			static void setViewMatrix(glm::mat4 &matrix);

			static glm::mat4 getProjectionMatrix();
			static glm::mat4 getViewMatrix();


			static enum CameraState camera_state;
			static float rotation_angle;

			static int precision_factor;
			static float speed_by_precision;





			static glm::vec3 L_light_position;
			static glm::vec3 L_eye_position;
			static unsigned int L_material_shininess;
			static float L_material_kd;
			static float L_material_ks;

			static glm::mat4 L_model_matrix;
			static glm::mat4 L_view_matrix;
			static glm::mat4 L_projection_matrix;
	};

	enum CameraState
	{
		PLAYER_FOCUS,
		ROTATE_LEFT,
		ROTATE_RIGHT
	};
}