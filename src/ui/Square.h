#ifndef SQUARE_H_
#define SQUARE_H_

namespace Shape
{
    class Square
    {
    public:
        Square(float side_size);

        virtual ~Square();

        void render();

    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    };
}


#endif //SQUARE_H_
