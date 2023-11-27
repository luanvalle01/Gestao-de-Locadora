#include "constructors.h"
#include <time.h>

int state1(char input , int *lastState, Frame *frame, int height, Table *moviesTable){
//EXIBIÇÃO DOS FILMES

	if(!*lastState){//INICIALIZANDO FRAME
		frameFree(frame);
		setupMovieMenu(frame, moviesTable, height);
		*lastState = 1;
	}
	
	frameSetTable(frame, moviesTable);
			
	updateFrame(frame, &input);
	showFrame(frame);
			
	if(input == 'o' || input == 'O'){
		return 10;
	}
	
	return 1;
}

int state10(char input, int *lastState, Frame *frame, Table *moviesTable, int *movieFilter){
//OPÇÕES DOS FILMES

	updateFrame(frame, &input);
	showFrame(frame);
			
	if(input == 10){
	switch(frame->optionSelect){
	
	case 0:
		*lastState = 10;
		return 11;
		break;
		
	case 1:
		tableRefresh(moviesTable);
		*movieFilter = 0;
		return 1;
		break;
		
	case 2:
		return 13;
		break;
		
	case 3:
		return 14;
		break;
		
	case 4:
		return 15;
		break;
		
	default:
		for(int i = 0; i < 6; i++)
			frameCursorSub(frame);
		return 0;
	}
	}
	
	return 10;
}

int state11(char input, int *lastState, int *movieFilter,Frame *frame, Table *tableFilter){
//OPÇÕES DE FILTRO
	
	updateFrame(frame, &input);
	showFrame(frame);
		
	if(input == 10){
		switch(frame->optionSelect){
			case 0:
				*lastState = 11;
				return 111;
				break;
			case 1:
				return 112;
				break;
			case 2:
				*lastState = 11;
				return 113;
				break;
			case 3:
				*movieFilter = 1;
				tableOrder(tableFilter, -1);
				return 1;
				break;
			case 4:
				*movieFilter = 1;
				tableOrder(tableFilter,2);
				return 1;
				break;
		}		
	}
	
	return 11;
}

int state111(char input, int *lastState, int *movieFilter, Frame *frame, Table *moviesTable, Table *moviesTableFilter){
//FILTRAR FILME POR GENERO

	*movieFilter = 1;
	
	updateFrame(frame, &input);
	showFrame(frame);
			
	//Genero Escolhido
	char *select = (char *)malloc(moviesTable->bigOfCol[4] + 2);
	bufferClean(select, moviesTable->bigOfCol[4] + 1);
	//Saida da Tabela
	char *outBuffer = (char *)malloc(moviesTable->bigOfCol[4] + 2);
	bufferClean(outBuffer, moviesTable->bigOfCol[4] + 1);
			
	if(input == 10){	
	switch(frame->optionSelect){
		case 0:
			strCopy(select,"Acao");
			break;
		case 1:
			strCopy(select,"Aventura");
			break;
		case 2:
			strCopy(select,"Comedia");
			break;
		case 3:
			strCopy(select,"Drama");
			break;	
		case 4:
			strCopy(select,"Romance");
			break;
		case 5:
			strCopy(select,"Suspense");
			break;
		case 6:
			strCopy(select,"Terror");
			break;
	}
				
	for(int i = 0; i < moviesTable->qtdLine; i++){
		tableGet(moviesTable, 4, i, outBuffer);
					
		if((strComp(select, outBuffer) < 2)){
			tableGet(moviesTable, 0, i, outBuffer);
			if(outBuffer[0] != ';')
				tableUpdate(moviesTableFilter,0,i,"  ");
		}
		else{
			moviesTableFilter->qtdLine--;
			tableUpdate(moviesTableFilter,0,i,": ");
		}
	}
		
	free(select);
	free(outBuffer);
	frameInputClean(frame);
	return 1;
	}
	
	*lastState = 111;
	return 111;
}

int state112(char input, int *lastState, int *movieFilter, Frame *frame, Table *moviesTable, Table *moviesTableFilter){
//FILTRAR FILME POR NOME

	*movieFilter = 1;
	
	if(*lastState != 113){
		setupMovieFilterL(frame);
		*lastState = 113;
	}

	updateFrame(frame, &input);
	showFrame(frame);
			
	//input
	char *inputBuffer = frameGetInput(frame);
	//Saida da Tabela
	char *outBuffer = (char *)malloc(moviesTable->bigOfCol[2] + 2);
	bufferClean(outBuffer, moviesTable->bigOfCol[2] + 1);
	
	if(input == 10){
		*movieFilter = 1;
		for(int i = 0; i < moviesTable->qtdLine; i++){
			upperText(inputBuffer);
			tableGet(moviesTable, 2, i, outBuffer);
				
			if(strComp(outBuffer, inputBuffer) < 2){
				tableGet(moviesTable, 0, i, outBuffer);
				if(outBuffer[0] != ';')
					tableUpdate(moviesTableFilter,0,i,"  ");
			}
			else{
				tableUpdate(moviesTableFilter,0,i,": ");
			}
		}
		frameInputClean(frame);
		return 1;
	}
	
	return 112;
}

