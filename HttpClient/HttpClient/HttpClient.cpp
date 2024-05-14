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

/**
 * @brief Sends an HTTP request and returns the response.
 *
 * @param url URL to send the request to.
 * @param headers Headers for the request
 * @param requestMethod (GET, POST, PUT, DELETE).
 * @param requestBody
 * @return Response The response from the server.
 */
Response HttpClient::Request(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod, const std::string& requestBody) {
    return performRequest(url, headers, requestMethod, requestBody.c_str());
}

/**
 * @brief Sends an HTTP request and decodes the JSON response into a  BaseJsonResponseBody object.
 *
 * @param url URL to send the request to.
 * @param headers Headers for the request
 * @param requestMethod (GET, POST, PUT, DELETE).
 * @param responseBody The object to decode the JSON response into.
 * @param requestBody The body of the request (used for POST and PUT).
 */
void HttpClient::Request(const std::string& url, const std::vector<std::string>& headers, HTTPMethod requestMethod, BaseJsonResponseBody& responseBody, const std::string& requestBody) {
    Response response = performRequest(url, headers, requestMethod, requestBody.c_str());
    responseBody.setHeaders(response.headers());
    responseBody.setStatusCode(response.statusCode());
    responseBody.decode(response.getJsonResponse());
}

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

/**
 * @brief Callback function for libcurl to write data.
 *
 * @param contents The pointer to the delivered data
 * @param size size of the data member
 * @param nmemb The number of data members
 * @param userp pointer to store the result
 * @return size_t the number of bytes written
 */
size_t HttpClient::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/**
 * @brief Parses HTTP headers from a string into a map.
 *
 * @param fromString The string containing the headers.
 * @return std::map<std::string, std::string> A map of header key-value pairs. 
 */
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
