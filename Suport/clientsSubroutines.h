#include "constructors.h"
#include <time.h>

int state2(char input , int *lastState, Frame *frame, int height, Table *clientsTable){
//EXIBIÇÃO DOS CLIENTES

	if(!*lastState){//INICIALIZANDO FRAME
		frameFree(frame);
		setupClientMenu(frame, clientsTable, height);
		*lastState = 2;
	}
	
	frameSetTable(frame, clientsTable);
			
	updateFrame(frame, &input);
	showFrame(frame);
			
	if(input == 'o' || input == 'O'){
		return 20;
	}
	
	return 2;
}

int state20(char input, int *lastState, Frame *frame, Table *clientsTable, int *clientsFilter){
//OPÇÕES DOS CLIENTES

	updateFrame(frame, &input);
	showFrame(frame);
			
	if(input == 10){
	switch(frame->optionSelect){
	
	case 0:
		*lastState = 20;
		return 21;
		break;
		
	case 1:
		tableRefresh(clientsTable);
		*clientsFilter = 0;
		return 2;
		break;
		
	case 2:
		return 23;
		break;
		
	case 3:
		return 24;
		break;
		
	case 4:
		return 25;
		break;
		
	default:
		for(int i = 0; i < 6; i++)
			frameCursorSub(frame);
		return 0;
	}
	}
	
	return 20;
}

int state21(char input, int *lastState, int *clientsFilter,Frame *frame, Table *tableFilter){
//OPÇÕES DE FILTRO
	
	updateFrame(frame, &input);
	showFrame(frame);
		
	if(input == 10){
		switch(frame->optionSelect){
			case 0:
				*lastState = 21;
				return 212;
				break;
			case 1:
				*lastState = 21;
				return 213;
				break;
			case 2:
				*clientsFilter = 1;
				tableOrder(tableFilter, 1);
				return 2;
				break;
			case 3:
				*clientsFilter = 1;
				tableOrder(tableFilter,2);
				return 2;
				break;
		}		
	}
	
	return 21;
}

int state212(char input, int *lastState, int *clientsFilter, Frame *frame, Table *clientsTable, Table *tableFilter){
//FILTRAR CLIENTES POR CPF
	*clientsFilter = 1;
	
	if(*lastState != 213){
		setupClientFilterCPF(frame);
		*lastState = 213;
	}

	updateFrame(frame, &input);
	showFrame(frame);
			
	//input
	char *inputBuffer = frameGetInput(frame);
	//Saida da Tabela
	char *outBuffer = (char *)malloc(clientsTable->bigOfCol[3] + 2);
	bufferClean(outBuffer, clientsTable->bigOfCol[3] + 1);
	
	if(input == 10){
		*clientsFilter = 1;
		for(int i = 0; i < clientsTable->qtdLine; i++){
			tableGet(clientsTable, 1, i, outBuffer);
				
			if(strComp(outBuffer, inputBuffer)  < strLen(inputBuffer)){
				tableGet(clientsTable, 0, i, outBuffer);
				if(outBuffer[0] != ';')
					tableUpdate(tableFilter,0,i,"  ");
			}
			else{
				tableUpdate(tableFilter,0,i,": ");
			}
		}
		frameInputClean(frame);
		return 2;
	}
	
	return 212;
}

int state213(char input, int *lastState, int *clientsFilter, Frame *frame, Table *clientsTable, Table *tableFilter){
//FILTRAR CLIENTES POR NOME

	*clientsFilter = 1;
	
	if(*lastState != 213){
		setupClientFilterL(frame);
		*lastState = 213;
	}

	updateFrame(frame, &input);
	showFrame(frame);
			
	//input
	char *inputBuffer = frameGetInput(frame);
	//Saida da Tabela
	char *outBuffer = (char *)malloc(clientsTable->bigOfCol[2] + 2);
	bufferClean(outBuffer, clientsTable->bigOfCol[2] + 1);
	
	if(input == 10){
		*clientsFilter = 1;
		for(int i = 0; i < clientsTable->qtdLine; i++){
			upperText(inputBuffer);
			tableGet(clientsTable, 2, i, outBuffer);
				
			if(strComp(outBuffer, inputBuffer) < 2){
				tableGet(clientsTable, 0, i, outBuffer);
				if(outBuffer[0] != ';')
					tableUpdate(tableFilter,0,i,"  ");
			}
			else{
				tableUpdate(tableFilter,0,i,": ");
			}
		}
		frameInputClean(frame);
		return 2;
	}
	
	return 213;
}

