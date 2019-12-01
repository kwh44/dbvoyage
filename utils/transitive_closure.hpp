//
// Created by kwh44 on 11/30/19.
//

#ifndef DBVOYAGE_TRANSITIVE_CLOSURE_HPP
#define DBVOYAGE_TRANSITIVE_CLOSURE_HPP

#include "triple.hpp"
#include <vector>

// it has to be parallelized, it is too slow

void transitive_closure(const std::vector<Triple> &c1,const  std::vector<Triple> &c2, std::vector<Triple> &out) {
    // find statements where c1-objects intersect with c2-subjects
    // for these statements form new statements
    // c1-subject - c2-predicate - c2-object
    for (const auto &v: c1) {
        for (const auto &r: c2) {
            if (r.cget_predicate() != "<https://dbvoyage.org/ontology/property/hasAttraction>") continue;
            if (v.cget_object() == r.cget_subject()) {
                out.emplace_back(v.get_subject(), r.get_predicate(), r.get_object());
            }
        }
    }
}

void transitive_closure(const std::vector<Triple> &c1, const std::vector<Triple> &c2,const  std::vector<Triple> &c3,
                        std::vector<Triple> &out) {
    // find statements where c1-objects intersect with c2-subjects and c2 object intersect with c3 subjects
    // for these statements form new statements
    // c1-subject - c3-predicate - c3-object
    std::vector<Triple> new_statements;
    for (const auto &v: c1) {
        for (const auto &r: c2) {
            if (v.cget_object() == r.cget_subject()) {
                for (const auto &j: c3) {
                    if (r.cget_object() == j.cget_subject()) {
                        out.emplace_back(v.get_subject(), j.get_predicate(), j.get_object());
                    }
                }
            }
        }
    }
}


#endif //DBVOYAGE_TRANSITIVE_CLOSURE_HPP
