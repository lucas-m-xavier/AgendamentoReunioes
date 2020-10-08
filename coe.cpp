#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <math.h>

using namespace std;

int main() {
	srand(time(NULL));

	lerDados();
	//testarDados();
	/*
	sol s;
	clock_t h;
	double tempo;
	
	h = clock();
	for (int i = 0; i < 1000000; i++) {
		heurConstAle(s);
	}
	h = clock() - h;
	tempo = ((double)h) / CLOCKS_PER_SEC;
	cout << "Tempo: " << tempo << "\n";

	h = clock();
	for (int i = 0; i < 1000000; i++) {
		calcFO(s);
	}
	h = clock() - h;
	tempo = ((double)h) / CLOCKS_PER_SEC;
	cout << "Tempo: " << tempo << "\n";
	*/

	//sol s;
	//heurConstAle(s);
	//calcFO(s);
	//escSol(s);
	//escSolArq(s);

	//Trab 2
	gerPop();
	heuAGT2();
	cout << "\nTempo Melhor FO: " << melhor << "\n\n";
	calcFO(apop[0]);
	escSol(apop[0]);
	//escSolArq(apop[0]);
	//escPop(tamPop);
	//
	getchar();
	return 0;
}

void lerDados() {
	FILE *arq;
	arq = fopen("input.txt", "r");

	for (int i = 0; i < NUM_DIA; i++)
		fscanf(arq, "%d", &vetDias[i]);

	for (int i = 0; i < NUM_MESES; i++) {
		fscanf(arq, "%d", &vetDiasMes[i]);
	}

	for (int i = 0; i < NUM_MESES; i++) {
		fscanf(arq, "%d", &vetNumReun[i]);
	}

	for (int i = 0; i < NUM_PROF; i++) {
		for (int j = 0; j < HOR_DISP; j++) {
			for (int k = 0; k < LET_SEM; k++) {
				fscanf(arq, "%d", &matHorProf[i][j][k]);
			}
		}
	}

	fclose(arq);

	//Matriz i/f meses
	matMes[0][0] = 0;
	matMes[1][0] = vetDiasMes[0] - 1;

	for (int j = 1; j < NUM_MESES; j++) {
		matMes[0][j] = matMes[0][j - 1] + vetDiasMes[j - 1];
		matMes[1][j] = matMes[1][j - 1] + vetDiasMes[j];
	}
}

