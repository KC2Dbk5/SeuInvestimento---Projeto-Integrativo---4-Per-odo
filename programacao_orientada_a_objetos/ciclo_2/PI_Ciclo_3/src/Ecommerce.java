public class Ecommerce {
    public static void main(String[] args) {
        // Criando o estoque
        Estoque estoque = new Estoque();

        // Usando a fábrica para criar produtos e adicionar ao estoque
        Produto camisa = CadastroConstrutor.criarProduto("Camisa Polo", 79.90, 50);
        Produto calca = CadastroConstrutor.criarProduto("Calça Jeans", 149.90, 30);
        estoque.adicionarProduto(camisa);
        estoque.adicionarProduto(calca);

        // Criando funcionários usando a fábrica
        Funcionario funcionario1 = CadastroConstrutor.criarFuncionario("João Silva", "joao@email.com", "Gerente");
        Funcionario funcionario2 = CadastroConstrutor.criarFuncionario("Maria Oliveira", "maria@email.com", "Atendente");

        // Exibindo produtos no estoque
        System.out.println("Produtos no Estoque:");
        estoque.listarProdutos();

        // Exibindo informações dos funcionários
        System.out.println("\nFuncionários cadastrados:");
        System.out.println(funcionario1);
        System.out.println(funcionario2);

        // Buscar um produto pelo nome
        System.out.println("\nBuscando produto 'Calça Jeans':");
        Produto produtoBuscado = estoque.buscarProdutoPorNome("Calça Jeans");
        if (produtoBuscado != null) {
            System.out.println(produtoBuscado);
        } else {
            System.out.println("Produto não encontrado.");
        }
    }
}
