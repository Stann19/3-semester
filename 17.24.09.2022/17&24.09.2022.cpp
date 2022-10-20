#include <iostream>
#include <set>
#include <random>

class State {
public:
    virtual bool contains(int s) const {
        return 0;
    }
};

class DiscreteState: public State {
private:
    int const state;

public:
    DiscreteState(int state) : state(state) { }

    bool contains(int s) const override{
        return s == state;
    }
};

class SegmentState: public State {
private:
    int const beg, end;

public:
    SegmentState() : beg(0), end(-1) { }
    SegmentState(int beg, int end) : beg(beg), end(end) { }

    bool contains(int s) const override{
        return s >= beg && s <= end;
    }
};

class SetState: public State {
private:
    std::set<int> const states;

public:
    SetState() : states() { }
    SetState(std::set<int> const& src) : states(src) { }

    bool contains(int s) const override{
        return states.count(s) > 0;
    }
};

class UnionStates: public State {
private:
    State const& a;
    State const& b;
public:
    UnionStates(State const& a, State const& b): a(a), b(b) { }

    bool contains(int s) const override {
        return a.contains(s) || b.contains(s);
    }
};

class IntersectionStates : public State {
private:
    State const& a;
    State const& b;
public:
    IntersectionStates(State const& a, State const& b): a(a), b(b) {}

    bool contains(int s) const override {
        return a.contains(s) && b.contains(s);
    }
};

class InversionStates : public State {
private:
    State const& a;
public:
    InversionStates(State const& a): a(a) {}

    bool contains(int s) const override {
        return !a.contains(s);
    }
};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count) : seed(seed), test_min(test_min), test_max(test_max), test_count(test_count) { }

    float operator()(State const& s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min, test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good) / static_cast<float>(test_count);
    }
};

int main(int argc, const char* argv[]) {
    DiscreteState d(1);
    SegmentState s(0, 20);
    SetState ss({ 1, 3, 5, 7, 23, 48, 57, 60, 90, 99 });
    UnionStates us(s, d);
    IntersectionStates ints(s, ss);
    InversionStates invs(ss);
    for (int i = 0; i < 100; i++) {
        ProbabilityTest pt(time(0), 0, 100, 100000);
        std::cout << pt(d) << " ";
        std::cout << pt(s) << " ";
        std::cout << pt(ss) << " ";
        std::cout << pt(us) << " ";
        std::cout << pt(ints) << " ";
        std::cout << pt(invs) << std::endl;
    }
    return 0;
}
