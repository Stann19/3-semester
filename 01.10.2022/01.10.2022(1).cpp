#include <iostream>
using namespace std;

struct point {
    int x;
    int y;
};

template <typename T>
struct Comparator {
    virtual int operator()(T*, T*) const = 0;
};

template<>
struct Comparator<double> {
    int operator()(double* a, double* b) const {
        if (*a < *b) {
            return -1;
        }
        if (*a == *b) {
            return 0;
        }
        return 1;
    }
};

template<>
struct Comparator<point> {
    int operator()(point* a, point* b) const {
        int square_a = a->x * a->y;
        int square_b = b->x * b->y;
        if (square_a < square_b) {
            return -1;
        }
        if (square_a == square_b) {
            return 0;
        }
        return 1;
    }
};

void swap(void* lha, void* rha, unsigned int element_byte_size)
{
    void* tmp = malloc(element_byte_size);
    if (tmp == 0) {
        cout << "error";
        free(tmp);
        return;
    }
    memcpy(tmp, lha, element_byte_size);
    memcpy(lha, rha, element_byte_size);
    memcpy(rha, tmp, element_byte_size);
    free(tmp);
}

template <typename T>
void sort(T* data, int array_size) {
    Comparator<T> comparator;
    if (array_size <= 1)
        return;
    int element_byte_size = sizeof(T);
    void* pivot = (char*)data + element_byte_size * (array_size - 1);
    int f = 1;
    for (int i = 0; i < array_size - 1; i++)
    {
        void* g = (char*)data + element_byte_size * i;
        if (f == 1 && comparator((T*)pivot, (T*)g) == -1)
        {
            swap(g, pivot, element_byte_size);
            pivot = g;
            f = -1;
        }
        else if (f == -1 && comparator((T*)g, (T*)pivot) == -1)
        {
            while (pivot != g)
            {
                swap((char*)g - element_byte_size, g, element_byte_size);
                g = (char*)g - element_byte_size;
            }
            pivot = (char*)pivot + element_byte_size;
        }
    }
    sort(data, ((char*)pivot - (void*)(char*)data) / element_byte_size);
    sort((T*)((char*)pivot + element_byte_size), array_size - 1 - ((char*)pivot - (void*)(char*)data) / element_byte_size);
}

int main()
{
    cout << "If you want to sort type point enter 0" << " " << "If you want to sort type double enter 1" << "\n";
    int n;
    cin >> n;
    if (n == 0) {
        int n_point;
        cin >> n_point;
        point* a = new point[n_point];
        for (int i = 0; i < n_point; i++) {
            cin >> a[i].x;
            cin >> a[i].y;
        }
        sort<point>(a, n_point);
        for (int i = 0; i < n_point; i++) {
            cout << a[i].x << " " << a[i].y << endl;
        }
        delete[] a;
        return 0;
    }

    if (n == 1) {
        int n_double;
        cin >> n_double;
        double* b = new double[n_double];
        for (int i = 0; i < n_double; i++) {
            cin >> b[i];
        }
        sort<double>(b, n_double);
        for (int i = 0; i < n_double; i++) {
            cout << b[i] << endl;
        }
        delete[] b;
        return 0;
    }
}