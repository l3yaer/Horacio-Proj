#ifndef TEXTURE_H_
#define TEXTURE_H_


class Texture
{
public:
    unsigned int id;
    int width;
    int height;
    unsigned int format;
    int internal_format;

    Texture();

    virtual ~Texture();

    void create(bool discard_pixels = true);

    void set_pixels(void *source, unsigned bytes_per_row);

    void use();

    bool valid();

private:
    void *pixels;
};


#endif //TEXTURE_H_
