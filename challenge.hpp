#include <iostream>
#include <string>

class Question {
  public: 
    char question[255];
    int index;
    int size;
    Question* next;
    Question (char* qu, int i, int s) {
      for (int x = 0; x < 255; ++x) { question[x] = qu[x];}
      index = i;
      size = s;
    }
};

class Challenge {
  private:
    int stored = 0;
    Question* first;
    Question* last;
  public:
    int process(std::string TestInput, bool isTested) {
      char valid[56] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\?\"";
      char text[255];
      int textSize = 0;
      std::string input;
      int returnValue = 0;
      if (!isTested) {
        std::cout << ".";
        std::getline(std::cin, input);
      } else {
        input = TestInput;
      }
      for (int i = 0; i < input.size() && i < 255; ++i) {
        text[i] = input[i];
        textSize = i;
      }
      ++textSize;
      //check for invalid characters
      bool invalid = true;
      int questionmark = 0;
      int questionmarkIndex = 0;
      int apostrophes = 0;
      int apostrophIndex = 0;
      for(int i = 0; i < textSize; ++i) {
        for (int j = 0; j < sizeof(valid); ++j) {
          if (text[i] == valid[j]) {
            invalid = false;
          }
        }
        if (text[i] == '\?') {
          ++questionmark;
          questionmarkIndex = i;
        }
        if (text[i] == '\"') {
          ++apostrophes;
          apostrophIndex = i;
        }
      }
      if (invalid) {
          std::cout << "invalid input\n";
          invalid = true;
          returnValue = 1;
      }
      if (apostrophIndex < questionmarkIndex && apostrophes%2 == 1) {
          std::cout << "invalid input - wrong apostrophes\n";
          invalid = true;
          returnValue = 2;
      }
      if (questionmark != 1) {
          std::cout << "invalid input - no question mark " << questionmark;
          invalid = true;
          returnValue = 3;
      }
      if (apostrophes >= 2 && !invalid) storeQuestion(text, questionmarkIndex, textSize);
      if (apostrophes == 0 && !invalid) answer(text, textSize);
      
      return returnValue;
    }

    void storeQuestion(char *question, int index, int textSize) {
      std::cout << "\n";
      Question* store = new Question(question, index, textSize);
      ++stored;
      if (stored == 1) {
        first = store;
        last = store;
      }
      last->next = store;
      last = store;
    }

    bool answer(char *question, int textSize) {
      std::cout << "\n";
      Question* next = first;
      bool answered = false;
      for (int i = 0; i < stored; ++i) {
        bool found = true;
        for (int j = 0;j < textSize; ++j) {
          if (question[j] != next->question[j]) found = false;
        }
        if (found) {
          printAnswer(next);
          answered = true;
          return true;
        }
        next = next->next;
      }
      if (!answered) {
        std::cout << "the answer to life, universe and everything is 42\n";
      }
      return false;
    }

    void printAnswer(Question *answer) {
      char* info = answer->question;
      char line[255] = "";
      bool bracketOn = false;
      for (int i = answer->index; i < answer->size; ++i) {
        if (info[i] == '\"') bracketOn = !bracketOn;
        if (info[i] == '\"' && bracketOn) std::cout << "* "; 
        if (info[i] != '\"' && bracketOn) std::cout << info[i];
        if (info[i] == '\"' && !bracketOn) std::cout << "\n";
      }
    }
};
