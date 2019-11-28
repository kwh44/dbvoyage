//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_ARTICLE_LINK_EXTRACTOR_HPP
#define DBVOYAGE_ARTICLE_LINK_EXTRACTOR_HPP

#include "extractor_base.hpp"

class ArticleLinkExtractor : public Extractor {

public:

    explicit ArticleLinkExtractor(PageNode *pn) { articles = pn; }

    // extracts page_title from dump and creates statements with http://xmlns.com/foaf/0.1/page predicate
    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            // subject is <https://dbvoyage.org/ontology/article/{PageNode::get_page_title(it)}
            // predicate is <http://xmlns.com/foaf/0.1/page>
            // object is <https://wikivoyage.org/wiki/{PageNode::get_page_title(it)}
            std::string page_title(PageNode::get_page_title(it));

            std::string subject("<https://dbvoyage.org/ontology/article/" + page_title + ">");
            std::string predicate("<http://xmlns.com/foaf/0.1/page>");
            std::string object("<https://wikivoyage.org/wiki/" + page_title + ">");

            create_statement(subject, predicate, object);
        }
    }

    void write_to_destination() override {
        // filename to write statements
        std::string filename("wikivoyage_links_en.nt");
        // open output file stream
        std::ofstream destination(filename);
        // write all statement to it
        for (const auto &statement: statements) { destination << statement; }
    }

};


#endif //DBVOYAGE_ARTICLE_LINK_EXTRACTOR_HPP
