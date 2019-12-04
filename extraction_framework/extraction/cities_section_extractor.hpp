//
// Created by kwh44 on 11/29/19.
//

#ifndef DBVOYAGE_CITIES_SECTION_EXTRACTOR_HPP
#define DBVOYAGE_CITIES_SECTION_EXTRACTOR_HPP

#include <memory>
#include <boost/algorithm/string/trim.hpp>
#include "../utils/listing_parameters.hpp"
#include "../dump_parser/parser.hpp"
#include "extractor_base.hpp"

class CitiesSectionExtractor : public Extractor {

    using cities_list=std::shared_ptr<std::vector<std::string>>;
public:
    explicit CitiesSectionExtractor(PageNode *pn) {
        articles = pn;
        filename = "cities_section.nt";
    }

    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            if (PageNode::na_article(it)) continue;
            if (PageNode::redirect_article(it)) continue;
            std::string page_title(PageNode::get_page_title(it));
            auto page_text_itr = PageNode::get_text(it);
            auto cities_list = get_cities_list(page_text_itr);
            if (cities_list == nullptr) continue;
            for (auto &city_name: *cities_list) {
                boost::algorithm::trim(page_title);
                boost::algorithm::trim(city_name);
                clean_url(page_title);
                clean_url(city_name);
                std::string subject("<https://dbvoyage.org/ontology/article/" + page_title + ">");
                std::string predicate("<https://dbvoyage.org/ontology/property/hasCity>");
                std::string object("<https://dbvoyage.org/ontology/article/" + city_name + '>');
                create_statement(subject, predicate, object);
            }
        }
    }

private:
    static cities_list get_cities_list(page_iterator_t &itr) {
        auto list = std::make_shared<std::vector<std::string>>();

        bool flag = start_find(itr, "type=city");

        while (flag) {

            while (*itr != '[') ++itr;

            auto end = itr;
            while (*end != ']') ++end;

            std::string city_name(itr+2, end);

            list->emplace_back(city_name);

            ++itr;
            flag = start_find(itr, "type=city");
        }
        return list;
    }
};

#endif //DBVOYAGE_CITIES_SECTION_EXTRACTOR_HPP
