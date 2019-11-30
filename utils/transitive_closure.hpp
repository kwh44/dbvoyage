//
// Created by kwh44 on 11/30/19.
//

#ifndef DBVOYAGE_TRANSITIVE_CLOSURE_HPP
#define DBVOYAGE_TRANSITIVE_CLOSURE_HPP

#include "triple.hpp"
#include <vector>

void transitive_closure(std::vector<Triple> &c1, std::vector<Triple> &c2, std::vector<Triple> &out) {
    // find statements where one-objects intersect with two-subjects
    // for these statements form new statements
    // one-subject - two-predicate - two-object
    for (const auto &v: c1) {
        for (const auto &r: c2) {
            if (r.get_predicate() != "<https://dbvoyage.org/ontology/property/hasAttraction>") continue;
            if (v.get_object() == r.get_subject()) {
                out.emplace_back(Triple(v.get_subject(), r.get_predicate(), r.get_object()));
            }
        }
    }
}

void transitive_closure(std::vector<Triple> &c1, std::vector<Triple> &c2, std::vector<Triple> &c3,
                        std::vector<Triple> &out) {
    // find statements where one-objects intersect with two-subjects and two object intersect with three subjects
    // for these statements form new statements
    // one-subject - three-predicate - three-object
    std::vector<Triple> new_statements;
    for (const auto &v: c1) {
        for (const auto &r: c2) {
            if (r.get_predicate() != "<https://dbvoyage.org/ontology/property/hasAttraction>") continue;
            if (v.get_object() == r.get_subject()) {
                for (const auto &j: c3) {
                    if (r.get_object() == j.get_subject()) {
                        out.emplace_back(v.get_subject(), j.get_predicate(), j.get_object());
                    }
                }
            }
        }
    }
}


#endif //DBVOYAGE_TRANSITIVE_CLOSURE_HPP