int state23(int state, char input, int *lastState, Frame *frame, Table *clientsTable){
//CADASTRAR CLIENTES

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
		int line = clientsTable->qtdLine;
	
		if(strLen(inputBuffer) < 2){
			*lastState = state;
			frameInputClean(frame);
			return -1;	
		}
			
		if(state == 23){//id / nome
			upperText(inputBuffer);
			
			if(strLen(inputBuffer)){
				tableNewLine(clientsTable);
				tableInsert(clientsTable, 1, line, &line);//id
				tableInsert(clientsTable, 2, line, inputBuffer);//nome
				frameInputClean(frame);
				return 231;	
			}
			fail = true;
		}
		else if(state == 231){//ano
			long now;
			time(&now);
			now = (now/31557600) + 1970;
			
			if(typeCast(inputBuffer) == 'i' && strLen(inputBuffer) == 4){
				int value = atoi(inputBuffer);
				int line = clientsTable->qtdLine;
				
				if(value <= now){
					tableInsert(clientsTable, 3, line-1, &value);
					frameInputClean(frame);
					return 232;
				}
			}
			fail = true;
		}
		else if(state == 232){//duracao
			if(typeCast(inputBuffer) == 'f' && strLen(inputBuffer) == 3){
				float value = atof(inputBuffer);
				int line = clientsTable->qtdLine;
			
				tableInsert(clientsTable, 5, line-1, &value);
				return 233;
			}
			
			fail = true;
		}
		
		if(fail){
			*lastState = state;
			frameInputClean(frame);
			return -1;
		}
		return 2;
	}
	return state;
}

int state24(int *idBuffer,int state, char input, int *lastState, Frame *frame, Table *clientsTable){
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
	
	if(input == 20){
		int line = clientsTable->qtdLine;
	
		if(strLen(inputBuffer) < 1){
			*lastState = state;
			frameInputClean(frame);
			return -1;	
		}
		
		if(state == 24){//id 
			
			*idBuffer = atoi(inputBuffer);
			upperText(inputBuffer);
			
			if(*idBuffer || !*idBuffer && inputBuffer[0] == '0'){
			
				if(*idBuffer < line){
					frameInputClean(frame);
					return 240;
				}
			}
			else if(strComp(inputBuffer, "ULTIMO") == 0){
			
				*idBuffer =	line-1;
				frameInputClean(frame);
				return 240;
			}
			fail = true;
		}
			
		if(state == 240){//nome
			upperText(inputBuffer);
			
			if(strLen(inputBuffer)){
				tableUpdate(clientsTable, 2, *idBuffer, inputBuffer);//nome
				frameInputClean(frame);
				return 241;
			}
			fail = true;
			
		}
		else if(state == 241){//ano
			long now;
			time(&now);
			now = (now/31557600) + 1970;
			
			if(typeCast(inputBuffer) == 'i' && strLen(inputBuffer) == 4){
				int value = atoi(inputBuffer);
				
				if(value <= now){
					tableUpdate(clientsTable, 3, *idBuffer, &value);
					frameInputClean(frame);
					return 242;
				}
			}
			fail = true;
		}
		else if(state == 242){//duracao
			if(typeCast(inputBuffer) == 'f' && strLen(inputBuffer) == 3){
				float value = atof(inputBuffer);
				int line = clientsTable->qtdLine;
			
				tableUpdate(clientsTable, 5, *idBuffer, &value);
				return 243;
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

int state25(int *idBuffer,int state, char input, int *lastState, Frame *frame, Table *clientsTable){
//DESATIVAR CLIENTE

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
		int line = clientsTable->qtdLine;
	
		if(strLen(inputBuffer) < 1){
			*lastState = state;
			frameInputClean(frame);
			return -1;	
		}
		
		if(state == 25){//id 
			
			*idBuffer = atoi(inputBuffer);
			upperText(inputBuffer);
			
			if(*idBuffer || !*idBuffer && inputBuffer[0] == '0'){
			
				if(*idBuffer < line){
					tableUpdate(clientsTable, 0, *idBuffer, ";");
					frameInputClean(frame);
					return -2;
				}
			}
			else if(strComp(inputBuffer, "ULTIMO") == 0){
			
				*idBuffer =	line-1;
				tableUpdate(clientsTable, 0, *idBuffer, ";");
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
		return 2;
	}
	return state;
}
