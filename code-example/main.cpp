#include <iostream>

using namespace std;

int main()
{
    // Use of not-allocated memory.
    int *not_allocatd;
    cout << *not_allocatd << endl;

    // Dereference of null pointer.
    int *a = nullptr;
    cout << *a << endl;

    return EXIT_SUCCESS;
}
