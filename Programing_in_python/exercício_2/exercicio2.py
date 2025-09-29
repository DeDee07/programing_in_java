dados = "dados.txt"

def exercicio_1():
    with open ("dados.txt", "r", encoding="utf-8") as ficheiro:
        linhas = ficheiro.readlines()

        for linha in linhas:
            print(linha, end="")

def exercicio_2():
    nomes = []
    idades = []
    with open ("dados.txt", "r", encoding="utf-8") as ficheiro:
        ficheiro.readline()

        for linha in ficheiro:
            partes = linha.strip().split(",")
            if len(partes) == '2':
                nome, idade = partes
                nomes.append(nome)
                idades.append(int(idade))

    total = len(nomes)
    media = sum(idades) / total if total > 0 else 0

    print(f"Tem o total de {total} pessoa/s")
    print(f"A média de idades é {media:.2f}")

def exercicio_3():
    nome = input("Qual é o teu nome? ")
    idade = input("Qual é a tua idade? ")

    with open("log_utilizador.txt", "a", encoding="utf-8") as ficheiro:
        ficheiro.write(f"nome: {nome} Idade: {idade}")

def exercicio_4():
    nomes_sub25 = []

    with open("dados.txt", "r", encoding="utf-8") as ficheiro:
        for linha in ficheiro:
            linha = linha.strip()
            if linha:
                nome, idade = linha.split(",")
                idade = int(idade)

                if idade < 25:
                    nomes_sub25.append(nome)
                    print(nome)

    with open("sub25.txt", "w", encoding="utf-8") as novo_ficheiro:
        for nome in nomes_sub25:
            novo_ficheiro.write(nome + "\n")

def menu():
    while True:
        print("\n" + "="*30)
        print(" Exercicio 2")
        print("\n" + "="*30)
        print("1. Leitura Simples de um texto")
        print("2. Contar e calcular médias")
        print("3. Recolher dados do utilizador e guardar num ficheiro")
        print("4. Análise com iteradores")
        print("0. Sair do Exercicio")
        print("\n" + "="*30)

        escolha = input("Escolha uma opção de (0-4)")

        if escolha == '1':
            exercicio_1()
        elif escolha == '2':
            exercicio_2()
        elif escolha == '3':
            exercicio_3()
        elif escolha == '4':
            exercicio_4()
        elif escolha == '0':
            print("Tchauzinho...")
            break
        else:
            print("Deu um Erro, tente novamente mais tarde!")

menu()