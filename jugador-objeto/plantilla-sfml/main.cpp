#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "include/Arachide.h"
#define kVel 5

int main() {
  Arachide *jugar =Arachide::getInstance();


jugar->iniciar();
  return 0;
}