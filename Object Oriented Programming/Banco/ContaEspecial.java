
public class ContaEspecial extends ContaBancaria {
private double limite;

	public ContaEspecial(String n, int num, double l) {
		super(n, num);
		limite = l;
	}
	
	@Override
	public void saca(double qto) {
		double s = getSaldo();
		if ( qto > s + limite )
			throw new IllegalArgumentException("Limite excedido para esse saque");
		setSaldo( s - qto );
	}

}
