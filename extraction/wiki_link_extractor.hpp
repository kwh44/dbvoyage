//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_WIKI_LINK_EXTRACTOR_HPP
#define DBVOYAGE_WIKI_LINK_EXTRACTOR_HPP

#include "extractor_base.hpp"

class WikiLinkExtractor: public Extractor {

public:
    explicit WikiLinkExtractor(PageNode * pn) {
        articles = pn;
        filename = "wiki_links.nt";
    }
    // internal links between dbvoyage articles.
    // and represent them by using the wikilink property.
    void extract() override {}
};
#endif //DBVOYAGE_WIKI_LINK_EXTRACTOR_HPP
