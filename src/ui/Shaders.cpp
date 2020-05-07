#include "Shaders.h"

std::string tile_vertex_shader_source = "#version 330 core\n"
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

std::string tile_fragment_shader_source = "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D texture1;\n"
                                          "void main()\n"
                                          "{\n"
                                          "    FragColor = texture(texture1, TexCoord);\n"
                                          "}";