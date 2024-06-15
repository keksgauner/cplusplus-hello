# RestApp

## Stack
- [docker](https://www.docker.com/)
- [cmake](https://cmake.org/download/)
- [beast](https://github.com/boostorg/beast)
- [jwt-cpp](https://github.com/Thalhammer/jwt-cpp)
- [sqlpp11](https://github.com/rbock/sqlpp11)


## Getting Started
Install requirements on a Ubuntu/Debian system 
```bash
sudo apt install build-essential cmake git curl zip unzip autoconf
```

Clone the repo with the `--recurse-submodules` flag
```bash
git clone --recurse-submodules https://github.com/keksgauner/cplusplus-rest
```  

Run `./vcpkg/bootstrap-vcpkg.sh` or `.\vcpkg\bootstrap-vcpkg.bat`

Fetch the dependencies (see [vcpkg.json](vcpkg.json)):  
(_This is optional, CMake should run `vcpkg install` anyway_)
```bash
./vcpkg/vcpkg --feature-flags=manifests install
```

Build the project using your IDE/build tool of choice or manually:

```bash
cmake -B build -S .
```
```bash
cmake --build build
```

## Docker

```bash
docker build -f Dockerfile.base -t ubuntubase .
```

## For CLion users
To avoid long file indexing, you might want to exclude the `vcpkg` directory:
1. Right click on `vcpkg` in the Project window
2. Mark Directory as -> _Library Files_ or _Excluded_ (I recommend choosing the latter)