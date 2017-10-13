//类似Java中的导包
#include <jni.h>
#include <string>

//extern "C"的主要作用就是为了能够正确实现C++代码调用其他C语言代码
//加上extern "C"后，会指示编译器这部分代码按C语言的进行编译，而不是C++的
extern "C"

//静态注册的方法
//JNIEnv:它指向一个函数表，该函数表指向一系列的JNI函数，我们通过调用这些JNI函数可以实现与Java层的交互
jstring Java_com_tsnt_jni_androidjnidemo_MainActivity_getStringFromJNIStatically(
        JNIEnv *env,
        jobject obj) {
    //声明一个string类型变量
    std::string hello = "Hello from native -- registered statically";
    return env->NewStringUTF(hello.c_str());
}

//动态注册的方法
jstring nativeGetStringFromJNIDynamically(JNIEnv *env, jobject obj) {
    std::string hello = "Hello from native -- registered dynamically";
    return env->NewStringUTF(hello.c_str());
}

//用来保存方法信息的数组
JNINativeMethod nativeMethod[] = {{"getStringFromJNIDynamically", "()Ljava/lang/String;", (void *) nativeGetStringFromJNIDynamically},};

//当我们使用System.loadLibarary()方法加载so库的时候,Java虚拟机就会找到这个函数并调用该函数
//因此可以在该函数中做一些初始化的动作
//其实这个函数就是相当于Activity中的onCreate()方法
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {

    JNIEnv *env;

    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {

        return -1;
    }

    //获取MainActivity对象
    jclass clz = env->FindClass("com/tsnt/jni/androidjnidemo/MainActivity");

    //动态注册方法
    env->RegisterNatives(clz, nativeMethod, sizeof(nativeMethod) / sizeof(nativeMethod[0]));

    //返回JNI版本
    return JNI_VERSION_1_4;
}