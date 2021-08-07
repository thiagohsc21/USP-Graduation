
/* Classe que representa uma pessoa, podendo ser física ou jurídica */
public class Pessoa {
	
	private String nome;
	private String endereco;
	private String email;
	
	/* Construtor da Classe Pessoa */
	public Pessoa(String n, String e, String em) {
		nome = n;
		endereco = e;
		email = em;
	}
	
	/* Getters */
	public String getNome() {
		return nome;
	}
	
	public String getEnd() {
		return endereco;
	}
	
	public String getEmail() {
		return email;
	}
	
	/* Setters */
	public void setNome(String n) {
		nome = n;
	}
	
	public void setEnd(String e) {
		endereco = e;
	}
	
	public void setEmail(String em) {
		email = em;
	}
	
	public String toString() {
		return "\nNome: " + nome + "\nEndereço: " + endereco + "\nEmail: " + email;
	}
	
}
