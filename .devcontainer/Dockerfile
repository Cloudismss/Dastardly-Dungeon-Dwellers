# Arch Linux base development package
FROM --platform=linux/amd64 archlinux:base-devel AS amd64

# Update distro and install C++ packages
RUN pacman -Syu  --noconfirm \
    git \
    gdb \
    gcc \
    clang \
    lldb \
    lldb-mi \
    ninja \
    cmake \
    cppcheck \
    valgrind \
    doxygen \
    bat \
    && pacman -Scc --noconfirm

# Copy local directory to docker container
COPY .. ./DDD

# Set docker container working directory
WORKDIR /DDD
