//
// Created by kwh44 on 11/30/19.
//

#ifndef DBVOYAGE_CLEAN_OBJECT_HPP
#define DBVOYAGE_CLEAN_OBJECT_HPP

#include <string>
#include <algorithm>

void clean_object(std::string &object) {
    std::replace(object.begin(), object.end(), '\n', ' ');
    std::replace(object.begin(), object.end(), '"', '\'');
    object[0] = '"';
    object[object.size() - 1] = '"';
}

#endif //DBVOYAGE_CLEAN_OBJECT_HPP
