//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_SEE_SECTION_EXTRACTOR_HPP
#define DBVOYAGE_SEE_SECTION_EXTRACTOR_HPP

#include "../dump_parser/parser.hpp"
#include "extractor_base.hpp"

class SeeSectionExtractor : Extractor {

public:
    // Extracts attractions from See section, enclosed in * {{see .. }}
    void extract() override {
        for (auto article = articles.begin(); article != PageNode::end(); ++article) {
            auto article_title = PageNode::get_page_title(article);
            auto article_text_itr = PageNode::get_text(article);
            // for each * {{see ... }}
            while (see_tag_start_find(article_text_itr)) {
                auto tag_size = see_tag_end_find(article_text_itr);
                // in string identified by range [article_text_itr, article_text_itr + tag_size)
                // extract statements ;=)
            }
            // auto article_text_see_tag_start = article_text.find("*")
        }
    }

private:
    static bool see_tag_start_find(page_iterator_t &itr) {
        // move itr to start of string "* {{see"
        // return true if start of string "* {{see" was found else false
        return false;
    }

    static size_t see_tag_end_find(page_iterator_t &itr) {
        // return number of character in string "* {{see ... }}",
        // to the start of which itr points
        // this routine should only be called if previous call
        // to see_tag_start_find returned true
        return 0;
    }
};

#endif //DBVOYAGE_SEE_SECTION_EXTRACTOR_HPP
