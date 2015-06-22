
#include "distance_relation_unl.h"

using namespace wn;
using namespace wn::distance;
using namespace std;


base_relation_unl::base_relation_unl() {
}

float base_relation_unl::operator()(const wn::unl::relation& rel1, const wn::unl::relation& rel2) const {
    auto f = [=](const relation& r1, const relation& r2) {
        using namespace wn::unl;
        if (r1.type_ == r2.type_) {
            return this->lower_bound();
        }
        else {
            if (r1.type_ == wn::unl::relation::AOJ && (
                r2.type_ == wn::unl::relation::ANT ||
                r2.type_ == wn::unl::relation::EQU ||
                r2.type_ == wn::unl::relation::FLD ||
                r2.type_ == wn::unl::relation::ICL ||
                r2.type_ == wn::unl::relation::IOF ||
                r2.type_ == wn::unl::relation::POF)) {
                return 0.2f;
            }
            else if (r1.type_ == wn::unl::relation::MOD && (
                     r2.type_ == wn::unl::relation::MAT ||
                     r2.type_ == wn::unl::relation::NAM ||
                     r2.type_ == wn::unl::relation::POS ||
                     r2.type_ == wn::unl::relation::QUA)) {
                return 0.2f;
            }
            else if (r1.type_ == wn::unl::relation::OBJ && (
                     r2.type_ == wn::unl::relation::OPL ||
                     r2.type_ == wn::unl::relation::RES)) {
                return 0.2f;
            }
            else if (r1.type_ == wn::unl::relation::PER && r2.type_ == wn::unl::relation::BAS) {
                return 0.2f;
            }
            else if (r1.type_ == wn::unl::relation::PLC && (
                     r2.type_ == wn::unl::relation::GOL ||
                     r2.type_ == wn::unl::relation::LPL ||
                     r2.type_ == wn::unl::relation::SRC ||
                     r2.type_ == wn::unl::relation::VIA)) {
                return 0.2f;
            }
            else if (r1.type_ == wn::unl::relation::TIM && (
                     r2.type_ == wn::unl::relation::TMF ||
                     r2.type_ == wn::unl::relation::TMT ||
                     r2.type_ == wn::unl::relation::DUR ||
                     r2.type_ == wn::unl::relation::COO)) {
                return 0.2f;
            }
            else if (r1.type_ == wn::unl::relation::MAN && (
                     r2.type_ == wn::unl::relation::INS ||
                     r2.type_ == wn::unl::relation::MET ||
                     r2.type_ == wn::unl::relation::PUR)) {
                return 0.2f;
            }
            else {
                return 0.8f;
            }
        }
    };
    auto f1 = f(rel1, rel2);
    auto f2 = f(rel2, rel1);
    return min(f1, f2);
}
