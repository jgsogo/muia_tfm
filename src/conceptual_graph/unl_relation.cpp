
#include "unl_relation.h"

namespace wn {
    namespace unl {

        const std::string unl_relation_to_str[] = {
            "agt",
            "and",
            "aoj",
            "ant",
            "equ",
            "fld",
            "icl",
            "iof",
            "pof",
            "ben",
            "cnt",
            "con",
            "exp",
            "mod",
            "mat",
            "nam",
            "pos",
            "qua",
            "obj",
            "opl",
            "res",
            "or",
            "per",
            "bas",
            "plc",
            "gol",
            "lpl",
            "src",
            "via",
            "ptn",
            "tim",
            "tmf",
            "tmt",
            "dur",
            "coo",
            "man",
            "ins",
            "met",
            "pur",
            "rsn",
            "seq"
        };
        
        std::ostream& operator<<(std::ostream& os, const unl::relation::type& rel_type) {
            os << unl_relation_to_str[rel_type];
            return os;
        }

        void from_string(const std::string& str, unl::relation::type& rel_type) {
            auto i = 0;
            for (auto& item : unl_relation_to_str) {
                if (item.compare(str) == 0) { break; }
                ++i;
            }
            rel_type = static_cast<unl::relation::type>(i);            
        }

    }
}
