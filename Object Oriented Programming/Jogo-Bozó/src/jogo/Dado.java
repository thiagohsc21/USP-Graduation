package jogo;

public class Dado {
	
	Random r = new Random();
	
	private int numero_lados;
	private int ultimo_gerado;
	
	// Gera um numero aleatorio entre 1 e numero_lados com semente variável e armazena no ultimo_lado
	public int rolar() {
		ultimo_gerado = r.getIntRand(numero_lados)+1;
		return ultimo_gerado;
	}
	
	// Retorna o último valor gerado, ultimo_lado
	public int getLado() {
		return ultimo_gerado;
	}
	
	// Retorna na string de retorno a face resultante do dado gerado
	public java.lang.String toString() {
				
		String dado = new String();
		
		if(ultimo_gerado == 1) {
			dado += "+-----+\n";
			dado += "|     |\n";
			dado += "|  *  |\n";
			dado += "|     |\n";
			dado += "+-----+\n";       
		}
		else if(ultimo_gerado == 2) {
			dado += "+-----+\n";
			dado += "|*    |\n";
			dado += "|     |\n";
			dado += "|    *|\n";
			dado += "+-----+\n";       
		}
		else if(ultimo_gerado == 3) {
			dado += "+-----+\n";
			dado += "|*    |\n";
			dado += "|  *  |\n";
			dado += "|    *|\n";
			dado += "+-----+\n";        
		}
		else if(ultimo_gerado == 4) {
			dado += "+-----+\n";
			dado += "|*   *|\n";
			dado += "|     |\n";
			dado += "|*   *|\n";
			dado += "+-----+\n";          
		}
		else if(ultimo_gerado == 5) {
			dado += "+-----+\n";
			dado += "|*   *|\n";
			dado += "|  *  |\n";
			dado += "|*   *|\n";
			dado += "+-----+\n";          
		}
		else if(ultimo_gerado == 6) {
			dado += "+-----+\n";
			dado += "|*   *|\n";
			dado += "|*   *|\n";
			dado += "|*   *|\n";
			dado += "+-----+\n";         
		}

		return dado;
	}
	
	// Construtor 1
	public Dado() {
		numero_lados = 6;
	}
	
	// Construtor 2
	public Dado(int k) {
		numero_lados = k;
	}
	
	

}
