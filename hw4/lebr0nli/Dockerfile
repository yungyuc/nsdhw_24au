FROM ubuntu:22.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    curl vim \
    make cmake libc6-dev gcc g++ gfortran intel-mkl-full \
    python3 \
    python3-pip \
    python3-venv \
    python3-dev \
    && rm -rf /var/lib/apt/lists/*

ENV MKL_LIBS=/usr/lib/x86_64-linux-gnu/libmkl_def.so:/usr/lib/x86_64-linux-gnu/libmkl_avx2.so:/usr/lib/x86_64-linux-gnu/libmkl_core.so:/usr/lib/x86_64-linux-gnu/libmkl_intel_lp64.so:/usr/lib/x86_64-linux-gnu/libmkl_sequential.so
ENV LD_PRELOAD=${MKL_LIBS}

ENTRYPOINT [ "/bin/bash" ]
