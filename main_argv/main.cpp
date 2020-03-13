#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <streambuf>
#include <vector>

#include <complex>
#include <math.h>
#include <vector>

int main(int argc, char *argv[]) {


  std::cout<<"input : "<<argv[1]<<std::endl;
  std::string buffer(argv[1]);
  std::stringstream stream(buffer);
  std::string sub;
  getline(stream, sub,' ');
  int num = buffer.find(",");
  int end_string = buffer.find("]");
  std::cout << num << std::endl;
  std::string sub1;
  std::string sub2;
  sub1.assign(buffer,1,num-1);
  sub2.assign(buffer,num+1,end_string-num-1);
  std::cout << stoi(sub1)<< std::endl;
  std::cout << stoi(sub2)<< std::endl;
  
  std::cout<<(argv[2]==NULL)<<std::endl;
  return 0;
}