void testarDados() {
	for (int i = 0; i < NUM_DIA; i++) {
		cout << vetDias[i] << " ";
	}

	cout << "\n\n";

	for (int i = 0; i < NUM_MESES; i++) {
		cout << vetDiasMes[i] << " ";
	}

	cout << "\n\n";

	for (int i = 0; i < NUM_MESES; i++) {
		cout << vetNumReun[i] << " ";
	}

	cout << "\n\n";

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUM_MESES; j++) {
			cout << matMes[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n\n";

	for (int i = 0; i < NUM_PROF; i ++) {
		for (int j = 0; j < HOR_DISP; j++) {
			for (int k = 0; k < LET_SEM; k++) {
				cout << matHorProf[i][j][k] << " ";
			}
			cout << "\n";
		}
		cout << "\n\n";
	}
}

void heurConstAle(sol &s) {
	int i, j, key;
	memset(s.matSol, 0, sizeof(s.matSol));

	for (int i = 0; i < NUM_REUN; i++) {
		s.matSol[0][i] = rand() % NUM_DIA;

		while (vetDias[s.matSol[0][i]] == -1 || s.matSol[0][i] == s.matSol[0][i - 1]) {
			s.matSol[0][i] = rand() % NUM_DIA;
		}
	}

	for (int i = 0; i < NUM_REUN; i++) {
		s.matSol[1][i] = rand() % 4;
	}
	//insertion sort
	for (i = 1; i < NUM_REUN; i++) {
		key = s.matSol[0][i];
		j = i - 1;

		while (j >= 0 && s.matSol[0][j] > key) {
			s.matSol[0][j + 1] = s.matSol[0][j];
			j--;
		}
		s.matSol[0][j + 1] = key;
	}
}

void calcFO(sol& s) {
	memset(s.vetAulasP, 0, sizeof(s.vetAulasP));
	memset(s.vetNAN, 0, sizeof(s.vetNAN));
	memset(s.vetNA3, 0, sizeof(s.vetNA3));
	memset(s.vetRM, 0, sizeof(s.vetRM));
	bool a1 = false, a2 = false, a3 = false;
	float aux1 = 0;
	int aux = 0;
	s.TAP = 0;
	s.MAP = 0;
	s.fo = 0;

	for (int i = 0; i < NUM_REUN; i++) {
		for (int j = 0; j < NUM_PROF; j++) {
			if (matHorProf[j][s.matSol[1][i]][vetDias[s.matSol[0][i]]]) {
				s.vetAulasP[j]++;
			}

			if ((vetDias[s.matSol[0][i]] - 1) != -1) {
				if (matHorProf[j][5][vetDias[s.matSol[0][i]] - 1]) s.vetNAN[j]++;
			}

			if (s.matSol[1][i] == 0 || s.matSol[1][i] == 1) a1 = true;

			if (s.matSol[1][i] == 2 || s.matSol[1][i] == 3) a2 = true;

			for (int k = 0; k < 2; k++) {
				if (matHorProf[j][k][vetDias[s.matSol[0][i]]] == 1) a1 = true;
			}

			for (int k = 2; k < 4; k++) {
				if (matHorProf[j][k][vetDias[s.matSol[0][i]]] == 1) a2 = true;
			}

			for (int k = 4; k < 6; k++) {
				if (matHorProf[j][k][vetDias[s.matSol[0][i]]] == 1) a3 = true;
			}

			if (a1 == true && a2 == true && a3 == true) {
				s.vetNA3[j]++;
			}

			a1 = false;
			a2 = false;
			a3 = false;
		}
	}

	//w1
	for (int i = 0; i < NUM_PROF; i++) {
		s.TAP += s.vetAulasP[i];
	}
	s.MAP = ((float)s.TAP / (float)NUM_PROF);
	s.fo += (vetPes[0] * s.TAP);

	//w2
	for (int i = 0; i < NUM_PROF; i++) {
		aux1 += fabs(s.vetAulasP[i] - s.MAP);
	}
	s.fo += (vetPes[1] * aux1);
	aux1 = 0;

	//w3
	for (int i = 0; i < NUM_PROF; i++) {
		aux += s.vetNAN[i];
	}
	s.fo += (vetPes[2] * aux);
	aux = 0;

	//w4
	for (int i = 0; i < NUM_PROF; i++) {
		aux += s.vetNA3[i];
	}
	s.fo += (vetPes[3] * aux);

	aux = 0;

	//w5
	for (int i = 0; i < NUM_PROF; i++) {
		aux += MAX(0, s.vetAulasP[i] - 3);
	}
	s.fo += (vetPes[4] * aux);
	aux = 0;

	//w6
	for (int i = 0; i < NUM_REUN; i++) {
		if (s.matSol[0][i] < matMes[0][1]) {
			s.vetRM[0]++;
		}
		else {
			if (s.matSol[0][i] < matMes[0][2]) {
				s.vetRM[1]++;
			}
			else {
				if (s.matSol[0][i] < matMes[0][3]) {
					s.vetRM[2]++;
				}
				else {
					if (s.matSol[0][i] < matMes[0][4]) {
						s.vetRM[3]++;
					}
					else {
						s.vetRM[4]++;
					}
				}
			}
		}
	}

	for (int i = 0; i < NUM_MESES; i++) {
		aux += fabs(vetNumReun[i] - s.vetRM[i]);
	}
	s.fo += (vetPes[5] * aux);
	aux = 0;

	//w7
	for (int i = 1; i < NUM_REUN; i++) {
		aux += MAX(0, 10 - s.matSol[0][i] + s.matSol[0][i - 1]);
	}
	s.fo += (vetPes[6] * aux);
}

void escSol(sol &s) {
	int flag = 0;
	cout << "\nValor FO: " << s.fo << "\n";

	for (int i = 0; i < 2; i++) {
		cout << "Reuniao no mes 3: \n";
		cout << "Dia: " << s.matSol[0][i] + 11 << " Horario: ";
		switch (s.matSol[1][i]) {
		case 0:
			cout << "08:00 - 10:00\n";
			break;
		case 1:
			cout << "10:00 - 12:00\n";
			break;
		case 2:
			cout << "14:00 - 16:00\n";
			break;
		case 3:
			cout << "16:00 - 18:00\n";
			break;
		}
	}

	for (int i = 2; i < NUM_REUN; i++) {
		cout << "Reuniao no mes " << (i / 2 + 3) << ": \n";
		cout << "Dia: " << (s.matSol[0][i] - matMes[0][i / 2] + 1) << " Horario: ";
		switch (s.matSol[1][i]) {
		case 0:
			cout << "08:00 - 10:00\n";
			break;
		case 1:
			cout << "10:00 - 12:00\n";
			break;
		case 2:
			cout << "14:00 - 16:00\n";
			break;
		case 3:
			cout << "16:00 - 18:00\n";
			break;
		}
	}

	cout << "\nAulas perdidas: \n";
	for (int i = 0; i < NUM_PROF; i++) {
		cout << "Prof " << i + 1 << ": " << s.vetAulasP[i] << "\n";
		flag = flag + s.vetAulasP[i];
	}
	cout << "Total de aulas perdidas: " << flag;
	cout << "\nNumero medio de aulas perdidas: " << ((float)flag / (float)NUM_PROF);
	flag = 0;

	cout << "\n\nAulas a noite antes de uma reuniao:\n";
	for (int i = 0; i < NUM_PROF; i++) {
		cout << "Prof " << i + 1 << ": " << s.vetNAN[i] << "\n";
		flag = flag + s.vetNAN[i];
	}
	cout << "Total de aulas a noite antes de uma reuniao: " << flag;
	flag = 0;

	cout << "\n\nNumero de aulas no terceiro turno:\n";
	for (int i = 0; i < NUM_PROF; i++) {
		cout << "Prof " << i + 1 << ": " << s.vetNA3[i] << "\n";
		flag = flag + s.vetNA3[i];
	}
	cout << "Total de aulas no terceiro turno: " << flag;
}

void escSolS(sol& s) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUM_REUN; j++) {
			cout << s.matSol[i][j] << " ";
		}
		cout << "\n";
	}
}

