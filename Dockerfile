FROM base

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    cmake \
    zip \
    unzip \
    curl \
    git \
    autoconf

WORKDIR /app
COPY . .

# install vcpkg and install dependencies
RUN ./vcpkg/bootstrap-vcpkg.sh
RUN ./vcpkg/vcpkg --feature-flags=manifests install

# build the app
RUN cmake -B build -S . \
    && cmake --build build

# start the app
CMD ["./build/app/RestApp"]
