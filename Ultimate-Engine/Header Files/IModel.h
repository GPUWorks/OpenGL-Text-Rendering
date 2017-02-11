/*-----------------------------------------------------------------------------
Author: B�rzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <vector>
#include <iostream>

#include <glew\glew.h>
#include <freeglut\freeglut.h>

#include "VertexFormat.h"


namespace rendering
{
	namespace interfaces
	{
		class IModel
		{
			public:
				virtual ~IModel() = 0;

				virtual void create() = 0;
				virtual void draw() = 0;
				virtual void drawMini() = 0;
				virtual void update() = 0;
				virtual void setProgram(GLuint shaderName) = 0;
				virtual const GLuint getProgram() = 0;
				virtual void destroy() = 0;

				virtual GLuint generateVBO() = 0;
				virtual GLuint generateIBO() = 0;
				virtual GLuint generateVAO() = 0;

				virtual const GLuint getVao()				const = 0;
				virtual const std::vector<GLuint> getIbos() const = 0;
				virtual const std::vector<GLuint> getVbos() const = 0;

				virtual void setModelMatrix() = 0;
				virtual void setModelMatrixMini() = 0;

				virtual void bindShaderInputData() = 0;

				glm::vec3 pos;
				glm::vec3 scale;
				std::string name;

				bool left_rotation;
				bool right_rotation;
				bool deadly_collision;

				bool active_left_rotation;
				bool active_right_rotation;

				bool* initial_status;

				bool is_next_left;
				bool is_next_right;
		};

		inline IModel::~IModel() { }
	}
}
