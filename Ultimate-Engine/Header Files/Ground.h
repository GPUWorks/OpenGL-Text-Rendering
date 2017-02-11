/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include "Model.h"
#include "Camera.h"


namespace rendering
{
	namespace models
	{
		namespace world
		{
			class Ground : public rendering::models::Model
			{
			public:
				Ground();
				~Ground();

				void create();
				virtual void draw()   override final;
				virtual void drawMini()   override final;
				virtual void update() override final;

				virtual GLuint generateVBO()	override final;
				virtual GLuint generateIBO()	override final;
				virtual GLuint generateVAO()	override final;

				virtual void setModelMatrix() override final;
				virtual void setModelMatrixMini() override final;

				virtual void bindShaderInputData() override final;

				static float z_negative, z_positive;
				static float x_negative, x_positive;
			};
		}
	}
}
