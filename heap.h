#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>
#include "Patient.h"

struct Node {
    Patient patient;
    uint64_t insertNum;
};

class TriageHeap {
    private:
        std::vector<Node> patientArray;
        uint64_t counter = 0;

        bool higherPriority(const Node& a, const Node& b) const {
            if (a.patient.getSeverity() != b.patient.getSeverity()) {
                return a.patient.getSeverity() < b.patient.getSeverity();
            }
            return a.insertNum < b.insertNum;
        }

        void siftUp(size_t i) {
            while (i > 0) {
                size_t p = (i - 1) / 2;
                if (!higherPriority(patientArray[i], patientArray[p])) break;
                std::swap(patientArray[i], patientArray[p]);
                i = p;
            }
        }

        void siftDown(size_t i) {
            size_t n = patientArray.size();
            while (true) {
                size_t best = i, left = 2 * i + 1, right = 2 * i + 2;
                if (left < n && higherPriority(patientArray[left], patientArray[best])) {
                    best = left;
                }
                if (right < n && higherPriority(patientArray[right], patientArray[best])) {
                    best = right;
                }
                if (best == i) break;
                std::swap(patientArray[i], patientArray[best]);
                i = best;
            }
        }

    public:
        void insert(const Patient& patient) {
            patientArray.push_back({patient, counter++});
            siftUp(patientArray.size() - 1);
        }

        Patient process() {
            if (patientArray.empty()) {
                throw std::out_of_range("process() called on empty TriageHeap");
            }
            Patient top = std::move(patientArray.front().patient);
            if (patientArray.size() > 1) {
                patientArray.front() = std::move(patientArray.back());
            }
            patientArray.pop_back();
            if (!patientArray.empty()) siftDown(0);
            return top;
        }

        bool remove(const Patient& patient) {
            size_t i = 0;
            while (i < patientArray.size() &&
                   patientArray[i].patient.getName() != patient.getName()) {
                ++i;
            }
            if (i == patientArray.size()) return false;

            if (i != patientArray.size() - 1) {
                patientArray[i] = std::move(patientArray.back());
            }
            patientArray.pop_back();
            if (i < patientArray.size()) {
                siftUp(i);
                siftDown(i);
            }
            return true;
        }

        const Patient& peek() const {
            if (patientArray.empty()) {
                throw std::out_of_range("peek() called on empty TriageHeap");
            }
            return patientArray.front().patient;
        }

        bool empty() const { return patientArray.empty(); }

        size_t size() const { return patientArray.size(); }
};
