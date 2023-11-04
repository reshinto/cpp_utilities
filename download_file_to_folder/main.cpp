#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <sys/stat.h>
#include <sys/types.h>

// Callback function writes data to a std::ostream
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp) {
    if (userp) {
        std::ostream& os = *static_cast<std::ostream*>(userp);
        std::streamsize len = size * nmemb;
        if (os.write(static_cast<char*>(buf), len))
            return len;
    }

    return 0;
}

// Helper function to check if a directory exists and create it if it doesn't
bool check_and_create_directory(const std::string& name) {
    struct stat st = {0};

    if (stat(name.c_str(), &st) == -1) {
        // Directory does not exist, so try to create it
        if (mkdir(name.c_str(), 0700) == -1) {
            std::cerr << "Error: Unable to create directory " << name << std::endl;
            return false;
        }
    }
    return true; // Directory exists or was successfully created
}

// Helper function to download a file using libcurl
CURLcode curl_read(const std::string& url, std::ostream& os, long timeout = 30) {
    CURLcode code(CURLE_FAILED_INIT);
    CURL* curl = curl_easy_init();

    if (curl) {
        if (CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write)) &&
            CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L)) &&
            CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L)) &&
            CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os)) &&
            CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout)) &&
            CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str()))) {
            code = curl_easy_perform(curl);
        }
        curl_easy_cleanup(curl);
    }
    return code;
}

int main(void) {
    const std::string url = "https://raw.githubusercontent.com/reshinto/Basic_technologies_revision/master/basics/OOP.md";
    const std::string dir = "myrandomfolder/";
    const std::string filepath = dir + "OOP.md";

    // Check if temp directory exists, create it if not
    if (!check_and_create_directory(dir)) {
        return -1; // Return error if directory cannot be created
    }

    // Open the file within the temp directory for writing
    std::ofstream file(filepath);
    if (file) {
        if (CURLE_OK == curl_read(url, file)) {
            // File successfully downloaded
            file.close();
            // Open the file again for reading and print its contents
            std::ifstream infile(filepath);
            std::string content((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));
            std::cout << content << std::endl;
        } else {
            std::cerr << "Error: File could not be downloaded" << std::endl;
        }
    } else {
        std::cerr << "Error: Could not open file for writing" << std::endl;
    }

    return 0;
}
