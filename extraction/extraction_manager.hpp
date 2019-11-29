//
// Created by kwh44 on 11/28/19.
//

#ifndef DBVOYAGE_EXTRACTION_MANAGER_HPP
#define DBVOYAGE_EXTRACTION_MANAGER_HPP

#include <thread>
#include <memory>
#include "article_link_extractor.hpp"
#include "title_extractor.hpp"
#include "abstract_article_extractor.hpp"
#include "see_section_extractor.hpp"
#include "regions_section_extractor.hpp"
#include "cities_section_extractor.hpp"

class ExtractionManager {
    std::vector<std::shared_ptr<Extractor>> extractors;
public:

    explicit ExtractionManager(PageNode *page_node) {
        extractors.emplace_back(std::make_shared<ArticleLinkExtractor>(page_node));
        extractors.emplace_back(std::make_shared<TitleExtractor>(page_node));
        extractors.emplace_back(std::make_shared<AbstractPageExtractor>(page_node));
        extractors.emplace_back(std::make_shared<SeeSectionExtractor>(page_node));
        extractors.emplace_back(std::make_shared<RegionsSectionExtractor>(page_node));
        extractors.emplace_back(std::make_shared<CitiesSectionExtractor>(page_node));
    }

    void start() {
        std::vector<std::thread> threads;
        for (auto &extractor :extractors) threads.emplace_back(&Extractor::extract, extractor.get());
        for (auto &v: threads) v.join();
    }

    void serialize() {
        std::vector<std::thread> threads;
        for (auto &extractor :extractors) threads.emplace_back(&Extractor::write_to_destination, extractor.get());
        for (auto &v: threads) v.join();
    }

};

#endif //DBVOYAGE_EXTRACTION_MANAGER_HPP
