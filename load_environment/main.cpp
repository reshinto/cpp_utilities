#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void load_dotenv(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening .env file" << std::endl;
        return;
    }

    while (getline(file, line)) {
        std::istringstream line_stream(line);
        std::string key;
        std::string value;

        if (std::getline(line_stream, key, '=') && std::getline(line_stream, value)) {
            setenv(key.c_str(), value.c_str(), 1); // Set or overwrite the environment variable
        }
    }

    file.close();
}

int main() {
    load_dotenv("myenvironments/.env"); // Load the .env file

    // Now you can use getenv to access the variables
    const char* my_env_var = getenv("DATA_FETCHER_GRPC_URL");
    if (my_env_var) {
        std::cout << "MY_ENV_VAR: " << my_env_var << std::endl;
    } else {
        std::cout << "MY_ENV_VAR is not set" << std::endl;
    }

    return 0;
}
