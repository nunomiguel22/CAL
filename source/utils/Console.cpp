#include "Console.h"
using namespace std;

void Console::clrscsr() {
  cout << "\033[2J";
}

void Console::setcolor(std::string color) {
  cout << color;
}

void Console::setColorAndBackground(std::string color, std::string background_color) {
  cout << color << background_color;
}

void Console::printLine(std::string color, std::string background, std::string text) {
  cout << color << background << text << NO_COLOR << endl;
}