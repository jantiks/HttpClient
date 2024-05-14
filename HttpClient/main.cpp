//
//  main.cpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#include <iostream>
#include "HttpClient.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    const Response response = HttpClient::Request("example.com", {}, HTTPMethod::GET);
    std::cout << response.statusCode() << std::endl;
    std::cout << response.headers() << std::endl;
    return 0;
}
