cmake_minimum_required(VERSION 3.0)

project(dbvoyage CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Release)

find_package(pugixml REQUIRED)

find_package(Threads REQUIRED)

set(extractors extraction/article_link_extractor.hpp
        extraction/title_extractor.hpp
        extraction/abstract_article_extractor.hpp
        extraction/see_section_extractor.hpp)


add_executable(main
        main.cpp
        dump_parser/parser.hpp
        utils/triple.hpp
        utils/listing_parameters.hpp
        extraction/extractor_base.hpp
        ${extractors}
        extraction/extraction_manager.hpp)

target_link_libraries(main pugixml Threads::Threads)
