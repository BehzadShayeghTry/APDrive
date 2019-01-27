#include "Core.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Group.hpp"
#include "../server/server.hpp"
using namespace std;

void replace_all(string before, string now, string& str) {
    for ( int character = str.find(before); character >= 0; character = str.find(before) )
        str.replace(character, before.size(), now);
}

string Core::body_folder_paste_page(Document* main_doc, int &n, string sorce_dir, string order) {
  vector<Document*> contents = main_doc->get_contents();
  string body;

  body += "<div>\n";
  body += "  <input id=\"n-"+to_string(++n)+"\" type=\"checkbox\"></input>\n";
  body += "  <pre class=\"doc-line\">\n";
  body += "    <label for=\"n-"+to_string(n)+"\"><i class=\"fas fa-folder-open\"></i> "+main_doc->get_name()+"</label>"; //---
  if((main_doc != Root)) {
    body += (check_hole_rw_access_http(main_doc, Document::WRITE)) ? //paste icon
             "   <a href=\"/moving?target-dir="+main_doc->path()+"&sorce-dir="+sorce_dir+"&order="+order+"\" class=\"black-enable\"><i class=\"fas fa-paste\"></i></a>\n" :
             "   <i class=\"red-trash-unable fas fa-paste\"></i>\n";
  }
  body += "  </pre>\n";
  body += "  <div class=\"sub\">\n";
  body += "    <div class=\"in\">\n";
  for(int i=0; i<contents.size(); i++) {
    if( contents[i]->is_folder() ){
      if( check_rw_access_http(contents[i], Document::READ) )
        body += body_folder_paste_page(contents[i], n, sorce_dir, order);
      else {
        body += "      <pre class=\"doc-line red-unable\"><i class=\"fas fa-folder-open\"></i> "+contents[i]->get_name(); //---
        body += (check_rw_access_http(contents[i], Document::WRITE)) ? //paste icon
                     "   <a href=\"/moving?target-dir="+main_doc->path()+"&sorce-dir="+sorce_dir+"&order="+order+"\" class=\"black-enable\"><i class=\"fas fa-paste\"></i></a>\n" :
                     "   <i class=\"red-trash-unable fas fa-paste\"></i></pre>\n";
      }
    }
  }
  body += "    </div>\n";
  body += "  </div>\n";
  body += "</div>\n";

  return body;
}

string Core::pastePageBody(string sorce_dir, string order) {
  string body;
  int n=-1;

  ifstream Dashboard_css("static/Dashboard.css");
  string css, css_line;
  while( getline(Dashboard_css,css_line) )
    css += css_line + "\n";

  body += "<!DOCTYPE html>\n";
  body += "<html>\n";
  body += "<head>";
  body += "  <link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.6.3/css/all.css\" integrity=\"sha384-UHRtZLI+pbxtHCWp1t77Bi1L4ZtiqrqD80Kn4Z8NTSRyMA2Fd33n5dQ8lWUE00s/\" crossorigin=\"anonymous\">";
  body += "  <link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Open+Sans:400,600\">";
  body += "  <title>Paste directory</title>";
  body += "</head>";
  body += "<body>\n";
  body += "  <h1>Choose a path to Paste file:</h1>\n";
  body += "  <div class=\"under_line\">\n";
  body += "    <div class=\"left_side\">\n";
  body += "      <a href=\"/dashboard\" class=\"left_icons\"><i class=\"fas fa-door-open\"></i></a>\n";
  body += "    </div>\n";
  body += "    <div class=\"main\">";
  body += "      <i id=\"archive-icon\" class=\"fas fa-archive\"></i>";
  body += "      <form class=\"prime\">\n";
  body += "        <h2>Choose a path to Paste file: </h2>\n";
  body += "        <div class=\"tree\">\n";
  body += body_folder_paste_page(Root,n,sorce_dir,order);
  body += "        </div>\n";
  body += "      </form>\n";
  body += "    </div>";
  body += "    <div class=\"right_side\">\n";
  body += "      <a href=\"/logout\" id=\"logout-icon\"><i class=\"fas fa-sign-out-alt\"></i></a>";
  body += "    </div>\n";     
  body += "  </div>";
  body += "</body>\n";
  body += "</html>\n\n";
  body += css;
  
  ofstream file("./static/on-time-pasteboard.html");
  file << body;
  return body;
}

