//
// Created by kwh44 on 11/29/19.
//

#ifndef DBVOYAGE_REGIONS_SECTION_EXTRACTOR_HPP
#define DBVOYAGE_REGIONS_SECTION_EXTRACTOR_HPP

#include <memory>
#include "../utils/listing_parameters.hpp"
#include "../dump_parser/parser.hpp"
#include "extractor_base.hpp"
#include <boost/algorithm/string/trim.hpp>

class RegionsSectionExtractor : public Extractor {
    using regions_list=std::shared_ptr<std::vector<std::string>>;
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
            while (start_find(page_text_itr, "{{Region")) {
                auto tag_size = find_regions_tag_size(page_text_itr);
                auto regions = get_region_names(std::string(page_text_itr, tag_size));
                for (auto &region: *regions) {
                    boost::algorithm::trim(region);
                    boost::algorithm::trim(page_title);
                    clean_url(region);
                    clean_url(page_title);
                    std::string subject('<' + graph + "/ontology/article/" + page_title + ">");
                    std::string predicate('<' + graph + "/ontology/property/hasRegion>");
                    std::string object('<' + graph + "/ontology/article/" + region + '>');
                    create_statement(subject, predicate, object);
                }
                ++page_text_itr;
            }
        }
    }

private:
    static size_t find_regions_tag_size(page_iterator_t itr) {
        size_t size = 0;
        while (*itr != '\0') {
            if (*itr == '}' && *(itr + 1) == '}' && *(itr + 2) == '\n' && *(itr + 3) == '\n') {
                break;
            }
            ++size;
            ++itr;
        }
        return size;
    }

    static regions_list get_region_names(std::string &&regions) {
        auto ptr = std::make_shared<std::vector<std::string>>();
        auto i = regions.find("name");
        auto j = regions.find("region", i - 9);
        while (i != std::string::npos && j != std::string::npos && i - j < 10) {
            auto region_name_start = regions.find("[[", i);
            auto region_name_end = regions.find("]]", i);
            auto region_name = regions.substr(region_name_start + 2, region_name_end - region_name_start - 2);
            auto pos = region_name.find('|');
            if (pos != std::string::npos) region_name.erase(pos, region_name.size() - pos);
            ptr->emplace_back(region_name);
            i = regions.find("name", i + 1);
            j = regions.find("region", i - 9);
        }
        return ptr;
    }

};

#endif //DBVOYAGE_REGIONS_SECTION_EXTRACTOR_HPP
