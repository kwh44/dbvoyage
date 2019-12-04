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
#include "do_section_extractor.hpp"
#include "../utils/transitive_closure.hpp"

class ExtractionManager {
    std::vector<std::shared_ptr<Extractor>> extractors;
public:

    explicit ExtractionManager(PageNode *page_node) {
        extractors.emplace_back(std::make_shared<ArticleLinkExtractor>(page_node));  // virtuoso accepted
        extractors.emplace_back(std::make_shared<TitleExtractor>(page_node));         // virtuoso accepted
        extractors.emplace_back(std::make_shared<AbstractPageExtractor>(page_node));  // virtuoso accepted
        extractors.emplace_back(std::make_shared<SeeSectionExtractor>(page_node));   // virtuoso accepted
        extractors.emplace_back(std::make_shared<RegionsSectionExtractor>(page_node));   // virtuoso accepted
        extractors.emplace_back(std::make_shared<CitiesSectionExtractor>(page_node));       // virtuoso accepted
        extractors.emplace_back(std::make_shared<DoSectionExtractor>(page_node));
    }

    void start() {
        std::vector<std::thread> threads;
        for (auto &extractor :extractors) threads.emplace_back(&Extractor::extract, extractor.get());
        for (auto &v: threads) v.join();
        std::cout << "[ DONE ] extraction" << std::endl;
    }

    void do_transitive_closure() {
        std::set<Triple> c1;

        // CityExtractor and SeeSection
        transitive_closure(extractors[5]->cget_triples(), extractors[3]->cget_triples(), c1);
        for (auto &v: c1) extractors[5]->get_triples().emplace(v);
        c1.clear();

        // RegionsExtractor and CityExtractor
        transitive_closure(extractors[4]->cget_triples(), extractors[5]->cget_triples(), c1);
        for (auto &v: c1) extractors[4]->get_triples().emplace(v);

        // several rounds of RegionsExtractor and RegionExtractor
        c1.clear();

        for (int i = 0; i < 10; ++i) {
            std::cout << "Transitive closure round " << i << std::endl;
            transitive_closure(extractors[4]->cget_triples(), extractors[4]->cget_triples(), c1);
            for (auto &v: c1) extractors[4]->get_triples().emplace(v);
            c1.clear();
        }

        std::cout << "[ DONE ] transitive closure" << std::endl;
    }

    void serialize() {
        std::vector<std::thread> threads;
        for (auto &extractor :extractors) threads.emplace_back(&Extractor::write_to_destination, extractor.get());
        for (auto &v: threads) v.join();
        std::cout << "[ DONE ] serialization" << std::endl;
    }

};

#endif //DBVOYAGE_EXTRACTION_MANAGER_HPP
