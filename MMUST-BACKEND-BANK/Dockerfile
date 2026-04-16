FROM fedora:43

RUN dnf install -y git cmake gcc-c++ jsoncpp-devel \
    libuuid-devel zlib-devel openssl-devel postgresql-devel \
    sqlite-devel hiredis-devel make

RUN git clone https://github.com/drogonframework/drogon && \
    cd drogon && \
    git submodule update --init && \
    mkdir build && cd build && \
    cmake .. && make -j$(nproc) && make install

WORKDIR /app

EXPOSE 8080

CMD ["tail", "-f", "/dev/null"]
