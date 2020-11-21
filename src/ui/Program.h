#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <string>
#include "constants.h"
#include <types.h>
#include <Resource.h>

class Program : public Resource {
private:
	unsigned int program_id;
	unsigned int vertex_shader;
	unsigned int fragment_shader;
	std::string vertex_shader_source;
	std::string fragment_shader_source;

public:
	Program(ResourceCallback *creator, const std::string &name, Handler handler);

	virtual ~Program() = default;

	void use(const Projection &model, const Projection &projection, const Projection &view);

	void use(const Projection &projection, const Projection &view);

	void set_vertex_shader_source(const std::string &vertex_shader_source);

	void set_fragment_shader_source(const std::string &fragment_shader_source);

	void set_matrix4(const glm::mat4 &mat, const std::string &name);

	void set_vector4(const glm::vec4 &vec, const std::string &name);

protected:
	void unready() override;

	void clear_out() override;

	void load_in() override;

	size_t check_size() override;
	void prepare() override;
};

#endif //_PROGRAM_H_
