#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>


using namespace std;

template <typename T>
class MaxHeap {
  private:
    T *array{};
    int size{};
    int capacity{1000};

    int left(int node) {
        int p = 2 * node + 1;
        return p >= size ? -1 : p; // ternary operator
    }

    int right(int node) {
        int p = 2 * node + 2;
        return p >= size ? -1 : p;
    }

    int parent(int node) {
        int p = (node - 1) / 2;
        return p < 0 ? -1 : p;
    }

    void heapify_up(int child_pos) {
        int par_pos = parent(child_pos);
        if (child_pos == 0 || array[par_pos] >= array[child_pos])
            return;
        swap(array[par_pos], array[child_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int par_pos) {
        int left_child = left(par_pos);
        int right_child = right(par_pos);

        if (left_child == -1) // leaf node
            return;

        int children_max = left_child;
        if (right_child != -1 && array[right_child] > array[left_child])
            children_max = right_child;

        if (array[par_pos] < array[children_max]) {
            swap(array[par_pos], array[children_max]);
            heapify_down(children_max);
        }
    }

    void heapify() { // O(n) not O(nlogn)
        // start from the last non-leaf node
        for (int i = size / 2 - 1; i >= 0; --i)
            heapify_down(i);
    }

  public:
    // MaxHeap() = default;
    MaxHeap() {
        array = new T[capacity];
        size = 0;
    }
    MaxHeap(const vector<T> &v) {
        assert((int)v.size() <= capacity);
        array = new T[capacity];
        size = v.size();

        for (int i = 0; i < (int)v.size(); i++)
            array[i] = v[i];
        heapify();
    }
    ~MaxHeap() {
        delete[] array;
        array = nullptr;
    }
    T top() const {
        assert(!isempty());
        return array[0];
    }
    void push(T key) {
        assert(size + 1 <= capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }
    void pop() {
        assert(!isempty());
        array[0] = array[--size];
        heapify_down(0);
    }
    bool isempty() const {
        return size == 0;
    }
};

template <typename T>
class PriorityQueue {
    private:
    MaxHeap<T> pq;

    public:
    PriorityQueue() : pq() {}

    PriorityQueue(const vector<T> &v) : pq(v) {}

    void enqueue(T value) {
        pq.push(value);
    }

    void dequeue() {
        pq.pop();
    }

    T peek() const {
        return pq.top();
    }

    bool isempty() const {
        return pq.isempty();
    }

};

template <typename T>
void heapsort(vector<T> &v) {
    MaxHeap<T> heap(v); 

    for (int i = v.size() - 1; i >= 0; --i) {
        v[i] = heap.top();  
        heap.pop(); 
    }
}