string Core::userListBody() {
  string body;

  ifstream userlist_static("static/userlist.html");
  string body_line;
  while( getline(userlist_static, body_line) )
    body += body_line + "\n";

  string adduserdoor_html;
  if(on_time_user->get_access_level() > User::ADMIN)
    adduserdoor_html += "      <a href=\"/signup\" class=\"left_icons\"><i class=\"fas fa-user-plus\"></i></a>\n";
  replace_all("$(Add_user_door)", adduserdoor_html, body);
  
  for(int i=1; i<users.size(); i++) {

    ifstream userinf_static("static/userinf.html");
    string users_html;
    while( getline(userinf_static, body_line) )
      users_html += body_line + "\n";

    replace_all("$(Username)", users[i]->get_user_name(), users_html);
    replace_all("$(Access_level)", access_level_reader(users[i]->get_access_level()), users_html);
    users_html += "         $(Other_user)";

    replace_all("$(Users)", users_html, body);
    replace_all("$(Other_user)", "$(Users)", body);
  }
  replace_all("$(Users)", "", body);
  
  return body;
}

string Core::dashboardBody() {
  string body;
  int n=-1;

  ifstream dashboard_html("static/dashboard.html");
  string body_line;
  while( getline(dashboard_html, body_line) )
    body += body_line + "\n";

  string usericon_html;
  if(on_time_user->get_access_level() > User::ADMIN)
    usericon_html += "      <i class=\"left_icons fas fa-user-secret\"></i>\n";
  else if(on_time_user->get_access_level() == User::ADMIN)
    usericon_html += "      <i class=\"left_icons fas fa-user-tie\"></i>\n";
  else
    usericon_html += "      <i class=\"left_icons fas fa-user\"></i>\n";
  replace_all("$(User_icon)", usericon_html, body);
  
  string usertsettingicon_html;
  if(on_time_user->get_access_level() >=User::ADMIN)
    usertsettingicon_html += "<a href=\"/users\" class=\"left_icons\"><i class=\"fas fa-users-cog\"></i></a>\n";
  replace_all("$(Users_setting_icon)", usertsettingicon_html, body);

  replace_all("$(User_name)", get_working_username(), body);  
  replace_all("$(Root_folder)", folderBody(Root,n), body);  

  ofstream file("static/on_time_dashboard.html");
  file << body;
  return body;
}

string Core::folderBody(Document* main_doc, int &n) {
  string body;

  ifstream dashboard_html("static/folder.html");
  string body_line;
  while( getline(dashboard_html, body_line) )
    body += body_line + "\n";

  replace_all("$(N)", to_string(++n), body);
  replace_all("$(Main_doc_name)", main_doc->get_name(), body);
  replace_all("$(Trash&Inf_icon)", trashInfoIconBody(main_doc, ++n), body);
  replace_all("$(New_document)", newDocumentBody(main_doc, ++n), body);
  replace_all("$(Contents)", contentsBody(main_doc, ++n), body);

  return body;
}

string Core::trashInfoIconBody(Document* main_doc, int &n) {
  string body;
  if((main_doc != Root)) {
    string trashicon_html;
    trashicon_html += (check_hole_rw_access_http(main_doc, Document::WRITE)) ?
             "   <a href=\"/remove?directory="+main_doc->path()+"\" class=\"black-enable\"><i class=\"fas fa-trash-alt\"></i></a>\n" :
             "   <i class=\"red-trash-unable fas fa-trash-alt\"></i>\n";
    body += trashicon_html;
  
    body += infoIconBody(main_doc, ++n);
  }
  return body;
}

