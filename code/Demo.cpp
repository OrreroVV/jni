#include <jni.h>
#include <iostream>
#include "Demo.h"

JNIEXPORT jstring JNICALL Java_Demo_sayHello(JNIEnv* env, jobject, jint a){
        // 创建一个 C++ 字符串
    std::string hello = "Hello from C++!" + std::to_string(a);

    // 将 C++ 字符串转换为 JNI jstring
    return env->NewStringUTF(hello.c_str());
}