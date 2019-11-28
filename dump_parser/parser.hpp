//
// Created by kwh44 on 11/22/19.
//

#ifndef DBVOYAGE_PARSER_H
#define DBVOYAGE_PARSER_H

#include <string>
#include "pugixml.hpp"


using page_iterator_t=const char *;

class PageNode {
public:
    pugi::xml_document doc;
    bool parse_status;

    explicit PageNode(const std::string &filename) : parse_status(doc.load_file(filename.c_str())) {}

    auto begin() { return doc.begin()->child("page"); }

    static auto end() { return pugi::xml_node(); }

    static page_iterator_t get_page_title(pugi::xml_node &it) { return it.child_value("title"); }

    static page_iterator_t get_text(pugi::xml_node &it) { return it.child("revision").child_value("text"); }

    static bool redirect_article(pugi::xml_node &it) { return std::string(PageNode::get_text(it), 9) == "#REDIRECT"; }

    static bool na_article(pugi::xml_node &it) {
        // method to determine non-travel-guide articles
        auto title = std::string(PageNode::get_page_title(it), 11);
        return title == "Wikivoyage:" || title.substr(0, 10) == "MediaWiki:" || title.substr(0, 9) == "Template:"
               || title.substr(0, 5) == "File:" || title.substr(0, 9) == "Main Page" || title.substr(0, 7) == "Module:";

    }

};

void operator++(pugi::xml_node &value) { value = value.next_sibling("page"); }

#endif //DBVOYAGE_PARSER_H
