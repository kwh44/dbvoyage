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
    std::string filename;
    std::vector<Triple> statements;
    PageNode *articles = nullptr;

public:

    virtual void extract() {}


    void write_to_destination() {
        std::ofstream destination(filename);
        for (const auto &statement: statements) { destination << statement; }
    }

    void create_statement(std::string &subj, std::string &pred, std::string &obj) {
        statements.emplace_back(Triple(subj, pred, obj));
    }

};

#endif //DBVOYAGE_EXTRACTOR_BASE_HPP