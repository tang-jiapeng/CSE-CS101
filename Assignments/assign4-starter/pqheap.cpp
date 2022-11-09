#include "pqheap.h"
#include "error.h"
#include "random.h"
#include "strlib.h"
#include "datapoint.h"
#include "testing/SimpleTest.h"
using namespace std;

const int INITIAL_CAPACITY = 10;
const int NONE = -1; // used as sentinel index

PQHeap::PQHeap() {
    _numAllocated=INITIAL_CAPACITY;
    _elements=new DataPoint[_numAllocated];
    _numFilled=0;
}

PQHeap::~PQHeap() {
    delete[] _elements;
}

void PQHeap::enqueue(DataPoint elem) {
    if(_numAllocated==_numFilled){
        DataPoint * temp=_elements;
        _numAllocated*=2;
        _elements=new DataPoint[_numAllocated];
        for(int i=0;i<_numFilled;i++){
            _elements[i]=temp[i];
        }
        delete[] temp;
    }
    int index=_numFilled;
    _elements[index]=elem;
    _numFilled++;
    swim(index);
}

DataPoint PQHeap::peek() const {
    if(isEmpty()){
        error("PQHeap is empty!");
    }
    return _elements[0];
}

DataPoint PQHeap::dequeue() {
    if (isEmpty()) {
        error("PQueue is empty!");
    }
    DataPoint front=_elements[0];
    swap(0,_numFilled-1);
    _numFilled--;
    sink(0);
    return front;
}

bool PQHeap::isEmpty() const {
    return size()==0;
}

int PQHeap::size() const {
    return _numFilled;
}

void PQHeap::clear() {
    _numFilled=0;
}

void PQHeap::swap(int indexA,int indexB){
    DataPoint temp=_elements[indexA];
    _elements[indexA]=_elements[indexB];
    _elements[indexB]=temp;
}


void PQHeap::swim(int index){
    int parentIndex = getParentIndex(index);
    if (parentIndex != -1) {
        if (larger(parentIndex, index)) {
            swap(index, parentIndex);
            swim(parentIndex);
        }
    }
}

void PQHeap::sink(int index){
    int left = getLeftChildIndex(index);
    int right = getRightChildIndex(index);
    if (left != -1) {
        int indexOfSmallerChild=left;
        if (right != -1 && larger(left, right)) {
            indexOfSmallerChild = right;
        }
        if (larger(index, indexOfSmallerChild)) {
            swap(index, indexOfSmallerChild);
            sink(indexOfSmallerChild);
        }
    }
}

bool PQHeap::larger(int indexA,int indexB){
    return _elements[indexA].priority>_elements[indexB].priority;
}

void PQHeap::printDebugInfo(string msg) const {
    cout << msg << endl;
    for(int i=0;i<size();i++){
        cout<<"["<<i<<"]"<<_elements[i]<<endl;
    }
}

void PQHeap::validateInternalState() const {
    if (_numFilled > _numAllocated) error("Too many elements in not enough space!");
    for (int i = 0; i < size(); i++) {
        int left = getLeftChildIndex(i);
        int right = getRightChildIndex(i);
        if (left != -1 && _elements[i].priority > _elements[left].priority) {
            error("PQHeap has an element larger than it left child");
        }
        if (right != -1 && _elements[i].priority > _elements[right].priority) {
            error("PQHeap has an element larger than it right child");
        }
    }
}

int PQHeap::getParentIndex(int child) const {
    if (child == 0) {
        return -1;
    }
    return (child-1)/2;
}

int PQHeap::getLeftChildIndex(int parent) const {
    int index=2*parent+1;
    if(index>=_numFilled){
        return -1;
    }
    return index;
}

int PQHeap::getRightChildIndex(int parent) const {
    int index=2*parent+2;
    if(index>=_numFilled){
        return -1;
    }
    return index;
}

/* * * * * * Test Cases Below This Point * * * * * */

STUDENT_TEST("PQHeap: operations size/isEmpty/clear") {
    PQHeap pq;

    EXPECT(pq.isEmpty());
    pq.clear();
    EXPECT_EQUAL(pq.isEmpty(), pq.size() == 0);
    pq.enqueue({ "", 7 });
    EXPECT_EQUAL(pq.size(), 1);
    pq.enqueue({ "", 5 });
    EXPECT_EQUAL(pq.size(), 2);
    pq.enqueue({ "", 5 });
    EXPECT_EQUAL(pq.size(), 3);
    pq.validateInternalState();
    pq.clear();
    pq.validateInternalState();
    EXPECT(pq.isEmpty());
    EXPECT_EQUAL(pq.size(), 0);
}

