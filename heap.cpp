#include <string>
#include "Patient.cpp"

struct Node {
    Patient patient;
    int score;
    Node* leftChild;
    Node* rightChild;

    Node(Patient patient_, int score_) : patient(patient_), score(score_), leftChild(nullptr), rightChild(nullptr) {};
};

class Heap
{
private:
    Node* front;
    Node* back;

public:
    Heap() : front(nullptr), back(nullptr) {}; // Constructor
    ~Heap(); // Destructor

    void insert(Patient patient, int score); // Insert into heap
    void remove(Patient patient); // Delete from heap
    void sort(); // Prioritize
};


/* Insert function */
void Heap::insert(Patient patient, int score) {
    Node* node = new Node(patient, score);

    if(!front) {  // nullptr returns a False, so if we want this case then we negate it
        front = node;
        back = node;
        return;
    }

}

/* Remove function */
void Heap::remove(Patient patient) {
    // body
}

/* Sort function */
void Heap::sort() {
    // body
}