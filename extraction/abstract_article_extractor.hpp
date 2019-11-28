//
// Created by kwh44 on 11/24/19.
//

#ifndef DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP
#define DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP


#include "extractor_base.hpp"

class AbstractPageExtractor : public Extractor {

public:
    // Extracts a short abstract (first paragraph, represented by using rdf-schema#comment)

    explicit AbstractPageExtractor(PageNode *pn) { articles = pn; }

    void extract() override {
        for (auto it = articles->begin(); it != PageNode::end(); ++it) {
            if (PageNode::redirect_article(it)) continue;
            if (PageNode::na_article(it)) continue;
            std::string page_title(PageNode::get_page_title(it));
            std::string subject("<https://dbvoyage.org/ontology/article/" + page_title + '>');
            std::string predicate(" <http://www.w3.org/2000/01/rdf-schema#comment>");
            std::string object('"' + get_abstract(PageNode::get_text(it)) + '"');
            clean_abstract(object);
            create_statement(subject, predicate, object);
        }
    }

    void write_to_destination() override {
        std::string filename("abstract_article_en.nt");
        std::ofstream destination(filename);
        for (const auto &statement: statements) { destination << statement; }
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
        if (abstract[abstract.size() - 2] == '\n') { abstract.erase(abstract.size() - 2, 1); }
    }
};

#endif //DBVOYAGE_ABSTRACT_ARTICLE_EXTRACTOR_HPP
