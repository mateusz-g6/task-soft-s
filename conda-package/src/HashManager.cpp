#include "HashManager.h"
#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <unordered_set>

// Constructor with default path
HashManager::HashManager(const string& defaultPath)
    : defaultPath(defaultPath) {}

// Public method to hash input
string HashManager::hashInput(const string& input) {
    return calculateHash(input);
}

// Public method to save entries to a file
bool HashManager::saveToFile(const string& path, const vector<Entry>& entries) {
    try {
        return writeToFile(path, entries);
    } catch (const runtime_error& e) {
        cerr << "Error saving file: " << e.what() << endl;
        return false;
    }
}

// Public method to load entries from a file
bool HashManager::loadFromFile(const string& path, vector<Entry>& entries) {
    try {
        return readFromFile(path, entries);
    } catch (const runtime_error& e) {
        cerr << "Error loading file: " << e.what() << endl;
        return false;
    }
}

// Private method to calculate SHA256 hash
string HashManager::calculateHash(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_ctx;

    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, input.c_str(), input.size());
    SHA256_Final(hash, &sha256_ctx);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

// Private method to write entries to a file
bool HashManager::writeToFile(const string& path, const vector<Entry>& entries) {
    // First, read the current entries from the file
    vector<Entry> existingEntries;
    readFromFile(path, existingEntries);

    ofstream file(path, ios::app);

    if (!file.is_open()) {
        throw runtime_error("Error opening file for writing!");
    }

    // Iterate through the new entries and add only unique ones
    for (const auto& entry : entries) {
        // Check if the entry already exists
        bool isDuplicate = false;
        for (const auto& existingEntry : existingEntries) {
            if (entry.id == existingEntry.id && entry.hash == existingEntry.hash) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            file << entry.id << "\t" << entry.input << "\t" << entry.hash << endl;
        }
    }

    return true;
}

// Private method to read entries from a file
bool HashManager::readFromFile(const string& path, vector<Entry>& entries) {
    ifstream file(path);

    // If file doesn't exist, create it
    if (!file.is_open()) {
        cerr << "File does not exist. Creating a new one." << endl;
        ofstream newFile(path);  // Create the file if it doesn't exist
        if (!newFile.is_open()) {
            throw runtime_error("Error opening file for reading and creating!");
        }
        return false;  // No entries to read, return false
    }

    Entry entry;
    unordered_set<string> seen; // Set to track seen hashes for deduplication
    while (file >> entry.id >> ws && getline(file, entry.input) && file >> entry.hash) {
        // Check for duplicate hashes
        if (seen.find(entry.hash) == seen.end()) {
            entries.push_back(entry);  // Only add if the hash is unique
            seen.insert(entry.hash);   // Mark this hash as seen
        }
    }

    return true;
}

// Public method to get the config path
string HashManager::getConfigPath() {
    return defaultPath;
}
