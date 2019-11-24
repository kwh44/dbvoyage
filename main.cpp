//
// Created by kwh44 on 11/22/19.
//
#include <iostream>
#include "dump_parser/parser.hpp"

int main(int argv, char *argc[]) {
    std::string filename("../dumps/enwikivoyage-latest-pages-articles.xml");
    PageNode page_node(filename);
    std::string target_city("Lviv");
    for (auto it = page_node.begin(); it != PageNode::end(); ++it) {
        if (PageNode::get_page_title(it) == target_city) {
            std::cout << PageNode::get_text(it) << std::endl;
            break;
        }
    }
    return 0;
}