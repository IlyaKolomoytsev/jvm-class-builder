#ifndef JVM__CONSTANT_STRING_H
#define JVM__CONSTANT_STRING_H

#include "constant-utf-8-info.h"
#include "constant.h"

namespace Jvm
{
    /**
     * String constant.
     */
    class ConstantString : public Constant
    {
    public:
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @note Cant create UTF-8 string constant.
         * @param string String value.
         * @param classOwner Class owner.
         * @return String constant.
         */
        ConstantString* getOrCreate(std::string string, Class* classOwner);

        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @param utf8StringConstant UTF-8 string constant.
         * @return String constant.
         */
        ConstantString* getOrCreate(ConstantUtf8Info* utf8StringConstant);

        /**
         * @return UTF-8 string constant.
         */
        [[nodiscard]] ConstantUtf8Info* getString();

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create string constant.
         * @param utf8StringConstant UTF-8 string constant.
         */
        ConstantString(ConstantUtf8Info* utf8StringConstant);

        ConstantUtf8Info* string_; ///< UTF-8 string constant.
    };
} // Jvm

#endif //JVM__CONSTANT_STRING_H
