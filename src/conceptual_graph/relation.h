
#pragma once

#include <ostream>
#include "../distance/synset.h"

namespace wn {
    struct relation {
        int type;
        wnb::synset source;
        wnb::synset target;
        /*
        relation& operator=(const relation& other) {
            this->type = other.type;
            this->source = other.source;
            this->target = other.target;
            return *this;
        }
        */
    };

    inline std::ostream& operator<<(std::ostream& os, const relation& rel) {
        os << rel.type;
        return os;
    }
}