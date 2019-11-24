//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_LABEL_EXTRACTOR_HPP
#define DBVOYAGE_LABEL_EXTRACTOR_HPP

#include "extractor_base.hpp"

class LabelExtractor : Extractor {
    // All wikivoyage articles have a title, which is used as an rdfs:label for the corresponding DBvoyage resource
    void extract() override {

    }
};

#endif //DBVOYAGE_LABEL_EXTRACTOR_HPP
