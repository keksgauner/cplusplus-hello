FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    zip \
    unzip \
    autoconf \
    pkg-config \ 
    && rm -rf /var/lib/apt/lists/*

# install vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git /vcpkg \
    && /vcpkg/bootstrap-vcpkg.sh

# vcpkg toolchain file
ENV VCPKG_ROOT=/vcpkg
ENV CMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake

WORKDIR /app
COPY . .

RUN /vcpkg/vcpkg --feature-flags=manifests install

RUN cmake -B build -S . \
    && cmake --build build

# test the app with 0.0.0.0:8080
CMD ["./build/app/RestApp", "0.0.0.0", "8080"]
