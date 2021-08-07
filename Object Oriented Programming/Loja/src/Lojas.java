
/* Classe para gerenciamento dos produtos da Loja */
public class Lojas {

	private Produtos produtosLoja[];
	private int qntProdutos;
	
	/* Construtor */
	public Lojas() {
		qntProdutos = 0;
		produtosLoja = new Produtos[100];
	}
	
	/* Getters */
	public int getQnt() {
		return qntProdutos;
	}
	
	/* Setters */
	public void setQnt(int q) {
		qntProdutos = q;
	}
	
	public Produtos procuraProdCod(String s) {
		for(int i  = 0 ; i < produtosLoja.length ; i++) {
			if(produtosLoja[i] != null && produtosLoja[i].getCod().equals(s)) return produtosLoja[i];
		}
		return null;
	}
	
	
	public Produtos procuraProdNome(String s) {
		for(int i  = 0 ; i < produtosLoja.length ; i++) {
			if(produtosLoja[i] != null && produtosLoja[i].getInfo().equals(s)) return produtosLoja[i];
		}
		return null;
	}
	
	public void printaInformacoes(Produtos p) {
		if(p != null) System.out.print("\nO produto consta no estoque! Temos atualmente " + p.getQnt() + " unidades.\n\n");
		else System.out.print("\nProduto não encontrado!\n\n");
	}
	
	public void vendaProdutos(Produtos produtoBuscado, int qntDesejada) {
		
		/* Se compraram menos produtos do que possuímos, atualiza o valor */
		if(produtoBuscado.getQnt() > qntDesejada) {
			produtoBuscado.setQnt(produtoBuscado.getQnt() - qntDesejada);
		}
		/* Caso contrário, como tratei o caso de ser menor na main, resta ser igual e nesse caso, removemos do vetor de produtos */
		else {
			int i = 0;

			/* Busca a posicao do produtoBuscado nos produtos da loja */
			for(i = 0 ; i < produtosLoja.length ; i++) {
				if(produtosLoja[i] != null && produtoBuscado.getInfo().equals(produtosLoja[i].getInfo())) {
					produtosLoja[i] = null;
				}
			}

			/* Faz um shift no array todo */
			for(int j = i ; j < (getQnt()-i-1) ; j++) {
				produtosLoja[j] = produtosLoja[j+1];
				produtosLoja[j+1] = null;
			}
			
			setQnt(getQnt() - 1);
		}
		
	}
	
	/* Função de Adicionar Produtos */
	public void adicionaProd (Produtos novoProduto) {
		
		/* Caso tenhamos um vetor de produtos cheio, alocamos mais espaço */
		if(produtosLoja.length == getQnt()) {
			Produtos[] novoVetor = new Produtos[getQnt() + 10];
			
			/* Copia um intervalo de elementos de um Array a partir do índice de origem especificado e cola-os em outro */
			System.arraycopy(produtosLoja, 0, novoVetor, 0, produtosLoja.length);
			produtosLoja = novoVetor;
		}
			
		/* Verifica se o produto já está na base de dados */
		Produtos resultadoBusca = procuraProdCod(novoProduto.getCod());
		
		/* Não consta no estoque */
		if(resultadoBusca == null) {
			produtosLoja[getQnt()] = novoProduto;
			setQnt(getQnt()+1);
		}
		/* Caso contrário adiciona nova quantidade */
		else {
			resultadoBusca.setQnt(resultadoBusca.getQnt() + novoProduto.getQnt());
		}
	
	}
	
	public void listaProdutos() {
		
		int qntDvd = 0, qntCd = 0, qntLivro = 0;
		
		System.out.print("\nTodos os Livros do estoque: \n-------------------------------------------------\n");
		for(int i = 0 ; i < produtosLoja.length ; i++) {
			if(produtosLoja[i] != null && produtosLoja[i] instanceof Livros) {
				System.out.print((Livros) produtosLoja[i]);
				qntLivro++;
			}
		}
		System.out.print("Total Livros = " + qntLivro+ "." + "\n-------------------------------------------------\n\n");
		
		System.out.print("Todos os CDs do estoque: \n-------------------------------------------------\n");
		for(int i = 0 ; i < produtosLoja.length ; i++) {
			if(produtosLoja[i] != null && produtosLoja[i] instanceof CD) {
				System.out.print((CD) produtosLoja[i]);
				qntCd++;
			}
		}
		System.out.print("Total CDs = " + qntCd + "." + "\n-------------------------------------------------\n\n");
		
		System.out.print("Todos os DVDs do estoque: \n-------------------------------------------------\n");
		for(int i = 0 ; i < produtosLoja.length ; i++) {
			if(produtosLoja[i] != null && produtosLoja[i] instanceof DVD) {
				System.out.print((DVD) produtosLoja[i]);
				qntDvd++;
			}
		}
		System.out.print("Total DVDs = " + qntDvd + "." + "\n-------------------------------------------------\n\n");
		System.out.print("Fim do estoque!\n\n");
	}
	
}
