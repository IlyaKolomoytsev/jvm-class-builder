#ifndef JVM__CONSTANT_INTERFACE_METHODREF_H
#define JVM__CONSTANT_INTERFACE_METHODREF_H

#include "constant-class.h"
#include "constant-methodref.h"
#include "constant-name-and-type.h"
#include "constant.h"

namespace Jvm
{
    class ConstantInterfaceMethodref: public Constant
    {
    public:
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @note Can create class constant or name and type constant.
         * @param className Class name string.
         * @param methodName Interface method name string.
         * @param methodDescriptor Interface method descriptor.
         * @param classOwner Class owner.
         * @return Interface methodref constant.
         */
        static ConstantInterfaceMethodref* getOrCreate(std::string className, std::string methodName,
                                              std::string methodDescriptor, Class* classOwner);
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @param classConstant Class constant.
         * @param nameAndTypeConstant Method name and type constant.
         * @return Interface methodref constant.
         */
        static ConstantInterfaceMethodref* getOrCreate(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant);

        /**
         * @return Class constant.
         */
        [[nodiscard]] ConstantClass* getClass() const;

        /**
         * @return Interface method name and type constant.
         */
        [[nodiscard]] ConstantNameAndType* getNameAndType() const;

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create interface methodref constant.
         * @param classConstant Class constant.
         * @param nameAndTypeConstant Interface method name and type constant.
         */
        ConstantInterfaceMethodref(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant);

        ConstantClass* class_; ///< Class constant.
        ConstantNameAndType* nameAndType_; ///< Interface method name and type constant.
    };
} //Jvm


#endif //JVM__CONSTANT_INTERFACE_METHODREF_H
