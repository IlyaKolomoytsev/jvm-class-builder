#include "jvm/descriptor-field.h"

#include <cassert>
#include <stdexcept>
#include <utility>

#include "jvm/internal/descriptor-utils.h"
using namespace jvm::internal;

using namespace jvm;

DescriptorField::DescriptorField(Type primitiveFieldType, uint8_t arrayDepth)
    : primitiveFieldType_(primitiveFieldType),
      arrayDepth_(arrayDepth),
      classReference_() {
    assert(primitiveFieldType_ != Type::Reference);
}

DescriptorField::DescriptorField(std::string classReference, uint8_t arrayDepth)
    : primitiveFieldType_(Type::Reference),
      arrayDepth_(arrayDepth),
      classReference_(std::move(classReference)) {
    if (classReference_.empty())
        throw std::invalid_argument("DescriptorField: classReference cannot be empty");

    // Accept single-letter primitives like "J", "D", "Z" (common in codegen code).
    Type prim{};
    if (tryParsePrimitive(classReference_, prim)) {
        primitiveFieldType_ = prim;
        classReference_.clear();
        return;
    }

    // Accept wrapped reference "Ljava/lang/String;" to avoid "LL...;;"
    if (isWrappedReference(classReference_)) {
        classReference_ = unwrapReference(classReference_);
    }
}

DescriptorField DescriptorField::Primitive(Type t, uint8_t arrayDepth) {
    return DescriptorField(t, arrayDepth);
}

DescriptorField DescriptorField::Ref(std::string internalName, uint8_t arrayDepth) {
    return DescriptorField(std::move(internalName), arrayDepth);
}

std::string DescriptorField::toString() const {
    std::string result;
    result.reserve(arrayDepth_ + 1 + classReference_.size() + 2);

    // arrays: [[[
    for (uint8_t i = 0; i < arrayDepth_; i++)
        result.push_back('[');

    if (primitiveFieldType_ == Type::Reference) {
        result.push_back('L');
        result += classReference_;
        result.push_back(';');
        return result;
    }

    result.push_back(static_cast<char>(primitiveFieldType_));
    return result;
}
