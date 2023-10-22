#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

struct Course {
    std::string title;
    std::vector<std::string> prerequisites;
};

void loadDataStructure(std::unordered_map<std::string, Course>& courses) {
    // Open file
    std::string fileName;
    // courses.txt
    std::cout << "Enter the file name that contains the course data: ";
    std::cin >> fileName;
    std::ifstream file(fileName);

    // If file is already opened
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Parse the line and then create a course object
        // Add a course object to the course hashtable
        std::istringstream iss(line);
        std::string courseNumber;
        std::getline(iss, courseNumber,';');
        std::string title;
        std::getline(iss, title, ';');
        std::string prerequisites_str;
        std::getline(iss, prerequisites_str, ';');
        std::istringstream iss2(prerequisites_str);
        std::string prerequisite;
        std::vector<std::string> prerequisites;
        while (std::getline(iss2, prerequisite, ',')) {
            prerequisites.push_back(prerequisite);
        }
        Course course = { title, prerequisites };
        courses[courseNumber] = course;
    }
    file.close();
}

void printCourseList(const std::unordered_map<std::string, Course>& courses) {
    std::vector<std::string> courseNumbers;
    for (const auto& [courseNumber, course] : courses) {
        courseNumbers.push_back(courseNumber);
    }
    std::sort(courseNumbers.begin(), courseNumbers.end());
    
    for (const auto& courseNumber : courseNumbers) {
        std::cout << courseNumber << ": " << courses.at(courseNumber).title << std::endl;
    }
}

void printCourse(const std::unordered_map<std::string, Course>& courses) {
    std::string courseNumber;
    std::cout << "Enter the course number: ";
    std::cin >> courseNumber;

    if (courses.count(courseNumber) == 0) {
        std::cerr << "Error: Course not found" << std::endl;
        return;
    }

    const auto& course = courses.at(courseNumber);
    std::cout << "Course title: " << course.title << std::endl;
    std::cout << "Prerequisites: ";
    for (const auto& prerequisite : course.prerequisites) {
        std::cout << prerequisite << " ";
    }
    std::cout << std::endl;
}

int main() {
    bool exit = false;
    int option;
    std::unordered_map<std::string, Course> courses;

    while (!exit) {
        std::cout << "Main Menu:" << std::endl;
        std::cout << "1. Load Data Structure" << std::endl;
        std::cout << "2. Print Course List" << std::endl;
        std::cout << "3. Print Course" << std::endl;
        std::cout << "4. Exit" << std::endl;

        do {
            std::cout << "Enter an option: ";
            if (!(std::cin >> option)) {
                option = 0;
                // Clear any error states and ignore the rest of line to prevent an infinite loop
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (option < 1 || option > 4);

        switch (option) {
        case 1:
            loadDataStructure(courses);
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            printCourse(courses);
            break;
        case 4:
            std::cout << "Exiting program..." << std::endl;
            exit = true;
            break;
        }
    }
    return 0;
}