
#pragma once

#include <ostream>

namespace wn {
    struct relation {
        int type;
    };
    inline std::ostream& operator<<(std::ostream& os, const relation& rel) {
        os << rel.type;
        return os;
    }
}