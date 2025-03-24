#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
    string name;
    int id;
    string address;
    string phoneNumber;
    string email;

public:
    Person(const string& name, int id, const string& address, const string& phoneNumber, const string& email)
        : name(name), id(id), address(address), phoneNumber(phoneNumber), email(email) {}

    virtual ~Person() {}

    virtual void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
    }

    void updateInfo(const string& address, const string& phoneNumber, const string& email) {
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->email = email;
    }

    string getName() const {
        return name;
    }
};

class Student : public Person {
private:
    string* coursesEnrolled;
    int courseCount;
    int maxCourses;
    double gpa;
    int enrollmentYear;

public:
    Student(const string& name, int id, const string& address, const string& phoneNumber, const string& email,
            double gpa, int enrollmentYear, int maxCourses = 10)
        : Person(name, id, address, phoneNumber, email), gpa(gpa), enrollmentYear(enrollmentYear), courseCount(0), maxCourses(maxCourses) {
        coursesEnrolled = new string[maxCourses];
    }

    ~Student() {
        delete[] coursesEnrolled;
    }

    void addCourse(const string& course) {
        if (courseCount < maxCourses) {
            coursesEnrolled[courseCount++] = course;
        } else {
            cout << "Error: Maximum courses reached for student " << name << endl;
        }
    }

    void displayInfo() const override {
        Person::displayInfo();
        cout << "GPA: " << gpa << endl;
        cout << "Enrollment Year: " << enrollmentYear << endl;
        cout << "Courses Enrolled: ";
        for (int i = 0; i < courseCount; ++i) {
            cout << coursesEnrolled[i];
            if (i < courseCount - 1) cout << ", ";
        }
        cout << endl << "------------------------------------" << endl;
    }
};

class Professor : public Person {
private:
    string department;
    string* coursesTaught;
    int taughtCount;
    int maxTaught;
    double salary;

public:
    Professor(const string& name, int id, const string& address, const string& phoneNumber, const string& email,
              const string& department, double salary, int maxTaught = 10)
        : Person(name, id, address, phoneNumber, email), department(department), salary(salary), taughtCount(0), maxTaught(maxTaught) {
        coursesTaught = new string[maxTaught];
    }

    ~Professor() {
        delete[] coursesTaught;
    }

    void addCourseTaught(const string& course) {
        if (taughtCount < maxTaught) {
            coursesTaught[taughtCount++] = course;
        } else {
            cout << "Error: Maximum courses reached for professor " << name << endl;
        }
    }

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Department: " << department << endl;
        cout << "Salary: $" << salary << endl;
        cout << "Courses Taught: ";
        for (int i = 0; i < taughtCount; ++i) {
            cout << coursesTaught[i];
            if (i < taughtCount - 1) cout << ", ";
        }
        cout << endl << "------------------------------------" << endl;
    }
};

class Staff : public Person {
private:
    string department;
    string position;
    double salary;

public:
    Staff(const string& name, int id, const string& address, const string& phoneNumber, const string& email,
          const string& department, const string& position, double salary)
        : Person(name, id, address, phoneNumber, email), department(department), position(position), salary(salary) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Department: " << department << endl;
        cout << "Position: " << position << endl;
        cout << "Salary: $" << salary << endl;
        cout << "------------------------------------" << endl;
    }
};

class Course {
private:
    int courseId;
    string courseName;
    int credits;
    Professor* instructor;
    string schedule;
    Student** enrolledStudents;
    int studentCount;
    int maxStudents;

public:
    Course(int courseId, const string& courseName, int credits, Professor* instructor, const string& schedule, int maxStudents = 20)
        : courseId(courseId), courseName(courseName), credits(credits), instructor(instructor), studentCount(0), maxStudents(maxStudents) {
        enrolledStudents = new Student * [maxStudents];
    }

    ~Course() {
        delete[] enrolledStudents;
    }

    void registerStudent(Student* student) {
        if (studentCount < maxStudents) {
            enrolledStudents[studentCount++] = student;
            student->addCourse(courseName);
        } else {
            cout << "Error: Maximum students reached for course " << courseName << endl;
        }
    }

    void calculateGrades() const {
        cout << "Calculating grades for course: " << courseName << "..." << endl;
    }

    void displayCourseInfo() const {
        cout << "Course ID: " << courseId << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credits: " << credits << endl;
        cout << "Instructor: " << instructor->getName() << endl;
        cout << "Schedule: " << schedule << endl;
        cout << "Enrolled Students: ";
        for (int i = 0; i < studentCount; ++i) {
            cout << enrolledStudents[i]->getName();
            if (i < studentCount - 1) cout << ", ";
        }
        cout << endl << "------------------------------------" << endl;
    }
};

int main() {
    Student student1("Alice", 1001, "123 Main St", "555-1234", "alice@example.com", 3.8, 2022);
    Student student2("Bob", 1002, "456 Lake Dr", "555-6789", "bob@example.com", 3.5, 2023);

    Professor professor1("Dr. Smith", 2001, "456 Oak Ave", "555-5678", "smith@example.com", "Computer Science", 80000.0);
    Staff staff1("John Doe", 3001, "789 Pine Ln", "555-9012", "john@example.com", "Administration", "Manager", 60000.0);

    Course course1(101, "Introduction to Programming", 3, &professor1, "Mon/Wed 10:00 AM");
    course1.registerStudent(&student1);
    course1.registerStudent(&student2);

    cout << "\n=== STUDENT INFO ===" << endl;
    student1.displayInfo();
    student2.displayInfo();

    cout << "\n=== PROFESSOR INFO ===" << endl;
    professor1.displayInfo();

    cout << "\n=== STAFF INFO ===" << endl;
    staff1.displayInfo();

    cout << "\n=== COURSE INFO ===" << endl;
    course1.displayCourseInfo();

    cout << "\nUpdating student1 information..." << endl;
    student1.updateInfo("999 New Address", "555-9999", "alice_new@example.com");
    student1.displayInfo();

    return 0;
}
