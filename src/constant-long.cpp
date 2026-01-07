#include "constant-long.h"

#include <cstring>
#include <arpa/inet.h>
#include "utils.h"

using namespace Jvm;

int64_t ConstantLong::getValue() const
{
    return value_;
}

uint16_t ConstantLong::getOccupiedSlots() const
{
    return 2;
}

void ConstantLong::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    Utils::writeBigEndian(os, value_);
}

ConstantLong::ConstantLong(int64_t value, Class* classOwner)
    : Constant(CONSTANT_Long, classOwner),
      value_(value)
{
}
