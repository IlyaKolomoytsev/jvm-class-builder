#include "constant-interface-methodref.h"

#include <cassert>
#include <ostream>

using namespace Jvm;

ConstantInterfaceMethodref* ConstantInterfaceMethodref::getOrCreate(std::string className, std::string methodName,
                                                                    std::string methodDescriptor, Class* classOwner)
{
    ConstantClass* classConstant = ConstantClass::getOrCreate(std::move(className), classOwner);
    ConstantNameAndType* nameAndTypeConstant = ConstantNameAndType::getOrCreate(
        std::move(methodName), std::move(methodDescriptor), classOwner);
    return getOrCreate(classConstant, nameAndTypeConstant);
}

ConstantInterfaceMethodref* ConstantInterfaceMethodref::getOrCreate(ConstantClass* classConstant,
                                                                    ConstantNameAndType* nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);

    // search constant
    Class* classOwner = classConstant->getClassOwner();
    for (auto constant : classOwner->constants())
    {
        if (constant->getTag() == CONSTANT_InterfaceMethodref)
        {
            // Use static method because only one tag can be associated with only one class type.
            ConstantInterfaceMethodref* constantMethodref = static_cast<ConstantInterfaceMethodref*>(constant);
            if (constantMethodref->getClass() == classConstant && constantMethodref->getNameAndType() ==
                nameAndTypeConstant)
            {
                return constantMethodref;
            }
        }
    }
    // create new
    return new ConstantInterfaceMethodref(classConstant, nameAndTypeConstant);
}

ConstantClass* ConstantInterfaceMethodref::getClass() const
{
    return class_;
}

ConstantNameAndType* ConstantInterfaceMethodref::getNameAndType() const
{
    return nameAndType_;
}

void ConstantInterfaceMethodref::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t classIndex = class_->getIndex();
    os.write(reinterpret_cast<const char*>(&classIndex), sizeof(classIndex));
    uint16_t nameAndTypeIndex = nameAndType_->getIndex();
    os.write(reinterpret_cast<const char*>(&nameAndTypeIndex), sizeof(nameAndTypeIndex));
}

ConstantInterfaceMethodref::ConstantInterfaceMethodref(ConstantClass* classConstant,
                                                       ConstantNameAndType* nameAndTypeConstant) :
    Constant(CONSTANT_InterfaceMethodref, classConstant->getClassOwner()), class_(classConstant),
    nameAndType_(nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);
}
