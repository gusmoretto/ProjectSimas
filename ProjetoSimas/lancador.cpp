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
		std::cout << "Erro ao carregar lancador.png" << std::endl;
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

void Lancador::atacar(Jogador* jogador1, Jogador*, float deltaTime, const sf::View& viewAtual, Gerenciadores::GerenciadorColisoes* gerenciadorColisoes, ListaEntidades* pListaEnts) {
	Jogador* alvo = jogador1;

	sf::FloatRect viewRect(
		viewAtual.getCenter().x - viewAtual.getSize().x / 2.f,
		viewAtual.getCenter().y - viewAtual.getSize().y / 2.f,
		viewAtual.getSize().x,
		viewAtual.getSize().y);
	if (!viewRect.contains(getPosicao()) || !alvo || !viewRect.contains(alvo->getPosicao()))
		return;

	for (auto it = projeteis.begin(); it != projeteis.end(); ) {
		Projetil* p = *it;
		if (!p->getestaAtivo()) {
			it = projeteis.erase(it); // Apenas remove da lista local
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
void Lancador::salvar() {
	if (auto* p_sstream = dynamic_cast<std::ostringstream*>(buffer)) {
		p_sstream->str("");
		p_sstream->clear();
	}
	else {
		return;
	}

	Inimigo::salvarDataBuffer();
	*buffer << tamanho << " " << tempoAtaque << " " << intervaloAtaque << " " << getPosicao().x << " " << getPosicao().y << endl;

	std::ofstream arquivoLancador("arquivo_lancador.txt", std::ios::app);
	if (arquivoLancador.is_open()) {
		arquivoLancador << buffer;
		arquivoLancador.close();
	}
}