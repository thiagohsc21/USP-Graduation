package jogo;

public class Bozo {
	
	public static void main(java.lang.String[] args) throws java.io.IOException{
		
		Placar p = new Placar();
		RolaDados r = new RolaDados(5);
		String dados_modificados = new String(), c = "espera_enter";
		
		int[] valores_dados;
		int posicao_ocupada;
		boolean aux = false;
		
		System.out.print("\n----------Jogo Bozó----------" + p + "\n\n" + "Algumas observações: \n");
		System.out.print("1) Quando quiser trocar o valor de alguns dados, quando solicitado, digite os números separados por espaço.\n");
		System.out.print("2) Quando não quiser trocar nenhum dado, digite um número menor que um, ou maior que 6.\n");
		System.out.print("3) Após digitar os números, pressione enter para executar.\n\n\n");

		// Representa cada uma das dez rodadas do jogo
		for(int i = 0 ; i < 10 ; i++) {
						
			System.out.printf("---Rodada (%d)---\n", i+1);
			System.out.print("Pressione ENTER para lançar os dados\n");
			
			// Recebe o ENTER do usuário
			while(!c.isBlank()) {
				c = EntradaTeclado.leString();
			}
			
			valores_dados = r.rolar(); // Rola todos os dados uma primeira vez
			System.out.println("Esses são seus dados iniciais: \n" + r);
									
			System.out.println("\nDigite os números dos dados que deseja girar novamente: ");
			dados_modificados = EntradaTeclado.leString();
			valores_dados = r.rolar(dados_modificados); // Rola somente os dados pedidos na segunda vez	
			
			System.out.println("\nEsses são seus dados atuais: \n" + r);

			System.out.println("\nDigite os números dos dados que deseja girar novamente: ");
			dados_modificados = EntradaTeclado.leString();
			valores_dados = r.rolar(dados_modificados); // Rola somente os dados pedidos na terceira vez
			
			System.out.println("\nEsses são seus dados finais: \n" + r + "\nEsse é o placar atual: \n" + p);
				
			while(!aux) {
				System.out.print("\n\nEscolha a posição que deseja ocupar: ");
				posicao_ocupada = EntradaTeclado.leInt();
				try{
					p.add(posicao_ocupada, valores_dados); // Atualiza a posicao pedida pelo usuario no placar
					aux = true;
				} catch(IllegalArgumentException e) {
					System.out.print("ERRO: O valor digitado não corresponde "
							+ "a uma das posições do placar ou é uma posição já preenchida.\n");
				}
			}
			
			System.out.println("\n\nEsse é o placar atualizado: \n" + p + "\n");
			// Atualiza as variáveis para não termos problema com os while
			c = "espera_enter";
			aux = false;

			if(i == 9) {
				System.out.printf("--------------------------------------");
				System.out.printf("\n--- Essa é sua pontuação final: %d ---\n", p.getScore());
				System.out.printf("--------------------------------------\n\n");
				System.out.print("FIM DE JOGO\n");
			}
		}
		
	}
}
