//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_EXTRACTOR_BASE_HPP
#define DBVOYAGE_EXTRACTOR_BASE_HPP

#include <vector>
#include <fstream>
#include "../dump_parser/parser.hpp"
#include "../utils/triple.hpp"

class Extractor {
protected:
    std::vector<Triple> statements;
    PageNode &articles;
public:
    explicit Extractor(PageNode &pn) : articles(pn) {}

    virtual void extract() = 0;

    void create_statement(std::string &subj, std::string &pred, std::string &obj) {
        statements.emplace_back(Triple(subj, pred, obj));
    }

    void write_to_destination(std::string &&filename) {
        // write all statements to file
        // Step one: create file
        std::ofstream file(filename);
        for (const auto &v: statements) {
            file << v;
            file << std::endl;
        }
    }
};

#endif //DBVOYAGE_EXTRACTOR_BASE_HPP