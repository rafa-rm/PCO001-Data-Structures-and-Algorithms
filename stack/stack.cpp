/*
Rafael Rocha Maciel
Mestrado em ciência e tecnologia da computação (UNIFEI)
Data Structures and Algorithms - Stack
*/

/*
 *
 * @file stack.cpp
 * @brief Implementation of a stack data structure using a singly linked list and
 * a function to verify if a sequence of parentheses and brackets is well-formed.
 *
 * The file contains:
 * - A templated Node class to represent each element in the stack.
 * - A templated Stack class that provides common stack operations such as push, pop, top, and size.
 * - A function `isWellFormed` to check if a sequence of parentheses and brackets is well-formed.
 *
 * @class Node
 * @tparam T The type of the element stored in the node.
 * @brief Represents a node in the linked list with an element of type T and a pointer to the next node.
 *
 * @class Stack
 * @tparam T The type of the elements stored in the stack.
 * @brief Implements a stack data structure using a singly linked list.
 *
 * The Stack class provides the following methods:
 * - `Stack()` - Constructor to initialize an empty stack.
 * - `bool empty()` - Returns true if the stack is empty, false otherwise.
 * - `T pop()` - Removes and returns the top element of the stack. Throws an exception if the stack is empty.
 * - `T top()` - Returns the top element of the stack without removing it. Throws an exception if the stack is empty.
 * - `void push(T data)` - Adds an element to the top of the stack.
 * - `int getSize()` - Returns the number of elements in the stack.
 *
 * @function bool isWellFormed(std::string sequence)
 * @brief Checks if a given sequence of parentheses and brackets is well-formed.
 * @param sequence The string containing the sequence of parentheses and brackets.
 * @return Returns true if the sequence is well-formed, false otherwise.
 *
 * The main function demonstrates the usage of the Stack class with integers
 * and tests the `isWellFormed` function with a user-provided sequence of parentheses and brackets.
 */


#include <iostream>
#include <unordered_map>

template <typename T>
class Node{
    public:
        T element;
        Node *next;
        Node(T);
};

template <typename T>
Node<T>::Node(T element){
    this->element = element;
    next = nullptr;
}

template <typename T>
class Stack{
    private:
        Node<T>* first;
        int size;

    public:
        Stack();
        bool empty();
        T pop();
        T top();
        void push(T);
        int getSize();
};

template <typename T>
Stack<T>::Stack(){
    first = nullptr;
    size = 0;
}

// Time complexity = O(1)
template <typename T>
bool Stack<T>::empty(){
    return first == nullptr;
}

// Time complexity = O(1)
template <typename T>
T Stack<T>::pop(){
    if(!empty()){
        Node<T>* aux = first;
        T value = first->element;
        first = first->next;
        size--;
        delete aux;
        return value;
    }
    else
        throw std::out_of_range("Stack is empty");
}

// Time complexity = O(1)
template <typename T>
T Stack<T>::top(){
    if(!empty())
        return first->element;
    else
        throw std::out_of_range("Stack is empty");
}

// Time complexity = O(1)
template <typename T>
void Stack<T>::push(T data){
    Node<T>* newNode = new Node<T>(data);
    newNode->next = first;
    first = newNode;
    size++;
}

// Time complexity = O(1)
template <typename T>
int Stack<T>::getSize(){
    return size;
}

// Function used to verify if a sequence of parentheses/brackets is well-formed
bool isWellFormed(std::string sequence){
    Stack<char> stack;

    std::unordered_map<char, char> matchingBrackets = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    for(char ch : sequence){
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (stack.empty() || stack.top() != matchingBrackets[ch]) {
                return false;
            }
            stack.pop();
        }
    }
    return stack.empty();
}

int main(){
    // Testing int stack
    Stack<int> intStack;

    // Push in intStack
    intStack.push(3);
    intStack.push(25);
    intStack.push(2);

    // Size after push elements
    std::cout << "Size = " << intStack.getSize() << "\n";

    // Printing top and poping elements
    std::cout << "Top = " << intStack.top() << "\n";
    intStack.pop();
    std::cout << "Top = " << intStack.top() << "\n";
    intStack.pop();
    std::cout << "Top = " << intStack.top() << "\n";
    intStack.pop();

    // Size after sequence of pops
    std::cout << "Size = " << intStack.getSize() << "\n";
    // Verifying if stack is empty and printing
    std::cout << "Is stack empty? " << (intStack.empty() ? "Yes" : "No") << std::endl;

    // Testing a sequence of parentheses and brackets
    std::cout << "\n\n\nInitiating sequence test...\n";
    std::string sequence;
    std::cout << "Enter a sequence of parentheses and brackets: ";
    std::getline(std::cin, sequence);

    if (isWellFormed(sequence)) {
        std::cout << "The sequence is well-formed." << std::endl;
    } else {
        std::cout << "The sequence isn't well-formed." << std::endl;
    }

    return 0;
}