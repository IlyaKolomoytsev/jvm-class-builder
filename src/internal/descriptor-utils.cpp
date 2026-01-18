#include "jvm/internal/descriptor-utils.h"

bool jvm::internal::isWrappedReference(std::string_view s) {
    return s.size() >= 2 && s.front() == 'L' && s.back() == ';';
}

std::string jvm::internal::unwrapReference(std::string_view s) {
    // assumes isWrappedReference(s) == true
    return std::string(s.substr(1, s.size() - 2));
}

bool jvm::internal::tryParsePrimitive(std::string_view s, Descriptor::Type &out) {
    if (s.size() != 1) return false;

    switch (s[0]) {
        case 'Z': out = Descriptor::Type::Boolean;
            return true;
        case 'B': out = Descriptor::Type::Byte;
            return true;
        case 'C': out = Descriptor::Type::Char;
            return true;
        case 'S': out = Descriptor::Type::Short;
            return true;
        case 'I': out = Descriptor::Type::Int;
            return true;
        case 'J': out = Descriptor::Type::Long;
            return true;
        case 'F': out = Descriptor::Type::Float;
            return true;
        case 'D': out = Descriptor::Type::Double;
            return true;
        default: return false;
    }
}
