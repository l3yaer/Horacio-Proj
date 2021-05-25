#include "Program.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Program::Program(ResourceCallback *creator, const std::string &name, Resource::Handler handler)
		: Resource(creator, name, handler)
{
}

void Program::use(const glm::mat4 &projection, const glm::mat4 &view)
{
	if(!is_ready())
		return;

	glUseProgram(program_id);
	set_matrix4(projection, "projection");
	set_matrix4(view, "view");
}

void Program::use(const glm::mat4 &model, const glm::mat4 &projection, const glm::mat4 &view)
{
	if(!is_ready())
		return;

	glUseProgram(program_id);
	set_matrix4(model, "model");
	set_matrix4(projection, "projection");
	set_matrix4(view, "view");
}

void Program::set_matrix4(const glm::mat4 &mat, const std::string &name)
{
	unsigned int mat_location = glGetUniformLocation(program_id, name.c_str());
	glUniformMatrix4fv(mat_location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Program::set_vector4(const glm::vec4 &vec, const std::string &name)
{
	unsigned int vec_location = glGetUniformLocation(program_id, name.c_str());
	glUniform4fv(vec_location, 1, glm::value_ptr(vec));
}

void Program::unready()
{
}

void Program::clear_out()
{
	glDeleteProgram(program_id);
}

void Program::load_in()
{
	int success;
	char info_log[512];

	const char *v_shader = vertex_shader_source.c_str();
	const char *f_shader = fragment_shader_source.c_str();

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &v_shader, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &f_shader, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}
}
void Program::prepare()
{
	int success;
	char info_log[512];
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader);
	glAttachShader(program_id, fragment_shader);
	glLinkProgram(program_id);

	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program_id, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}
size_t Program::check_size()
{
	return Resource::check_size() + vertex_shader_source.size() + fragment_shader_source.size();
}
void Program::set_vertex_shader_source(const std::string &vertex_shader_source)
{
	Program::vertex_shader_source = vertex_shader_source;
}
void Program::set_fragment_shader_source(const std::string &fragment_shader_source)
{
	Program::fragment_shader_source = fragment_shader_source;
}
