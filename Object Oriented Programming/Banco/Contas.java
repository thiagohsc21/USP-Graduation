/**
 * Essa classe implementa alguns métodos para manipular as contas bancárias.
 * @author delamaro
 *
 */
public class Contas {

	/**
	 * Array para armazenar as contas poupança
	 */
	private ContaPoupanca contasP[];
	/** 
	 * Numero de posicoes ocupadas no array
	 */
	private int nContasP;
	
	/**
	 * Array para armazenar as contas especiais
	 */
	private ContaEspecial contasE[];
	/** 
	 * Numero de posicoes ocupadas no array
	 */
	private int nContasE;
	
	
	/**
	 * Conatrutor. Cria os arrays para armazenar as contas e inicializa os contadores.
	 */
	public Contas() {
		contasP = new ContaPoupanca[100];
		contasE = new ContaEspecial[100];
		nContasP = 0;
		nContasE = 0;
	}

	
	/**
	 * Método principal. Implementa um laço para relizar as operacoes definidas.
	 * O numero da opcao eh lida do teclado.
	 * 
	 * @param args
	 * @throws Exception
	 */
	public static void main(String[] args) throws Exception {
		int op = 0;
		Contas ct = new Contas();
		
		while (true) {
			op = ct.leOpcao();
			switch (op)
			{
			case 1: 
				System.out.println("Numero da conta: ");
				int conta = EntradaTeclado.leInt();
				System.out.println("Nome do correntista: ");
				String s = EntradaTeclado.leString();
				System.out.println("Dia de vencimento: ");
				int dia = EntradaTeclado.leInt();
				ContaPoupanca cp = new ContaPoupanca(s, conta, dia);
				ct.add(cp);
				System.out.println("************ Conta criada.**************");
				break;
				
			case 2: 
				System.out.println("Numero da conta: ");
				conta = EntradaTeclado.leInt();
				System.out.println("Nome do correntista: ");
				s = EntradaTeclado.leString();
				System.out.println("Limite de saque: ");
				double limite = EntradaTeclado.leDouble();
				ContaEspecial ce = new ContaEspecial(s, conta, limite);
				ct.add(ce);
				System.out.println("************ Conta criada.**************");
				break;

			case 3:
				System.out.println("Numero da conta: ");
				conta = EntradaTeclado.leInt();
				System.out.println("Valor a sacar: ");
				double valor = EntradaTeclado.leDouble();
				cp = ct.procuraP(conta);
				if ( cp != null ) {
					try {
						cp.saca(valor);
						System.out.println("****************** Saque realizado ***********");
					} catch (Exception e) {
						System.out.println("****************** Saque não realizado ***********");
						System.out.println(e.getMessage());
					}
				}
				else {
					ce = ct.procuraE(conta);
					if (ce == null) {
						System.out.println("************* Conta não existe **************");
						break;
					}
					try {
						ce.saca(valor);
						System.out.println("****************** Saque realizado ***********");
					} catch (Exception e) {
						System.out.println("****************** Saque não realizado ***********");
						System.out.println(e.getMessage());
					}
					
				}
				break;

			case 4:
				System.out.println("Numero da conta: ");
				conta = EntradaTeclado.leInt();
				System.out.println("Valor a depositar: ");
				valor = EntradaTeclado.leDouble();
				cp = ct.procuraP(conta);
				if ( cp != null ) {
					cp.deposita(valor);
					System.out.println("****************** Depósito realizado ***********");
				}
				else {
					ce = ct.procuraE(conta);
					if (ce == null ) {
						System.out.println("************* Conta não existe **************");
						break;
					}
					ce.deposita(valor);
					System.out.println("****************** Depósito realizado ***********");
				}
				break;

			case 6: 
				ct.printSaldos();
				break;

			case 5:
				System.out.println("Qual o valor da taxa? ");
				double tx = EntradaTeclado.leDouble();
				ct.atualizaPoupança(tx);
				System.out.println("Saldos atualizados");
				break;

			case 7:
				System.out.println("Terminando o programa....");
				return;
			}
			
			System.out.println("Digite ENTER para continuar");
			EntradaTeclado.leString();
			System.out.println("\n\n");
		}

	}

	/**
	 * Mostra o menu e lê a opcao desejada. Se um valor invalido for digitado, 
	 * pede ao usuario que digite novamente
	 * @return o numero da opcao escolhida
	 */
	private int leOpcao() {
        System.out.println("1) Criar poupança\n2) Criar conta especial\n3) Realizar saque\n4) Realizar deposito\n"
        		+ "5) Atualizar poupanças\n6) Mostrar saldos\n7) Sair");
        int k = -1;
        while (true)
        {
        	System.out.println("Digite a opção desejada ===> ");
        	try {
        		k = EntradaTeclado.leInt();
        		if ( k > 0 && k < 8 )
        			return k;
        	}
        	catch (Exception e) {
        		;
        	}
        }
	}

	/**
	 * Adiciona uma conta poupanca no array correspondente
	 * @param cb eh um objeto ContaPoupanca que foi criada e vai ser inserida no array
	 */
	private void add(ContaPoupanca cb) {
		contasP[nContasP++] = cb;		
	}
	
	/**
	 * Adiciona uma conta especial no array correspondente
	 * @param cb eh um objeto ContaEspecial que foi criada e vai ser inserida no array
	 */
	private void add(ContaEspecial cb) {
		contasE[nContasE++] = cb;		
	}

	/**
	 * Percorre os dois arrays de contas e para cada conta presente, mostra o numero o 
	 * nome do titular e o saldo.
	 */
	private void printSaldos() {
		for (ContaPoupanca ctb : contasP)
		{
			if ( ctb == null ) break;
			System.out.println("Numero da conta poupança:" + ctb.getNumConta());
			System.out.println("Titular: " + ctb.getNomeCliente());
			System.out.println("Saldo: " + ctb.getSaldo());
			System.out.println();
		}

		for (ContaEspecial ctb : contasE)
		{
			if ( ctb == null ) break;
			System.out.println("Numero da conta especial:" + ctb.getNumConta());
			System.out.println("Titular: " + ctb.getNomeCliente());
			System.out.println("Saldo: " + ctb.getSaldo());
			System.out.println();
		}
	}

	/**
	 * Percorre o array de contas poupanca e atualiza o saldo corrente, utilizando a taxa.
	 * @param tx valor da taxa a usar para atualizar poupanca. Por exemplo, 0.10 significa que 
	 * o saldo deve aumentar 10%
	 */
	private void atualizaPoupança(double tx) {
		for (ContaPoupanca ctb : contasP)
		{
			if ( ctb == null ) break;

			ctb.atualiza(tx);
		}
	}

	/** 
	 * Procura uma conta no array de poupancas
	 * @param conta numero da conta a procurar
	 * @return se achou a conta, retorna o objeto que esta no array, para aquela conta.
	 * Se nao achar, retorna null.
	 */
	private ContaPoupanca procuraP(int conta) {
		for (ContaPoupanca ctb: contasP )
		{
			if ( ctb == null ) break;

			if (conta == ctb.getNumConta())
				return ctb;
		}
		return null;
	}

	/** 
	 * Procura uma conta no array de contas especiais
	 * @param conta numero da conta a procurar
	 * @return se achou a conta, retorna o objeto que esta no array, para aquela conta.
	 * Se nao achar, retorna null.
	 */
	private ContaEspecial procuraE(int conta) {
		for (ContaEspecial ctb: contasE )
		{
			if ( ctb == null ) break;

			if (conta == ctb.getNumConta())
				return ctb;
		}
		return null;
	}

}
