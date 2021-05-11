FROM       32bit/ubuntu:16.04
MAINTAINER Hyungjoon Koo (kevin.koo@skku.edu)

RUN apt-get -y update && apt-get install -y \
    git \
    texinfo \
    byacc \
    flex \
    bison \
    automake \
    autoconf \
    build-essential \
    libtool \
    cmake \
    gawk \
    python \
    python-dev \
    wget \
    elfutils \
    sudo \
    python-pip \
    gdb

RUN pip install pyelftools 
RUN git clone https://github.com/longld/peda.git ~/peda
RUN echo "source ~/peda/peda.py" >> ~/.gdbinit
RUN echo "[ES4010] docker ready!"

