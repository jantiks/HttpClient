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
enum class HTTPMethod { GET, POST };

class HttpClient {
public:
    static void Request(std::string& url, HTTPMethod requestMethod);
};
#endif /* HttpClient_hpp */
