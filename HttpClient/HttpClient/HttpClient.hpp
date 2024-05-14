//
//  HttpClient.hpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#ifndef HttpClient_hpp
#define HttpClient_hpp

#include <stdio.h>
#include "iostream"
#include "map"
#include "Response.hpp"
#include "BaseJsonResponseBody.hpp"

enum class HTTPMethod { GET, POST };

class HttpClient {
public:
    static Response Request(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod);
    static void Request(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod, BaseJsonResponseBody& responseBody);
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    static Response performRequest(const std::string& url, const std::vector<std::string>& headers, const char* postData = nullptr);
    static std::map<std::string, std::string> parseHeaders(const std::string& fromString);
};
#endif /* HttpClient_hpp */
