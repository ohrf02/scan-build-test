#include <iostream>

using namespace std;

bool bar(int a)
{
    return a > 0 ? true : false;
}

class A
{
public:
    virtual bool foo(int a) = 0;
};

class B : public A
{
public:
    virtual bool foo(int a) override
    {
        return bar(a);
    }
};

int main()
{
    // Unused var.
    bool b = bar(-5);

    // Out of range.
    static constexpr size_t size_of_buf = 100;
    int buf[size_of_buf] = {};
    cout << buf[size_of_buf + 1];

    // Use of not-allocated memory.
    int *not_allocated;
    cout << *not_allocated << endl;

    // Dereference of null pointer.
    int *a = nullptr;
    cout << *a << endl;

    return EXIT_SUCCESS;
}
