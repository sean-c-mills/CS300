// Name        : ProjectTwo.cpp                   
// Author      : Sean Mills
// Description : Project Two BST
// =================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to hold the course data
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// This structure is used to create nodes for the BST
struct Node {
    Course course; // Holds the course information 
    Node* left;    // Points to a smaller course
    Node* right;   // Points to a larger course

    // Constructor that creates a node with a course
    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};

// Class that manages the binary search tree of courses
class BinarySearchTree {
private:
    Node* root; // Top node of the tree

    // Helper function to insert a course into the tree
    void insertNode(Node* node, Course course) {
        if (course.courseNumber < node->course.courseNumber) {
            // If the new course number is smaller, then go left
            if (node->left == nullptr) {
                node->left = new Node(course); // Add course to the left if empty
            }
            else {
                insertNode(node->left, course); // Keep going left
            }
        }
        else {
            // If the new course number is bigger, then go right
            if (node->right == nullptr) {
                node->right = new Node(course); // Add course to the right if empty
            }
            else {
                insertNode(node->right, course); // Keep going right
            }
        }
    }

    // Helper function to print the courses in order
    void inOrder(Node* node) {
        if (node == nullptr) return;

        inOrder(node->left); // Visits the left side first
        cout << node->course.courseNumber << ", " << node->course.courseName << endl;
        inOrder(node->right); // Visits the right next
    }

    // Check if each courses prerequisites are in the tree
    void validateNode(Node* node) {
        if (node == nullptr) return;

        for (string prereq : node->course.prerequisites) {
            if (Search(prereq) == nullptr) {
                cout << "Error: Prerequisite " << prereq
                    << " not found for course " << node->course.courseNumber << endl;
            }
        }

        validateNode(node->left); // Check left side
        validateNode(node->right); // Check right side
    }

public:
    // Constructor that sets the root to nothing
    BinarySearchTree() {
        root = nullptr;
    }

    // Insert the course into the tree
    void Insert(Course course) {
        if (root == nullptr) {
            root = new Node(course); // First course becomes the root
        }
        else {
            insertNode(root, course); // Adds more courses
        }
    }

    // Finds a course in the tree
    Course* Search(string courseNumber) {
        Node* current = root;
        while (current != nullptr) {
            if (courseNumber == current->course.courseNumber) {
                return &current->course; // If found
            }
            else if (courseNumber < current->course.courseNumber) {
                current = current->left; // Go to the left is smaller
            }
            else {
                current = current->right; // Go to the right if bigger
            }
        } 
        return nullptr; // If its not found
    }

    // Print all of the courses in order
    void PrintAllCoursesInOrder() {
        cout << "Here is a sample schedule:\n\n";
        inOrder(root);
    }

    // Checks that every courses prerequisite exists within the tree
    void ValidatePrerequisites() {
        validateNode(root);
    }
};

// Helper function to trim whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Change all the letters in a string to uppercase
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Load courses from CSV file
BinarySearchTree LoadCoursesFromFile(string filename, bool& success) {
    BinarySearchTree bst;
    ifstream file(filename);

    // If the file wont open then show an error
    if (!file.is_open()) {
        cout << "Error: Cannot open the file. Please check the file name." << endl;
        success = false;
        return bst;
    }

    success = true; // File opened with no problems

    string line;
    while (getline(file, line)) {
        vector<string> tokens;
        string token;
        stringstream ss(line);

        // Splits the line into pieces at each comma
        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token)); // Cleans up each piece
        }

        if (tokens.size() < 2) {
            cout << "Error: Line is missing course number or name\n\n";
            continue; // Skips bad lines
        }

        // Make a new course with the data
        Course newCourse;
        newCourse.courseNumber = toUpper(tokens[0]);
        newCourse.courseName = tokens[1];

        // Any remaining tokens are prerequisites
        for (size_t i = 2; i < tokens.size(); ++i) {
            string prereq = toUpper(trim(tokens[i]));
            if (!prereq.empty()) {
                newCourse.prerequisites.push_back(prereq);
            }
        }

        bst.Insert(newCourse); // Adds to the tree
    }

    file.close();
    bst.ValidatePrerequisites(); // Checks for missing prereqs
    return bst;
}

// Print a specific course and its prerequisites
void PrintCourseInformation(BinarySearchTree& bst, string courseNumber) {
    Course* course = bst.Search(toUpper(courseNumber));

    if (course == nullptr) {
        cout << "Course not found\n";
        return;
    }

    // Print courses number and name
    cout << course->courseNumber << ", " << course->courseName << endl;

    // Print prerequisites if there are any
    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None\n";
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            cout << course->prerequisites[i];
            if (i < course->prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Menu display function
void DisplayMenu() {
    cout << "1. Load Data Structure.\n";
    cout << "2. Print Course List.\n";
    cout << "3. Print Course.\n";
    cout << "9. Exit\n";
}

int main() {
    BinarySearchTree bst;
    bool dataLoaded = false; // This checks to see if the file has been loaded
    int choice;

    cout << "Welcome to the course planner.\n\n";

    while (true) {
        DisplayMenu();
        cout << endl << "What would you like to do? ";
        cin >> choice;

        // Makes sure the user enters a number and not letters
        if (cin.fail()) {
            cin.clear(); // Clear fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards the invalid input
            cout << "Invalid input: Please enter a number from the menu.\n\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
        case 1: {
            bool success = false;
            // Attempts to load the courses from the file
            bst = LoadCoursesFromFile("CS 300 ABCU_Advising_Program_Input.csv", success);
            if (!success) {
                return 1; // Exit the program if it fails
            }
            dataLoaded = true;
            cout << "File loaded successfully." << endl << endl;
            break;
        }
        case 2:
            // Won't allow any printing if the data isnt loaded first
            if (!dataLoaded) {
                cout << "Please load the data structure first.\n\n";
            }
            else {
                bst.PrintAllCoursesInOrder();
                cout << endl;
            }
            break;
        case 3:
            // Won't allow any searching if the data isn't loaded first
            if (!dataLoaded) {
                cout << "Please load the data structure first.\n\n";
            }
            else {
                string courseNum;
                cout << "What course do you want to know about? ";
                getline(cin, courseNum);
                PrintCourseInformation(bst, courseNum);
                cout << endl;
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!\n";
            return 0; // Exits the program
        default:
            cout << choice << " is not a valid option.\n\n";
        }
    }

    return 0;
}

