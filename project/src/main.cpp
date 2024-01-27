#include <oatpp/network/Server.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/web/server/HttpRouter.hpp>

// clang-format off
oatpp::String html =
    "<!DOCTYPE html>"
    " <head>"
    "   <script src='https://unpkg.com/htmx.org@1.9.10' integrity='sha384-D1Kt99CQMDuVetoL1lrYwg5t+9QdHe7NLX/SoJYkXDFfX37iInKRy5xLSi8nO7UC' crossorigin='anonymous'></script>"
    " </head>"
    " <body>"
    "   <h1>fluido de pal</h1>"
    "   <button hx-get='/turnon' hx-trigger='click' hx-swap='none'>Turn on</button>"
    "   <button hx-get='/turnoff' hx-trigger='click' hx-swap='none'>Turn off</button>"
    "   <img src='https://cdn.discordapp.com/emojis/747989853358260246.gif?size=1024'/>"
    " </body>"
    "</html>";
// clang-format on

oatpp::String palServerStatus = "0";

class rootHandler : public oatpp::web::server::HttpRequestHandler {
 public:
  std::shared_ptr<OutgoingResponse> handle(
      const std::shared_ptr<IncomingRequest>& request) override {
    return ResponseFactory::createResponse(Status::CODE_200, html);
  }
};

class turnOnHandler : public oatpp::web::server::HttpRequestHandler {
 public:
  std::shared_ptr<OutgoingResponse> handle(
      const std::shared_ptr<IncomingRequest>& request) override {
    OATPP_LOGI("Dickworld Server", "turn on");
    palServerStatus = "1";
    return ResponseFactory::createResponse(Status::CODE_200, "");
  }
};

class turnOffHandler : public oatpp::web::server::HttpRequestHandler {
 public:
  std::shared_ptr<OutgoingResponse> handle(
      const std::shared_ptr<IncomingRequest>& request) override {
    OATPP_LOGI("Dickworld Server", "turn off");
    palServerStatus = "0";
    return ResponseFactory::createResponse(Status::CODE_200, "");
  }
};

class serverStatusHandler : public oatpp::web::server::HttpRequestHandler {
 public:
  std::shared_ptr<OutgoingResponse> handle(
      const std::shared_ptr<IncomingRequest>& request) override {
    return ResponseFactory::createResponse(Status::CODE_200, palServerStatus);
  }
};

void run() {
  auto router = oatpp::web::server::HttpRouter::createShared();

  router->route("GET", "/", std::make_shared<rootHandler>());
  router->route("GET", "/turnon", std::make_shared<turnOnHandler>());
  router->route("GET", "/turnoff", std::make_shared<turnOffHandler>());
  router->route("GET", "/status", std::make_shared<serverStatusHandler>());

  auto connectionHandler =
      oatpp::web::server::HttpConnectionHandler::createShared(router);
  auto connectionProvider =
      oatpp::network::tcp::server::ConnectionProvider::createShared(
          {"localhost", 8080, oatpp::network::Address::IP_4});
  oatpp::network::Server server(connectionProvider, connectionHandler);
  OATPP_LOGI("Dickworld Server", "Pal ready on port %s",
             connectionProvider->getProperty("port").getData());
  server.run();
}

int main() {
  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  return 0;
}
