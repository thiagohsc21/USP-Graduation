
/* Superclasse que representa todos os produtos da loja */
public class Produtos {

	private String codigoBarras;
	private String tipoProduto; /* Livro, CD ou DVD */
	private String informacoesProduto; /* T�tulo Livro, Nome �lbum Musical ou Nome V�deo) */
	private int quantidadeItens;
	
	/* Construtor */
	public Produtos(String c, String t, String i, int q) {
		setCod(c);
		setTipo(t);
		setInfo(i);
		setQnt(q);
	}
	
	/* Getters */
	public String getCod() {
		return codigoBarras;
	}
	
	public String getTipo() {
		return tipoProduto;
	}
	
	public int getQnt() {
		return quantidadeItens;
	}
	
	public String getInfo() {
		return informacoesProduto;
	}
	
	/* Setters */
	public void setCod(String c) {
		codigoBarras = c;
	}
	
	public void setTipo(String t) {
		tipoProduto = t;
	}
	
	public void setQnt(int q) {
		quantidadeItens = q;
	}
	
	public void setInfo(String i) {
		informacoesProduto = i;
	}
	
	public String toString() {
		return "Nome: " + getInfo() + "\nC�digo Barras: " + getCod() + "\nQuantidade: " + getQnt();
	}
}
