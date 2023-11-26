#include "google/cloud/storage/client.h"
#include <iostream>
#include <string>

google::cloud::StatusOr<google::cloud::storage::Client> CreateClient() {
    return google::cloud::storage::Client::CreateDefaultClient();
}

void ReadFileFromGCS(const std::string& bucket_name, const std::string& object_name) {
    auto client = CreateClient();
    if (!client) {
        std::cerr << "Failed to create Storage Client, status=" << client.status() << "\n";
        return;
    }

    google::cloud::storage::ObjectReadStream stream = client->ReadObject(bucket_name, object_name);

    if (!stream.status().ok()) {
        std::cerr << "Error reading object: " << stream.status() << "\n";
        return;
    }

    std::string line;
    while (std::getline(stream, line, '\n')) {
        std::cout << line << "\n";
    }
}

int main() {
    std::string bucket_name = "trades-ai-config";
    std::string object_name = "environments/.env";

    ReadFileFromGCS(bucket_name, object_name);

    return 0;
}
