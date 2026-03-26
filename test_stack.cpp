#include "Stack.h"
#include <iostream>
#include <random>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;

static void check(bool cond, const string& msg) {
    if (!cond) throw runtime_error(msg);
}

void runStackTests() {
    cout << "\n============================================================\n";
    cout << "[Stack] tests\n";
    cout << "============================================================\n\n";

    Stack<string> st;
    cout << "[Stack] creado stack vacio, verificando estado inicial...\n";
    check(st.isEmpty(), "Stack should start empty");
    check(st.size() == 0, "Stack size should be 0");
    cout << "[Stack] OK: isEmpty=true, size=0\n";

    // Insertions
    cout << "[Stack] push('Mundo')\n";
    st.push("Mundo");
    cout << "[Stack] push('Hola')\n";
    st.push("Hola");
    check(st.size() == 2, "Stack size should be 2");
    check(st.top() == "Hola", "Top should be 'Hola'");
    cout << "[Stack] OK: size=2, top='Hola'\n";

    // Pop
    cout << "[Stack] pop()\n";
    st.pop();
    check(st.size() == 1, "Stack size should be 1");
    check(st.top() == "Mundo", "Top should be 'Mundo' after pop");
    cout << "[Stack] OK: size=1, top='Mundo'\n";

    // Pop all
    cout << "[Stack] pop() para vaciar\n";
    st.pop();
    check(st.isEmpty(), "Stack should be empty after popping all");
    cout << "[Stack] OK: stack vacio\n";

    // Exception on top()
    cout << "[Stack] verificando excepcion al consultar top() en stack vacio...\n";
    try {
        (void)st.top();
        throw runtime_error("Expected exception not thrown");
    } catch (const runtime_error&) {
        // ok
    }
    cout << "[Stack] OK: top() en vacio lanza excepcion\n";

    cout << "\n[Stack] basic tests PASSED\n";
}

void runRandomStackStressTests() {
    const int OPS = 10000;

    Stack<int> st;
    stack<int> ref;

    mt19937_64 rng(123456789ULL);
    uniform_int_distribution<int> valDist(-1000000, 1000000);
    uniform_int_distribution<int> opDist(0, 4); // 0 push, 1 pop, 2 top, 3 size, 4 isEmpty

    for (int i = 0; i < OPS; ++i) {
        int op = opDist(rng);
        int x = valDist(rng);

        if (ref.empty()) {
            // Solo operaciones validas cuando el stack esta vacio.
            if (op == 0) {
                st.push(x);
                ref.push(x);
            }
        } else {
            switch (op) {
                case 0: { // push
                    st.push(x);
                    ref.push(x);
                    break;
                }
                case 1: { // pop
                    st.pop();
                    ref.pop();
                    break;
                }
                case 2: { // top
                    check(st.top() == ref.top(), "Stack top mismatch");
                    break;
                }
                case 3: { // size
                    check(st.size() == (int)ref.size(), "Stack size mismatch");
                    break;
                }
                case 4: { // isEmpty
                    check(st.isEmpty() == false, "Stack isEmpty should be false");
                    break;
                }
            }
        }

        // Comparaciones consistentes despues de cada iteracion.
        check(st.size() == (int)ref.size(), "Stack size mismatch after op");
        check(st.isEmpty() == ref.empty(), "Stack isEmpty mismatch after op");

        if (!ref.empty()) {
            check(st.top() == ref.top(), "Stack top mismatch after op");
        }
    }

    // Vaciar completamente y verificar.
    while (!ref.empty()) {
        check(st.top() == ref.top(), "Final top mismatch");
        st.pop();
        ref.pop();
    }

    check(ref.empty() && st.isEmpty(), "Final stack should be empty");
    cout << "[Stack] random stress PASSED (" << OPS << " ops)\n\n";
}

