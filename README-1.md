# 🎓 Student Management System

A modular and dynamic student management system demonstrating data structures, sorting algorithms, and structured programming in C.

## Features
- Dynamic student and subject management using arrays and structures
- Multi-criteria sorting (name, subject, total, average)
- Real-time calculation of total, average, and pass/fail status
- Input validation for names, marks (0–100), and menu choices
- Formatted tabular output for readability

## How to Compile & Run

```bash
gcc student_management.c -o student_management
./student_management
```

> Requires a C compiler (GCC recommended). Works on Linux, macOS, and Windows (via MinGW or WSL).

## Sample Output

```
-------------------------------------------------------------
Name         Roll  Subject1   Subject2  Total    Avg      Result
-------------------------------------------------------------
Alice        101   95         88        183      91.50    PASS
Bob          102   72         65        137      68.50    PASS
Charlie      103   38         70        108      54.00    FAIL
-------------------------------------------------------------
```

## Project Structure

```
student_management.c   # Single-file implementation
README.md
```

## Concepts Used
- Structures (`struct`)
- Arrays and array of structures
- Functions and modular design
- Bubble sort (multi-criteria)
- Input validation

## 🎯 Learning Outcomes
- Designed modular C programs using functions and structures
- Implemented dynamic data handling using arrays
- Applied sorting algorithms with multiple conditions
- Improved problem-solving and debugging skills

## 🚀 Future Improvements
- File handling for persistent storage
- Linked list implementation for dynamic memory management
- GUI-based version

## Limitations
- Maximum 100 students and 10 subjects (configurable via `#define`)
- Names cannot contain spaces (single-word only)
- Data is not saved between sessions (no file I/O)
