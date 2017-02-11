/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Rectangle.h"
#include "ModelManager.h"
#include <CameraManager.h>
#include <glm/gtc/type_ptr.hpp>
#include <SceneManager.h>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;









static unsigned int wall_texture;

Rectangle::Rectangle() {
}

Rectangle::~Rectangle() { }

void Rectangle::create()
{
	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	bindShaderInputData();

	wall_texture = loadTextureBMP("Image Files\\wall.bmp");
}

GLuint Rectangle::generateVBO()
{
	GLuint vbo;

	std::vector<VertexFormat> vertices;

	VertexFormat* rectangle_back_left_up = new VertexFormat(glm::vec4(-0.10, 0.1, -0.10, 1), glm::vec4(0, 0, 1, 1), glm::vec2(0, 1));
	VertexFormat* rectangle_back_left_down = new VertexFormat(glm::vec4(-0.10, -0.1, -0.10, 1), glm::vec4(0, 0, 1, 1), glm::vec2(0, 0));
	VertexFormat* rectangle_back_right_down = new VertexFormat(glm::vec4(0.10, -0.1, -0.10, 1), glm::vec4(0, 0, 1, 1), glm::vec2(1, 0));
	VertexFormat* rectangle_back_right_up = new VertexFormat(glm::vec4(0.10, 0.1, -0.10, 1), glm::vec4(0, 0, 1, 1), glm::vec2(1, 1));

	VertexFormat* rectangle_left_up = new VertexFormat(glm::vec4(-0.10, 0.1, 0.10, 1), glm::vec4(0, 0, 1, 1), glm::vec2(0, 1));
	VertexFormat* rectangle_left_down = new VertexFormat(glm::vec4(-0.10, -0.1, 0.10, 1), glm::vec4(0, 0, 1, 1), glm::vec2(0, 0));
	VertexFormat* rectangle_right_down = new VertexFormat(glm::vec4(0.10, -0.1, 0.10, 1), glm::vec4(0, 0, 1, 1), glm::vec2(1, 0));
	VertexFormat* rectangle_right_up = new VertexFormat(glm::vec4(0.10, 0.1, 0.10, 1), glm::vec4(0, 0, 1, 1), glm::vec2(1, 1));


	vertices.push_back(*rectangle_back_left_up);
	vertices.push_back(*rectangle_back_left_down);
	vertices.push_back(*rectangle_back_right_down);
	vertices.push_back(*rectangle_back_right_up);

	vertices.push_back(*rectangle_left_up);
	vertices.push_back(*rectangle_left_down);
	vertices.push_back(*rectangle_right_down);
	vertices.push_back(*rectangle_right_up);



	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 8, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint Rectangle::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	//Back Face
	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(0);

	//Front Face
	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(6);
	indexes.push_back(6);
	indexes.push_back(7);
	indexes.push_back(4);

	//Up Face
	indexes.push_back(0);
	indexes.push_back(4);
	indexes.push_back(7);
	indexes.push_back(7);
	indexes.push_back(3);
	indexes.push_back(0);

	//Down Face
	indexes.push_back(1);
	indexes.push_back(5);
	indexes.push_back(6);
	indexes.push_back(6);
	indexes.push_back(2);
	indexes.push_back(1);

	//Left Face
	indexes.push_back(0);
	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(5);
	indexes.push_back(1);
	indexes.push_back(0);

	//Right Face
	indexes.push_back(3);
	indexes.push_back(7);
	indexes.push_back(6);
	indexes.push_back(6);
	indexes.push_back(2);
	indexes.push_back(3);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 36, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint Rectangle::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void Rectangle::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texcoord)));

	glBindVertexArray(0);
}

void Rectangle::setModelMatrix()
{
	glm::mat4 model_matrix = glm::mat4(1);
	model_matrix *= managers::ModelManager::translate(10.0f, 0.5f, 0.895f);
	model_matrix *= managers::ModelManager::scaleX(100.0f);
	model_matrix *= managers::ModelManager::scaleY(15.0f);

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, glm::value_ptr(CameraManager::getViewMatrix()));

	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, glm::value_ptr(CameraManager::getProjectionMatrix()));

	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, wall_texture);
	unsigned int locatie = glGetUniformLocation(program, "textura2");
	glUniform1i(locatie, 2);

	glUniform1i(glGetUniformLocation(program, "is_text"), 0);

}

void Rectangle::setModelMatrixMini()
{

}

void Rectangle::update()
{
}

void Rectangle::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Rectangle::drawMini()
{

}
