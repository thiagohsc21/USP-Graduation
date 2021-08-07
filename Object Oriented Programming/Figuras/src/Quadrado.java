
/* Subclasse da classe Figuras*/
public class Quadrado extends Figuras{

	private double lado;
	
	/* Construtor */
	public Quadrado(String cor, boolean preenchida, double l) {
		super(cor, preenchida);
		lado = l;
	}	
	
	/* Getters */
	public double getLado() {
		return lado;
	}
	
	/* Setters */
	public void setLado(double l) {
		lado = l;
	}
	
	/* Area = l * l */
	public double areaQuadrado() {
		return getLado() * getLado();
	}
	
	/* Perimetro = 4 * l */
	public double perimetroQuadrado() {
		return 4 * getLado();
	}
	
	/* Retorna a Área e Perímetro */
	public String toString() {
		
		String aux;
		
		if(getPreenchida() == true) {
			aux = "preenchido com a cor " + getCor();
		}
		else aux = "com a borda na cor " + getCor();
		
		// preenchido com a cor tal, nao preenchido com a cor tal
		return "A área do seu quadrado " +  aux + " é igual a " + areaQuadrado() + " e seu perímetro vale " + perimetroQuadrado();
	}
}
