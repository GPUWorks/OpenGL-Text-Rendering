/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Sun.h"
#include "ModelManager.h"
#include <CameraManager.h>
#include <glm/gtc/type_ptr.hpp>
#include <SceneManager.h>

using namespace rendering;
using namespace models;
using namespace formats;
using namespace managers;







class Texture {
public:
	glm::vec2 right_up;
	glm::vec2 right_down;
	glm::vec2 left_up;
	glm::vec2 left_down;

	VertexFormat* right_u;
	VertexFormat* right_d;
	VertexFormat* left_u;
	VertexFormat* left_d;
};





static unsigned int earth_texture;
static unsigned int word_texture;
static std::map<char, Texture> texChar;


Sun::Sun() {
}

Sun::~Sun() { }

static int index = 0;

void Sun::create()
{
	char c = 32;

	for (float y = 1.0; y > 0.05; y -= 0.1) {
		for (float x = 0.0; x < 0.95; x += 0.1) {
			if (c > 126)
				break;

			Texture pos;
			pos.left_up = glm::vec2(x + 0.001, y - 0.001);
			pos.left_down = glm::vec2(x + 0.001, y - 0.1 + 0.002);
			pos.right_up = glm::vec2(x + 0.1 - 0.001, y - 0.001);
			pos.right_down = glm::vec2(x + 0.1 - 0.001, y - 0.1 + 0.002);

			texChar[c] = pos;

			c++;
		}
	}

	this->vao = generateVAO();
	this->vbos.push_back(generateVBO());
	this->ibos.push_back(generateIBO());

	index = vbos.size();

	bindShaderInputData();

	earth_texture = loadTextureBMP("Image Files\\lucidagrande2.bmp");
	word_texture = loadTextureBMP("Image Files\\wood.bmp");
}





static float start_x = 0.0f;
static float finish_x = 99.5f;

static float start_y = 0.0f;
static float finish_y = 1.5f;

static int no = 20;

static std::vector<VertexFormat> vertices;

static std::vector<Texture> allText;








GLuint Sun::generateVBO()
{
	GLuint vbo;

		for (float y = start_y; y < finish_y; y += 1.0f)
		{
			for (float x = start_x; x < finish_x; x += 1.0f)
			{
				VertexFormat* v1 = new VertexFormat(glm::vec4(x, y, 1, 1), glm::vec4(0.0, 0.0f, 1.0, 1));
				v1->normal = glm::vec3(0, 1, 0);
				vertices.push_back(*v1);

				VertexFormat* v2 = new VertexFormat(glm::vec4(x + 1.0f, y, 1, 1), glm::vec4(0.0, 0.0f, 1.0, 1));
				v2->normal = glm::vec3(0, 1, 0);
				vertices.push_back(*v2);
			}
		}

		char c1 = 32;

		for (int i = 0; i < 200; i += 200)
		{
			for (int j = 0; j < 200; j += 2)
			{
				Texture square;

				VertexFormat* v1 = &vertices.at(i + j);
				v1->texcoord = texChar[c1].left_down;
				square.left_d = v1;
			
				v1 = &vertices.at(i + j + 1);
				v1->texcoord = texChar[c1].right_down;
				square.right_d = v1;

				v1 = &vertices.at(i + j + 200);
				v1->texcoord = texChar[c1].left_up;
				square.left_u = v1;

				v1 = &vertices.at(i + j + 200 + 1);
				v1->texcoord = texChar[c1].right_up;
				square.right_u = v1;


				allText.push_back(square);
			}
		}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 400, &vertices[0], GL_STATIC_DRAW);

	return vbo;
}

GLuint Sun::generateIBO()
{
	GLuint ibo;

	std::vector<GLuint> indexes;

	for (int i = 0; i < 200; i += 200)
	{
		for (int j = 0; j < 200; j += 2)
		{
			indexes.push_back(i + j);
			indexes.push_back(i + j + 1);
			indexes.push_back(i + j + 200);

			indexes.push_back(i + j + 1);
			indexes.push_back(i + j + 200 + 1);
			indexes.push_back(i + j + 200);
		}
	}

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 1200, &indexes[0], GL_STATIC_DRAW);

	return ibo;
}

