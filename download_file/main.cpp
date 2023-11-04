#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

// Callback function writes data to a std::ostream
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp) {
    if(userp) {
        std::ostream& os = *static_cast<std::ostream*>(userp);
        std::streamsize len = size * nmemb;
        if(os.write(static_cast<char*>(buf), len))
            return len;
    }

    return 0;
}

// Helper function to download a file using libcurl
CURLcode curl_read(const std::string& url, std::ostream& os, long timeout = 30) {
    CURLcode code(CURLE_FAILED_INIT);
    CURL* curl = curl_easy_init();

    if(curl) {
        if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write)) &&
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

    // Download to a file
    std::ofstream file("OOP.md");
    if(CURLE_OK == curl_read(url, file)) {
        // File successfully downloaded
        file.close();
        // Open the file again for reading
        std::ifstream file("OOP.md");
        std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        // Print the file contents
        std::cout << content << std::endl;
    } else {
        std::cerr << "Error: File could not be downloaded" << std::endl;
    }
    
    return 0;
}
