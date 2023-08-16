FROM ubuntu:22.04

# Set environment variables to non-interactive (this prevents some prompts)
ENV DEBIAN_FRONTEND=noninteractive

# Install Clang, CMake, git, and other required tools
RUN apt-get update && apt-get install -y \
    clang \
    cmake \
    make \
    git \
    libstdc++-10-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Set the working directory 
WORKDIR /usr/src/graaf

# Copy the entire project to the working directory
COPY . .

# Build the project using CMake and Clang
RUN mkdir build && cd build && \
    cmake  -DBUILD_TESTS=True -DBUILD_EXAMPLES=True -DBUILD_BENCHMARKS=True .. && \
    cmake --build .

CMD ["/bin/bash"]
