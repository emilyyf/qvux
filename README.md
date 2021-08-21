# qvux
Yet another useless operating system that will probably never be finished

## Prerequisites
- [Docker](https://www.docker.com/)
- [QEMU](https://www.qemu.org/)

## Setup
Build the docker image with:
- `docker build buildenv -t qvux`

## Build
Enter build environment:
- `docker run --rm -it -v '$pwd:/root/qvux' qvux`

Build the system with:
- `make all`

## Run
Run the system with:
- `qemu-system-x86_64 qvux.iso`