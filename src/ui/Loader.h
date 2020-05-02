#ifndef LOADER_H_
#define LOADER_H_

#include <cstdint>
#include <string>

namespace Map
{
    class Tile;

    class Loader
    {
    public:
        Loader(bool tms, bool zxy, uint16_t max_zoom, const std::string &prefix, const std::string &extension,
               const std::string &dir);

        ~Loader();

        void load_image(Tile &tile);

        void open_image(Tile &tile);

        uint16_t get_max_zoom() const;

    private:
        Loader(const Loader &) = delete;

        static void start();

        static void stop();

        bool tms;
        bool zxy;
        uint16_t max_zoom;

        const std::string prefix;
        const std::string extension;
        const std::string dir;

        void download_image(Tile *tile);

        FILE *get_file(const std::string &filename) const;

        int download_file(const std::string &url, FILE *out, char *out_msg);


    };
}

#endif //LOADER_H_
