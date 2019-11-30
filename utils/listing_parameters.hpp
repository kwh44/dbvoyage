//
// Created by kwh44 on 11/29/19.
//

#ifndef DBVOYAGE_LISTING_PARAMETERS_HPP
#define DBVOYAGE_LISTING_PARAMETERS_HPP

#include <string>
#include "../dump_parser/parser.hpp"

namespace listing {
    std::vector<std::string> keys{"name"};/*, "alt"};/*, "address", "directions", "phone"};/*,
                                  "tollfree", "email", "fax", "url", "hours", "checkin", "checkout",
                                  "wikidata", "wikipedia", "image", "price", "lat", "long", "content"};*/
}

std::string get_parameter_value(page_iterator_t &itr, const size_t &size, const std::string &key) {
    std::string see_section(itr, size);

    auto pos = see_section.find(key + "=");

    if (pos == std::string::npos) return std::string();
    // extract value of key and return it
    auto end_value_pos = see_section.find('|', pos);
    if (end_value_pos == std::string::npos && key=="content") {
        end_value_pos = see_section.size() - 1;
    }
    pos += 1 + key.size();
    auto value = see_section.substr(pos, end_value_pos - pos);
    if (value == "\n" || value == " ") return std::string();
    if (value.back() == '\n') value.erase(value.size() - 1);
    if (value[0] == '=') value.erase(0, 1);
    while (value[0] == ' ') value.erase(0, 1);
    if (value[0] == '=') value.erase(0, 1);
    pos = value.find('\\');
    while (pos != std::string::npos) {
        value.insert(pos, "\\");
        pos = value.find('\\', pos + 2);
    }

    return value;
}


[[nodiscard]] static bool start_find(page_iterator_t &itr, std::string target) {
    // move itr to end of target string and return true
    size_t i = 0;
    while (*itr != '\0') {
        if (*itr == target[i]) ++i;
        else i = 0;
        if (i == target.size()) { return true; }
        ++itr;
    }
    return false;
}

#endif //DBVOYAGE_LISTING_PARAMETERS_HPP
