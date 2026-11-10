#include <iostream>;
#include <vector>
#include "Patient.cpp";

struct Node {
    Patient patient;
    uint64_t insertNum;
};

class TriageHeap {
    private:
        vector<Node> patientArray;
        uint64_t counter = 0;

        /**
         * Returns true if patient a should be serviced before patient b.
         *
         * @param a
         * @param b
         * @return
         */
        bool higherPriority(const Node& a, const Node& b) {
            if (a.patient.getSeverity() != b.patient.getSeverity()) {
                return a.patient.getSeverity() < b.patient.getSeverity();
            };
            return a.insertNum < b.insertNum;
        };

        /**
         *
         */
        void siftUp(size_t i) {
            while (i > 0) {
                size_t p = (i - 1) / 2;
                if (!higherPriority(patientArray[i], patientArray[p])) break;
                swap(patientArray[i], patientArray[p]);
                i = p;
            };
        };

        /**
         *
         */
        void siftDown(size_t i) {
            size_t n = patientArray.size();
            while (true) {
                size_t best = i, left = 2*i + 1, right = 2*i + 2;
                if (left < n && higherPriority(patientArray[left], patientArray[best])) {
                    best = left;
                }
                if (right < n && higherPriority(patientArray[right], patientArray[best])) {
                    best = right;
                }
                if (best == i) break;
                swap(patientArray[i], patientArray[best]);
                i = best;
            };

        }

    public:
        TriageHeap() {
            this->patientArray = {};
        };

        void insert(const Patient& patient) {
            patientArray.push_back({patient, counter++});
            siftUp(patientArray.size() - 1);
        };

        Patient process() {
            Patient top = move(patientArray.front().patient);
            patientArray.front() = move(patientArray.back());
            patientArray.pop_back();
            if (!patientArray.empty()) siftDown(0);
            return top;
        };

        bool remove(Patient patient) {
            size_t i = 0;
            while (i < patientArray.size() && patientArray[i].patient.getName() != patient.getName()) {
                ++i;
            }
            if (i == patientArray.size()) return false;

            patientArray[i] = move(patientArray.back());
            patientArray.pop_back();
            if (i < patientArray.size()) {
                siftUp(i);
                siftDown(i);
            }
            return true;
        };
};
