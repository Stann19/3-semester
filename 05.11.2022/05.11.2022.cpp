#include <iostream>

class Container {
private:
    Container* a[10]{};
    int n;
    double c_amount;
public:
    double amount;
    Container(): c_amount(0), n(0){
        for (int i = 0; i < 10; i++) *(a + i) = nullptr;
        a[0] = this;
        n++;
    }
    void addWater(double amount) {
        c_amount = amount;
    }
    double getAmount() {
        double number = 0.0;
        for (int i = 0; i < n; i++){
            if (*(a + i) == nullptr) break;
            number += (**(a + i)).c_amount;
            c_amount = number;
        }
        return c_amount;
    }
    void connectTo(Container other) {
        for (int i = 0; i < 10; i++) {
            if (*(a+i) == nullptr) {
                for (int j = 0; j < other.n; j++) {
                    *(a + i + j) = other.a[j];
                    n++;
                }
                break;
            }
        }
    }
};

int main()
{
    Container b;
    b.addWater(5.0);
    Container c;
    Container d;
    c.connectTo(d);
    std::cout << c.getAmount() << " ";
    b.connectTo(c);
    c.addWater(4.0);
    std::cout << c.getAmount() << " ";
    std::cout << b.getAmount();
}

