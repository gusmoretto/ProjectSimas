#pragma once
#include "entidade.h"
#include "jogador.h"

class Projetil: public Entidade {
private:
	Vector2f velocidade, destino;
	bool ativo;
	float dano;


public:
	Projetil(); 
	~Projetil();
	void executar();
	void salvar(std::ostream& os);
	void setId(int novoId) ;
	int getId() const ;
	void disparar(const Vector2f& origem, const Vector2f& alvo, float velocidadeInicial, float forcaMitico = 0.f, bool anularGravidade=true);
	bool getestaAtivo() const { return ativo; }
	void setAtivo(bool novoAtivo) { this->ativo = novoAtivo; }
	void setForcaMitico(float forca);
	float getForcaMitico() const;
	void checarColisaoComJogador(Jogador* jogador);
	void desenhar();
	void restaurar(sf::Vector2f pos, sf::Vector2f vel, bool isAtivo, float danoProjetil, bool anularGravidade);
};
