/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Model.h"


using namespace rendering;
using namespace models;

Model::Model() { }

Model::~Model()
{
	destroy();
}

void Model::create()
{
	//this is abstract, we don't continue to override this method
}

void Model::draw()
{
	//this is abstract, we don't continue to override this method
}

void Model::drawMini()
{
	//this is abstract, we don't continue to override this method
}

void Model::update()
{
	//this is abstract, we don't continue to override this method
}

void Model::setProgram(GLuint program)
{
	this->program = program;
}

const GLuint Model::getProgram()
{
	return this->program;
}

const GLuint Model::getVao() const
{
	return vao;
}

const std::vector<GLuint> Model::getIbos() const
{
	return ibos;
}

const std::vector<GLuint> Model::getVbos() const
{
	return vbos;
}

void Model::destroy()
{
	glDeleteVertexArrays(1, &vao);

	if (!ibos.empty())
	{
		glDeleteBuffers(ibos.size(), &ibos[0]);
		ibos.clear();
	}

	if (!vbos.empty())
	{
		glDeleteBuffers(vbos.size(), &vbos[0]);
		vbos.clear();
	}
}

unsigned int Model::loadTextureBMP(const std::string &filename) {

	unsigned int width, height;
	unsigned char* data = _loadBMPFile(filename, width, height);

	unsigned int gl_texture_object;
	glGenTextures(1, &gl_texture_object);
	glBindTexture(GL_TEXTURE_2D, gl_texture_object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	float maxAnisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	delete data;

	glGenerateMipmap(GL_TEXTURE_2D);

	return gl_texture_object;
}

unsigned char* Model::_loadBMPFile(const std::string &filename, unsigned int &width, unsigned int &height) {
	struct header {
		unsigned char type[2];
		int f_lenght;
		short rezerved1;
		short rezerved2;
		int offBits;
	};
	struct header_info {
		int size;
		int width;
		int height;
		short planes;
		short bitCount;
		int compresion;
		int sizeImage;
		int xPelsPerMeter;
		int yPelsPerMeter;
		int clrUsed;
		int clrImportant;
	};

	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file.good()) {
		std::cout << "Texture Loader: Nu am gasit fisierul bmp " << filename << " sau nu am drepturile sa il deschid!" << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}
	std::cout << "Texture Loader: Incarc fisierul " << filename << std::endl;


	header h; header_info h_info;
	file.read((char*)&(h.type[0]), sizeof(char));
	file.read((char*)&(h.type[1]), sizeof(char));
	file.read((char*)&(h.f_lenght), sizeof(int));
	file.read((char*)&(h.rezerved1), sizeof(short));
	file.read((char*)&(h.rezerved2), sizeof(short));
	file.read((char*)&(h.offBits), sizeof(int));
	file.read((char*)&(h_info), sizeof(header_info));

	unsigned char *data = new unsigned char[h_info.width*h_info.height * 3];

	long padd = 0;
	if ((h_info.width * 3) % 4 != 0) padd = 4 - (h_info.width * 3) % 4;

	width = h_info.width;
	height = h_info.height;

	long pointer;
	unsigned char r, g, b;

	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			file.read((char*)&b, 1);
			file.read((char*)&g, 1);
			file.read((char*)&r, 1);

			pointer = (i*width + j) * 3;
			data[pointer] = r;
			data[pointer + 1] = g;
			data[pointer + 2] = b;
		}

		file.seekg(padd, std::ios_base::cur);
	}
	file.close();

	return data;
}
