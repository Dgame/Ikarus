#ifndef IKARUS_VARIABLEDECLARATION_HPP
#define IKARUS_VARIABLEDECLARATION_HPP

#include "Declaration.hpp"
#include "StorageClass.hpp"

class VariableDeclaration : public Declaration {
private:
    std::string _name;
    u32_t _stc = StorageClass.MUTABLE;

    explicit VariableDeclaration(const std::string&, size_t, Expression*);

public:
    explicit VariableDeclaration(const std::string&, Expression*);

    const std::string& getName() const {
        return _name;
    }

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

    virtual void accept(EvalVisitor&) override;
    virtual VariableDeclaration* child(Expression*) const override;
};

#endif //IKARUS_VARIABLEDECLARATION_HPP
