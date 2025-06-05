#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_REFEICOES_DIA 100 // Estabelece o máximo de refeições
#define MAX_MESES 12 // Estabelece o máximo de meses
#define NUM_DIAS 30 // Estabelece o máximo de dias

// Define a estrutura de uma venda
typedef struct {
    int tipo;
    float peso;
    int bebidas;
    float valor_compra;
    float valor_total;
} Venda;

// Array de um Ano, com 12 meses, 30 dias e 100 vendas em cada dia
Venda Ano[MAX_REFEICOES_DIA][NUM_DIAS][MAX_MESES] = {};

// Armazena o faturamento bruto de cada dia de cada mês
float faturamentoDiario[NUM_DIAS][MAX_MESES] = {};

// Armazena o faturamento bruto total de cada mês
float faturamentoMensal[MAX_MESES] = {};

int diaSelecionado; // Dia selecionado pelo usuário
int mesSelecionado; // Mês selecionado pelo usuário

int main() {
    int continuar = 1;
    
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    // Loop que repete o processo inteiro de criação de vendas para cada mês
    for(int mes = 0; mes < MAX_MESES; mes++){
        
        // Loop que repete o processo de criação de vendas para cada dia do mês
        for (int dia = 0; dia < NUM_DIAS; dia++) {
            
            // Loop que cria 100 vendas aleatorizadas para um dia
            for (int i = 0; i < MAX_REFEICOES_DIA; i++) {
                Venda *venda = &Ano[i][dia][mes];
                venda->tipo = rand() % 2 + 1;
                
                // Tipo 1 = quentinha, tipo 2 = a quilo
                if(venda->tipo == 1){
                    venda->peso = 1;
                    venda->valor_compra = 20.50;
                }
                
                // Caso não seja quentinha, aleatorizar o peso em kilos (1kg vale R$20,00)
                else{
                    venda->peso = (float)rand() / (float)(RAND_MAX/ 5) + 0.3;
                    venda->valor_compra = venda->peso * 20;
                }
                
                // Aleatoriza o número de bebidas da venda
                venda->bebidas = rand() % 3;
                
                venda->valor_total = venda->valor_compra + venda->bebidas * 2.5; // Calcula o valor total da venda, sendo R$2,50 o valor de uma bebida
                faturamentoDiario[dia][mes] += venda->valor_total; // Adiciona o valor total da venda ao faturamento do dia
            }
            
            faturamentoMensal[mes] += faturamentoDiario[dia][mes]; // Adiciona o valor bruto do dia ao valor bruto do mês
        }
        
    }
    
    // Loop principal
    do{
        // Pede o input do usuário para decidir o que o programa vai apresentar
        printf("\nAperte 1 para ver os meses ordenados, 2 para relatórios diários, e 3 para fechar o programa.\n");
        char resposta;
        scanf(" %c", &resposta);
        
        if(resposta == '1'){
            // Função de comparação para qsort
            int comparar(const void *a, const void *b) {
                return (*(float*)b - *(float*)a);
            }
            
            // Criar um array para armazenar o faturamento mensal junto com o número do mês
            float faturamentoMensalOrdenado[MAX_MESES][2];
            for (int i = 0; i < MAX_MESES; i++) {
                faturamentoMensalOrdenado[i][0] = faturamentoMensal[i];
                faturamentoMensalOrdenado[i][1] = i + 1; // Número do mês
            }
            
            // Ordenar o array em ordem decrescente de faturamento mensal
            qsort(faturamentoMensalOrdenado, MAX_MESES, sizeof(faturamentoMensalOrdenado[0]), comparar);
        
            // Exibir os meses com faturamento mais alto primeiro
            printf("Faturamento Mensal em Ordem Decrescente:\n");
            for (int i = 0; i < MAX_MESES; i++) {
                printf("Mês %d: R$%.2f\n", (int)faturamentoMensalOrdenado[i][1], faturamentoMensalOrdenado[i][0]);
            }
            continue;
        } else if(resposta == '2'){
            // Pede ao usuário qual mês ele deseja visualizar
            printf("Digite o mês que você quer (1 a %d).\n", MAX_MESES);
            scanf("%d", &mesSelecionado);
                
            // Estabelece um estado de erro caso o input seja inválido
            if (mesSelecionado < 1 || mesSelecionado > MAX_MESES) {
                printf("Mês inválido. Por favor, digite um número entre 1 e %d.\n", MAX_MESES);
                continue;
            }
                
            // Pede ao usuário qual dia ele deseja visualizar
            printf("Digite o dia que você quer (1 a %d).\n", NUM_DIAS);
            scanf("%d", &diaSelecionado);
        
            // Estabelece um estado de erro caso o input seja inválido
            if (diaSelecionado < 1 || diaSelecionado > NUM_DIAS) {
                printf("Dia inválido. Por favor, digite um número entre 1 e %d.\n", NUM_DIAS);
                continue;
            }
            
            // Imprime o relatório do dia selecionado, junto com o faturamento bruto do mês
            printf("\nRelatório do dia %d:\n", diaSelecionado);
            for (int i = 0; i < MAX_REFEICOES_DIA; i++) {
                Venda *venda = &Ano[i][diaSelecionado - 1][mesSelecionado - 1];
                char tipoComida[] = "";
                if(venda->tipo == 1){
                    tipoComida[0] = *"Q";
                    tipoComida[1] = *"u";
                    tipoComida[2] = *"e";
                    tipoComida[3] = *"n";
                    tipoComida[4] = *"t";
                    tipoComida[5] = *"i";
                    tipoComida[6] = *"n";
                    tipoComida[7] = *"h";
                    tipoComida[8] = *"a";
                }
                else{
                    tipoComida[0] = *"A";
                    tipoComida[1] = *" ";
                    tipoComida[2] = *"Q";
                    tipoComida[3] = *"u";
                    tipoComida[4] = *"i";
                    tipoComida[5] = *"l";
                    tipoComida[6] = *"o";
                    tipoComida[7] = *" ";
                    tipoComida[8] = *" ";
                }
                printf("Venda: %d  Tipo: %s  Peso: %.2fkg  Bebidas: %d  Valor: R$%.2f \n", i+1, tipoComida, venda->peso, venda->bebidas, venda->valor_total);
            }
                
            printf("\nFaturamento Bruto do Dia: %.2f\n\n", faturamentoDiario[diaSelecionado - 1][mesSelecionado - 1]);
            printf("Faturamento Bruto do Mês: %.2f\n\n", faturamentoMensal[mesSelecionado - 1]);
        } else if(resposta == '3'){
            break;
        } else{
                printf("Resposta Inválida. Tente Novamente.");
            }
    } while(continuar);
    
    return 0;
}