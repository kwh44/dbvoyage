//
// Created by kwh44 on 11/30/19.
//

#ifndef DBVOYAGE_URL_FORMAT_HPP
#define DBVOYAGE_URL_FORMAT_HPP


void replace_url(std::string &source, std::string from, std::string to) {
    auto pos = source.find(from);
    while (pos != std::string::npos) {
        source.erase(pos, 1);
        source.insert(pos, to);
        pos = source.find(from);
    }
}


void clean_url(std::string & value) {
    replace_url(value, " ", "%20");
    replace_url(value, "\\", "/");
    replace_url(value, "<", "%3C");
    replace_url(value, ">", "%3E");
}

#endif //DBVOYAGE_URL_FORMAT_HPP
