#ifndef JVM__DESCRIPTOR_FIELD_H
#define JVM__DESCRIPTOR_FIELD_H

#include <cassert>
#include <utility>

#include "descriptor.h"

namespace jvm {
    /**
     * @brief JVM field type descriptor.
     *
     * Represents a JVM field descriptor, including:
     * - primitive types,
     * - reference types,
     * - array types with arbitrary depth.
     */
    class DescriptorField : public Descriptor {
    public:
        /**
         * @brief Construct a primitive field descriptor.
         *
         * Builds a JVM field descriptor for a primitive type (e.g. int, long, boolean),
         * optionally wrapped in one or more array dimensions.
         *
         * Examples:
         * - DescriptorField(Type::Int)           -> "I"
         * - DescriptorField(Type::Long, 2)       -> "[[J"
         *
         * @param primitiveFieldType Primitive JVM type tag. Must NOT be Type::Reference.
         * @param arrayDepth Number of array dimensions (0 = not an array, 1 = one-dimensional, etc.).
         */
        DescriptorField(Type primitiveFieldType, uint8_t arrayDepth = 0);

        /**
         * @brief Construct a reference field descriptor.
         *
         * Builds a JVM reference descriptor for a class type, optionally wrapped in array dimensions.
         *
         * Accepted inputs:
         * - Internal JVM class names: "java/lang/String"      -> "Ljava/lang/String;"
         * - Wrapped reference descriptors: "Ljava/lang/String;" (will be normalized)
         * - Convenience single-letter primitive descriptors: "J", "D", "Z", ... (treated as primitive)
         *
         * Examples:
         * - DescriptorField("java/lang/String")        -> "Ljava/lang/String;"
         * - DescriptorField("Ljava/lang/String;")      -> "Ljava/lang/String;"
         * - DescriptorField("java/lang/String", 1)     -> "[Ljava/lang/String;"
         * - DescriptorField("J")                       -> "J"   (convenience for codegen)
         *
         * @param classReference Internal JVM class name (e.g. "java/lang/String") or an accepted form listed above.
         * @param arrayDepth Number of array dimensions (0 = not an array, 1 = one-dimensional, etc.).
         *
         * @throws std::invalid_argument If @p classReference is empty.
         */
        DescriptorField(std::string classReference, uint8_t arrayDepth = 0);

        /**
         * @brief Create a primitive field descriptor (named constructor).
         *
         * This is a convenience factory that makes call sites self-documenting and
         * avoids accidental confusion with the string constructor.
         *
         * Examples:
         * - DescriptorField::Primitive(Type::Long)      -> "J"
         * - DescriptorField::Primitive(Type::Int, 3)    -> "[[[I"
         *
         * @param t Primitive JVM type tag. Must NOT be Type::Reference.
         * @param arrayDepth Number of array dimensions.
         * @return A DescriptorField representing the primitive type (optionally as an array).
         */
        static DescriptorField Primitive(Type t, uint8_t arrayDepth = 0);

        /**
         * @brief Create a reference field descriptor (named constructor).
         *
         * This is a convenience factory that makes call sites self-documenting.
         *
         * Expected input:
         * - Internal JVM class name like "java/lang/String"
         *
         * Note: This does NOT require "L...;" wrapping; wrapping is added by toString().
         *
         * Examples:
         * - DescriptorField::Ref("java/lang/String")      -> "Ljava/lang/String;"
         * - DescriptorField::Ref("java/lang/String", 2)   -> "[[Ljava/lang/String;"
         *
         * @param internalName JVM internal class name (e.g. "java/lang/String").
         * @param arrayDepth Number of array dimensions.
         * @return A DescriptorField representing the reference type (optionally as an array).
         */
        static DescriptorField Ref(std::string internalName, uint8_t arrayDepth = 0);

        /**
         * @return Field base type.
         */
        [[nodiscard]] Type getType() const { return primitiveFieldType_; }

        /**
         * @return Number of array dimensions.
         */
        [[nodiscard]] uint8_t getArrayDepth() const { return arrayDepth_; }

        /**
         * @return True if this descriptor represents a reference type.
         */
        [[nodiscard]] bool isReferenceType() const { return getType() == Type::Reference; }

        /**
         * @return JVM class reference name (valid only for reference types).
         */
        [[nodiscard]] std::string getClassReference() const { return classReference_; }

        /**
         * @brief Convert field descriptor to JVM string form.
         *
         * @return JVM field descriptor string.
         */
        [[nodiscard]] std::string toString() const override;

    private:
        Type primitiveFieldType_;
        uint8_t arrayDepth_;
        std::string classReference_;
    };
} //jvm

#endif //JVM__DESCRIPTOR_FIELD_H
