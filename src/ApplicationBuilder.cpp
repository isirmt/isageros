#include "ApplicationBuilder.hpp"

void GLSYS::ApplicationBuilder::Initialize() {
  Time::Initialize();
  std::setlocale(LC_ALL, "");

  if (mkdir("./saves", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP |
                           S_IROTH | S_IWOTH) == 0) {
    puts("Info: Created Directory \"./saves\"");
  } else {
    perror("mkdir");
  }
  if (mkdir("./saves/story", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP |
                                 S_IROTH | S_IWOTH) == 0) {
    puts("Info: Created Directory \"./saves/story\"");
  } else {
    perror("mkdir");
  }
}

void GLSYS::ApplicationBuilder::Update() {
  Time::Update();
  Input::MouseInput::Update();
}