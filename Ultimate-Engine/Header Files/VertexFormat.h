/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <glm\glm.hpp>


namespace rendering
{
	namespace formats
	{
		class VertexFormat
		{
			public:
				glm::vec4 position;
				glm::vec4 color;
				glm::vec3 normal;
				glm::vec2 texcoord;

				glm::vec4 position1;
				glm::vec4 position2;
				glm::vec4 position3;
				glm::vec4 position4;

				VertexFormat();
				VertexFormat(const glm::vec4 &iPos);
				VertexFormat(const glm::vec4 &iPos, const glm::vec4 &iColor);
				VertexFormat(const glm::vec4 &iPos, const glm::vec4 &iColor, const glm::vec2 &texcoord);

				void setPosition(glm::vec4 position);
				void setColor(glm::vec4 color);

				glm::vec4 getPosition();
				glm::vec4 getColor();

				float get_X();
				float get_Y();
		};
	}
}
