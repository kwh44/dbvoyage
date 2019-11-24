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

    explicit Triple(str &&subj, str &&pred, str &&obj) : subject(subj), predicate(pred), object(obj) {}

    Triple() = default;

    Triple(Triple &&) = default;

    Triple(Triple &) = default;

    friend std::ofstream &operator<<(std::ofstream &output, const Triple &tr);

    friend std::ostream &operator<<(std::ostream &output, const Triple &tr);
};

std::ofstream &operator<<(std::ofstream &output, const Triple &tr) {
    output << tr.subject << " " << tr.predicate << " " << tr.object;
    return output;
}

std::ostream &operator<<(std::ostream &output, const Triple &tr) {
    output << tr.subject << " " << tr.predicate << " " << tr.object;
    return output;
}

#endif //DBVOYAGE_TRIPLE_HPP
