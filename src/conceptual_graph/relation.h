
#pragma once

#include <ostream>
#include "../wordnet/synset.h"

namespace wn {
    struct relation {
        int type;
        synset source;
        synset target;       
        bool operator==(const relation& other) const {
            return type == other.type;
        };
    };

    inline std::ostream& operator<<(std::ostream& os, const relation& rel) {
        os << rel.type;
        return os;
    }
}