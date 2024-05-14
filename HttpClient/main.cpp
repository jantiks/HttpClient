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
    std::cout << "ASD STARTED" << std::endl;
    Response postResponse = HttpClient::Request("https://jsonplaceholder.typicode.com/posts", {"Content-Type: application/json"}, HTTPMethod::POST);
    std::cout << postResponse.getJsonResponse() << std::endl;
    std::cout << "ASD ENDED" << std::endl;
    return 0;
}
