#include "constant-methodref.h"

#include <cassert>
#include <ostream>

using namespace Jvm;

ConstantMethodref* ConstantMethodref::getOrCreate(std::string className, std::string methodName,
                                                  std::string methodDescriptor, Class* classOwner)
{
    ConstantClass* classConstant = ConstantClass::getOrCreate(std::move(className), classOwner);
    ConstantNameAndType* nameAndTypeConstant = ConstantNameAndType::getOrCreate(
        std::move(methodName), std::move(methodDescriptor), classOwner);
    return getOrCreate(classConstant, nameAndTypeConstant);
}

ConstantMethodref* ConstantMethodref::getOrCreate(ConstantClass* classConstant,
                                                  ConstantNameAndType* nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);

    // search constant
    Class* classOwner = classConstant->getClassOwner();
    for (auto constant : classOwner->constants())
    {
        if (constant->getTag() == CONSTANT_Methodref)
        {
            // Use static method because only one tag can be associated with only one class type.
            ConstantMethodref* constantMethodref = static_cast<ConstantMethodref*>(constant);
            if (constantMethodref->getClass() == classConstant && constantMethodref->getNameAndType() ==
                nameAndTypeConstant)
            {
                return constantMethodref;
            }
        }
    }
    // create new
    return new ConstantMethodref(classConstant, nameAndTypeConstant);
}

ConstantClass* ConstantMethodref::getClass() const
{
    return class_;
}

ConstantNameAndType* ConstantMethodref::getNameAndType() const
{
    return nameAndType_;
}

void ConstantMethodref::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t classIndex = class_->getIndex();
    os.write(reinterpret_cast<const char*>(&classIndex), sizeof(classIndex));
    uint16_t nameAndTypeIndex = nameAndType_->getIndex();
    os.write(reinterpret_cast<const char*>(&nameAndTypeIndex), sizeof(nameAndTypeIndex));
}

ConstantMethodref::ConstantMethodref(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant) :
    Constant(CONSTANT_Methodref, classConstant->getClassOwner()), class_(classConstant),
    nameAndType_(nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);
}
