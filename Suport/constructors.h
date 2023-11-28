#ifndef CONSTRUCTORS_H
#define CONSTRUCTORS_H

void updateFrame(Frame *frame, char *buffer){
	frame->inputBuffer[0] = buffer[0];
	frameRefresh(frame);
			
	clear();
	imageShow(&frame->image);
}

void showFrame(Frame *frame){
	clear();
	imageShow(&frame->image);
}

void resetOcult(Table *table){
	for(int i = 0; i < table->qtdLine-1; i++)
			tableUpdate(table,0,i,"  ");
}

//MAIN
void setupInvalidInput(Frame *frame, int height);//MENU
void setupMainMenu(Frame *frame, int height);//MENU
void setupSucess(Frame *frame, int height);//MENU

//MOVIE CONSTRUCTOR
void setupMovieMenu(Frame *frame, Table *table, int height);//TABLE
void setupMovieOptions(Frame *frame, int height);//MENU
void setupMovieFilter(Frame *frame, int height);//MENU
void setupMovieFilterG(Frame *frame, int height);//MENU
void setupMovieFilterL(Frame *frame);//INPUT LEN 35
void setupMovieFilterY(Frame *frame);//INPUT LEN 4

//CLIENT COSTRUCTOR
void setupClientMenu(Frame *frame, Table *table, int height);//TABLE
void setupClientOptions(Frame *frame, int height);//MENU
void setupClientFilter(Frame *frame, int height);//MENU
void setupClientFilterL(Frame *frame);//INPUT LEN 35
void setupClientFilterCPF(Frame *frame);//INPUT LEN 8
void setupClientRegister(Frame *frame, int state);

//-------//

void setupInvalidInput(Frame *frame, int height){
	frameFree(frame);

	frameSetup(frame, "ENTRADA INVALIDA", 52, height, 'n');

	frameInsertCenter(frame, "Como deseja proceder?", 2);

	frameInsertOption(frame, "Tentar novamente");
	frameInsertOption(frame, "Cancelar");
}


void setupSucess(Frame *frame, int height){
	frameFree(frame);

	frameSetup(frame, "CADASTRO EFETUADO", 52, height, 'n');

	frameInsertCenter(frame, "Cadastro efetuado com sucesso!", 2);

	frameInsertOption(frame, "OK");
}

void setupMainMenu(Frame *frame, int height){
	frameFree(frame);

	frameSetup(frame, "MENU PRINCIPAL", 52, height, 'n');

	frameInsertCenter(frame, "Seja bem vindo!", 2);

	frameInsertOption(frame, "Consultar Filmes");
	frameInsertOption(frame, "Consultar Clientes");
	frameInsertOption(frame, "Consultar Pedidos");
	frameInsertOption(frame, "Sair");
	
	frameInsert(frame, "NOTA: Esse trabalho deu trabalho", 2, height - 3);
	frameInsert(frame, "se concorda respira.", 2, height - 2);
}

void setupMovieMenu(Frame *frame, Table *table, int height){
	frameFree(frame);

	frameSetup(frame, "FILMES", 125, height, 'n');
	
	frameSetTable(frame, table);
	frameRefresh(frame);
}

void setupMovieOptions(Frame *frame, int height){
	frameFree(frame);

	frameSetup(frame, "MENU FILMES", 52, height, 'n');
	frameInsertCenter(frame, "O que deseja fazer?", 2);

	frameInsertOption(frame, "Filtrar Filmes");
	frameInsertOption(frame, "Limpar Filtros");
	frameInsertOption(frame, "Cadastrar Filme");
	frameInsertOption(frame, "Atualizar Cadastro");
	frameInsertOption(frame, "Desativar Cadastro");
	frameInsertOption(frame, "Voltar para menu principal");
	
}

void setupMovieFilter(Frame *frame, int height){
	frameFree(frame);

	frameSetup(frame, "FILTRAR FILME", 50, height, 'n');

	frameInsertCenter(frame, "Escolha como deseja filtrar:", 2);
	
	frameInsertOption(frame, "Filtrar por genero");
	frameInsertOption(frame, "Filtrar por nome");
	frameInsertOption(frame, "Filtrar por ano");
	frameInsertOption(frame, "Ordenar por id");
	frameInsertOption(frame, "Ordenar por nome");
}

