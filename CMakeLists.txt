cmake_minimum_required(VERSION 3.0)

project(dbvoyage CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Release)

find_package(pugixml REQUIRED)

add_executable(main main.cpp dump_parser/parser.hpp extractors/extractor_base.hpp extractors/see_section_extractor.hpp
        utils/triple.hpp extractors/abstract_article_extractor.hpp extractors/page_id_extractor.hpp
        extractors/page_revision_extractor.hpp extractors/label_extractor.hpp extractors/page_link_extractor.hpp)

target_link_libraries(main pugixml)
