#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <curl/curl.h>
#include <unistd.h>

// Function to write the response data to a string
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

// Function to write the headers data to a string
size_t HeaderCallback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    std::string *headers = (std::string *)userdata;
    headers->append(buffer, size * nitems);
    return size * nitems;
}

// Function to parse session ID from Set-Cookie header
std::string parseSessionIdFromHeaders(const std::string &headers)
{
    std::string sessionId;

    std::string::size_type pos = headers.find("Set-Cookie:");
    while (pos != std::string::npos)
    {
        pos += std::string("Set-Cookie: ").length();
        std::string::size_type endPos = headers.find("\r\n", pos);
        if (endPos == std::string::npos)
        {
            endPos = headers.length();
        }

        std::string cookieHeader = headers.substr(pos, endPos - pos);
        std::cout << "Extracted Cookie Header: " << cookieHeader << std::endl;

        std::string::size_type idPos = cookieHeader.find("id=");
        if (idPos != std::string::npos)
        {
            idPos += std::string("id=").length();
            std::string::size_type idEndPos = cookieHeader.find(';', idPos);
            if (idEndPos == std::string::npos)
            {
                idEndPos = cookieHeader.length();
            }
            sessionId = cookieHeader.substr(idPos, idEndPos - idPos);
            std::cout << "Session ID: " << sessionId << std::endl;
            break; // Assuming only one relevant cookie header
        }

        pos = headers.find("Set-Cookie:", endPos);
    }

    return sessionId;
}

std::string readFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to perform login and retrieve cookies
std::string loginAndGetSessionId(const std::string &url, const std::string &username, const std::string &password)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string headersBuffer;
    std::string sessionId;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        char *encodedUsername = curl_easy_escape(curl, username.c_str(), username.length());
        char *encodedPassword = curl_easy_escape(curl, password.c_str(), password.length());

        std::string postFields = "action=login&page=general&username=" + std::string(encodedUsername) + "&password=" + std::string(encodedPassword);

        curl_free(encodedUsername);
        curl_free(encodedPassword);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postFields.length());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headersBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            std::cout << "Login response: " << readBuffer << std::endl;
            std::cout << "Headers response: " << headersBuffer << std::endl;

            sessionId = parseSessionIdFromHeaders(headersBuffer);
            if (!sessionId.empty())
            {
                std::cout << "Login successful. Session ID: " << sessionId << std::endl;
            }
            else
            {
                std::cerr << "Failed to retrieve session ID" << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return sessionId;
}

void sendPostRequest(const std::string &url, const std::string &sessionId, const std::string &postData)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string cookieHeader = "Cookie: id=" + sessionId;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, cookieHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);                     // POST request
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str()); // Add data if needed
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Disable SSL verification for development
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Enable verbose for debugging

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            std::cout << "HTTP Response Code: " << http_code << std::endl;
            std::cout << "POST request to " << url << " successful. Response: " << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
}

// Function to send a GET request with the cookie
void sendGetRequest(const std::string &url, const std::string &sessionId)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string cookieHeader = "Cookie: id=" + sessionId;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, cookieHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);        // GET request
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Disable SSL verification for development
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Enable verbose for debugging

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            std::cout << "HTTP Response Code: " << http_code << std::endl;
            std::cout << "GET request to " << url << " successful. Response: " << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
}

void sendPostRequestWithParams(const std::string &url, const std::string &sessionId)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string cookieHeader = "Cookie: id=" + sessionId;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, cookieHeader.c_str());
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded"); // Set content type for POST

        std::string postData = "action=reboot&page=general"; // POST data

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str()); // Set POST data
        curl_easy_setopt(curl, CURLOPT_POST, 1L);                     // POST request
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);           // Follow redirects
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Disable SSL verification for development
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Enable verbose for debugging

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            std::cout << "HTTP Response Code: " << http_code << std::endl;
            std::cout << "POST request to " << url << " successful. Response: " << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
}

int main()
{
    std::string loginUrl = "";
    std::string statusUrl = "";
    std::string postUrl = "";
    std::string getUrl = "";
    std::string rebootUrl = "";
    std::string username = "";
    std::string password = "";
    std::string data = "conf.cfg";

    std::string cookie = loginAndGetSessionId(loginUrl, username, password);

    if (cookie.empty())
    {
        std::cerr << "Failed to retrieve cookie" << std::endl;
        return 1;
    }

    sendPostRequest(postUrl, cookie, data);
    std::cout << "STARTING THE REBOOT AFTER SEND CONF" << std::endl;
    sleep(5);
    // sendGetRequestWithParams(getUrl, cookie);
    sendPostRequestWithParams(rebootUrl, cookie);
    sleep(60);
    std::cout << "After sleep of REBOOT gonna get the status" << std::endl;
    std::string id = loginAndGetSessionId(loginUrl, username, password);
    sendGetRequest(statusUrl, id);

    return 0;
}

