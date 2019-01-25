#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include <vector>
#include "../core/Core.hpp"

struct Client {
  std::string username;
  std::string password;
  std::string sid;
};

class ShowHandler : public RequestHandler {
public:
  ShowHandler(Core*, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class MovingHandler : public RequestHandler {
public:
  MovingHandler(Core*, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class MoveHandler : public RequestHandler {
public:
  MoveHandler(Core*, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class DownloadHandler : public RequestHandler {
public:
  DownloadHandler(Core*, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class RemoveHandler : public RequestHandler {
public:
  RemoveHandler(Core*, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class MoteHandler : public RequestHandler {
public:
  MoteHandler(Core*, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class UsersHandler : public RequestHandler {
public:
  UsersHandler(Core*, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class UploadHandler : public RequestHandler {
public:
  UploadHandler(Core*, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class MakeDirecroeyHandler : public RequestHandler {
public:
  MakeDirecroeyHandler(Core* , std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class DashboardHandler : public RequestHandler {
public:
	DashboardHandler(Core *, std::vector<Client>*);
	Response *callback(Request *);
private:
	Core* core;
	std::vector<Client>* clients;
};

class SignupHandler : public RequestHandler {
public:
	SignupHandler(Core *, std::vector<Client>*);
	Response *callback(Request *);
private:
	Core* core;
	std::vector<Client>* clients;
};

class LoginGetter : public RequestHandler {
public:
  LoginGetter(Core *, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class LoginHandler : public RequestHandler {
public:
  LoginHandler(Core *, std::vector<Client>*, int*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
  int *sid_number;
};

class LogoutHandler : public RequestHandler {
public:
	LogoutHandler(std::vector<Client>*);
	Response *callback(Request *);
private:
	std::vector<Client>* clients;
};