#include <trlang/Curl.hpp>

using namespace trl;

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

Curl::Curl():
        _curlContext(curl_easy_init())
{
    curl_easy_setopt(_curlContext, CURLOPT_WRITEFUNCTION, writeFunction);
}

Curl::~Curl()
{
    curl_easy_cleanup(_curlContext);
}

std::variant<int, std::string> Curl::get(const std::string& url) const
{
    if (_curlContext)
    {
        curl_easy_setopt(_curlContext, CURLOPT_URL, url.c_str());

        std::string response_string;
        std::string header_string;
        curl_easy_setopt(_curlContext, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(_curlContext, CURLOPT_HEADERDATA, &header_string);

        int returnCode = curl_easy_perform(_curlContext);

        if (returnCode == 0)
        {
            return response_string;
        }
        else
        {
            return returnCode;
        }
    }

    return 418;
}