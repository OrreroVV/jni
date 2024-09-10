#include <jni.h>
#include <iostream>
#include "Demo.h"
#include "code/thread.h"
#include <unistd.h> 
#include <pthread.h>
#include <iostream>
#include <vector>
#include <condition_variable>

int capacity = 10000;
hzh::Semaphore s1(capacity); // 生产者剩余总量
hzh::Semaphore s2(0);  // 消费者已消费的数量
hzh::Semaphore mutex(1); // 互斥量
std::vector<int>v;

std::atomic<bool> stop_flag;
std::condition_variable cv;
// hzh::Mutex::Lock Lock;
std::mutex stop_mutex;
int active_producer = 100;
int active_consumer = 100;
int total_consumer = 0;

void* producer(void* arg) {
    static thread_local int cnt = 0;
    while (true) {
        if (stop_flag.load()) {
            break;
        }
        s1.wait();
        mutex.wait();
        v.push_back(++cnt);
        std::cout << "producer: " << v.back() << std::endl;
        
        s2.notify();
        mutex.notify();
    }

    {
        std::lock_guard<std::mutex> lock(stop_mutex);
        --active_producer;
        cv.notify_one();
    }
    return 0;
}

void* consumer(void* arg) {
    while (true) {
        if (stop_flag.load()) {
            break;
        }
        s2.wait();
        mutex.wait();
        auto t = v.back();
        v.pop_back();
        ++total_consumer;
        std::cout << "consumer: " << t << std::endl;

        s1.notify();
        mutex.notify();
    }

    {
        std::lock_guard<std::mutex> lock(stop_mutex);
        --active_consumer;
        cv.notify_one();
    }
    return 0;
}

JNIEXPORT jstring JNICALL Java_Demo_sayHello(JNIEnv* env, jobject, jint a){
    
    pthread_t produces[100];
    for (int i = 0; i < 100; i++) {
        pthread_create(reinterpret_cast<pthread_t*>(reinterpret_cast<char*>(produces) + i * sizeof(pthread_t)), nullptr, &producer, nullptr);
        pthread_detach(produces[i]);
    }

    pthread_t consumers[100];
    for (int i = 0; i < 100; i++) {
        pthread_create(reinterpret_cast<pthread_t*>(reinterpret_cast<char*>(consumers) + i * sizeof(pthread_t)), nullptr, &consumer, nullptr);
        pthread_detach(consumers[i]);
    }

    sleep(a);
    stop_flag.store(true);
    {
        std::unique_lock<std::mutex> lock(stop_mutex);
        cv.wait(lock, [](){ return !active_consumer && !active_producer;});
    }
    // 将 C++ 字符串转换为 JNI jstring
    return env->NewStringUTF(std::to_string(total_consumer).c_str());
}