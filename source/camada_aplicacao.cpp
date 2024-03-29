#include "camada_aplicacao.hpp"

using namespace std;

void CamadaAplicacaoTransmissora :: transmitir(const Mensagem &mensagem){
     
    Quadro quadro = convMensagemPorQuadro(mensagem);
    std::cout
        << esc::color::foreground::BRIGHT_BLUE  // Transformar texto para azul 
        << "Camada Aplicacao transmitiu: " << quadro << std::endl
        << esc::RESET // Resetar configurações de cores de texto
    ;
    camada_enlace->transmitir(quadro);

}

Quadro CamadaAplicacaoTransmissora:: convMensagemPorQuadro(const Mensagem &mensagem){
    
    std::string mensagem_convertida = ""; //String que vai receber a mensagem em binario

    //Realiza a conversao da mensagem original para uma mensagem em binario
    for(int i = 0; i < mensagem.length(); i++){    
        mensagem_convertida += bitset<8> (mensagem[i]).to_string();
    }

    Quadro mensagem_bit = {}; 
    
    //Preenche o vector<bool> com bits de acordo com os valores da string
    for(int i = 0; i < mensagem_convertida.length(); i++){
        if(mensagem_convertida[i] == '1'){
            mensagem_bit.push_back(true); 
        }if(mensagem_convertida[i] == '0'){
            mensagem_bit.push_back(false);
        }
    }

    return (mensagem_bit);
}

void CamadaAplicacaoReceptora :: receber(const Quadro &quadro){
    std::cout 
        << esc::color::foreground::BRIGHT_BLUE  // Transformar texto para azul 
        << "Camada Aplicacao recebeu:    " << quadro << '\n'
        << esc::RESET
    ;
    Mensagem mensagem = convQuadroPorMensagem(quadro);
    aplicacao->receber(mensagem);

}

Mensagem CamadaAplicacaoReceptora::convQuadroPorMensagem(const Quadro &quadro){
    
    string string_binaria = ""; //Armazena a string binaria

    //Converte o fluxodebits para string
    for(int i = 0; i < (quadro.size()); i++){
        
        string_binaria += bitset<1> (quadro[i]).to_string();
        
    }
    
    //Converte a string em binario para ASCII
    stringstream sstream(string_binaria);
    Mensagem string_ascii;
    while(sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        string_ascii += c;
    }

    return (string_ascii);
 
}