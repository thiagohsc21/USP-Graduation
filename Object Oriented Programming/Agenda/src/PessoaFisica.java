
public class PessoaFisica extends Pessoa {
	
	private String cpf;
	private String estadoCivil;
	private String nascimento;

	/* Construtor */
	public PessoaFisica(String nome, String endereco, String email, String c, String es, String nasc) {
		super(nome, endereco, email);
		cpf = c;
		estadoCivil = es;
		nascimento = nasc;
	}
	
	/* Getters */
	public String getCpf() {
		return cpf;
	}
	
	public String getEstadoCivil() {
		return estadoCivil;
	}
	
	public String getNascimento() {
		return nascimento;
	}
	
	/* Setters */
	public void setCpf(String c) {
		cpf = c;
	}
	
	public void setEstadoCivil(String e) {
		estadoCivil = e;
	}
	
	public void setNascimento(String n) {
		nascimento = n;
	}
	
	public String toString() {
		return super.toString() + "\nCpf: " + cpf + "\nEstado Civil: " + estadoCivil + "\nData de Nascimento: " + nascimento + "\n";
	}
}
