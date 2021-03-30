// ************* contaBancaria.h ************
// defini��o do tipo e suas opera��es

// typedef stuct Conta Bancaria
typedef struct {
    int numero;
    double saldo;
}ContaBancaria;

//cabe�alho das fun��es
void Inicializa(ContaBancaria *conta, int numero, double saldo);
void Deposito(ContaBancaria *conta, double valor);
void Saque(ContaBancaria *conta, double valor);
void Imprime(ContaBancaria *conta);



