//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_ARTICLE_LINK_EXTRACTOR_HPP
#define DBVOYAGE_ARTICLE_LINK_EXTRACTOR_HPP

#include "extractor_base.hpp"

class ArticleLinkExtractor : public Extractor {
public:

    explicit ArticleLinkExtractor(PageNode *pn) {
        articles = pn;
        filename = "wikivoyage_links_en.nt";
    }

    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            if (PageNode::na_article(it)) continue;
            std::string page_title(PageNode::get_page_title(it));
            std::string subject("<https://dbvoyage.org/ontology/article/" + page_title + ">");
            std::string predicate("<http://xmlns.com/foaf/0.1/page>");
            std::string object("<https://wikivoyage.org/wiki/" + page_title + ">");
            create_statement(subject, predicate, object);
        }
    }

};


#endif //DBVOYAGE_ARTICLE_LINK_EXTRACTOR_HPP
