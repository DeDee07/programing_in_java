import random

def soma():
    nu1 = int(input("Escolha um número: "))
    nu2 = int(input("Escolha mais um número: "))
    resoltado = nu1 + nu2
    print("Resoltado da conta é: {resoltado}")

def acerta():
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

def contador():
    nu1 = int(input("Escolha um número: "))
    nu2 = int(input("Escolhe outro número: "))
    for i in range(nu1, nu2 + 1 ):
        print(i, end=" ")


def menu():
    while True:
        print("\n" + "="*30)
        print(" Treino de python - ex.1 ")
        print("\n" + "="*30)
        print("1. Soma de dois números")
        print
        print("0. Sair do Treino")

        escolha = input("Escolha um número de (0-4): ")

        if escolha == '1':
            soma()
        elif escolha == '2':
            acerta()
        elif escolha == '3':
            contador()
        elif escolha == '0':
            print("Até uma próxima...")
            break
        else:
            print("tenta novamente mais tarde!")

menu()