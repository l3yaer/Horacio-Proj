#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <World.h>
#include <LogManager.h>
#include <SceneNode.h>
#include "constants.h"
#include "WindowManager.h"
#include "Program.h"
#include "ProgramManager.h"
#include "VectorArea.h"

Renderer::Renderer() : current_program(nullptr)
{
	unsigned int TBO;
	unsigned int RBO;

	glGenFramebuffers(1, &frame);
	glBindFramebuffer(GL_FRAMEBUFFER, frame);

	glGenTextures(1, &TBO);
	glBindTexture(GL_TEXTURE_2D, TBO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, MAP_WIDTH, MAP_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TBO, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, MAP_WIDTH, MAP_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::begin()
{
	glViewport(0, 0, MAP_WIDTH, MAP_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, frame);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::end()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glViewport(0, 0, WindowManager::instance().width, WindowManager::instance().height);
}

void Renderer::setup(Renderer::Programs program)
{
	current_program = ProgramManager::instance().create(program_name(program));
	current_program->use(World::instance().get_matrix(), World::instance().get_view());
}

void Renderer::draw_node(SceneNode &node)
{
	if(current_program)
		current_program->set_matrix4(node.matrix(), "model");
	node.render();
}

std::string Renderer::program_name(Renderer::Programs program) const
{
	switch(program)
	{
	case TILE:
		return "tile";
	case ACTOR:
		return "actor";
	case VECTOR:
		return "vector";
	}
	return "";
}

Program *Renderer::get_current_program()
{
	return current_program;
}
