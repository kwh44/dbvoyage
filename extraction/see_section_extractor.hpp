//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_SEE_SECTION_EXTRACTOR_HPP
#define DBVOYAGE_SEE_SECTION_EXTRACTOR_HPP

#include <map>
#include "../dump_parser/parser.hpp"
#include "extractor_base.hpp"
#include "../utils/listing_parameters.hpp"

class SeeSectionExtractor : public Extractor {

public:
    explicit SeeSectionExtractor(PageNode *pn) {
        articles = pn;
        filename = "see_section.nt";
    }

    // Extracts attractions from See section, enclosed in * {{see .. }}
    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            if (PageNode::na_article(it)) continue;
            if (PageNode::redirect_article(it)) continue;
            std::string page_title(PageNode::get_page_title(it));
            auto page_text_itr = PageNode::get_text(it);
            std::map<std::string, std::string> see_key_value;
            while (see_tag_start_find(page_text_itr)) {
                // page_text_itr was moved to the start of '* {{see' tag
                auto see_tag_size = find_see_tag_size(page_text_itr);
                std::string attraction_name;
                for (const auto &key: listing::keys) {
                    auto value = get_parameter_value(page_text_itr, see_tag_size, key);
                    if (value.empty()) continue;
                    std::string predicate;
                    if (key == "name") {
                        attraction_name = "<https://dbvoyage.org/ontology/attraction/" + value + ">";
                        std::string subject("<https://dbvoyage.org/ontology/article/" + page_title + ">");
                        predicate = "<https://dbvoyage.org/ontology/property/hasAttraction>";
                        create_statement(subject, predicate, attraction_name);
                        predicate = "<https://dbvoyage.org/ontology/property/locatedAt>";
                        create_statement(attraction_name, predicate, subject);
                    }
                    predicate = "<https://dbvoyage.org/ontology/property/" + key + ">";
                    create_statement(attraction_name, predicate, value);
                }
                ++page_text_itr;
            }
        }
    }

private:
    static bool see_tag_start_find(page_iterator_t &itr) {
        // move itr to start of string "* {{see"
        while (*itr != '\0') {
            if (*itr == '{' && *(itr + 1) == '{' && *(itr + 2) == 's'
                && *(itr + 3) == 'e' && *(itr + 4) == 'e') {
                return true;
            }
            ++itr;
        }
        return false;
    }

    static size_t find_see_tag_size(page_iterator_t itr) {
        size_t size = 1;
        while (*++itr != '}') ++size;
        return size;
    }
};

#endif //DBVOYAGE_SEE_SECTION_EXTRACTOR_HPP
