#include <string>
#include "Patient.h"

struct Node {
    Patient patient;
    Node* next;

    Node(Patient patient_) : patient(patient_), next(nullptr) {};
};

class LL {
private:
    Node* head;
    Node* tail;

public:
    LL() : head(nullptr), tail(nullptr) {}; // Constructor
    ~LL(); // Destructor

    void insert(Patient patient); // Insert into heap
    void remove(Patient &patient); // Delete from heap
};


/* Insert function */
void LL::insert(Patient patient) {
    Node* node = new Node(patient);

    // There is no node in the LL
    if(!head) {
        head = node;
        tail = node;
        return;
    }

    /* There is only one node in the LL */
    if(!head->next) {
        head->next = node;
        tail = node;
        return;
    }

    /* 
     * If patient has Severity 5, automatically insert at the end. 
     * Arrival time is taken care of by FCFS basis. 
    */
    if(node->patient.getSeverity() == 5) {
        tail->next = node;
        tail = node;
        return;
    }

    Node* current = head;
    Node* prev = nullptr;
    while(current && current->patient.getSeverity() <= node->patient.getSeverity())  // Stops when the current node has higher Severity
    {
        prev = current;
        current = current->next;
    }
    prev->next = node;
    node->next = current;
    return;
}

/* Remove function */
void LL::remove(Patient &patient) { // Solves issue if a patient has the same name 
    
    // If there is no nodes in the LL, no patients
    if (!head) return;

    // If the patient is stored in the head node
    if (&(head->patient) == &patient) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;
    while (temp && &(temp->patient) != &patient) { // Traverse through all the patients
        prev = temp;
        temp = temp->next;
    }

    if (!temp) return; // If no matching patient was found, return

    prev->next = temp-> next; // If the patient was found, delete it
    delete temp;
}
