#include "Queue.h"
#include <deque>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
using namespace std;

static void check(bool cond, const string& msg) {
    if (!cond) throw runtime_error(msg);
}

void runQueueTests() {
    cout << "[Queue] tests\n";

    Queue<string> q;
    check(q.isEmpty(), "Queue should start empty");
    check(q.size() == 0, "Queue size should be 0");

    q.push("Mundo");
    q.push("Hola");
    check(q.size() == 2, "Queue size should be 2");

    // Según tu implementación: front apunta al "tail" (FIFO real al hacer pop desde el tail).
    check(q.front() == "Mundo", "front should be 'Mundo'");

    q.pop();
    check(q.size() == 1, "Queue size should be 1 after pop");
    check(q.front() == "Hola", "front should be 'Hola' after one pop");

    q.pop();
    check(q.isEmpty(), "Queue should be empty after popping all");

    // Exception on front()
    try {
        (void)q.front();
        throw runtime_error("Expected exception not thrown");
    } catch (const runtime_error&) {
        // ok
    }
}

void runRandomQueueStressTests() {
    const int OPS = 10000;

    Queue<int> q;
    deque<int> ref;

    mt19937_64 rng(987654321ULL);
    uniform_int_distribution<int> valDist(-1000000, 1000000);
    uniform_int_distribution<int> opDist(0, 4); // 0 push, 1 pop, 2 front, 3 size, 4 isEmpty

    for (int i = 0; i < OPS; ++i) {
        int op = opDist(rng);
        int x = valDist(rng);

        if (ref.empty()) {
            // Solo operaciones validas cuando la cola esta vacia.
            if (op == 0) {
                q.push(x);
                ref.push_back(x);
            } else {
                // Cuando esta vacia: no debe poder pedir front/pop.
                check(q.isEmpty() == true, "Queue should be empty");
                check(q.size() == (int)ref.size(), "Queue size mismatch on empty");
            }
        } else {
            switch (op) {
                case 0: { // push (al final)
                    q.push(x);
                    ref.push_back(x);
                    break;
                }
                case 1: { // pop (remove del frente)
                    check(q.front() == ref.front(), "Queue front mismatch before pop");
                    q.pop();
                    ref.pop_front();
                    break;
                }
                case 2: { // front
                    check(q.front() == ref.front(), "Queue front mismatch");
                    break;
                }
                case 3: { // size
                    check(q.size() == (int)ref.size(), "Queue size mismatch");
                    break;
                }
                case 4: { // isEmpty
                    check(q.isEmpty() == false, "Queue isEmpty should be false");
                    break;
                }
            }
        }

        // Comparaciones consistentes despues de cada iteracion.
        check(q.size() == (int)ref.size(), "Queue size mismatch after op");
        check(q.isEmpty() == ref.empty(), "Queue isEmpty mismatch after op");
        if (!ref.empty()) {
            check(q.front() == ref.front(), "Queue front mismatch after op");
        }
    }

    while (!ref.empty()) {
        check(q.front() == ref.front(), "Final queue front mismatch");
        q.pop();
        ref.pop_front();
    }

    check(ref.empty() && q.isEmpty(), "Final queue should be empty");
    cout << "[Queue] random stress PASSED (" << OPS << " ops)\n";
}

