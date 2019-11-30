//
// Created by kwh44 on 11/29/19.
//

#ifndef DBVOYAGE_CITIES_SECTION_EXTRACTOR_HPP
#define DBVOYAGE_CITIES_SECTION_EXTRACTOR_HPP

#include <memory>
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
            for (const auto &city_name: *cities_list) {
                std::string subject("<https://dbvoyage.org/ontology/article/" + page_title + ">");
                std::string predicate("<https://dbvoyage.org/ontology/property/hasCity>");
                std::string object("<https://dbvoyage.org/ontology/article/" + city_name + '>');
                create_statement(subject, predicate, object);
                ++page_text_itr;
            }
        }
    }

private:
    static cities_list get_cities_list(page_iterator_t &itr) {
        bool flag = start_find(itr, "==Cities==");
        if (flag == 0) return nullptr;
        size_t end = 0;
        while (*(itr + end) != '\n' || *(itr + 1 + end) != '\n') ++end;
        std::string cities(itr, end);
        auto list = std::make_shared<std::vector<std::string>>();
        std::vector<std::string> city_name_keys{"name=", "name ="};
        for (const auto &key: city_name_keys) {
            for (size_t i = cities.find(key); i != std::string::npos; i = cities.find(key, i + 1)) {
                auto city_name = cities.substr(i + key.size(), cities.find('|', i) - i - key.size());
                auto link = city_name.find('[');
                if (link != std::string::npos) city_name.erase(0, 2);
                link = city_name.find(']');
                if (link != std::string::npos) city_name.erase(city_name.size() - 2, 2);
                list->emplace_back(city_name);
            }
        }
        return list;
    }
};

#endif //DBVOYAGE_CITIES_SECTION_EXTRACTOR_HPP
