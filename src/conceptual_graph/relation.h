
#pragma once

#include <ostream>
#include "../wordnet/synset.h"

namespace wn {
    struct relation {
        std::uint16_t type_;
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
