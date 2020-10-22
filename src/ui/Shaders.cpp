#include "Shaders.h"

std::string basic_vertex_shader_source = "#version 330 core\n"
										 "layout (location = 0) in vec3 aPos;\n"
										 "layout (location = 1) in vec2 aTexCoord;\n"
										 "out vec3 ourColor;\n"
										 "out vec2 TexCoord;\n"
										 "uniform mat4 model;\n"
										 "uniform mat4 view;\n"
										 "uniform mat4 projection;\n"
										 "void main()\n"
										 "{\n"
										 "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
										 "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
										 "}";

std::string basic_fragment_shader_source = "#version 330 core\n"
										   "out vec4 FragColor;\n"
										   "in vec2 TexCoord;\n"
										   "uniform sampler2D texture1;\n"
										   "void main()\n"
										   "{\n"
										   "    vec4 texColor = texture(texture1, TexCoord);"
										   "		if(texColor.a < 0.1)\n"
										   "      discard;"
										   "    FragColor = texColor;\n"
										   "}";

std::string debug_square_vertex_shader_source = "#version 330 core\n"
												"layout (location = 0) in vec3 aPos;\n"
												"uniform mat4 model;\n"
												"uniform mat4 view;\n"
												"uniform mat4 projection;\n"
												"void main()\n"
												"{\n"
												"   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
												"}";

std::string debug_square_fragment_shader_source = "#version 330 core\n"
												  "out vec4 FragColor;\n"
												  "void main()\n"
												  "{\n"
												  "    FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
												  "}";

std::map<std::string, ShaderPair> shaders = {
	{ "tile", { basic_vertex_shader_source, basic_fragment_shader_source } },
	{ "actor", { basic_vertex_shader_source, basic_fragment_shader_source } },
	{ "debug square", { debug_square_vertex_shader_source, debug_square_fragment_shader_source } }
};