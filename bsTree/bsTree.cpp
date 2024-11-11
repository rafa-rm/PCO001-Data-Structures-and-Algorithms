/**
 * Binary Search Tree Implementation
 *
 * This program provides a basic implementation of a binary search tree (BST) with 
 * standard operations such as insertion, search, deletion, and height calculation. 
 * Additionally, it includes a visual representation function to print the BST structure 
 * in the console in a formatted manner. The program also features a user interface for 
 * performing various tree operations interactively.
 *
 * Main Features:
 * - Insert: Adds a new value to the tree.
 * - Remove: Deletes a specified value from the tree, adjusting the structure accordingly.
 * - Search: Checks if a value exists within the tree.
 * - Get Height: Calculates the height of the tree.
 * - Visual Print: Displays the tree structure in a simple console format.
 *
 * Usage:
 * The `interface()` function handles user input for interacting with the tree. Users 
 * can choose different operations, see the tree's structure after each operation, and 
 * continue working with the tree until they choose to exit.
 *
 * Author: Rafael Rocha
 * Mestrado em ciência e tecnologia da computação (UNIFEI)
 * Date: 11/11/2024
 */

#include <iostream>
#include <queue>
#include <iomanip>  
#include <cmath>
struct Node {
    int value;
    struct Node *left;
    struct Node *right;
};

typedef Node* Tree;

/**
 * Inserts a value into the binary search tree.
 * @param tree Reference to the tree where the value is to be inserted.
 * @param value The integer value to insert.
 */
void insert(Tree& tree, int value){
    if(tree == nullptr){
        tree = new Node;
        tree->left = nullptr;
        tree->right = nullptr;
        tree->value = value;
    } else if (value < tree->value) {
        insert(tree->left, value);
    } else {
        insert(tree->right, value);
    }
}

/**
 * Searches for a value in the binary search tree.
 * @param tree The tree to search within.
 * @param value The integer value to search for.
 * @return True if the value is found, otherwise false.
 */
bool search(Tree tree, int value){
    if(tree){
        if(tree->value == value)
            return true;
        if(value < tree->value)
            return search(tree->left,value);
        if(value > tree->value)
            return search(tree->right,value);
    }
    return false;
}

/**
 * Removes a value from the binary search tree.
 * @param tree Reference to the tree from which to remove the value.
 * @param value The integer value to remove.
 * @note Prints a message indicating whether the value was found and removed.
 */
void remove(Tree& tree, int value, int printOpt = 0) {
    // Value not found
    if (tree == nullptr){
        std::cout << "-----------Value " << value << " not found-----------\n";
        return;
    }
    // Value is lower than tree value
    else if (value < tree->value) 
        remove(tree->left, value, printOpt);
    // Value is higher  than tree value
    else if (value > tree->value) 
        remove(tree->right, value, printOpt); 
    // Value found
    else {
        if(printOpt == 0)
            std::cout << "-----------Value " << value << " found and removed-----------\n";
        // Node doesn't have children
        if (tree->left == nullptr && tree->right == nullptr) {
            delete tree;
            tree = nullptr;
        // Node doesn't have left child
        } else if (tree->left == nullptr) {
            tree = tree->right;
        // Node doesn't have right child
        } else if (tree->right == nullptr) {
            tree = tree->left;
        // Node has both children
        } else {
            // Find lower element in right subtree
            Tree temp = tree->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            tree->value = temp->value; // Change tree value for lower value in right subtree
            remove(tree->right, temp->value, 1); // Remove lower element in right subtree and doesn't print
        }
    }
}

/**
 * Calculates the height of the binary search tree.
 * @param tree The tree for which to calculate the height.
 * @return The height of the tree as an integer.
 */
int getHeight(Tree tree) {
    if (tree == nullptr) {
        return 0;
    } else {
        int heightLeft = getHeight(tree->left);
        int heightRight = getHeight(tree->right);
        return 1 + std::max(heightLeft, heightRight);
    }
}

/**
 * Populates a matrix used for printing the tree visually.
 * @param M The matrix to populate.
 * @param root The root of the tree.
 * @param col The column position for the current node in the matrix.
 * @param row The row position for the current node in the matrix.
 * @param height The remaining height of the subtree to print.
 */
