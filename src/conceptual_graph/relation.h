
#pragma once

#include <ostream>
#include <cstdint>
#include "../wordnet/synset.h"

namespace wn {
    struct relation {
        typedef std::uint16_t type;
        type type_;
        synset source;
        synset target;
        bool operator==(const relation& other) const {
            return type_ == other.type_;
        };
    };

    inline std::ostream& operator<<(std::ostream& os, const relation& rel) {
        os << rel.type_;
        return os;
    }
}
