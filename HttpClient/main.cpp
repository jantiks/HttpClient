//
//  main.cpp
//  HttpClient
//
//  Created by Tigran on 14.05.24.
//

#include <iostream>
#include "HttpClient.hpp"

void testGetRequest() {
    std::vector<std::string> headers = { "Content-Type: application/json" };
    std::string url = "https://jsonplaceholder.typicode.com/posts/1";

    try {
        Response response = HttpClient::Request(url, headers, HTTPMethod::GET);
        std::cout << "GET Response: \n" << response.getJsonResponse() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "GET request failed: " << e.what() << std::endl;
    }
}

void testPostRequest() {
    std::vector<std::string> headers = { "Content-Type: application/json" };
    std::string url = "https://jsonplaceholder.typicode.com/posts";
    std::string requestBody = R"({"title": "foo", "body": "bar", "userId": 1})";

    try {
        Response response = HttpClient::Request(url, headers, HTTPMethod::POST, requestBody);
        std::cout << "POST Response: \n" << response.getJsonResponse() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "POST request failed: " << e.what() << std::endl;
    }
}

void testPutRequest() {
    std::vector<std::string> headers = { "Content-Type: application/json" };
    std::string url = "https://jsonplaceholder.typicode.com/posts/1";
    std::string requestBody = R"({"id": 1, "title": "foo", "body": "bar", "userId": 1})";

    try {
        Response response = HttpClient::Request(url, headers, HTTPMethod::PUT, requestBody);
        std::cout << "PUT Response: \n" << response.getJsonResponse() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "PUT request failed: " << e.what() << std::endl;
    }
}

void testDeleteRequest() {
    std::vector<std::string> headers = { "Content-Type: application/json" };
    std::string url = "https://jsonplaceholder.typicode.com/posts/1";

    try {
        Response response = HttpClient::Request(url, headers, HTTPMethod::DELETE);
        std::cout << "DELETE Response: \n" << response.getJsonResponse() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "DELETE request failed: " << e.what() << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    testGetRequest();
    testPostRequest();
    testPutRequest();
    testDeleteRequest();
    
    return 0;
}
