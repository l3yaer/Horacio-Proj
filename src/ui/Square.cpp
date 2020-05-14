#include "Square.h"
#include <glad/glad.h>

Shape::Square::Square (float side_size)
{
  float vertices[] = {
	  // positions                // texture coords
	  side_size, side_size, 0.0f, 1.0f, 1.0f,   // top right
	  side_size, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom right
	  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // bottom left
	  0.0f, side_size, 0.0f, 0.0f, 1.0f    // top left
  };
  unsigned int indices[] = {
	  0, 1, 3, // first triangle
	  1, 2, 3  // second triangle
  };
  glGenVertexArrays (1, &VAO);
  glGenBuffers (1, &VBO);
  glGenBuffers (1, &EBO);

  glBindVertexArray (VAO);

  glBindBuffer (GL_ARRAY_BUFFER, VBO);
  glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void *)0);
  glEnableVertexAttribArray (0);
  // texture coord attribute
  glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void *)(3 * sizeof (float)));
  glEnableVertexAttribArray (1);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer (GL_ARRAY_BUFFER, 0);

  // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray (0);
}

Shape::Square::~Square ()
{
  glDeleteVertexArrays (1, &VAO);
  glDeleteBuffers (1, &VBO);
  glDeleteBuffers (1, &EBO);
}

void Shape::Square::draw ()
{
  glBindVertexArray (VAO);
  glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

