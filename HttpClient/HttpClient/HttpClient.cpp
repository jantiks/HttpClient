//
//  HttpClient.cpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#include "HttpClient.hpp"
#include "Response.hpp"
#include <curl/curl.h>
#include <sstream>


Response HttpClient::Request(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod) {
    return performRequest(url, headers, requestMethod);
}

void HttpClient::Request(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod, BaseJsonResponseBody& responseBody) {
    Response response = performRequest(url, headers, requestMethod);
    responseBody.decode(response.getJsonResponse());
}

Response HttpClient::performRequest(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod, const char* postData) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string responseHeader;
    long statusCode;
    struct curl_slist* curlHeaders = NULL;

    curl = curl_easy_init();
    if(curl) {
        for(const auto& header : headers) {
            curlHeaders = curl_slist_append(curlHeaders, header.c_str());
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &responseHeader);

        switch(requestMethod) {
            case HTTPMethod::GET:
                break;
            case HTTPMethod::POST:
                if (postData) {
                    curl_easy_setopt(curl, CURLOPT_POST, 1L);
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
                }
                break;
            case HTTPMethod::PUT:
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
                if (postData) {
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
                }
                break;
            case HTTPMethod::DELETE:
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
                break;
        }

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            // cleaning before throwing the error.
            curl_slist_free_all(curlHeaders);
            curl_easy_cleanup(curl);
            throw std::runtime_error("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
        } else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
        }

        curl_slist_free_all(curlHeaders);
        curl_easy_cleanup(curl);
    }

    return Response(statusCode, parseHeaders(responseHeader), readBuffer);
}

size_t HttpClient::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::map<std::string, std::string> HttpClient::parseHeaders(const std::string& fromString) {
    std::map<std::string, std::string> headers;
    std::istringstream stream(fromString);
    std::string line;

    while (std::getline(stream, line)) {
        size_t colonPosition = line.find(":");
        if (colonPosition != std::string::npos) {
            std::string key = line.substr(0, colonPosition);
            std::string value = line.substr(colonPosition + 2); // skipping ": "
            value.erase(value.find_last_not_of("\r\n") + 1); // removing newlines
            headers[key] = value;
        }
    }

    return headers;
}
