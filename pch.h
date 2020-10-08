#ifndef PCH_H
#define PCH_H
//trab 1
#define NUM_DIA 125 //Numero de dias totais
#define NUM_MESES 5 //Numero de meses
#define LET_SEM 5 //Dias letivos na semana
#define NUM_PROF 16 //Numero de professores
#define NUM_REUN 9 //Numero de reuniões
#define HOR_DISP 6 //Numero de horarios
#define MAX(x,y) (x) > (y) ? (x) : (y)
//trab 2
#define tamPop 150 //Tamanho populãção (AG)
#define cro 100 //Quantidade de cruzamentos (AG)
//

typedef struct tSol {	
	int matSol[2][NUM_REUN];	//matriz solução
	int vetAulasP[NUM_PROF];	//vet aulas perdidas
	int vetNAN[NUM_PROF];	//vet aulas a noite
	int vetNA3[NUM_PROF];  //vet aulas 3° turno
	int vetRM[NUM_MESES]; //Quantidade de reuniões agendadas em cada mes
	float MAP;  // Media de aulas perdidas
	int TAP;   //Total de aulas perdidas
	int fo;   //valor da FO
} sol;

int vetNumReun[NUM_MESES];
int vetPes[NUM_REUN] = {10, 5, 1, 1, 100, 500, 500};
int vetDiasMes[NUM_MESES];
int matMes[2][NUM_MESES];
int vetDias[NUM_DIA];
int vetLim[NUM_REUN];
int matHorProf[NUM_PROF][HOR_DISP][LET_SEM];
//trab 2
sol apop[tamPop + cro];
float tMut = 0.1;
double melhor;
//

void lerDados();
void testarDados();
void escSol(sol &s);
void escSolS(sol& s);
void escSolArq(sol &s);
void heurConstAle(sol &s);
void calcFO(sol &s);
void CpySol(sol &s, sol &s1);
//trab 2
void ordenaAPop();
void gerPop();
void escPop(int tam);
void mutInd(int s);
void cruAG(int p, int p1, int f);
void heuAGT2();
//
#endif
