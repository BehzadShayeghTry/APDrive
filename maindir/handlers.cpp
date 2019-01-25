#include "handlers.hpp"

using namespace std;

int find_client_index_username(std::string username, const vector<Client> clients){
  int index;
  for(int index=0; index<clients.size(); index++)
    if(clients[index].username == username) return index;
  return -1;
}
int find_client_index_sid(std::string sid, const vector<Client> clients){
  int index;
  for(int index=0; index<clients.size(); index++)
    if(clients[index].sid == sid) return index;
  return -1;
}

RemoveHandler::RemoveHandler(Core* _core, vector<Client> *_clients) {
  core = _core;
  clients = _clients;
}

Response *RemoveHandler::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  if(index == -1) throw Server::Exception("you should login first...");
  core->login((*clients)[index].username, (*clients)[index].password);

  core->remove( req->getQueryParam("directory") );

  Response* res = Response::redirect("/dashboard");
  core->logout();
  return res;
}


MoteHandler::MoteHandler(Core* _core, vector<Client> *_clients) {
  core = _core;
  clients = _clients;
}

Response *MoteHandler::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  if(index == -1) throw Server::Exception("you should login first...");
  core->login((*clients)[index].username, (*clients)[index].password);
  
  string order = req->getQueryParam("order");
  string user = req->getQueryParam("user");
  string mote = req->getQueryParam("mote");
  User::AccessLevel new_mote;

  if(order == "promote") {
    if(mote == "user")
      core->promote(user, User::ADMIN);
    else if(mote == "admin")
      core->promote(user, User::SUPERUSER);
  }
  else if(order == "demote") {
    if(mote == "superuser")
      core->demote(user, User::ADMIN);
    else if(mote == "admin")
      core->demote(user, User::USER);
  }
  else throw Server::Exception("Wrong order ...");

  Response* res = Response::redirect("/users");
  core->logout();
  return res;
}

UsersHandler::UsersHandler(Core* _core, vector<Client> *_clients) {
  core = _core;
  clients = _clients;
}

Response *UsersHandler::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  if(index == -1) throw Server::Exception("you should login first...");
  core->login((*clients)[index].username, (*clients)[index].password);
  
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body = core->setUserListBody();

  res->setBody(body);
  core->logout();
  return res;
}

UploadHandler::UploadHandler(Core* _core, vector<Client> *_clients) {
  core = _core;
  clients = _clients;
}

Response *UploadHandler::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  if(index == -1) throw Server::Exception("you should login first...");
  core->login((*clients)[index].username, (*clients)[index].password);

  core->change_directory(req->getQueryParam("directory"));
  core->upload_http(req->getBodyParam("file"), req->getBodyParam("file_name"));

  Response* res = Response::redirect("/dashboard");
  core->logout();
  return res;
}

MakeDirecroeyHandler::MakeDirecroeyHandler(Core* _core, vector<Client> *_clients) {
  core = _core;
  clients = _clients;
}

Response *MakeDirecroeyHandler::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  if(index == -1) throw Server::Exception("you should login first...");
  core->login((*clients)[index].username, (*clients)[index].password);

  core->change_directory(req->getQueryParam("directory"));
  core->make_directory(req->getBodyParam("foldername"));

  Response* res = Response::redirect("/dashboard");
  core->logout();
  return res;
}

DashboardHandler::DashboardHandler(Core* _core, vector<Client> *_clients) {
  core = _core;
  clients = _clients;
}

Response *DashboardHandler::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  if(index == -1) throw Server::Exception("you should login first...");
  core->login((*clients)[index].username, (*clients)[index].password);

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body = core->setBody();

  res->setBody(body);
  core->logout();
  return res;
}

SignupHandler::SignupHandler(Core* _core, vector<Client> *_clients) {
  core = _core;
  clients = _clients;
}

Response *SignupHandler::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  if(index == -1) throw Server::Exception("you should login first...");
  core->login((*clients)[index].username, (*clients)[index].password);
  if(core->get_working_user_accesslevel() < User::SUPERUSER)
    throw Server::Exception("low access level. need super user access");

  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string rep_pass = req->getBodyParam("confirm-password");

  if(username == "" || password == "")
    throw Server::Exception("one field is empty!");

  if (password != rep_pass)
    throw Server::Exception("wrong password confirm");

  else {
  core->add_user(username,password);
  cout << "username: " << username << ",\tpassword: " << password << endl;

  Response* res = Response::redirect("/signup");
  core->logout();
  return res;
  }
}

LoginGetter::LoginGetter(Core* _core, vector<Client> *_clients) {
  core = _core;
  clients = _clients;
}

Response *LoginGetter::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  Response *res;
  res = (index == -1) ? Response::redirect("/loginpage") : Response::redirect("/dashboard");
  return res;
}

LoginHandler::LoginHandler(Core* _core, vector<Client> *_clients) {
  core = _core;
  clients = _clients;
}

Response *LoginHandler::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  if(index != -1) throw Server::Exception("logout first...");

  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");

  core->login(username,password);

  string sid = "user"+to_string((*clients).size()+65);
  Client new_client;
  new_client.username = username;
  new_client.password = password;
  new_client.sid = sid;
  (*clients).push_back(new_client);

  cout << "username: " << username << ",\tpassword: " << password << endl;
  
  Response *res = Response::redirect("/login");

  res->setSessionId(sid);
  
  core->logout();
  return res;
}

LogoutHandler::LogoutHandler(vector<Client> *_clients) {
  clients = _clients;
}

Response *LogoutHandler::callback(Request *req) {
  int index = find_client_index_sid( req->getSessionId() , (*clients));
  if(index == -1) throw Server::Exception("you are not already login...");

  (*clients).erase((*clients).begin()+index);

  Response *res = Response::redirect("/login");
  return res;
}

Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}