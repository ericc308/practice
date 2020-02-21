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

int main() {

  std::string path = "db.sqlite";
  std::cout << "Create File:\n";

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
    }
  }

  auto storage =
      make_storage("db.sqlite", make_table("users", make_column("id", &User::id, autoincrement(), primary_key()), make_column("first_name", &User::firstName), make_column("type_id", &User::typeId)));

  storage.sync_schema();

  User user1;
  user1.id = 1;
  user1.firstName = "John";
  user1.typeId = 2;
  auto insertedId = storage.insert(user1);
  User user2;
  user2.id = 1;
  user2.firstName = "Mary";
  user2.typeId = 2;
  auto insertedId2 = storage.insert(user2);
  User user3{1, "Ken", 3};
  auto insertedId3 = storage.insert(user3);
  //  SELECT doctor_id
  //  FROM visits
  //  WHERE LENGTH(patient_name) > 8
  std::vector<User> allUsers = storage.get_all<User>();
  std::cout << "allUsers (" << allUsers.size() << "):" << std::endl;
  //   for (auto &user : allUsers) {
  //     std::cout
  //         << storage.dump(user)
  //         << std::
  //                endl; //  dump returns std::string with json-like style
  //                      //  object info. For example: { id : '1', first_name
  //                      //  : 'Jonh', last_name : 'Doe', birth_date :
  //                      //  '664416000', image_url :
  //                      //  'https://cdn1.iconfinder.com/data/icons/man-icon-set/100/man_icon-21-512.png',
  //                      //  type_id : '3' }
  //   }
  for (int item = 0; item < allUsers.size(); item++) {
    std::cout << allUsers[item].id << " " << allUsers[item].firstName << " " << allUsers[item].typeId << "\n";
  }
  try {
    auto user = storage.get<User>(insertedId);
    std::cout << "user = " << user.firstName << " " << user.typeId << std::endl;
  } catch (std::system_error e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unknown exeption" << std::endl;
  }
  return 0;
}