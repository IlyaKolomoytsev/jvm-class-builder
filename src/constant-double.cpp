#include "constant-double.h"

#include <cstring>
#include <arpa/inet.h>

#include "utils.h"

using namespace Jvm;

double ConstantDouble::getValue() const
{
    return value_;
}

uint16_t ConstantDouble::getOccupiedSlots() const
{
    return 2;
}

void ConstantDouble::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    Utils::writeBigEndian(os, value_);
}

ConstantDouble::ConstantDouble(double value, Class* classOwner)
    : Constant(CONSTANT_Double, classOwner),
      value_(value)
{
}
