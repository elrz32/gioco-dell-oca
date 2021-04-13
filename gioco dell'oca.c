#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define N 100

//prototipi
void regole();
void stampa_campo(int *v);
int *tiro_dadi(int *numero_giocatore);
void risultati(int *vittoria,int *mosse_fatte,int *caselle_speciali,int *tiro_massimo_giocatore);
void spostamento(int *v,int *distanza,int *numero_giocatore, int *pos,int *mosse_giocatore, int *trappole_giocatore,int *tiro_massimo_giocatore);
int vincitore(int *v);
void invio();


//main, cuore del programma
main(){
	int n=N+13;
	system("cls");
	int vettore[N],i;
	for(i=0;i<n;i++){	//inizializzo la prima volta il campo nel main
		vettore[i]=0;
	}
	
	int cnt_giocatore=1,pos_giocatore[4],mosse_giocatore[5],trappole_giocatore[5],tiro_massimo[5];
	for(i=0;i<5;i++){
		tiro_massimo[i]=0;
		pos_giocatore[i]=0;
		mosse_giocatore[i]=0;
		trappole_giocatore[i]=0;
	}
	mosse_giocatore[4]=0;
	tiro_massimo[4]=0;
	trappole_giocatore[4]=0;			//questo perchè per il conteggio delle mosse dei giocatori e delle trappole prese si inizia a contare da 1 a 4, non da 0 a 3
	int valore_dadi;
	regole();
	int vittoria=0;
	while(vittoria==0){	//while principale 
		system("cls");
		stampa_campo(vettore);
		printf("\n");
		valore_dadi=tiro_dadi(&cnt_giocatore);
		spostamento(vettore,&valore_dadi,&cnt_giocatore,&pos_giocatore[cnt_giocatore],&mosse_giocatore[cnt_giocatore],&trappole_giocatore[cnt_giocatore],&tiro_massimo[cnt_giocatore]);
		vittoria=vincitore(vettore);
		cnt_giocatore++;
		if(cnt_giocatore>=5){	//da vedere
			cnt_giocatore=1;
		}
		if(vittoria!=0){
			system("cls");
			vettore[N]=vittoria;		//così da vedere chi ha vinto
			stampa_campo(vettore);
		}
	}
	switch(vittoria){
		case 1:{
			printf("\nIL GIOCATORE 1 (%c) ARRIVA PER PRIMO ALLA FINE E VINCE!\n",64);
			break;
		}
		case 2:{
			printf("\nIL GIOCATORE 2 (%c) ARRIVA PER PRIMO ALLA FINE E VINCE!\n",36);
			break;
		}
		case 3:{
			printf("\nIL GIOCATORE 3 (%c) ARRIVA PER PRIMO ALLA FINE E VINCE!\n",35);
			break;
		}
		case 4:{
			printf("\nIL GIOCATORE 4 (%c) PER ARRIVA PRIMO ALLA FINE E VINCE!\n",38);
			break;
		}
	}
	risultati(&vittoria,mosse_giocatore,trappole_giocatore,tiro_massimo);
}

//questa funzione è stata creata per la pressione dell'invio
void invio(){
	int input;
	do{
		input=getch();
	}while(input!=13);
}

//regole del gioco
void regole(){
	printf(" Il gioco dell'oca:");
	printf("\nbenvenuto al gioco dell'oca, in questa versione quasi automatica del gioco ognuno dei giocatori \ndovra arrivare alla fine del percorso prima degli altri.\nE consigliabile giocare a schermo pieno\n");
	printf("fai attenzione pero alle trappole, che potranno darti svantaggi, o vantaggi...\n");
	printf("bisogna arrivare per primi nelle ultime caselle (per arrivare primi bisogna superare la fine del campo)'\n");
	printf("premere invio quando bisogna tirare i dadi\n");
	printf("conflitto non possibile: se il tiro dei dadi ti farebbe entrare in caselle gia occupate da altri giocatori, resterai fermo, perdendo il turno.\n");
	printf("\n  premi invio per continuare: ");
	invio();
	system("cls");
}

