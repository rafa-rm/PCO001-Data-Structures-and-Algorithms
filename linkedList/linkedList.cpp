#include <iostream>

class Node{
    public:
        int data;
        Node* next;
        Node(int);
};

Node::Node(int data){
    this->data = data;
    next = nullptr;
}

class LinkedList{
    private:
        Node* first;
        Node* last;
        bool isSorted;

        void insertFirst(int);
        void insertLast(int);
        void insert(int, int = 0);
        void insertSorted(int, Node*&, Node*&);
        void insertAtPosition(int, Node*, Node*, int);
        void search(int);
        void removeFirst();
        void remove(int);
        void printList();
        void interfaceSortedList();
        void interfaceList();
    public:
        LinkedList(bool);
        void interface();        
};

LinkedList::LinkedList(bool isSorted){
    first = nullptr;
    last = nullptr;
    this->isSorted = isSorted;
}

// Time Complexity O(1)
void LinkedList::insertFirst(int data){
    Node* newNode = new Node(data);
    newNode->next = first;
    if(first == nullptr)
        last = newNode;
    first = newNode;
}

// Time Complexity O(1)
void LinkedList::insertLast(int data){
    Node* newNode = new Node(data);
    if(last == nullptr)
        first = newNode;
    else{
        last->next = newNode;
    }
    last = newNode;
}

// Time Complexity O(1)
void LinkedList::insert(int data, int position){
    Node* aux = first;
    Node* prev = nullptr;
    if(isSorted){
        insertSorted(data, aux, prev);
    }
    else
        insertAtPosition(data, aux, prev, position);
}

// Time Complexity O(n)
void LinkedList::insertSorted(int data, Node* &aux, Node* &prev){
    while(aux != nullptr && aux->data <= data){
        prev = aux;
        aux = aux->next;
    }
    if(prev == nullptr){
        this->insertFirst(data);
    }
    else{
        Node* newNode = new Node(data);
        prev->next = newNode;
        newNode->next = aux;
    }
}

// Time Complexity O(n)
void LinkedList::insertAtPosition(int data, Node* aux, Node* prev, int position){
    int positionAux = 0;
    while(aux != nullptr && positionAux < position){
        positionAux++;
        prev = aux;
        aux = aux->next;
    }
    if(positionAux != position){
        std::cout << "List doesn't have " << position <<
            " elements. Inserting at the position: " << positionAux << std::endl;
    }
    if(positionAux == 0){
        this->insertFirst(data);
    }
    else{
        Node* newNode = new Node(data);
        prev->next = newNode;
        newNode->next = aux;
        if(aux == nullptr)
            last = newNode;
    }
}

// Time Complexity O(n)
void LinkedList::search(int data){
    Node* aux = first;
    int position = 0;
    while(aux != nullptr && aux->data != data){
        aux = aux->next;
        position++;
    }
    if(aux != nullptr)
        std::cout << "Data was found at the position " << position << "\n";
    else
        std::cout << "This Data doesn't exist\n";
}

// Time Complexity O(1)
void LinkedList::removeFirst(){
    if(first != nullptr){
        Node* aux = first;
        first = first->next;
        if(first == nullptr)
            last = first;
        delete aux;
        std::cout << "Successfully excluded\n";
    }
    else
        std::cout << "Data doesn't exists\n";
}

// Time Complexity O(n)
void LinkedList::remove(int data){
    Node* prev = nullptr;
    Node* aux = first;
    while(aux != nullptr && aux->data != data){
        prev = aux;
        aux = aux->next;
    }
    if(aux != nullptr){
        if(aux == first){
            first = first->next;
            if(first == nullptr)
                last = nullptr;
        }
        else{
            prev->next = aux->next;
            if(aux == last)
                last = prev;
        }
        delete aux;
        std::cout << "Successfully excluded\n";               
    }
    else
        std::cout << "Data doesn't exists\n";
}

// Time Complexity O(n)
void LinkedList::printList(){
    Node* aux = first;
    while(aux != nullptr){
        std::cout << aux->data << " -> ";
        aux = aux->next;
    }
    std::cout << "NULL" << std::endl;
}

void LinkedList::interface(){
    system("cls");
    if(isSorted)
        interfaceSortedList();
    else
        interfaceList();
}

void LinkedList::interfaceSortedList(){
    char option = 'y';
    int operation, data;
    while(option == 'y' || option == 'Y'){
        std::cout << "What operation?"
        << "\n1 - Insert\n2 - Remove\n3 - Remove first element"
        << "\n4 - Search element\n5 - Print List\n";
        std::cin >> operation;
        switch (operation)
        {
            case 1:
                std::cout << "What integer do you want to insert? ";
                std::cin >> data;
                insert(data);
                break;
            case 2:
                std::cout << "What data do you want to remove? ";
                std::cin >> data;
                remove(data);
                break;
            case 3:
                removeFirst();
                break;
            case 4:
                std::cout << "What data do you want to search? ";
                std::cin >> data;
                search(data);
                break;
            case 5:
                printList();
                break;
            default:
                std::cout << "Invalid Case. Try another one\n";
        }
        std::cout << "Do you want to continue working with this list? (y/n)\n";
        std::cin >> option;
        system("cls");
    }
}

void LinkedList::interfaceList(){
    char option = 'y';
    int operation, data, position;
    while(option == 'y' || option == 'Y'){
        std::cout << "What operation?"
            << "\n1 - Insert at first position"
            << "\n2 - Insert at last position"
            << "\n3 - Insert at any position"
            << "\n4 - Remove first element"
            << "\n5 - Remove any element"
            << "\n6 - Search element"
            << "\n7 - Print list\n";
        std::cin >> operation;
        switch (operation)
        {
            case 1:
                std::cout << "What integer do you want to insert? ";
                std::cin >> data;
                insertFirst(data);
                break;
            case 2:
                std::cout << "What integer do you want to insert? ";
                std::cin >> data;
                insertLast(data);
                break; 
            case 3:
                std::cout << "What integer do you want to insert? ";
                std::cin >> data;
                std::cout << "In which position should it be inserted? ";
                std::cin >> position;
                insert(data,position);
                break;
            case 4:
                removeFirst();
                break;
            case 5:
                std::cout << "What data do you want to remove? ";
                std::cin >> data;
                remove(data);
                break;
            case 6:
                std::cout << "What data do you want to search? ";
                std::cin >> data;
                search(data);
                break;
            case 7:
                printList();
                break;
            default:
                std::cout << "Invalid Case. Try another one";
        }
        std::cout << "Do you want to continue working with this list? (y/n)\n";
        std::cin >> option;
        system("cls");
    }
}

int main(){
    int isSorted;
    std::cout << "What type of list do you want to create?"
    << "\n0-Unordered 1-Ordered\n";
    std::cin >> isSorted;
    if(isSorted == 0){
        LinkedList list(false);
        list.interface();
    }
    else{
        LinkedList list(true);
        list.interface();
    }
    return 0;
}