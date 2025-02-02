FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
                        build-essential \
                        cmake \
                        gcc-arm-none-eabi \
                        gdb \
                        git

RUN ln -s -f gcc-12 /usr/bin/gcc
