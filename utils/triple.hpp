//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_TRIPLE_HPP
#define DBVOYAGE_TRIPLE_HPP

#include <string>
#include <iostream>
#include <fstream>

class Triple {

    using str=std::string;

    str subject;
    str predicate;
    str object;
public:
    explicit Triple(str &subj, str &pred, str &obj) : subject(subj), predicate(pred), object(obj) {}

    explicit Triple(const str &subj, const str &pred, const str &obj) : subject(subj), predicate(pred), object(obj) {}

    explicit Triple(str &&subj, str &&pred, str &&obj) : subject(subj), predicate(pred), object(obj) {}

    Triple() = default;

    Triple(Triple &&) = default;

    Triple(Triple &) = default;

    inline auto &get_subject() const { return subject; }

    inline auto &get_predicate() const { return predicate; }

    inline auto &get_object() const { return object; }

    friend std::ofstream &operator<<(std::ofstream &, const Triple &);

    friend std::ostream &operator<<(std::ostream &, const Triple &);
};

std::ofstream &operator<<(std::ofstream &output, const Triple &tr) {
    output << tr.subject << " " << tr.predicate << " " << tr.object << " ." << std::endl;
    return output;
}

std::ostream &operator<<(std::ostream &output, const Triple &tr) {
    output << tr.subject << " " << tr.predicate << " " << tr.object << " ." << std::endl;
    return output;
}

#endif //DBVOYAGE_TRIPLE_HPP
