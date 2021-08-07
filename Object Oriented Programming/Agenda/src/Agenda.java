
public class Agenda {
	
	private Pessoa contatos[];
	private int numContatos;

	/* Construtor */
	public Agenda() {
		contatos = new Pessoa[100];
		numContatos = 0;
	}
	
	/* Getters */
	public int getQnt() {
		return numContatos; 
	}
	
	public Pessoa[] getContatos() {
		return contatos; 
	}
	
	/* Setters */
	public void setQnt(int k) {
		numContatos = k;
	}
	
	public void setContato(Pessoa[] p) {
		contatos = p;
	}
	
	/* Adiciona pessoa na agenda */
	public void addPessoa(Pessoa novoContato) {
		
		/* Caso tenhamos um vetor de contatos cheio, alocamos mais espaço */
		if(getContatos().length == getQnt()) {
			Pessoa[] novoVetor = new Pessoa[getQnt() + 10];
			
			/* Copia um intervalo de elementos de um Array a partir do índice de origem especificado e cola-os em outro */
			System.arraycopy(contatos, 0, novoVetor, 0, contatos.length);
			setContato(novoVetor);
		}
		
		contatos[getQnt()] = novoContato;
		setQnt(getQnt()+1);
	}
	
	
	/* Remove pessoa da agenda */
	public void removePessoa(Pessoa contatoRemovido) {
	
		int i = 0;
		
		/* Contato a ser removido é uma pessoa física */
		if(contatoRemovido instanceof PessoaFisica) {
			/* Busca a posicao da PF na agenda e seta como nulo */
			for(i = 0 ; i < getContatos().length ; i++) {
				if(contatos[i] != null && contatos[i] instanceof PessoaFisica && (((PessoaFisica) contatoRemovido).getCpf()).equals(((PessoaFisica) contatos[i]).getCpf()))
					contatos[i] = null;
			}
		}
		
		/* Contato a ser removido é uma pessoa jurídica */
		else if(contatoRemovido instanceof PessoaJuridica){
			/* Busca a posicao da PJ na agenda e seta como nulo */
			for(i = 0 ; i <  getContatos().length ; i++) {
				if(contatos[i] != null && contatos[i] instanceof PessoaJuridica && (((PessoaJuridica) contatoRemovido).getCnpj()).equals(((PessoaJuridica) contatos[i]).getCnpj()))
					contatos[i] = null;
			}
		}

		/* Faz um shift no array todo */
		for(int j = i ; j < (getQnt()-i-1) ; j++) {
			contatos[j] = contatos[j+1];
			contatos[j+1] = null;		
		}
		
		setQnt(getQnt() - 1);
	}
	
	/* Pesquisa por nome, cpf ou cnpj */
	public Pessoa pesquisaPessoa(String informacaoContato, int modoBusca) {
		
		/* Busca pelo nome */
		if(modoBusca == 1) {
			for(int i  = 0 ; i < getContatos().length ; i++) {
				if(contatos[i] != null && contatos[i].getNome().equals(informacaoContato)) return contatos[i];
			}
		}
		
		/* Busca pelo CPF */
		else if(modoBusca == 2){
			for(int i  = 0 ; i < getContatos().length ; i++) {
				if(contatos[i] != null && contatos[i] instanceof PessoaFisica && (((PessoaFisica) contatos[i]).getCpf()).equals(informacaoContato)) 
					return contatos[i];
			}
		}
		
		/* Busca pelo CNPJ */
		else if(modoBusca == 3) {
			for(int i  = 0 ; i < getContatos().length ; i++) {
				if(contatos[i] != null && contatos[i] instanceof PessoaJuridica && (((PessoaJuridica) contatos[i]).getCnpj()).equals(informacaoContato))
					return contatos[i];
			}
		}
		
		return null;
	}
	
	/* Ordena os contatos em ordem crescente de CPF/CNPJ e todas as pessoas físicas (PF) aparecem antes das jurídicas (PJ) */
	public void ordenaContatos() {
		
		Pessoa[] vetorCpf = new Pessoa[getContatos().length];
		Pessoa[] vetorCnpj = new Pessoa[getContatos().length];
		
		/* Separa em dois vetores as PF e PJ - O(N)*/
		int j = 0, k = 0;
		for(int i = 0 ; i < getContatos().length ; i++) {
			if(contatos[i] != null && contatos[i] instanceof PessoaJuridica) vetorCnpj[j++] = contatos[i];
			else if(contatos[i] != null & contatos[i] instanceof PessoaFisica) vetorCpf[k++] = contatos[i];
		}
		
		/* Ordena cada um desses vetores - Como uma agenda não costuma ter mais de 100k de contatos, Bubble Sort é uma boa alternativa */
		for(int i = 0 ; i < k ; i++) {
			for(int p = 0 ; p < k-1 ; p++) {
				
				String cpf1 = ((PessoaFisica) vetorCpf[p]).getCpf();
				String cpf2 = ((PessoaFisica) vetorCpf[p+1]).getCpf();
				int num1 = Integer.parseInt(cpf1);
				int num2 = Integer.parseInt(cpf2);
				
				if(num1 > num2) {
					Pessoa aux = vetorCpf[p];
					vetorCpf[p] = vetorCpf[p+1];
					vetorCpf[p+1] = aux;
				}
			}	
		}
		
		for(int i = 0 ; i < j ; i++) {
			for(int p = 0 ; p < j-1 ; p++) {
				
				String cnpj1 = ((PessoaJuridica) vetorCnpj[p]).getCnpj();
				String cnpj2 = ((PessoaJuridica) vetorCnpj[p+1]).getCnpj();
				int num1 = Integer.parseInt(cnpj1);
				int num2 = Integer.parseInt(cnpj2);
				
				if(num1 > num2) {
					Pessoa aux = vetorCnpj[p];
					vetorCnpj[p] = vetorCnpj[p+1];
					vetorCnpj[p+1] = aux;
				}
			}
		}
		
		for(int i = 0; i < k; i++) contatos[i] = vetorCpf[i];
		for(int i = k, t = 0; i < (k+j); i++, t++) contatos[i] = vetorCnpj[t];
	
	}
	
	/* Lista todos os contatos da agenda */
	public void listaContatos() {
		
		System.out.print("\nContatos: \n----------------------------------------------");
		for(int i = 0 ; i < getContatos().length ; i++) {
			if(contatos[i] != null && contatos[i] instanceof PessoaFisica) {
				System.out.print((PessoaFisica) contatos[i]);
			}
			if(contatos[i] != null && contatos[i] instanceof PessoaJuridica) {
				System.out.print((PessoaJuridica) contatos[i]);
			}
		}
		System.out.print("----------------------------------------------\nFim da agenda.\n\n");
		
	}
}