GLuint Sun::generateVAO()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return vao;
}

void Sun::bindShaderInputData()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texcoord)));

	glBindVertexArray(0);
}



static float translate_left = -22.0f;
static int text_length = 0;

bool is_Edit_Activated = false;

static float speed = 0.02f;
static float scaleSpeed = 1.1f;

void Sun::setModelMatrix()
{
	glm::mat4 model_matrix = glm::mat4(1);
	model_matrix *= managers::ModelManager::translateX(-translate_left);
	model_matrix *= managers::ModelManager::scale(1, scaleSpeed, 1);

	translate_left += speed;

	if (translate_left > text_length)
		translate_left = -22.0f;

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, glm::value_ptr(model_matrix));

	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, glm::value_ptr(CameraManager::getViewMatrix()));

	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, glm::value_ptr(CameraManager::getProjectionMatrix()));


	//send texture
	glActiveTexture(GL_TEXTURE0 + 3);
	glBindTexture(GL_TEXTURE_2D, earth_texture);
	unsigned int locatie = glGetUniformLocation(program, "textura1");
	glUniform1i(locatie, 3);

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, word_texture);
	locatie = glGetUniformLocation(program, "textura3");
	glUniform1i(locatie, 1);



	glUniform1i(glGetUniformLocation(program, "is_text"), 1);
	glUniform1f(glGetUniformLocation(program, "limit_left"), translate_left + 1.0);
	glUniform1f(glGetUniformLocation(program, "limit_right"), translate_left + 19.0);


	//modify size of text
	if (!is_Edit_Activated) {
		if (SceneManager::keyPressed == '+') {
			speed += 0.002f;
			SceneManager::keyPressed = 0;
		}
		else if (SceneManager::keyPressed == '-') {
			speed -= 0.002f;
			SceneManager::keyPressed = 0;
		}
	}

	if (managers::SceneManager::mouseScrool.x == 0) {
		if (managers::SceneManager::mouseScrool.y == 1) {
			scaleSpeed += 0.1f;
		}
		else if (managers::SceneManager::mouseScrool.y == -1) {
			scaleSpeed -= 0.1f;
		}

		managers::SceneManager::mouseScrool.y = 0;
	}
}

void Sun::setModelMatrixMini()
{

}





void Sun::update()
{
	glBindVertexArray(this->vao);

	// If editing is activated insert key in the text message
	if (is_Edit_Activated) {
		if (SceneManager::keyPressed >= 32 && SceneManager::keyPressed <= 126 && text_length < 97) {
			int i = text_length;

			allText.at(i).left_d->texcoord = texChar[SceneManager::keyPressed].left_down;
			allText.at(i).right_d->texcoord = texChar[SceneManager::keyPressed].right_down;
			allText.at(i).left_u->texcoord = texChar[SceneManager::keyPressed].left_up;
			allText.at(i).right_u->texcoord = texChar[SceneManager::keyPressed].right_up;

			text_length++;

			SceneManager::keyPressed = 0;
		}
	}

	// if backspace is pressed, remove a character
	if (SceneManager::keyPressed == 8) {
		if (text_length > 0) {
			int i = text_length - 1;

			allText.at(i).left_d->texcoord = glm::vec2();
			allText.at(i).right_d->texcoord = glm::vec2();
			allText.at(i).left_u->texcoord = glm::vec2();
			allText.at(i).right_u->texcoord = glm::vec2();

			text_length--;
		}

		SceneManager::keyPressed = 0;
	}

	// if Enter is pressed activate/deactivate editing text message
	if (SceneManager::keyPressed == 13) {
		if (is_Edit_Activated)
			is_Edit_Activated = false;
		else
			is_Edit_Activated = true;

		SceneManager::keyPressed = 0;
	}


	glBindBuffer(GL_ARRAY_BUFFER, this->vbos.at(index - 1));
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 400, &vertices[0], GL_STATIC_DRAW);

	bindShaderInputData();
}

void Sun::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	setModelMatrix();
	glDrawElements(GL_TRIANGLES, 1200, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sun::drawMini()
{

}
