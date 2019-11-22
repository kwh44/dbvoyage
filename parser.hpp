//
// Created by kwh44 on 11/22/19.
//

#ifndef DBVOYAGE_PARSER_H
#define DBVOYAGE_PARSER_H

#include <string>
#include "pugixml.hpp"

class PageNode {

public:
    pugi::xml_document doc;
    bool parse_status;

    explicit PageNode(const std::string &filename) : parse_status(doc.load_file(filename.c_str())) {}

    auto begin() { return doc.begin()->child("page"); }

    static auto end() { return pugi::xml_node(); }

    static auto get_page_title(pugi::xml_node &it) { return it.child_value("title"); }

    static auto get_text(pugi::xml_node &it) { return it.child("revision").child_value("text"); }
};

void operator++(pugi::xml_node &value) { value = value.next_sibling("page"); }

#endif //DBVOYAGE_PARSER_H
