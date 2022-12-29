//
// Created by lenovo on 12/29/2022.
//

#include <string>
#include <regex>
#include "ClientInputCheck.h"

bool isValidPort(std::string port) {
    for (int i = 0; i < port.size(); ++i) {
        if (!isdigit(port[i])) {
            return false;
        }
    }
    if (std::stoi(port) < 0 || std::stoi(port) > 65535) {
        return false;
    }
    return true;
}

bool isValidIP(std::string ip) {
    std::regex pattern("(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])");
    return std::regex_match(ip, pattern);
}

bool inputCheck(int argc, char **argv) {
    if (argc != 3) {
        return false;
    } else if (!isValidPort(argv[2])) {
        return false;
    } else if (!isValidIP(argv[1])) {
        return false;
    } else {
        return true;
    }
}
