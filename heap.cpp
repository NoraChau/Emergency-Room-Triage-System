#include <string>
#include "Patient.cpp"

struct Node {
    Patient patient;
    int score;
    Node* leftChild;
    Node* rightChild;

    Node(Patient patient_, int score_) : patient(patient_), score(score_) {};
};

class Heap
{
private:
    Node* front;

public:
    Heap(); // Constructor
    ~Heap(); // Destructor
    
    void insert(Patient patient); // Insert into heap
    void remove(Patient patient); // Delete from heap
    void sort(); // Prioritize
};

/* Constructor */
Heap::Heap() {
    // body
}

/* Destructor */
Heap::~Heap() {
    // body
}

/* Insert function */
void Heap::insert(Patient patient) {
    // body
}

/* Remove function */
void Heap::remove(Patient patient) {
    // body
}

/* Sort function */
void Heap::sort() {
    // body
}