void printTree(int **M, Tree root, int col, int row, int height) {
    if (root == nullptr){
        if(height > 0)
            M[row][col] = -1;
        return;
    }
    M[row][col] = root->value;
    printTree(M, root->left, col - pow(2, height - 2), row + 1, height - 1);
    printTree(M, root->right, col + pow(2, height - 2), row + 1, height - 1);
}

/**
 * Prints a visual representation of the binary tree to the console.
 * The print works very well for elements with 3 or less digits.
 * @param tree The tree to print.
 */
void TreePrinter(Tree tree) {
    int h = getHeight(tree);
    int i = 0;
    int col = pow(2, h) - 1;
    int **M = new int*[h];
    for (int i = 0; i < h; i++) {
        M[i] = new int[col];
    }
    for (int i = 0; i < h; i++) 
        for (int j = 0; j < col; j++) 
            M[i][j] = 0;
    printTree(M, tree, col / 2, 0, h);
    
    for (int i = 0; i < h; i++) {
        if(i != 0){
            // Ploting "/" and "\"
            int aux_h = h - i; // Variable used to print '/' acording to height
            int aux = 0; // Variable used to print '/' or '\' correctly

            // Print aux_h '/' and '\'
            while(aux_h > 0){
                // Verifying each col in print matrix 
                for(int j = 0; j < col; j++){
                    if (M[i][j] == 0) // Doesn't have element in this position
                        std::cout << "   ";
                    else if (M[i][j] == -1){ // Tree doesn't have this child (nullptr)
                        if (aux % 2 == 0) // left child element
                            std::cout << std::setfill(' ') << std::setw(aux_h + 1) << "  " << " "; // printing spaces accordingly
                        else{ // right child element
                            std::string backspaces((aux_h - 1) * 2, '\b'); 
                            std::cout << backspaces; // backspacing positions
                            std::cout << " " << std::setfill(' ') << std::setw(aux_h + 1) << "  "; // printing spaces accordingly
                        }
                        aux++;
                    }
                    else{ // There is element in this position
                        if (aux % 2 == 0) // left child element
                            std::cout << std::setfill(' ') << std::setw(aux_h + 1) << "  " << "/"; // printing '/' with spaces
                        else{ // right child element
                            std::string backspaces((aux_h - 1) * 2, '\b');
                            std::cout << backspaces;  // backspacing positions
                            std::cout << "\\" << std::setfill(' ') << std::setw(aux_h + 1) << "  "; // printing '\' with spaces
                        }
                        aux++;
                    }
                }
                std::cout << std::endl;
                aux_h--;
            }
        }
        // Printing elements
        for (int j = 0; j < col; j++) {
            // If doesn't have element in this position, printing spaces
            if (M[i][j] == 0 || M[i][j] == -1){
                std::cout << "   ";
            }
            // There is element in this position, printing element with 3 digits
            else
                std::cout << std::setfill('0') << std::setw(3) << M[i][j];
        }
        std::cout << std::endl;
    }
}

/**
 * User interface for tree operations including insertion, deletion, search, and height retrieval.
 */
void interface(){
    Tree tree = nullptr;
    char option = 'y';
    int operation, value;
    while(option == 'y' || option == 'Y'){
        std::cout << "What operation?"
        << "\n1 - Insert\n2 - Remove\n3 - Search"
        << "\n4 - Get Height\n";
        std::cin >> operation;
        system("cls");
        switch (operation)
        {
            case 1:
                std::cout << "What integer do you want to insert? ";
                std::cin >> value;
                insert(tree, value);
                TreePrinter(tree);
                break;
            case 2:
                std::cout << "What value do you want to remove? ";
                std::cin >> value;
                remove(tree, value);
                TreePrinter(tree);
                break;
            case 3:
                std::cout << "What value do you want to search? ";
                std::cin >> value;
                TreePrinter(tree);
                if(search(tree, value))
                    std::cout << "-----------Value is in this tree-----------\n\n";
                else
                    std::cout << "--------Value isn't in this tree-----------\n\n";
                break;
            case 4:
                TreePrinter(tree);
                std::cout << "-----------Height is = " << getHeight(tree) << "-----------\n\n";
                break;
            default:
                std::cout << "Invalid Case. Try another one\n";
        }
        std::cout << "Do you want to continue working with this tree? (y/n)\n";
        std::cin >> option;
        system("cls");
    }
}

int main(){
    Tree tree = nullptr;
    interface();
    return 0;
}