# vcmp-python-plugin
Python binding plugin for VC:MP.

# Building
This project uses [CMake](https://cmake.org/) build system.

## Cloning
This project includes `pybind11` submodule, use:

`git clone --recursive https://github.com/ysc3839/vcmp-python-plugin.git`

## Linux
You need to install `python-dev` or `python3-dev` and `camke`.

On Debian-like systems just run:
`sudo apt install python3-dev cmake`

After installation, run:
```sh
mkdir build
cd build
cmake ..
make
```

## Windows
Download & install [CMake](https://cmake.org/download/) and [Python](https://www.python.org/downloads/).

After installation, run:
```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
Or you can open generated solution files in Visual Studio.
