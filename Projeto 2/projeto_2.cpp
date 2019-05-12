#include <cg_window.hpp>

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    printf("uso: ./projeto2CPP arquivo.obj");
    return -1;
  }

  const char * objFile = argv[1];
  cgicmc::Window window;
  window.createWindow(500, 500);
  window.run(objFile);
}
