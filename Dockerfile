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

WORKDIR /app
COPY . .

# install vcpkg
RUN git submodule init && \
    git submodule update
RUN ./vcpkg/bootstrap-vcpkg.sh

# install vcpkg dependencies
RUN ./vcpkg/vcpkg --feature-flags=manifests install

# build the app
RUN cmake -B build -S .
RUN cmake --build build

# start the app
CMD ["./build/app/RestApp"]
