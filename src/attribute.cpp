#include "jvm/attribute.h"

#include <ostream>

#include "jvm/internal/utils.h"

using namespace jvm;

void Attribute::toBinary(std::ostream& os) const
{
    // u2 attribute_name_index;
    uint16_t nameIndex = name_->getIndex();
    internal::Utils::writeBigEndian(os, static_cast<uint16_t>(nameIndex));

    // u4 attribute_length;
    uint32_t length = getAttributeLength();
    internal::Utils::writeBigEndian(os, static_cast<uint32_t>(length));
}

std::ostream& jvm::operator<<(std::ostream& os, const Attribute& attribute)
{
    attribute.toBinary(os);
    return os;
}
