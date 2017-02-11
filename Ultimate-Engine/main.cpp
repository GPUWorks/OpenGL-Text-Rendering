/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include "Init_GLUT.h"
#include "SceneManager.h"
#include "WindowsManager.h"
#include "VertexFormat.h"
#include "CameraManager.h"


using namespace rendering::formats;

void windowMain(managers::SceneManager *scene)
{
	scene->getShaderManager()->createProgram("colorShader",
		"Resource Files\\Shader Files\\Vertex_Shader.glsl",
		"Resource Files\\Shader Files\\Fragment_Shader.glsl");

	managers::SceneManager::scene_manager = scene;

	managers::CameraManager::init();

	scene->getModelManager()->createModel(new rendering::models::Rectangle(), "rectangle_me", scene->getShaderManager()->getProgram("colorShader"));
	scene->getModelManager()->createModel(new rendering::models::Sun(), "world_sun_me", scene->getShaderManager()->getProgram("colorShader"));

	
	
}


int main(int argc, char **argv)
{
	core::info::WindowInfo window(std::string("OpenGL Window"), 0, 0, 800, 600, true);
	core::info::ContextInfo context(3, 3, true);
	core::info::FramebufferInfo frameBufferInfo(true, true, true, true);

	managers::windows::WindowsManager::create("window1", window, context, frameBufferInfo, windowMain);


	return 0;
}