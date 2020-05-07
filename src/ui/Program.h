#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <glm/glm.hpp>
#include <string>

class Program
{
public:

    Program(const std::string &vertex_shader, const std::string &fragment_shader);

    virtual ~Program();

    void use(const glm::mat4 &model, const glm::mat4 &projection, const glm::mat4 &view);

private:
    unsigned int program_id;
};


#endif //PROGRAM_H_
