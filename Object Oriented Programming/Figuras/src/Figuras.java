
/* Classe para uma figura qualquer*/
public class Figuras {

	private String corFigura;
	private boolean corPreenchida = false;
	
	/* Construtor */
	public Figuras(String cor, boolean preenchida) {
		corFigura = cor;
		corPreenchida = preenchida;
	}
	
	/* Getters */
	public String getCor() {
		return corFigura;
	}
	
	public boolean getPreenchida() {
		return corPreenchida;
	}
	
	/* Setters */
	public void setCor(String cor) {
		corFigura = cor;
	}
	
	public void setPreenchida(boolean b) {
		corPreenchida = b;
	}
		
}
