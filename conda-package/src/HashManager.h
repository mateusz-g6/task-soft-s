#pragma once
#include <string>
#include <vector>
using namespace std;


// Structure to store hashed data
struct Entry {
    int id;                // Unique identifier for the entry
    string input;     // Original input string
    string hash;      // SHA-256 hash of the input string
};

// Class for managing hashing and file operations
class HashManager {
public:
    // Constructor with default path
    HashManager(const string& defaultPath = "hashes.txt");

    // Public methods to hash input, save and load entries
    string hashInput(const string& input);  // Hash the input string
    bool saveToFile(const string& path, const vector<Entry>& entries);  // Save entries to a file
    bool loadFromFile(const string& path, vector<Entry>& entries);  // Load entries from a file
    string getConfigPath();  // Get the config file path

private:
    string defaultPath;  // Default path for the hash entries file

    // Private helper methods
    string calculateHash(const string& input);  // Calculate SHA-256 hash for the input
    bool writeToFile(const string& path, const vector<Entry>& entries);  // Write entries to the file
    bool readFromFile(const string& path, vector<Entry>& entries);  // Read entries from the file
};