int state113(char input, int *lastState, int *movieFilter, Frame *frame, Table *moviesTable, Table *moviesTableFilter){
//FILTRAR FILME POR ANO
	*movieFilter = 1;
	
	if(*lastState != 113){
		setupMovieFilterY(frame);
		*lastState = 113;
	}

	updateFrame(frame, &input);
	showFrame(frame);
			
	//input
	char *inputBuffer = frameGetInput(frame);
	//Saida da Tabela
	char *outBuffer = (char *)malloc(moviesTable->bigOfCol[3] + 2);
	bufferClean(outBuffer, moviesTable->bigOfCol[3] + 1);
	
	if(input == 10){
		*movieFilter = 1;
		for(int i = 0; i < moviesTable->qtdLine; i++){
			tableGet(moviesTable, 3, i, outBuffer);
				
			if(strComp(outBuffer, inputBuffer)  == 0){
				tableGet(moviesTable, 0, i, outBuffer);
				if(outBuffer[0] != ';')
					tableUpdate(moviesTableFilter,0,i,"  ");
			}
			else{
				tableUpdate(moviesTableFilter,0,i,": ");
			}
		}
		frameInputClean(frame);
		return 1;
	}
	
	return 113;
}

int state13(int state, char input, int *lastState, Frame *frame, Table *moviesTable){
//CADASTRAR FILME

	int fail = false;

	if(*lastState != state){
		setupMovieRegister(frame, state);
		*lastState = state;
	}

	updateFrame(frame, &input);
	showFrame(frame);

	//input
	char *inputBuffer = frameGetInput(frame);
	
	if(input == 10){
		int line = moviesTable->qtdLine;
	
		if(strLen(inputBuffer) < 2){
			*lastState = state;
			frameInputClean(frame);
			return -1;	
		}
			
		if(state == 13){//id / nome
			upperText(inputBuffer);
			
			if(strLen(inputBuffer)){
				tableNewLine(moviesTable);
				tableInsert(moviesTable, 1, line, &line);//id
				tableInsert(moviesTable, 2, line, inputBuffer);//nome
				frameInputClean(frame);
				return 131;	
			}
			fail = true;
		}
		else if(state == 131){//ano
			long now;
			time(&now);
			now = (now/31557600) + 1970;
			
			if(typeCast(inputBuffer) == 'i' && strLen(inputBuffer) == 4){
				int value = atoi(inputBuffer);
				int line = moviesTable->qtdLine;
				
				if(value <= now){
					tableInsert(moviesTable, 3, line-1, &value);
					frameInputClean(frame);
					return 132;
				}
			}
			fail = true;
		}
		else if(state == 132){//duracao
			if(typeCast(inputBuffer) == 'f' && strLen(inputBuffer) == 3){
				float value = atof(inputBuffer);
				int line = moviesTable->qtdLine;
			
				tableInsert(moviesTable, 5, line-1, &value);
				return 133;
			}
			
			fail = true;
		}
		
		if(fail){
			*lastState = state;
			frameInputClean(frame);
			return -1;
		}
		return 1;
	}
	return state;
}

int state133(char input, Frame *frame, Table *moviesTable){
//CADASTRO GENERO

	updateFrame(frame, &input);
	showFrame(frame);

	if(input == 10){
		int line = moviesTable->qtdLine;
		
		switch(frame->optionSelect){
			case 0:
				tableInsert(moviesTable, 4, line-1, "Acao\0");
				break;
			case 1:
				tableInsert(moviesTable, 4, line-1, "Aventura\0");
				break;
			case 2:
				tableInsert(moviesTable, 4, line-1, "Comedia\0");
				break;
			case 3:
				tableInsert(moviesTable, 4, line-1, "Drama\0");
				break;	
			case 4:
				tableInsert(moviesTable, 4, line-1, "Romance\0");
				break;
			case 5:
				tableInsert(moviesTable, 4, line-1, "Suspense\0");
				break;
			case 6:
				tableInsert(moviesTable, 4, line-1, "Terror\0");
				break;
		}
		tableRefresh(moviesTable);
		return -2;
	}
	return 133;
}

