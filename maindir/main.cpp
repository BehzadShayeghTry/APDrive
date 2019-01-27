#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include <vector>
#include "../core/Core.hpp"
using namespace std;

const string red("\033[0;31m");
const string reset("\033[0m");


int main(int argc, char **argv) {
  srand(time(NULL));

  Core *core = new Core();
  vector<Client>* clients = new vector<Client>;
  int *sid_number = new int;
  (*sid_number) = 0;

  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");

    server.get("/", new LoginGetter(core, clients) );
    server.get("/signup", new ShowPage("static/signup.html") );
    server.post("/signup", new SignupHandler(core, clients) );
    server.get("/login", new LoginGetter(core, clients) );
    server.get("/loginpage", new ShowPage("static/login.html") );
    server.post("/login", new LoginHandler(core, clients, sid_number) );
    server.get("/logout", new LogoutHandler(clients) );
    server.get("/dashboard", new DashboardHandler(core, clients) );
    server.post("/makedirectory", new MakeDirecroeyHandler(core, clients) );
    server.post("/upload", new UploadHandler(core, clients) );
    server.get("/users", new UsersHandler(core, clients) );
    server.get("/changemote", new MoteHandler(core, clients) );
    server.get("/remove", new RemoveHandler(core, clients) );
    server.post("/download", new DownloadHandler(core, clients) );
    server.get("/move", new MoveHandler(core, clients) );
    server.get("/moving", new MovingHandler(core, clients) );
    server.get("/show", new ShowHandler(core, clients) );

    server.run();
  }
  catch (Server::Exception e) {
    cerr << red << e.getMessage() << reset << endl;
  }

  delete core;
}
