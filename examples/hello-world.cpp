#include <fstream>
#include <jvm/class.h>
#include <jvm/method.h>
#include <jvm/instruction.h>
#include <jvm/serializable.h>

#include "jvm/descriptor-method.h"

using namespace jvm;

int main()
{
    Class helloWorldClass("hello", "java/lang/Object");

    Method* mainMethod = helloWorldClass.getOrCreateMethod(
        "main",
        DescriptorMethod{
            std::nullopt,
            {{"java/lang/String", 1}}
        }
    );

    helloWorldClass.addFlag(Class::ACC_SUPER);
    helloWorldClass.addFlag(Class::ACC_PUBLIC);
    mainMethod->addFlag(Method::ACC_PUBLIC);
    mainMethod->addFlag(Method::ACC_STATIC);

    AttributeCode* code = mainMethod->getCodeAttribute();
    *code
        << code->ReturnVoid();


    {
        std::ofstream file("hello.class");
        helloWorldClass.writeTo(file);
        file.close();
    } // файл закрыт автоматически
};
