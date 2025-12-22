# SCMS — Smart Course Management System

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-informational)
![Version](https://img.shields.io/badge/version-0.1.0-brightgreen)

SCMS is a simple, fast, and portable command‑line system for managing a small academic environment. It provides user authentication with roles, course management with enrollment and teacher assignment, attendance tracking, exams and marks, a lightweight report generator, and a minimal library system — all backed by plain files for easy setup.

## What It Does

-   Role‑based users: `Student`, `Teacher`, `Admin` (register/login, change password).
-   Courses: create/update/delete, teacher assignment, capacity limits, enroll/drop students.
-   Exams: create exams, enter marks with validation, view marks, generate reports.
-   Attendance: mark attendance by course/date, students can view their records.
-   Library: add books, issue/return with copy counts, transaction log.
-   Logging: structured logs to `logs/` for auditability.

Key modules live under [include/](include) and [src/](src), for example:

-   Auth: [AuthManager.h](include/AuthManager.h), [User.h](include/User.h)
-   Courses: [CourseManager.h](include/CourseManager.h), [Course.h](include/Course.h)
-   Exams: [ExamManager.h](include/ExamManager.h), [Exam.h](include/Exam.h), [ReportGenerator.h](include/ReportGenerator.h)
-   Attendance: [AttendanceManager.h](include/AttendanceManager.h), [AttendanceRecord.h](include/AttendanceRecord.h)
-   Library: [LibraryManager.h](include/LibraryManager.h), [Book.h](include/Book.h)
-   App entry: [main.cpp](src/main.cpp)

## Why It’s Useful

-   Minimal dependencies: C++20 + CMake; data persisted in CSV/flat files under [data/](data).
-   Clear separation of concerns: managers per domain, easy to extend.
-   Deterministic tests you can run locally; great starter for coursework or prototypes.
-   Cross‑platform: builds with MSVC, MinGW, Clang, or GCC.

## Getting Started

### Prerequisites

-   CMake 3.20+
-   A C++20 compiler
    -   Windows: MSVC (Visual Studio 2022) or MinGW‑w64
    -   Linux: GCC 10+ or Clang 12+
    -   macOS: Apple Clang 14+

### Build

```bash
# From the repository root
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON
cmake --build build --config Release
```

Artifacts:

-   App binary: `build/scms` (or `build/Release/scms.exe` on MSVC)
-   Test binaries: one per file in [tests/](tests) when `BUILD_TESTS=ON`

### Run

```bash
# Run the CLI app
./build/scms            # Linux/macOS
./build/Release/scms.exe  # Windows (MSVC)
./build/scms.exe          # Windows (MinGW)
```

Default data locations (created on demand if missing):

-   Users: `data/users.csv`
-   Courses: `data/courses.csv`
-   Attendance: `data/attendance/`
-   Exams: `data/exams/`
-   Library: `data/books.dat`, transactions `logs/transaction.log`
-   App log: `logs/scms.log`

Sample data files are provided under [data/](data).

### Quick Usage (CLI)

The app is menu‑driven. A typical flow:

1. Login or Register

-   Register with role (Student/Teacher/Admin)
-   Login with your username/password

2. Explore and act (role‑specific)

-   Students: list courses, enroll/drop; view attendance; view exam marks; list/issue/return books
-   Teachers: view assigned courses; view students; create exams; enter marks; mark/view attendance
-   Admins: add/update/delete courses; assign teachers; add library books

Example interactions you’ll see:

```
==== Smart CMS ====
1) Login
2) Register
3) Exit
```

```
==== Main Menu (alice) ====
1) View profile
2) List all courses
3) Change password
4) Enroll in course
5) Drop course
...
```

### Running Tests

Tests are simple main‑based executables registered with CTest.

```bash
# From the repository root
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build --config Release
ctest --test-dir build --output-on-failure
```

You can also run individual test binaries, e.g. `build/test_auth` or `build/Release/test_exam.exe`.

## Project Structure

-   [include/](include): Public headers for managers, models, and utilities
-   [src/](src): Implementations and [main.cpp](src/main.cpp)
-   [data/](data): CSV and flat‑file persistence
-   [logs/](logs): Application and library transaction logs
-   [tests/](tests): Lightweight tests per domain
-   [CMakeLists.txt](CMakeLists.txt): Build targets and test registration

## Help & Support

-   Open an issue with reproducible steps and expected vs actual behavior
-   Check logs in [logs/](logs) for diagnostics
-   Review example flows in [tests/](tests) to understand expected behavior

## Notes

-   C++ standard: C++20 (see [CMakeLists.txt](CMakeLists.txt))
-   On older GCC (< 9), filesystem linkage is handled in the build config
-   No external runtime dependencies beyond the standard library
