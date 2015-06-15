
#pragma once

#include "conceptual_graph/wn_conceptual_graph_export.h"
#include "relation.h"

namespace wn {
    namespace unl {
        struct relation : wn::relation {
            //! Relation types taken from http://www.unlweb.net/wiki/Universal_Relations
            enum type : std::uint16_t {
                    AGT,    // Agent
                    AND,    // Conjuntion
                    AOJ,    // Object of an attribute
                        ANT,// Antonym, different from
                        EQU,// Synonym, equal to
                        FLD,// Field
                        ICL,// Hyponym, a kind of
                        IOF,// Example, instance of
                        POF,// Meronym, part of
                    BEN,    // Beneficiary
                    CNT,    // Content or theme
                    CON,    // Condition
                    EXP,    // Experiencer
                    MOD,    // Modifier
                        MAT,// Material
                        NAM,// Name
                        POS,// Possessor
                        QUA,// Quantifier
                    OBJ,    // Patient
                        OPL,// Objective place
                        RES,// Result
                    OR,     // Disjunction
                    PER,    // Proportion, rate, distribution or basis for a comparison
                        BAS,// Basis for a comparison
                    PLC,    // Location: physical or logical
                        GOL,// Final place or state, destination
                        LPL,// Logical place, scene
                        SRC,// Initial place or state, origin
                        VIA,// Intermediate place, path
                    PTN,    // Partner
                    TIM,    // Time
                        TMF,// Initial time
                        TMT,// Final time
                        DUR,// Duration
                            COO,    // Co-ocurrence
                    MAN,    // Manner
                        INS,// Instrument or method
                            MET,    // Method
                        PUR,// Purpose
                    RSN,    // Reason
                    SEQ     // Consequence
                    };


        };

        WN_CONCEPTUAL_GRAPH_EXPORT std::ostream& operator<<(std::ostream& os, const unl::relation::type& rel_type);
        WN_CONCEPTUAL_GRAPH_EXPORT void from_string(const std::string&, unl::relation::type& rel_type);
        

    }
}
