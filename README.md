# Projeto - FEIFOOD
### Bem Vindo(a) ao FeiFood!
*Este projeto tem como objetivo desenvolver um sistema de gerenciamento de pedidos utilizando a linguagem de programação C. O programa permite que o usuário cadastre alimentos, crie pedidos personalizados, edite e remova itens, além de realizar buscas e avaliações. Todas as informações são armazenadas em arquivos .txt, simulando uma base de dados simples e acessível.*

### Estrutura dos Arquivos:
*O projeto foi dividido em arquivos específicos para facilitar a organização do código, essa separação foi feita agrupando funcionalidades semelhantes e mantendo os dados em arquivos .txt.*

*  `main.c` — Arquivo principal que executa o programa e chama as funções.
* `funcoes.h` — Cabeçalhos das funções utilizadas no projeto.
* `alimentos.c` — Funções relacionadas ao cadastro e busca de alimentos.
* `pedidos.c` — Funções que manipulam os pedidos (criar, editar, remover, etc).
* `usuario.c` — Funções relacionadas ao login e gerenciamento de usuários

### Arquivos de Dados
*  `alimentos.txt` — Lista de alimentos disponíveis no sistema
* `pedidos.txt` — Armazena os pedidos feitos pelos usuários.
* `avaliacoes.txt` — Guarda as avaliações feitas nos pedidos.
* `buscados.txt` — Histórico de alimentos buscados.
* `sessao.txt` — Registra o usuário atualmente logado.
* `usuarios.txt` — Lista de usuários cadastrados no sistema.

## Funcionalidades Principais:

**1. Cadastrar Novo Usuário:**

*Permite que novos usuários sejam registrados no sistema, armazenando seus dados em um arquivo de texto.*

![CadastrarUser.](/prints/menuInicial.png)

![CadastrarUser.](/prints/cadastrando.png)


**2. Login de Usuário:**

*Verifica se o usuário existe e registra a sessão atual para controle das ações realizadas.*

![LoginUser.](/prints/login.png)

**3. Criar pedidos:**

*Aqui o usuário escolhe um nome para o pedido, adiciona alimentos com suas quantidades e pode incluir uma observação.*

![criaPed.](/prints/criarPedido.png)

**4. Editar pedidos (nome ou quantidade de um item):**

*Permite alterar o nome do pedido ou a quantidade de um item específico.*

![editaPed.](/prints/editarPedido.png)

![EditarNomePedido.](/prints/EditarNomePedido.png)

![EditarQtdPedido.](/prints/EditarQtdPed.png)

**5. Excluir pedidos:**

*Remove um pedido do sistema, desde que pertença ao usuário logado.*

![ExcluiPed.](/prints/excluirPed.png)

**6. Adicionar alimentos de um pedido:**

*Insere um novo alimento ao pedido existente, mantendo a estrutura correta dos dados.*

![adicAlim.](/prints/adicionarItem.png)

**7. Remover alimentos de um pedido:**

*Exclui um item específico de um pedido. Se não restarem itens, o pedido é apagado.*

![removAlim.](/prints/removerItem.png)

**8. Buscar alimentos por nome:**

*Procura um alimento pelo nome na lista de alimentos disponíveis e registra a busca.*

![buscaAlim.](/prints/buscarAlim.png)

**9. Listar alimentos buscados:**

*Exibe todos os alimentos que foram buscados anteriormente pelo usuário.*

![listaAlim.](/prints/ListaAlim.png)

**10. Avaliar pedidos com estrelas:**
*Permite que o usuário atribua uma nota ao pedido, registrando a avaliação no sistema.*

![avaliarPed.](/prints/AvaliarPed.png)


## Conclusão

*Durante o desenvolvimento deste projeto, consegui aplicar vários conceitos importantes da linguagem C, principalmente relacionados à manipulação de arquivos e à organização do código em funções separadas. A ideia foi criar um sistema simples, mas funcional, que permitisse gerenciar pedidos, alimentos e usuários de forma prática pelo terminal. Além de reforçar o uso de estruturas básicas da linguagem, o projeto também me ajudou a entender melhor como organizar um programa em partes e como deixar o código mais claro e reutilizável.*
