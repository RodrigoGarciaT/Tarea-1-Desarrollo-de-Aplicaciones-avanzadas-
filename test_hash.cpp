#include "HashTable.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
using namespace std;

static void check(bool cond, const string& msg) {
    if (!cond) throw runtime_error(msg);
}

void runHashTableTests() {
    cout << "[HashTable] tests\n";

    HashTable<int, string> table(32);
    check(table.empty(), "HashTable should start empty");
    check(table.size() == 0, "HashTable size should start at 0");

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.insert(2, "TWO"); // update
    table[300] = "yolo";

    check(table.contains(2), "Should contain key 2");
    check(table.at(2) == "TWO", "Key 2 should be updated to 'TWO'");
    check(table.at(300) == "yolo", "operator[] should insert missing keys");

    check(table.get(1) != nullptr, "get(1) should not be null");
    check(*table.get(1) == "one", "get(1) should return 'one'");
    check(table.get(999) == nullptr, "get(999) should be null");

    check(table.size() == 4, "Size should be 4 after inserts (1,2,3,300)");

    table.remove(3);
    check(!table.contains(3), "Key 3 should be removed");
    check(table.size() == 3, "Size should be 3 after removing key 3");

    // operator[] access (insert missing keys)
    table[10] = "ten";
    table[20] = "twenty";
    check(table.at(10) == "ten", "Key 10 should be 'ten'");
    check(table.at(20) == "twenty", "Key 20 should be 'twenty'");

    // empty, count, at, clear
    check(!table.empty(), "Table should not be empty yet");
    check(table.count_key(1) == 1, "count_key(1) should be 1");
    check(table.count_key(99) == 0, "count_key(99) should be 0");

    check(table.at(1) == "one", "at(1) should be 'one'");

    try {
        table.at(99);
        throw runtime_error("Expected out_of_range not thrown");
    } catch (const out_of_range&) {
        // ok
    }

    table.clear();
    check(table.empty(), "Table should be empty after clear()");
    check(table.size() == 0, "Size should be 0 after clear()");

    cout << "[HashTable] basic tests PASSED\n";
}

void runRandomHashTableStressTests() {
    const int OPS = 10000;

    HashTable<int, int> table(10007);
    unordered_map<int, int> ref;

    mt19937_64 rng(192837465ULL);
    uniform_int_distribution<int> keyDist(-50000, 50000);
    uniform_int_distribution<int> valDist(-1000000, 1000000);
    uniform_int_distribution<int> opDist(0, 9);

    for (int i = 0; i < OPS; ++i) {
        int op = opDist(rng);
        int key = keyDist(rng);
        int value = valDist(rng);

        switch (op) {
            case 0: { // insert/update
                table.insert(key, value);
                ref[key] = value;
                break;
            }
            case 1: { // remove
                bool r1 = table.remove(key);
                auto it = ref.find(key);
                bool r2 = (it != ref.end());
                if (r2) ref.erase(it);
                check(r1 == r2, "HashTable remove return mismatch");
                break;
            }
            case 2: { // contains
                bool c1 = table.contains(key);
                bool c2 = (ref.find(key) != ref.end());
                check(c1 == c2, "HashTable contains mismatch");
                break;
            }
            case 3: { // get
                int* p = table.get(key);
                auto it = ref.find(key);
                if (it == ref.end()) {
                    check(p == nullptr, "HashTable get should be nullptr");
                } else {
                    check(p != nullptr, "HashTable get should not be nullptr");
                    check(*p == it->second, "HashTable get value mismatch");
                }
                break;
            }
            case 4: { // at (solo si la key existe)
                auto it = ref.find(key);
                if (it != ref.end()) {
                    check(table.at(key) == it->second, "HashTable at value mismatch");
                }
                break;
            }
            case 5: { // operator[]
                table[key] = value;
                ref[key] = value;
                check(table[key] == ref[key], "HashTable operator[] write mismatch");
                break;
            }
            case 6: { // size
                check(table.size() == (int)ref.size(), "HashTable size mismatch");
                break;
            }
            case 7: { // empty
                check(table.empty() == ref.empty(), "HashTable empty mismatch");
                break;
            }
            case 8: { // clear (siempre valido)
                table.clear();
                ref.clear();
                break;
            }
            case 9: { // operator[] read access (inserta default si no existe)
                int v1 = table[key];
                int v2 = ref[key];
                check(v1 == v2, "HashTable operator[] read mismatch");
                break;
            }
        }

        // Verificacion consistente en cada iteracion.
        check(table.size() == (int)ref.size(), "HashTable size mismatch after op");
        check(table.empty() == ref.empty(), "HashTable empty mismatch after op");

        // Verificacion ocasional para validar at/get sin costear demasiado.
        if (!ref.empty() && (i % 1000 == 0)) {
            int anyKey = ref.begin()->first;
            check(table.contains(anyKey) == true, "HashTable contains(anyKey) should be true");
            check(table.at(anyKey) == ref[anyKey], "HashTable at(anyKey) mismatch");
            check(table[anyKey] == ref[anyKey], "HashTable operator[](anyKey) mismatch");

            int* p = table.get(anyKey);
            check(p != nullptr, "HashTable get(anyKey) should not be nullptr");
            check(*p == ref[anyKey], "HashTable get(anyKey) mismatch");
        }
    }

    // Limpieza final.
    table.clear();
    ref.clear();
    check(table.empty() && ref.empty(), "Final hash table should be empty");
    cout << "[HashTable] random stress PASSED (" << OPS << " ops)\n";
}

