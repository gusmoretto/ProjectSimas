#include "espinho.h"
#include "jogador.h"

Espinho::Espinho() : Obstaculo(), elasticidade(128.f) { danoso = true; }
Espinho::~Espinho() {
}
void Espinho::executar() {
	setId(10);
	retangulo.setSize(sf::Vector2f(64.f, 64.f));
	if (!textura.loadFromFile("cacto.png")) {
		std::cout << "Erro ao carregar espinho.png" << std::endl;
	}
	retangulo.setTexture(&textura);
}
void Espinho::obstacular(Jogador* p) {
	if (p) {
		sf::FloatRect areaJogador = p->getRetangulo().getGlobalBounds();
		sf::FloatRect areaEspinho = this->getRetangulo().getGlobalBounds();
		if (areaJogador.intersects(areaEspinho)) {
			if (elasticidade) {
				p->setVelocidadeVertical(-p->getVelocidadeVertical() * 0.5f);
			}
			else {
				p->setVida(p->getVida() - 10); 
			}
			std::cout << "Jogador atingido por espinho! Vida restante: " << p->getVida() << std::endl;
		}
	}
}
void Espinho::setId(int novoId) {
	id = novoId;
}
int Espinho::getId() const {
	return id;
}
void Espinho::setElasticidade(bool e){
	elasticidade = e;
}
bool Espinho::getElasticidade() const {
	return elasticidade;
}
void Espinho::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
	}
}
void Espinho::atualizarFisica(float dt) {
	if (!gravidadeAtiva) {
		aplicarGravidade(dt, getForcaMitico());

		sf::Vector2f pos = retangulo.getPosition();
		if (pos.y + retangulo.getSize().y > 670.f) {
			pos.y = 670.f - retangulo.getSize().y;
			velocidadeVertical = 0.f;
			retangulo.setPosition(pos);
		}
	}
}
void Espinho::salvar() {
	Obstaculo::salvarDataBuffer();
	if (buffer)
		*buffer << elasticidade << endl;
	ofstream arquivoEspinhos;
	arquivoEspinhos.open("arquivo_espinho.txt");
	arquivoEspinhos << buffer;
	arquivoEspinhos.close();
}