string Core::infoIconBody(Document* main_doc, int &n) {
  string body;
  if (check_rw_access_http(main_doc, Document::READ)) {
    body += "      <div class=\"doc-line\">\n";
    body += "        <input id=\"n-"+to_string(++n)+"\" type=\"checkbox\"></input>\n";
    body += "        <label id=\"info-icon\" class=\"black-enable\" for=\"n-"+to_string(n)+"\"><i class=\"fas fa-info-circle\"></i></label>\n";
    body += "        <div class=\"sub\">\n";
    body += "          <p class=\"info-type\">"+main_doc->info_http()+"</p>\n";
    body += "        </div>\n";
    body += "      </div>\n";
  }
  else
    body += "      <i class=\"red-info-unable fas fa-info-circle\"></i>\n";

  return body;
}

string Core::newDocumentBody(Document* main_doc, int &n) {
  string body;
  if(main_doc == Root)
    return body;

  body += ( check_rw_access_http(main_doc, Document::WRITE) ) ?
    newIconBody(main_doc, ++n) :
    "      <p class=\"red-unable\"><i class=\"fas fa-plus-square\"></i> new</p>\n";

  return body;
}

string Core::contentsBody(Document* main_doc, int &n) {
  vector<Document*> contents = main_doc->get_contents();

  string body;
  for(int i=0; i<contents.size(); i++) {
    if( contents[i]->is_folder() )
      body += (check_rw_access_http(contents[i], Document::READ)) ?
          folderBody(contents[i], ++n) :
          unableFolderBody(contents[i], ++n) ;
    else
      body += fileBody(contents[i], ++n);
  }

  return body;
}

string Core::unableFolderBody(Document* main_doc, int &n) {
  string body;

  ifstream unablefolder_html("static/unablefolder.html");
  string body_line;
  while( getline(unablefolder_html, body_line) )
    body += body_line + "\n";

  replace_all("$(Main_doc_name)", main_doc->get_name(), body);
  replace_all("$(Trash&Inf_icon)", trashInfoIconBody(main_doc, ++n), body);

  return body;
}

string Core::fileBody(Document* main_doc, int &n) {
  string body;

  body += "      <div>\n";
      body += "        <input id=\"n-"+to_string(++n)+"\" type=\"checkbox\"></input>\n";
      body += "        <pre class=\"doc-line\">\n";
      body += "          <label for=\"n-"+to_string(n)+"\" class=\"folder\"><i class=\"fas fa-file\"></i> "+main_doc->get_name()+"</label>"; //---
      body += trashInfoIconBody(main_doc, ++n);
      body += "        </pre>\n";
      body += "        <div class=\"sub\">\n";
      body += "          <div class=\"file-options\">\n";
      body += fileIconsBody(main_doc, ++n);
      body += "          </div>\n";
      body += "        </div>\n";
      body += "      </div>\n";

  return body;
}

string Core::fileIconsBody(Document* main_doc, int &n) {
  string body;

  body += (check_rw_access_http(main_doc, Document::READ)) ? //read icon
              "            <a class=\"options-info\" href=\"/show?directory="+main_doc->path()+"\"><i class=\"fas fa-eye\" style=\"color: black;\"></i></a>\n" :
              "            <i class=\"options-info fas fa-eye\" style=\"color: red;\"></i>\n";
      body += (check_rw_access_http(main_doc, Document::READ)) ? //copy icon
              "            <a class=\"options-info\" href=\"/move?directory="+main_doc->path()+"&order=copy\"><i class=\"fas fa-copy\" style=\"color: black;\"></i></a>\n" :
              "            <i class=\"options-info fas fa-copy\" style=\"color: red;\"></i>\n";
      body += (check_rw_access_http(main_doc, Document::WRITE)) ? //cut icon
              "            <a class=\"options-info\" href=\"/move?directory="+main_doc->path()+"&order=cut\"><i class=\"fas fa-cut\" style=\"color: black;\"></i></a>\n" :
              "            <i class=\"options-info fas fa-cut\" style=\"color: red;\"></i>\n";
      body += downloadIconBody(main_doc, ++n);

  return body;
}

string Core::downloadIconBody(Document* main_doc, int &n) {
  string body;

  if (check_rw_access_http(main_doc, Document::READ)) {
      ifstream downloadicon_html("static/downloadicon.html");
      string body_line;
      while( getline(downloadicon_html, body_line) )
        body += body_line + "\n";

      replace_all("$(N)", to_string(++n), body);
      replace_all("$(Path)", main_doc->path(), body);
  }
  else
    body += "            <i class=\"fas fa-download\" style=\"color: red;\"></i>\n";

  return body;
}

