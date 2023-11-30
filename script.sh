g++ -std=c++17 -pthread -pg Q1.cpp -o output1
./output1
gprof ./output1 gmon.out > profile.txt
less profile.txt

g++ -std=c++17 -pthread -pg Q3.cpp -o output3
./output3
gprof ./output3 gmon.out > profile.txt
less profile.txt