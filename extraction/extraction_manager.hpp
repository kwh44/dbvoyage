//
// Created by kwh44 on 11/28/19.
//

#ifndef DBVOYAGE_EXTRACTION_MANAGER_HPP
#define DBVOYAGE_EXTRACTION_MANAGER_HPP

#include <thread>
#include <memory>
#include <vector>
#include "article_link_extractor.hpp"
#include "title_extractor.hpp"
#include "abstract_article_extractor.hpp"
#include "see_section_extractor.hpp"
#include "regions_section_extractor.hpp"
#include "cities_section_extractor.hpp"
#include "../utils/transitive_closure.hpp"

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

    void do_transitive_closure() {
        std::cout << "Started transitive closure\n";
        std::vector<std::thread> threads;
        std::vector<Triple> c1;
        // regions and attractions
        threads.emplace_back(
                [&] { transitive_closure(extractors[4]->get_triples(), extractors[3]->get_triples(), c1); });
        std::vector<Triple> c2;
        // cities and attractions
        threads.emplace_back(
                [&] { transitive_closure(extractors[5]->get_triples(), extractors[3]->get_triples(), c2); });
        std::vector<Triple> c3;
        // regions, cities and attractions
        threads.emplace_back([&] {
            transitive_closure(extractors[4]->get_triples(), extractors[5]->get_triples(), extractors[3]->get_triples(),
                               c3);
        });
        for (auto &v: threads) v.join();
        for (auto &v: c1) extractors[4]->get_triples().emplace_back(v);
        for (auto &v: c2) extractors[4]->get_triples().emplace_back(v);
        for (auto &v: c3) extractors[4]->get_triples().emplace_back(v);

        std::cout << "Finished transitive closure\n";
    }

    void serialize() {
        std::vector<std::thread> threads;
        for (auto &extractor :extractors) threads.emplace_back(&Extractor::write_to_destination, extractor.get());
        for (auto &v: threads) v.join();
    }

};

#endif //DBVOYAGE_EXTRACTION_MANAGER_HPP
