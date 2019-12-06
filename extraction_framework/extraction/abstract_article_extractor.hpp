//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP
#define DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP


#include "extractor_base.hpp"

class AbstractPageExtractor : public Extractor {

public:
    // Extracts a short abstract (first paragraph, represented by using rdf-schema#comment)

    explicit AbstractPageExtractor(PageNode *pn) {
        articles = pn;
        filename = "abstract_article_en.nt";
    }

    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            if (PageNode::redirect_article(it)) continue;
            if (PageNode::na_article(it)) continue;
            std::string page_title(PageNode::get_page_title(it));
            std::string subject('<' + graph +"/ontology/article/" + page_title + '>');
            std::string predicate("<http://www.w3.org/2000/01/rdf-schema#comment>");
            std::string object('"' + get_abstract(PageNode::get_text(it)) + '"');
            if (object.size() == 2) continue;
            replace_url(subject, " ", "%20");
            replace_url(predicate, " ", "%20");
            clean_abstract(object);
            if (object.size() == 2) continue;
            create_statement(subject, predicate, object);
        }
    }

private:
    static std::string get_abstract(page_iterator_t start) {
        auto next = start;
        bool previous_newline = false;
        while (*next != '\0') {
            if (*next == '\n') {
                if (previous_newline) { break; }
                else { previous_newline = true; }
            } else { previous_newline = false; }
            ++next;
        }
        return std::string(start, next);
    }

    static void clean_abstract(std::string &abstract) {
        // this method can be further expanded to remove other types
        // of noise characters from article abstract
        auto p1 = abstract.find("{{");
        while (p1 != std::string::npos) {
            auto p2 = abstract.find("}}");
            abstract.erase(p1, p2 - p1 + 3);
            p1 = abstract.find("{{");
        }
        clean_object(abstract);
    }
};

#endif //DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP
