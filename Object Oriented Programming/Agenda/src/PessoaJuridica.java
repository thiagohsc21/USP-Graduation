
public class PessoaJuridica extends Pessoa {
	
	private String cnpj;
	private String inscricaoEstadual;
	private String razaoSocial;
	
	/* Construtor */
	public PessoaJuridica(String nome, String endereco, String email, String c, String i, String r) {
		super(nome, endereco, email);
		cnpj = c;
		inscricaoEstadual = i;
		razaoSocial = r;
	}
	
	/* Getters */
	public String getCnpj() {
		return cnpj;
	}
	
	public String getInscricaoEstadual() {
		return inscricaoEstadual;
	}
	
	public String getRazaoSocial() {
		return razaoSocial;
	}
	
	/* Setters */
	public void setCnpj(String c) {
		cnpj = c;
	}
	
	public void setInscricaoEstadual(String i) {
		inscricaoEstadual = i;
	}
	
	public void setRazaoSocial(String r) {
		razaoSocial = r;
	}
	
	public String toString() {
		return super.toString() + "\nCnpj: " + cnpj + "\nInscricao Estadual: " + inscricaoEstadual + "\nRazao Social: " + razaoSocial + "\n";
	}
	
}
