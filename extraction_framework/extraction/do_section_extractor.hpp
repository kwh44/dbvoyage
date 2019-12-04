//
// Created by kwh44 on 12/4/19.
//

#ifndef DBVOYAGE_DO_SECTION_EXTRACTOR_HPP
#define DBVOYAGE_DO_SECTION_EXTRACTOR_HPP

#include "extractor_base.hpp"
#include "../utils/listing_parameters.hpp"
#include <boost/algorithm/string/trim.hpp>

class DoSectionExtractor : public Extractor {

public:
    explicit DoSectionExtractor(PageNode *pn) {
        articles = pn;
        filename = "do_section.nt";
    }

    // Extracts attractions from Do section, enclosed in * {{do .. }} or * {{listing | type=do ...}}
    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            if (PageNode::na_article(it)) continue;
            if (PageNode::redirect_article(it)) continue;
            std::string page_title(PageNode::get_page_title(it));
            auto page_text_itr = PageNode::get_text(it);
            while (start_find(page_text_itr, "{{do")) {
                ++page_text_itr;
            }
        }
    }
};

#endif //DBVOYAGE_DO_SECTION_EXTRACTOR_HPP
