#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <thread>
#include <mutex>

using namespace std;
namespace fs = filesystem;

class CustomShell {
private:
    string current_directory;
    mutex mtx; // Mutex for protecting shared resources in multi-threading

public:
    string getCurrentDirectory() {
        return current_directory;
    }

    CustomShell() {
        current_directory = fs::current_path().string();
    }

    void changeDirectory(const vector<string>& parameters) {
        if (parameters.size() > 0) {
            string path = parameters[0];

            for (size_t i = 1; i < parameters.size(); ++i) {
                if (parameters[i] == "-l" || parameters[i] == "--long") {
                    cout << "Full path: " << fs::absolute(path) << endl;
                } else if (parameters[i] == "-r" || parameters[i] == "--relative") {
                    cout << "Relative path: " << fs::relative(fs::path(path), fs::path(current_directory)) << endl;
                } else if (parameters[i] == "-h" || parameters[i] == "--help") {
                    cout << "cd <directory> : Change directory" << endl;
                    cout << "Options:" << endl;
                    cout << "-l, --long: Display full path" << endl;
                    cout << "-r, --relative: Show relative path" << endl;
                    cout << "-h, --help: Display help information" << endl;
                }
            }

            try {
                fs::current_path(path);
                current_directory = fs::current_path().string();
            } catch (exception& e) {
                cout << "Directory not found." << endl;
            }
        } else {
            cout << "Please provide a directory." << endl;
        }
    }

    void moveFile(const vector<string>& parameters) {
        string source, destination;

        for (size_t i = 0; i < parameters.size(); ++i) {
            if (parameters[i] == "-i" || parameters[i] == "--interactive") {
                // Implement interactive mode
            } else if (parameters[i] == "-b" || parameters[i] == "--backup") {
                // Implement backup option
            } else if (parameters[i] == "-r" || parameters[i] == "--recursive") {
                // Implement recursive move
            } else if (parameters[i] == "-h" || parameters[i] == "--help") {
                cout << "mv <source> <destination> : Move file" << endl;
                cout << "Options:" << endl;
                cout << "-i, --interactive: Prompt before overwriting" << endl;
                cout << "-b, --backup: Create backup copies" << endl;
                cout << "-r, --recursive: Recursively move" << endl;
                cout << "-h, --help: Display help information" << endl;
            } else {
                if (source.empty()) {
                    source = parameters[i];
                } else if (destination.empty()) {
                    destination = parameters[i];
                }
            }
        }

        try {
            fs::path sourcePath(source);
            fs::path destPath(destination);

            // Multi-threaded move operation
            thread t1(&CustomShell::moveFileThread, this, sourcePath, destPath);
            t1.join();

            cout << "File or directory moved successfully." << endl;
        } catch (exception& e) {
            cout << "File or directory not found or permission denied." << endl;
        }
    }

    // Multi-threaded moveFileThread method
    void moveFileThread(const fs::path& source, const fs::path& destination) {
        lock_guard<mutex> lock(mtx); // Lock to ensure thread safety

        fs::rename(source, destination);
    }

    void removeFile(const vector<string>& parameters) {
        string filename;
        bool recursive = false;

        for (size_t i = 0; i < parameters.size(); ++i) {
            if (parameters[i] == "-i" || parameters[i] == "--interactive") {
                // Implement interactive mode
            } else if (parameters[i] == "-r" || parameters[i] == "--recursive") {
                recursive = true;
            } else if (parameters[i] == "-f" || parameters[i] == "--force") {
                // Implement force option
            } else if (parameters[i] == "-h" || parameters[i] == "--help") {
                cout << "rm <file/dir> [-r] : Remove file/directory (-r for recursive deletion)" << endl;
                cout << "Options:" << endl;
                cout << "-i, --interactive: Prompt before removing" << endl;
                cout << "-r, --recursive: Recursively remove" << endl;
                cout << "-f, --force: Ignore nonexistent files" << endl;
                cout << "-h, --help: Display help information" << endl;
            } else {
                filename = parameters[i];
            }
        }

        try {
            // Multi-threaded remove operation
            thread t1(&CustomShell::removeFileThread, this, filename, recursive);
            t1.join();

            cout << "File(s) removed successfully." << endl;
        } catch (exception& e) {
            cout << "File not found or permission denied." << endl;
        }
    }

