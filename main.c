#include "./BADT/frame.h"
#include "./Suport/constructors.h"
#include "./Suport/subroutines.h"

void main(){

	#define height 18
	int state = 0;
	int lastState = 0, stateBuffer = 0;//State buffer sempre atualiza | lastState para testes lógicos
	int idBuffer = 0; //Usado como referência para atualizar informações de tablelas
	char input = '\0';
	
	//Tabelas
	int movieFilter = 0;
	int clientFilter = 0;
	Table moviesTable[3];
	Table clientsTable[3];
	
	//Frames
	Frame *menuFrames = (Frame *)malloc(sizeof(Frame) * 100);
	
	setupMainMenu(&menuFrames[0], height);
	setupMovieOptions(&menuFrames[1], height);
	setupMovieFilter(&menuFrames[2], height);
	setupMovieFilterG(&menuFrames[3], height);
	setupInvalidInput(&menuFrames[4], height);
	setupSucess(&menuFrames[5], height);
	
	setupClientOptions(&menuFrames[6], height);
	setupClientFilter(&menuFrames[7], height);
	
	Frame *frames = (Frame *)malloc(sizeof(Frame) * 100);//FILMES
	
	Frame *framesC = frames;
	
	
	//FILMES
	tableSetup(&moviesTable[0], "sdsdsf",",id, nome, ano, genero, duracao", 'n');//TODOS
	txtToTable(&moviesTable[0], "./movies",'y');
	
	tableSetup(&moviesTable[1], "sdsdsf",",id, nome, ano, genero, duracao", 'n');//FILTROS
	txtToTable(&moviesTable[1], "./movies",'y');
	
	//CLIENTES
	
	tableSetup(&clientsTable[0], "sdssd",",cpf, nome, email, ano de nascimento", 'n');//TODOS
	txtToTable(&clientsTable[0], "./clients",'y');
	
	tableSetup(&clientsTable[1], "sdssd",",cpf, nome, email, ano de nascimento", 'n');//FILTROS
	txtToTable(&clientsTable[1], "./clients",'y');
	
	// LOOP DO PROGRAMA
	while(state > -3){
		
		//MÁQUINA DE ESTADOS
		if(state == 0){
			state = state0(input, &menuFrames[0]);
		}
		
		else if(state == -1){
			state = stateInvalid(input, &menuFrames[4], lastState);
		}
		else if(state == -2){
			state = stateSucess(input, &menuFrames[5], lastState);
		}
		
		//FILMES
		else if(state > 0 && state < 200 && state != 2 && state != 20  && state != 21 && state != 23 && state != 24 && state != 25){
			if(state == 1)
				state = state1(input, &lastState, &frames[0], height,&moviesTable[movieFilter]);
		
			else if(state == 10)//MENU DE OPÇÕES
				state = state10(input, &lastState, &menuFrames[1], &moviesTable[0],  &moviesTable[1], &movieFilter);
		
			else if(state == 11)
				state = state11(input, &lastState, &movieFilter,&menuFrames[2], &moviesTable[1]);
		
			else if(state == 111)
				state = state111(input, &lastState, &movieFilter, &menuFrames[3], &moviesTable[0], &moviesTable[1]);
		
			else if(state == 112)
				state = state112(input, &lastState, &movieFilter, &frames[1], &moviesTable[0], &moviesTable[1]);

			else if(state == 113)
				state = state113(input, &lastState, &movieFilter, &frames[1], &moviesTable[0], &moviesTable[1]);

			else if(state == 13 || state == 131 || state == 132)//CADASTRAR FILME
				state = state13(state, input, &lastState, &frames[1], &moviesTable[0]);
			
			else if(state == 133)//GENERO DO CADASTRO
				state = state133(input, &menuFrames[3], &moviesTable[0]);
			
			else if(state == 14 || state == 140 || state == 141 || state == 142)//ATUALIZAR CADASTRO
				state = state14(&idBuffer, state, input, &lastState, &frames[1], &moviesTable[0]);
			
			else if(state == 143)//ATUALIZAR GENERO
				state = state143(&idBuffer, input, &menuFrames[3], &moviesTable[0]);

			else if(state == 15 )//DESATIVAR CADASTRO
				state = state15(&idBuffer, state, input, &lastState, &frames[1], &moviesTable[0]);
		}
		
		//CLIENTES
		else if(state == 2 || state > 200 && state < 300 || state == 20  || state == 21 || state == 23 || state == 24 || state == 25){
		
			if(state == 2)
				state = state2(input, &lastState, &framesC[0], height,&clientsTable[clientFilter]);
		
			else if(state == 20)//MENU DE OPÇÕES
				state = state20(input, &lastState, &menuFrames[6], &clientsTable[0], &clientsTable[1], &clientFilter);
		
			else if(state == 21)
				state = state21(input, &lastState, &clientFilter,&menuFrames[7], &clientsTable[1]);
		
			else if(state == 212)
				state = state212(input, &lastState, &clientFilter, &framesC[1], &clientsTable[0], &clientsTable[1]);

			else if(state == 213)
				state = state213(input, &lastState, &clientFilter, &framesC[1], &clientsTable[0], &clientsTable[1]);

			else if(state == 23 || state == 231 || state == 232 || state == 233)//CADASTRAR CLIENTES
				state = state23(state, input, &lastState, &framesC[1], &clientsTable[0]);

			else if(state == 24 || state == 240 || state == 241 || state == 242)//ATUALIZAR CADASTRO
				state = state24(&idBuffer, state, input, &lastState, &framesC[1], &clientsTable[0]);

			else if(state == 25 )//DESATIVAR CADASTRO
				state = state25(&idBuffer, state, input, &lastState, &framesC[1], &clientsTable[0]);
		}
		
		//GET INPUT
		if(input != 10 && stateBuffer == state){
			input = getch();
		}
		else{
			input = '\0';
			stateBuffer = state;
		}
		
	}
	
	//ENCERRAMENTO
	clear();
	
	for(int i = 0; i < 7; i++)
		frameFree(&menuFrames[i]);
	
	tableToTxt(&moviesTable[0],"./movies");
	tableToTxt(&clientsTable[0],"./clients");
	
	for(int i = 0; i < 2; i++){
		frameFree(&frames[i]);
		tableFree(&moviesTable[i]);
	}
	
	printf("\n====================================\n");
	printf("|                                  |\n");
	printf("| Programa encerrado corretamente! |\n");
	printf("|                                  |\n");
	printf("====================================\n");
}
