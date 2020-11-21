#include "RegularPolygon.h"
#include <glad/glad.h>

Shape::RegularPolygon::RegularPolygon(ResourceCallback *creator, const std::string &name, Handler handler, RegularPolygonData data) :
	Mesh(creator, name, handler, data)
{}

Shape::RegularPolygon::RegularPolygon(ResourceCallback *creator, const std::string &name, Handler handler) :
	Mesh(creator, name, handler)
{}

Shape::RegularPolygon::~RegularPolygon()
{}

void Shape::RegularPolygon::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, data.sides * 3, GL_UNSIGNED_INT, 0);
}

void Shape::RegularPolygon::unready()
{}

void Shape::RegularPolygon::clear_out()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Shape::RegularPolygon::load_in()
{
	int sides = data.sides;
	float vertices[(sides + 1) * 5];
	int indices[sides * 3];
	float radius = data.radius;

	vertices[3] = 0.5f;
	vertices[4] = 0.5f;
	for(int i = 0; i < sides; ++i)
	{
		double angle = ((double)i/(double)sides) * 2.0 * M_PI;
		int pos = (i + 1) * 5;
		vertices[pos] = sin(angle) * radius;
		vertices[pos + 1] = cos(angle) * radius;
		vertices[pos + 2] = 0;
		vertices[pos + 3] = (sin(angle) + 1) / 2.0f;
		vertices[pos + 4] = (cos(angle) + 1) / 2.0f;

		int index_pos = i * 3;
		indices[index_pos] = 0;
		indices[index_pos + 1] = i + 1;
		indices[index_pos + 2] = i + 2;
	}
	indices[(sides * 3) - 1] = 1;

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

size_t Shape::RegularPolygon::check_size()
{
	return Mesh::check_size() + sizeof(VBO) + sizeof(VAO) + sizeof(EBO);
}

void Shape::RegularPolygon::prepare()
{}
