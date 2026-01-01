#include "constant-name-and-type.h"

#include <assert.h>
#include <ostream>
#include <utility>

namespace Jvm
{
    ConstantNameAndType* ConstantNameAndType::getOrCreate(std::string name, std::string descriptor, Class* classOwner)
    {
        ConstantUtf8Info* nameConstant = ConstantUtf8Info::getOrCreate(std::move(name), classOwner);
        ConstantUtf8Info* descriptorConstant = ConstantUtf8Info::getOrCreate(std::move(descriptor), classOwner);
        return getOrCreate(nameConstant, descriptorConstant);
    }

    ConstantNameAndType* ConstantNameAndType::getOrCreate(std::string name, ConstantUtf8Info* descriptorConstant)
    {
        Class* classOwner = descriptorConstant->getClassOwner();
        ConstantUtf8Info* nameConstant = ConstantUtf8Info::getOrCreate(std::move(name), classOwner);
        return getOrCreate(nameConstant, descriptorConstant);
    }

    ConstantNameAndType* ConstantNameAndType::getOrCreate(ConstantUtf8Info* nameConstant, std::string descriptor)
    {
        Class* classOwner = nameConstant->getClassOwner();
        ConstantUtf8Info* descriptorConstant = ConstantUtf8Info::getOrCreate(std::move(descriptor), classOwner);
        return getOrCreate(nameConstant, descriptorConstant);
    }

    ConstantNameAndType* ConstantNameAndType::getOrCreate(ConstantUtf8Info* nameConstant,
                                                          ConstantUtf8Info* descriptorConstant)
    {
        // check if constants have a common class owner
        bool equalClassOwner = nameConstant->getClassOwner() == descriptorConstant->getClassOwner();
        assert(equalClassOwner);

        // search constant
        Class* classOwner = nameConstant->getClassOwner();
        for (auto constant : classOwner->constants())
        {
            if (constant->getTag() == CONSTANT_NameAndType)
            {
                // Use static method because only one tag can be associated with only one class type.
                ConstantNameAndType* constantNameAndType = static_cast<ConstantNameAndType*>(constant);
                if (constantNameAndType->getName() == nameConstant && constantNameAndType->getDescriptor() ==
                    descriptorConstant)
                {
                    return constantNameAndType;
                }
            }
        }
        // create new
        return new ConstantNameAndType(nameConstant, descriptorConstant);
    }

    ConstantUtf8Info* ConstantNameAndType::getName() const
    {
        return name_;
    }

    ConstantUtf8Info* ConstantNameAndType::getDescriptor() const
    {
        return descriptor_;
    }

    void ConstantNameAndType::toBinary(std::ostream& os) const
    {
        Constant::toBinary(os);
        uint16_t nameIndex = name_->getIndex();
        os.write(reinterpret_cast<const char*>(&nameIndex), sizeof(nameIndex));
        uint16_t descriptorIndex = descriptor_->getIndex();
        os.write(reinterpret_cast<const char*>(&descriptorIndex), sizeof(descriptorIndex));
    }

    ConstantNameAndType::ConstantNameAndType(ConstantUtf8Info* name, ConstantUtf8Info* descriptor) :
        Constant(CONSTANT_NameAndType, name->getClassOwner()), name_(name), descriptor_(descriptor)
    {
        Class* nameClassOwner = name->getClassOwner();
        Class* descriptorClassOwner = descriptor->getClassOwner();
        assert(nameClassOwner == descriptorClassOwner);
    }
} // Jvm
