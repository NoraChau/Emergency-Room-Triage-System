#include <string>
#include <list>
using namespace std;

class Patient
{
private:
    string name, severity;

public:
    Patient(string name, int severity) {  // Constructor
        this->name = name;
        this->severity = severity;
    };
    ~Patient(); // Destructor

    // Setters
    void setName(string name) {
        this->name = name;
    };
    void setSeverity(string severity) {
        this->severity = severity;
    };

};

Patient::~Patient()
{
}

