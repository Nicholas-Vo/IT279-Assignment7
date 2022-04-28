//
// Created by nvoss on 4/14/2022.
//

#include "BinaryHeap.h"
#include "dsexceptions.h"

template<typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(int capacity) {
    currentSize = capacity;
}

template<typename Comparable>
void BinaryHeap<Comparable>::makeEmpty() {
    array.clear();
    currentSize = 0;
}

template<typename Comparable>
bool BinaryHeap<Comparable>::isEmpty() const {
    return currentSize == 0;
}

template<typename Comparable>
const Comparable &BinaryHeap<Comparable>::findMax() const {
    if (isEmpty()) {
        throw UnderflowException{};
    }

    return array[1];
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMax() {
    if (isEmpty()) {
        throw UnderflowException{};
    }

    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMax(Comparable &maxItem) {
    if (isEmpty()) {
        throw UnderflowException{};
    }

    maxItem = std::move(array[1]);
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}

template<typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable &x) {
    if (currentSize == array.size() - 1) {
        array.resize(array.size() * 2);
    }

    int hole = ++currentSize;
    Comparable copy = x;

    array[0] = move(copy);

    for (; x < array[hole / 2]; hole /= 2) {
        array[hole] = std::move(array[hole / 2]);
    }

    array[hole] = std::move(array[0]);
}

template<typename Comparable>
void BinaryHeap<Comparable>::updateVal(int p, Comparable newValue) {

}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteVal(int p, Comparable &val) {

}

template<typename Comparable>
vector<Comparable> BinaryHeap<Comparable>::heapsort() {
    for (int i = (array.size() / 2) - 1; i >= 0; i--) {
        percolateDown(i);
    }

    for (int j = array.size() - 1; j > 0; j--) {
        swap(array[0], array[j]);
        percolateDown(0);
    }

    return vector<Comparable>(this);
}

template<typename Comparable>
void BinaryHeap<Comparable>::printHeap() {
    for (int i = 0; i < currentSize; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

template<typename Comparable>
void BinaryHeap<Comparable>::buildHeap() {
    // Floyd's method
    for (int i = currentSize / 2; i > 0; --i) {
        percolateDown(i);
    }
}

template<typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole) {
    int child;
    Comparable tmp;

    for (tmp = array[hole]; 2 * hole + 1 < currentSize; hole = child) {
        child = 2 * hole + 1;
        if (child != currentSize - 1 && array[child] < array[child + 1]) {
            child++;
        }
        if (tmp < array[child]) {
            array[hole] = array[child];
        } else
            break;
    }
    array[hole] = tmp;
}

