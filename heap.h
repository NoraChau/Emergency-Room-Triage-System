#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>
#include "Patient.h"

struct Node {
    Patient patient;
    uint64_t insertNum;
};

/**
 * Priority Queue implemented using a binary heap (implemented through arrays).
 */
class TriageHeap {
    private:
        std::vector<Node> patientArray;
        uint64_t counter = 0;

        /**
         * Helper function that checks which node has priority by insertion
         * order when they have the same severity value.
         *
         * @param a first node
         * @param b second node
         * @returns true if a has higher priority than b, false otherwise
         */
        bool higherPriority(const Node& a, const Node& b) const {
            if (a.patient.getSeverity() != b.patient.getSeverity()) {
                return a.patient.getSeverity() < b.patient.getSeverity();
            }
            return a.insertNum < b.insertNum;
        }

        /**
         * Helper function to move up nodes when they are too far down.
         *
         * Swaps the node at index i with its parent as long as it has higher
         * priority than the parent.
         *
         * @param i index of the node to move up
         */
        void moveUp(size_t i) {
            while (i > 0) {
                // identify the node's parent
                size_t parent = (i - 1) / 2;
                // check if node has priority over its parent, break if not
                if (!higherPriority(patientArray[i], patientArray[parent])) break;
                // swap the nodes
                std::swap(patientArray[i], patientArray[parent]);
                i = parent;
            }
        }

        /**
         * Helper function to move nodes down when they are too high up.
         *
         * Swaps the node at index i with its children as long as that child has
         * higher priority than it self.
         *
         * @param i index of the node to move down
         */
        void moveDown(size_t i) {
            size_t n = patientArray.size();
            while (true) {
                // identify the left child and right child of node i
                size_t best = i, left = 2 * i + 1, right = 2 * i + 2;
                // check whether the left child has priority over the current node
                if (left < n && higherPriority(patientArray[left], patientArray[best])) {
                    best = left;
                }
                // check whether the right child has priority over the current node
                if (right < n && higherPriority(patientArray[right], patientArray[best])) {
                    best = right;
                }
                // break if neither left or right child nodes have priority
                if (best == i) break;
                // swap the current node with whatever child node has priority
                std::swap(patientArray[i], patientArray[best]);
                i = best;
            }
        }

        /**
         * Helper function to check if the queue is empty.
         *
         * @returns true if queue is empty, false otherwise
         */
        bool empty() const {
            return patientArray.empty();
        }

        /**
         * Helper function that returns the size of the queue.
         *
         * @return queue size
         */
        size_t size() const {
            return patientArray.size();
        }

    public:
        /**
         * Adds a patient to the queue.
         *
         * Patient is appended to the end of the queue, and moved up
         * to its correct position by priority.
         *
         * @param patient patient to be inserted into the queue
         */
        void insert(const Patient& patient) {
            // add patient to the end of the queue
            patientArray.push_back({patient, counter++});
            // move patient up the tree to the correct spot
            moveUp(patientArray.size() - 1);
        }

        /**
         * Removes and returns the highest priority patient.
         *
         * The last node in the tree fills the root and is then
         * moved down, so the next priority patient moves to the top
         * to maintain the priority queue structure.
         *
         * @return the patient that was processed
         * @throw std::out_of_range if the queue is empty
         */
        Patient process() {
            // check if queue is empty
            if (patientArray.empty()) {
                throw std::out_of_range("Queue is empty.");
            }

            // select the highest priority patient
            Patient top = std::move(patientArray.front().patient);
            if (patientArray.size() > 1) {
                // move the tail patient to the head of the queue
                patientArray.front() = std::move(patientArray.back());
            }
            // remove old tail node copy
            patientArray.pop_back();
            // move the new head down as needed to restore priority queue
            if (!patientArray.empty()) moveDown(0);
            return top;
        }

        /**
         * Removes any specific patient from the queue by name.
         *
         * The last node fills the gap, and is then moved up or
         * moved down as needed to restore the priority queue.
         *
         * @param patient patient to be removed from the queue
         * @returns true if the patient was found and removed, false otherwise
         */
        bool remove(const Patient& patient) {
            size_t i = 0;
            // search for a patient in the queue whose name matches
            while (i < patientArray.size() &&
                patientArray[i].patient.getName() != patient.getName()) {
                ++i;
            }
            // return false if patient was not found
            if (i == patientArray.size()) return false;

            // move the tail node to the patient-to-be-removed's spot
            if (i != patientArray.size() - 1) {
                patientArray[i] = std::move(patientArray.back());
            }
            // remove old tail node copy
            patientArray.pop_back();
            // move node up and down as needed to restore priority queue
            if (i < patientArray.size()) {
                moveUp(i);
                moveDown(i);
            }
            return true;
        }

        /**
         * Helper function to view head of queue without removing it.
         *
         * @return patient at the head of the queue
         * @throw std::out_of_range if queue is empty
         */
        const Patient& peek() const {
            if (patientArray.empty()) {
                throw std::out_of_range("Queue is empty.");
            }
            return patientArray.front().patient;
        }
};
