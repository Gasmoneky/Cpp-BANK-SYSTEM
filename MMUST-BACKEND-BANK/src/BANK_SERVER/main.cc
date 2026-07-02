#include <iostream>
#include <drogon/drogon.h>
int main() {
    using namespace drogon;

    drogon::app().loadConfigFile("config.json");
    app().registerHandler("/api/v1/health", [](const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) {

    });


   app().run();
    return 0;
}
