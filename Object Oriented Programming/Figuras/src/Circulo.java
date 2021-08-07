
/* Subclasse da classe Figuras*/
public class Circulo extends Figuras{
		
	private double raio;
	
	/* Construtor */
	public Circulo(String cor, boolean preenchida, double r) {
		super(cor, preenchida);
		raio = r;
	}
	
	/* Getters */
	public double getRaio() {
		return raio;
	}
	
	/* Setters */
	public void setRaio(double r) {
		raio = r;
	}
	
	/* Area = pi * r^2 */
	public double areaCirculo() {
		return 3.14159 * getRaio() * getRaio();
	}
	
	/* Perimetro = 2 * pi * r */
	public double perimetroCirculo() {
		return 2 * 3.14159 * getRaio();
	}
	
	/* Retorna a Área e Perímetro */
	public String toString() {
		
		String aux;
		
		if(getPreenchida() == true) {
			aux = "preenchido com a cor " + getCor();
		}
		else aux = "com a borda na cor " + getCor();
		
		// preenchido com a cor tal, nao preenchido com a cor tal
		return "A área do seu círculo " +  aux + " é igual a " + areaCirculo() + " e seu perímetro vale " + perimetroCirculo();
	}
}
