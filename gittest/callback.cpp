//bzj^_^
//callback.cpp
//IMPORTANT!!!!!
#include <iostream>
#include <cstdlib>
#include <ctime>

//callback
void generator(unsigned& v) { v = rand() % 100; }//得到一个0到99的值

void arrayWalk(unsigned *a, size_t len, void callback(unsigned&))
{
    for (size_t i = 0; i < len; ++i) callback(a[i]);
}//函数调用，用于填充数组

//predicate
bool gt50(unsigned v) { return v > 50; }

size_t countif(unsigned *a, size_t len, bool pred(unsigned))
{
    size_t count = 0;
    for (size_t i = 0; i < len; ++i) if (pred(a[i])) ++count;
    return count;
}

int main ()
{
    srand(static_cast<unsigned>(time(NULL)));

    const size_t len = 5;
    unsigned a[len];

    //fill array
    arrayWalk(a, len, generator);
    //print array, using lambda
    arrayWalk(a, len, [](unsigned& v) { std::cout << v << ' '; });
    std::cout << "\nCount of greater than 50: " << countif(a, len, gt50);
    std::cout << "\nCount of greater than 20: " << countif(a, len, [](unsigned v) {return v > 20;});

    return 0;
}
