
public class ContaPoupanca extends ContaBancaria {
private int vencimento;
	
	public ContaPoupanca(String n, int num, int dia) {
		super(n, num);
		vencimento = dia;
	}

	public int getVencimento() {
		return vencimento;
	}

	public void setVencimento(int vencimento) {
		this.vencimento = vencimento;
	}

	public void atualiza(double taxa) {
		double s = getSaldo();
		setSaldo(s * (1.0 + taxa));
	}
	
}
