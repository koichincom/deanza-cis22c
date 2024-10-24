// CIS22C-HM2B : This single file will contain all the code for Homework 2. Program execution begins and ends here (in main).


using namespace std;
#include <iostream>
#include <fstream>

/*
    The following code file is divided into 4 sections

	1. The interface and code for Class Student  (supplied)
	2. The interface and code for class StudentEsa  (insert your HM1 code here)
	3. The interface and code for class StudentDQI  (The interface is supplied. HM2 is writing the code to implement this interface)
	4. The HM2 test program code (supplied)
*/


// 1.  ************************ class Student code included here  ***************************

class Student
{   // A VERY simple Student consisting only of the student's ID and Name
    // Both the interface and the code will be located here.

private:
    int sid; // Student ID
    string sname; // Full Name (Ex: KleinmanRon)

public:
    Student() { // Default constructor
        sid = 0; sname.clear();
    };
    Student(const Student& os) { // Copy constructor - overwrite internal variables
        sid = os.sid;  sname = os.sname;
    };
    Student(int id, string name) { // Initializer Constructor - set internal variables
        sid = id; sname = name;
    };
    ~Student() { // Default Destructor - clear string
        sname.clear();
    };

    //Getters 
    string getName() { return (sname); };
    int getId() { return (sid); };
};

//      ********************** End class Student ***************************************


// 2.   ********************** Insert "class StudentEsa" code from your homework 1 assignment here

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

//    ********************** End class StudentEsa ******************************


// 3. *************************** Homework 2.  insert the code for the StudentDQI into the StudentDQI interface below ***************


// class "StudentDQI   <Homework #2 - wraps (embeds) Extended Student Array (ESA) so it is invisible to external users of this class

class StudentDQI
{
private:
    StudentEsa *esa; // Internal ESA array
    int front;       // Index for the front element
    int back;        // Index for the back element
    int maxSize;

public:
    // Constructor that initializes ESA and centers the deque indices
    StudentDQI(int initialSize)
    {
        maxSize = initialSize * 2; // Double the size to handle both ends
        esa = new StudentEsa(maxSize);

        // Center the deque
        front = initialSize - 1; // Front starts just before the middle
        back = initialSize;      // Back starts at the middle
    }

    ~StudentDQI()
    {
        delete esa; // Clean up ESA memory
    }

    bool isEmpty() const
    {
        return front + 1 == back; // Deque is empty when front crosses back
    }

    int getSize() const
    {
        return back - front - 1; // Return the number of elements in the deque
    }

    // Push Front: Insert a new element at the front
    int pushFront(Student *student)
    {
        if (front < 0)
        {
            return -1; // No more space at the front
        }
        esa->set(student, front); // Store the student at the front
        front--;
        return 0;
    }

    // Push Back: Insert a new element at the back
    int pushBack(Student *student)
    {
        if (back >= maxSize)
        {
            return -1; // No more space at the back
        }
        esa->set(student, back); // Store the student at the back
        back++;
        return 0;
    }

    // Pop Front: Remove and return the element at the front
    Student *popFront()
    {
        if (isEmpty())
        {
            std::cout << "Deque is empty, cannot popFront." << std::endl;
            return nullptr;
        }
        front++;
        Student *student = esa->get(front);
        if (student)
        {
            std::cout << "Pop Front " << student->getId() << "  " << student->getName() << std::endl;
        }
        return student;
    }

    // Pop Back: Remove and return the element at the back
    Student *popBack()
    {
        if (isEmpty())
        {
            return nullptr; // Deque is empty
        }
        back--;
        return esa->get(back); // Return the back element
    }

    // Look at the front element without removing it
    Student *lookFront() const
    {
        if (isEmpty())
        {
            return nullptr;
        }
        return esa->get(front + 1); // Return the front element
    }

    // Look at the back element without removing it
    Student *lookBack() const
    {
        if (isEmpty())
        {
            return nullptr;
        }
        return esa->get(back - 1); // Return the back element
    }
};

// **************************** End class StudentDQI ******************************


// 4.  ***********************  Start of StudentDQI Test Program Code  ************

