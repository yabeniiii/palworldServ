#include "project/main.hpp"

#include <crow/crow_all.h>

#include <string>

bool palServerStatus = false;

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/").methods("GET"_method)([]() {
    // clang-format off
    std::string html =
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
    return html;
  });

  CROW_ROUTE(app, "/turnon").methods("GET"_method)([]() {
    palServerStatus = true;
    return "";
  });

  CROW_ROUTE(app, "/turnoff").methods("GET"_method)([]() {
    palServerStatus = false;
    return "";
  });

  CROW_ROUTE(app, "/status").methods("GET"_method)([]() {
    return std::to_string(palServerStatus);
  });

  app.port(8080).multithreaded().run();
  // clang-format off
  return 0;
}

