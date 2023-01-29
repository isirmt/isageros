#include "ApplicationBuilder.hpp"

void GLSYS::ApplicationBuilder::Initialize() {
  Time::Initialize();
  std::setlocale(LC_ALL, "");

  char path[PATH_MAX + 1];

  const size_t LINKSIZE = 100;
  char link[LINKSIZE];

  // 実行中のプロセスのシンボリックリンク
  snprintf(link, LINKSIZE, "/proc/%d/exe", getpid());

  // ファイルパスが得る
  auto resi = readlink(link, path, PATH_MAX);
//
  std::string sPath = path;
  // std::cout << sPath.c_str() << std::endl;
  auto pos = sPath.rfind("/");
  sPath.erase(sPath.begin() + pos, sPath.end());
  // std::cout << sPath.c_str() << std::endl;

  auto resc = chdir(sPath.c_str());

  if (mkdir("./saves", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP |
                           S_IROTH | S_IWOTH) == 0) {
    // puts("Info: Created Directory \"./saves\"");
  } else {
    // perror("mkdir");
  }
  if (mkdir("./saves/story", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP |
                                 S_IROTH | S_IWOTH) == 0) {
    // puts("Info: Created Directory \"./saves/story\"");
  } else {
    // perror("mkdir");
  }
}

void GLSYS::ApplicationBuilder::Update() {
  Time::Update();
  Input::MouseInput::Update();
}