void escSolArq(sol &s) {
	FILE *arq;
	arq = fopen("output.txt", "w");

	int flag = 0;
	fprintf(arq, "FO: %d\n", s.fo);

	for (int i = 0; i < 2; i++) {
		fprintf(arq, "Reuniao no mes 3: \n");
		fprintf(arq, "Dia: %d Horario: ", s.matSol[0][i] + 11);
		switch (s.matSol[1][i]) {
		case 0:
			fprintf(arq, "08:00 - 10:00\n");
			break;
		case 1:
			fprintf(arq, "10:00 - 12:00\n");
			break;
		case 2:
			fprintf(arq, "14:00 - 16:00\n");
			break;
		case 3:
			fprintf(arq, "16:00 - 18:00\n");
			break;
		}
	}

	for (int i = 2; i < NUM_REUN; i++) {
		fprintf(arq, "Reuniao no mes %d: \n", (i / 2 + 3));
		fprintf(arq, "Dia: %d Horario: ", (s.matSol[0][i] - matMes[0][i / 2] + 1));
		switch (s.matSol[1][i]) {
		case 0:
			fprintf(arq, "08:00 - 10:00\n");
			break;
		case 1:
			fprintf(arq, "10:00 - 12:00\n");
			break;
		case 2:
			fprintf(arq, "14:00 - 16:00\n");
			break;
		case 3:
			fprintf(arq, "16:00 - 18:00\n");
			break;
		}
	}

	fprintf(arq, "\nAulas Perdidas:\n");
	for (int i = 0; i < NUM_PROF; i++) {
		fprintf(arq, "Prof %d: %d \n", i + 1, s.vetAulasP[i]);
		flag = flag + s.vetAulasP[i];
	}
	fprintf(arq, "Total de aulas perdidas: %d", flag);
	fprintf(arq, "\nNumero medio de aulas perdidas: %.3f", s.MAP);
	flag = 0;

	fprintf(arq, "\n\nAulas a noite antes de uma reuniao:\n");
	for (int i = 0; i < NUM_PROF; i++) {
		fprintf(arq, "Prof %d: %d \n", i + 1, s.vetNAN[i]);
		flag = flag + s.vetNAN[i];
	}
	fprintf(arq, "Total de aulas a noite antes de uma reunião: %d\n", flag);
	flag = 0;

	fprintf(arq, "\nAulas no terceiro turno: \n");
	for (int i = 0; i < NUM_PROF; i++) {
		fprintf(arq, "Prof %d: %d\n", i + 1, s.vetNA3[i]);
		flag = flag + s.vetNA3[i];
	}
	fprintf(arq, "Total de aulas no terceiro turno: %d", flag);

	fclose(arq);
}

