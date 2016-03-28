#ifndef IKARUS_STORAGECLASS_HPP
#define IKARUS_STORAGECLASS_HPP

struct {
    enum {
        NONE      = 0x0,
        MUTABLE   = 0x1,
        IMMUTABLE = 0x2,
        REFERENCE = 0x4,
    };
} StorageClass;

#endif //IKARUS_STORAGECLASS_HPP
