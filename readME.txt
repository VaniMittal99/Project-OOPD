1. Change Directory (cd)
2. Move File (mv)
3. Remove File (rm)
4.  List Directory Contents (ls)
5. Copy File (cp)
6. Help (help)
7. Exit (exit)
Multi-threading
The program incorporates multi-threading for potentially time-consuming file operations such as moving, copying, and removing.
A mutex is used to ensure thread safety and avoid conflicts between multiple threads.

Compile the program using a C++ compiler (e.g., g++).
g++ custom_shell.cpp -o custom_shell -std=c++17 -lstdc++fs -pthread

Run the compiled executable.
./custom_shell