void CpySol(sol &s, sol &s1) {
	memcpy(&s1, &s, sizeof(s));
}

//Trab2
void ordenaAPop() {
	int i, j;
	sol temp;

	for (i = 1; i < (tamPop + cro); i++) {
		j = i;

		while (j > 0 && apop[j - 1].fo > apop[j].fo) {
			memcpy(&temp, &apop[j], sizeof(temp)); 
			memcpy(&apop[j], &apop[j - 1], sizeof(temp));
			memcpy(&apop[j - 1], &temp, sizeof(temp));
			j--;
		}
	}
}

void gerPop() {
	for (int i = 0; i < tamPop; i++) {
		heurConstAle(apop[i]);
		calcFO(apop[i]);
	}
}

void escPop(int tam) {
	for (int i = 0; i < tam; i++) {
		cout << "Valor FO: " << apop[i].fo << "\n";
	}
}

void mutInd(int s) {
	int aux1 = rand() % 2;
	int aux2 = rand() % NUM_REUN;

	if (aux1 == 0) {
		apop[s].matSol[0][aux2] = rand() % NUM_DIA;

		while (apop[s].matSol[0][aux2] == apop[s].matSol[0][aux2 - 1]) {
			apop[s].matSol[0][aux2] = rand() % NUM_DIA;
		}
	}
	else {
		apop[s].matSol[1][aux2] = rand() % 4;
	}
}

void cruAG(int p, int p1, int f) {
	int x = rand() % (NUM_REUN - 1) + 1;

	for (int i = 0; i < x; i++) {
		apop[f].matSol[0][i] = apop[p].matSol[0][i];
		apop[f].matSol[1][i] = apop[p1].matSol[1][i];
	}

	for (int i = x; i < NUM_REUN; i++) {
		apop[f].matSol[0][i] = apop[p1].matSol[0][i];
		apop[f].matSol[1][i] = apop[p].matSol[1][i];
	}
}

void heuAGT2() {
	int IDp1, IDp2, aux, flag, k, key, j;
	aux = apop[0].fo;
	sol mel;
	clock_t h, hf;
	double tempo, prob;
	h = clock();
	hf = clock();
	tempo = ((double)hf - (double)h) / CLOCKS_PER_SEC;

	do {
		for (k = 0; k < cro; k++) {
			//escolhendo os pais
			IDp1 = rand() % tamPop;
			IDp2 = rand() % tamPop;

			while (IDp2 == IDp1) {
				IDp2 = rand() % tamPop;
			}

			//criando filho
			cruAG(IDp1, IDp2, (tamPop + k));

			prob = ((double)rand() / ((double)RAND_MAX + 1));

			if (prob < tMut) {
				mutInd((tamPop + k));
				//Ordenando o vetor matsol[0]
				for (int i = 1; i < NUM_REUN; i++) {
					key = apop[(tamPop + k)].matSol[0][i];
					j = i - 1;

					while (j >= 0 && apop[(tamPop + k)].matSol[0][j] > key) {
						apop[(tamPop + k)].matSol[0][j + 1] = apop[(tamPop + k)].matSol[0][j];
						j--;
					}
					apop[(tamPop + k)].matSol[0][j + 1] = key;
				}
			}

			calcFO(apop[(tamPop + k)]);
		}
		ordenaAPop();

		if (apop[0].fo != aux) {
			//cout << "\nMelhor FO: " << apop[0].fo << "\tTempo: " << tempo << " segundos.";
			melhor = tempo;
			aux = apop[0].fo;
		}
		//Epidemia
		flag = 0;

		for (int i = 1; i < tamPop; i++) {
			if (apop[i].fo == aux) flag++;
		}

		if (flag == (tamPop - 1)) {
			memcpy(&mel, &apop[0], sizeof(mel));

			gerPop();

			memcpy(&apop[0], &mel, sizeof(mel));
		}
		//calculando o tempo
		hf = clock();
		tempo = ((double)hf - (double)h) / CLOCKS_PER_SEC;
	} while (tempo <= 300);
}
//