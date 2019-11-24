//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_PAGE_REVISION_EXTRACTOR_HPP
#define DBVOYAGE_PAGE_REVISION_EXTRACTOR_HPP

#include "extractor_base.hpp"

class PageRevisionExtractor : Extractor {
    // Whenever a Wikivoyage article is modified, it gets a new Revision ID.
    // This extractor extracts that ID and represents it using wikiPageRevisionID
    void extract() override {

    }
};

#endif //DBVOYAGE_PAGE_REVISION_EXTRACTOR_HPP
