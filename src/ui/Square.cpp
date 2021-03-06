#include "Square.h"
#include <glad/glad.h>

Shape::Square::Square(ResourceCallback *creator, const std::string &name, Handler handler, float data)
		: Mesh(creator, name, handler, data)
{
}

Shape::Square::Square(ResourceCallback *creator, const std::string &name, Handler handler)
		: Mesh(creator, name, handler)
{
}

Shape::Square::~Square()
{
}

void Shape::Square::draw()
{
	if (!is_ready())
		return;

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Shape::Square::unready()
{
}

void Shape::Square::clear()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Shape::Square::load_in()
{
	float side_size = data;

	float vertices[] = {
		// positions and texture coords
		side_size / 2,
		side_size / 2,
		0.0f,
		1.0f,
		1.0f, // top right

		side_size / 2,
		-side_size / 2,
		0.0f,
		1.0f,
		0.0f, // bottom right

		-side_size / 2,
		-side_size / 2,
		0.0f,
		0.0f,
		0.0f, // bottom left

		-side_size / 2,
		side_size / 2,
		0.0f,
		0.0f,
		1.0f // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

size_t Shape::Square::check_size()
{
	return Mesh::check_size() + sizeof(VBO) + sizeof(VAO) + sizeof(EBO);
}

void Shape::Square::prepare()
{
}