string Core::newIconBody(Document* main_doc, int &n) {
  string body;
  body += "      <div>\n";
    body += "        <input id=\"n-"+to_string(++n)+"\" type=\"checkbox\"></input>\n";
    body += "        <label for=\"n-"+to_string(n)+"\"><i class=\"fas fa-plus-square\"></i> new</label>\n";
    body += "        <div class=\"sub\">\n";
    body += newFolderIconBody(main_doc, ++n);
    body += newFileIconBody(main_doc, ++n);
    body += "        </div>\n";
    body += "      </div>\n";

  return body;
}

string Core::newFolderIconBody(Document* main_doc, int &n) {
  string body;

  ifstream newfoldericon_html("static/newfoldericon.html");
    string body_line;
    while( getline(newfoldericon_html, body_line) )
      body += body_line + "\n";

    replace_all("$(N)", to_string(++n), body);
    replace_all("$(Path)", main_doc->path(), body);
 
  return body;
}

string Core::newFileIconBody(Document* main_doc, int &n) {
  string body;

  ifstream newfileicon_html("static/newfileicon.html");
    string body_line;
    while( getline(newfileicon_html, body_line) )
      body += body_line + "\n";

    replace_all("$(N)", to_string(++n), body);
    replace_all("$(Path)", main_doc->path(), body);
 
  return body;
}

// ---------------------------------------------------------------------------------------

