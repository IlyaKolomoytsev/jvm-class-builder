#ifndef JVM__CONSTANT_CLASS_H
#define JVM__CONSTANT_CLASS_H
#include "constant-utf-8-info.h"
#include "constant.h"

namespace Jvm
{
    /**
     * Class constant.
     */
    class ConstantClass : public Constant
    {
    public:
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * Can create UTF-8 constant.
         * @param name String of class name.
         * @param classOwner Pointer to class owner object.
         * @return Class constant.
         */
        static ConstantClass* getOrCreate(std::string name, Class* classOwner);

        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @param name UTF-8 constant.
         * @return Class constant.
         */
        static ConstantClass* getOrCreate(ConstantUtf8Info* name);

        /**
         * @return Utf-8 constant.
         */
        ConstantUtf8Info* getName() const;

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create constant class.
         * @param name Utf-8 constant with class name.
         */
        ConstantClass(ConstantUtf8Info* name);

        /**
         * Utf-8 constant with class name.
         */
        ConstantUtf8Info* name_ = nullptr;
    };
} // Jvm

#endif //JVM__CONSTANT_CLASS_H
