#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;
namespace fs = filesystem;

class CustomShell {
private:
    string current_directory;

public:
    string getCurrentDirectory() {
        return current_directory;
    }

    CustomShell() {
        current_directory = fs::current_path().string();
    }

    void changeDirectory(const vector<string>& parameters) {
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

            fs::rename(sourcePath, destPath);
            cout << "File or directory moved successfully." << endl;
        } catch (exception& e) {
            cout << "File or directory not found or permission denied." << endl;
        }
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
            if (recursive) {
                fs::remove_all(filename);
            } else {
                fs::remove(filename);
            }
            cout << "File(s) removed successfully." << endl;
        } catch (exception& e) {
            cout << "File not found or permission denied." << endl;
        }
    }

    void listDirectory(const vector<string>& parameters) {
        // Implement options for ls command
        // ...
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
            fs::copy(source, destination);
            cout << "File copied successfully." << endl;
        } catch (exception& e) {
            cout << "File not found or permission denied." << endl;
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
            if (!parameters.empty()) {
                changeDirectory(parameters);
            } else {
                cout << "Please provide a directory." << endl;
            }
        } else if (command == "mv") {
            if (parameters.size() >= 2) {
                moveFile(parameters);
            } else {
                cout << "Usage: mv <source> <destination>" << endl;
            }
        } else if (command == "rm") {
            if (!parameters.empty()) {
                removeFile(parameters);
            } else {
                cout << "Please provide a file/directory." << endl;
            }
        } else if (command == "ls") {
            listDirectory(parameters);
        } else if (command == "cp") {
            if (parameters.size() >= 2) {
                copyFile(parameters);
            } else {
                cout << "Usage: cp <source> <destination>" << endl;
            }
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
