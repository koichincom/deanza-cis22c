// Implementation of the StudentEsa class
#include <iostream>
using namespace std;

class StudentEsa
{
private:
    Student **sap; // Pointer to an array of Student pointers
    int cnum;      // Current number of students in the array
    int cmz;       // Current max size of the array

    // Private method to handle resizing of the array
    void resizeArray()
    {
        cmz *= 2; // Double the size
        Student **newSap = new Student *[cmz];
        for (int i = 0; i < cnum; ++i)
        {
            newSap[i] = sap[i];
        }
        delete[] sap;
        sap = newSap;
    }

public:
    // 1. Normal Constructor. Create ESA of this size.
    StudentEsa(int ms)
    {
        sap = new Student *[cmz = ms];
        cnum = 0;
    }

    // 2. Default Constructor
    StudentEsa()
    {
        cmz = 10; // Default size of 10, chosen arbitrarily
        sap = new Student *[cmz];
        cnum = 0;
    }

    // 3. Copy Constructor
    StudentEsa(StudentEsa &sep)
    {
        cmz = sep.cmz;
        cnum = sep.cnum;
        sap = new Student *[cmz];
        for (int i = 0; i < cnum; ++i)
        {
            sap[i] = sep.sap[i];
        }
    }

    // 4. Default Destructor
    ~StudentEsa()
    {
        delete[] sap;
    }

    // 1. Get current number of students in the array
    int getSize()
    {
        return cnum;
    }

    // 2. Get pointer to the Student at the specified index
    Student *get(int index)
    {
        if (index < 0 || index >= cnum)
        {
            return nullptr; // Bad index
        }
        return sap[index];
    }

    // 3. Set: Replace the student pointer at the specified index
    int set(Student *student, int index)
    {
        if (index < 0 || index >= cnum)
        {
            return -1; // Bad index
        }
        sap[index] = student;
        return index;
    }

    // 4. Insert: Insert a student pointer at the specified index
    int insert(Student *student, int index)
    {
        if (index < 0 || index > cnum)
        {
            return -1; // Bad index
        }
        if (cnum >= cmz)
        {
            resizeArray(); // Resize if needed
        }
        for (int i = cnum; i > index; --i)
        {
            sap[i] = sap[i - 1];
        }
        sap[index] = student;
        cnum++;
        return index;
    }

    // 5. Remove: Remove the student pointer at the specified index
    int remove(int index)
    {
        if (index < 0 || index >= cnum)
        {
            return -1; // Bad index
        }
        for (int i = index; i < cnum - 1; ++i)
        {
            sap[i] = sap[i + 1];
        }
        cnum--;
        return cnum;
    }

    // 6. Append: Append a student pointer to the end of the array
    int append(Student *student)
    {
        if (cnum >= cmz)
        {
            resizeArray(); // Resize if needed
        }
        sap[cnum++] = student;
        return cnum - 1;
    }

    // 7. Prepend: Prepend a student pointer to the front of the array
    int prepend(Student *student)
    {
        return insert(student, 0);
    }
};