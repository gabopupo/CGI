#include <cg_window.hpp>

int main(int argc, char const *argv[]) {
  cgicmc::Window window;
  window.createWindow(800, 600);
  window.run();
}