#ifndef JVM__CONSTANT_METHODREF_H
#define JVM__CONSTANT_METHODREF_H

#include "constant-class.h"
#include "constant-name-and-type.h"
#include "constant.h"

namespace Jvm
{
    class ConstantMethodref : public Constant
    {
    public:
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @note Can create class constant or name and type constant.
         * @param className Class name string.
         * @param methodName Method name string.
         * @param methodDescriptor Method descriptor.
         * @param classOwner Class owner.
         * @return Methodref constant.
         */
        static ConstantMethodref* getOrCreate(std::string className, std::string methodName,
                                              std::string methodDescriptor, Class* classOwner);
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @param classConstant Class constant.
         * @param nameAndTypeConstant Method name and type constant.
         * @return Methodref constant.
         */
        static ConstantMethodref* getOrCreate(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant);

        /**
         * @return Class constant.
         */
        [[nodiscard]] ConstantClass* getClass() const;

        /**
         * @return Method name and type constant.
         */
        [[nodiscard]] ConstantNameAndType* getNameAndType() const;

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create methodref constant.
         * @param classConstant Class constant.
         * @param nameAndTypeConstant Method name and type constant.
         */
        ConstantMethodref(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant);

        ConstantClass* class_; ///< Class constant.
        ConstantNameAndType* nameAndType_; ///< Method name and type constant.
    };
} // Jvm

#endif //JVM__CONSTANT_METHODREF_H