STUDENT_TEST("PQHeap: enqueue, dequene and peek, size, isEmpty") {
    PQHeap pq;
    EXPECT(pq.isEmpty());
    pq.enqueue({ "A", 7 });
    pq.enqueue({ "C", 2 });
    pq.enqueue({ "B", 5 });
    pq.enqueue({ "D", 3 });
    pq.enqueue({ "E", 1 });
    EXPECT(!pq.isEmpty());
    EXPECT_EQUAL(pq.size(), 5);
    EXPECT_EQUAL(pq.peek(), {"E", 1});
    EXPECT_EQUAL(pq.dequeue(), {"E", 1});
    EXPECT_EQUAL(pq.size(), 4);
    EXPECT_EQUAL(pq.peek(), {"C", 2});
    EXPECT_EQUAL(pq.dequeue(), {"C", 2});
    EXPECT_EQUAL(pq.size(), 3);
    EXPECT_EQUAL(pq.peek(), {"D", 3});
    EXPECT_EQUAL(pq.dequeue(), {"D", 3});
    EXPECT_EQUAL(pq.size(), 2);
    EXPECT(!pq.isEmpty());
    EXPECT_EQUAL(pq.peek(), {"B", 5});
    EXPECT_EQUAL(pq.dequeue(), {"B", 5});
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.peek(), {"A", 7});
    EXPECT_EQUAL(pq.dequeue(), {"A", 7});
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT(pq.isEmpty());
}

STUDENT_TEST("PQHeap: test enlarge array memory") {
    for (int size = 5; size <= 500; size *= 5) {
        PQHeap pq;

        for (int i = 1; i <= size; i++) {
            pq.enqueue({"", double(i) });
        }
        pq.validateInternalState();

        for (int i = 1; i <= size; i++) {
            DataPoint expected = {"", double(i) };
            EXPECT_EQUAL(pq.dequeue(), expected);
        }
    }

}

STUDENT_TEST("PQHeap, sequence of mixed operations") {
    PQHeap pq;
    int size = 30;
    double val = 0;

    for (int i = 0; i < size; i++) {
        pq.enqueue({"", --val });
    }
    val = 0;
    for (int i = 0; i < pq.size(); i++) {
        DataPoint front = pq.peek();
        EXPECT_EQUAL(pq.dequeue(), front);
        pq.enqueue( { "", ++val });
    }
    EXPECT_EQUAL(pq.size(), size);
    val = 0;
    while (!pq.isEmpty()) {
        DataPoint expected = { "", ++val };
        EXPECT_EQUAL(pq.dequeue(), expected);
    }
}

STUDENT_TEST("PQHeap stress test, cycle many random elements in and out") {
    PQHeap pq;
    int n = 0, maxEnqueues = 1000;
    double sumEnqueued = 0, sumDequeued = 0;

    setRandomSeed(42); // make test behavior deterministic

    DataPoint mostUrgent = { "", 0 };
    pq.enqueue(mostUrgent);
    while (true) {
        if (++n < maxEnqueues && randomChance(0.9)) {
            DataPoint elem = { "", randomInteger(-10, 10) + 0.5 };
            if (elem.priority < mostUrgent.priority) {
                mostUrgent = elem;
            }
            sumEnqueued += elem.priority;
            pq.enqueue(elem);
        } else {
            DataPoint elem = pq.dequeue();
            sumDequeued += elem.priority;
            EXPECT_EQUAL(elem, mostUrgent);
            if (pq.isEmpty()) break;
            mostUrgent = pq.peek();
        }
    }
    EXPECT_EQUAL(sumEnqueued, sumDequeued);
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("PQHeap example from writeup, validate each step") {
    PQHeap pq;
    Vector<DataPoint> input = {
        { "R", 4 }, { "A", 5 }, { "B", 3 }, { "K", 7 }, { "G", 2 },
        { "V", 9 }, { "T", 1 }, { "O", 8 }, { "S", 6 } };

    pq.validateInternalState();
    for (DataPoint dp : input) {
        pq.enqueue(dp);
        pq.validateInternalState();
    }
    while (!pq.isEmpty()) {
        pq.dequeue();
        pq.validateInternalState();
    }
}
