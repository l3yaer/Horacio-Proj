#include "MapRenderer.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Loader.h"
#include "TileFactory.h"
#include "Tile.h"
#include "Program.h"
#include "Square.h"

std::string vertex_shader_source = "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "layout (location = 1) in vec2 aTexCoord;\n"
                                   "out vec3 ourColor;\n"
                                   "out vec2 TexCoord;\n"
                                   "uniform mat4 model;\n"
                                   "uniform mat4 projection;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   gl_Position = projection * model * vec4(aPos, 1.0);\n"
                                   "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
                                   "}";

std::string fragment_shader_source = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "in vec2 TexCoord;\n"
                                     "uniform sampler2D texture1;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    FragColor = texture(texture1, TexCoord);\n"
                                     "}";


Map::MapRenderer::MapRenderer()
{

    loader = new Loader(false, false, 19, "http://a.tile.openstreetmap.fr/hot/", ".png", "./maps/");

    world = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    program = new Program(vertex_shader_source, fragment_shader_source);

    square = new Shape::Square(1.0f);

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &TBO);
    glBindTexture(GL_TEXTURE_2D, TBO);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TBO, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Map::MapRenderer::render()
{
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(200.0f, 200.0f, -1.0f));
    trans = glm::scale(trans, glm::vec3(100, 100, 1));

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Tile *current = TileFactory::instance()->get_tile_at(*loader, 5, 51.505, -0.09);
    current->texture->use();
    program->use(trans, world);
    square->render();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void Map::MapRenderer::update()
{
}

void Map::MapRenderer::handle_event(SDL_Event *event)
{
}
