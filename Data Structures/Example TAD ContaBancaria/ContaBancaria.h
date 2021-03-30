// ************* contaBancaria.h ************
// definição do tipo e suas operações

// typedef stuct Conta Bancaria
typedef struct {
    int numero;
    double saldo;
}ContaBancaria;

//cabeçalho das funções
void Inicializa(ContaBancaria *conta, int numero, double saldo);
void Deposito(ContaBancaria *conta, double valor);
void Saque(ContaBancaria *conta, double valor);
void Imprime(ContaBancaria *conta);