int state14(int *idBuffer,int state, char input, int *lastState, Frame *frame, Table *moviesTable){
//ATUALIZAR FILME

	int fail = false;
	//input
	char *inputBuffer = frameGetInput(frame);

	if(*lastState != state){
		setupMovieRegister(frame, state);
		*lastState = state;
		frameInputClean(frame);
	}

	updateFrame(frame, &input);
	showFrame(frame);
	
	if(input == 10){
		int line = moviesTable->qtdLine;
	
		if(strLen(inputBuffer) < 1){
			*lastState = state;
			frameInputClean(frame);
			return -1;	
		}
		
		if(state == 14){//id 
			
			*idBuffer = atoi(inputBuffer);
			upperText(inputBuffer);
			
			if(*idBuffer || !*idBuffer && inputBuffer[0] == '0'){
			
				if(*idBuffer < line){
					frameInputClean(frame);
					return 140;
				}
			}
			else if(strComp(inputBuffer, "ULTIMO") == 0){
			
				*idBuffer =	line-1;
				frameInputClean(frame);
				return 140;
			}
			fail = true;
		}
			
		if(state == 140){//nome
			upperText(inputBuffer);
			
			if(strLen(inputBuffer)){
				tableUpdate(moviesTable, 2, *idBuffer, inputBuffer);//nome
				frameInputClean(frame);
				return 141;
			}
			fail = true;
			
		}
		else if(state == 141){//ano
			long now;
			time(&now);
			now = (now/31557600) + 1970;
			
			if(typeCast(inputBuffer) == 'i' && strLen(inputBuffer) == 4){
				int value = atoi(inputBuffer);
				
				if(value <= now){
					tableUpdate(moviesTable, 3, *idBuffer, &value);
					frameInputClean(frame);
					return 142;
				}
			}
			fail = true;
		}
		else if(state == 142){//duracao
			if(typeCast(inputBuffer) == 'f' && strLen(inputBuffer) == 3){
				float value = atof(inputBuffer);
				int line = moviesTable->qtdLine;
			
				tableUpdate(moviesTable, 5, *idBuffer, &value);
				return 143;
			}
			fail = true;
		}
		
		if(fail){
			*lastState = state;
			frameInputClean(frame);
			return -1;
		}
		return 1;
	}
	return state;
}

int state143(int *idBuffer, char input, Frame *frame, Table *moviesTable){
//ATUALIZAR GENERO 

	updateFrame(frame, &input);
	showFrame(frame);

	if(input == 10){

		switch(frame->optionSelect){
			case 0:
				tableUpdate(moviesTable, 4, *idBuffer, "Acao\0");
				break;
			case 1:
				tableUpdate(moviesTable, 4, *idBuffer, "Aventura\0");
				break;
			case 2:
				tableUpdate(moviesTable, 4, *idBuffer, "Comedia\0");
				break;
			case 3:
				tableUpdate(moviesTable, 4, *idBuffer, "Drama\0");
				break;	
			case 4:
				tableUpdate(moviesTable, 4, *idBuffer, "Romance\0");
				break;
			case 5:
				tableUpdate(moviesTable, 4, *idBuffer, "Suspense\0");
				break;
			case 6:
				tableUpdate(moviesTable, 4, *idBuffer, "Terror\0");
				break;
		}
		tableRefresh(moviesTable);
		return -2;
	}
	return 143;
}

int state15(int *idBuffer,int state, char input, int *lastState, Frame *frame, Table *moviesTable){
//DESATIVAR FILME

	int fail = false;
	//input
	char *inputBuffer = frameGetInput(frame);

	if(*lastState != state){
		setupMovieRegister(frame, state);
		*lastState = state;
		frameInputClean(frame);
	}

	updateFrame(frame, &input);
	showFrame(frame);
	
	if(input == 10){
		int line = moviesTable->qtdLine;
	
		if(strLen(inputBuffer) < 1){
			*lastState = state;
			frameInputClean(frame);
			return -1;	
		}
		
		if(state == 15){//id 
			
			*idBuffer = atoi(inputBuffer);
			upperText(inputBuffer);
			
			if(*idBuffer || !*idBuffer && inputBuffer[0] == '0'){
			
				if(*idBuffer < line){
					tableUpdate(moviesTable, 0, *idBuffer, ";");
					frameInputClean(frame);
					return -2;
				}
			}
			else if(strComp(inputBuffer, "ULTIMO") == 0){
			
				*idBuffer =	line-1;
				tableUpdate(moviesTable, 0, *idBuffer, ";");
				frameInputClean(frame);
				return -2;
			}
			fail = true;
		}
		
		if(fail){
			*lastState = state;
			frameInputClean(frame);
			return -1;
		}
		return 1;
	}
	return state;
}
