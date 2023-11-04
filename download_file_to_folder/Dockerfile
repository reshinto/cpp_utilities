# Use a base image with a C++ compiler and curl installed
FROM ubuntu:latest

# Install necessary packages
RUN apt-get update && \
    apt-get install -y g++ curl libcurl4-openssl-dev

# Copy the C++ source code into the container
COPY main.cpp /main.cpp

# Compile the C++ program
RUN g++ -o main /main.cpp -lcurl

# Run the program when the container starts, downloading the file and printing its contents
CMD ["./main"]
