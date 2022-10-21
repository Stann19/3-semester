#include <iostream>
using namespace std;

struct point {
    double x;
    double y;
};

template <typename T>
struct Comparator {
    virtual int operator()(T&, T&) const = 0;
};

struct double_Comparator final: Comparator<double> {
    int operator()(double& a, double& b) const {
        if (a < b) {
            return -1;
        }
        if (a == b) {
            return 0;
        }
        return 1;
    }
};

struct point_Comparator final: Comparator<point> {
    int operator()(point& a, point& b) const {
        double square_a = a.x * a.y;
        double square_b = b.x * b.y;
        if (square_a < square_b) {
            return -1;
        }
        if (square_a == square_b) {
            return 0;
        }
        return 1;
    }
};

template <typename T, typename P>
class PriorityQueue {
private:
    T* data;
    P* prior;
    int size;
    bool emptyness;
    Comparator<T>& comparator_data;
    Comparator<P>& comparator_prior;

public:
    PriorityQueue(Comparator<T>& comparator_data, Comparator<P>& comparator_prior) : comparator_data(comparator_data), comparator_prior(comparator_prior), emptyness(true), size(0) {
        P* b = new P[size];
        T* a = new T[size];
        data = a;
        prior = b;
    }

    void print() {
        using namespace std;
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << "(" << data[i] << ";" << prior[i] << ")";

        }
        cout << "]" << endl;
    }

    template<typename F>
    void swap(F* t, int i, int j) {
        F temp;
        temp = t[j];
        t[j] = t[i];
        t[i] = temp;
        return;
    }

    void swap_with_ancestor(int i) {
        if (i == 0) {
            return;
        }

        if ((comparator_prior(prior[i], prior[(i - 1) / 2]) == 1) || (comparator_prior(prior[i], prior[(i - 1) / 2]) == 0 && comparator_data(data[i], data[(i - 1) / 2]) == 1)) {
            swap<T>(data, i, (i - 1) / 2);
            swap<P>(prior, i, (i - 1) / 2);
            swap_with_ancestor((i - 1) / 2);
        }
        return;
    }

    void push(T to_push, P priority) {
        size++;
        T* a = new T[size];
        for (int i = 0; i < size - 1; i++) {
            a[i] = data[i];
        }
        a[size - 1] = to_push;
        data = a;

        P* b = new P[size];
        for (int i = 0; i < size - 1; i++) {
            b[i] = prior[i];
        }
        b[size - 1] = priority;
        prior = b;

        swap_with_ancestor(size - 1);
        return;
    }

    void peek() {
        cout << "(" << data[0] << ";" << prior[0] << ")" << endl;
    }

    void swap_with_descendant(int i) {

        if (2 * i + 1 >= size) {
            return;
        }
        if ((comparator_prior(prior[i], prior[2 * i + 1]) == -1) || (comparator_prior(prior[i], prior[2 * i + 1]) == 0 && comparator_data(data[i], data[2 * i + 1]) == -1)) {
            swap<T>(data, i, 2 * i + 1);
            swap<P>(prior, i, 2 * i + 1);
            swap_with_descendant(2 * i + 1);
        }
        if (2 * i + 2 < size) {
            if ((comparator_prior(prior[i], prior[2 * i + 2]) == -1) || (comparator_prior(prior[i], prior[2 * i + 2]) == 0 && comparator_data(data[i], data[2 * i + 2]) == -1)) {
                swap<T>(data, i, 2 * i + 2);
                swap<P>(prior, i, 2 * i + 2);
                swap_with_descendant(2 * i + 2);
            }
        }
        return;
    }

    void poll() {
        if (size == 0) {
            cout << "heap is empty" << endl;
            return;
        }
        size--;
        T* a = new T[size];
        for (int i = 1; i < size; i++) {
            a[i] = data[i];
        }
        a[0] = data[size];
        data = a;

        P* b = new P[size];
        for (int i = 1; i < size; i++) {
            b[i] = prior[i];
        }
        b[0] = prior[size];
        prior = b;

        swap_with_descendant(0);
        return;
    }

    bool is_empty() {
        return size == 0;
    }

    void free() {
        delete[] data;
        delete[] prior;
        return;
    }
};

int main()
{
        double_Comparator double_comparator_data;
        double_Comparator double_comparator_prior;
        PriorityQueue<double, double> p(double_comparator_data, double_comparator_prior);
        p.push(2, 1);
        p.push(3, 2);
        p.push(4, 1);
        p.push(8, 1);
        p.print();
        p.peek();
        p.print();
        p.poll();
        p.print();
        p.free();
    return 0;
}