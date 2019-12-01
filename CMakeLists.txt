cmake_minimum_required(VERSION 3.0)

project(dbvoyage CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)

find_package(pugixml REQUIRED)

find_package(Threads REQUIRED)

set(parsing dump_parser/parser.hpp)

set(extraction
        extraction/extractor_base.hpp
        extraction/extraction_manager.hpp
        extraction/article_link_extractor.hpp
        extraction/title_extractor.hpp
        extraction/abstract_article_extractor.hpp
        extraction/see_section_extractor.hpp
        extraction/regions_section_extractor.hpp
        extraction/cities_section_extractor.hpp
        extraction/wiki_link_extractor.hpp)

set(utils utils/triple.hpp
        utils/listing_parameters.hpp
        utils/transitive_closure.hpp
        utils/url_format.hpp
        utils/clean_object.hpp)

add_executable(main
        main.cpp
        ${parsing}
        ${utils}
        ${extraction})

target_link_libraries(main pugixml Threads::Threads)
