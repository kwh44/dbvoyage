//
// Created by kwh44 on 11/30/19.
//

#ifndef DBVOYAGE_TRANSITIVE_CLOSURE_HPP
#define DBVOYAGE_TRANSITIVE_CLOSURE_HPP

#include "triple.hpp"

void transitive_closure(const std::set<Triple> &c1, const std::set<Triple> &c2, std::set<Triple> &out) {
    // find statements where c1-objects intersect with c2-subjects
    // for these statements form new statements
    // c1-subject - c2-predicate - c2-object
    for (const auto &v: c1) {
        for (const auto &r: c2) {
            if (v.cget_object() == r.cget_subject()) {
                out.emplace(v.get_subject(), r.get_predicate(), r.get_object());
            }
        }
    }
}

#endif //DBVOYAGE_TRANSITIVE_CLOSURE_HPP
