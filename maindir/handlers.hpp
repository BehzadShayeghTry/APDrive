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
  LoginHandler(Core *, std::vector<Client>*);
  Response *callback(Request *);
private:
  Core* core;
  std::vector<Client>* clients;
};

class LogoutHandler : public RequestHandler {
public:
	LogoutHandler(std::vector<Client>*);
	Response *callback(Request *);
private:
	std::vector<Client>* clients;
};

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};