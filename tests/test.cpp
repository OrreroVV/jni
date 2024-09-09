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

    std::future<Output> t1 = std::async(std::launch::async, &func1, 3, 5);
    
    return 0;
}