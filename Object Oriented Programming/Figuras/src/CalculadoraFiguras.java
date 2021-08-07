import java.io.IOException;

/* Main */
public class CalculadoraFiguras {
	
	Figuras minhaFigura;
	
	public static void main(String[] args) throws IOException{
		
		int op = 0;
		
		while(op != 4) {
						
				System.out.print("Bem vindo(a) a c�lculadora de �reas e per�metros! Abaixo temos nossas op��es de figuras.\n\n" +
				"1) Quadrado\n" + "2) Ret�ngulo\n" + "3) C�rculo\n" + "4) Encerrar\n\n" + 
				"Digite o n�mero associado a figura para a qual deseja obter tais valores: ");	
				
				boolean aux = true;
				int escolha = 0;
				while(aux) {
					try{
						escolha = EntradaTeclado.leInt();
						if(escolha < 1 || escolha > 4) System.out.print("Por favor, digite um valor entre 1 e 4: ");
						else aux = false;
						
					} catch(Exception e) {
						System.out.print("Por favor, digite um valor entre 1 e 4: ");
					}
				}
				
				if(escolha == 4) {
					System.out.print("\nFim do programa.");
					break;
				}
				else op = escolha;
				
				System.out.print("\nDigite a cor dessa figura: ");
				String cor = EntradaTeclado.leString();
				
				System.out.print("Digite se ela est� preenchida por essa cor (1 = sim e qualquer valor inteiro = n�o): ");
				int preenchida = 0;
				while(!aux) {
					try{
						preenchida = EntradaTeclado.leInt();
						aux = true;
				
					} catch(Exception e) {
						System.out.print("Por favor, digite um n�mero: ");
					}
				}
				
				boolean aux_boolean;
				if(preenchida == 1) aux_boolean = true;
				else aux_boolean = false;
				
				// Quadrado
				if(op == 1) {
					int lado = 0;
					System.out.print("Digite o valor do lado: ");
					lado = recebeEntrada(aux);
					
					Quadrado Q = new Quadrado(cor, aux_boolean, lado);
					System.out.print("\n" + Q + ".\n\n\n");
				}
				
				// Ret�ngulo
				else if(op == 2) {
					int base = 0, altura = 0;
					System.out.print("Digite o valor da base: ");
					base = recebeEntrada(aux);
					
					System.out.print("Digite o valor da altura: ");
					altura = recebeEntrada(aux);
					
					Retangulo R = new Retangulo(cor, aux_boolean, base, altura);
					System.out.print("\n" + R + ".\n\n\n");
				}
				
				// C�rculo
				else if(op == 3){
					int raio = 0;
					System.out.print("Digite o valor do raio: ");
					raio = recebeEntrada(aux);
					
					Circulo C = new Circulo(cor, aux_boolean, raio);
					System.out.print("\n" + C + ".\n\n\n");
				}
				
		}
	}
	
	public static int recebeEntrada(boolean aux) {
		int valor = 0;
		while(aux) {
			try{
				valor = EntradaTeclado.leInt();
				if(valor <= 0) System.out.print("Digite um valor positivo e diferente de zero: ");
				else aux = false;
				
			} catch(Exception e) {
				System.out.print("Por favor, digite um n�mero: ");
			}
		}
		return valor;
	}
}


