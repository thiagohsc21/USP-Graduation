public class Ex1 {

	public static void main(String[] args) {
		
		boolean var = true;
        double x = 0.0;
        
        while(var) {
	        try {
	        	System.out.printf("Digite o número para cálculo da raiz quadrada: ");
	            x = EntradaTeclado.leDouble();
	            if(x > 0) var = false;
	            else System.out.printf("Por favor, digite um número positivo.\n");
	        } catch(Exception e) {
	        	System.out.printf("Por favor, digite um double.\n");
	        }
        }
        
        double x0 = 1;
        while(!var) {
	        try {
	        	System.out.printf("Chute um número aproximado pra raiz de x: ");
	            x0 = EntradaTeclado.leDouble();
	            if(x0 > 0) var = true;
	            else System.out.printf("Por favor, digite um número positivo.\n");
	        } catch(Exception e) {
	        	System.out.printf("Por favor, digite um double.\n");
	        }
        }
        
        boolean ans = false;
        while(!ans) {
        	double xi = ((x0)+(x/x0))/2;
        	if(Math.abs(xi-x0) < 1e-8) {
        		System.out.printf("A raiz de %f é : %f", x, xi);
        		ans = true;
        	}
            x0 = xi;
        }
	}

}
