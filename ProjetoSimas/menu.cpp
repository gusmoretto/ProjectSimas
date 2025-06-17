#include "menu.h"
#include <iostream>

Menu::Menu() : pJogo(nullptr) {
}

Menu::~Menu() {

}

void Menu::executar() {

}
void Menu::setId(int novoId) {
    id = novoId;
}

int Menu::getId() const {
    return id;
}