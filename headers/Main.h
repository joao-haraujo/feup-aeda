#ifndef HEADERS_MAIN_H_
#define HEADERS_MAIN_H_

#include "../headers/Header.h"
#include "../headers/Utilizador.h"

class Main {
private:
	vector<vector<string> > menu;
	int option = 0;
	vector<Utilizador> utilizadores;
	Utilizador* currentUser = NULL;

public:
	Main(){} //default constructor

	bool importUtilizadores();
	bool exportUtilizadores();
	int exitFunction();

	void setMenus(vector<vector<string> > menu);
	void setUtilizadores(vector<Utilizador> utilizadores);

	//Menu functions
	int menuInicial();
	int menuLogin();
	int menuRegisto();
	int menuUtilizador();
	int menuEditDadosConta();

	void resetOption();
	int displayMenuOptions(int position);
	void displayUsers() const;
	void displayCurrentUser() const;
	bool editDadosConta(int option);
	void editDadosCondomino();
	bool validLogin(string utilizador, string password);
	bool validRegister(string utilizador, string password);
	bool addUtilizador(Utilizador utilizador);
	bool eraseUtilizador(string nomeUtilizador);
};

const string currentDateTime();
void displayTime();
void pressEnterToContinue();
vector<vector<string> > createMenuOptions();
vector<Utilizador> createUtilizadores();
bool hasWhitespace(string s);
int main();

#endif /* HEADERS_MAIN_H_ */