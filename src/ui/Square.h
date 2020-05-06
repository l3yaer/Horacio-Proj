#ifndef SQUARE_H_
#define SQUARE_H_

#include "Mesh.h"

namespace Shape
{
    class Square : public Mesh
    {
    public:
        Square(float side_size);

        virtual ~Square();

        void draw() override;

    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    };
}


#endif //SQUARE_H_
