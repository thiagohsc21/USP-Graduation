import java.io.IOException;

// FALTA ADICIONAR PRODUTOS E REMOVER PRODUTOS

public class Main {
	
	public static void main(String[] args) throws IOException {
		
		Lojas loja = new Lojas();
		int op = 0;
		
		while(op != 5) {
			
			System.out.print("Bem vindo(a) ao sistema de gerenciamento da loja XYZ.\n\n" + 
					"1) Adicionar Produtos\n2) Buscar Produtos\n3) Comprar Produtos\n4) Listar Produtos no Estoque\n5) Encerrar\n\n" +
					"Acima temos todas as opções disponíveis, digite o número associado a desejada: ");
			
			boolean aux = true;
			int escolha = 0;
			while(aux) {
				try{
					escolha = EntradaTeclado.leInt();
					if(escolha < 1 || escolha > 6) System.out.print("Por favor, digite um valor entre 1 e 5: ");
					else aux = false;
					
				} catch(Exception e) {
					System.out.print("Por favor, digite um valor entre 1 e 5: ");
				}
			}
			
			if(escolha == 5) {
				System.out.print("\nFim do programa.");
				break;
			} else op = escolha;
			
			// Adiciona Produtos
			if(op == 1) {
				
				System.out.print("\nDigite a quantidade de produtos que deseja adicionar: ");
				int quantidadeProd = recebeEntrada(!aux, 1);
				
				System.out.print("Digite o tipo do produto (1 = Livro, 2 = CD ou 3 = DVD): ");
				int opcaoProduto = recebeEntrada(!aux, 2);

				String autorProduto, nomeProduto, codigoBarras, tipoProduto;
				
				if(opcaoProduto == 1) {
					System.out.print("Digite o título do Livro: ");
					nomeProduto = EntradaTeclado.leString();
					
					System.out.print("Digite o autor do livro " + nomeProduto + ": ");
					autorProduto = EntradaTeclado.leString();

					System.out.print("Digite o código de barras do livro: ");
					codigoBarras = EntradaTeclado.leString();
					
					tipoProduto = "Livro";
					
					Livros p = new Livros(codigoBarras, tipoProduto, nomeProduto, quantidadeProd, autorProduto); 
					loja.adicionaProd((Livros) p);
				}
				
				else if(opcaoProduto == 2) {
					System.out.print("Digite o nome do álbum do CD: ");
					nomeProduto = EntradaTeclado.leString();
					
					System.out.print("Digite o nome da banda criadora do álbum " + nomeProduto + ": ");
					autorProduto = EntradaTeclado.leString();

					System.out.print("Digite o código de barras do CD: ");
					codigoBarras = EntradaTeclado.leString();
					
					tipoProduto = "CD";
					
					CD p = new CD(codigoBarras, tipoProduto, nomeProduto, quantidadeProd, autorProduto); 
					loja.adicionaProd((CD) p);
				}
				
				else {
					System.out.print("Digite o nome do vídeo DVD: ");
					nomeProduto = EntradaTeclado.leString();
					
					System.out.print("Digite o nome da produtora criadora do DVD " + nomeProduto + ": ");
					autorProduto = EntradaTeclado.leString();
					
					System.out.print("Digite o código de barras do DVD: ");
					codigoBarras = EntradaTeclado.leString();
					
					tipoProduto = "DVD";
					
					DVD p = new DVD(codigoBarras, tipoProduto, nomeProduto, quantidadeProd, autorProduto); 
					loja.adicionaProd((DVD) p);
				}
				
				System.out.print("\nProduto(s) adicionado(s) com sucesso!\n\n");
				
			}
			
			// Busca Produtos
			else if(op == 2) {
				
				System.out.print("\nDigite como deseja buscar esse produto (1 = Código de Barras e 2 = Nome Produto): ");
				int modoBusca = recebeEntrada(!aux, 3);
				
				String informacaoBuscada;
				Produtos informacoesCompletas;
				
				if(modoBusca == 1) {
					System.out.print("Digite o código do produto: ");
					informacaoBuscada = EntradaTeclado.leString();
					informacoesCompletas = loja.procuraProdCod(informacaoBuscada);
				}
				
				else {
					System.out.print("Digite o nome do produto: ");
					informacaoBuscada = EntradaTeclado.leString();
					informacoesCompletas = loja.procuraProdNome(informacaoBuscada);
				}
				
				if(informacoesCompletas == null) System.out.print("\nProduto não encontrado!\n\n");
				
				else{
					System.out.print("\nProduto encontrado:\n");
					if(informacoesCompletas instanceof Livros) System.out.print((Livros) informacoesCompletas);
					else if(informacoesCompletas instanceof CD) System.out.print((CD) informacoesCompletas);
					else if(informacoesCompletas instanceof DVD) System.out.print((DVD) informacoesCompletas);
				}
			}
			
			// Compra Produtos
			else if(op == 3) {
				
				System.out.print("\nDigite o código do produto procurado: ");
				String nomeProd = EntradaTeclado.leString();
				Produtos resultadoBusca = loja.procuraProdCod(nomeProd);
				
				if(resultadoBusca != null) {
					loja.printaInformacoes(resultadoBusca);
					
					int qntDesejada = 0;
					System.out.print("Digite a quantidade desejada: ");
					while(!aux) {
						try {
							qntDesejada = EntradaTeclado.leInt();
							if(qntDesejada > resultadoBusca.getQnt() || qntDesejada < 0) System.out.print("Quantidade inválida, digite novamente: ");
							else aux = true;
						} catch(Exception e) {
							System.out.print("Quantidade inválida, digite novamente: ");
						}
					}
					
					loja.vendaProdutos(resultadoBusca, qntDesejada);	
					System.out.print("\nCompra realizada com sucesso!\n\n");
				}
				
				else {
					loja.printaInformacoes(resultadoBusca);
				}
				
			}
			
			// Lista Produtos no Estoque
			else if(op == 4) {
				loja.listaProdutos();
			}
		}

	}
	
	/* Funções de Recebimento de Entradas com Tratamento de Erros */
	public static int recebeEntrada(boolean aux, int op) {
		int valor = 0;
		if(op == 1) {
			while(aux) {
				try{
					valor = EntradaTeclado.leInt();
					if(valor <= 0) System.out.print("Digite um valor positivo e diferente de zero: ");
					else aux = false;
					
				} catch(Exception e) {
					System.out.print("Por favor, digite um número: ");
				}
			}
		}
			
		if(op == 2) {
			while(aux) {
				try{
					valor = EntradaTeclado.leInt();
					if(valor < 1 || valor > 3) System.out.print("Por favor, digite um valor entre 1 e 3: ");
					else aux = false;
					
				} catch(Exception e) {
					System.out.print("Por favor, digite um valor entre 1 e 3: ");
				}
			}
		}
		
		if(op == 3) {
			while(aux) {
				try{
					valor = EntradaTeclado.leInt();
					if(valor < 1 || valor > 2) System.out.print("Por favor, digite um valor entre 1 e 2: ");
					else aux = false;
					
				} catch(Exception e) {
					System.out.print("Por favor, digite um valor entre 1 e 2: ");
				}
			}
		}
		return valor;
	}
	
}
