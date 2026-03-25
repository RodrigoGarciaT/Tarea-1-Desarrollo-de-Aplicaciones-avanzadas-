// https://codeforces.com/contest/5/submission/368201569
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

#define ll long long

template <typename T>
class Stack {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
        Node() : data(T()), next(nullptr) {}
    };

    Node* head;
    int length;

public:
    Stack() {
        head = new Node();
        length = 0;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
        delete head;
    }

    void push(T val) {
        Node* newNode = new Node(val);
        newNode->next = head->next;
        head->next = newNode;
        length++;
    }

    void pop() {
        if (isEmpty()) return;

        Node* temp = head->next;
        head->next = head->next->next;
        delete temp;
        length--;
    }

    T& top() {
        if (!isEmpty()) {
            return head->next->data;
        }
        throw runtime_error("Stack is empty");
    }

    bool isEmpty() const {
        return head->next == nullptr;
    }

    int size() const {
        return length;
    }
};

struct CHash {
    const uint64_t C = uint64_t(2e18L * acosl(-1.0L)) + 71;
    const uint32_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();

    size_t operator()(uint64_t x) const {
        return __builtin_bswap64((x ^ RANDOM) * C);
    }
};

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

    Node* find(const K& key) const {
        for (Node* cur = head; cur; cur = cur->next)
            if (cur->key == key) return cur;
        return nullptr;
    }

    void upsert(const K& key, const V& value) {
        if (Node* node = find(key)) {
            node->value = value;
            return;
        }
        Node* node = new Node(key, value);
        node->next = head;
        head = node;
    }

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

    void insert(const K& key, const V& value) {
        if (!buckets[index(key)].find(key)) count++;
        buckets[index(key)].upsert(key, value);
    }

    bool remove(const K& key) {
        if (buckets[index(key)].erase(key)) {
            count--;
            return true;
        }
        return false;
    }

    V* get(const K& key) const {
        auto* node = buckets[index(key)].find(key);
        return node ? &node->value : nullptr;
    }

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

HashTable<int, int> freq(1 << 20);
bool visited[(ll)1e6];
vector<ll> currentCount((ll)1e6, 0);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    Stack<char> st, st2;
    ll cont = 0, maxCont = 0;

    for (ll i = 0; i < (ll)s.size(); i++) {
        if (s[i] == '(') {
            st.push('(');
            cont++;
        } else {
            if (st.size() == 0) currentCount[i] = -1;
            if (st.size() == 1) {
                currentCount[i] = cont * 2;
                cont = 0;
            }
            if (st.size() > 0) st.pop();
        }
    }

    cont = 0;
    ll end = (ll)s.size() - 1;
    for (ll i = (ll)s.size() - 1; i >= 0; i--) {
        if (s[i] == ')') {
            st2.push(')');
            cont++;
        } else {
            if (st2.size() == 0) {
                currentCount[end] = -1;
                end = i - 1;
            }
            if (st2.size() == 1) {
                currentCount[end] = cont * 2;
                cont = 0;
                end = i - 1;
            }
            if (st2.size() > 0) st2.pop();
        }
    }

    cont = 0;
    for (ll i = 0; i < (ll)s.size(); i++) {
        if (currentCount[i] == -1) {
            cont = 0;
        } else {
            cont += currentCount[i];
            freq[(int)cont]++;
        }
        maxCont = max(cont, maxCont);
    }

    if (maxCont == 0) {
        cout << 0 << ' ' << 1 << '\n';
        return 0;
    }

    cout << maxCont << ' ' << freq[(int)maxCont] << '\n';

    return 0;
}
