#pragma once
#include <unistd.h>

#include <fstream>

template <class T>
class DataStore {
 public:
  DataStore(std::string _filePath);
  ~DataStore();

  T Read();
  void Write(T& _data);

 private:
  std::string filePath;
  std::fstream fs;
};

template <class T>
DataStore<T>::DataStore(std::string _filePath) : filePath(_filePath) {
  fs.open(_filePath, std::ios::binary | std::ios::in | std::ios::out);
  if (!fs) {
    // printf("Error: cannot open \"%s\"\n", _filePath.c_str());
    FILE* fp = fopen(_filePath.c_str(), "w+");
    fclose(fp);
    int res = truncate(_filePath.c_str(), sizeof(T));
    fs.open(_filePath, std::ios::binary | std::ios::in | std::ios::out);
  } else {
    // printf("Info: Successed opening \"%s\"\n", filePath.c_str());
  }
}

template <class T>
DataStore<T>::~DataStore() {
  fs.close();
}

template <class T>
void DataStore<T>::Write(T& _data) {
  fs.seekg(0);
  fs.write(reinterpret_cast<char*>(&_data), sizeof(T));
  if (fs.rdstate() & std::ios_base::failbit)
    printf("Error: cannot write in \"%s\"\n", filePath.c_str());
}

template <class T>
T DataStore<T>::Read() {
  T res;
  fs.read(reinterpret_cast<char*>(&res), sizeof(T));
  if (fs.rdstate() & std::ios_base::failbit)
    printf("Error: cannot read in \"%s\"\n", filePath.c_str());
  return res;
}