void Core::upload_http(string real_file, string upload_path) {
    check_on_time_user();

    vector<string> dirs = read_path(upload_path);
    if(upload_path[upload_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string file_name = dirs[dirs.size()-1];
    dirs.pop_back();
    Document* target_dir = upload_path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);

    check_rw_access(target_dir, Document::WRITE);

    if(target_dir->check_name_exist(file_name))
        remove(upload_path);

    if(real_file.size()==0){
        logout();
        throw Server::Exception("no file has choosen!");
    }
    
    vector<unsigned char> buffer;
    for(int i=0; i<real_file.size(); i++)
        buffer.push_back(real_file[i]);
    new File(on_time_user,file_name,target_dir, on_time_user->get_own_group() ,buffer);
}

User::AccessLevel Core::get_working_user_accesslevel() {
    return on_time_user->get_access_level();
}

bool Core::check_rw_access_http(Document* doc, Document::Access acc) {
    if( on_time_user == users[0] ) return true;
    if( doc == Root ) return false;

    Document::Access user_access = doc->get_access(on_time_user);

    if( (acc == Document::READ) &&
        (user_access == Document::WRITE || user_access == Document::NONE) )
        return false;

    if( (acc == Document::WRITE) &&
        (user_access == Document::READ || user_access == Document::NONE) )
        return false;

    if( (acc == Document::READ_WRITE) &&
        (user_access != Document::READ_WRITE))
        return false;

    return true;
}

bool Core::check_hole_rw_access_http(Document* doc, Document::Access acc) {
    if( on_time_user == users[0] ) return true;
    return doc->hole_access(on_time_user,acc);
}

string Core::read_name_of_path(string path) {
    vector<string> all = read_path(path);
    return all[all.size()-1];
}

string Core::show_media(string target) {
    check_on_time_user();

    vector<string> dirs = read_path(target);
    if(target[target.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string file_name = dirs[dirs.size()-1];
    dirs.pop_back();
    Document* target_dir = target[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);
    Document* downloading_file = target_dir->select_file(file_name);

    check_rw_access(downloading_file, Document::READ);

    vector<unsigned char> buffer = downloading_file->get_buffer();
    string output;
    for(int i=0; i<buffer.size(); i++)
        output.push_back(buffer[i]);

    return output;
}

// --------------------------------------------------------------------------------------------

Core::Core() {
    Root = new Folder();
    users.push_back(new User(Root));
    groups.push_back(users[0]->get_own_group());
    on_time_directory = Root;
}

string Core::get_working_username() {
    if(on_time_user == NULL) return "(?)";
    return on_time_user->get_user_name();
}

string Core::get_working_path() {
    return on_time_directory->path();
}

void Core::set_home_directory(string _home_directory) {
    if(_home_directory[home_directory.size()-1]!='/')
        _home_directory.push_back('/');
        
    home_directory = _home_directory;
}

void Core::login(string user_name, string password) {
    if( on_time_user != NULL ){
        logout();
        throw Server::Exception("should log out at first");
    }

    int user_index = index_user(user_name);

    if(user_index < 0){
        logout();
        throw Server::Exception("not found user "+user_name);
    }
    if(!users[user_index]->check_password(password)){
        logout();
        throw Server::Exception("wrong password"+password);
    }

    on_time_user = users[user_index];
    on_time_directory = on_time_user->get_home();
}

void Core::logout() {
    on_time_user = NULL;
    on_time_directory = Root;
}

void Core::add_user(string user_name, string password) {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN ){
        logout();
        throw Server::Exception("low access, need admin at least");
    }

    if( index_user(user_name) > 0 ){
        logout();
        throw Server::Exception("already exist "+user_name);
    }
    if( index_group(user_name) > 0 ){
        logout();
        throw Server::Exception("already exist "+user_name+" as a group");
    }

    users.push_back(new User(user_name,password,Root));
    groups.push_back(users[users.size()-1]->get_own_group());
}

void Core::change_directory(string path) {
    check_on_time_user();
    vector<string> dirs = read_path(path);

    Document* target_directory = path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);

    check_rw_access(target_directory, Document::READ);
    on_time_directory = target_directory;
}

void Core::make_directory(string name) {
    check_on_time_user();
    if(check_name_exist(name)){
        logout();
        throw Server::Exception("already exist "+name);
    }

    check_rw_access(on_time_directory, Document::WRITE);

    new Folder(on_time_user,name,on_time_directory, on_time_user->get_own_group());
}

void Core::print_directory() {
    check_on_time_user();
    cout << "you are in : \"" << get_working_path() << "\"" << endl;
}

void Core::promote(string username, User::AccessLevel Mote) {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN){
        logout();
        throw Server::Exception("low access, need superuser at least");
    }

    int index = index_user(username);
    if(index < 0){
        logout();
        throw Server::Exception("not found user: "+username);
    }
    if(Mote == User::ROOT || users[index]->get_access_level() == User::ROOT){
        logout();
        throw Server::Exception("cannt use this command on root");
    }
    if(users[index]->get_access_level() >= Mote){
        logout();
        throw Server::Exception("you cant use this command for demote");
    }
    else users[index]->change_access_level(Mote);
}

void Core::demote(string username, User::AccessLevel Mote) {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN){
        logout();
        throw Server::Exception("low access, need superuser at least");
    }

    int index = index_user(username);
    if(index < 0){
        logout();
        throw Server::Exception("not found user: "+username);
    }
    if(Mote == User::ROOT || users[index]->get_access_level() == User::ROOT){
        logout();
        throw Server::Exception("cannt use this command on root");
    }
    if(users[index]->get_access_level() <= Mote){
        logout();
        throw Server::Exception("you cant use this command for demote");
    }
    else users[index]->change_access_level(Mote);
}

void Core::userlist() {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN){
        logout();
        throw Server::Exception("low access, need admin at least");
    }

    print_users_list();
}

void Core::add_group(string group_name) {
    check_on_time_user();

    if( index_group(group_name) > 0 ){
        logout();
        throw Server::Exception("already exist "+group_name);
    }

    groups.push_back( new Group(group_name, on_time_user));
}

void Core::add_to_group(string group_name, string user_name) {
    check_on_time_user();

    int group_index = index_group(group_name);
    if( group_index < 0 ){
        logout();
        throw Server::Exception("already not fount "+group_name);
    }
    if( !groups[group_index]->has_same_member(on_time_user)){
        logout();
        throw Server::Exception("user is not in group "+group_name);
    }

    int user_index = index_user(user_name);
    if( user_index < 0 ){
        logout();
        throw Server::Exception("already not fount "+user_name);
    }
    if( groups[group_index]->has_same_member(users[user_index])){
        logout();
        throw Server::Exception(user_name+"is already in group "+group_name);
    }

    groups[group_index]->add_member(users[user_index]);
}

