//
// Created by kwh44 on 11/28/19.
//

#ifndef DBVOYAGE_EXTRACTION_MANAGER_HPP
#define DBVOYAGE_EXTRACTION_MANAGER_HPP

#include <thread>
#include <memory>
#include "article_link_extractor.hpp"
#include "title_extractor.hpp"

class ExtractionManager {
    // input:
    //          PageNode
    // work:
    //      instantiates all extraction and calls extract method on each in separate thread
    // return:
    //      status indication the success or failure of extraction process

    std::vector<std::shared_ptr<Extractor>> extractors;

public:

    ExtractionManager(PageNode *page_node) {
        extractors.emplace_back(std::make_shared<ArticleLinkExtractor>(page_node));
        extractors.emplace_back(std::make_shared<TitleExtractor>(page_node));
    }

    void start() {
        std::vector<std::thread> threads;
        for (size_t i = 0; i < extractors.size(); ++i) {
            threads.emplace_back(&Extractor::extract, extractors[i].get());
        }
        for (auto &v: threads) v.join();
    }

    void serialize() {
        std::vector<std::thread> threads;
        for (size_t i = 0; i < extractors.size(); ++i) {
            threads.emplace_back(&Extractor::write_to_destination, extractors[i].get());
        }
        for (auto &v: threads) v.join();
    }

};

#endif //DBVOYAGE_EXTRACTION_MANAGER_HPP
