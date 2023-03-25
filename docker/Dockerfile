FROM ubuntu:20.04

ARG BRANCH_OR_TAG=main
ARG CMAKE_OPTIONS=
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    g++ \
    iproute2 \
    iputils-ping net-tools \
    make \
    netcat-openbsd \
    vim \
    sudo

# install google test
RUN git clone --depth=1 -b $BRANCH_OR_TAG -q https://github.com/google/googletest.git /googletest
RUN mkdir -p /googletest/build
WORKDIR /googletest/build
RUN cmake .. ${CMAKE_OPTIONS} && make && make install
WORKDIR /workspace
RUN rm -rf /googletest