//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_PAGE_ID_EXTRACTOR_HPP
#define DBVOYAGE_PAGE_ID_EXTRACTOR_HPP

#include "extractor_base.hpp"

class PageIDExtractor : Extractor {
    // Each wikivoyage article has a unique ID. This extractor extracts that ID and represents it using wikiPageID predicate.
    void extract() override {

    }
};


#endif //DBVOYAGE_PAGE_ID_EXTRACTOR_HPP
