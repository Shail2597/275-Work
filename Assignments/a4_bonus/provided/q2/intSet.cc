#include "intSet.h"
#include <iostream>

void intSet::swap(intSet& other) {
    int* temp_elements = data;
    data = other.data;
    other.data = temp_elements;

    int temp_count = size;
    size = other.size;
    other.size = temp_count;

    int temp_cap = capacity;
    capacity = other.capacity;
    other.capacity = temp_cap;
}

int intSet::indexOf(int e) const {
    for (int k = 0; k < size; k++) {
        if (data[k] == e) {
            return k;
        }
    }
    return -1;
}

intSet::intSet() {
    capacity = 4;
    size = 0;
    data = new int[capacity];
}

intSet::intSet(const intSet& is) : data{new int[is.capacity]}, size{is.size}, capacity{is.capacity} {
    for (int idx = 0; idx < size; idx++) {
        data[idx] = is.data[idx];
    }
}

intSet::intSet(intSet&& is) : data{is.data}, size{is.size}, capacity{is.capacity} {
    is.data = nullptr;
    is.size = 0;
    is.capacity = 0;
}

intSet& intSet::operator=(const intSet& is) {
    intSet copySet(is);
    swap(copySet);
    return *this;
}

intSet& intSet::operator=(intSet&& is) {
    swap(is);
    return *this;
}

intSet::~intSet() {
    delete[] data;
}

bool intSet::contains(int e) const {
    return indexOf(e) != -1;
}

void intSet::add(int e) {
    if (contains(e)) {
        return;
    }

    if (size == capacity) {
        capacity *= 2;
        int* newArray = new int[capacity];
        for (int p = 0; p < size; p++) {
            newArray[p] = data[p];
        }
        delete[] data;
        data = newArray;
    }

    data[size++] = e;
}

void intSet::remove(int e) {
    int found_idx = indexOf(e);
    if (found_idx != -1) {
        data[found_idx] = data[size - 1];
        size--;
    }
}

intSet intSet::operator|(const intSet& other) const {
    intSet unionResult(*this);
    for (int m = 0; m < other.size; m++) {
        unionResult.add(other.data[m]);
    }
    return unionResult;
}

intSet intSet::operator&(const intSet& other) const {
    intSet intersectionResult;
    for (int m = 0; m < size; m++) {
        if (other.contains(data[m])) {
            intersectionResult.add(data[m]);
        }
    }
    return intersectionResult;
}

bool intSet::operator==(const intSet& other) const {
    if (size != other.size) {
        return false;
    }
    return isSubset(other);
}

bool intSet::isSubset(const intSet& sub) const {
    for (int m = 0; m < sub.size; m++) {
        if (!this->contains(sub.data[m])) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const intSet& is) {
    if (is.size == 0) {
        out << "()";
        return out;
    }

    int* sorted_vals = new int[is.size];
    for (int p = 0; p < is.size; p++) {
        sorted_vals[p] = is.data[p];
    }

    for (int i = 0; i < is.size - 1; i++) {
        int least_pos = i;
        for (int j = i + 1; j < is.size; j++) {
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
    for (int i = 1; i < is.size; i++) {
        out << ", " << sorted_vals[i];
    }
    out << ")";

    delete[] sorted_vals;
    return out;
}
