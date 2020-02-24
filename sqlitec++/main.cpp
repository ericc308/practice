#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sqlite_orm/sqlite_orm.h>
using namespace sqlite_orm;

struct User {
  int id;
  std::string firstName;
  int typeId;
};

struct UserType {
  int id;
  std::string name;
};

inline auto ini_db(std::string filepath) {
  auto storage =
      make_storage(filepath, make_table("users", make_column("id", &User::id, autoincrement(), primary_key()), make_column("first_name", &User::firstName), make_column("type_id", &User::typeId)));
  storage.sync_schema();
  return storage;
}

using Storage = decltype(ini_db(""));

auto add_data_to_database(User u1, Storage storage) {
  auto insertedId = storage.insert(u1);
  return insertedId;
}

void add_datagroup_to_database(std::vector<User> user_list, Storage storage) {
  for (int iuser = 0; iuser < user_list.size(); iuser++) {
    add_data_to_database(user_list[iuser], storage);
  }
}

void update_to_database(User u1, Storage storage) { storage.update(u1); }

int main() {

  std::string path = "sqlite.db";
  std::cout << "Create File:\n";

  // sqlite_orm::internal::storage_t<User> storage;

  FILE *pFile;
  pFile = fopen(path.c_str(), "rb");
  if (pFile != nullptr) {
    std::cout << "File is already exit.\n";
    std::cout << "Delete " << path << "\n";

#ifdef _WIN32
    std::string command_del = "del " + path;
    system(command_del.c_str());
#else
    std::string command_del = "rm -f " + path;
    system(command_del.c_str());
#endif

    pFile = fopen(path.c_str(), "rb");
    if (pFile != nullptr) {
      std::cout << "File cannot be removed!\n";
      exit(0);
    }
  } else {
  }

  Storage storage = ini_db(path);

  User user1;
  user1.id = 1;
  user1.firstName = "John";
  user1.typeId = 2;
  add_data_to_database(user1, storage);
  User user2;
  user2.id = 1;
  user2.firstName = "Mary";
  user2.typeId = 2;
  update_to_database(user2, storage);
  User user3{1, "Ken", 3};
  add_data_to_database(user3, storage);
  User user4{1, "Penaa", 3};
  User user5{1, "Yen", 5};
  User user6{1, "Fenff", 2};
  User user7{1, "Gen", 1};
  std::vector<User> user_list;
  user_list.push_back(user4);
  user_list.push_back(user5);
  user_list.push_back(user6);
  user_list.push_back(user7);
  add_datagroup_to_database(user_list, storage);

  // print all
  std::vector<User> allUsers = storage.get_all<User>();
  std::cout << "allUsers (" << allUsers.size() << "):" << std::endl;
  for (int item = 0; item < allUsers.size(); item++) {
    std::cout << allUsers[item].id << " " << allUsers[item].firstName << " " << allUsers[item].typeId << "\n";
  }

  // select 1 and show all
  std::vector<User> SelectUsers = storage.get_all<User>(where(c(&User::typeId) > 2));
  std::cout << "User typeId > 2 (" << SelectUsers.size() << "):" << std::endl;
  for (auto &iUser : SelectUsers) {
    std::cout << storage.dump(iUser) << std::endl;
  }

  //select by execute sql command
  auto selectStatement = storage.prepare(select(&User::firstName, where(length(&User::firstName) > 3)));
  std::cout << "selectStatement = " << selectStatement.sql() << std::endl;  //  prints "SELECT doctor_id FROM ..."
  auto userrows = storage.execute(selectStatement); //  rows is std::vector<decltype(Visit::doctor_id)>

     for (int iUser=0;iUser<userrows.size();iUser++) {
    std::cout << userrows[iUser] << std::endl;
     }

//select order by desc
  std::cout << "where length( firstname > 3 ) order by id desc" << std::endl; 
    auto select_desc = storage.get_all<User>(where(length(&User::firstName) > 3),order_by(&User::id).desc());
    for (auto &iUser : select_desc) {
      std::cout << storage.dump(iUser) << std::endl;
    }

    //select order by asc
    std::cout << "where length( firstname > 3 ) order by id asc" << std::endl; 
    auto select_asc = storage.get_all<User>(where(length(&User::firstName) > 3),order_by(&User::id).asc());
    for (auto &iUser : select_asc) {
      std::cout << storage.dump(iUser) << std::endl;
    }




  return 0;
}