void setupMovieFilterG(Frame *frame, int height){
	frameFree(frame);

	frameSetup(frame, "FILTRAR POR GENERO", 50, height, 'n');

	frameInsertCenter(frame, "Selecione um genero deseja:", 2);
	
	frameInsertOption(frame, "Acao");
	frameInsertOption(frame, "Aventura");
	frameInsertOption(frame, "Comedia");
	frameInsertOption(frame, "Drama");
	frameInsertOption(frame, "Romance");
	frameInsertOption(frame, "Suspense");
	frameInsertOption(frame, "Terror");
}

void setupMovieFilterL(Frame *frame){
	frameFree(frame);

	frameSetup(frame, "FILTRAR POR NOME", 50, 5, 'n');
	frameSetInput(frame, "Digite o nome: ",35);
}

void setupMovieFilterY(Frame *frame){
	frameFree(frame);

	frameSetup(frame, "FILTRAR POR ANO", 50, 5, 'n');
	frameSetInput(frame, "Digite o ano: ",4);
}

void setupMovieRegister(Frame *frame, int state){
	frameFree(frame);
	
	if(state == 13 || state == 131 || state == 132)
		frameSetup(frame, "===CADASTRAR NOVO FILME===", 50, 5, 'n');
	else if(state == 14 ||state == 140 || state == 141 || state == 142)
		frameSetup(frame, "======ATUALIZAR FILME=====", 50, 5, 'n');
	else if(state == 15)
		frameSetup(frame, "======DESATIVAR FILME=====", 50, 5, 'n');
	
	if(state == 14 || state == 15)
		frameSetInput(frame, "Digite o id do filme: ",9);
	
	if(state == 13 || state == 140)
		frameSetInput(frame, "Digite o nome: ",35);

	else if(state == 131 || state == 141)
		frameSetInput(frame, "Digite o ano: ",4);

	else if(state == 132 || state == 142)
		frameSetInput(frame, "Digite a duracao em horas: ",3);

}

//-------//

void setupClientMenu(Frame *frame, Table *table, int height){
	frameFree(frame);

	frameSetup(frame, "CLIENTES", 125, height, 'n');
	
	frameSetTable(frame, table);
	frameRefresh(frame);
}

void setupClientOptions(Frame *frame, int height){
	frameFree(frame);

	frameSetup(frame, "MENU CLIENTES", 52, height, 'n');
	frameInsertCenter(frame, "O que deseja fazer?", 2);

	frameInsertOption(frame, "Filtrar Clientes");
	frameInsertOption(frame, "Limpar Filtros");
	frameInsertOption(frame, "Cadastrar Clientes");
	frameInsertOption(frame, "Atualizar Cadastro");
	frameInsertOption(frame, "Desativar Cadastro");
	frameInsertOption(frame, "Voltar para menu principal");
	
}

void setupClientFilter(Frame *frame, int height){
	frameFree(frame);

	frameSetup(frame, "FILTRAR CLIENTES", 50, height, 'n');

	frameInsertCenter(frame, "Escolha como deseja filtrar:", 2);
	
	frameInsertOption(frame, "Filtrar por CPF");
	frameInsertOption(frame, "Filtrar por nome");
	frameInsertOption(frame, "Ordenar por CPF");
	frameInsertOption(frame, "Ordenar por nome");
}

void setupClientFilterL(Frame *frame){
	frameFree(frame);

	frameSetup(frame, "FILTRAR POR NOME", 50, 5, 'n');
	frameSetInput(frame, "Digite o nome: ",35);
}

void setupClientFilterCPF(Frame *frame){
	frameFree(frame);

	frameSetup(frame, "FILTRAR POR CPF", 50, 5, 'n');
	frameSetInput(frame, "Digite o CPF: ",8);
}

void setupClientRegister(Frame *frame, int state){
	frameFree(frame);
	
	if(state == 23 || state == 231 || state == 232 || state == 233)
		frameSetup(frame, "===CADASTRAR NOVO CLIENTE===", 50, 5, 'n');
	else if(state == 24 ||state == 240 || state == 241 || state == 242 || state == 243)
		frameSetup(frame, "======ATUALIZAR CLIENTE=====", 50, 5, 'n');
	else if(state == 25)
		frameSetup(frame, "======DESATIVAR CLIENTE=====", 50, 5, 'n');
	
	if(state == 23 || state == 24)
		frameSetInput(frame, "Digite o cpf: ",10);
	
	if(state == 231 || state == 241)
		frameSetInput(frame, "Digite o nome: ",35);

	else if(state == 232 || state == 242)
		frameSetInput(frame, "Digite o email: ",35);

	else if(state == 233 || state == 243)
		frameSetInput(frame, "Digite o ano de nascimento: ",4);

}

//-------//

#endif

