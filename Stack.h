#pragma once

#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    // Nodo Genérico
    class Node {
    public:
        T data;
        Node* next; // No hace falta el <T> aquí adentro
        Node(T val) : data(val), next(nullptr) {}
        Node() : data(T()), next(nullptr) {}
    };
    Node* head;
    int length;

public:
    Stack() {
        head = new Node(); // dummy
        length = 0;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
        delete head;
    }

    // Crea un nuevo nodo con nuestra data y lo inserta despues del head
    void push(T val) {
        Node* newNode = new Node(val);
        newNode->next = head->next;
        head->next = newNode;
        length++;
    }

    // Apunta el head al nodo que sigue despues del que vamos a borrar y borra ese nodo
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

