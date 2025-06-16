#pragma once
#include "inimigo.h"
#include "jogador.h"
#include "projetil.h"
#include "gerenciador_colisoes.h"

class InimMedio : public Inimigo {
private:
	int tamanho;
	float direcao; // -1 para esquerda, 1 para direita
	float tempoAtaque; // tempo acumulado para controlar disparos
	float intervaloAtaque; // intervalo entre disparos
	std::vector<Projetil*> projeteis;
	float deslocamentoMax;
	float deslocamentoAtual;
	Vector2f posicaoInicial;

public:
	InimMedio();
	~InimMedio();
	void executar();
	void danificar(Jogador* p);
	void mover();
	int getVida() const;
	int getAtaque() const;
	void setVida(int v);
	void setAtaque(int a);
	void setId(int novoId);
	int getId() const;
	void setVelocidade(float nvVelocidade);
	float getVelocidade();
	void desenhar();
	void setForcaMitico(float forca) {
		forcaMitico = forca;
	};
	float getForcaMitico() const {
		return forcaMitico;
	};
	void atacar(Jogador* jogador1, Jogador* jogador2, float deltaTime, const sf::View& viewAtual, Gerenciadores::GerenciadorColisoes* gerenciadorColisoes);
	void tratarColisaoComJogador(Jogador* jogador, int tipoColisao);
	void setVelocidadeVertical(float nvVelocidadeVertical);
	float getVelocidadeVertical() const;
	void setNoChao(bool NC);
	bool getNochao();
};
