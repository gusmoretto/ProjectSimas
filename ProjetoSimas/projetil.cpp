#include "projetil.h"
#include <iostream>
#include <cmath>

Projetil::Projetil() : Entidade(), velocidade(0.f, 0.f), destino(0.f, 0.f), ativo(false), dano(10){
	setForcaMitico(-980.f); 
    setId(6);
	retangulo.setSize(sf::Vector2f(32.f, 32.f));
    if (!textura.loadFromFile("pedraazul.png")) {
        std::cout << "Erro ao carregar pedraazul.png" << std::endl;
    }
    retangulo.setTexture(&textura);
}
Projetil::~Projetil() {
	
}
void Projetil::disparar(const Vector2f& origem, const Vector2f& alvo, float velocidadeInicial, float forcaMitico, bool anularGravidade) {
    setPosicao(origem.x, origem.y);
    destino = alvo;
    ativo = true;

    Vector2f direcao = alvo - origem;
    float comprimento = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
    if (comprimento != 0)
        direcao = Vector2f(direcao.x / comprimento, direcao.y / comprimento);

    velocidade = direcao * velocidadeInicial;

    forcaMiticaAtiva = anularGravidade;
}


void Projetil::executar() {
    if (!ativo)
        return;

    float dt = 0.016f; // ou deltaTime real

    // Só aplica gravidade se não estiver anulada
    if (!forcaMiticaAtiva)
        velocidade.y += aplicarGravidade(dt);

    Vector2f pos = getPosicao();
    pos += velocidade * dt;
    setPosicao(pos.x, pos.y);

    // Desativa se sair da tela
    if (pos.x < 0.f || pos.x > 3840.f || pos.y < 0.f || pos.y > 700.f)
        ativo = false;
}


void Projetil::setId(int novoId) {
	id = novoId;
}
int Projetil::getId() const {
	return id;
}
void Projetil::setForcaMitico(float forca) {
    forcaMitico = forca;
}
float Projetil::getForcaMitico() const {
    return forcaMitico;
}
void Projetil::checarColisaoComJogador(Jogador* jogador) {
    if (!ativo || !jogador)
        return;

    // Usa o retângulo de colisão de Entidade
    if (getRetangulo().getGlobalBounds().intersects(jogador->getRetangulo().getGlobalBounds())) {
        ativo = false;
        jogador->setVida(jogador->getVida() - dano);
    }
}
void Projetil::desenhar(){
    if (pGG)
        pGG->desenha(retangulo);
}
void Projetil::salvar() {
    if (auto* p_sstream = dynamic_cast<std::ostringstream*>(buffer)) {
        p_sstream->str("");
        p_sstream->clear();
    }
    else {
        return;
    }

    Entidade::salvarDataBuffer();
    *buffer << velocidade.x << " " << velocidade.y << " " << ativo << " " << dano << std::endl;

    std::ofstream arquivoProjetil("arquivo_projetil.txt", std::ios::app);
    if (arquivoProjetil.is_open()) {
        arquivoProjetil << buffer;
        arquivoProjetil.close();
    }
}


