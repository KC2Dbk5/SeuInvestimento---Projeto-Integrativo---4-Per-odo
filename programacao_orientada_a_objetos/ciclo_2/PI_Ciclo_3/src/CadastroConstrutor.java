public class CadastroConstrutor {

    public static Funcionario criarFuncionario(String nome, String email, String cargo) {
        return new Funcionario(nome, email, cargo);
    }

    public static Produto criarProduto(String nome, double preco, int quantidade) {
        return new Produto(nome, preco, quantidade);
    }
}
