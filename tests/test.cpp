#include <bits/stdc++.h>

using namespace std;

struct Output
{
    int a, b;
};

Output func1(int x, int y) {
    std::cout << "start: " << x << " " << y << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return { x, y };
}
    
int main() {

    char* p = new char[100];
    p[0] = '1';
    std::future<Output> t1 = std::async(std::launch::async, &func1, 3, 5);
    t1.get();
    delete []p;
    return 0;
}