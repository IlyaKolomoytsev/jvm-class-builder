#include "constant-integer.h"

#include <ostream>
#include <arpa/inet.h>
#include "utils.h"

using namespace Jvm;

int32_t ConstantInteger::getValue()
{
    return value_;
}

void ConstantInteger::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    Utils::writeBigEndian(os, value_);
}

ConstantInteger::ConstantInteger(int32_t value, Class* classOwner) : Constant(CONSTANT_Integer, classOwner),
                                                                     value_(value)
{
}
