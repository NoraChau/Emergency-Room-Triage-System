#include <string>
#include <list>
using namespace std;

class Patient
{
private:
    string firstN = "", lastN = "", age = "", sex = "", gender = "";
    list<string> currentMeds, symptoms;

public:
    Patient(); // Constructor
    ~Patient(); // Destructor

    // Setters
    void setFirstN(string firstN)                        {this->firstN = firstN;};
    void setLastN(string lastN)                        {this->lastN = lastN;};
    void setAge(string age)                            {this->age = age;};
    void setSex(string sex)                            {this->sex = sex;};
    void setGender(string gender)                      {this->gender = gender;};
    void setCurrentMeds(list<string> currentMeds)      {this->currentMeds = currentMeds;};
    void setSymptoms(list<string> symptoms)            {this->symptoms = symptoms;};

    // Getters
    string getfirstN()                  {return firstN;}
    string getlastN()                   {return lastN;}
    string getAge()                     {return age;}
    string getSex()                     {return sex;}
    string getGender()                  {return gender;}
    list<string> getCurrentMeds()       {return currentMeds;}
    list<string> getSymptoms()          {return symptoms;}
};

Patient::Patient(/* args */)
{
}

Patient::~Patient()
{
}

