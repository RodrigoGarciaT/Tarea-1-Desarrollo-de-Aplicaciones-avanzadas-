#pragma once

#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    // Nodo Genérico
    class Node {
        public:
            T data;
            Node* next;
            Node* prev;
            Node() : data(T()), next(nullptr), prev(nullptr) {}
            Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };
    Node* head, *tail; 
    int length;

public:
    Queue() {
        head = new Node(); // dummy
        tail = head;
        length = 0;
    }

    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
        delete head; 
    }

    // Agrega un valor al principio de la lista como en el stack 
    // Checando que los ->next y ->prev esten correctos
    void push(T val) {
        Node* newNode = new Node(val);
        if(isEmpty()){
            tail = newNode;
        }
        newNode->next = head->next;
        newNode->prev = head;
        head->next = newNode;
        if (newNode->next != nullptr) {
            newNode->next->prev = newNode;
        }
        length++;
    }

    // Quitamos el elemento en el tail de la lista
    void pop() {
        if (isEmpty()) return;
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        length--;
    }

    // Retornamos la data del nodo Tail
    T& front() {
        if (!isEmpty()) {
            return tail->data;
        }
        throw runtime_error("Queue is empty");
    }

    bool isEmpty() const {
        return head->next == nullptr;
    }

    int size() const {
        return length;
    }
};

