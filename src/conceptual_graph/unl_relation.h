
#pragma once

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

        inline std::ostream& operator<<(std::ostream& os, const unl::relation::type& rel_type) {
            switch(rel_type) {
                case relation::AGT: return os << "agt";
                case relation::AND: return os << "and";
                case relation::AOJ: return os << "aoj";
                case relation::ANT: return os << "ant";
                case relation::EQU: return os << "equ";
                case relation::FLD: return os << "fld";
                case relation::ICL: return os << "icl";
                case relation::IOF: return os << "iof";
                case relation::POF: return os << "pof";
                case relation::BEN: return os << "ben";
                case relation::CNT: return os << "cnt";
                case relation::CON: return os << "con";
                case relation::EXP: return os << "exp";
                case relation::MOD: return os << "mod";
                case relation::MAT: return os << "mat";
                case relation::NAM: return os << "nam";
                case relation::POS: return os << "pos";
                case relation::QUA: return os << "qua";
                case relation::OBJ: return os << "obj";
                case relation::OPL: return os << "opl";
                case relation::RES: return os << "res";
                case relation::OR: return os << "or";
                case relation::PER: return os << "per";
                case relation::BAS: return os << "bas";
                case relation::PLC: return os << "plc";
                case relation::GOL: return os << "gol";
                case relation::LPL: return os << "lpl";
                case relation::SRC: return os << "src";
                case relation::VIA: return os << "via";
                case relation::PTN: return os << "ptn";
                case relation::TIM: return os << "tim";
                case relation::TMF: return os << "tmf";
                case relation::TMT: return os << "tmt";
                case relation::DUR: return os << "dur";
                case relation::COO: return os << "coo";
                case relation::MAN: return os << "man";
                case relation::INS: return os << "ins";
                case relation::MET: return os << "met";
                case relation::PUR: return os << "pur";
                case relation::RSN: return os << "rsn";
                case relation::SEQ: return os << "seq";
                // omit default case to trigger compiler warning for missing cases
            };
        }


    }
}
