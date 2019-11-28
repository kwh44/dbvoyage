//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP
#define DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP


#include "extractor_base.hpp"

class AbstractPageExtractor : Extractor {
public:
    // Extracts a short abstract (first paragraph, represented by using rdfs:comment)
    void extract() override {

    }
    void write_to_destination() override {
        // filename to write statements
        std::string filename("abstract_article_en.nt");
        // open output file stream
        std::ofstream destination(filename);
        // write all statement to it
        for (const auto &statement: statements) {
            destination << statement;
        }
    }
};

#endif //DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP
