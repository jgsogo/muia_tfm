
#pragma once

#include "relation.h"

namespace wn {
    namespace unl {
        struct relation : wn::relation {
            //! Unl relations: http://www.undl.org/unlsys/unl/unl2005/Relation.htm
            enum class types {
                AGT, AND, AOJ, BAS, BEN, CAG, CAO, CNT, COB, CON, COO, DUR, EQU, FMT, FRM,
                GOL, ICL, INS, INT, IOF, MAN, MET, MOD, NAM, OBJ, OPL, OR, PER, PLC, PLF,
                PLT, POF, POS, PTN, PUR, QUA, RSN, SCN, SEQ, SHD, SRC, TIM, TMF, TMT, TO,
                VIA
            };
            static const char* str_types[];
        };
    }
}