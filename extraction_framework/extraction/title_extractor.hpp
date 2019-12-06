//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_TITLE_EXTRACTOR_HPP
#define DBVOYAGE_TITLE_EXTRACTOR_HPP

#include "extractor_base.hpp"
class TitleExtractor : public Extractor {

public:

    explicit TitleExtractor(PageNode *pn) {
        articles = pn;
        filename = "labels_en.nt";
    }

    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            if (PageNode::na_article(it)) continue;
            if (PageNode::redirect_article(it)) continue;
            std::string page_title(PageNode::get_page_title(it));
            std::string subject('<' + graph + "/ontology/article/" + page_title + ">");
            std::string predicate("<http://www.w3.org/2000/01/rdf-schema#label>");
            std::string object("\"" + page_title + "\"");
            replace_url(subject, " ", "%20");
            replace_url(predicate, " ", "%20");
            create_statement(subject, predicate, object);
        }
    }

};

#endif //DBVOYAGE_TITLE_EXTRACTOR_HPP
