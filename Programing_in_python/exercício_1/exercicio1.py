import random

def exercicio_1():
    nu1 = int(input("Escreve"))
    nu2 = int(input("escreve outro número:"))
    resoltado = nu1 + nu2
    print("O resoltado é:", resoltado)

def exercicio_2():
    numero_secreto = random.randint(1, 100)
    palpite = int(input("Qual é seu palpite: "))
    tentativa = 1
    
    if numero_secreto < palpite:
        print("Erraste, o número secreto não é {palpite} pequeno")
        tentativa += 1
    elif numero_secreto > palpite:
        print("Erraste, o número secreto não é {palpite} grande")
        tentativa += 1
    elif numero_secreto == palpite:
        print("Wow acertaste com um total de {tentativa} tentativa(s)")  
    
def exercicio_3():
    nu1 = int(input("Escolha um número: "))
    nu2 = int(input("Escolhe outro número: "))
    for i in range(nu1, nu2 + 1 ):
        print(i, end=" ")

def exercicio_4():
    nu1 = float(input("Escolha um número: "))
    nu2 = float(input("Escolha outro número: "))
    
    soma = nu1 + nu2
    subtracao = nu1 - nu2
    multiplicacao = nu1 * nu2
    
    if nu2 == 0:
        divisao = "não é possível dividir por zero"
    else:
        divisao = nu1 / nu2

    print("A Soma é:", soma)
    print("A subtração é:", subtracao)
    print("A multiplicação é:", multiplicacao)
    print("A Divisão é:", divisao)

def exercicio_5():
    palavra_passe1 = str(input("Escreve a tua palavra-passe: "))
    palavra_passe2 = str(input("Escreve outra vez a tua palavra-passe: "))

    if palavra_passe1 == palavra_passe2:
        print("As Palavras-passe coincidem!")
    else:
        print("As palavras-passe não coincidem. Tenta novamente!")

def exercicio_6():
    palavra = str(input("Escreva uma frasse/texto para ver quantas vogais: "))
    vogais = "aeiouAEIOU"
    contador = 0

    for letra in palavra:
        if letra in vogais:
            contador +=1

    print(f"O número de vogais na frasse/texto é: {contador}")
    

def exercicio_7():
    print("Eu não sei realmente fazer isto :( ")

def menu():
    while True:
        print("\n" + "="*30)
        print(" Menu de Exercícios")
        print("\n" + "="*30)
        print("1. Soma de dois números")
        print("2. Adivinha o número")
        print("3. Contagem de x até y")
        print("4. Operações matemáticas")
        print("5. Palavra-passe Forte")
        print("0. Sair do Exercício")
        print("\n" + "="*30)

        escolha = input("Escolha uma opção de (0-7): ")

        if escolha == '1':
            exercicio_1()
        elif escolha == '2':
            exercicio_2()
        elif escolha == '3':
            exercicio_3()
        elif escolha == '4':
            exercicio_4()
        elif escolha == '5':
            exercicio_5()
        elif escolha == '6':
            exercicio_6()
        elif escolha == '7':
            exercicio_7()
        elif escolha == '0':
            print("tchauzinho...")
            break
        else:
            print("Opção inválida, tente um número (0-7)")

menu()