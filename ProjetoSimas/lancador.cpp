#include "lancador.h"
#include "jogador.h"
#include "inimigo.h"
#include "gerenciador_colisoes.h"
#include <iostream>

Lancador::Lancador() : Inimigo(), tamanho(50), tempoAtaque(0.f), intervaloAtaque(4.f) {
	nivel_maldade = 2;
	vida = 200;
	ataque = 15;
	num_vidas = 1;
}
Lancador::~Lancador() {
	tamanho = -1;
}

void Lancador::danificar(Jogador* p) {
	if (p) {
		p->setVida(p->getVida() - ataque); 
	}
}
void Lancador::executar() {
	setId(4);
	retangulo.setSize(sf::Vector2f(64.f, 64.f));
	if (!textura.loadFromFile("lancador.png")) {
		std::cerr << "Erro fatal: Nao foi possivel carregar a textura lancador.png" << std::endl;
		return;
	}
	retangulo.setTexture(&textura);
}
void Lancador::mover() {
	if (!noChao) {
		sf::Vector2f pos = getPosicao();
		pos.y += aplicarGravidade(0.016f, forcaMitico);
		setPosicao(pos.x, pos.y);
	}
}

void Lancador::atacar(Jogador* jogador1, Jogador* jogador2, float deltaTime, const sf::View& viewAtual, Gerenciadores::GerenciadorColisoes* gerenciadorColisoes, ListaEntidades* pListaEnts) {
	Jogador* alvo = nullptr;
	if (jogador1) {
		alvo = jogador1;
	}
	else if (jogador2) {
		alvo = jogador2;
	}

	if (!alvo) {
		return;
	}

	sf::FloatRect viewRect(
		viewAtual.getCenter().x - viewAtual.getSize().x / 2.f,
		viewAtual.getCenter().y - viewAtual.getSize().y / 2.f,
		viewAtual.getSize().x,
		viewAtual.getSize().y);

	if (!viewRect.contains(getPosicao()) || !viewRect.contains(alvo->getPosicao()))
		return;

	for (auto it = projeteis.begin(); it != projeteis.end(); ) {
		Projetil* p = *it;
		if (!p->getestaAtivo()) {
			it = projeteis.erase(it);
		}
		else {
			++it;
		}
	}
	tempoAtaque += deltaTime;
	if (tempoAtaque >= intervaloAtaque) {
		Projetil* novoProj = new Projetil();
		novoProj->disparar(getPosicao(), alvo->getPosicao(), 200.f, 0.f, true);

		projeteis.push_back(novoProj);

		if (gerenciadorColisoes)
			gerenciadorColisoes->inclueEntidade(novoProj);
		if (pListaEnts)
			pListaEnts->incluir(novoProj);

		tempoAtaque = 0.f;
	}
}
int Lancador::getVida() const {
	return vida;
}
int Lancador::getAtaque() const {
	return ataque;
}
void Lancador::setVida(int v) {
	vida = v;
}
void Lancador::setAtaque(int a) {
	ataque = a;
}
void Lancador::setId(int novoId) {
	id = novoId;
}
int Lancador::getId() const {
	return id;
}
void Lancador::setVelocidade(float nvVelocidade) {
	velocidade = nvVelocidade;
}
float Lancador::getVelocidade() {
	return velocidade;
}
void Lancador::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
		for (Projetil* p : projeteis) {
			if (p && p->getestaAtivo())
				pGG->desenha(p->getRetangulo());
		}
	}
}
void Lancador::tratarColisaoComJogador(Jogador* jogador, int tipoColisao) {
	if (tipoColisao == 1) { 
		this->setVida(0); 
		jogador->setVelocidadeVertical(-400.f); 
	}
	else {
		this->danificar(jogador);
		sf::Vector2f pos = jogador->getRetangulo().getPosition();
		pos.x += (tipoColisao == 2) ? -10.f : 10.f; 
		jogador->setPosicao(pos.x, pos.y);
	}
}
void Lancador::setVelocidadeVertical(float nvVelocidadeVertical) {
	velocidadeVertical = nvVelocidadeVertical;
}
float Lancador::getVelocidadeVertical() const {
	return velocidadeVertical;
}
void Lancador::setNoChao(bool NC) {
	noChao = NC;
}
bool Lancador::getNochao() {
	return noChao;
}
void Lancador::salvar(std::ostream& os) {
	// Escreve todos os dados do lançador
	os << gravidade << " " << forcaMitico << " " << forcaMiticaAtiva << " "
		<< num_vidas << " " << getVida() << " " << velocidade << " " << noChao << " " << ataque << " "
		<< nivel_maldade << " " << tamanho << " " << tempoAtaque << " " << intervaloAtaque << " "
		<< getPosicao().x << " " << getPosicao().y << std::endl;
}