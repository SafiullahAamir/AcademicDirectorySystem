# **Academic Directory System**

## **1. Introduction**
The **Academic Directory System** is a student management application that allows administrators to manage student records, announcements, and feedback. It utilizes **DSA Concepts** like an **AVL tree** for student record management, a **queue** for feedback handling, and a **stack** for announcements. The system is built in **C++** and provides a console-based interface.

## **2. Features**
- **Login System:** Separate login credentials for admin and students.
- **Student Management:** Add, update, delete, and view student records.
- **Course & Timetable Management:** View assigned courses and timetable.
- **Fee Management:** Calculate fees based on scholarships.
- **Feedback System:** Students can submit feedback.
- **Announcements System:** Admin can post announcements.
- **File Handling:** Stores feedbacks and announcements in text files.

## **3. Data Structures Used**
#### **AVL Tree**
- Used for efficient student record storage and retrieval.
- Balancing operations (rotation) ensure O(log n) complexity for insertions and deletions.

#### **Queue (Singly Linked List)**
- Used to manage student feedback.
- Feedbacks are stored in a text file for persistence.

#### **Stack (Circular Implementation)**
- Used to store announcements.
- Implements a fixed-size circular stack.

## **4. Implementation Details**
- **Programming Language:** C++
- **Development Environment:** Visual Studio Code on Windows 11
- **File Handling:** Feedback and announcements stored in `feedbacks.txt` and `announcements.txt`.
- **CSV File Handling:** Stores student records in `data.csv`.

## **5. Code Overview**
- **`Admin` Class**: Handles student management, feedback, and announcements.
- **`AVL` Class**: Implements the AVL tree for student records.
- **`Student` Class**: Manages student functionalities like viewing courses and payments.
- **`Menu` Class**: Provides the UI for both admin and students.
- **`UserManager` Class**: Manages login authentication and data loading.

## **6. File Handling**
- `feedbacks.txt` - Stores student feedback.
- `announcements.txt` - Stores admin announcements.
- `data.csv` - Stores student records in CSV format for persistence.

## **7. Installation & Usage**
1. **Clone the repository**  
   ```sh
   git clone https://github.com/SafullahAamir/AcademicDirectorySystem.git
