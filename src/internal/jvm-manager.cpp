#include "jvm-manager.h"

JNIEnv* JvmManager::getJniEnv()
{
    static JNIEnv* jniEnv = initJniEnv();
    return jniEnv;
}

JNIEnv* JvmManager::initJniEnv()
{
    JavaVM* jvm = nullptr;
    JNIEnv* env = nullptr;

    std::string classpath = std::string("-Djava.class.path=") + JAVA_INTERNAL_JAR;
    JavaVMOption options[1];
    options[0].optionString = classpath.data();
    JavaVMInitArgs vm_args{};
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    // run jvm
    jint correctJvmCreation = JNI_CreateJavaVM(&jvm, reinterpret_cast<void**>(&env), &vm_args);
    if (correctJvmCreation != JNI_OK || !env)
    {
        throw std::runtime_error("Failed to create JVM");
    }

    return env;
}
