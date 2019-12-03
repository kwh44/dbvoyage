//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_TRIPLE_HPP
#define DBVOYAGE_TRIPLE_HPP

class Triple {

    using str=std::string;

    str subject;
    str predicate;
    str object;
public:
    explicit Triple(str &subj, str &pred, str &obj) : subject(subj), predicate(pred), object(obj) {}

    explicit Triple(const str &subj, const str &pred, const str &obj) : subject(subj), predicate(pred), object(obj) {}

    Triple(str &&subj, str &&pred, str &&obj) : subject(subj), predicate(pred), object(obj) {}

    Triple() = default;

    Triple(Triple &&) = default;

    Triple(const Triple &) = default;

    Triple(Triple &) = default;

    const str &cget_subject() const { return subject; }

    const str &cget_object() const { return object; }

    str get_subject() const { return subject; }

    str get_predicate() const { return predicate; }

    str get_object() const { return object; }

    friend std::ofstream &operator<<(std::ofstream &, const Triple &);

    friend std::ostream &operator<<(std::ostream &, const Triple &);

    friend bool operator<(const Triple &, const Triple &);

    friend bool operator>(const Triple &, const Triple &);

    friend bool operator==(const Triple &a, const Triple &b);
};

std::ofstream &operator<<(std::ofstream &output, const Triple &tr) {
    output << tr.subject << " " << tr.predicate << " " << tr.object << " ." << std::endl;
    return output;
}

bool operator<(const Triple &a, const Triple &b) {
    if (a == b) return false;
    return !(a > b);
}

bool operator>(const Triple &a, const Triple &b) {
    if (a == b) return false;
    if (a.subject == b.subject) {
        if (a.predicate == b.predicate) return a.object > b.object;
        else return a.predicate > b.predicate;
    } else return a.subject > b.subject;
}

bool operator==(const Triple &a, const Triple &b) {
    return a.subject == b.subject && a.predicate == b.predicate && a.object == b.object;
}

std::ostream &operator<<(std::ostream &output, const Triple &tr) {
    output << tr.subject << " " << tr.predicate << " " << tr.object << " ." << std::endl;
    return output;
}


#endif //DBVOYAGE_TRIPLE_HPP