//per stampare il campo
void stampa_campo(int *v){
	printf("CONDIZIONI ATTUALI CAMPO:\n");
	printf("\n %c = giocatore 1",64);
	printf("\n %c = giocatore 2",36);
	printf("\n %c = giocatore 3",35);
	printf("\n %c = giocatore 4",38);
	HANDLE  colore;
	colore = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("\n\n");
	int i,j;
	for(j=0;j<3;j++){
		if(j==1){
			for(i=0;i<=N;i++){
				//qui si stampano i bordi laterali
				if(i==34 || i==24 || i==14 || i==44 || i==54 || i==64 || i==74 || i==84){	//cambia colore dei bordi in casi particolari
					SetConsoleTextAttribute(colore, 4);
				} else if(i==6 || i==28){
					SetConsoleTextAttribute(colore, 9);
				} else if(i==47 || i==67){
					SetConsoleTextAttribute(colore, 1);
				} else if(i==N){
					SetConsoleTextAttribute(colore, 2);
				} else if(i==95){
					SetConsoleTextAttribute(colore, 5);
				} else if(i==78 || i==38){
					SetConsoleTextAttribute(colore, 6);
				}else{
					SetConsoleTextAttribute(colore, 7);
				}
				printf("%c",186);
				SetConsoleTextAttribute(colore, 7);
				//qui si stampa il valore della casella, ovvero giocatori e spazi vuoti
			if(v[i]==0){	
				printf(" ");
			} else if(v[i]==1){
				printf("%c",64);
			} else if(v[i]==2){
				printf("%c",36);
			} else if(v[i]==3){
				printf("%c",35);
			} else if(v[i]==4){
				printf("%c",38);
			} 
			}
		} else if(j==0){	//qui si stampano i bordi superiori
			for(i=0;i<=N;i++){
				if(i==34 || i==24 || i==14 || i==44 || i==54 || i==64 || i==74 || i==84){	//cambia colore dei bordi in casi particolari
					SetConsoleTextAttribute(colore, 4);
				} else if(i==6 || i==28){
					SetConsoleTextAttribute(colore, 9);
				} else if(i==47 || i==67){
					SetConsoleTextAttribute(colore, 1);
				} else if(i==N){
					SetConsoleTextAttribute(colore, 2);
				} else if(i==95){
					SetConsoleTextAttribute(colore, 5);
				} else if(i==78 || i==38){
					SetConsoleTextAttribute(colore, 6);
				}else{
					SetConsoleTextAttribute(colore, 7);
				}
				printf("%c%c",203,205);
				}
			} else{
				for(i=0;i<=N;i++){
				if(i==34 || i==24 || i==14 || i==44 || i==54 || i==64 || i==74 || i==84){	//cambia colore dei bordi in casi particolari
					SetConsoleTextAttribute(colore, 4);
				} else if(i==6 || i==28){
					SetConsoleTextAttribute(colore, 9);
				} else if(i==47 || i==67){
					SetConsoleTextAttribute(colore, 1);
				} else if(i==N){
					SetConsoleTextAttribute(colore, 2);
				} else if(i==95){
					SetConsoleTextAttribute(colore, 5);
				} else if(i==78 || i==38){
					SetConsoleTextAttribute(colore, 6);
				}else{		//qui si stampano i bordi inferiori
					SetConsoleTextAttribute(colore, 7);
				}
				printf("%c%c",202,205);
				}	
			}
		printf("\n");
	}
	SetConsoleTextAttribute(colore, 7); //questo per essere sicuri che alla fine della funzione si stampi in bianco
}

//tiro  i dadi
int *tiro_dadi(int *numero_giocatore){
	int valore_complessivo;
	switch(*numero_giocatore){
		case 1:{
			printf(" tira i tuoi dadi, %c !\n",64);
			break;
		}
		case 2:{
			printf(" tira i tuoi dadi, %c !\n",36);
			break;
		}
		case 3:{
			printf(" tira i tuoi dadi, %c !\n",35);
			break;
		}
		case 4:{
			printf(" tira i tuoi dadi, %c !\n",38);
			break;
		}
	}
	invio();
	srand(time(0));
	do{
		valore_complessivo=rand()%13;
	}while(valore_complessivo<2);
	printf(" e uscito il numero %d\n",valore_complessivo);
	
	return valore_complessivo;
}

