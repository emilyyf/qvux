FROM ubuntu

RUN apt update
RUN apt upgrade -y
RUN apt install -y clang
RUN apt install -y lld
RUN apt install -y make
RUN apt install -y nasm
RUN apt install -y xorriso
RUN apt install -y grub-pc-bin
RUN apt install -y grub-common

VOLUME /root/qvux
WORKDIR /root/qvux
