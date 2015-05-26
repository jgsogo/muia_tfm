
#pragma once

#include <ostream>
#include "../distance/synset.h"

namespace wn {
    struct relation {
        int type;
        wnb::synset source;
        wnb::synset target;       
    };

    inline std::ostream& operator<<(std::ostream& os, const relation& rel) {
        os << rel.type;
        return os;
    }
}