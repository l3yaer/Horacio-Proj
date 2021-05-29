# Horacio Project

![Linux](https://github.com/l3yaer/Horacio-Proj/workflows/Linux/badge.svg)

Horacio Project currently is a OSM slippymap software made with cpp.

## Requirements

* [glm](https://glm.g-truc.net/)
* [SDL2](https://www.libsdl.org/)
* [SDL2-Image](https://www.libsdl.org/)
* [curl](https://curl.haxx.se/)

## Windows Setup
For windows download and setup [vcpkg](https://vcpkg.io/en/getting-started.html) and install the dependencies:

```console
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
vcpkg install curl:x64-windows sdl2:x64-windows sdl2-image:x64-windows
vcpkg integrate install
```
Also don't forgget to change the CMake Generator in CMakeSettings.json to Visual Studio, for some reason ninja keeps crashing when generating the build files
## Installation

Use [CMake](https://cmake.org/) to install Horacio Project.

```bash
mkdir build
cd build
cmake ..
make
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
