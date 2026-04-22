#include "intSet.h"
#include <iostream>

void intSet::swap(intSet& otherSet) {
    int* tmpArr = elements;
    elements = otherSet.elements;
    otherSet.elements = tmpArr;
    
    int tmpSize = elementCount;
    elementCount = otherSet.elementCount;
    otherSet.elementCount = tmpSize;
    
    int tmpCap = currentCapacity;
    currentCapacity = otherSet.currentCapacity;
    otherSet.currentCapacity = tmpCap;
}

int intSet::indexOf(int val) const {
    for (int i = 0; i < elementCount; i++) {
        if (elements[i] == val) {
            return i;
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
    for (int i = 0; i < elementCount; i++) {
        elements[i] = otherSet.elements[i];
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
    intSet tmp(otherSet);
    swap(tmp);
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
        int* newArr = new int[currentCapacity];
        for (int i = 0; i < elementCount; i++) {
            newArr[i] = elements[i];
        }
        delete[] elements;
        elements = newArr;
    }
    
    elements[elementCount++] = val;
}

void intSet::remove(int val) {
    int pos = indexOf(val);
    if (pos != -1) {
        elements[pos] = elements[elementCount - 1];
        elementCount--;
    }
}

intSet intSet::operator|(const intSet& otherSet) const {
    intSet result(*this);
    for (int i = 0; i < otherSet.elementCount; i++) {
        result.add(otherSet.elements[i]);
    }
    return result;
}

intSet intSet::operator&(const intSet& otherSet) const {
    intSet result;
    for (int i = 0; i < elementCount; i++) {
        if (otherSet.contains(elements[i])) {
            result.add(elements[i]);
        }
    }
    return result;
}

bool intSet::operator==(const intSet& otherSet) const {
    if (elementCount != otherSet.elementCount) {
        return false;
    }
    return isSubset(otherSet);
}

bool intSet::isSubset(const intSet& s) const {
    for (int i = 0; i < s.elementCount; i++) {
        if (!this->contains(s.elements[i])) {
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
    
    int* arr = new int[otherSet.elementCount];
    for (int i = 0; i < otherSet.elementCount; i++) {
        arr[i] = otherSet.elements[i];
    }
    
    for (int i = 0; i < otherSet.elementCount - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < otherSet.elementCount; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            int t = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = t;
        }
    }
    
    out << "(" << arr[0];
    for (int i = 1; i < otherSet.elementCount; i++) {
        out << ", " << arr[i];
    }
    out << ")";
    
    delete[] arr;
    return out;
}
