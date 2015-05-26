
#pragma once

#include <ostream>
#include "../wordnet/synset.h"

namespace wn {
    struct relation {
        int type;
        synset source;
        synset target;       
    };

    inline std::ostream& operator<<(std::ostream& os, const relation& rel) {
        os << rel.type;
        return os;
    }
}