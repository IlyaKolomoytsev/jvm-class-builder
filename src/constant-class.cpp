#include "constant-class.h"

#include <ostream>

using namespace Jvm;

ConstantClass* ConstantClass::getOrCreate(std::string name, Class* classOwner)
{
    ConstantUtf8Info* nameConstant = ConstantUtf8Info::getOrCreate(name, classOwner);
    return getOrCreate(nameConstant);
}

ConstantClass* ConstantClass::getOrCreate(ConstantUtf8Info* name)
{
    // search constant
    Class* classOwner = name->getClassOwner();
    for (auto constant : classOwner->constants())
    {
        if (constant->getTag() == CONSTANT_Class)
        {
            // Use static method because only one tag can be associated with only one class type.
            ConstantClass* constantClass = static_cast<ConstantClass*>(constant);
            if (constantClass->getName() == name)
            {
                return constantClass;
            }
        }
    }
    // create new
    return new ConstantClass(name);
}

ConstantUtf8Info* ConstantClass::getName() const
{
    return name_;
}

void ConstantClass::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t nameIndex = name_->getIndex();
    os.write(reinterpret_cast<const char*>(&nameIndex), sizeof(nameIndex));
}

ConstantClass::ConstantClass(ConstantUtf8Info* name) : Constant(CONSTANT_Class, name->getClassOwner()), name_(name)
{
}
