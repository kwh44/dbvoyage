//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_EXTRACTOR_BASE_HPP
#define DBVOYAGE_EXTRACTOR_BASE_HPP

#include <set>
#include <fstream>
#include "../dump_parser/parser.hpp"
#include "../utils/triple.hpp"
#include "../utils/url_format.hpp"
#include "../utils/clean_object.hpp"

class Extractor {

protected:
    std::string filename;
    std::set<Triple> statements;
    PageNode *articles = nullptr;
    std::string graph{"http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com"};
public:

    virtual void extract() {}


    void write_to_destination() {
        std::ofstream destination(filename);
        for (const auto &statement: statements) { destination << statement; }
    }

    auto &get_triples() { return statements; }

    [[nodiscard]] const auto &cget_triples() const { return statements; }

    void create_statement(std::string &subj, std::string &pred, std::string &obj) {
        statements.emplace(subj, pred, obj);
    }

};

#endif //DBVOYAGE_EXTRACTOR_BASE_HPP