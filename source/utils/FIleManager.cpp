#include "FileManager.h"

using namespace std;

// TODO: handle exception in case the file does not open properly
FileManager::FileManager(const std::string& file) {
  //  FileManager::file.open(BASE_DIR_CLION + city + "/" + file + city +
  //  FILE_EXT);
  FileManager::file.open(file);
  this->convFileToVector();
}

void FileManager::convFileToVector() {
  if (this->file.is_open()) {
    string line;
    while (!this->file.eof()) {
      getline(this->file, line);
      this->fileLines.push_back(this->trimSpaces(line));
    }
  }
}

string FileManager::trimSpaces(const string& s) {
  string aux = "";
  for (char i : s) {
    if (i != ' ') {
      aux += i;
    }
  }

  return aux;
}

std::vector<std::string> FileManager::explode(char c, const std::string& s) {
  vector<string> result;
  string str = "";
  for (char i : s) {
    if (i != c) {
      str += i;
    } else {
      if (str.length() > 0) {
        result.push_back(str);
        str = "";
      }
    }
  }

  if (str.length() > 0) {
    result.push_back(str);
  }

  return result;
}

std::vector<std::string> FileManager::getVectorFileLines() {
  return this->fileLines;
}

void FileManager::printFile() {
  if (FileManager::file.is_open()) {
    string line;
    while (!FileManager::file.eof()) {
      getline(FileManager::file, line);
      cout << line << endl;
    }
  }
}

void FileManager::closeFileStream() {
  if (FileManager::file.is_open()) {
    FileManager::file.close();
  }
}
