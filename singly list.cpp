#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

// Linked List class
class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    // Insert at beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node{value, head};
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int value) {
        Node* newNode = new Node{value, nullptr};
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }

    // Insert at specific position (1-based index)
    void insertAtPosition(int value, int position) {
        if (position < 1) {
            cout << "Invalid position.\n";
            return;
        }
        if (position == 1) {
            insertAtBeginning(value);
            return;
        }

        Node* newNode = new Node{value, nullptr};
        Node* temp = head;
        for (int i = 1; temp != nullptr && i < position - 1; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position out of range.\n";
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Delete from beginning
    void deleteFromBeginning() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Delete from end
    void deleteFromEnd() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next)
            temp = temp->next;
        delete temp->next;
        temp->next = nullptr;
    }

    // Delete at specific position
    void deleteAtPosition(int position) {
        if (position < 1 || !head) {
            cout << "Invalid position or empty list.\n";
            return;
        }
        if (position == 1) {
            deleteFromBeginning();
            return;
        }

        Node* temp = head;
        for (int i = 1; temp && i < position - 1; ++i)
            temp = temp->next;

        if (!temp || !temp->next) {
            cout << "Position out of range.\n";
            return;
        }

        Node* delNode = temp->next;
        temp->next = delNode->next;
        delete delNode;
    }

    // Search for a value
    void search(int value) {
        Node* temp = head;
        int pos = 1;
        while (temp) {
            if (temp->data == value) {
                cout << "Value " << value << " found at position " << pos << ".\n";
                return;
            }
            temp = temp->next;
            pos++;
        }
        cout << "Value " << value << " not found in the list.\n";
    }

    // Count nodes
    int count() {
        int cnt = 0;
        Node* temp = head;
        while (temp) {
            cnt++;
            temp = temp->next;
        }
        return cnt;
    }

    // Display the list
    void display() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // Reverse the list
    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // Destructor to clean up memory
    ~SinglyLinkedList() {
        while (head)
            deleteFromBeginning();
    }
};

// Main function to demonstrate
int main() {
    SinglyLinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtBeginning(5);
    list.insertAtPosition(15, 3);
    list.display();  // 5 -> 10 -> 15 -> 20 -> NULL

    list.deleteFromBeginning();
    list.deleteFromEnd();
    list.deleteAtPosition(2);
    list.display();  // 10 -> NULL

    list.insertAtEnd(30);
    list.insertAtEnd(40);
    list.search(30);  // Found
    list.search(100); // Not found

    cout << "Total nodes: " << list.count() << "\n";

    list.display();
    list.reverse();
    list.display();  // Reversed list

    return 0;
}
