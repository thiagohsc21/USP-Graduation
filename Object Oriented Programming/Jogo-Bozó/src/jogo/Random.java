package jogo;
import java.util.Calendar;

/** 
 * gerador simples de números aleatórios.
 * @author delamaro
 *
 */
public class Random {
	private long p = 2147483648l;
	private long m = 843314861;
	private long a = 453816693;
	
	private long xi;

/**
 * Retorna um número aleatório no intervalo (0,1[
 * @return o número gerado.
 */
	public double getRand() {
		xi = (a + m * xi) % p;
		double d = xi;
		return d / p;
	}
	
	/**
	 * Retorna um valor inteiro no intervalo (0,max[
	 * @param max O valor limite para a geração do número inteiro
	 * @return o número gerado
	 */
	public int getIntRand(int max)
	{
		double d = getRand() * max;
		return (int) d;
	}

	/**
	 * Permite alterar a semente de geração de números aleatórios. Supostamente deve ser chamada
	 * antes de iniciar a geração, mas se for chamado a qualquer instante, reseta o valor
	 * da semante
	 * @param semente o valor da nova semente de geração
	 */
	public void setSemente(int semente) {
       xi = semente;		
	}

	/**
	 * Construtor que permite criar o gerador, especificando o valor inicial da semente.
	 * @param k O valor inicial da semente.
	 */
	public Random(int k)
	{
		xi = k;
	}
	
	/**
	 * Construtor que usa uma semente aleatória, adquerida usando o método Calendar.getTimeInMillis().
	 */
	public Random() {
		xi = Calendar.getInstance().getTimeInMillis() % p;
	}
}
	