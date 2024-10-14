#include <iostream>
using namespace std;

template <class T>
class Node 
{
public:
    T info;
    Node<T>* next;

    Node(T value)
{
        info = value;
        next = nullptr;
    }
};

template <class T>
class LinkedList 
{
private:
    Node<T>* head;

public:
    // Constructor
    LinkedList() 
{
        head = nullptr;
    }

    // Destructor
    ~LinkedList() 
{
        if (!head) return;

        Node<T>* current = head;
        Node<T>* nextNode;
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
        
        head = nullptr;
    }

    // Copy constructor
    LinkedList(const LinkedList& other)
{
        head = nullptr;
        if (!other.head) return;

        Node<T>* current = other.head;
        do 
        {
            insertAtTail(current->info);
            current = current->next;
        } while (current != other.head);
    }

    // Insert at head
    void insertAtHead(T value) 
{
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
            newNode->next = head; // Point to itself in circular list
        } else {
            Node<T>* temp = head;
            while (temp->next != head) 
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
            head = newNode;
        }
    }

    // Insert at tail
    void insertAtTail(T value) 
{
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
            newNode->next = head; // Point to itself
        } else {
            Node<T>* temp = head;
            while (temp->next != head) 
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    // Delete at head
    bool deleteAtHead() 
{
        if (!head) return false;

        if (head->next == head) 
        {
            delete head;
            head = nullptr;
            return true;
        }

        Node<T>* temp = head;
        Node<T>* tail = head;

        while (tail->next != head)
          {
            tail = tail->next;
        }
        head = head->next;
        tail->next = head;
        delete temp;
        return true;
    }

    // Delete at tail
    bool deleteAtTail() {
        if (!head) return false;

        if (head->next == head) {
            delete head;
            head = nullptr;
            return true;
        }

        Node<T>* prev = nullptr;
        Node<T>* temp = head;

        while (temp->next != head) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = head;
        delete temp;
        return true;
    }

    // Insert after a node with a specific value
    bool insertAfter(T value, T key) {
        if (!head) return false;

        Node<T>* temp = head;
        do {
            if (temp->info == key) {
                Node<T>* newNode = new Node<T>(value);
                newNode->next = temp->next;
                temp->next = newNode;
                return true;
            }
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    // Insert before a node with a specific value
    bool insertBefore(T value, T key)
{
        if (!head) return false;

        if (head->info == key)
        {
            insertAtHead(value);
            return true;
        }

        Node<T>* prev = nullptr;
        Node<T>* temp = head;

        do {
            if (temp->next->info == key) 
            {
                Node<T>* newNode = new Node<T>(value);
                newNode->next = temp->next;
                temp->next = newNode;
                return true;
            }
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    // Delete node before a specific value
    bool deleteBefore(T key) 
{
        if (!head || head->next == head) return false;

        if (head->next->info == key)
        {
            return deleteAtHead();
        }

        Node<T>* prev = nullptr;
        Node<T>* temp = head;

        do {
            if (temp->next->next->info == key)
            {
                prev = temp;
                Node<T>* nodeToDelete = temp->next;
                prev->next = nodeToDelete->next;
                delete nodeToDelete;
                return true;
            }
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    // Delete node after a specific value
    bool deleteAfter(T key)
{
        if (!head) return false;

        Node<T>* temp = head;
        do
          {
            if (temp->info == key)
            {
                Node<T>* nodeToDelete = temp->next;
                temp->next = nodeToDelete->next;
                delete nodeToDelete;
                return true;
            }
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    // Get length of the list
    int getLength()
{
        if (!head) return 0;

        int length = 0;
        Node<T>* temp = head;

        do {
            length++;
            temp = temp->next;
        } while (temp != head);

        return length;
    }

    // Search for a node with specific value
    Node<T>* search(T value)
{
        if (!head) return nullptr;

        Node<T>* temp = head;
        do {
            if (temp->info == value) 
            {
                return temp;
            }
            temp = temp->next;
        } while (temp != head);

        return nullptr;
    }

    // Display list
    void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* temp = head;
        do {
            cout << temp->info << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
};

// Example usage
int main() {
    LinkedList<int> list;

    list.insertAtHead(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAfter(25, 20);
    list.insertBefore(15, 20);
    list.display();  // Output: 10 15 20 25 30

    list.deleteAtHead();
    list.deleteAtTail();
    list.deleteAfter(20);
    list.display();  // Output: 15 20

    cout << "Length: " << list.getLength() << endl;  // Output: Length: 2

    return 0;
}
