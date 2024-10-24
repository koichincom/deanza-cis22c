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
{ // A VERY simple Student consisting only of the student's ID and Name
  // Both the interface and the code will be located here.

private:
    int sid;      // Student ID
    string sname; // Full Name (Ex: KleinmanRon)

public:
    Student()
    { // Default constructor
        sid = 0;
        sname.clear();
    };
    Student(const Student &os)
    { // Copy constructor - overwrite internal variables
        sid = os.sid;
        sname = os.sname;
    };
    Student(int id, string name)
    { // Initializer Constructor - set internal variables
        sid = id;
        sname = name;
    };
    ~Student()
    { // Default Destructor - clear string
        sname.clear();
    };

    // Getters
    string getName() { return (sname); };
    int getId() { return (sid); };
};

//      ********************** End class Student ***************************************

// 2.   ********************** Insert "class StudentEsa" code from your homework 1 assignment here

class StudentEsa
{
private:           // Define whatever additional private variables you need
    Student **sap; // Underlying pointer to array of Student pointers, which you will allocate
    Student **tp;  // Optionally used in realloc
    int cnum;      // Number of students currently in array
    int cmz;       // Current Max size of the array (may need to be expanded)

public: // Publically supported methods YOU NEED TO IMPLEMENT.  Replace each declaration with complete code
        // ****************  Constructors / Destructor

    //  1. Normal Constructor.  Create ESA of this size.  May need to be resized later
    StudentEsa(int ms)
    {
        sap = new Student *[cmz = ms];
        cnum = 0;
        tp = NULL;
    }

    //  *** The code for this might look like:
    //
    //  StudentEsa(int ms) { // Allocate Enhanced Student Array capable of holding this many Student Ptrs
    //       sap = new Student* [cmz = ms]; // sap points to an array of Student pointers of size cmz
    //       cnum = 0; tp = NULL; // Initialize with no pointers currently in array
    //  }

    // 2. Default Constructor <Comment out, or use some predefined size, and EXPLAIN YOUR CHOICE>
    StudentEsa()
    {
        sap = new Student *[cmz = 10]; // Default size is 10
        cnum = 0;
        tp = NULL;
    }

    // 3. Copy Constructor  (what gets copied and what does not?)
    StudentEsa(StudentEsa &sep)
    {
        cmz = sep.cmz;
        cnum = sep.cnum;
        sap = new Student *[cmz];
        for (int i = 0; i < cnum; i++)
        {
            sap[i] = new Student(*sep.sap[i]);
        }
    };

    // 4. Default destructor  (what gets freed up and what does not?)
    ~StudentEsa()
    {
        for (int i = 0; i < cnum; i++)
        {
            delete sap[i];
        }
        delete[] sap;
    }

    // ******************* Remaining public functions of the Extended Student Array

    // 1. Return the number of Students in the Collection
    int getSize()
    {
        return cnum;
    }

    // 2. GET:  Get and return the ptr to the Student at the specified Array Index
    //          Error if the supplied index >= number of entries.  Return a NULL ptr
    Student *get(int index)
    {
        if ((index < 0) || (index >= cnum))
            return NULL; // This is a bad index
        return sap[index];
    }

    // *** The code for this might look like:

    //   Student* get (int idx) {
    //      if ((idx<0) || (idx>=cnum))  return (NULL);  // Bad index
    //      return (sap[idx]); // Otherwise return Student ptr at that index in the array
    //   }

    // 3. SET: Replace whatever is at the supplied index with the new Student ptr. Return index # on success
    // Error if the supplied index >= number of entries.  Return -1
    // <DO NOT Destruct the Student whose ptr is at the supplied index>
    //
    int set(Student *student, int index)
    {
        if ((index < 0) || (index >= cnum))
            return -1; // This is a pattern of bad index
        sap[index] = student;
        return index;
    }

    // 4. INSERT: Insert Student ptr at the supplied index, by first "pushing back" every subsequent element
    //    Error if the supplied index > number of entries.  Return -1
    //    OK if supplied index == number of entries (equivalent to an append)
    //    Note:  ESA size increases which may force a reallocation of the array.  Return index # on success
    int insert(Student *nsp, int index)
    {
        if (index > cnum || index < 0)
            return -1; // This is a bad index

        // Resize as needed
        if (cnum >= cmz)
        {
            cmz *= 2;
            tp = new Student *[cmz];
            for (int i = 0; i < cnum; i++)
            {
                tp[i] = sap[i];
            }
            delete[] sap;
            sap = tp;
        }

        // Move elements up
        for (int i = cnum; i > index; i--)
        {
            sap[i] = sap[i - 1];
        }
        sap[index] = nsp;
        cnum++;
        return index;
    }

