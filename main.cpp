#include <iostream>
#include <exception>
using namespace std;

void runStackTests();
void runRandomStackStressTests();
void runQueueTests();
void runRandomQueueStressTests();
void runHashTableTests();
void runRandomHashTableStressTests();

int main() {
    try {
        runStackTests();
        runRandomStackStressTests();
        runQueueTests();
        runRandomQueueStressTests();
        runHashTableTests();
        runRandomHashTableStressTests();
        cout << "All tests passed.\n";
        return 0;
    } catch (const exception& e) {
        cerr << "Test failure: " << e.what() << "\n";
        return 1;
    }
}

