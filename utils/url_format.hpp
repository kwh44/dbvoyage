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

#endif //DBVOYAGE_URL_FORMAT_HPP
