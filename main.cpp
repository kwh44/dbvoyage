//
// Created by kwh44 on 11/22/19.
//

#include <iostream>
#include "dump_parser/parser.hpp"
#include "extraction/extraction_manager.hpp"

int main(int argv, char *argc[]) {
    std::string filename("../dumps/enwikivoyage-latest-pages-articles.xml");
    PageNode page_node(filename);
    PageNode * page_node_ptr = &page_node;
    ExtractionManager extraction(page_node_ptr);
    extraction.start();
    extraction.serialize();
    return 0;
}