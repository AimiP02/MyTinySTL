#include <iostream>
#include "stl_vector.h"

int main() {
    bronya_stl::vector<int> Test(5);
    Test.push_back(4);
    Test.push_back(5);
    printf("Test[0]=%d\nTest[1]=%d\n", Test[0], Test[1]);
    return 0;
}