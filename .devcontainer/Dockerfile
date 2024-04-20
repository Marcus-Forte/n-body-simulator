# Basic tools for C++ development.
FROM ubuntu:mantic

ARG DEBIAN_FRONTEND=interactive
RUN apt-get update && apt-get install -y git cmake build-essential \ 
 libgmock-dev clang-tidy clang-format \
 libeigen3-dev

WORKDIR /tmp

RUN git clone --recurse-submodules -b v1.62.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc && \
    mkdir -p grpc/build && cd grpc/build && \
    cmake .. -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF && \
    make -j8 install && \
    rm -rf /tmp/grpc