//spostamento dei giocatori nel vettore + controlli e reazione delle caselle trappola
void spostamento(int *v,int *distanza,int *numero_giocatore,int *pos,int *mosse_giocatore, int *trappole_giocatore,int *tiro_massimo_giocatore){
	if(*distanza>*tiro_massimo_giocatore){
		*tiro_massimo_giocatore=*distanza;
	}
	srand(time(0));
	v[*pos]=0; 
	*distanza=*distanza+*pos;
	switch(*numero_giocatore){
		case 1:{
			if(v[*distanza]!=0 && *distanza<N){
				printf("CASELLA GIA OCCUPATA, il giocatore 1 perde il turno\n");
				*distanza=*pos;
			}
			else if(*distanza==14 || *distanza==24 || *distanza==34 || *distanza==44 || *distanza==54 || *distanza==64 || *distanza==74 || *distanza==84){
				*distanza=*distanza-5;
				printf("\n CASELLA TRAPPOLA, il giocatore 1 torna indietro di 5 caselle\n");
				if(v[*distanza]!=0){
					printf(" CASELLA TRAPPOLA FALLITA perche un giocatore e gia situato nella zona d'interesse, il giocatore 1 non si sposta\n");
					*distanza=*distanza+5;
				}
				(*trappole_giocatore)++;
			} else if(*distanza==6){
				printf("SCORCIATOIA, il giocatore 1 avanza di caselle\n");
				*distanza=28;
				if(v[*distanza]!=0){
					printf("SCORCIATOIA FALLITA perche un giocatore e gia situato nella zona d'interesse\n");
					*distanza=6;
				}
				(*trappole_giocatore)++;
			} else if(*distanza==47){
				*distanza=67;
				printf("SCORCIATOIA, il giocatore 1 avanza di caselle\n");
				if(v[*distanza]!=0){
					printf("SCORCIATOIA FALLITA perche un giocatore e gia situato nella zona d'interesse\n");
					*distanza=47;
				}
				(*trappole_giocatore)++;
			} else if(*distanza==78 || *distanza==38){
				printf("TRAPPOLA LETALE, il giocatore 2 ricomincia da capo\n");
				if(v[*distanza]!=0){
					printf("TRAPPOLA LETALE FALLITA perche un giocatore e gia situato nel punto di interesse\n");
					*distanza=*distanza;
				}
				else{
					*distanza=0;
					(*trappole_giocatore)++;
				}
			} else if(*distanza==95){
				printf("CASELLA RANDOMICA, ti teletrasporterai in una casella randomica del campo, senza pero subire variazioni di posizione, in caso esse siano speciali\n");
				do{
					*distanza=rand()%N;
				}while(v[*distanza]!=0);
				(*trappole_giocatore)++;
			}
			else if(v[*distanza]!=0 && *distanza<N){										//per un corretto funzionamento del programma è meglio che ci siano 2 controlli, anche se uguali
				printf("CASELLA GIA OCCUPATA, il giocatore 1 perde il turno\n");
				*distanza=*pos;
			}
			invio();
			v[*distanza]=1;
			(*mosse_giocatore)++;
			break;
		}
		
		case 2:{
			if(v[*distanza]!=0 && *distanza<N){
				printf("CASELLA GIA OCCUPATA, il giocatore 2 perde il turno\n");
				*distanza=*pos;
			}
				else if(*distanza==14 || *distanza==24 || *distanza==34 || *distanza==44 || *distanza==54 || *distanza==64 || *distanza==74 || *distanza==84){
				*distanza=*distanza-5;
				printf("\n CASELLA TRAPPOLA, il giocatore 2 torna indietro di 5 caselle\n");
					if(v[*distanza]!=0){
						printf(" CASELLA TRAPPOLA FALLITA perche un giocatore e gia situato nella zona d'interesse, il giocatore 2 non si sposta\n");
						*distanza=*distanza+5;
						(*trappole_giocatore)++;
					}	
				
			} else if(*distanza==6){
				printf("SCORCIATOIA, il giocatore 2 avanza di caselle\n");
				*distanza=28;
				if(v[*distanza]!=0){
					printf("SCORCIATOIA FALLITA perche un giocatore e gia situato nella zona d'interesse\n");
					*distanza=6;
				}
				(*trappole_giocatore)++;
			} else if(*distanza==47){
				*distanza=67;
				printf("SCORCIATOIA, il giocatore 2 avanza di caselle\n");
				if(v[*distanza]!=0){
					printf("SCORCIATOIA FALLITA perche un giocatore e gia situato nella zona d'interesse\n");
					*distanza=47;
				}
				(*trappole_giocatore)++;	
				
			} else if(*distanza==78 || *distanza==38){
				printf("TRAPPOLA LETALE, il giocatore 2 ricomincia da capo\n");
				if(v[*distanza]!=0){
					printf("TRAPPOLA LETALE FALLITA perche un giocatore e gia situato nel punto di interesse\n");
					*distanza=*distanza;
				}
				else{
					*distanza=0;
					(*trappole_giocatore)++;
				}				
			} else if(*distanza==95){
				do{
					*distanza=rand()%N;
				}while(v[*distanza]!=0);
				(*trappole_giocatore)++;														//per far crashare il gioco
			} else if(v[*distanza]!=0 && *distanza<N){
				printf("CASELLA GIA OCCUPATA, il giocatore 2 perde il turno\n");
				*distanza=*pos;
			}
			invio();
			v[*distanza]=2;
			(*mosse_giocatore)++;
			break;
		}
		case 3:{
			 if(v[*distanza]!=0 && *distanza<N){
				printf("CASELLA GIA OCCUPATA, il giocatore 3 perde il turno\n");
				*distanza=*pos;
			}
				else if(*distanza==14 || *distanza==24 || *distanza==34 || *distanza==44 || *distanza==54 || *distanza==64 || *distanza==74 || *distanza==84){
				*distanza=*distanza-5;
				printf("\n CASELLA TRAPPOLA, il giocatore 3 torna indietro di 5 caselle\n");
					if(v[*distanza]!=0){
						printf(" CASELLA TRAPPOLA FALLITA perche un giocatore e gia situato nella zona d'interesse, il giocatore 3 non si sposta\n");
						*distanza=*distanza+5;
					}
				(*trappole_giocatore)++;	
			} else if(*distanza==6){
				printf("SCORCIATOIA, il giocatore 3 avanza di caselle\n");
				*distanza=28;
				printf("SCORCIATOIA, il giocatore 3 avanza di caselle\n");	
				(*trappole_giocatore)++;
			} else if(*distanza==47){
				*distanza=67;
				printf("SCORCIATOIA, il giocatore 3 avanza di caselle\n");
				if(v[*distanza]!=0){
					printf("SCORCIATOIA FALLITA perche un giocatore e gia situato nella zona d'interesse\n");
					*distanza=47;
				}	
				(*trappole_giocatore)++;
			} else if(*distanza==78 || *distanza==38){
				printf("TRAPPOLA LETALE, il giocatore 2 ricomincia da capo\n");
				if(v[*distanza]!=0){
					printf("TRAPPOLA LETALE FALLITA perche un giocatore e gia situato nel punto di interesse\n");
					*distanza=*distanza;
				}
				else{
					*distanza=0;
					(*trappole_giocatore)++;
				}
			} else if(*distanza==95){
				do{
					*distanza=rand()%N;
				}while(v[*distanza]!=0);
				(*trappole_giocatore)++;
			
			} else if(v[*distanza]!=0 && *distanza<N){
				printf("CASELLA GIA OCCUPATA, il giocatore 3 perde il turno\n");
				*distanza=*pos;
			}
			invio();
			v[*distanza]=3;
			(*mosse_giocatore)++;
			break;
		}
		case 4:{
			if(v[*distanza]!=0 && *distanza<N){
				printf("CASELLA GIA OCCUPATA, il giocatore 4 perde il turno\n");
				*distanza=*pos;
			}
				else if(*distanza==14 || *distanza==24 || *distanza==34 || *distanza==44 || *distanza==54 || *distanza==64 || *distanza==74 || *distanza==84){
				*distanza=*distanza-5;
				printf("\n CASELLA TRAPPOLA, il giocatore 4 torna indietro di 5 caselle\n");
				if(v[*distanza]!=0){
					printf(" CASELLA TRAPPOLA FALLITA perche un giocatore e gia situato nella zona d'interesse, il giocatore 4 non si sposta\n");
					*distanza=*distanza+5;
				}
				(*trappole_giocatore)++;	
				
			} else if(*distanza==6){
				printf("SCORCIATOIA, il giocatore 4 avanza di caselle\n");
				*distanza=28;
				printf("SCORCIATOIA, il giocatore 4 avanza di caselle\n");	
				(*trappole_giocatore)++;
			} else if(*distanza==47){
				*distanza=67;
				printf("SCORCIATOIA, il giocatore 1 avanza di caselle\n");
				if(v[*distanza]!=0){
					printf("SCORCIATOIA FALLITA perche un giocatore e gia situato nella zona d'interesse\n");
					*distanza=47;
				}
				(*trappole_giocatore)++;	
				
			} else if(*distanza==78 || *distanza==38){
				printf("TRAPPOLA LETALE, il giocatore 2 ricomincia da capo\n");
				if(v[*distanza]!=0){
					printf("TRAPPOLA LETALE FALLITA perche un giocatore e gia situato nel punto di interesse\n");
					*distanza=*distanza;
				}
				else{
					*distanza=0;
					(*trappole_giocatore)++;
				}
			} else if(*distanza==95){
				do{
					*distanza=rand()%N;
				}while(v[*distanza]!=0);
				(*trappole_giocatore)++;
		
			} else if(v[*distanza]!=0 && *distanza<N){
				printf("CASELLA GIA OCCUPATA, il giocatore 4 perde il turno\n");
				*distanza=*pos;
			}
			invio();
			v[*distanza]=4;
			(*mosse_giocatore)++;
			break;
		}
	}
	*pos=*distanza;
}

