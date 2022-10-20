#include <iostream>
using namespace std;

struct point{
    int x;
    int y;
};

int double_comparator(void* a, void* b) {
    double* a2 = (double*)a;
    double* b2 = (double*)b;
    if (*a2 < *b2)
    {
        return -1;
    }
    if (*a2 == *b2)
    {
        return 0;
    }
    return 1;
}

int point_comparator(void* a, void* b){
    point* a2 = (point*)a;
    point* b2 = (point*)b;
    int square_a = a2->x * a2->y;
    int square_b = b2->x * b2->y;
    if (square_a < square_b)
    {
        return -1;
    }
    if (square_a == square_b)
    {
        return 0;
    }
    return 1;
}

void swap(void* lha, void* rha, unsigned int element_byte_size)
{
    void* tmp = malloc(element_byte_size);
    memcpy(tmp, lha, element_byte_size);
    memcpy(lha, rha, element_byte_size);
    memcpy(rha, tmp, element_byte_size);
    free(tmp);
}

void sort(void* data, int element_byte_size, int array_size, int comparator(void*, void*)) {
    if (array_size <= 1)
        return;
    void* pivot = (char*)data + element_byte_size * (array_size - 1);
    int f = 1;
    for (int i = 0; i < array_size - 1; i++)
    {
        void* g = (char*)data + element_byte_size * i;
        if (f == 1 && comparator(pivot, g) == -1)
        {
            swap(g, pivot, element_byte_size);
            pivot = g;
            f = -1;
        }
        else if (f == -1 && comparator(g, pivot) == -1)
        {
            while (pivot != g)
            {
                swap((char*)g - element_byte_size, g, element_byte_size);
                g = (char*)g - element_byte_size;
            }
            pivot = (char*)pivot + element_byte_size;
        }
    }
    sort(data, element_byte_size, ((char*)pivot - (char*)data) / element_byte_size, comparator);
    sort((char*)pivot + element_byte_size, element_byte_size, array_size - 1 - ((char*)pivot - (char*)data) / element_byte_size, comparator);
}

int main()
{
    cout << "If you want to sort type point enter 0" <<" " << "If you want to sort type double enter 1" << "\n";
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
        sort(a, sizeof(point), n_point, point_comparator);
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
        sort(b, sizeof(double), n_double, double_comparator);
        for (int i = 0; i < n_double; i++) {
            cout << b[i] << endl;
        }
        delete[] b;
        return 0;
    }
}

