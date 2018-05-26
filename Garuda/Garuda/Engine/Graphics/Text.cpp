#include "Text.h"

Text::Text() 
{

}

Text::~Text()
{

}

void Text::Initialize() 
{
	mEngine = new Engine();
	InitText();
	program = mEngine->BuildShader("Engine/Graphics/Shaders/shader.vert", "Engine/Graphics/Shaders/shader.frag");
}

void Text::InitText() 
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		cout << "ERROR::FREETYPE: Inisialisasi Gagal" << endl;
	}

	FT_Face face;
	if (FT_New_Face(ft, "Assets/Font/Pixeled.ttf", 0, &face))
	{
		cout << "ERROR::FREETYPE: gagal memuat font" << endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 40);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		cout << "ERROR::FREETYPE: Gagal memuat glyph" << endl;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character =
		{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}


	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Text::RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color)
{
	// Activate corresponding render state;
	//glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "ourColor"), color.x, color.y, color.z);
	glUniform1i(glGetUniformLocation(program, "text"), 1);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 0);
	mat4 model;
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));
	glBindVertexArray(VAO);

	// Iterate through all characters
	string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];
		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;
		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;

		// Update VBO for each character

		GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },            
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }           
        };
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_QUADS, 0, 4);
		// Now advance cursors for next glyph (note that advance is number of 1 / 64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels(2 ^ 6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

GLuint Text::GetProgram() 
{
	return program;
}

void Text::Update() 
{

}
void Text::Render() 
{
}