int main()
{ // Redirect Input
    string infileName; // Use if Input redirected
    string outfileName; // Use if output redirected 
    FILE** input = NULL;  // Recovering Cin

    // Command File Record entries
    int ssize; // Size of extended array
    int nops; // # operations to perform

    char command; // Command (G,Z   F,G,H   B,C,D)
            // Not all of the following are present in each command (Default given)
    int num;  // Student ID Number (-1 default)
    string name;  // Student Name (XXXX default)

    StudentDQI* dqi = NULL;   // Pointer to DeQue
    Student sc; // A class to collect Students is generated

    int x = 0; // Useful variables

    cout << "Use input file:  ";
    cin >> infileName; // Get name of file containing input data
    cout << "Using input file " << infileName << endl << endl;

    // Create an input file stream to read supplied file
    std::ifstream inp;
    inp.open(infileName.c_str());
    if (!inp) {
        cerr << "Error: file " << infileName.c_str() << "  could not be opened" << endl;
        exit(1);
    }

    // First line is array size and # commands to add, every subsequent line is one of:
    // 
    // GetSize:      S / -1 / -1
    // isEmpty:      Z / -1 / -1
    // 
    //  PushFront:   F / Student ID / Student Name
    //  PopFront:    G / -1 / -1
    //  LookFront :  H / -1 / -1
    //
    //  PushBack:    B / Student ID / Student Name
    //  PopBack:     C / -1 / -1
    //  LookBack :   D / -1 / -1

    // Get Size of Extended Array and # of commands
    // ssize is size of extended array, nops is # commands

    inp >> ssize >> nops;
    cout << "Read Array size " << ssize << "  Read # commands " << nops << endl;

    Student* stud;    // Array to hold pointer of created student.
    dqi = new StudentDQI(ssize);  // Create Dequeue of specified size.


    for (int i = 0; i < nops; i++) {  // Process Commands 
        //**************************************************************
        inp >> command;
        inp >> num;
        inp >> name;
        cout << "Command: " << command << "  " << num << "  " << name << endl;

        // Process each command
        switch (command)
        { // Convert to command for Extended Array
        case 'S':  // Get Size
            cout << "Size:  " << dqi->getSize() << endl;
            break;

        case 'Z':  // Check if Empty
            cout << "Empty : " << dqi->isEmpty() << endl;
            break;

        case 'F':  // Push Front
            stud = new Student(num, name);
            (void)dqi->pushFront(stud);
            cout << "Pushed Front " << num << "  " << name << endl;
            break;

        case 'G': // Pop Front
            stud = dqi->popFront();
            if (stud) { // Success
                cout << "Pop Front " << stud->getId() << "  " << stud->getName() << endl;
                delete (stud);
            }
            break;

        case 'H':  // Look Front
            stud = dqi->lookFront();
            if (stud) { // Success ... don't delete Student
                cout << "Look Front " << stud->getId() << "  " << stud->getName() << endl;
            }
            break;

        case 'B':  // Push Back
            stud = new Student(num, name);
            (void)dqi->pushBack(stud);
            cout << "Pushed Back " << num << "  " << name << endl;
            break;

        case 'C':  // Pop Back
            stud = dqi->popBack();
            if (stud) { // Success
                cout << "Pop Back " << stud->getId() << "  " << stud->getName() << endl;
                delete (stud);
            }
            break;


        case 'D':  // Look Back
            stud = dqi->lookBack();
            if (stud) { // Success ... don't delete Student
                cout << "Look Back " << stud->getId() << "  " << stud->getName() << endl;
            }
            break;

        default:
            cout << "Illegal Command:  " << command << endl;
        }
    }
    // Print out Current contents of extended array
    x = dqi->getSize(); // Get number of array elements
    cout << "------------------" << endl << "Start Popping from bottom  " << x << "  Elements queued" << endl << endl;

    while (stud = dqi->popBack())
    {
            cout << "Student: ID = " << stud->getId() << "  Name = " << stud->getName() << endl;
    }
    return (0);
};


// **********************************  End of test code  *************************************