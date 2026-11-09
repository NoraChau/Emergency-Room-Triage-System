#include <string>
#include "Patient.cpp"

struct Node {
    Patient patient;
    int score;
    Node* leftChild;
    Node* rightChild;
};

class Heap
{
private:
    Node* front;

public:
    Heap(); // Constructor
    ~Heap(); // Destructor

    int insert(); // Insert into heap
    int remove(); // Delete from heap
    void sort(); // Prioritize

};


Heap::Heap()
{
}

Heap::~Heap()
{
}
