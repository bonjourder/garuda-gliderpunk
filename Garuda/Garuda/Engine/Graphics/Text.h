#ifndef GARUDA_TEXT
#define GARUDA_TEXT

#include "../Engine.h"
#include "SOIL/src/SOIL.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <unordered_map>
#include <map>

#define FONTSIZE 48

using namespace std;
using namespace glm;

struct Character
{
	GLuint		TextureID;
	glm::ivec2	Size;
	glm::ivec2	Bearing;
	GLuint		Advance;
};

class Text 
{
public:

	Text();
	~Text();
	void Initialize();
	void InitText();
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	
	void Update();
	void Render();

	GLuint GetProgram();

	map<GLchar, Character> Characters;
private:
	Engine * mEngine;
	GLuint VAO, VBO, program;
	
};

#endif // !GARUDA_TEXT