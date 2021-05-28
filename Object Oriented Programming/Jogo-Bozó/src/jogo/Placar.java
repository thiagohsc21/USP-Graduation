package jogo;

public class Placar {
	
	// -1 => posição ainda não alterada, auxilia na impressão
	private int[] pontuacao = new int[]{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
	// Adiciona valor no placar
	public void add(int posicao, int[] dados) throws java.lang.IllegalArgumentException{
		
		// Trata as exceções, que são: posicao < 1 ou posicao > 10 e posicao = posicao já preenchida
		if((posicao < 1 || posicao > 10) || pontuacao[posicao-1] != -1) {
			throw new java.lang.IllegalArgumentException("ERRO: O valor digitado não corresponde "
					+ "a uma das posições do placar ou é uma posição já preenchida.\n");
		}
		
		// Vai armazenar em cada posição o número de ocorrências de um dado específico
		// ex: se qnt_dados[0] = 3, quer dizer que temos três dados com o valor 1
		int[] qnt_dados = new int[] {0,0,0,0,0,0};
		
		for(int i = 0 ; i < 5 ; i++) {
			if(dados[i] == 1) qnt_dados[0] += 1;
			else if(dados[i] == 2) qnt_dados[1] += 1;
			else if(dados[i] == 3) qnt_dados[2] += 1;
			else if(dados[i] == 4) qnt_dados[3] += 1;
			else if(dados[i] == 5) qnt_dados[4] += 1;
			else if(dados[i] == 6) qnt_dados[5] += 1;
		}
		
		// Vetor auxiliar referente a parte central do placar
		boolean[] flag = new boolean[]{false,false,false};
		
		// Parte lateral do placar:
		if(posicao >= 1 && posicao <= 6) {
				pontuacao[posicao-1] = qnt_dados[posicao-1]*posicao;
		}
				
		// Parte central do placar:
		
		// Três dados de um tipo e dois de outro (ou 5 do mesmo)
		else if(posicao == 7) {
			
			for(int i = 0 ; i < 6 ; i++) {
				if(qnt_dados[i] == 3) flag[0] = true;
				else if(qnt_dados[i] == 2) flag[1] = true;
				else if(qnt_dados[i] == 5) flag[2] = true;
			}
			
			if(flag[0] == true && flag[1] == true || flag[2] == true) {
				pontuacao[posicao-1] = 15;				
				for(int i = 0 ; i < 3 ; i++) flag[i] = false;
			}
			else pontuacao[posicao-1] = 0;
			
		}
		// Sequência 1,2,3,4,5 ou 2,3,4,5,6
		else if(posicao == 8) {
			
			if(qnt_dados[0] == 1 && qnt_dados[1] == 1 && qnt_dados[2] == 1 && qnt_dados[3] == 1 && qnt_dados[4] == 1 ||
			   qnt_dados[1] == 1 && qnt_dados[2] == 1 && qnt_dados[3] == 1 && qnt_dados[4] == 1 && qnt_dados[5] == 1) {
				pontuacao[posicao-1] = 20;
			}
			else pontuacao[posicao-1] = 0;
			
		}
		// Quatro ou Cinco dados de um mesmo tipo 
		else if(posicao == 9) {
			
			for(int i = 0 ; i < 6 ; i++) {
				if(qnt_dados[i] == 4) flag[0] = true;
				else if(qnt_dados[i] == 5) flag[1] = true;
			}
			
			if(flag[0] == true || flag[1] == true) {
				pontuacao[posicao-1] = 30;
				flag[0] = false;
				flag[1] = false;
			}
			else pontuacao[posicao-1] = 0;
		}
		// Cinco dados de um mesmo tipo
		else if(posicao == 10) {
			
			for(int i = 0 ; i < 6 ; i++) {
				if(qnt_dados[i] == 5) flag[0] = true;
			}
			
			if(flag[0] == true) {
				pontuacao[posicao-1] = 40;
				flag[0] = false;
			}
			else pontuacao[posicao-1] = 0;
			
		}
	}
	
	// Faz a soma de cada posição do placar e a retorna
	public int getScore() {
		int sum = 0;
		for(int i = 0 ; i < 10 ; i++) {
			sum += pontuacao[i];
		}
		return sum;
	}


	// Passa o placar para a string de retorno, lembrando que as posicoes 2 3 7 8 9 10
	// precisam de tratamento especial pela variação do número de digitos
	public java.lang.String toString(){
		
		String s = new String(); 
		
		s += "\n";
		
		if(pontuacao[0] == -1) s += "   (1)   |";
		else s += "    " + pontuacao[0] + "    |";
		
		if(pontuacao[6] == -1) s += "   (7)   |";
		else {
			if(pontuacao[6] == 0) s += "    " + pontuacao[6] + "    |";
			else s += "    " + pontuacao[6] + "   |";
		}
		
		if(pontuacao[3] == -1) s += "   (4)   ";
		else s += "    " + pontuacao[3] + "    ";
		
		s += "\n-----------------------------\n";
		
		if(pontuacao[1] == -1) s += "   (2)   |";
		else {
			if(pontuacao[1] < 10) s += "    " + pontuacao[1] + "    |";
			else s+= "    " + pontuacao[1] + "   |";
		}
		
		if(pontuacao[7] == -1) s += "   (8)   |";
		else {
			if(pontuacao[7] == 0) s += "    " + pontuacao[7] + "    |";
			else s += "    " + pontuacao[7] + "   |";
		}
		
		if(pontuacao[4] == -1) s += "   (5)   ";
		else s += "    " + pontuacao[4] + "    ";
		
		s += "\n-----------------------------\n";
		
		if(pontuacao[2] == -1) s += "   (3)   |";
		else {
			if(pontuacao[2] < 10) s += "    " + pontuacao[2] + "    |";
			else s+= "    " + pontuacao[2] + "   |";
		}
		
		if(pontuacao[8] == -1) s += "   (9)   |";
		else {
			if(pontuacao[8] == 0) s += "    " + pontuacao[8] + "    |";
			else s += "    " + pontuacao[8] + "   |";
		}
		
		if(pontuacao[5] == -1) s += "   (6)   ";
		else s += "    " + pontuacao[5] + "    ";
		
		s += "\n-----------------------------\n";
		
		if(pontuacao[9] == -1) s += "         |   (10)  |      ";
		else {
			if(pontuacao[9] != 0) s+= "         |    " + pontuacao[9] + "   |      ";
			else s+= "         |    " + pontuacao[9] + "    |      ";
		}
		
		s += "\n         +---------+       ";

		return s;
	}
}
