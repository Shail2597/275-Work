#include "intSet.h"
#include <iostream>

void intSet::swap(intSet& otherSet) {
    int* temp_elements = elements;
    elements = otherSet.elements;
    otherSet.elements = temp_elements;
    
    int temp_count = elementCount;
    elementCount = otherSet.elementCount;
    otherSet.elementCount = temp_count;
    
    int temp_cap = currentCapacity;
    currentCapacity = otherSet.currentCapacity;
    otherSet.currentCapacity = temp_cap;
}

int intSet::indexOf(int val) const {
    for (int k = 0; k < elementCount; k++) {
        if (elements[k] == val) {
            return k;
        }
    }
    return -1;
}

intSet::intSet() {
    currentCapacity = 4;
    elementCount = 0;
    elements = new int[currentCapacity];
}

intSet::intSet(const intSet& otherSet) : elements{new int[otherSet.currentCapacity]}, elementCount{otherSet.elementCount}, currentCapacity{otherSet.currentCapacity}  {
    for (int idx = 0; idx < elementCount; idx++) {
        elements[idx] = otherSet.elements[idx];
    }
}

intSet::intSet(intSet&& otherSet) : elements{otherSet.elements}, elementCount{otherSet.elementCount}, currentCapacity{otherSet.currentCapacity} {
    otherSet.elements = nullptr;
    otherSet.elementCount = 0;
    otherSet.currentCapacity = 0;
}

intSet& intSet::operator=(const intSet& otherSet) {
    if (this == &otherSet) {
        return *this;
    }
    intSet copySet(otherSet);
    swap(copySet);
    return *this;
}

intSet& intSet::operator=(intSet&& otherSet) {
    swap(otherSet);
    return *this;
}

intSet::~intSet() {
    delete[] elements;
}

bool intSet::contains(int val) const {
    return indexOf(val) != -1;
}

void intSet::add(int val) {
    if (contains(val)) {
        return;
    }
    
    if (elementCount == currentCapacity) {
        currentCapacity = (currentCapacity == 0) ? 4 : currentCapacity * 2;
        int* newElementsArray = new int[currentCapacity];
        for (int p = 0; p < elementCount; p++) {
            newElementsArray[p] = elements[p];
        }
        delete[] elements;
        elements = newElementsArray;
    }
    
    elements[elementCount++] = val;
}

void intSet::remove(int val) {
    int found_idx = indexOf(val);
    if (found_idx != -1) {
        elements[found_idx] = elements[elementCount - 1];
        elementCount--;
    }
}

intSet intSet::operator|(const intSet& otherSet) const {
    intSet unionResult(*this);
    for (int m = 0; m < otherSet.elementCount; m++) {
        unionResult.add(otherSet.elements[m]);
    }
    return unionResult;
}

intSet intSet::operator&(const intSet& otherSet) const {
    intSet intersectionResult;
    for (int m = 0; m < elementCount; m++) {
        if (otherSet.contains(elements[m])) {
            intersectionResult.add(elements[m]);
        }
    }
    return intersectionResult;
}

bool intSet::operator==(const intSet& otherSet) const {
    if (elementCount != otherSet.elementCount) {
        return false;
    }
    return isSubset(otherSet);
}

bool intSet::isSubset(const intSet& s) const {
    for (int m = 0; m < s.elementCount; m++) {
        if (!this->contains(s.elements[m])) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const intSet& otherSet) {
    if (otherSet.elementCount == 0) {
        out << "()";
        return out;
    }
    
    int* sorted_vals = new int[otherSet.elementCount];
    for (int p = 0; p < otherSet.elementCount; p++) {
        sorted_vals[p] = otherSet.elements[p];
    }
    
    for (int i = 0; i < otherSet.elementCount - 1; i++) {
        int least_pos = i;
        for (int j = i + 1; j < otherSet.elementCount; j++) {
            if (sorted_vals[j] < sorted_vals[least_pos]) {
                least_pos = j;
            }
        }
        if (least_pos != i) {
            int copy_val = sorted_vals[i];
            sorted_vals[i] = sorted_vals[least_pos];
            sorted_vals[least_pos] = copy_val;
        }
    }
    
    out << "(" << sorted_vals[0];
    for (int i = 1; i < otherSet.elementCount; i++) {
        out << ", " << sorted_vals[i];
    }
    out << ")";
    
    delete[] sorted_vals;
    return out;
}
