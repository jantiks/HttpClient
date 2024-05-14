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
    const Response response = HttpClient::Request("https://jsonplaceholder.typicode.com/posts/1", {"Content-Type: application/json"}, HTTPMethod::GET);
    std::cout << response.getJsonResponse() << std::endl;
    return 0;
}
