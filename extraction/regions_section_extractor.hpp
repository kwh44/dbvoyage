//
// Created by kwh44 on 11/29/19.
//

#ifndef DBVOYAGE_REGIONS_SECTION_EXTRACTOR_HPP
#define DBVOYAGE_REGIONS_SECTION_EXTRACTOR_HPP

#include <memory>
#include "../dump_parser/parser.hpp"
#include "extractor_base.hpp"

class RegionsSectionExtractor : public Extractor {
public:
    explicit RegionsSectionExtractor(PageNode *pn) {
        articles = pn;
        filename = "regions_section.nt";
    }

    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            if (PageNode::na_article(it)) continue;
            if (PageNode::redirect_article(it)) continue;
            std::string page_title(PageNode::get_page_title(it));
            auto page_text_itr = PageNode::get_text(it);
            while (regions_tag_start_find(page_text_itr)) {
                auto tag_size = find_regions_tag_size(page_text_itr);
                auto regions = get_region_names(std::string(page_text_itr, tag_size));
                for (const auto &region: *regions) {
                    std::string subject("<https://dbvoyage.org/ontology/article/" + page_title + ">");
                    std::string predicate("<https://dbvoyage.org/ontology/property/hasRegion>");
                    std::string object("<https://dbvoyage.org/ontology/region/" + region + '>');
                    create_statement(subject, predicate, object);
                }
                ++page_text_itr;
            }
        }
    }

    static bool regions_tag_start_find(page_iterator_t &itr) {
        // move itr to start of string "{{Regionlist"
        while (*itr != '\0') {
            if (*itr == '{' && *(itr + 1) == '{' && *(itr + 2) == 'R'
                && *(itr + 3) == 'e' && *(itr + 4) == 'g' && *(itr + 5) == 'i'
                && *(itr + 6) == 'o' && *(itr + 7) == 'n') {
                return true;
            }
            ++itr;
        }
        return false;
    }

    static size_t find_regions_tag_size(page_iterator_t itr) {
        size_t size = 0;
        while (*itr != '\0') {
            if (*itr == '\n' && *(itr + 1) == '}' && *(itr + 2) == '}') {
                size += 3;
                break;
            }
            ++size;
            ++itr;
        }
        return size;
    }

    static std::shared_ptr<std::vector<std::string>> get_region_names(std::string &&regions) {
        auto ptr = std::make_shared<std::vector<std::string>>();
        size_t i = regions.find("name");
        for (; i != std::string::npos; i = regions.find("name", i + 1)) {
            auto region_name_start = regions.find("[[", i);
            auto region_name_end = regions.find("]]", i);
            auto region_name = regions.substr(region_name_start + 2, region_name_end - region_name_start - 2);
            auto pos = region_name.find('|');
            if (pos != std::string::npos) {
                region_name.erase(pos, region_name.size() - pos);
            }
            ptr->emplace_back(region_name);
        }
        return ptr;
    }

};

#endif //DBVOYAGE_REGIONS_SECTION_EXTRACTOR_HPP
