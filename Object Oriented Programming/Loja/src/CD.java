
/* Subclasse da classe Produtos */
public class CD extends Produtos{

	private String nomeBanda;
	
	/* Construtor */
	public CD(String c, String t, String i, int q, String n) {
		super(c, t, i, q);
		setAutor(n);
	}
	
	/* Getters */
	public String getAutor() {
		return nomeBanda;
	}
	
	/* Setters */
	public void setAutor(String n) {
		nomeBanda = n;
	}
	
	public String toString() {
		return super.toString() + "\nBanda: " + getAutor() + "\n\n";
	}
	
}
