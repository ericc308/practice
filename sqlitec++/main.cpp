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
  std::vector<User> first_update = storage.get_all<User>();
  first_update[0].firstName = "Mary";
  update_to_database(first_update[0], storage);
  User user3{1, "Ken", 3};
  add_data_to_database(user3, storage);
  std::vector<User> user_list = {{1, "Penaa", 3}, {1, "Yen", 5}, {1, "Fenff", 2}, {1, "Gen", 2}, {1, "Zenni", 2}, {1, "Xoen", 2}, {1, "Benna", 2}};

  add_datagroup_to_database(user_list, storage);

  // print all
  std::cout << "Print all data in database. \n";
  std::vector<User> allUsers = storage.get_all<User>();
  std::cout << "allUsers (" << allUsers.size() << "):" << std::endl;
  for (int item = 0; item < allUsers.size(); item++) {
    std::cout << allUsers[item].id << " " << allUsers[item].firstName << " " << allUsers[item].typeId << "\n";
  }

  // select 1 and show all
  std::cout << "Get_all @ condition. \n";
  std::vector<User> SelectUsers = storage.get_all<User>(where(c(&User::typeId) > 2));
  std::cout << "User typeId > 2 (" << SelectUsers.size() << "):" << std::endl;
  for (auto &iUser : SelectUsers) {
    std::cout << storage.dump(iUser) << std::endl;
  }

  // select order by asc
  std::cout << "Get_all @ condition with  order in asc. \n";
  auto select_asc = storage.get_all<User>(where(length(&User::firstName) > 3), order_by(&User::id).asc());
  std::cout << "Get_all @ condition(length(name)>3)order by id asc " << select_asc.size() << std::endl;
  for (auto &iUser : select_asc) {
    std::cout << storage.dump(iUser) << std::endl;
  }

  // select order by desc
  std::cout << "Get_all @ condition(length(name)>3) with  order in desc. \n";
  auto select_desc = storage.get_all<User>(where(length(&User::firstName) > 3), order_by(&User::id).desc());
  std::cout << "where length( firstname > 3 ) order by id desc " << select_desc.size() << std::endl;
  for (auto &iUser : select_desc) {
    std::cout << storage.dump(iUser) << std::endl;
  }

  // select order and limit(the number of showing)
  std::cout << "Get_first 3 data @ condition(length(name)>3) with  order in desc. \n";
  auto select_desc_limit3 = storage.get_all<User>(where(length(&User::firstName) > 3), order_by(&User::id).desc(), limit(3));
  for (auto &iUser : select_desc_limit3) {
    std::cout << storage.dump(iUser) << std::endl;
  }
  std::cout << "Get 4th, 5th and 6th data @ condition(length(name)>3) with  order in desc. \n";
  auto select_desc_limit35 = storage.get_all<User>(where(length(&User::firstName) > 3), order_by(&User::id).desc(), limit(3, 5));
  for (auto &iUser : select_desc_limit35) {
    std::cout << storage.dump(iUser) << std::endl;
  }
  std::cout << "Get first 3 data after 2nd data @ condition(length(name)>3) with  order in desc. \n";
  auto select_desc_offset2 = storage.get_all<User>(where(length(&User::firstName) > 3), order_by(&User::id).desc(), limit(3, offset(2)));
  for (auto &iUser : select_desc_offset2) {
    std::cout << storage.dump(iUser) << std::endl;
  }



  // select by execute sql command
  std::cout << "Use select firstname @  condition(length(name)>3). \n";
  auto selectStatement = storage.select(&User::firstName, where(length(&User::firstName) > 3));
 for (auto &iUser : selectStatement) {
    std::cout << iUser<< std::endl;
  }

    //select distinct
  std::cout<<"Get distinct typeid data @ (length(name)>3)";
  auto selectStatement_dist = storage.select(columns(&User::firstName,&User::typeId), where(length(&User::firstName) > 3));
    for(int iUser=0;iUser<selectStatement_dist.size();iUser++){
      std::cout<<std::get<0>(selectStatement_dist[iUser])<<" "<<std::get<1>(selectStatement_dist[iUser])<<std::endl;
    }
  return 0;
}