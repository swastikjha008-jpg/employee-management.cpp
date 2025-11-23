What This Program Can Do

✔ Add new employees
✔ Display all employees
✔ Search employees by ID
✔ Modify employee information
✔ Delete employee records
✔ Automatically save data into employee.txt

🧠 Concepts Used

Classes & Objects
Constructors
File Handling (fstream)
Loops & Conditions
Strings
Basic CRUD operations
Persistent storage logic

📂 File Structure
employee-management.cpp   → Main program  
employee.txt              → Auto-generated storage file  
README.md                 → Documentation

🧱 Employee Data Fields

Each employee record contains:
🆔 Employee ID
👤 Name
💼 Job Position
💰 Salary
📅 Experience (years)

Sample line stored inside employee.txt:
101 Rahul Kumar Manager 45000 5

🎯 Feature Breakdown

➕ Add Employee
Take user input → append it to employee.txt.

📄 Display Employees
Reads file line-by-line → prints all employee records.

🔍 Search Employee
Enter ID → find and display matching employee details.

✏ Modify Employee
Locate employee by ID → update the record → rewrite updated list to the file.

❌ Delete Employee
Remove an employee by rewriting all records except the deleted one.

***** Employee Management System *****

1. Add Employee
2. Display All Employees
3. Search Employee
4. Modify Employee
5. Delete Employee
6. Exit

Enter your choice: 1

Enter Employee ID: 101
Enter Name: Rahul Kumar
Enter Post: Manager
Enter Salary: 45000
Enter Experience: 5

💾 Storage System
All data is saved permanently in:
📁 employee.txt
This ensures information remains safe even after your program closes.
Record added successfully!

📌 Why This Project Is Useful
Beginner-friendly
Great GitHub portfolio project
Demonstrates real-world CRUD logic
Helps understand how databases work using files
Shows clean coding structure

🛠 Built With
C++ (MinGW / g++)
VS Code
File Handling

© 2025 Swastik — Keep Coding, Keep Growing.
