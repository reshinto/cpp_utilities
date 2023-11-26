cmake_minimum_required(VERSION 3.0)
project(GCSReader)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)

# Find the google cloud cpp storage package
find_package(google_cloud_cpp_storage REQUIRED)

# Add executable
add_executable(gcs_reader main.cpp)

# Link libraries
target_link_libraries(gcs_reader google-cloud-cpp::storage)
