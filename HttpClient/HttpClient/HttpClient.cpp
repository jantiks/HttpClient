//
//  HttpClient.cpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#include "HttpClient.hpp"
#include <curl/curl.h>


Response HttpClient::Request(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod)
{
    std::string& response = performRequest(url, headers);
    std::cout << response << std::endl;
    return Response(201, "headers", "someText");
}


std::string& HttpClient::performRequest(const std::string& url, const std::vector<std::string>& headers, const char* postData)
{
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

        if(postData) {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
        }

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
        }

        curl_slist_free_all(curlHeaders);
        curl_easy_cleanup(curl);
    }
    
    std::cout << "ASD STATUS CODE: " << statusCode << "ASD HEADER RESPONSE: " << responseHeader << std::endl;

    return readBuffer;
}

//size_t HttpClient::HeaderCallback(void* contents, size_t size, size_t nmemb, void* userp) {
//    ((std::string*)userp)->append((char*)contents, size * nmemb);
//    return size * nmemb;
//}

size_t HttpClient::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
