dados_pessoais = "dadospessoais.txt"
dados_musicais = "dadosmusicais.txt"
dados_jogos = "dadosjogos.txt"

def dado_pessoais():
    with open("Dadospessoais.txt", "r", encoding="utf-8") as ficheiro:
        print("Conteúdo do arquivo:")

        for linha in ficheiro:
            print(linha.strip())

    nome = input("\nDigite o seu nome: ")
    idade = input("\nDigite a sua idade: ")

    print(f"\nNome: {nome}")
    print(f"\nIdade: {idade}")

def dado_musicais():
    musica = input("Qual é a tua música favorita: ")
    with open("dados musicais.txt", "a", encoding="utf-8") as ficheiro:
        ficheiro.write(musica + "\n")

def dado_jogos():
    jogo = input("Qual é o seu jogo favorito: ")
    with open("dadosjogos.txt", "a", encoding="utf-8") as ficheiro:
        ficheiro.write(jogo + "\n")

def menu():
    while True:
        print("\n" + "="*30)
        print(" Menu De dados")
        print("\n" + "="*30)
        print("1. Dados Pessoais")
        print("2. Dados Músicas")
        print("3. Dados Jogos")
        print("0. Sair do Dados")
        print("\n" + "="*30)

        escolha = input("Escolha uma opção (0-3): ")

        if escolha == '1':
            dado_pessoais()
        elif escolha == '2':
            dado_musicais()
        elif escolha == '3':
            dado_jogos()
        elif escolha == '0':
            print("Tchauzinho...")
            break
        else:
            print("Deu um erro. Tenta novaamente mais tarde!")