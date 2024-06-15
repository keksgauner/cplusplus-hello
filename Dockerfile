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

# clone vcpkg
RUN git clone https://github.com/microsoft/vcpkg vcpkg

# install vcpkg and install dependencies
RUN ./vcpkg/bootstrap-vcpkg.sh
RUN ./vcpkg/vcpkg --feature-flags=manifests install

# build the app
RUN cmake -B build -S . \
    && cmake --build build

# start the app
CMD ["./build/app/RestApp"]
