//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_SEE_SECTION_EXTRACTOR_HPP
#define DBVOYAGE_SEE_SECTION_EXTRACTOR_HPP

#include "extractor_base.hpp"
#include "../utils/listing_parameters.hpp"
#include <boost/algorithm/string/trim.hpp>

class SeeSectionExtractor : public Extractor {

public:
    explicit SeeSectionExtractor(PageNode *pn) {
        articles = pn;
        filename = "see_section.nt";
    }

    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            if (PageNode::na_article(it)) continue;
            if (PageNode::redirect_article(it)) continue;
            std::string page_title(PageNode::get_page_title(it));
            auto page_text_itr = PageNode::get_text(it);
            while (find_see(page_text_itr)) {
                auto see_tag_size = tag_size(page_text_itr);
                std::string attraction_name;
                for (const auto &key: listing::keys) {
                    auto value = get_parameter_value(page_text_itr, see_tag_size, key);
                    clean_value(value);
                    if (value.empty() && key == "name") break;
                    if (value.empty()) continue;
                    std::string predicate;
                    boost::algorithm::trim(value);
                    if (key == "name") {
                        attraction_name = graph + "/ontology/attraction/" + value;
                        std::string subject('<' + graph + "/ontology/article/" + page_title + ">");
                        predicate = '<' + graph + "/ontology/property/hasAttraction>";
                        replace_url(attraction_name, "<", "%3C");
                        replace_url(attraction_name, ">", "%3E");
                        replace_url(attraction_name, "\\", "%5C");
                        replace_url(attraction_name, "'", "%27");
                        attraction_name.insert(0, "<");
                        attraction_name.push_back('>');
                        replace_url(attraction_name, " ", "%20");
                        replace_url(subject, " ", "%20");
                        create_statement(subject, predicate, attraction_name);
                        predicate = '<' + graph + "/ontology/property/locatedAt>";
                        create_statement(attraction_name, predicate, subject);
                    }
                    predicate = '<' + graph + "/ontology/property/" + key + ">";
                    if (key == "url") {
                        while (value[value.size() - 1] == ' ') value.erase(value.size() - 1, 1);
                        replace_url(value, " ", "%20");
                        replace_url(value, "\\", "/");
                        replace_url(value, "<", "%3C");
                        replace_url(value, ">", "%3E");
                        value.insert(0, "\"");
                        value.push_back('"');
                    } else {
                        value.insert(0, "\"");
                        replace_url(value, "\n", "%20");
                        value.push_back('"');
                    }
                    create_statement(attraction_name, predicate, value);
                }
                ++page_text_itr;
            }
        }
    }

private:

    static bool find_see(page_iterator_t &itr) {
        std::vector<page_iterator_t> tags;
        std::vector<std::string> patterns{"{{see", "{{ see", "type = see", "type=see"};
        for (auto &v: patterns) {
            auto ptr = find_tag(itr, v);
            if (ptr != nullptr) tags.emplace_back(ptr);
        }
        if (tags.empty()) return false;
        else {
            std::sort(tags.begin(), tags.end());
            itr = tags[0];
            return true;
        }
    }

};

#endif //DBVOYAGE_SEE_SECTION_EXTRACTOR_HPP