int vincitore(int *v){
	int i;
	for(i=0;i<N+12;i++){
		if(i>=N && v[i]==1){
			return 1;
		}
		if(i>=N && v[i]==2){
			return 2;
		}
		if(i>=N && v[i]==3){
			return 3;
		}
		if(i>=N && v[i]==4){
			return 4;
		}
	}
}

//scivo su un blocco note i risultati
void risultati(int *vittoria,int *mosse_fatte,int *caselle_speciali,int *tiro_massimo_giocatore){
	FILE*fp;
	fp=fopen("risultati finali.txt","w");
	fprintf(fp,"risultati gioco dell'oca:\n");
	fprintf(fp,"\n\n--> IL GIOCATORE %d HA VINTO\n\n",*vittoria);
	int i;
	for(i=1;i<5;i++){
		if(i==1){
			fprintf(fp,"il giocatore 1 si e mosso %d volte",mosse_fatte[i]);
			fprintf(fp," e ha toccato %d caselle speciali.",caselle_speciali[i]);
			fprintf(fp," Il suo tiro migliore e stato %d\n\n",tiro_massimo_giocatore[i]);
		} else if(i==2){
			fprintf(fp,"il giocatore 2 si e mosso %d volte",mosse_fatte[i]);
			fprintf(fp," e ha toccato %d caselle speciali.",caselle_speciali[i]);
			fprintf(fp," Il suo tiro migliore e stato %d\n\n",tiro_massimo_giocatore[i]);
		}  else if(i==3){
			fprintf(fp,"il giocatore 3 si e mosso %d volte",mosse_fatte[i]);
			fprintf(fp," e ha toccato %d caselle speciali.",caselle_speciali[i]);
			fprintf(fp," Il suo tiro migliore e stato %d\n\n",tiro_massimo_giocatore[i]);
		}  else if(i==4){
			fprintf(fp,"il giocatore 4 si e mosso %d volte",mosse_fatte[i]);
			fprintf(fp," e ha toccato %d caselle speciali.",caselle_speciali[i]);
			fprintf(fp," Il suo tiro migliore e stato %d\n\n",tiro_massimo_giocatore[i]);
		}  
	}
	fclose(fp);	
}
