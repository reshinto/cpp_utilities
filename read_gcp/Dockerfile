# Use a base image with a C++ compiler and curl installed
FROM ubuntu:20.04

# Set non-interactive installation mode
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary tools and dependencies
RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y cmake
RUN apt-get install -y git
RUN apt-get install -y curl
RUN apt-get install -y zip
RUN apt-get install -y unzip
RUN apt-get install -y tar
RUN apt-get install -y pkg-config
RUN apt-get install -y tzdata
RUN ln -fs /usr/share/zoneinfo/UTC /etc/localtime
RUN dpkg-reconfigure --frontend noninteractive tzdata
RUN apt-get install -y python3
RUN apt-get install -y python3-pip
RUN apt-get install -y python3-dev
RUN rm -rf /var/lib/apt/lists/*

# Install vcpkg
RUN git clone https://github.com/Microsoft/vcpkg.git /vcpkg \
    && /vcpkg/bootstrap-vcpkg.sh

# Install Google Cloud C++ Client Libraries using vcpkg
RUN /vcpkg/vcpkg install google-cloud-cpp

# Set the working directory in the container
WORKDIR /app

# Copy the C++ source code and CMakeLists.txt into the container
COPY main.cpp CMakeLists.txt /app/

# Compile the C++ program, specifying include and library paths
RUN cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake \
    && cmake --build build

# Run the program when the container starts
CMD ["./build/gcs_reader"]