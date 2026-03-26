#pragma once

#include <chrono>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <vector>
using namespace std;

// Randomized Hash Function
struct CHash {
    const uint64_t C = uint64_t(2e18L * acosl(-1.0L)) + 71;
    const uint32_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();

    size_t operator()(uint64_t x) const {
        return __builtin_bswap64((x ^ RANDOM) * C);
    }
};

// Linked List (with nested Node)

template <typename K, typename V>
class LinkedList {
public:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    Node* head = nullptr;

    ~LinkedList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // Busca la key en la lista del bucket
    Node* find(const K& key) const {
        for (Node* cur = head; cur; cur = cur->next)
            if (cur->key == key) return cur;
        return nullptr;
    }

    // Actualiza si existe o inserta al inicio si no existe
    void upsert(const K& key, const V& value) {
        if (Node* node = find(key)) { node->value = value; return; }
        Node* node = new Node(key, value);
        node->next = head;
        head = node;
    }

    // Borra la key de la lista y confirma si se elimino
    bool erase(const K& key) {
        Node** ptr = &head;
        while (*ptr) {
            if ((*ptr)->key == key) {
                Node* tmp = *ptr;
                *ptr = tmp->next;
                delete tmp;
                return true;
            }
            ptr = &(*ptr)->next;
        }
        return false;
    }
};

// Hash Table
// Solo por cada key genera un hash y lo mete en el bucket correspondiente
// Si la key ya existe, actualiza el valor, si no, inserta el valor
template <typename K, typename V, typename Hash = CHash>
class HashTable {
    vector<LinkedList<K, V>> buckets;
    int count = 0;
    Hash hasher;

    int index(const K& key) const {
        return hasher(static_cast<uint64_t>(key)) % buckets.size();
    }

public:
    HashTable(int cap = 1e5) : buckets(cap) {}

    // Inserta o actualiza una key en su bucket
    void insert(const K& key, const V& value) {
        if (!buckets[index(key)].find(key)) count++;
        buckets[index(key)].upsert(key, value);
    }

    // Elimina una key y ajusta el conteo si existe
    bool remove(const K& key) {
        if (buckets[index(key)].erase(key)) { count--; return true; }
        return false;
    }

    // Regresa puntero al valor o nullptr si no existe
    V* get(const K& key) const {
        auto* node = buckets[index(key)].find(key);
        return node ? &node->value : nullptr;
    }

    // Regresa referencia al valor y crea key con default si falta
    V& operator[](const K& key) {
        auto* node = buckets[index(key)].find(key);
        if (!node) {
            count++;
            buckets[index(key)].upsert(key, V{});
            node = buckets[index(key)].find(key);
        }
        return node->value;
    }

    bool contains(const K& key) const {
        return buckets[index(key)].find(key) != nullptr;
    }

    int size() const { return count; }

    bool empty() const { return count == 0; }

    void clear() {
        for (auto& bucket : buckets) {
            while (bucket.head) {
                auto* tmp = bucket.head;
                bucket.head = bucket.head->next;
                delete tmp;
            }
        }
        count = 0;
    }

    int count_key(const K& key) const { return contains(key) ? 1 : 0; }

    V& at(const K& key) {
        auto* node = buckets[index(key)].find(key);
        if (!node) throw out_of_range("key not found");
        return node->value;
    }

    const V& at(const K& key) const {
        auto* node = buckets[index(key)].find(key);
        if (!node) throw out_of_range("key not found");
        return node->value;
    }
};