void Core::upload(string real_file, string upload_path) {
    check_on_time_user();

    vector<string> dirs = read_path(upload_path);
    if(upload_path[upload_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string file_name = dirs[dirs.size()-1];
    dirs.pop_back();
    Document* target_dir = upload_path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);

    check_rw_access(target_dir, Document::WRITE);

    if(target_dir->check_name_exist(file_name))
        remove(upload_path);

    ifstream file(home_directory+real_file, ifstream::binary);
    if (!file){
        logout();
        throw Server::Exception("not found "+real_file);
    }
    
    vector<unsigned char> buffer(istreambuf_iterator<char>(file), {});
    new File(on_time_user,file_name,target_dir, on_time_user->get_own_group() ,buffer);
}

void Core::download(string output_name, string file_path) {
    check_on_time_user();

    vector<string> dirs = read_path(file_path);
    if(file_path[file_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string file_name = dirs[dirs.size()-1];
    dirs.pop_back();
    Document* target_dir = file_path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);
    Document* downloading_file = target_dir->select_file(file_name);

    check_rw_access(downloading_file, Document::READ);

    ofstream new_file(home_directory+output_name, ofstream::binary);

    vector<unsigned char> buffer = downloading_file->get_buffer();
    new_file.write ((char*)&buffer[0] , buffer.size());
}

void Core::list_documents() {
    check_on_time_user();
    on_time_directory->list_contents();
}

void Core::copy(string sorce_path, string destination_path) {
    check_on_time_user();

    vector<string> sorce_dirs = read_path(sorce_path);
    if(sorce_path[sorce_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string sorce_name = sorce_dirs[sorce_dirs.size()-1];
    sorce_dirs.pop_back();
    Document* sorce_dir = sorce_path[0]=='/' ? find_diraction(Root,sorce_dirs) :
                            find_diraction(on_time_directory,sorce_dirs);
    Document* sorce = sorce_dir->select_file(sorce_name);

    check_rw_access(sorce, Document::READ);

    vector<string> destination_dirs = read_path(destination_path);
    if(destination_path[destination_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string file_name = destination_dirs[destination_dirs.size()-1];
    destination_dirs.pop_back();
    Document* destination_dir = destination_path[0]=='/' ? find_diraction(Root,destination_dirs) :
                            find_diraction(on_time_directory,destination_dirs);

    check_rw_access(destination_dir, Document::WRITE);

    new File(on_time_user, file_name, destination_dir, on_time_user->get_own_group() , sorce);
}

void Core::move(string sorce_path, string destination_path) {
    copy(sorce_path,destination_path);
    remove(sorce_path);
}

void Core::remove(string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);

    check_hole_rw_access(target, Document::WRITE);

    (target->get_station())->remove(target->get_pure_name());
}

void Core::file_size(string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);

    check_rw_access(target, Document::READ);

    unsigned long size = target->size();
    cout << size << " bytes = ";
    if(size%1000 < 500)
        cout << size/1000;
    else
        cout << size/1000 + 1;
    cout << " Kb" << endl;
}

void Core::storage() {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN)
        Server::Exception("low access, need admin at least");

    file_size("/");
}

void Core::elem_info(string path) {
    check_on_time_user();
    Document* target = find_file_or_folder(path);

    target->show_info();
}

void Core::elem_info() {
    check_on_time_user();

    on_time_directory->show_folder_info();
}

void Core::plus_group_mode(Document::Access mode, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    target->add_group_access(mode);
}

void Core::sub_group_mode(Document::Access mode, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    target->sub_group_access(mode);
}

void Core::plus_user_mode(Document::Access mode, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    target->add_user_access(mode);
}

void Core::sub_user_mode(Document::Access mode, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    target->sub_user_access(mode);
}

void Core::change_owner(string username, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    int user_index = index_user(username);
    if(user_index < 0){
        logout();
        throw Server::Exception("not found user: "+username);
    }

    target->change_owner(users[user_index]);
}

void Core::change_group(string groupname, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    int group_index = index_group(groupname);
    if( index_group(groupname) < 0 ){
        logout();
        throw Server::Exception("not found group: "+groupname);
    }

    target->change_group(groups[group_index]);
}

int Core::index_user(string user_name) {
    for(int i=0; i<users.size(); i++) {
        if(users[i]->is_same_user(user_name)) return i;
    }
    return -1;
}

int Core::index_group(string group_name) {
    for(int i=0; i<groups.size(); i++) {
        if(groups[i]->is_same_group(group_name)) return i;
    }
    return -1;
}

Document* Core::find_diraction(Document* start, vector<string> dirs) {
    Document* response = start;
    if(dirs.size()==0) return start;

    if(dirs[0]=="")
        dirs.erase(dirs.begin()+0);

    for(int i=0; i<dirs.size(); i++){
        if(dirs[i]==".") continue;
        if(dirs[i]=="..") {
            response = response->get_station();
            continue;
        }
        response = response->subset_folder(dirs[i]);
    }
    return response;
}

vector<string> Core::read_path(string path) {
    vector<string> dirs;
    int slash_index = path.find('/');
    while(slash_index < path.size()-1) {
        dirs.push_back( path.substr(0,slash_index) );
        path.erase(0,slash_index+1);
        slash_index = path.find('/');
    }
    if(path[path.size()-1]=='/')
        path.pop_back();
    dirs.push_back(path);
    return dirs;
}

bool Core::check_name_exist(string name) {
    return on_time_directory->check_name_exist(name);
}

void Core::print_users_list() {
    cout << "Username\t\tAccessLevel" << endl;
    cout << "--------\t\t-----------" << endl;
    for(int i=0; i<users.size(); i++) {
        cout << "--- " << users[i]->get_user_name()
         << "\t\t" << access_level_reader(users[i]->get_access_level()) << endl;
    }
    cout << "------------------" << endl;
}

string Core::access_level_reader(User::AccessLevel access_level) {
    if( access_level == User::USER ) return "user";
    if( access_level == User::ADMIN ) return "admin";
    if( access_level == User::SUPERUSER ) return "superuser";
    if( access_level == User::ROOT ) return "root";
    else{
        logout();
        throw Server::Exception("unknown access level");
    }
}

Document* Core::find_file_or_folder(string path) {
    if(path == "/") return Root;
    vector<string> dirs = read_path(path);
    
    string name;
    bool poped = false;
    if(path[path.size()-1] != '/'){
        name = dirs[dirs.size()-1];
        dirs.pop_back();
        poped = true;
    }

    Document* dir = path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory, dirs);

    if(!poped) return dir;

    return (dir->is_folder(name)) ? dir->subset_folder(name)
                                : dir->select_file(name);
}

void Core::check_on_time_user() {
    if( on_time_user == NULL ){
        logout();
        throw Server::Exception("no user is working");
    }
}

void Core::check_rw_access(Document* doc, Document::Access acc) {
    if( on_time_user == users[0] ) return;
    if( doc == Root ){
        logout();
        throw Server::Exception("access denied, need Root access");
    }

    Document::Access user_access = doc->get_access(on_time_user);

    if( (acc == Document::READ) &&
        (user_access == Document::WRITE || user_access == Document::NONE) ){
        logout();
    throw Server::Exception("access denied, need Read access");
    }

    if( (acc == Document::WRITE) &&
        (user_access == Document::READ || user_access == Document::NONE) ){
        logout();
    throw Server::Exception("access denied, need Write access");
    }

    if( (acc == Document::READ_WRITE) &&
        (user_access != Document::READ_WRITE)){
        logout();
    throw Server::Exception("access denied, need Read-Write access");
    }
}

void Core::check_hole_rw_access(Document* doc, Document::Access acc) {
    if( on_time_user != users[0])
        if( !(doc->hole_access(on_time_user,acc)) ){
            logout();
            throw Server::Exception("access denied, need Hole-Write access");
        }
}