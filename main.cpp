#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Student
{
    int studentID;
    string name;
    string programme;
    string course;
    float score;
    char grade;
    Student* next;
};

class StudentList
{
private:
    Student* head;

public:
    StudentList()
    {
        head = NULL;
    }

    ~StudentList()
    {
        Student* current = head;

        while(current != NULL)
        {
            Student* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    int getValidInteger()
    {
        int value;

        while(true)
        {
            cin >> value;

            if(cin.fail())
            {
                cout << "Invalid input! Enter a number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                return value;
            }
        }
    }

    float getValidScore()
    {
        float score;

        while(true)
        {
            cin >> score;

            if(cin.fail())
            {
                cout << "Invalid input! Enter a numeric score: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if(score < 0 || score > 100)
            {
                cout << "Score must be between 0 and 100. Try again: ";
            }
            else
            {
                return score;
            }
        }
    }

    char calculateGrade(float score)
    {
        if(score >= 80)
            return 'A';
        else if(score >= 70)
            return 'B';
        else if(score >= 60)
            return 'C';
        else if(score >= 50)
            return 'D';
        else
            return 'F';
    }

    bool studentExists(int id)
    {
        Student* temp = head;

        while(temp != NULL)
        {
            if(temp->studentID == id)
                return true;

            temp = temp->next;
        }

        return false;
    }

    int getStudentCount()
    {
        int count = 0;
        Student* temp = head;

        while(temp != NULL)
        {
            count++;
            temp = temp->next;
        }

        return count;
    }

    void addStudent()
    {
        Student* newStudent = new Student;

        cout << "\nEnter Student ID: ";
        newStudent->studentID = getValidInteger();

        if(studentExists(newStudent->studentID))
        {
            cout << "\nDuplicate Student ID not allowed!\n";
            delete newStudent;
            return;
        }

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, newStudent->name);

        cout << "Enter Programme: ";
        getline(cin, newStudent->programme);

        cout << "Enter Course: ";
        getline(cin, newStudent->course);

        cout << "Enter Score (0-100): ";
        newStudent->score = getValidScore();

        newStudent->grade = calculateGrade(newStudent->score);
        newStudent->next = NULL;

        if(head == NULL)
        {
            head = newStudent;
        }
        else
        {
            Student* temp = head;

            while(temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newStudent;
        }

        cout << "\nStudent Added Successfully!\n";
    }

    void displayStudents()
    {
        if(head == NULL)
        {
            cout << "\nNo student records available.\n";
            return;
        }

        Student* temp = head;

        cout << "\n================================================================================================\n";
        cout << left
             << setw(10) << "ID"
             << setw(20) << "NAME"
             << setw(20) << "PROGRAMME"
             << setw(20) << "COURSE"
             << setw(10) << "SCORE"
             << setw(10) << "GRADE";
        cout << "\n================================================================================================\n";

        while(temp != NULL)
        {
            cout << left
                 << setw(10) << temp->studentID
                 << setw(20) << temp->name
                 << setw(20) << temp->programme
                 << setw(20) << temp->course
                 << setw(10) << temp->score
                 << setw(10) << temp->grade
                 << endl;

            temp = temp->next;
        }

        cout << "================================================================================================\n";
        cout << "Total Students: " << getStudentCount() << endl;
    }

    void searchStudent()
    {
        if(head == NULL)
        {
            cout << "\nNo student records available.\n";
            return;
        }

        int id;
        cout << "\nEnter Student ID to search: ";
        id = getValidInteger();

        Student* temp = head;

        while(temp != NULL)
        {
            if(temp->studentID == id)
            {
                cout << "\nStudent Found!\n";
                cout << "Student ID : " << temp->studentID << endl;
                cout << "Name       : " << temp->name << endl;
                cout << "Programme  : " << temp->programme << endl;
                cout << "Course     : " << temp->course << endl;
                cout << "Score      : " << temp->score << endl;
                cout << "Grade      : " << temp->grade << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "\nStudent not found.\n";
    }

    void updateScore()
    {
        if(head == NULL)
        {
            cout << "\nNo student records available.\n";
            return;
        }

        int id;
        cout << "\nEnter Student ID to update: ";
        id = getValidInteger();

        Student* temp = head;

        while(temp != NULL)
        {
            if(temp->studentID == id)
            {
                cout << "Current Score: " << temp->score << endl;
                cout << "Enter New Score: ";

                temp->score = getValidScore();
                temp->grade = calculateGrade(temp->score);

                cout << "\nScore Updated Successfully!\n";
                return;
            }

            temp = temp->next;
        }

        cout << "\nStudent not found.\n";
    }

    void deleteStudent()
    {
        if(head == NULL)
        {
            cout << "\nNo student records available.\n";
            return;
        }

        int id;
        cout << "\nEnter Student ID to delete: ";
        id = getValidInteger();

        if(head->studentID == id)
        {
            Student* temp = head;
            head = head->next;
            delete temp;

            cout << "\nStudent deleted successfully.\n";
            return;
        }

        Student* current = head;
        Student* previous = NULL;

        while(current != NULL && current->studentID != id)
        {
            previous = current;
            current = current->next;
        }

        if(current == NULL)
        {
            cout << "\nStudent not found.\n";
            return;
        }

        previous->next = current->next;
        delete current;

        cout << "\nStudent deleted successfully.\n";
    }

    void calculateAverage()
    {
        if(head == NULL)
        {
            cout << "\nNo student records available.\n";
            return;
        }

        float sum = 0;
        int count = 0;

        Student* temp = head;

        while(temp != NULL)
        {
            sum += temp->score;
            count++;
            temp = temp->next;
        }

        cout << "\nAverage Score: " << (sum / count) << endl;
    }

    void highestScore()
    {
        if(head == NULL)
        {
            cout << "\nNo student records available.\n";
            return;
        }

        Student* highest = head;
        Student* temp = head->next;

        while(temp != NULL)
        {
            if(temp->score > highest->score)
                highest = temp;

            temp = temp->next;
        }

        cout << "\n===== HIGHEST SCORING STUDENT =====\n";
        cout << "ID: " << highest->studentID << endl;
        cout << "Name: " << highest->name << endl;
        cout << "Score: " << highest->score << endl;
        cout << "Grade: " << highest->grade << endl;
    }

    void lowestScore()
    {
        if(head == NULL)
        {
            cout << "\nNo student records available.\n";
            return;
        }

        Student* lowest = head;
        Student* temp = head->next;

        while(temp != NULL)
        {
            if(temp->score < lowest->score)
                lowest = temp;

            temp = temp->next;
        }

        cout << "\n===== LOWEST SCORING STUDENT =====\n";
        cout << "ID: " << lowest->studentID << endl;
        cout << "Name: " << lowest->name << endl;
        cout << "Score: " << lowest->score << endl;
        cout << "Grade: " << lowest->grade << endl;
    }
};

int main()
{
    StudentList list;
    int choice;

    do
    {
        cout << "\n=================================================\n";
        cout << "      STUDENT RESULT MANAGEMENT SYSTEM\n";
        cout << "=================================================\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Search Student\n";
        cout << "4. Display Results\n";
        cout << "5. Update Score\n";
        cout << "6. Calculate Average Score\n";
        cout << "7. Find Highest Score\n";
        cout << "8. Find Lowest Score\n";
        cout << "9. Exit\n";
        cout << "\n";
        cout << "Enter Choice: ";

        choice = list.getValidInteger();

        switch(choice)
        {
            case 1:
                list.addStudent();
                break;

            case 2:
                list.deleteStudent();
                break;

            case 3:
                list.searchStudent();
                break;

            case 4:
                list.displayStudents();
                break;

            case 5:
                list.updateScore();
                break;

            case 6:
                list.calculateAverage();
                break;

            case 7:
                list.highestScore();
                break;

            case 8:
                list.lowestScore();
                break;

            case 9:
                cout << "\nThank you for using the system.\n";
                break;

            default:
                cout << "\nInvalid menu choice.\n";
        }

    } while(choice != 9);

    return 0;
}
