
#include "main.h"
#include "HashManager.h"


using namespace std;


int main() {
    HashManager hashManager;
    string path = hashManager.getConfigPath();
    vector<Entry> entries;

    while (true) {
        cout << "\nIf 'hashes.txt' does not exist in the current directory, it will be created." << endl;
        cout << "\nPlease choose an option:" << endl;
        cout << "1. Hash a password with SHA-256" << endl;
        cout << "2. Check database for a hash" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore(); // To ignore the newline left by the previous input

        switch (choice) {
            case 1: {
                // Hash a password
                hashManager.loadFromFile(path, entries);

                cout << "Enter a string to hash: ";
                string input;
                getline(cin, input);

                string hash = hashManager.hashInput(input);

                int id = entries.size() + 1;
                entries.push_back({id, input, hash});

                if (hashManager.saveToFile(path, entries)) {
                    cout << "Hash saved successfully!" << endl;
                }
                break;
            }

            case 2: {
                // Check the hash in the database
                hashManager.loadFromFile(path, entries);

                cout << "Enter a hash to search: ";
                string searchHash;
                getline(cin, searchHash);

                bool found = false;
                for (const auto& entry : entries) {
                    if (entry.hash == searchHash) {
                        cout << "Found entry with ID: " << entry.id 
                             << ", Input: " << entry.input << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Hash not found!" << endl;
                }
                break;
            }

            case 3:
                // Exit the program
                cout << "Exiting program..." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }
    }

    return 0;
}
