#include <string>
#include <list>
using namespace std;

class Patient
{
private:
    string name;
    int severity;

public:
    Patient(string name, int severity) {  // Constructor
        this->name = name;
        this->severity = severity;
    };
    ~Patient(); // Destructor

    // Setters
    void setName(string name) {
        this->name = name;
    }
    void setSeverity(int severity) {
        this->severity = severity;
    }

    // Getters
    string getName() const {
        return name;
    }
    int getSeverity() const {
        return severity;
    }

};

Patient::~Patient()
{
}

