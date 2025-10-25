//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Megan Mitchell
// Version     : 1.0
// Description : ABCU Advising Program 
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Define Course structure
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Global list of courses
vector<Course> courses;

// Function to trim spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Convert string to uppercase
string toUpperCase(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

// Load Data Structure
void LoadDataStructure() {
    string fileName = "CS 300 ABCU_Advising_Program_Input.csv"; 
    ifstream infile(fileName);

    courses.clear(); // clear existing data

    if (!infile.is_open()) {
        cout << "Error: File not found. Please check file path.\n" << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        vector<string> tokens;
        string token;
        stringstream ss(line);

        // Split by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        if (tokens.size() < 2) continue;

        Course newCourse;
        newCourse.courseNumber = toUpperCase(tokens[0]);
        newCourse.courseName = tokens[1];

        // If prerequisites exist
        for (size_t i = 2; i < tokens.size(); ++i) {
            newCourse.prerequisites.push_back(toUpperCase(tokens[i]));
        }

        courses.push_back(newCourse);
    }

    infile.close();
    cout << "Data structure loaded successfully!" << endl;
}

// Print Course List
void PrintCourseList() {
    if (courses.empty()) {
        cout << "Error: Please load course data first.\n" << endl;
        return;
    }

    // Sort alphabetically by course number (bubble sort style)
    for (size_t i = 0; i < courses.size() - 1; ++i) {
        for (size_t j = 0; j < courses.size() - i - 1; ++j) {
            if (courses[j].courseNumber > courses[j + 1].courseNumber) {
                swap(courses[j], courses[j + 1]);
            }
        }
    }

    cout << "Here is a sample schedule:\n" << endl;
    for (const auto& course : courses) {
        cout << course.courseNumber << ", " << course.courseName << endl;
    }
    cout << endl;
}

// Print Course Information
void PrintCourse() {
    if (courses.empty()) {
        cout << "Error: Please load data structure first.\n" << endl;
        return;
    }

    string input;
    cout << "What course do you want to know about? ";
    cin >> input;
    input = toUpperCase(input);

    bool found = false;
    for (const auto& course : courses) {
        if (course.courseNumber == input) {
            found = true;
            cout << "\n" << course.courseNumber << ", " << course.courseName << "\n" << endl;
            cout << "Prerequisites: ";

            if (course.prerequisites.empty()) {
                cout << "None" << endl;
            }
            else {
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    cout << course.prerequisites[i];
                    if (i + 1 < course.prerequisites.size()) cout << ", ";
                }
                cout << endl;
            }
            cout << endl;
            break;
        }
    }

    if (!found) {
        cout << "Invalid Course. Please try again.\n" << endl;
    }
}

// Main Menu
int main() {
    bool quit = false;
    string choice;

    cout << "\nWelcome to the course planner.\n" << endl;

    while (!quit) {
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "\nWhat would you like to do? ";
        cin >> choice;
        cout << endl;

        if (choice == "1") {
            LoadDataStructure();
        }
        else if (choice == "2") {
            PrintCourseList();
        }
        else if (choice == "3") {
            PrintCourse();
        }
        else if (choice == "9") {
            cout << "Thank you for using the course planner!" << endl;
            quit = true;
        }
        else {
            cout << choice << " is not a valid option.\n" << endl;
        }
    }

    return 0;
}

