FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    cmake \
    zip \
    unzip \
    curl \
    git \
    autoconf \
    pkg-config

# install vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git /vcpkg
RUN /vcpkg/bootstrap-vcpkg.sh

# vcpkg toolchain file
ENV VCPKG_ROOT=/vcpkg
ENV CMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake

WORKDIR /app
COPY . .

# install vcpkg dependencies
RUN /vcpkg/vcpkg --feature-flags=manifests install

# build the app
RUN cmake -B build -S . \
    -D CMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake
RUN cmake --build build

# start the app
CMD ["./build/app/RestApp"]
