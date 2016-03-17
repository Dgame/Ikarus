#ifndef IKARUS_VARIABLEDECLARATION_HPP
#define IKARUS_VARIABLEDECLARATION_HPP

#include <StorageClass.hpp>
#include "Declaration.hpp"
#include "StorageClass.hpp"

class VariableDeclaration : public Declaration {
private:
    u32_t _stc = StorageClass.MUTABLE;

public:
    using Declaration::Declaration;

    void setStorageClass(u32_t stc) {
        _stc = stc;
    }

    u32_t getStorageClass() const {
        return _stc;
    }

    u32_t& getStorageClass() {
        return _stc;
    }

    bool isConst() const {
        return (_stc & StorageClass.IMMUTABLE) != 0;
    }

    bool isRef() const {
        return (_stc & StorageClass.REFERENCE) != 0;
    }
};

#endif //IKARUS_VARIABLEDECLARATION_HPP
