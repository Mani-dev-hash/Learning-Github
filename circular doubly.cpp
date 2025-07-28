#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

class CircularDoublyLinkedList {
private:
    Node* head;

public:
    CircularDoublyLinkedList() {
        head = nullptr;
    }

    // Insert at beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node{value, nullptr, nullptr};

        if (!head) {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
            return;
        }

        Node* tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int value) {
        if (!head) {
            insertAtBeginning(value);
            return;
        }

        Node* newNode = new Node{value, head, head->prev};
        head->prev->next = newNode;
        head->prev = newNode;
    }

    // Insert at a specific position (1-based)
    void insertAtPosition(int value, int position) {
        if (position < 1) {
            cout << "Invalid position.\n";
            return;
        }
        if (position == 1) {
            insertAtBeginning(value);
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position - 1 && temp->next != head; ++i)
            temp = temp->next;

        if (temp->next == head && position > 2) {
            cout << "Position out of range.\n";
            return;
        }

        Node* newNode = new Node{value, temp->next, temp};
        temp->next->prev = newNode;
        temp->next = newNode;
    }

    // Delete from beginning
    void deleteFromBeginning() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        Node* tail = head->prev;
        Node* temp = head;

        head = head->next;
        head->prev = tail;
        tail->next = head;

        delete temp;
    }

    // Delete from end
    void deleteFromEnd() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        Node* tail = head->prev;
        tail->prev->next = head;
        head->prev = tail->prev;

        delete tail;
    }

    // Delete at a specific position
    void deleteAtPosition(int position) {
        if (!head || position < 1) {
            cout << "Invalid position or empty list.\n";
            return;
        }

        if (position == 1) {
            deleteFromBeginning();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position && temp->next != head; ++i)
            temp = temp->next;

        if (temp->next == head && position > 2) {
            cout << "Position out of range.\n";
            return;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        delete temp;
    }

    // Search for a value
    void search(int value) {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        int pos = 1;
        do {
            if (temp->data == value) {
                cout << "Value " << value << " found at position " << pos << ".\n";
                return;
            }
            temp = temp->next;
            pos++;
        } while (temp != head);

        cout << "Value not found.\n";
    }

    // Count nodes
    int count() {
        if (!head) return 0;
        int cnt = 0;
        Node* temp = head;
        do {
            cnt++;
            temp = temp->next;
        } while (temp != head);
        return cnt;
    }

    // Display forward
    void displayForward() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        do {
            cout << temp->data << " <-> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(back to head)\n";
    }

    // Display backward
    void displayBackward() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head->prev;
        Node* start = temp;
        do {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        } while (temp != start);
        cout << "(back to tail)\n";
    }

    // Reverse the list
    void reverse() {
        if (!head || head->next == head)
            return;

        Node* current = head;
        Node* temp = nullptr;

        do {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev; // Move to "next" node, which is prev due to swap
        } while (current != head);

        head = head->prev;
    }

    // Destructor
    ~CircularDoublyLinkedList() {
        while (head)
            deleteFromBeginning();
    }
};

// Demo
int main() {
    CircularDoublyLinkedList cdll;

    cdll.insertAtEnd(10);
    cdll.insertAtEnd(20);
    cdll.insertAtBeginning(5);
    cdll.insertAtPosition(15, 3);

    cdll.displayForward();   // 5 <-> 10 <-> 15 <-> 20 ...
    cdll.displayBackward();  // 20 <-> 15 <-> 10 <-> 5 ...

    cdll.deleteFromBeginning();
    cdll.deleteFromEnd();
    cdll.deleteAtPosition(2);

    cdll.displayForward();   // Should display the remaining elements
    cdll.search(10);         // Found or not found
    cdll.search(100);        // Not found

    cout << "Total nodes: " << cdll.count() << "\n";

    cdll.reverse();
    cdll.displayForward();

    return 0;
}
