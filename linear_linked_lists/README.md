# Linked Lists

## Node.h

A Node class for a linked list of Student objects.

Notes:

- Includes a `Student.h` file for the Student class. If the Student class is implemented without a `.h` file, line `3` in `Node.h` should be adjusted accordingly. 

- Constructor: `Node(Student*)`

  - Default constructor not implemented, as the Student class would also need a default constructor. It is commented out below the first constructor. 
  
- Destructor: `~Node()`

- Getters/Setters:

  - `setNext(Node*)`: set the pointer to the next element in the list to be the passed-in Node.

  - `getNext()`: get the next Node in the list.

  - `getStudent()`: get the Student for the current Node.

## Node.cpp

Implements all functions detailed in `Node.h`, with default constructor implementation commented out below the primary constructor. 

Notes:

- The constructor for a Node sets the pointer to the next object as `NULL`.

- The destructor for a Node calls the Student class destructor. 