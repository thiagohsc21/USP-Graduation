
/* Subclasse da classe Produtos */
public class DVD extends Produtos{
	
	private String nomeProdutora;
	
	/* Construtor */
	public DVD(String c, String t, String i, int q, String n) {
		super(c, t, i, q);
		setAutor(n);
	}
	
	/* Getters */
	public String getAutor() {
		return nomeProdutora;
	}
	
	/* Setters */
	public void setAutor(String n) {
		nomeProdutora = n;
	}

	public String toString() {
		return super.toString() + "\nProdutora: " + getAutor() + "\n\n";
	}
}
