#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <World.h>
#include "constants.h"
#include "WindowManager.h"
#include "SceneNode.h"
#include "Program.h"
#include "ProgramManager.h"

Renderer::Renderer()
{
	unsigned int TBO;
	unsigned int RBO;

	glGenFramebuffers(1, &frame);
	glBindFramebuffer(GL_FRAMEBUFFER, frame);

	glGenTextures(1, &TBO);
	glBindTexture(GL_TEXTURE_2D, TBO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FRAME_SIZE, FRAME_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TBO, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, FRAME_SIZE, FRAME_SIZE);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::begin()
{
	glViewport(0, 0, FRAME_SIZE, FRAME_SIZE);
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

void Renderer::setup_map()
{
	if (program == nullptr)
		program = ProgramManager::instance().create("tile");

	program->use(World::instance().get_matrix(), World::instance().get_view());
}

void Renderer::draw_node(SceneNode *node)
{
	program->set_matrix4(node->matrix(), "model");
	node->render();
}
