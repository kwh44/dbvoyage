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
            while (find_do(page_text_itr)) {
                // subject predicate object
                // page_title do_place name_of_do_place
                auto do_tag_size = tag_size(page_text_itr);

                std::string do_place_name;

                for (const auto &key: listing::keys) {

                    auto value = get_parameter_value(page_text_itr, do_tag_size, key);

                    clean_value(value);

                    if (value.empty() && key == "name") break;

                    if (value.empty()) continue;

                    std::string predicate;

                    boost::algorithm::trim(value);

                    if (key == "name") {

                        do_place_name = graph + "/ontology/activity/" + value;

                        std::string subject('<' + graph + "/ontology/article/" + page_title + ">");

                        predicate = '<' + graph + "/ontology/property/hasActivity>";

                        replace_url(do_place_name, "<", "%3C");
                        replace_url(do_place_name, ">", "%3E");
                        replace_url(do_place_name, "\\", "%5C");
                        replace_url(do_place_name, "'", "%27");
                        do_place_name.insert(0, "<");
                        do_place_name.push_back('>');

                        replace_url(do_place_name, " ", "%20");
                        replace_url(subject, " ", "%20");

                        create_statement(subject, predicate, do_place_name);

                        predicate = '<' + graph + "/ontology/property/locatedAt>";
                        create_statement(do_place_name, predicate, subject);
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

                    create_statement(do_place_name, predicate, value);

                }

                ++page_text_itr;

            }
        }
    }

    static bool find_do(page_iterator_t &itr) {
        std::vector<page_iterator_t> tags;
        std::vector<std::string> patterns{"{{do", "{{do", "type = do", "type=do"};
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

#endif //DBVOYAGE_DO_SECTION_EXTRACTOR_HPP
