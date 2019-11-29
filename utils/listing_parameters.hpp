//
// Created by kwh44 on 11/29/19.
//

#ifndef DBVOYAGE_LISTING_PARAMETERS_HPP
#define DBVOYAGE_LISTING_PARAMETERS_HPP

#include <string>
#include "../dump_parser/parser.hpp"

namespace listing {
    std::vector<std::string> keys{"name", "alt", "address", "directions", "phone",
                                  "tollfree", "email", "fax", "url", "hours", "checkin", "checkout",
                                  "wikidata", "wikipedia", "image", "price", "lat", "long", "content"};
}

std::string get_parameter_value(page_iterator_t &itr, const size_t &size, const std::string &key) {
    std::string see_section(itr, size);
    auto pos = see_section.find(key);
    if (pos == std::string::npos) return std::string();
    // extract value of key and return it
    auto end_value_pos = see_section.find('|', pos);
    pos += 1 + key.size();
    auto value = see_section.substr(pos, end_value_pos - pos);
    if (value == "\n" || value == " ") return std::string();
    if (value.back() == '\n') value.erase(value.size() - 1);
    return value;
}

#endif //DBVOYAGE_LISTING_PARAMETERS_HPP
