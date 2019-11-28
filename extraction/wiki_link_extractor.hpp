//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_WIKI_LINK_EXTRACTOR_HPP
#define DBVOYAGE_WIKI_LINK_EXTRACTOR_HPP
#include "extractor_base.hpp"

class WikiLinkExtractor: Extractor {
    // internal links between dbvoyage instances.
    // and represent them by using the wikilink property.
    void extract() override {

    }

    void write_to_destination() override {
        // filename to write statements
        std::string filename("xxxxxx_en.nt");
        // open output file stream
        std::ofstream destination(filename);
        // write all statement to it
        for (const auto &statement: statements) {
            destination << statement;
        }
    }
};
#endif //DBVOYAGE_WIKI_LINK_EXTRACTOR_HPP
