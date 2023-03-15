#include <atomic>
#include <chrono>

int main() {
    std::atomic<bool> done(false);
    auto start = std::chrono::steady_clock::now();

   
    while (!done.load()) {
        std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
        if (elapsed.count() >= 110.0) {
            done.store(true);
        }
    }

    return 0;
}
//使用了一个std::atomic<bool>变量来表示延时是否已经完成。我们循环检查这个变量是否为true，并在110秒钟后将其设置为true，以停止循环