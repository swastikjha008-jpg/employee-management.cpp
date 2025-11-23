#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Employee {
    int id;
    string name;
    string department;
    double salary;
    int age;
    bool isActive; // true = active, false = deleted
};

// ---------- Function Declarations ----------
void loadFromFile(vector<Employee>& employees, const string& filename);
void saveToFile(const vector<Employee>& employees, const string& filename);

void addEmployee(vector<Employee>& employees);
void displayAllEmployees(const vector<Employee>& employees);
void searchEmployeeById(const vector<Employee>& employees);
void updateEmployee(vector<Employee>& employees);
void deleteEmployee(vector<Employee>& employees);

int findEmployeeIndexById(const vector<Employee>& employees, int id);
void clearInput();

// ---------- Main ----------
int main() {
    vector<Employee> employees;
    const string filename = "employees.txt";
    int choice = 0;

    // Load existing data (if any)
    loadFromFile(employees, filename);

    do {
        cout << "\n=====================================\n";
        cout << "       Employee Management System    \n";
        cout << "=====================================\n";
        cout << "1. Add New Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee by ID\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addEmployee(employees);
                saveToFile(employees, filename);
                break;
            case 2:
                displayAllEmployees(employees);
                break;
            case 3:
                searchEmployeeById(employees);
                break;
            case 4:
                updateEmployee(employees);
                saveToFile(employees, filename);
                break;
            case 5:
                deleteEmployee(employees);
                saveToFile(employees, filename);
                break;
            case 6:
                cout << "\n👋 Exiting Employee Management System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

// ---------- Helper to Clear Invalid Input ----------
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ---------- File Handling ----------
void loadFromFile(vector<Employee>& employees, const string& filename) {
    ifstream file(filename);
    if (!file) {
        // No file yet, that's fine.
        return;
    }

    employees.clear();
    Employee emp;
    string line;

    while (getline(file, line)) {
        // Expected format: id|name|department|salary|age|isActive
        if (line.empty()) continue;

        size_t pos = 0;
        size_t nextPos;

        // id
        nextPos = line.find('|', pos);
        emp.id = stoi(line.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        // name
        nextPos = line.find('|', pos);
        emp.name = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        // department
        nextPos = line.find('|', pos);
        emp.department = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        // salary
        nextPos = line.find('|', pos);
        emp.salary = stod(line.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        // age
        nextPos = line.find('|', pos);
        emp.age = stoi(line.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        // isActive
        emp.isActive = (line.substr(pos) == "1");

        employees.push_back(emp);
    }

    file.close();
}

void saveToFile(const vector<Employee>& employees, const string& filename) {
    ofstream file(filename, ios::trunc);
    if (!file) {
        cout << "⚠️ Error opening file for saving data.\n";
        return;
    }

    for (const auto& emp : employees) {
        file << emp.id << "|"
             << emp.name << "|"
             << emp.department << "|"
             << emp.salary << "|"
             << emp.age << "|"
             << (emp.isActive ? "1" : "0") << "\n";
    }

    file.close();
}

// ---------- Core Features ----------

void addEmployee(vector<Employee>& employees) {
    Employee emp;
    cout << "\n--- Add New Employee ---\n";

    cout << "Enter Employee ID: ";
    cin >> emp.id;
    clearInput();

    // Check for duplicate ID
    if (findEmployeeIndexById(employees, emp.id) != -1) {
        cout << "⚠️ Employee with this ID already exists. Try a different ID.\n";
        return;
    }

    cout << "Enter Name: ";
    getline(cin, emp.name);

    cout << "Enter Department: ";
    getline(cin, emp.department);

    cout << "Enter Salary: ";
    cin >> emp.salary;
    clearInput();

    cout << "Enter Age: ";
    cin >> emp.age;
    clearInput();

    emp.isActive = true;

    employees.push_back(emp);
    cout << "✅ Employee added successfully!\n";
}

void displayAllEmployees(const vector<Employee>& employees) {
    cout << "\n--- Employee List ---\n";

    if (employees.empty()) {
        cout << "No employee records found.\n";
        return;
    }

    cout << left << setw(6) << "ID"
         << setw(20) << "Name"
         << setw(15) << "Department"
         << setw(10) << "Salary"
         << setw(6)  << "Age"
         << setw(12) << "Status"
         << "\n";

    cout << string(69, '-') << "\n";

    for (const auto& emp : employees) {
        cout << left << setw(6) << emp.id
             << setw(20) << emp.name
             << setw(15) << emp.department
             << setw(10) << fixed << setprecision(2) << emp.salary
             << setw(6)  << emp.age
             << setw(12) << (emp.isActive ? "Active" : "Deleted")
             << "\n";
    }
}

int findEmployeeIndexById(const vector<Employee>& employees, int id) {
    for (size_t i = 0; i < employees.size(); ++i) {
        if (employees[i].id == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void searchEmployeeById(const vector<Employee>& employees) {
    cout << "\n--- Search Employee by ID ---\n";
    if (employees.empty()) {
        cout << "No employee records to search.\n";
        return;
    }

    int id;
    cout << "Enter Employee ID: ";
    cin >> id;
    clearInput();

    int index = findEmployeeIndexById(employees, id);
    if (index == -1) {
        cout << "❌ No employee found with ID " << id << ".\n";
        return;
    }

    const Employee& emp = employees[index];
    cout << "\nEmployee Found:\n";
    cout << "ID        : " << emp.id << "\n";
    cout << "Name      : " << emp.name << "\n";
    cout << "Department: " << emp.department << "\n";
    cout << "Salary    : " << fixed << setprecision(2) << emp.salary << "\n";
    cout << "Age       : " << emp.age << "\n";
    cout << "Status    : " << (emp.isActive ? "Active" : "Deleted") << "\n";
}

void updateEmployee(vector<Employee>& employees) {
    cout << "\n--- Update Employee ---\n";
    if (employees.empty()) {
        cout << "No employee records to update.\n";
        return;
    }

    int id;
    cout << "Enter Employee ID to update: ";
    cin >> id;
    clearInput();

    int index = findEmployeeIndexById(employees, id);
    if (index == -1) {
        cout << "❌ No employee found with ID " << id << ".\n";
        return;
    }

    Employee& emp = employees[index];
    cout << "Editing Employee: " << emp.name << " (ID: " << emp.id << ")\n";

    cout << "Enter new Name (leave empty to keep same): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        emp.name = newName;
    }

    cout << "Enter new Department (leave empty to keep same): ";
    string newDept;
    getline(cin, newDept);
    if (!newDept.empty()) {
        emp.department = newDept;
    }

    cout << "Enter new Salary (or -1 to keep same): ";
    double newSalary;
    cin >> newSalary;
    clearInput();
    if (newSalary >= 0) {
        emp.salary = newSalary;
    }

    cout << "Enter new Age (or -1 to keep same): ";
    int newAge;
    cin >> newAge;
    clearInput();
    if (newAge >= 0) {
        emp.age = newAge;
    }

    cout << "✅ Employee updated successfully!\n";
}

void deleteEmployee(vector<Employee>& employees) {
    cout << "\n--- Delete Employee ---\n";
    if (employees.empty()) {
        cout << "No employee records to delete.\n";
        return;
    }

    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;
    clearInput();

    int index = findEmployeeIndexById(employees, id);
    if (index == -1) {
        cout << "❌ No employee found with ID " << id << ".\n";
        return;
    }

    Employee& emp = employees[index];
    cout << "Are you sure you want to delete employee " << emp.name << " (ID: " << emp.id << ")? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInput();

    if (confirm == 'y' || confirm == 'Y') {
        emp.isActive = false; // mark as deleted (soft delete)
        cout << "✅ Employee marked as deleted.\n";
    } else {
        cout << "❎ Delete cancelled.\n";
    }
}
