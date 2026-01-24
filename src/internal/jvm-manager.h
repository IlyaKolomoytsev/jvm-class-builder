#ifndef LUA_COMPILER_JVM_MANAGER_H
#define LUA_COMPILER_JVM_MANAGER_H
#include <jni.h>
#include <stdexcept>
#include <string>

#include "java-internal-paths.h"


class JvmManager
{
public:
    static JNIEnv* getJniEnv();

private:
    static JNIEnv* initJniEnv();
};


#endif //LUA_COMPILER_JVM_MANAGER_H
