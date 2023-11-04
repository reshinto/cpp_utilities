# Use a base image with a C++ build environment
FROM gcc:latest

# Set the working directory in the container
WORKDIR /usr/src/myapp

# Copy the current directory contents into the container at /usr/src/myapp
COPY . .

# Compile the C++ program
RUN g++ -std=c++14 -o myapp main.cpp

# Run the program when the container launches
CMD ["./myapp"]