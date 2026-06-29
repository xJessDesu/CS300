// Jessica Paul
// 6/21/2026
// CS300 Project 2


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Course {
	string courseId;
	string courseName;
	vector<string> prerequisites;
};

void loadCourses(const string& csvPath, vector<Course>& courseList);

int main() {
	vector<Course> data;
	int choice = 0;
	string filename = "CS 300 ABCU_Advising_Program_Input.csv";
	string searchId;

	cout << "Welcome to the course planner." << endl;

	while (choice != 9) {
		cout << "\n1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl;
		cout << "What would you like to do? ";

		if (!(cin >> choice)) {
			cout << "Invalid input." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		switch (choice) {
		case 1:
			if (!data.empty()) {
				cout << "Courses already loaded" << endl;
			}

			else {
				loadCourses(filename, data);
				cout << "Courses loaded" << endl;
			}
			break;

		case 2:
			if (data.empty()) {
				cout << "No data loaded yet. Please select option 1 first." << endl;
			}
			else {
				sort(data.begin(), data.end(), [](const Course& a, const Course& b) {
					return a.courseId < b.courseId;
					});

				cout << "Here is a sample schedule:\n" << endl;
				for (const auto& course : data) {
					cout << course.courseId << ", " << course.courseName << endl;
				}
			}
			break;

		case 3:
			if (data.empty()) {
				cout << "No data loaded yet. Please select option 1 first." << endl;
			}
			else {
				cout << "What course do you want to know about? ";
				cin >> searchId;

				string upperSearchId = searchId;
				transform(upperSearchId.begin(), upperSearchId.end(), upperSearchId.begin(), ::toupper);

				bool found = false;
				for (const auto& course : data) {
					if (course.courseId == upperSearchId) {
						found = true;
						cout << course.courseId << ", " << course.courseName << endl;

						if (!course.prerequisites.empty()) {
							cout << "Prerequisites: ";
							for (size_t i = 0; i < course.prerequisites.size(); ++i) {
								cout << course.prerequisites[i];
								if (i < course.prerequisites.size() - 1) {
									cout << ", ";
								}
							}
							cout << endl;
						}
						break;
					}
				}

				if (!found) {
					cout << "Course " << searchId << " not found." << endl;
				}
			}
			break;

		case 9:
			cout << "Thank you for using the course planner!" << endl;
			break;

		default:
			cout << choice << " is not a valid option." << endl;
			break;
		}
	}

	return 0;
}

void loadCourses(const string& csvPath, vector<Course>& courseList) {
	ifstream file(csvPath);

	if (!file.is_open()) {
		cout << "Error: Could not open file " << csvPath << endl;
		return;
	}

	courseList.clear();
	string line;
	int count = 0;

	while (getline(file, line)) {
		stringstream iss(line);
		string cell;
		Course course;

		if (getline(iss, course.courseId, ',')) {
			if (getline(iss, course.courseName, ',')) {
				transform(course.courseId.begin(), course.courseId.end(), course.courseId.begin(), ::toupper);

				while (getline(iss, cell, ',')) {
					cell.erase(remove(cell.begin(), cell.end(), '\r'), cell.end());
					cell.erase(remove(cell.begin(), cell.end(), '\n'), cell.end());

					if (!cell.empty()) {
						transform(cell.begin(), cell.end(), cell.begin(), ::toupper);
						course.prerequisites.push_back(cell);
					}
				}
				courseList.push_back(course);
				count++;
			}
		}
	}

	file.close();
}