import java.util.Scanner;

public class Tentarfazersemajudadeumaia {
    public static void main(String[] args) {
        System.out.println("Tentando fazer algo sem ajuda de uma IA.");

        try (Scanner scanner = new Scanner(System.in)) {
            System.out.print("Digite um número: ");
            int numero = scanner.nextInt();

            if (numero % 2 == 0) {
                System.out.println("O número " + numero + " é par.");
            } else {
                System.out.println("O número " + numero + " é ímpar.");
            }
        }
    }
}