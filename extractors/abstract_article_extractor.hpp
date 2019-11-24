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
};

#endif //DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP
