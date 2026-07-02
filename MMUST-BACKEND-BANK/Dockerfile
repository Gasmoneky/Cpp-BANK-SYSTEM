# Use the official Ubuntu base image
FROM ubuntu:24.04

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# 1. Install compilation tools, Git, Boost, and your mandatory dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libjsoncpp-dev \
    libuuid1 \
    uuid-dev \
    zlib1g-dev \
    libssl-dev \
    libboost-all-dev \
    libpq-dev \
    postgresql-server-dev-all \    
    && rm -rf /var/lib/apt/lists/*

# Set the working directory for our build process
WORKDIR /usr/src

# 2. Clone Drogon and all its required submodules directly into the image
RUN git clone --recursive https://github.com/drogonframework/drogon.git

# 3. Navigate to drogon, configure CMake for Debug mode, and build it
RUN cd drogon && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Debug .. && \
    make -j$(nproc) && \
    make install

# Set working directory back to a clean app space for your projects
WORKDIR /usr/src/app

# By default, drop into a bash terminal when the container runs
CMD ["/bin/bash"]
