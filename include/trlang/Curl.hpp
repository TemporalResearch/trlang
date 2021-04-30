//
// Created by lynchm on 30/04/2021.
//

#ifndef ETHERTREE_CURL_HPP
#define ETHERTREE_CURL_HPP

#include <curl/curl.h>
#include <variant>
#include <string>

namespace trl
{
    class Curl
    {
    private:
        CURL* _curlContext;
    public:
        Curl();
        ~Curl();

        [[nodiscard]] std::variant<int, std::string> get(const std::string& url) const;
    };
}

#endif //ETHERTREE_CURL_HPP
