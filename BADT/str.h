#ifndef STR_H
#define STR_H

/******************************************************************************/
/* DEESENVOLVIDO POR LUAN VALLE                                               */
/* https://github.com/luanvalle01/BADT                                        */
/* (V 1.0)                                                                    */
/*                                                                            */
/*  Os métodos de str.h foram criados para trabalhar de maneira mais direta   */
/* com char *.                                                                */
/*                                                                            */
/******************************************************************************/

#define true 1
#define false 0

int strLen(char *string);
int strLenPlus(char *string, char terminator);
void strCopy(char *strDestiny, char *strOrigin);
void strCat(char *strDestiny, char *strOrigin);
int strComp(char *string1, char *string2);

void toStr(char *output, void *input, char typeInput);
void getBiggest(char *string, int *bigLen);
void bufferClean(char *buffer, int size);

//ADICIONAR À BADT ORIGINAL
int justLetters(char *string);
void upperText(char *string);
int strVerify(char *input, int *letras, int *pontos);
char typeCast(char *input);

void charValue(char *input, long *out);

int strLen(char *string){

	int len = 0;
	while(string[len++] != '\0')
		continue;

	return --len;
}

int strLenPlus(char *string, char terminator){

	int len = 0;
	while(string[len++] != terminator)
		continue;

	return --len;
}

void strCopy(char *strDestiny, char *strOrigin){

	int i = 0;
	int size = strLen(strOrigin);
	
	for(i; i < size; i++)
		strDestiny[i] = strOrigin[i];
}

void strCat(char *strDestiny, char *strOrigin){

	int sizeOrigin = strLen(strOrigin);
	int sizeDestiny = strLen(strDestiny);
	int max = sizeOrigin + sizeDestiny;


	for(int i = sizeDestiny; i < max; i++)
		strDestiny[i] = strOrigin[i - sizeDestiny];

	strDestiny[max + 1] = '\0';
}

int strComp(char *string1, char *string2){

	int i = 0;
	int fails = 0;
	
	while(string1[i] != '\0' && string2[i] != '\0'){
		if(string1[i] != string2[i])
			fails++;
		i++;
	}
	
	return fails;
}

void toStr(char *output, void *input, char typeInput){

	output = (char *)malloc(30);

	if(typeInput == 'd' || typeInput == 'i'){
		int *buffer = (int *)input;
		sprintf(output,"%d\n", *buffer);
	}

	else if(typeInput == 'f'){
		float *buffer = (float *)input;
		sprintf(output,"%.2f\n", *buffer);
	}

	output = (char *)realloc(output, strLen(output));
}

void getBiggest(char *string, int *bigLen){

	int len = 0;
	while(string[len++] != '\0')
		continue;

	if(len > *bigLen)
		*bigLen = len;
}

void bufferClean(char *buffer, int size){
	
	for(int i = 0; i < size; i++)
		buffer[i] = '\0';
}

int justLetters(char *string){

	int index = 0;
	while(string[index] != '\0'){
		if(!(string[index] > 64 && string[index] < 91)  || !(string[index] > 96 && string[index] < 123))
			return 0; // FALSE
		index++;
	}
	
	return 1;
}

void upperText(char *string){

	int index = 0;
	while(string[index] != '\0'){
		if(string[index] > 96 && string[index] < 122)
			string[index] -= 32;
			
		index++;
	}
}

int strVerify(char *input, int *letras, int *pontos){

	/* Retorna quantas letras e     */
	/* pontos existem em uma string */

	int quantidade = strLen(input);

	//Referencias ASCII
	char ascii = '0';
	char ponto = '.';

	for(int i = 0; i < quantidade; i++){
		if(input[i] == ponto){
			*pontos += 1;
		}

		//Verifica se o char é um número entre 0 e 9
		int encontrado = 0;
		if(input[i] > 47 && input[i] < 58)
			encontrado = 1;
		
		//Caso não seja o contador de erros aumenta
		if(encontrado < 1 && input[i] != ponto){
			*letras += 1;
		}
	}
}

char typeCast(char *input){

	//Verificar o tamanho da string para diferir int dos demais tipos
	int erros = 0;
	int pontos = 0;

	strVerify(input, &erros, &pontos);

	if(pontos == 1 && erros == 0){
		return 'f';
	}
	else if(pontos < 1 && erros == 0){
		return 'i';
	}
	else{
		return 's';
	}
}

void charValue(char *input, long *out){

	int i = 0;
	int weight = 1;
	
	*out = 999999999999999999;
	
	upperText(input);
	
	while(input[i] != '\0'){
		if (input[i] > 64)
			*out -= (input[i]*9999999999) / weight;
		i++;
		weight += 90;
	}
}


#endif
