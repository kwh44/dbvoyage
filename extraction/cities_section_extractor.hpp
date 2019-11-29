//
// Created by kwh44 on 11/29/19.
//

#ifndef DBVOYAGE_CITIES_SECTION_EXTRACTOR_HPP
#define DBVOYAGE_CITIES_SECTION_EXTRACTOR_HPP

#include "../dump_parser/parser.hpp"
#include "extractor_base.hpp"

class CitiesSectionExtractor : public Extractor {
public:
    explicit CitiesSectionExtractor(PageNode *pn) {
        articles = pn;
        filename = "cities_section.nt";
    }

    void extract() override {

    }
};

#endif //DBVOYAGE_CITIES_SECTION_EXTRACTOR_HPP
