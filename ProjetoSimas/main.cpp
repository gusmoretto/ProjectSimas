#include "menu.h"
#include "gerenciador_grafico.h"

int main() {
    Gerenciadores::GerenciadorGrafico* pGG = new Gerenciadores::GerenciadorGrafico(); 
    Menu menuPrincipal(pGG); 
    menuPrincipal.executar(); 
    delete pGG; 
    return 0; 
}