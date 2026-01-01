#include "constant-string.h"

#include <ostream>
#include <utility>

using namespace Jvm;

ConstantString* ConstantString::getOrCreate(std::string string, Class* classOwner)
{
    ConstantUtf8Info* stringConstant = ConstantUtf8Info::getOrCreate(std::move(string), classOwner);
    return getOrCreate(stringConstant);
}

ConstantString* ConstantString::getOrCreate(ConstantUtf8Info* utf8StringConstant)
{
    // search constant
    Class* classOwner = utf8StringConstant->getClassOwner();
    for (auto constant : classOwner->constants())
    {
        if (constant->getTag() == CONSTANT_String)
        {
            // Use static method because only one tag can be associated with only one class type.
            ConstantString* constantString = static_cast<ConstantString*>(constant);
            if (constantString->getString() == utf8StringConstant)
            {
                return constantString;
            }
        }
    }
    // create new
    return new ConstantString(utf8StringConstant);
}

ConstantUtf8Info* ConstantString::getString()
{
    return string_;
}

void ConstantString::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t stringIndex = string_->getIndex();
    os.write(reinterpret_cast<const char*>(&stringIndex), sizeof(stringIndex));
}

ConstantString::ConstantString(ConstantUtf8Info* utf8StringConstant) :
    Constant(CONSTANT_String, utf8StringConstant->getClassOwner()), string_(utf8StringConstant)
{
}
