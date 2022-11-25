#include "challenge.hpp"

int main(){
  Challenge challenge;

  std::cout << " @- should return 3\n";
  int test1 = challenge.process("@-", true);
  std::cout << test1 << "\n";
  if (test1 == 3) { 
    std::cout << "passed\n";
  } else {
    std::cout << "failed\n";
  }

  std::cout << " xx?? should return 3";
  int test2 = challenge.process("xx\?\?", true);
  std::cout << test2 << "\n";
  if (test2 == 3) { 
    std::cout << "passed\n";
  } else {
    std::cout << "failed\n";
  }

  std::cout << " xx\"\? should return 2";
  int test3 = challenge.process("xx\"\?", true);
  std::cout << test3 << "\n";
  if (test3 == 2) { 
    std::cout << "passed\n";
  } else {
    std::cout << "failed\n";
  }

  challenge.process("k\? \"a\"", true);
  challenge.process("q\? \"a\" \"b\"", true);
  std::cout << "q\? should answer with stored response\n";
  char check4[12] = "q\?";
  bool test4 = challenge.answer(check4, 2);
  if (test4) { 
    std::cout << "passed\n";
  } else {
    std::cout << "failed\n";
  }

  std::cout << "x\? should trigger the 42-answer \n";
  char check5[12] = "x\?";
  bool test5 = challenge.answer(check5, 2);
  if (!test5) { 
    std::cout << "passed\n";
  } else {
    std::cout << "failed\n";
  }
}