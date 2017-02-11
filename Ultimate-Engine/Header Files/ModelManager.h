/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <unordered_map>

#include "ShaderManager.h"
#include "IModel.h"

#include <glm\glm.hpp>


namespace managers
{
	class ModelManager
	{
		public:
			ModelManager();
			~ModelManager();

			void ModelManager::createModel(
				rendering::interfaces::IModel* model,
				std::string modelName, 
				GLuint shader);
			void draw();
			void drawMini();
			void update();
			void deleteModel(const std::string& gameModelName);
			const rendering::interfaces::IModel& getModel(const std::string& gameModelName) const;

			static glm::mat4 translate(float tx, float ty, float tz);
			static glm::mat4 translateX(float t);
			static glm::mat4 translateY(float t);
			static glm::mat4 translateZ(float t);
			static glm::mat4 rotateX(float r);
			static glm::mat4 rotateY(float r);
			static glm::mat4 rotateZ(float r);
			static glm::mat4 scale(float sx, float sy, float sz);
			static glm::mat4 scaleX(float s);
			static glm::mat4 scaleY(float s);
			static glm::mat4 scaleZ(float s);

		private:
			std::map<std::string, rendering::interfaces::IModel*> modelList;
	};
}
