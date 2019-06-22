#include "sistema_comunicacao.hpp"

// Transmissor ////////////////////////////////////////////////////////////////

Transmissor::Transmissor() {
  this->aplicacao.configCamadaAplicacaoTransmissora(&this->camada_aplicacao);
  this->camada_aplicacao.configCamadaEnlaceTransmissora(&this->camada_enlace);
  this->camada_enlace.configCamadaFisicaTransmissora(&this->camada_fisica);
}

void Transmissor::run() {
  this->aplicacao.run();
}

void Transmissor::configMeioFisico(MeioFisico* meio_fisico) {
  this->camada_fisica.configMeioFisico(meio_fisico);
}

void Transmissor::configCodificadorDeBits(ICodificadorDeBits* codificador) {
  this->camada_fisica.configCodificador(codificador);
}

// Receptor ///////////////////////////////////////////////////////////////////

Receptor::Receptor() {
  this->camada_aplicacao.configAplicacaoReceptora(&this->aplicacao);
  this->camada_enlace.configCamadaAplicacaoReceptora(&this->camada_aplicacao);
  this->camada_fisica.configCamadaEnlaceReceptora(&this->camada_enlace);
}

void Receptor::configCodificadorDeBits(ICodificadorDeBits* codificador) {
  this->camada_fisica.configCodificador(codificador);
}

void Receptor::configMeioFisico(MeioFisico* meio_fisico) {
  this->camada_fisica.configMeioFisico(meio_fisico);
}

// SistemaDeComunicacao ///////////////////////////////////////////////////////

//Instanciar o codificador e a porcentagem de erros no meio fisico
SistemaDeComunicacao::SistemaDeComunicacao(ICodificadorDeBits* codificador, double taxa_de_erro) {
  this->meio_fisico.taxaDeErro(taxa_de_erro); //Definir Taxa de erro
  this->transmissor.configMeioFisico(&this->meio_fisico);
  this->transmissor.configCodificadorDeBits(codificador);
  this->receptor.configCodificadorDeBits(codificador);
  this->receptor.configMeioFisico(&this->meio_fisico);
}


void SistemaDeComunicacao::run() {
  this->transmissor.run();
}