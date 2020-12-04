#include "ProgramManager.h"
#include "Program.h"
#include "Shaders.h"

IMPLEMENT_SINGLETON(ProgramManager)

ProgramManager::ProgramManager() : Singleton<ProgramManager>()
{
}

Program *ProgramManager::create(const std::string &name)
{
	const std::pair<Resource *, bool> &resource = ResourceManager::create_ou_retrieve(name);
	Program *program = dynamic_cast<Program *>(resource.first);
	if (resource.second) {
		ShaderPair &shader_source = shaders[name];
		program->set_vertex_shader_source(shader_source.first);
		program->set_fragment_shader_source(shader_source.second);
	}

	if (!program->is_ready()) {
		if (!program->is_loaded())
			program->load();
		program->ready();
	}
	return program;
}

Resource *ProgramManager::create(const std::string &name, Resource::Handler handler)
{
	return new Program(this, name, get_next_handler());
}
