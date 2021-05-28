import java.lang.Math;

public class Ex2 {

	public static void main(String[] args) {
		
		boolean var = true;
		double a=0, b=0, c=0;
		
		while(var) {
			try {
				System.out.printf("Digite o primeiro coeficiente: ");
				a = EntradaTeclado.leDouble();
				var = false;
			} catch(Exception e) {
				System.out.printf("Erro no recebimento do primeiro coeficiente.\n");
			}
		}
		
		while(!var) {
			try {
				System.out.printf("Digite o segundo coeficiente: ");
				b = EntradaTeclado.leDouble();
				var = true;
			} catch(Exception e) {
				System.out.printf("Erro no recebimento do segundo coeficiente.\n");
			}
		}
		
		while(var) {
			try {
				System.out.printf("Digite o terceiro coeficiente: ");
				c = EntradaTeclado.leDouble();
				var = false;
			} catch(Exception e) {
				System.out.printf("Erro no recebimento do terceiro coeficiente.\n");
			}
		}
		
		System.out.printf("Equação dada: %fx + %fy + %f = 0\n", a, b, c);
		
		double delta = (b*b) - (4*a*c);
		if(delta < 0) {
			System.out.printf("A equação dada não possui raízes reais.\n");
			return;
		}
		delta = Math.sqrt(delta);
		double x1 = (delta - b)/(2*a);
		double x2 = (-1 * (b + delta))/(2*a);
		
		System.out.printf("As soluções da equação são x1 = %f e x2 = %f", x1, x2);
	}

}
