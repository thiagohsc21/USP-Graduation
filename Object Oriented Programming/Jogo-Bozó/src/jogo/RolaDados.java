package jogo;
import java.lang.Thread;

public class RolaDados {
			
	// Instancia 5 objetos do tipo Dado
	private Dado[] dados = new Dado[5];
	
	private int num_dados;
	private int[] valores_dados;

	// Rola todos os dados e retorna os valores obtidos e armazena em valores_dados
	public int[] rolar() {
		for(int i = 0 ; i < num_dados ; i++) {
			dados[i].rolar();
			valores_dados[i] = dados[i].getLado();
		}
		return valores_dados;
	}
	
	// Rola todos os dados que tiverem true em sua posição no array boleano
	public int[] rolar(boolean[] quais) {
		for(int i = 0 ; i < num_dados ; i++) {
			if(quais[i] == true) {
				dados[i].rolar();
				valores_dados[i] = dados[i].getLado();
			}
		}
		return valores_dados;
	}
	
	// Rola todos os dados passados na string do parâmetro
	public int[] rolar(java.lang.String s) {
		
		// Separa a string por meio dos espaços
		String[] entrada_string = s.split(" ");
		boolean[] entrada_int = new boolean[]{false,false,false,false,false,false};
		
		// Seta true em todas as posições que deveremos rodar, ignorando valores em ]oo,1[ ou ]6,oo[
		for(int i = 0 ; i < entrada_string.length ; i++) {
			if(Integer.parseInt(entrada_string[i]) >= 1 && Integer.parseInt(entrada_string[i]) <= 6)
					entrada_int[Integer.parseInt(entrada_string[i])-1] = true;
		}
		
		return rolar(entrada_int);
	}
	
	// Retorna uma string com a impressão de todos os dados 
	public java.lang.String toString() {
		
		String face_dados = new String();
		String[][] desenho_splitado = new String[num_dados][];
		
		// Escreve o "cabecalho" 123456 na string de retorno 
		// Divide a string de Dado.java utilizando o \n como delimitador e retorna para a matriz desenho_splitado
		for(int i = 0 ; i < num_dados ; i++) {
			face_dados += (i+1) + "           ";	
			desenho_splitado[i] = (dados[i].toString()).split("\n");
			if(i == num_dados-1) {
				face_dados += "\n";
			}
		}
		
		// Pega a matriz desenho_splitado e armazena suas informações na string de retorno
		for(int i = 0 ; i < 5 ; i++) {
			for(int j = 0 ;  j < num_dados ; j++) {
				face_dados += (desenho_splitado[j][i]) + "     ";
				if(j == num_dados-1) face_dados += "\n";
			}
		}
		
		return face_dados;
	}
	
	// Construtor que declara n objetos da classe Dado
	public RolaDados(int n) {
		num_dados = n;
		
		for(int i = 0 ; i < num_dados ; i++) {
			
			// Como o loop executa muito rapidamente, dou um sleep para alterar a seed do random
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
			dados[i] = new Dado();
		}
		valores_dados = new int[num_dados];
	}
	
}
