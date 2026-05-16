FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive \
    TZ=Asia/Tokyo

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        make \
        valgrind \
        libc6-dbg \
        gdb \
        ca-certificates \
        bash \
        less \
        vim-tiny \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work

CMD ["/bin/bash"]