    // Multi-threaded removeFileThread method
    void removeFileThread(const string& filename, bool recursive) {
        lock_guard<mutex> lock(mtx); // Lock to ensure thread safety

        if (recursive) {
            fs::remove_all(filename);
        } else {
            fs::remove(filename);
        }
    }

    void listDirectory(const vector<string>& parameters) {
        // Implement options for ls command
        // ...
        // Multi-threaded list operation
        thread t1(&CustomShell::listDirectoryThread, this, parameters);
        t1.join();
    }

    // Multi-threaded listDirectoryThread method
    void listDirectoryThread(const vector<string>& parameters) {
        lock_guard<mutex> lock(mtx); // Lock to ensure thread safety

        for (const auto& entry : fs::directory_iterator(current_directory)) {
            cout << entry.path().filename().string() << endl;
        }
    }

    void copyFile(const vector<string>& parameters) {
        string source, destination;

        for (size_t i = 0; i < parameters.size(); ++i) {
            if (parameters[i] == "-i" || parameters[i] == "--interactive") {
                // Implement interactive mode
            } else if (parameters[i] == "-b" || parameters[i] == "--backup") {
                // Implement backup option
            } else if (parameters[i] == "-r" || parameters[i] == "--recursive") {
                // Implement recursive copy
            } else if (parameters[i] == "-h" || parameters[i] == "--help") {
                cout << "cp <source> <destination> : Copy file" << endl;
                cout << "Options:" << endl;
                cout << "-i, --interactive: Prompt before overwriting" << endl;
                cout << "-b, --backup: Create backup copies" << endl;
                cout << "-r, --recursive: Recursively copy" << endl;
                cout << "-h, --help: Display help information" << endl;
            } else {
                if (source.empty()) {
                    source = parameters[i];
                } else if (destination.empty()) {
                    destination = parameters[i];
                }
            }
        }

        try {
            fs::path sourcePath(source);
            fs::path destPath(destination);

            // Multi-threaded copy operation
            thread t1(&CustomShell::copyFileThread, this, sourcePath, destPath);
            t1.detach();  // Detach the thread, allowing it to run independently

            cout << "File copy in progress. You can continue using the shell." << endl;
        } catch (exception& e) {
            cout << "File not found or permission denied." << endl;
        }
    }

    // Multi-threaded copyFileThread method
    void copyFileThread(const fs::path& source, const fs::path& destination) {
        lock_guard<mutex> lock(mtx); // Lock to ensure thread safety

        try {
            fs::copy(source, destination);
            cout << "File copied successfully." << endl;
        } catch (exception& e) {
            cout << "Error copying file: " << e.what() << endl;
        }
    }

    void showHelp() {
        cout << "Available commands:" << endl;
        cout << "cd <directory> : Change directory" << endl;
        cout << "mv <source> <destination> : Move file" << endl;
        cout << "rm <file/dir> [-r] : Remove file/directory (-r for recursive deletion)" << endl;
        cout << "ls : List directory contents" << endl;
        cout << "cp <source> <destination> : Copy file" << endl;
        cout << "help : Show available commands" << endl;
        cout << "exit : Exit the shell" << endl;
    }

    void executeCommand(const vector<string>& args) {
        if (args.empty()) {
            cout << "Please enter a command." << endl;
            return;
        }

        string command = args[0];
        vector<string> parameters(args.begin() + 1, args.end());

        if (command == "cd") {
            changeDirectory(parameters);
        } else if (command == "mv") {
            moveFile(parameters);
        } else if (command == "rm") {
            removeFile(parameters);
        } else if (command == "ls") {
            listDirectory(parameters);
        } else if (command == "cp") {
            copyFile(parameters);
        } else if (command == "help") {
            showHelp();
        } else if (command == "exit") {
            cout << "Exiting the shell." << endl;
            exit(0);
        } else {
            cout << "Command not recognized. Type 'help' for available commands." << endl;
        }
    }
};

int main() {
    CustomShell shell;

    while (true) {
        cout << shell.getCurrentDirectory() << " $ ";
        string input;
        getline(cin, input);

        istringstream iss(input);
        vector<string> args(istream_iterator<string>{iss}, istream_iterator<string>());

        shell.executeCommand(args);
    }

    return 0;
}
