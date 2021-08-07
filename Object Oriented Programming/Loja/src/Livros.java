
/* Subclasse da classe Produtos */
public class Livros extends Produtos{
	
	private String autorLivro;
	
	/* Construtor */
	public Livros(String c, String t, String i, int q, String a) {
		super(c, t, i, q);
		setAutor(a);
	}
	
	/* Getters */
	public String getAutor() {
		return autorLivro;
	}
	
	/* Setters */
	public void setAutor(String a) {
		autorLivro = a;
	}
	
	public String toString() {
		return super.toString() + "\nAutor: " + getAutor() + "\n\n";
	}

}
