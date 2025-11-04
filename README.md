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

### Funcionalidades Principais:

* Cadastrar Novo Usuário;
* Login de Usuário;
* Criar pedidos com múltiplos alimentos;
* Editar pedidos (nome ou quantidade de um item);
* Excluir pedidos;
* Adicionar ou remover alimentos de um pedido;
* Buscar alimentos por nome;
* Listar alimentos buscados;
* Avaliar pedidos com estrelas;