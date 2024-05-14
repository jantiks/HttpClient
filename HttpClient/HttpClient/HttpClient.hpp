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

enum class HTTPMethod { GET, POST, PUT, DELETE };

class HttpClient {
public:
    /**
     * @brief Sends an HTTP request and returns the response.
     *
     * @param url URL to send the request to.
     * @param headers Headers for the request
     * @param requestMethod (GET, POST, PUT, DELETE).
     * @param requestBody
     * @return Response The response from the server.
     */
    static Response Request(const std::string& url,
                            const std::vector<std::string>& headers,
                            HTTPMethod requestMethod,
                            const std::string& requestBody = "");

    /**
     * @brief Sends an HTTP request and decodes the JSON response into a  BaseJsonResponseBody object.
     *
     * @param url URL to send the request to.
     * @param headers Headers for the request
     * @param requestMethod (GET, POST, PUT, DELETE).
     * @param responseBody The object to decode the JSON response into.
     * @param requestBody The body of the request (used for POST and PUT).
     */
    static void Request(const std::string& url,
                        const std::vector<std::string>& headers,
                        HTTPMethod requestMethod,
                        BaseJsonResponseBody& responseBody,
                        const std::string& requestBody = "");
private:

    /**
     * @brief Callback function for libcurl to write data.
     *
     * @param contents The pointer to the delivered data
     * @param size size of the data member
     * @param nmemb The number of data members
     * @param userp pointer to store the result
     * @return size_t the number of bytes written
     */
    static size_t WriteCallback(void* contents,
                                size_t size,
                                size_t nmemb,
                                void* userp);

    /**
     * @brief Performs the HTTP request using libcurl.
     *
     * @param url URL to send the request to.
     * @param headers Headers for the request
     * @param requestMethod (GET, POST, PUT, DELETE).
     * @param postData The body of the request (used for POST and PUT).
     * @return Response The response from the server.
     *
     * @throw std::runtime_error if the request fails.
     */
    static Response performRequest(const std::string& url,
                                   const std::vector<std::string>& headers,
                                   HTTPMethod requestMethod,
                                   const char* postData = nullptr);

    /**
     * @brief Parses HTTP headers from a string into a map.
     *
     * @param fromString The string containing the headers.
     * @return std::map<std::string, std::string> A map of header key-value pairs.
     */
    static std::map<std::string, std::string> parseHeaders(const std::string& fromString);
};
#endif /* HttpClient_hpp */