    // 5. REMOVE: Delete specified array element by "pulling forward" every subsequent element
    //    Error if the supplied index >= number of entries.  Return -1.  Else decrement ESA size and return it
    //    Note: <DO NOT Destruct the Student whose ptr is at the supplied index>
    int remove(int index)
    {
        if ((index < 0) || (index >= cnum))
            return -1; // This is a bad index

        delete sap[index]; // Free the memory allocated for the Student pointer at the specified inex
        // Move elements down
        for (int i = index; i < cnum - 1; i++)
        {
            sap[i] = sap[i + 1];
        }
        cnum--;
        return cnum;
    }

    // 6. APPEND:  Append the ptr to the supplied Student to back of the ESA, bump ESA size
    //    Return index # of new entry on success, -1 on failure
    //    Note:  This may force a reallocation of the array.
    int append(Student *nsp)
    {
        if (cnum >= cmz)
        {
            cmz *= 2;
            tp = new Student *[cmz];
            for (int i = 0; i < cnum; i++)
            {
                tp[i] = sap[i];
            }
            delete[] sap;
            sap = tp;
        }
        sap[cnum++] = nsp;
        return cnum - 1;
    }
    // 7. PREPEND: Prepend the ptr to the supplied Student to the front of the ESA, increment ESA size
    //    Return 0 on success, -1 on failure
    //    Note:  This may force a reallocation of the array.
    int prepend(Student *nsp)
    {
        return insert(nsp, 0);
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
{                        // Redirect Input
    string infileName;   // Use if Input redirected
    string outfileName;  // Use if output redirected
    FILE **input = NULL; // Recovering Cin

    // Command File Record entries
    int ssize; // Size of extended array
    int nops;  // # operations to perform

    char command; // Command (G,Z   F,G,H   B,C,D)
                  // Not all of the following are present in each command (Default given)
    int num;      // Student ID Number (-1 default)
    string name;  // Student Name (XXXX default)

    StudentDQI *dqi = NULL; // Pointer to DeQue
    Student sc;             // A class to collect Students is generated

    int x = 0; // Useful variables

    cout << "Use input file:  ";
    cin >> infileName; // Get name of file containing input data
    cout << "Using input file " << infileName << endl
         << endl;

    // Create an input file stream to read supplied file
    std::ifstream inp;
    inp.open(infileName.c_str());
    if (!inp)
    {
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

    Student *stud;               // Array to hold pointer of created student.
    dqi = new StudentDQI(ssize); // Create Dequeue of specified size.

    for (int i = 0; i < nops; i++)
    { // Process Commands
        //**************************************************************
        inp >> command;
        inp >> num;
        inp >> name;
        cout << "Command: " << command << "  " << num << "  " << name << endl;

        // Process each command
        switch (command)
        {         // Convert to command for Extended Array
        case 'S': // Get Size
            cout << "Size:  " << dqi->getSize() << endl;
            break;

        case 'Z': // Check if Empty
            cout << "Empty : " << dqi->isEmpty() << endl;
            break;

        case 'F': // Push Front
            stud = new Student(num, name);
            (void)dqi->pushFront(stud);
            cout << "Pushed Front " << num << "  " << name << endl;
            break;

        case 'G': // Pop Front
            stud = dqi->popFront();
            if (stud)
            { // Success
                cout << "Pop Front " << stud->getId() << "  " << stud->getName() << endl;
                delete (stud);
            }
            break;

        case 'H': // Look Front
            stud = dqi->lookFront();
            if (stud)
            { // Success ... don't delete Student
                cout << "Look Front " << stud->getId() << "  " << stud->getName() << endl;
            }
            break;

        case 'B': // Push Back
            stud = new Student(num, name);
            (void)dqi->pushBack(stud);
            cout << "Pushed Back " << num << "  " << name << endl;
            break;

        case 'C': // Pop Back
            stud = dqi->popBack();
            if (stud)
            { // Success
                cout << "Pop Back " << stud->getId() << "  " << stud->getName() << endl;
                delete (stud);
            }
            break;

        case 'D': // Look Back
            stud = dqi->lookBack();
            if (stud)
            { // Success ... don't delete Student
                cout << "Look Back " << stud->getId() << "  " << stud->getName() << endl;
            }
            break;

        default:
            cout << "Illegal Command:  " << command << endl;
        }
    }
    // Print out Current contents of extended array
    x = dqi->getSize(); // Get number of array elements
    cout << "------------------" << endl
         << "Start Popping from bottom  " << x << "  Elements queued" << endl
         << endl;

    while (stud = dqi->popBack())
    {
        cout << "Student: ID = " << stud->getId() << "  Name = " << stud->getName() << endl;
    }
    return (0);
};

// **********************************  End of test code  *************************************