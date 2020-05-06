#include "MapRenderer.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Loader.h"
#include "TileFactory.h"
#include "Tile.h"
#include "Program.h"
#include "Square.h"

const int NUMBER_OF_TILES = 5;
const float TILE_SIZE = 200.0f;
const int RENDER_SIZE = NUMBER_OF_TILES * (int) TILE_SIZE;

Map::MapRenderer::MapRenderer()
{

    loader = new Loader(false, false, 19, "http://a.tile.openstreetmap.fr/hot/", ".png", "./maps/");

    world = glm::ortho(0.0f, (float) RENDER_SIZE, 0.0f, (float) RENDER_SIZE, 0.1f, 100.0f);

    unsigned int TBO;
    unsigned int RBO;

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
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Tile *tile = TileFactory::instance()->get_tile_at(*loader, 5, 51.505, -0.09);
    for (int y = -NUMBER_OF_TILES/2; y < NUMBER_OF_TILES/2 + 1; ++y)
    {
        for (int x = -NUMBER_OF_TILES/2; x < NUMBER_OF_TILES/2 + 1; ++x)
        {
            Tile* current = tile->get(*loader, x, -y);
            current->position = Position(TILE_SIZE * (float) x + (RENDER_SIZE / 2) - TILE_SIZE / 2, TILE_SIZE * (float) y + (RENDER_SIZE / 2) - TILE_SIZE / 2, -1.0f);
            current->scale = Scale(TILE_SIZE, TILE_SIZE, 1);
            current->render(world);
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void Map::MapRenderer::update()
{
}

void Map::MapRenderer::handle_event(SDL_Event *event)
{
}
