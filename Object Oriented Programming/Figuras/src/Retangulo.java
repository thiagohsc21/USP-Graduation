
/* Subclasse da classe Figuras*/
public class Retangulo extends Figuras{
	
	private double base;
	private double altura;
	
	/* Construtor */
	public Retangulo(String cor, boolean preenchida, double b, double a) {
		super(cor, preenchida);
		base = b;
		altura = a;
	}
	
	/* Getters */
	public double getBase() {
		return base;
	}
	
	public double getAltura() {
		return altura;
	}
	
	/* Setters */
	public void setBase(double b) {
		base = b;
	}
	
	public void setAltura(double a) {
		altura = a;
	}
	
	/* Area = base * altura */
	public double areaRetangulo() {
		return getBase() * getAltura();
	}
	
	/* Perímetro = 2 * base + 2 * altura */
	public double perimetroRetangulo() {
		return getBase() * 2 + getAltura() * 2;
	}
	
	/* Retorna a Área e Perímetro */
	public String toString() {
		
		String aux;
		
		if(getPreenchida() == true) {
			aux = "preenchido com a cor " + getCor();
		}
		else aux = "com a borda na cor " + getCor();
		
		// preenchido com a cor tal, nao preenchido com a cor tal
		return "A área do seu retângulo " +  aux + " é igual a " + areaRetangulo() + " e seu perímetro vale " + perimetroRetangulo();
	}

}
