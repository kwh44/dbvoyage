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
        extractors.emplace_back(std::make_shared<ArticleLinkExtractor>(page_node));     // 0
        extractors.emplace_back(std::make_shared<TitleExtractor>(page_node));           // 1
        extractors.emplace_back(std::make_shared<AbstractPageExtractor>(page_node));    // 2
        extractors.emplace_back(std::make_shared<SeeSectionExtractor>(page_node));      // 3
        extractors.emplace_back(std::make_shared<RegionsSectionExtractor>(page_node));  // 4
        extractors.emplace_back(std::make_shared<CitiesSectionExtractor>(page_node));   // 5
        extractors.emplace_back(std::make_shared<DoSectionExtractor>(page_node));       // 6
    }

    void start() {
        std::vector<std::thread> threads;
        for (auto &extractor :extractors) threads.emplace_back(&Extractor::extract, extractor.get());
        for (auto &v: threads) v.join();
        std::cout << "[ DONE ] extraction" << std::endl;
    }

    void do_transitive_closure() {
        std::cout << "[ INFO ] started transitive closure" << std::endl;
        std::vector<std::thread> workers;

        std::set<Triple> c1;
        std::set<Triple> c2;

        auto regions_copy(extractors[4]->cget_triples());
        auto cities_copy(extractors[5]->cget_triples());

        // CityExtractor and SeeSection
        std::cout << "Cities & See section transitive closure" << std::endl;
        workers.emplace_back([&] {
            transitive_closure(extractors[5]->cget_triples(), extractors[3]->cget_triples(), c1);
            for (auto &v: c1) extractors[5]->get_triples().emplace(v);
            c1.clear();
        });

        // CityExtractor and DoSection
        std::cout << "Cities & Do section transitive closure" << std::endl;
        workers.emplace_back([&] {
            transitive_closure(extractors[5]->cget_triples(), extractors[6]->cget_triples(), c2);
            for (auto &v: c2) cities_copy.emplace(v);
            c2.clear();
        });

        for (auto &v: workers) v.join();
        workers.clear();

        // RegionsExtractor and CityExtractor&SeeExtractor
        std::cout << "Regions & See section transitive closure" << std::endl;
        workers.emplace_back([&] {
            transitive_closure(extractors[4]->cget_triples(), extractors[5]->cget_triples(), c1);
            for (auto &v: c1) extractors[4]->get_triples().emplace(v);
            c1.clear();
        });

        // RegionsExtractor and CityExtractor&DoExtractor
        std::cout << "Regions & Do section transitive closure" << std::endl;
        workers.emplace_back([&] {
            transitive_closure(extractors[4]->cget_triples(), cities_copy, c2);
            for (auto &v: c2) regions_copy.emplace(v);
            c2.clear();
        });

        for (auto &v: workers) v.join();
        workers.clear();

        workers.emplace_back([&] {
            for (int i = 0; i < 10; ++i) {
                transitive_closure(extractors[4]->cget_triples(), extractors[4]->cget_triples(), c1);
                for (auto &v: c1) extractors[4]->get_triples().emplace(v);
                c1.clear();
            }
        });

        workers.emplace_back([&] {
            for (int i = 0; i < 10; ++i) {
                transitive_closure(regions_copy, regions_copy, c2);
                for (auto &v: c2) regions_copy.emplace(v);
                c2.clear();
            }
        });

        for (auto &v: workers) v.join();
        workers.clear();

        workers.emplace_back([&] { for (auto &v: cities_copy) extractors[5]->get_triples().emplace(v); });
        workers.emplace_back([&] { for (auto &v: regions_copy) extractors[4]->get_triples().emplace(v); });

        for (auto &v: workers) v.join();
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
