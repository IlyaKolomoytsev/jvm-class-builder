#ifndef JVM_DESCRIPTOR_UTILS_H
#define JVM_DESCRIPTOR_UTILS_H

#include <string>
#include <string_view>

#include "jvm/descriptor.h"

namespace jvm::internal {
    /**
     * @brief Check whether a string is a wrapped JVM reference descriptor.
     *
     * A wrapped reference descriptor has the form:
     *   "L" + internalName + ";"
     *
     * Examples:
     * - "Ljava/lang/String;"  -> true
     * - "java/lang/String"    -> false
     * - "I"                   -> false
     *
     * @param s Input string to test.
     * @return True if @p s is wrapped as "L...;".
     */
    bool isWrappedReference(std::string_view s);

    /**
     * @brief Remove the "L" and ";" wrapper from a wrapped JVM reference descriptor.
     *
     * Preconditions:
     * - The input must satisfy isWrappedReference(s) == true.
     *
     * Examples:
     * - unwrapReference("Ljava/lang/String;") -> "java/lang/String"
     *
     * @param s Wrapped reference descriptor (must be "L...;").
     * @return The internal JVM class name without wrapping.
     */
    std::string unwrapReference(std::string_view s);

    /**
     * @brief Parse a single-letter primitive JVM type descriptor.
     *
     * Supported letters:
     * - Z, B, C, S, I, J, F, D
     *
     * Examples:
     * - "I" -> Type::Int
     * - "J" -> Type::Long
     *
     * @param s Input string view to parse.
     * @param out Output parameter receiving the parsed primitive type on success.
     * @return True if parsing succeeded; false otherwise.
     */
    bool tryParsePrimitive(std::string_view s, Descriptor::Type &out);
} // namespace jvm::detail

#endif // JVM_DESCRIPTOR_UTILS_H
