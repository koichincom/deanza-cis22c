#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student
{
private:
    int sid;      // Student ID
    string sname; // Student Name

public:
    Student() : sid(0), sname("") {} // Default constructor

    Student(int id, const string &name) : sid(id), sname(name) {} // Parameterized constructor

    Student(const Student &other)
    { // Copy constructor
        sid = other.sid;
        sname = other.sname;
    }

    int getId() const { return sid; }        // Getter for ID
    string getName() const { return sname; } // Getter for name
};

class StudentEsa
{
private:
    Student **sap; // Array of Student pointers
    int cmz;       // Max size of the array
    int cnum;      // Current number of elements

public:
    StudentEsa(int maxSize)
    {
        cmz = maxSize;
        cnum = 0;
        sap = new Student *[cmz]; // Allocate memory for array of pointers
        for (int i = 0; i < cmz; ++i)
        {
            sap[i] = nullptr;
        }
    }

    ~StudentEsa()
    { // Destructor to clean up memory
        for (int i = 0; i < cnum; ++i)
        {
            delete sap[i]; // Free memory for each Student
        }
        delete[] sap; // Free array of pointers
    }

    // Copy constructor for deep copy
    StudentEsa(const StudentEsa &sep)
    {
        cmz = sep.cmz;
        cnum = sep.cnum;
        sap = new Student *[cmz];

        for (int i = 0; i < cnum; i++)
        {
            if (sep.sap[i] != nullptr)
            {
                sap[i] = new Student(*sep.sap[i]); // Deep copy of the Student object
            }
            else
            {
                sap[i] = nullptr;
            }
        }
    }

    int append(Student *stud)
    {
        if (cnum < cmz)
        {
            sap[cnum] = stud; // Append the new student
            cnum++;
            return cnum;
        }
        return -1; // Array is full
    }

    int insert(Student *stud, int index)
    {
        if (index < 0 || index > cnum || cnum >= cmz)
        {
            return -1; // Invalid index or array full
        }
        for (int i = cnum; i > index; --i)
        {
            sap[i] = sap[i - 1]; // Shift elements to the right
        }
        sap[index] = stud;
        cnum++;
        return cnum;
    }

    int remove(int index)
    {
        if (index < 0 || index >= cnum)
        {
            return -1; // Invalid index
        }
        delete sap[index]; // Free memory for the student at the given index
        for (int i = index; i < cnum - 1; ++i)
        {
            sap[i] = sap[i + 1]; // Shift elements to the left
        }
        cnum--;
        return cnum;
    }

    int set(Student *stud, int index)
    {
        if (index < 0 || index >= cmz)
        {
            return -1; // Invalid index
        }
        if (sap[index] != nullptr)
        {
            delete sap[index]; // Free the old memory
        }
        sap[index] = stud; // Set new student
        return index;
    }

    Student *get(int index) const
    {
        if (index < 0 || index >= cnum)
        {
            return nullptr; // Invalid index
        }
        return sap[index]; // Return the student at the given index
    }

    int getSize() const
    {
        return cnum; // Return the number of students in the array
    }
};

int main()
{
    int ssize, nops;
    char command;
    int index, num;
    string name;

    StudentEsa *esa = nullptr;

    cout << "Use input file: ";
    string infileName;
    cin >> infileName;
    cout << "Using input file " << infileName << endl;

    ifstream inp(infileName.c_str());
    if (!inp)
    {
        cerr << "Error: file " << infileName << " could not be opened" << endl;
        return 1;
    }

    inp >> ssize >> nops;
    cout << "Read Array size " << ssize << "  Read # commands " << nops << endl;

    esa = new StudentEsa(ssize);

    for (int i = 0; i < nops; i++)
    {
        inp >> command >> index >> num >> name;
        cout << "Command: " << command << "  " << index << "  " << num << "  " << name << endl;

        Student *stud;
        switch (command)
        {
        case 'A': // Append
            stud = new Student(num, name);
            esa->append(stud);
            break;
        case 'I': // Insert
            stud = new Student(num, name);
            esa->insert(stud, index);
            break;
        case 'R': // Remove
            esa->remove(index);
            break;
        case 'S': // Store (overwrite)
            stud = new Student(num, name);
            esa->set(stud, index);
            break;
        default:
            cout << "Illegal Command: " << command << endl;
        }
    }

    cout << "-------" << endl << endl;

    int x = esa->getSize();
    for (int i = 0; i < x; i++)
    {
        Student *stud = esa->get(i);
        cout << i << "  Student: ID = " << stud->getId() << "  Name = " << stud->getName() << endl;
    }

    delete esa; // Clean up the allocated memory
    return 0;
}
