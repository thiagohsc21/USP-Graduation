import java.io.IOException;

/*
 * Exercício 2 - Implementar nova funcionalidade de Bubble Sort 
 * 1) separa o vetor criando um novo para cpf e um novo para cnpj
 * 2) ordenar cada um desses vetores separadamente
 * 3) copiar esses vetores para o vetor original
 */

public class GerenciaAgenda {

	public static void main(String[] args) throws IOException {
			
		int op = 0;
		Agenda ag = new Agenda();
		
		while(op != 6) {
			
			System.out.print("Bem vindo(a) ao sistema de gerenciamento da agenda.\n\n" + 
					"1) Adicionar Pessoa\n2) Buscar Pessoa\n3) Remover Pessoa\n4) Listar Pessoas na Agenda\n5) Ordenar Contatos\n6) Encerrar\n\n" +
					"Acima temos todas as opções disponíveis, digite o número associado a desejada: ");
			
			boolean aux = true;
			int escolha = 0;
			while(aux) {
				try{
					escolha = EntradaTeclado.leInt();
					if(escolha < 1 || escolha > 7) System.out.print("Por favor, digite um valor entre 1 e 6: ");
					else aux = false;
					
				} catch(Exception e) {
					System.out.print("Por favor, digite um valor entre 1 e 6: ");
				}
			}
			
			if(escolha == 6) {
				System.out.print("\nFim do programa.");
				break;
			} else op = escolha;
			
			// Adiciona Pessoas
			if(op == 1) {
				
				System.out.print("\nDigite o tipo de pessoa que deseja adicionar (1 = Pessoa Fisica e 2 = Pessoa Juridica): ");
				int tipoPessoa = recebeEntrada(!aux, 3);
				
				System.out.print("Digite o nome: ");
				String nomePessoa = EntradaTeclado.leString();
				
				System.out.print("Digite o endereço: ");
				String enderecoPessoa = EntradaTeclado.leString();

				System.out.print("Digite o email: ");
				String emailPessoa = EntradaTeclado.leString();
				
				if(tipoPessoa == 1) {
					
					System.out.print("Digite o CPF: ");
					String cpfPessoa = EntradaTeclado.leString();
					
					Pessoa resultadoBusca = ag.pesquisaPessoa(cpfPessoa, 2);
					if(resultadoBusca != null) {
						System.out.print("A pessoa associada a esse CPF já consta na base de dados!\n\n");
						while(resultadoBusca != null) {
							System.out.print("Digite novamente: ");
							cpfPessoa = EntradaTeclado.leString();
							resultadoBusca = ag.pesquisaPessoa(cpfPessoa, 2);
						}
					}
					
					System.out.print("Digite o estado civil: ");
					String estadoCivil = EntradaTeclado.leString();
					
					System.out.print("Digite a data de nascimento (exemplo: 21/07/1985): ");
					String nascimentoPessoa = EntradaTeclado.leString();
					
					PessoaFisica novoContato = new PessoaFisica(nomePessoa, enderecoPessoa, emailPessoa, cpfPessoa, estadoCivil, nascimentoPessoa);
					ag.addPessoa(novoContato);
				}
				
				else {
					System.out.print("Digite o CNPJ: ");
					String cnpjPessoa = EntradaTeclado.leString();
					
					Pessoa resultadoBusca = ag.pesquisaPessoa(cnpjPessoa, 3);
					if(resultadoBusca != null) {
						System.out.print("A empresa associada a esse CNPJ já consta na base de dados!\n\n");
						while(resultadoBusca != null) {
							System.out.print("Digite novamente: ");
							cnpjPessoa = EntradaTeclado.leString();
							resultadoBusca = ag.pesquisaPessoa(cnpjPessoa, 3);
						}
					}

					System.out.print("Digite a razão social: ");
					String razaoSocial = EntradaTeclado.leString();

					System.out.print("Digite a inscrição estadual: ");
					String inscricaoEstadual = EntradaTeclado.leString();
					
					PessoaJuridica novoContato = new PessoaJuridica(nomePessoa, enderecoPessoa, emailPessoa, cnpjPessoa, razaoSocial, inscricaoEstadual);
					ag.addPessoa(novoContato);
				}
			
				System.out.print("\nContato adicionado com sucesso!\n\n");
				
			}
			
			// Busca Pessoas
			else if(op == 2) {
				
				System.out.print("\nDigite como deseja buscar essa pessoa (1 = Nome, 2 = CPF e 3 = CNPJ): ");
				int modoBusca = recebeEntrada(!aux, 2);
				
				String informacaoBuscada;
				Pessoa informacoesCompletas;
				
				if(modoBusca == 1) {
					System.out.print("Digite o nome da pessoa: ");
					informacaoBuscada = EntradaTeclado.leString();
					
					informacoesCompletas = ag.pesquisaPessoa(informacaoBuscada, 1);
					if(informacoesCompletas != null && informacoesCompletas instanceof PessoaFisica)
						System.out.print("\nContato encontrado! Informações:" + (PessoaFisica) informacoesCompletas + "\n\n");
					else if(informacoesCompletas != null && informacoesCompletas instanceof PessoaJuridica)
						System.out.print("\nContato encontrado! Informações:" + (PessoaJuridica) informacoesCompletas + "\n\n");

				}
				
				else if(modoBusca == 2){
					System.out.print("Digite o CPF da pessoa: ");
					informacaoBuscada = EntradaTeclado.leString();
					
					informacoesCompletas = ag.pesquisaPessoa(informacaoBuscada, 2);
					if(informacoesCompletas != null) System.out.print("\nContato encontrado! Informações:" + (PessoaFisica) informacoesCompletas  + "\n\n");
				}
				
				else {
					System.out.print("Digite o CNPJ da pessoa: ");
					informacaoBuscada = EntradaTeclado.leString();
					
					informacoesCompletas = ag.pesquisaPessoa(informacaoBuscada, 3);
					if(informacoesCompletas != null) System.out.print("\nContato encontrado! Informações:" + (PessoaJuridica) informacoesCompletas + "\n\n");
				}
				
				if(informacoesCompletas == null) System.out.print("\nContato não encontrado!\n\n");
			}
			
			// Remove Pessoas
			else if(op == 3) {
				
				System.out.print("\nDigite o tipo de pessoa que deseja remover (1 = Pessoa Fisica e 2 = Pessoa Juridica): ");
				int tipoPessoa = recebeEntrada(!aux, 3);
				
				Pessoa resultadoBusca;
			
				if(tipoPessoa == 1) {
					System.out.print("\nDigite o CPF dessa pessoa: ");
					String cpfPessoa = EntradaTeclado.leString();
					resultadoBusca = ag.pesquisaPessoa(cpfPessoa, 2);
				}
				else {
					System.out.print("\nDigite o CNPJ dessa pessoa: ");
					String cnpjPessoa = EntradaTeclado.leString();
					resultadoBusca = ag.pesquisaPessoa(cnpjPessoa, 3);
				}
				
				if(resultadoBusca == null) System.out.print("A pessoa procurada não consta na agenda!\n\n");
				else {
					ag.removePessoa(resultadoBusca);
					System.out.print("Pessoa removida com sucesso!\n\n");
				}
			}
			
			// Lista Contatos na agenda
			else if(op == 4) {
				ag.listaContatos();
			}
			
			// Ordena Vetor
			else if(op == 5) {
				ag.ordenaContatos();
				System.out.print("Vetor ordenado com sucesso!\n\n");
			}
		}
	}
		
	/* Funções de Recebimento de Entradas com Tratamento de Erros */
	public static int recebeEntrada(boolean aux, int op) {
		int valor = 0;	
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
	
	

