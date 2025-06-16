#include "inim_medio.h"
#include "jogador.h"
#include "inimigo.h"
#include "gerenciador_colisoes.h"
#include <iostream>

InimMedio::InimMedio() : Inimigo(), tamanho(50), direcao(1.f), tempoAtaque(0.f), intervaloAtaque(2.f) {
	nivel_maldade = 2;
	vida = 200;
	ataque = 20;
	deslocamentoMax = 32.f;
	deslocamentoAtual = 0.f;
	posicaoInicial = getPosicao();
}
InimMedio::~InimMedio() {
	tamanho = -1;
}

void InimMedio::danificar(Jogador* p) {
	if (p) {
		p->setVida(p->getVida() - ataque); 
		std::cout << "Jogador danificado! Vida restante: " << p->getVida() << std::endl;
	}
}
void InimMedio::executar() {
	setId(4);
	retangulo.setSize(sf::Vector2f(64.f, 64.f));
	if (!textura.loadFromFile("lancador.png")) {
		std::cout << "Erro ao carregar lancador.png" << std::endl;
	}
	retangulo.setTexture(&textura);
}
void InimMedio::mover() {
	sf::Vector2f pos = getPosicao();
	setNoChao(false); 
	if (!getNochao()) {
		velocidadeVertical += 9.8f * 0.016f;
		pos.y += velocidadeVertical * 0.016f;
	}
	else {
		velocidadeVertical = 0.f;
	}
	pos.y += aplicarGravidade(0.016f);

	sf::Vector2f size = retangulo.getSize();
	if (pos.y + size.y >= 670.f) {
		pos.y = 670.f - size.y;
		retangulo.setPosition(pos);
	}
	setPosicao(pos.x, pos.y);
}

void InimMedio::atacar(Jogador* jogador1, Jogador*, float deltaTime, const sf::View& viewAtual, Gerenciadores::GerenciadorColisoes* gerenciadorColisoes) {
	Jogador* alvo = jogador1;

	sf::FloatRect viewRect(
		viewAtual.getCenter().x - viewAtual.getSize().x / 2.f,
		viewAtual.getCenter().y - viewAtual.getSize().y / 2.f,
		viewAtual.getSize().x,
		viewAtual.getSize().y
	);
	if (!viewRect.contains(getPosicao()) || !alvo || !viewRect.contains(alvo->getPosicao()))
		return;

	// 1. Remova e delete projeteis inativos ANTES de criar novos
	for (auto it = projeteis.begin(); it != projeteis.end(); ) {
		Projetil* p = *it;
		if (!p->getestaAtivo()) {
			if (gerenciadorColisoes)
				gerenciadorColisoes->removeEntidade(p);
			delete p;
			it = projeteis.erase(it);
		}
		else {
			++it;
		}
	}

	// 2. Agora crie novos projeteis se for o momento
	tempoAtaque += deltaTime;
	if (tempoAtaque >= intervaloAtaque) {
		for (int i = 0; i < 15; ++i) {
			Projetil* novoProj = new Projetil();
			//novoProj->disparar(getPosicao(), alvo->getPosicao(), 300.f, true);
			projeteis.push_back(novoProj);
			if (gerenciadorColisoes)
				gerenciadorColisoes->inclueEntidade(novoProj);
		}
		tempoAtaque = 0.f;
	}
}


int InimMedio::getVida() const {
	return vida;
}
int InimMedio::getAtaque() const {
	return ataque;
}
void InimMedio::setVida(int v) {
	vida = v;
}
void InimMedio::setAtaque(int a) {
	ataque = a;
}
void InimMedio::setId(int novoId) {
	id = novoId;
}
int InimMedio::getId() const {
	return id;
}
void InimMedio::setVelocidade(float nvVelocidade) {
	velocidade = nvVelocidade;
}
float InimMedio::getVelocidade() {
	return velocidade;
}
void InimMedio::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
		for (Projetil* p : projeteis) {
			if (p && p->getestaAtivo())
				pGG->desenha(p->getRetangulo());
		}
	}
}
void InimMedio::tratarColisaoComJogador(Jogador* jogador, int tipoColisao) {
	// tipoColisao: 1 = por cima, 2/3 = laterais, 4 = por baixo (ajuste conforme seu verificarColisao)
	if (tipoColisao == 1) { // Por cima
		// Elimina o inimigo (pode ser delete this, ou sinalizar para o gerenciador remover)
		this->setVida(0); // ou outro mecanismo de remoção
		// Opcional: jogador pode quicar/pular ao eliminar o inimigo
		jogador->setVelocidadeVertical(-400.f); // impulso de pulo, ajuste conforme seu jogo
	}
	else {
		// Dano e empurra pouco o jogador
		this->danificar(jogador);
		sf::Vector2f pos = jogador->getRetangulo().getPosition();
		pos.x += (tipoColisao == 2) ? -10.f : 10.f; // empurra para o lado oposto
		jogador->setPosicao(pos.x, pos.y);
	}
}
void InimMedio::setVelocidadeVertical(float nvVelocidadeVertical) {
	velocidadeVertical = nvVelocidadeVertical;
}
float InimMedio::getVelocidadeVertical() const {
	return velocidadeVertical;
}
void InimMedio::setNoChao(bool NC) {
	noChao = NC;
}
bool InimMedio::getNochao() {
	return noChao;
}