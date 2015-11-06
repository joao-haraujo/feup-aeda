#include "../headers/Main.h"

#include "../headers/Header.h"
#include "../headers/Utils.h"

#define pathLogo "../savedata/logo.txt"
#define pathCondominio "../savedata/condominio.txt"
#define pathCondominos "../savedata/condominos.txt"
#define pathHabitacoes "../savedata/habitacoes.txt"
#define pathFuncionarios "../savedata/funcionarios.txt"
#define pathServicos "../savedata/servicos.txt"

vector<string> mesesAno;
vector<vector<string> > menu;

/*
 * Class functions
 */

/**
 * Displays month and time of the day in position (x,y) = (50,20), using currentDateTime().
 */
void Main::displayTime() {
	string time = currentTime();
	gotoxy(50, 20);
	cout << mesesAno[this->condominio.getMes()] << "\t" << time;
}

/**
 * Sets the menu options vector (this is only done on startup).
 * @param menu New menu.
 */
void Main::setMenus(vector<vector<string> > menu) {
	this->menu = menu;
}
/**
 * Sets the currentUser pointer.
 * @param condomino Copy of a condomino to be searched in the users menu and set as currentUser.
 */
void Main::setCurrentUser(Condomino condomino) {
	int pos = sequentialSearch(this->condominio.getMoradores(), condomino);
	if (pos == -1) {
		this->currentUser = NULL;
	} else
		this->currentUser = this->condominio.getCondomino(pos);
}

/**
 * Resets menu option to 0. Called every time we switch to a new menu.
 */
void Main::resetOption() {
	this->option = 0;
}
/**
 * Prints a Yes/No select screen.
 * @param option If 0, highlights "Yes", else if 1, highlights "No".
 */
bool Main::displayYesNo(int option) {
	if (option >= 2) {
		return EXIT_FAILURE;
	}

	if (option == 0) {
		setcolor(BLACK, LIGHTGREY);
		cout << "Sim";
		setcolor(WHITE, BLACK);
		cout << "\tNao" << endl;
	} else if (option == 1) {
		setcolor(WHITE, BLACK);
		cout << "Sim\t";
		setcolor(BLACK, LIGHTGREY);
		cout << "Nao" << endl;
		setcolor(WHITE, BLACK);
	}
	return EXIT_SUCCESS;
}
/**
 * Prints a Vivenda/Apartamento select screen.
 * @param option If 0, highlights "Vivenda, else if 1, highlights "Apartamento.
 */
bool Main::displayVivendaApartamento(int option) {
	if (option >= 2) {
		return EXIT_FAILURE;
	}

	if (option == 0) {
		setcolor(BLACK, LIGHTGREY);
		cout << "Vivenda";
		setcolor(WHITE, BLACK);
		cout << "\tApartamento" << endl;
	} else if (option == 1) {
		setcolor(WHITE, BLACK);
		cout << "Vivenda\t";
		setcolor(BLACK, LIGHTGREY);
		cout << "Apartamento" << endl;
		setcolor(WHITE, BLACK);
	}
	return EXIT_SUCCESS;
}
/**
 * Prints a Menu select screen.
 * @param position Position of the menu in the menu options vector.
 */
bool Main::displayMenuOptions(int position) {
	if (option >= menu[position].size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < menu[position].size(); i++) {
		gotoxy(25, 10 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << "=> " << left << setw(15) << setfill(' ')
					<< menu[position][option] << endl;
			setcolor(WHITE, BLACK);
		} else
			cout << menu[position][i] << endl;
	}
	return EXIT_SUCCESS;
}

/**
 * Prints a Condomino select screen.
 */
bool Main::displaySelectCondomino() {
	if (option >= this->condominio.getMoradores().size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < this->condominio.getMoradores().size(); i++) {
		gotoxy(0, 14 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << left << setw(10) << setfill(' ')
					<< this->condominio.getMoradores()[i].getNomeUtilizador()
					<< " - " << left << setw(20) << setfill(' ')
					<< this->condominio.getMoradores()[i].getNomeCivil() << left
					<< setw(10) << setfill(' ') << " - "
					<< this->condominio.getMoradores()[i].getNIF() << endl;
			setcolor(WHITE, BLACK);
		} else {
			cout << left << setw(10) << setfill(' ')
					<< this->condominio.getMoradores()[i].getNomeUtilizador()
					<< " - " << left << setw(20) << setfill(' ')
					<< this->condominio.getMoradores()[i].getNomeCivil() << left
					<< setw(10) << setfill(' ') << " - "
					<< this->condominio.getMoradores()[i].getNIF() << endl;
		}
	}
	return EXIT_SUCCESS;
}
/**
 * Prints a Habitacao select screen.
 */
bool Main::displaySelectHabitacao(vector<Habitacao*> habitacoes) {
	if (option >= habitacoes.size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < habitacoes.size(); i++) {
		gotoxy(0, 14 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << left << setw(12) << setfill(' ') << habitacoes[i]->getTipo()
					<< " - " << habitacoes[i]->calcRenda() << "$" << left
					<< setw(10) << setfill(' ') << " - "
					<< habitacoes[i]->getNIFProprietario() << endl;
			setcolor(WHITE, BLACK);
		} else {
			cout << left << setw(12) << setfill(' ') << habitacoes[i]->getTipo()
					<< " - " << habitacoes[i]->calcRenda() << "$" << left
					<< setw(10) << setfill(' ') << " - "
					<< habitacoes[i]->getNIFProprietario() << endl;
		}
	}
	return EXIT_SUCCESS;
}
/**
 * Prints a Funcionario select screen.
 */
bool Main::displaySelectFuncionario() {
	if (option >= this->condominio.getFuncionarios().size()) {
		return EXIT_FAILURE;
	}
	for (size_t i = 0; i < this->condominio.getFuncionarios().size(); i++) {
		gotoxy(0, 14 + i);
		if (i == option) {
			setcolor(BLACK, LIGHTGREY);
			cout << this->condominio.getFuncionarios()[i].getID() << "\t"
					<< left << setw(16) << setfill(' ')
					<< this->condominio.getFuncionarios()[i].getEspecialidade();
			if (this->condominio.getFuncionarios()[i].getOcupado())
				cout << "Ocupado" << "\t\t";
			else
				cout << "Livre" << "\t\t";
			cout
					<< this->condominio.getFuncionarios()[i].getServicosEfectuados()
					<< endl;
			setcolor(WHITE, BLACK);
		} else {
			cout << this->condominio.getFuncionarios()[i].getID() << "\t"
					<< left << setw(16) << setfill(' ')
					<< this->condominio.getFuncionarios()[i].getEspecialidade();
			if (this->condominio.getFuncionarios()[i].getOcupado())
				cout << "Ocupado" << "\t\t";
			else
				cout << "Livre" << "\t\t";
			cout
					<< this->condominio.getFuncionarios()[i].getServicosEfectuados()
					<< endl;
		}
	}
	return EXIT_SUCCESS;

}

/*
 * Checks if the user trying to log in exists and, if so, updates currentUser.
 * @param utilizador Name of the user.
 * @param password Password of the user.
 * @retval TRUE Successful login.
 * @retval FALSE Invalid login.
 */
bool Main::validLogin(string utilizador, string password) {
	Condomino c1 = Condomino(utilizador, password);
	int pos = sequentialSearch(this->condominio.getMoradores(), c1);
	if (pos == -1)
		return false;
	if (this->condominio.getMoradores()[pos].getPassword() != password)
		return false;
	setCurrentUser(c1);
	return true;
}
/**
 * Checks if username and password are within the rules
 * @param utilizador Name of the new user.
 * @param password Password of the new user.
 * @retval TRUE Valid register.
 * @retval FALSE Either user already exists or the parameters were invalid.
 */
bool Main::validRegister(string utilizador, string password) {
	if (utilizador.size() < 1 || utilizador.size() > 20) {
		cout
				<< "\nO nome de utilizador tem que conter entre 1 a 20 caracteres inclusive."
				<< endl;
		return false;
	}
	if (password.size() < 5 || password.size() > 20) {
		cout << "\nA password tem que conter entre 5 a 20 caracteres inclusive."
				<< endl;
		return false;
	}
	if (hasWhitespace(utilizador) || hasWhitespace(password)) {
		cout << "\nO nome de utilizador e password nao podem conter espacos."
				<< endl;
		return false;
	}
	Condomino c1 = Condomino(utilizador, password);
	int pos = sequentialSearch(this->condominio.getMoradores(), c1);
	if (pos == -1)
		return true;
	else {
		cout << "\nO nome de utilizador nao esta disponivel." << endl;
		return false;
	}
}
/**
 * Receives user input to change the user account data specified by editOption.
 * @param editOption 0 = Username, 1 = Password.
 * @retval TRUE Successfully changed account data.
 * @retval FALSE Account data wasn't changed.
 */
bool Main::editDadosConta(int editOption) {
	displayLogo();
	gotoxy(0, 8);
	if (editOption == 0) {
		cout << "Alterar nome de utilizador:\n" << endl;
		string utilizadorActual = this->currentUser->getNomeUtilizador();
		cout << "Nome actual: " << utilizadorActual << endl;
		string utilizadorNovo = "";
		cout << "Introduza o novo nome de utilizador: ";
		getline(cin, utilizadorNovo);
		string password = "";
		cout << "Introduza a sua password: ";
		getline(cin, password);
		if (password != this->currentUser->getPassword()) {
			cout << "\nNao foi possivel alterar o nome de utilizador." << endl;
			cout << "Password invalida." << endl;
			pressEnterToContinue();
			return false;
		}
		if (utilizadorActual == utilizadorNovo) {
			cout << "\nNao foi possivel alterar o nome de utilizador." << endl;
			cout << "O novo nome tem que ser diferente do actual." << endl;
			pressEnterToContinue();
			return false;
		}
		if (validRegister(utilizadorNovo, this->currentUser->getPassword())) {
			this->currentUser->setNomeUtilizador(utilizadorNovo);

			Condomino c1 = Condomino(this->currentUser->getNomeUtilizador(),
					this->currentUser->getPassword());
			this->condominio.sortMoradores(0);
			int pos = sequentialSearch(this->condominio.getMoradores(), c1);
			this->currentUser = &this->condominio.getMoradores()[pos];

			cout << "\nNome de utilizador alterado." << endl;
			pressEnterToContinue();
			return true;
		} else
			pressEnterToContinue();
		return false;
	} else if (editOption == 1) {
		cout << "Alterar password:\n" << endl;
		string passwordActual = this->currentUser->getPassword();
		string password = "";
		cout << "Introduza a sua password actual: ";
		getline(cin, password);
		if (password != passwordActual) {
			cout << "\nPassword invalida." << endl;
			pressEnterToContinue();
			return false;
		}
		string passwordNova = "";
		cout << "Introduza a nova password: ";
		getline(cin, passwordNova);
		if (passwordActual == passwordNova) {
			cout << "\nNao foi possivel alterar a password." << endl;
			cout << "A nova password tem que ser diferente da actual." << endl;
			pressEnterToContinue();
			return false;
		}
		if (validRegister(this->currentUser->getNomeUtilizador(),
				passwordNova)) {
			this->currentUser->setPassword(passwordNova);
			cout << "\nPassword alterada." << endl;
			pressEnterToContinue();
			return true;
		}
	}
	return false;
}
/**
 * Receives user input to change the user account data specified by editOption. This function is for administrators only.
 * @param editOption 0 = Username, 1 = Password.
 * @param condomino User to be changed.
 * @retval TRUE Successfully changed account data.
 * @retval FALSE Account data wasn't changed.
 */
bool Main::editDadosContaAdmin(int editOption, Condomino &condomino) {
	displayLogo();
	gotoxy(0, 8);
	if (editOption == 0) {
		cout << "Alterar nome de utilizador:\n" << endl;
		string utilizadorActual = condomino.getNomeUtilizador();
		cout << "Nome actual: " << utilizadorActual << endl;
		string utilizadorNovo = "";
		cout << "Introduza o novo nome de utilizador: ";
		getline(cin, utilizadorNovo);
		if (utilizadorActual == utilizadorNovo) {
			cout << "\nNao foi possivel alterar o nome de utilizador." << endl;
			cout << "O novo nome tem que ser diferente do actual." << endl;
			pressEnterToContinue();
			return false;
		}
		if (validRegister(utilizadorNovo, condomino.getPassword())) {
			this->condominio.setNomeUtilizador(condomino, utilizadorNovo);
			condomino.setNomeUtilizador(utilizadorNovo);

			Condomino c1 = Condomino(this->currentUser->getNomeUtilizador(),
					this->currentUser->getPassword());
			this->condominio.sortMoradores(0);
			this->setCurrentUser(c1);

			cout << "\nNome de utilizador alterado." << endl;
			pressEnterToContinue();
			return true;

		} else
			pressEnterToContinue();
		return false;
	} else if (editOption == 1) {
		cout << "Alterar password:\n" << endl;
		string passwordActual = condomino.getPassword();
		string passwordNova = "";
		cout << "Introduza a nova password: ";
		getline(cin, passwordNova);
		if (passwordActual == passwordNova) {
			cout << "\nNao foi possivel alterar a password." << endl;
			cout << "A nova password tem que ser diferente da actual." << endl;
			pressEnterToContinue();
			return false;
		}
		if (validRegister(condomino.getNomeUtilizador(), passwordNova)) {
			this->condominio.setPassword(condomino, passwordNova);
			cout << "\nPassword alterada." << endl;
			pressEnterToContinue();
			return true;
		}
	} else if (editOption == 2) {
		cout << "Alterar estado de administrador:\n" << endl;
		string admin = "";
		if (condomino.isAdmin())
			admin = "ADMIN";
		else
			admin = "Conta normal";
		cout << "Estado anterior = " << admin << endl;
		if (condomino == *(this->currentUser)) {
			cout << "\nNao foi possivel alterar o estado da conta." << endl;
			cout
					<< "Nao e possivel revogar direitos administrativos do proprio utilizador."
					<< endl;
			pressEnterToContinue();
			return false;
		} else if (condomino.isAdmin()) {
			cout
					<< "Tem a certeza que pretende revogar os direitos administrativos do condomino?"
					<< endl;
		} else {
			cout
					<< "Tem a certeza que pretente tornar este condomino administrador?"
					<< endl;
		}
		displayYesNo(option);

		int c = getch();
		switch (c) {
		case KEY_LEFT:
			if (option - 1 >= 0)
				option--;
			break;
		case KEY_RIGHT:
			if (option + 1 < 2)
				option++;
			break;
		case KEY_ENTER:
			if (option == 0) {
				if (condomino.isAdmin()) {
					this->condominio.setAdmin(condomino, false);
					cout << "\nO condomino deixou de ser administrador."
							<< endl;
				} else {
					this->condominio.setAdmin(condomino, true);
					cout << "\nO condomino passou a ser administrador." << endl;
				}
				pressEnterToContinue();
				resetOption();
				return true;
			} else if (option == 1) {
				resetOption();
				return false;
			}
			break;
		case KEY_ESC:
			resetOption();
			return menuGerirCondominos();
			break;
		default:
			break;
		}
		return editDadosContaAdmin(editOption, condomino);
	}
	return false;
}
/**
 * Receives user input to change the user tenant data specified by editOption.
 * @param editOption 0 = Name, 1 = NIF, 2 = Monthly funds, 3 = Clear debt.
 * @retval TRUE Successfully changed tenant data.
 * @retval FALSE Tenant data wasn't changed.
 */
bool Main::editDadosCondomino(int editOption) {
	displayLogo();
	gotoxy(0, 8);
	if (editOption == 0) {
		cout << "Alterar nome civil:\n" << endl;
		string nomeActual = this->currentUser->getNomeCivil();
		cout << "Nome civil actual: " << nomeActual << endl;
		string nomeNovo = "";
		cout << "Introduza o novo nome civil: ";
		getline(cin, nomeNovo);
		if (!isName(nomeNovo)) {
			cout << "\nNao foi possivel alterar o nome civil." << endl;
			cout << "O nome civil que introduziu nao e valido." << endl;
			pressEnterToContinue();
			return false;
		}
		this->currentUser->setNomeCivil(nomeNovo);
		cout << this->currentUser->getNomeCivil() << endl;
		cout << "\nNome civil alterado." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 1) {
		cout << "Alterar NIF:\n" << endl;
		string nifActual = this->currentUser->getNIF();
		cout << "NIF actual: " << nifActual << endl;

		string nifNovo = "";
		cout << "Introduza o novo NIF: ";
		getline(cin, nifNovo);
		if (nifNovo.size() != 9 || !isNumber(nifNovo)) {
			cout << "\nNao foi possivel alterar o NIF." << endl;
			cout << "O NIF tem que ser um inteiro positivo de 9 digitos."
					<< endl;
			pressEnterToContinue();
			return false;
		}
		Condomino c1 = Condomino("nome", nifNovo);
		int pos1 = sequentialSearch(this->condominio.getMoradores(), c1);
		if (pos1 != -1) {
			cout << "\nNao foi possivel alterar o NIF." << endl;
			cout << "O NIF ja pertence a outro condomino." << endl;
			pressEnterToContinue();
			return false;
		}
		this->currentUser->setNIF(nifNovo);
		cout << this->currentUser->getNIF() << endl;
		cout << "\nNIF alterado." << endl;
		pressEnterToContinue();
		return true;

	} else if (editOption == 2) {
		cout << "Alterar fundos mensais:\n" << endl;
		long int fundosActuais = this->currentUser->getFundosMensais();
		cout << "Fundos mensais actuais: " << fundosActuais << endl;
		string novosFundos = "";
		cout << "Introduza os novos fundos mensais: ";
		getline(cin, novosFundos);
		if (novosFundos.size() > 9 || !isNumber(novosFundos)) {
			cout << "\nNao foi possivel alterar os fundos mensais." << endl;
			cout << "Os fundos mensais tem que ser um inteiro positivo."
					<< endl;
			pressEnterToContinue();
			return false;
		}
		long int fundosMensais = atoi(novosFundos.c_str());
		this->currentUser->setFundosMensais(fundosMensais);
		cout << "\nFundos Mensais alterados." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 3) {
		if (this->currentUser->getDivida() == 0) {
			cout << "\nNao foi possivel saldar a divida" << endl;
			cout << "O condomino nao tem divida." << endl;
			pressEnterToContinue();
			return false;
		}
		cout << "Pretende saldar a divida?";
		long int dividaActual = this->currentUser->getDivida();
		cout << "Divida actual = " << dividaActual << endl;

		displayYesNo(option);

		int c = getch();
		switch (c) {
		case KEY_LEFT:
			if (option - 1 >= 0)
				option--;
			break;
		case KEY_RIGHT:
			if (option + 1 < 2)
				option++;
			break;
		case KEY_ENTER:
			if (option == 0) {
				this->condominio.saldarDivida(*this->currentUser);
				cout << "\nDivida saldada." << endl;
				resetOption();
				pressEnterToContinue();
				return true;
			} else if (option == 1) {
				resetOption();
				return false;
			}
			break;
		case KEY_ESC:
			resetOption();
			return false;
			break;
		default:
			break;
		}
		return editDadosCondomino(editOption);
	}
	return false;
}
/**
 * Receives user input to change the user tenant data specified by editOption. This function is for administrators only.
 * @param editOption 0 = Name, 1 = NIF, 2 = Monthly funds, 3 = Clear debt.
 * @param condomino User to be changed.
 * @retval TRUE Successfully changed tenant data.
 * @retval FALSE Tenant data wasn't changed.
 */
bool Main::editDadosCondominoAdmin(int editOption, Condomino &condomino) {
	displayLogo();
	gotoxy(0, 8);
	if (editOption == 0) {
		cout << "Alterar nome civil:\n" << endl;
		string nomeActual = condomino.getNomeCivil();
		cout << "Nome civil actual: " << nomeActual << endl;
		string nomeNovo = "";
		cout << "Introduza o novo nome civil: ";
		getline(cin, nomeNovo);
		if (!isName(nomeNovo)) {
			cout << "\nNao foi possivel alterar o nome civil." << endl;
			cout << "O nome civil que introduziu nao e valido." << endl;
			pressEnterToContinue();
			return false;
		}
		this->condominio.setNomeCivil(condomino, nomeNovo);
		cout << "\nNome civil alterado." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 1) {
		cout << "Alterar NIF:\n" << endl;
		string nifActual = condomino.getNIF();
		cout << "NIF actual: " << nifActual << endl;

		string nifNovo = "";
		cout << "Introduza o novo NIF: ";
		getline(cin, nifNovo);
		if (nifNovo.size() != 9 || !isNumber(nifNovo)) {
			cout << "\nNao foi possivel alterar o NIF." << endl;
			cout << "O NIF tem que ser um inteiro positivo de 9 digitos."
					<< endl;
			pressEnterToContinue();
			return false;
		}
		Condomino c1 = Condomino("nome", nifNovo);
		int pos1 = sequentialSearch(this->condominio.getMoradores(), c1);
		if (pos1 != -1) {
			cout << "\nNao foi possivel alterar o NIF." << endl;
			cout << "O NIF ja pertence a outro condomino." << endl;
			pressEnterToContinue();
			return false;
		}
		this->condominio.setNIF(condomino, nifNovo);
		cout << "\nNIF alterado." << endl;
		pressEnterToContinue();
		return true;

	} else if (editOption == 2) {
		cout << "Alterar fundos mensais:\n" << endl;
		long int fundosActuais = condomino.getFundosMensais();
		cout << "Fundos mensais actuais: " << fundosActuais << endl;
		string novosFundos = "";
		cout << "Introduza os novos fundos mensais: ";
		getline(cin, novosFundos);
		if (novosFundos.size() > 9 || !isNumber(novosFundos)) {
			cout << "\nNao foi possivel alterar os fundos mensais." << endl;
			cout << "Os fundos mensais tem que ser um inteiro positivo."
					<< endl;
			pressEnterToContinue();
			return false;
		}
		long int fundosMensais = atoi(novosFundos.c_str());
		this->condominio.setFundosMensais(condomino, fundosMensais);
		cout << "\nFundos Mensais alterados." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 3) {
		if (condomino.getDivida() == 0) {
			cout << "\nNao foi possivel saldar a divida" << endl;
			cout << "O condomino nao tem divida." << endl;
			pressEnterToContinue();
			return false;
		}
		cout << "Pretende saldar a divida?";
		long int dividaActual = condomino.getDivida();
		cout << "Divida actual = " << dividaActual << "$" << endl;

		displayYesNo(option);

		int c = getch();
		switch (c) {
		case KEY_LEFT:
			if (option - 1 >= 0)
				option--;
			break;
		case KEY_RIGHT:
			if (option + 1 < 2)
				option++;
			break;
		case KEY_ENTER:
			if (option == 0) {
				this->condominio.saldarDivida(condomino);
				cout << "\nDivida saldada." << endl;
				resetOption();
				pressEnterToContinue();
				return true;
			} else if (option == 1) {
				resetOption();
				return false;
			}
			break;
		case KEY_ESC:
			resetOption();
			return false;
			break;
		default:
			break;
		}
		return editDadosCondominoAdmin(editOption, condomino);
	}
	return false;
}
/**
 * Receives user input to change housing data specified by editOption.
 * @param editOption 0 = Address, 1 = Postal Code, 2 = Living area.  If it's a house -> 3 = Exterior area, 4 = Swimming pool, else if it's an apartment -> 3 = Number of rooms, 4 = Floor.
 * @retval TRUE Successfully changed housing data.
 * @retval FALSE Housing data wasn't changed.
 */
bool Main::editHabitacao(int editOption, Habitacao* h1) {
	displayLogo();
	gotoxy(0, 8);
	if (editOption == 0) {
		cout << "Alterar morada:\n" << endl;
		string moradaActual = h1->getMorada();
		cout << "Morada actual: " << moradaActual << endl;
		string moradaNova = "";
		cout << "Introduza a nova morada: ";
		getline(cin, moradaNova);
		Vivenda* v1 = new Vivenda(moradaNova, "", 0, 0, false);
		if (this->condominio.findHabitacao(this->condominio.getHabitacoes(), v1)
				!= -1) {
			cout << "\nNao foi possivel alterar a morada." << endl;
			cout << "Ja existe outra habitacao com a mesma morada." << endl;
			pressEnterToContinue();
			return false;
		}
		delete v1;
		h1->setMorada(moradaNova);
		cout << "\nMorada alterada." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 1) {
		cout << "Alterar codigo postal:\n" << endl;
		string codPostalActual = h1->getCodigoPostal();
		cout << "Codigo postal actual: " << codPostalActual << endl;

		string novoCodigo = "";
		cout << "Introduza o novo codigo postal: ";
		getline(cin, novoCodigo);
		h1->setCodigoPostal(novoCodigo);
		cout << "Codigo postal alterado." << endl;
		pressEnterToContinue();
		return true;
	} else if (editOption == 2) {
		cout << "Alterar area habitacional:\n" << endl;
		float areaInteriorActual = h1->getAreaInterior();
		cout << "Area habitacional actual: " << areaInteriorActual << " m2"
				<< endl;
		string novaAreaInterior = "";
		do {
			cout << "Introduza a nova area habitacional: ";
			getline(cin, novaAreaInterior);
			if (!isNumber(novaAreaInterior))
				cout
						<< "Area habitacional tem que ser um numero inteiro positivo.\n"
						<< endl;
		} while (!isNumber(novaAreaInterior));
		float area = atof(novaAreaInterior.c_str());
		h1->setAreaInterior(area);
		cout << "\nArea habitacional alterada." << endl;
		pressEnterToContinue();
		return true;
	} else {
		if (h1->getTipo() == "Vivenda") {
			if (editOption == 3) {
				cout << "Alterar area exterior:\n" << endl;
				float areaExteriorActual = h1->getAreaExterior();
				cout << "Area exterior actual: " << areaExteriorActual << " m2"
						<< endl;
				string input = "";
				do {
					cout << "Introduza a nova area exterior: ";
					getline(cin, input);
					if (!isNumber(input))
						cout
								<< "Area habitacional tem que ser um numero inteiro positivo.\n"
								<< endl;
				} while (!isNumber(input));
				float area = atof(input.c_str());
				h1->setAreaExterior(area);
				cout << "\nArea exterior alterada." << endl;
				pressEnterToContinue();
				return true;
			} else if (editOption == 4) {
				cout << "Alterar piscina:\n" << endl;
				bool piscinaActual = h1->getPiscina();
				cout << "Piscina actual: ";
				if (piscinaActual)
					cout << "SIM" << endl;
				else
					cout << "NAO" << endl;
				string input = "";
				do {
					cout << "Introduza o novo estado de piscina (Sim/Nao): ";
					getline(cin, input);
				} while (input != "Sim" && input != "sim" && input != "Nao"
						&& input != "nao");
				if (input == "Sim" || input == "sim")
					piscinaActual = true;
				else if (input == "Nao" || input == "nao")
					piscinaActual = false;
				h1->setPiscina(piscinaActual);
				cout << "\nEstado de piscina alterado." << endl;
				pressEnterToContinue();
				return true;
			}
		} else {
			if (editOption == 3) {
				cout << "Alterar a tipologia:\n" << endl;
				int tipologiaActual = h1->getTipologia();
				cout << "Tipologia actual: T" << tipologiaActual << endl;
				string input = "";
				do {
					cout << "Introduza a novo numero de quartos: ";
					getline(cin, input);
					if (!isNumber(input)) {
						cout
								<< "A tipologia tem que ser um numero inteiro positivo.\n"
								<< endl;
					}
				} while (!isNumber(input));
				int tipologia = atoi(input.c_str());
				h1->setTipologia(tipologia);
				cout << "\nTipologia alterada." << endl;
				pressEnterToContinue();
				return true;
			} else if (editOption == 4) {
				cout << "Alterar o piso:\n" << endl;
				int pisoActual = h1->getPiso();
				cout << "Piso actual: " << pisoActual << endl;
				string input = "";
				do {
					cout << "Introduza o novo piso: ";
					getline(cin, input);
					if (!isNumber(input)) {
						cout
								<< "O piso tem que ser um numero inteiro positivo.\n"
								<< endl;
					}
				} while (!isNumber(input));
				int piso = atoi(input.c_str());
				h1->setPiso(piso);
				cout << "\nPiso alterado." << endl;
				pressEnterToContinue();
				return true;
			}
		}
	}
}

/**
 * Displays current user account info.
 */
void Main::displayCurrentUserInfoConta() {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS:\n" << endl;
	this->currentUser->infoConta();
	pressEnterToContinue();
}
/**
 * Displays current user tenant info.
 */
void Main::displayCurrentUserInfoCondomino() {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS:\n" << endl;
	(*this->currentUser).infoCondomino();
	pressEnterToContinue();
}
/**
 * Displays info of a house owned by the current user.
 * @param pos Position of the house in the vector of houses owned by user.
 */
void Main::displayCurrentUserHabitacao(int pos) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DA HABITACAO\n" << endl;
	cout << "Tipo: ";
	this->currentUser->getHabitacoes()[pos]->info();

	pressEnterToContinue();
}
/**
 * Displays rent status for every house owned by the current user.
 */
void Main::displayCurrentUserRenda() {
	displayLogo();
	gotoxy(0, 8);
	cout << "Mes actual -> ";
	setcolor(YELLOW, BLACK);
	cout << mesesAno[this->condominio.getMes()] << endl << endl;
	setcolor(WHITE, BLACK);
	this->currentUser->infoRenda();
	cout << endl;
	pressEnterToContinue();
}
/**
 * Displays info of a specified user.
 * @param pos Position of the user in the vector of tenants of the condominium.
 */
void Main::displayCondominoInfo(int pos) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DO CONDOMINO\n" << endl;
	cout << "Nome Utilizador: "
			<< this->condominio.getMoradores()[pos].getNomeUtilizador() << endl
			<< endl;
	cout << "Nome Civil: ";
	this->condominio.getMoradores()[pos].infoCondomino();
	cout << endl;
	pressEnterToContinue();
}
/**
 * Displays info of a specified house.
 * @param pos Position of the house in the vector of houses of the condominium.
 */
void Main::displayHabitacaoInfo(int pos) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DA HABITACAO" << endl;
	cout << "Tipo: ";
	this->condominio.getHabitacoes()[pos]->info();

	if (this->condominio.getHabitacoes()[pos]->hasProprietario()) {
		Condomino c1 = Condomino("nome", "password", "nomeCivil",
				this->condominio.getHabitacoes()[pos]->getNIFProprietario());
		int pos2 = sequentialSearch(this->condominio.getMoradores(), c1);

		cout << "PROPRIETARIO" << endl;
		cout << "Nome: " << this->condominio.getMoradores()[pos2].getNomeCivil()
				<< endl;
		cout << "NIF: " << this->condominio.getMoradores()[pos2].getNIF()
				<< endl;
	}
	pressEnterToContinue();
}
/**
 * Displays info of a specified employee.
 * @param pos Position of the employee in the vector of employees of the condominium.
 */
void Main::displayFuncionarioInfo(int pos) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DO FUNCIONARIO\n" << endl;
	this->condominio.getFuncionarios()[pos].info();
	if (this->condominio.getFuncionarios()[pos].getOcupado()) {
		for (size_t i = 0; i < this->condominio.getServicosEmCurso().size();
				i++) {
			if (this->condominio.getServicosEmCurso()[i].getIDFuncionario()
					== this->condominio.getFuncionarios()[pos].getID()) {
				cout << "\nA efectuar:" << endl;
				this->condominio.getServicosEmCurso()[i].info();
				break;
			}
		}
	}
	if (this->condominio.getFuncionarios()[pos].getServicosEfectuados() > 0) {
		cout << "\nServicos efectuados:\n" << endl;
		for (size_t j = 0; j < this->condominio.getServicosTerminados().size();
				j++)
			if (this->condominio.getServicosTerminados()[j].getIDFuncionario()
					== this->condominio.getFuncionarios()[pos].getID())
				this->condominio.getServicosTerminados()[j].info();
	}
	pressEnterToContinue();
}
/**
 * Displays end month info.
 * @retval TRUE Every tenant paid their rent.
 * @retval FALSE Not every tenant paid their rent.
 */
bool Main::fimDoMes() {
	displayLogo();
	gotoxy(30, 8);
	cout << "FIM DO MES\n" << endl;
	cout << "Mes actual -> ";
	setcolor(YELLOW, BLACK);
	cout << mesesAno[this->condominio.getMes()];
	setcolor(WHITE, BLACK);
	cout << "\nFundos actuais = " << this->condominio.getFundos() << "$\n"
			<< endl;

	vector<Condomino> caloteiros = this->condominio.fimDoMes();
	cout << "Novo mes -> ";
	setcolor(YELLOW, BLACK);
	cout << mesesAno[this->condominio.getMes()];
	setcolor(WHITE, BLACK);
	cout << "\nNovos fundos = " << this->condominio.getFundos() << "$\n"
			<< endl;

	if (caloteiros.empty()) {
		cout << "Todos os condominos pagaram a renda." << endl;
		pressEnterToContinue();
		return true;
	} else {
		cout << "Numero de caloteiros = " << caloteiros.size() << "\n" << endl;
		cout << "Divida           Nome Civil  			NIF" << endl;
		for (size_t i = 0; i < caloteiros.size(); i++) {
			cout << caloteiros[i].getDivida() << "$" << left << setw(10)
					<< setfill(' ') << "   " << left << setw(20) << setfill(' ')
					<< caloteiros[i].getNomeCivil() << left << setw(10)
					<< setfill(' ') << "   " << caloteiros[i].getNIF() << endl;
		}
		cout << endl;
		pressEnterToContinue();
		return false;
	}
}

/*
 * Menu functions
 */

/**
 *	Initial menu. User has the option to log in, create a new account or exit the program.
 *	@retval EXIT_SUCCESS Shutdown.
 *	@return A new menu.
 */
int Main::menuInicial() {
	displayLogo();
	gotoxy(30, 8);
	cout << "MENU INICIAL\n" << endl;

	displayMenuOptions(0);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[0].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Menu Login
			resetOption();
			return menuLogin();
		} else if (option == 1) { //Menu Registo
			resetOption();
			menuRegisto();
		} else
			//Sair
			return EXIT_SUCCESS;
		break;
	default:
		break;
	}

	return menuInicial();
}

/**
 * Login screen. User needs to input their username and password.
 * @return User menu if valid login, initial menu if invalid login.
 */
int Main::menuLogin() {
	displayLogo();
	gotoxy(30, 8);
	cout << "LOGIN\n" << endl;
	cout << "Introduza os seus dados de login:\n";

	string utilizador = "";
	string password = "";

	cout << "Utilizador: ";
	getline(cin, utilizador);
	cout << "Password: ";
	getline(cin, password);

	if (validLogin(utilizador, password)) {
		resetOption();
		return menuUtilizador();
	} else {
		cout << "\nDados invalidos\n";
		pressEnterToContinue();
		resetOption();
		return menuInicial();
	}
	return EXIT_SUCCESS;
}
/**
 * Register screen. User needs to input their username, password, name and NIF to create a new account.
 * @retval EXIT_SUCCESS Initial menu.
 */
int Main::menuRegisto() {
	displayLogo();
	gotoxy(30, 8);
	cout << "REGISTO\n" << endl;
	cout << "Introduza os seus dados de login:\n";

	string utilizador = "";
	string password = "";
	string nomeCivil = "";
	string NIF = "";

	cout << "Utilizador: ";
	getline(cin, utilizador);
	cout << "Password: ";
	getline(cin, password);

	if (validRegister(utilizador, password)) {
		do {
			cout << "Nome Civil: ";
			getline(cin, nomeCivil);
			if (!isName(nomeCivil))
				cout << "Introduza um nome valido.\n" << endl;
		} while (!isName(nomeCivil));
		do {
			cout << "NIF: ";
			getline(cin, NIF);
			if ((NIF.size() != 9) && (!isNumber(NIF))) {
				cout << "Introduza um NIF valido.\n" << endl;
			}
		} while ((NIF.size() != 9) && (!isNumber(NIF)));
		Condomino c1 = Condomino(utilizador, password, nomeCivil, NIF);
		int pos = this->condominio.addMorador(c1);
		if (pos != -1)
			cout << "\nConta criada com sucesso!" << endl;
		else {
			cout << "\nNao foi possivel criar uma conta." << endl;
			cout
					<< "Ja existe um condomino com o mesmo nome de utilizador e/ou NIF."
					<< endl;
		}
	} else {
		cout << "\nNao foi possivel criar uma conta." << endl;
	}
	pressEnterToContinue();
	resetOption();
	return EXIT_SUCCESS;
}

/**
 * User menu. The user has several options such as view or change their user info. Add a house, request service, etc.
 * @return A new menu.
 */
int Main::menuUtilizador() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	int menuOption = -1;
	if (this->currentUser->isAdmin()) {
		menuOption = 1; //Admin menu
	} else {
		menuOption = 2; //Normal menu
	}

	gotoxy(30, 8);
	cout << "MENU UTILIZADOR" << endl;
	displayMenuOptions(menuOption);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[menuOption].size())
			option++;
		break;
	case KEY_ENTER:
		if (menuOption == 1)
			if (option == 0) { //Menu Administrador
				resetOption();
				return menuAdministrador();
			} else if (option == 1) { //Editar dados conta
				resetOption();
				return menuEditDadosConta(*(this->currentUser));
			} else if (option == 2) { //Ver dados condomino
				displayCurrentUserInfoCondomino();
			} else if (option == 3) { //Editar dados condomino
				resetOption();
				return menuEditDadosCondomino(*(this->currentUser));
			} else if (option == 4) { //Ver habitacoes possuidas
				resetOption();
				return menuHabitacoesPossuidas();
			} else if (option == 5) { //Adicionar habitacao
				resetOption();
				return menuSelectOrNewHabitacao();
			} else if (option == 6) { //Ver servicos requisitados

			} else if (option == 7) { //Requisitar servico

			} else { //Sair
				resetOption();
				return menuInicial();
			}
		else if (menuOption == 2) {
			if (option == 0) { //Editar dados conta
				resetOption();
				return menuEditDadosConta(*(this->currentUser));
			} else if (option == 1) { //Ver dados condomino
				displayCurrentUserInfoCondomino();
			} else if (option == 2) { //Editar dados condomino
				resetOption();
				return menuEditDadosCondomino(*(this->currentUser));
			} else if (option == 3) { //Ver habitacoes possuidas
				resetOption();
				return menuHabitacoesPossuidas();
			} else if (option == 4) { //Adicionar habitacao
				resetOption();
				return menuSelectOrNewHabitacao();
			} else if (option == 5) { //Ver servicos requisitados

			} else if (option == 6) { //Requisitar servico

			} else { //Sair
				resetOption();
				return menuInicial();
			}
		}
		break;
	default:
		break;
	}

	return menuUtilizador();
}
/**
 * Change user account data menu. The user selects which info of their account data they want to change.
 * @return User menu.
 */
int Main::menuEditDadosConta(Condomino &condomino) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ALTERAR DADOS\n" << endl;
	displayMenuOptions(3);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[3].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Alterar nome de utilizador
			editDadosConta(0);
			resetOption();
			return menuUtilizador();
		} else if (option == 1) { //Alterar password
			editDadosConta(1);
			resetOption();
			return menuUtilizador();
		} else if (option == 2) { //Voltar atras
			resetOption();
			return menuUtilizador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuUtilizador();
		break;
	default:
		break;
	}
	return menuEditDadosConta(condomino);
}
/**
 * �Change tenant data menu. The user selects which info of their tenant data they want to change.
 * @return User menu.
 */
int Main::menuEditDadosCondomino(Condomino &condomino) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ALTERAR DADOS\n" << endl;
	displayMenuOptions(4);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[4].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Alterar nome civil
			resetOption();
			editDadosCondomino(0);
			return menuUtilizador();
		} else if (option == 1) { //Alterar NIF
			resetOption();
			editDadosCondomino(1);
			return menuUtilizador();
		} else if (option == 2) { //Alterar fundos mensais
			resetOption();
			editDadosCondomino(2);
			return menuUtilizador();
		} else if (option == 3) { //Saldar divida
			resetOption();
			editDadosCondomino(3);
			return menuUtilizador();
		} else { //Voltar atras
			resetOption();
			return menuUtilizador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuUtilizador();
		break;
	default:
		break;
	}
	return menuEditDadosCondomino(condomino);
}
/**
 * Owned housing menu. The user selects if they want to view an owned house info, remove an owned house or view their rent status.
 * @return A new menu.
 */
int Main::menuHabitacoesPossuidas() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "HABITACOES POSSUIDAS\n" << endl;
	displayMenuOptions(5);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[5].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Ver informacao das habitacoes
			resetOption();
			return menuSelectHabitacoesPossuida(false);
		} else if (option == 1) { //Ver estado da renda
			displayCurrentUserRenda();
		} else if (option == 2) { //Remover habitacao
			resetOption();
			return menuSelectHabitacoesPossuida(true);
		} else { //Voltar atras
			resetOption();
			return menuUtilizador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuUtilizador();
		break;
	default:
		break;
	}
	return menuHabitacoesPossuidas();
}
/**
 * Select owned housing menu. The user selects which house they want to remove or just see its data.
 * @param remover If true, selecting an house will remove it. If false, selecting an house will display its info.
 * @return A new menu.
 */
int Main::menuSelectHabitacoesPossuida(bool remover) {
	displayLogo();
	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE A HABITACAO:\n" << endl;
	if (remover)
		cout << "[ENTER] Remover" << endl;
	else
		cout << "[ENTER] Ver dados" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Habitacao      Renda         Morada" << endl;

	if (this->currentUser->getHabitacoes().empty()) {
		cout << "Nao possui habitacoes.\n" << endl;
		pressEnterToContinue();
		resetOption();
		return menuHabitacoesPossuidas();
	}
	displaySelectHabitacao(currentUser->getHabitacoes());

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->currentUser->getHabitacoes().size())
			option++;
		break;
	case KEY_ENTER:
		if (!remover)
			displayCurrentUserHabitacao(option);
		else {
			menuDeleteHabitacaoPossuida(option, 0);
			resetOption();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuHabitacoesPossuidas();
		break;
	default:
		break;
	}
	return menuSelectHabitacoesPossuida(remover);
}
/**
 * Delete owned house menu. The user is given a prompt to confirm if they want to remove a house.
 * @param pos Position of the house in the vector of houses owned by the user.
 * @param menuOption Changes the highlighted option. 0 = Yes, 1 = No.
 * @return A new menu.
 */
int Main::menuDeleteHabitacaoPossuida(int pos, int menuOption) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DA HABITACAO\n" << endl;
	cout << "Tipo: ";
	this->currentUser->getHabitacoes()[pos]->info();

	cout << "Tem a certeza que pretende remover esta habitacao?" << endl;
	displayYesNo(menuOption);

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (menuOption - 1 >= 0)
			menuOption--;
		break;
	case KEY_RIGHT:
		if (menuOption + 1 < 2)
			menuOption++;
		break;
	case KEY_ENTER:
		if (menuOption == 0) {
			this->condominio.eraseHabitacaoPossuida(*currentUser, pos);
			cout << "\nHabitacao removida." << endl;
			if (this->option > 0)
				option--;
			pressEnterToContinue();
			return menuSelectHabitacoesPossuida(true);
		} else if (menuOption == 1) {
			return menuSelectHabitacoesPossuida(true);
		}
		break;
	default:
		break;
	}
	return menuDeleteHabitacaoPossuida(pos, menuOption);
}
/**
 * Rent an empty house or add a new house. The user is given the choice to rent an empty house or add a new house.
 * @return A new menu.
 */
int Main::menuSelectOrNewHabitacao() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ADICIONAR HABITACAO" << endl;
	displayMenuOptions(15);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[15].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Selecionar habitacao
			resetOption();
			vector<Habitacao*> habitacoesLivres;
			for (size_t i = 0; i < this->condominio.getHabitacoes().size();
					i++) {
				if (!this->condominio.getHabitacoes()[i]->hasProprietario())
					habitacoesLivres.push_back(
							this->condominio.getHabitacoes()[i]);
			}
			return menuSelectHabitacaoAdd(habitacoesLivres);
		} else if (option == 1) { //Nova habitacao
			resetOption();
			return menuAddHabitacao(*currentUser);
		} else { //Voltar atras
			resetOption();
			return menuHabitacoesPossuidas();
		}
		break;
	default:
		break;
	}

	return menuSelectOrNewHabitacao();
}
/**
 * Select empty house to add menu. The user is given a list of empty houses which they can rent.
 * @param habitacoes Vector containing all the empty houses in the condominium.
 * @return A new menu.
 */
int Main::menuSelectHabitacaoAdd(vector<Habitacao*> habitacoes) {
	displayLogo();
	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE A HABITACAO:\n" << endl;
	cout << "[ENTER] Adicionar habitacao" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Habitacao      Renda         Morada" << endl;

	if (habitacoes.empty()) {
		cout << "Nao existem habitacoes livres.\n" << endl;
		pressEnterToContinue();
		resetOption();
		return menuSelectOrNewHabitacao();
	}
	displaySelectHabitacao(habitacoes);

	int pos = -1;

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < habitacoes.size())
			option++;
		break;
	case KEY_ENTER:
		pos = option;
		resetOption();
		return menuConfirmAddHabitacao(*this->currentUser, habitacoes[pos]);
		break;
	case KEY_ESC:
		resetOption();
		return menuUtilizador();
		break;
	default:
		break;
	}
	return menuSelectHabitacaoAdd(habitacoes);
}
/**
 * Add a new house menu. The user inputs the info of the new house to be added to his owned houses.
 * @param condomino User to whom the house is added.
 * @return A new menu.
 */
int Main::menuAddHabitacao(Condomino condomino) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ADICIONAR HABITACAO" << endl;

	cout << "\nSelecione o tipo de habitacao: ";
	displayVivendaApartamento(this->option);

	string line = "";
	string morada = "";
	string codigoPostal = "";
	float areaInterior = 0;
	float areaExterior = 0;
	bool piscina = false;
	int tipologia = 0;
	int piso = 0;

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_RIGHT:
		if (option + 1 < 2)
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Vivenda
			cout << "Morada: ";
			getline(cin, morada);
			cout << "Codigo Postal: ";
			getline(cin, codigoPostal);
			do {
				cout << "Area habitacional: ";
				getline(cin, line);
				if (!isNumber(line))
					cout
							<< "A area habitacional tem que ser um numero inteiro positivo.\n"
							<< endl;
			} while (!isNumber(line));
			areaInterior = atof(line.c_str());
			do {
				cout << "Area exterior: ";
				getline(cin, line);
				if (!isNumber(line))
					cout
							<< "A area exterior tem que ser um numero inteiro positivo.\n"
							<< endl;
			} while (!isNumber(line));
			areaExterior = atof(line.c_str());
			while (line != "Sim" && line != "sim" && line != "Nao"
					&& line != "nao") {
				cout << "Piscina(Sim/Nao): ";
				getline(cin, line);
				if (line == "Sim" || line == "sim")
					piscina = true;
				else if (line == "Nao" || line == "nao")
					piscina = false;
			}

			Vivenda* v1 = new Vivenda(morada, codigoPostal, condomino.getNIF(),
					areaInterior, areaExterior, piscina);
			return menuConfirmAddHabitacao(condomino, v1);

		} else if (option == 1) {
			cout << "Morada: ";
			getline(cin, morada);
			cout << "Codigo Postal: ";
			getline(cin, codigoPostal);
			do {
				cout << "Area habitacional: ";
				getline(cin, line);
				if (!isNumber(line))
					cout
							<< "A area habitacional tem que ser um numero inteiro positivo.\n"
							<< endl;
			} while (!isNumber(line));
			areaInterior = atof(line.c_str());
			do {
				cout << "Numero de quartos: ";
				getline(cin, line);
				if (!isNumber(line))
					cout
							<< "O numero de quartos tem que ser um numero inteiro positivo.\n"
							<< endl;
				else
					break;
			} while (!isNumber(line));
			tipologia = atoi(line.c_str());
			do {
				cout << "Piso: ";
				getline(cin, line);
				if (!isNumber(line))
					cout << "O piso tem que ser um numero inteiro positivo.\n"
							<< endl;
			} while (!isNumber(line));
			piso = atoi(line.c_str());

			Apartamento* a1 = new Apartamento(morada, codigoPostal,
					condomino.getNIF(), tipologia, areaInterior, piso);

			return menuConfirmAddHabitacao(condomino, a1);
		}
		break;
	default:
		break;
	}
	return menuAddHabitacao(condomino);
}
/**
 * Confirm adding a new house menu. The user is given the info of the house they're about to own and is given a prompt to confirm that addition.
 *	@param condomino User to whom the house is added.
 *	@param h1 Pointer to the house being added.
 *	@return A new menu.
 */
int Main::menuConfirmAddHabitacao(Condomino condomino, Habitacao* h1) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DA HABITACAO\n" << endl;
	cout << "Tipo: ";
	h1->info();

	if (condomino.hasDados()) {
		int gastos = 0;
		for (size_t i = 0; i < condomino.getHabitacoes().size(); i++)
			gastos += condomino.getHabitacoes()[i]->calcRenda();
		if (condomino.getFundosMensais() < gastos)
			cout
					<< "AVISO: Este condomino ja esta a exceder o orcamento mensal."
					<< endl;
		else if (condomino.getFundosMensais() < gastos + h1->calcRenda())
			cout
					<< "AVISO: Esta habitacao vai exceder o orcamento mensal do condomino."
					<< endl;
	}
	cout << "Tem a certeza que pretende adicionar esta habitacao?" << endl;
	displayYesNo(option);

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_RIGHT:
		if (option + 1 < 2)
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			int pos = sequentialSearch(this->condominio.getMoradores(),
					condomino);
			if (h1->hasProprietario()) {
				if (this->condominio.addHabitacao(h1)) {
					this->condominio.getCondomino(pos)->addHabitacao(h1,
							this->condominio.getMes());
					cout << "\nHabitacao adicionada." << endl;
				} else {
					cout << "\nNao foi possivel adicionar a habitacao." << endl;
					cout << "Ja existe uma habitacao com a mesma morada."
							<< endl;
				}
				pressEnterToContinue();
				resetOption();
				return menuUtilizador();
			} else {
				this->condominio.getCondomino(pos)->addHabitacao(h1,
						this->condominio.getMes());
				cout << "\nHabitacao adicionada." << endl;
				pressEnterToContinue();
				resetOption();
				return menuUtilizador();
			}
		} else if (option == 1) {
			resetOption();
			if (h1->getNIFProprietario() == this->currentUser->getNIF())
				return menuUtilizador();
			else
				return menuSelectOrVacantHabitacao();
		}
		break;
	default:
		break;
	}
	return menuConfirmAddHabitacao(condomino, h1);
}

/**
 * Administrator menu. The admin is given several options, such as create, edit or remove users, houses, services or employees. The admin can also end the month.
 * @return A new menu.
 */
int Main::menuAdministrador() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "MENU ADMINISTRADOR" << endl;
	displayMenuOptions(7);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[7].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Gerir condominos
			resetOption();
			return menuGerirCondominos();
		} else if (option == 1) { //Gerir habitacoes
			resetOption();
			return menuGerirHabitacoes();
		} else if (option == 2) { //Gerir funcionarios
			resetOption();
			return menuGerirFuncionarios();
		} else if (option == 4) { //Fim do Mes
			fimDoMes();
		} else {
			resetOption();
			return menuUtilizador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuUtilizador();
		break;
	default:
		break;
	}

	return menuAdministrador();
}

/**
 * Manage users menu. The admin can create, edit or remove users.
 * @return A new menu.
 */
int Main::menuGerirCondominos() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "GERIR CONDOMINOS" << endl;
	displayMenuOptions(8);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[8].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) //Ver lista de condominos
			return menuDisplayCondominosBy();
		else if (option == 1) { //Alterar dados de um condomino
			resetOption();
			return menuSelectCondomino(false);
		} else if (option == 2) { //Adicionar condomino
			resetOption();
			Condomino c1 = *currentUser;
			menuRegisto();
			setCurrentUser(c1);
			return menuGerirCondominos();
		} else if (option == 3) { //Remover condomino
			resetOption();
			return menuSelectCondomino(true);
		} else { //Voltar atras
			resetOption();
			return menuAdministrador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuAdministrador();
		break;
	default:
		break;
	}
	return menuGerirCondominos();
}
/**
 * Display users by menu. The admin can list users by username, name or NIF.
 */
int Main::menuDisplayCondominosBy() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ORDENAR POR" << endl;
	displayMenuOptions(17);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[17].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Ordenar por nome de utilizador
			resetOption();
			//Ordena os moradores e actualiza o currentUser
			Condomino c1 = Condomino("nome", "password", "nomeCivil",
					this->currentUser->getNIF());
			this->condominio.sortMoradores(0);
			int pos = sequentialSearch(this->condominio.getMoradores(), c1);
			setCurrentUser(this->condominio.getMoradores()[pos]);

			return menuDisplayAllCondominos();
		} else if (option == 1) { //Ordenar por nome civil
			resetOption();
			//Ordena os moradores e actualiza o currentUser
			Condomino c1 = Condomino("nome", "password", "nomeCivil",
					this->currentUser->getNIF());
			this->condominio.sortMoradores(1);
			int pos = sequentialSearch(this->condominio.getMoradores(), c1);
			setCurrentUser(this->condominio.getMoradores()[pos]);

			return menuDisplayAllCondominos();
		} else if (option == 2) { //Ordenar por NIF
			resetOption();
			//Ordena os moradores e actualiza o currentUser
			Condomino c1 = Condomino("nome", "password", "nomeCivil",
					this->currentUser->getNIF());
			this->condominio.sortMoradores(2);
			int pos = sequentialSearch(this->condominio.getMoradores(), c1);
			setCurrentUser(this->condominio.getMoradores()[pos]);

			return menuDisplayAllCondominos();
		} else { //Voltar atras
			resetOption();
			return menuGerirCondominos();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirCondominos();
		break;
	default:
		break;
	}
	return menuDisplayCondominosBy();
}
/**
 * Display all users menu. The users are listed according to the option specified before. The admin can view their info by selecting them.
 * @return A new menu.
 */
int Main::menuDisplayAllCondominos() {
	displayLogo();
	gotoxy(0, 8);
	cout << "LISTA DE CONDOMINOS:" << endl;
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE O UTILIZADOR:\n" << endl;
	cout << "[ENTER] Ver dados" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Utilizador   Nome Civil                    NIF" << endl;

	displaySelectCondomino();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getMoradores().size())
			option++;
		break;
	case KEY_ENTER:
		displayCondominoInfo(option);
		break;
	case KEY_ESC:
		resetOption();
		return menuDisplayCondominosBy();
		break;
	default:
		break;
	}

	return menuDisplayAllCondominos();
}
/**
 * Select user menu. The admin can choose a user to remove or to view its info.
 * @param remover If true, selecting will remove the user. If false, selecting will view its info.
 * @return A new menu.
 */
int Main::menuSelectCondomino(bool remover) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE O UTILIZADOR:\n" << endl;
	if (remover)
		cout << "[ENTER] Remover condomino" << endl;
	else
		cout << "[ENTER] Alterar dados" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Utilizador   Nome Civil                    NIF" << endl;
	displaySelectCondomino();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getMoradores().size())
			option++;
		break;
	case KEY_ENTER:
		if (!remover) {
			int pos = option;
			resetOption();
			return menuEditCondomino(this->condominio.getMoradores()[pos]);
		} else {
			return menuDeleteCondomino(this->condominio.getMoradores()[option],
					0);
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirCondominos();
		break;
	default:
		break;
	}

	return menuSelectCondomino(remover);

}
/**
 * Edit tenant menu. The admin can choose a tenant data to be edited.
 * @param condomino Tenant whose data is going to be changed.
 * @return A new menu.
 */
int Main::menuEditCondomino(Condomino &condomino) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Condomino a alterar -> ";
	setcolor(YELLOW, BLACK);
	cout << condomino.getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ALTERAR DADOS\n" << endl;
	displayMenuOptions(12);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[12].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) {
			resetOption();
			editDadosContaAdmin(0, condomino); //Alterar nome de utilizador
		} else if (option == 1) {
			resetOption();
			editDadosContaAdmin(1, condomino); //Alterar password
		} else if (option == 2) {
			resetOption();
			editDadosContaAdmin(2, condomino); //Alterar direitos administrativos
		} else if (option == 3) {
			resetOption();
			editDadosCondominoAdmin(0, condomino); //Alterar nome civil
		} else if (option == 4) {
			resetOption();
			editDadosCondominoAdmin(1, condomino); //Alterar NIF
		} else if (option == 5) {
			resetOption();
			editDadosCondominoAdmin(2, condomino); //Alterar fundos mensais
		} else if (option == 6) {
			resetOption();
			editDadosCondominoAdmin(3, condomino); //Saldar divida
		} else { //Voltar atras
			resetOption();
			return menuGerirCondominos();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirCondominos();
		break;
	default:
		break;
	}
	return menuEditCondomino(condomino);
}
/**
 * Delete tenant menu. The admin can remove a tenant from the condominium.
 * @param condomino Tenant to be removed.
 * @param menuOption Option to be highlighted. 0 = Yes, 1 = No.
 */
int Main::menuDeleteCondomino(Condomino &condomino, int menuOption) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DO CONDOMINO A REMOVER:\n" << endl;
	cout << "Nome de utilizador - " << condomino.getNomeUtilizador() << endl;
	cout << "\nDados do condomino:" << endl;
	condomino.infoCondomino();

	bool sameUser = false;
	if (*(this->currentUser) == condomino)
		sameUser = true;
	if (sameUser)
		cout << "Tem a certeza que pretende remover a sua conta?" << endl;
	else
		cout << "Tem a certeza que pretende remover este condomino?" << endl;
	displayYesNo(menuOption);

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (menuOption - 1 >= 0)
			menuOption--;
		break;
	case KEY_RIGHT:
		if (menuOption + 1 < 2)
			menuOption++;
		break;
	case KEY_ENTER:
		if (menuOption == 0) {
			Condomino c1 = *currentUser;
			if (this->condominio.eraseMorador(condomino))
				cout << "\nUtilizador removido." << endl;
			setCurrentUser(c1);
			pressEnterToContinue();
			resetOption();
			if (sameUser)
				return menuInicial();
			else {
				if (this->option > 0)
					option--;
				return menuSelectCondomino(true);
			}
		} else if (menuOption == 1) {
			return menuSelectCondomino(true);
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirCondominos();
		break;
	default:
		break;
	}
	return menuDeleteCondomino(condomino, menuOption);
}

/**
 * Manage houses menu. The admin can list, create, edit or remove houses.
 * @return A new menu.
 */
int Main::menuGerirHabitacoes() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "GERIR HABITACOES" << endl;
	displayMenuOptions(9);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[9].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) //Ver lista de habitacoes
			return menuDisplayHabitacoesBy();
		else if (option == 1) { //Alterar dados de uma habitacao
			resetOption();
			return menuSelectHabitacao(false);
		} else if (option == 2) { //Adicionar habitacao
			resetOption();
			return menuSelectOrVacantHabitacao();
		} else if (option == 3) { //Remover habitacao
			resetOption();
			return menuSelectHabitacao(true);
		} else { //Voltar atras
			resetOption();
			return menuAdministrador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuAdministrador();
		break;
	default:
		break;
	}
	return menuGerirHabitacoes();
}
/**
 * Display houses by menu. The admin can list houses by type, rent or owner's NIF.
 * @return A new menu.
 */
int Main::menuDisplayHabitacoesBy() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ORDENAR POR" << endl;
	displayMenuOptions(18);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[18].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Ordenar por tipo
			resetOption();
			this->condominio.sortHabitacoes(0);
			return menuDisplayAllHabitacoes();
		} else if (option == 1) { //Ordenar por renda
			resetOption();
			this->condominio.sortHabitacoes(1);
			return menuDisplayAllHabitacoes();
		} else if (option == 2) { //Ordenar por NIF proprietario
			resetOption();
			this->condominio.sortHabitacoes(2);
			return menuDisplayAllHabitacoes();
		} else { //Voltar atras
			resetOption();
			return menuGerirHabitacoes();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirHabitacoes();
		break;
	default:
		break;
	}
	return menuDisplayHabitacoesBy();
}
/**
 * Display all houses menu. The houses are listed according to the option specified before. The admin can view their info by selecting them.
 * @return A new menu.
 */
int Main::menuDisplayAllHabitacoes() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE A HABITACAO:\n" << endl;
	cout << "[ENTER] Ver dados" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Habitacao      Renda         NIF Proprietario" << endl;

	if (this->condominio.getHabitacoes().empty()) {
		cout << "Nao existem habitacoes no condominio" << endl;
		pressEnterToContinue();
		return menuDisplayHabitacoesBy();
	}
	displaySelectHabitacao(this->condominio.getHabitacoes());

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getHabitacoes().size())
			option++;
		break;
	case KEY_ENTER:
		displayHabitacaoInfo(option);
		break;
	case KEY_ESC:
		resetOption();
		return menuDisplayHabitacoesBy();
		break;
	default:
		break;
	}
	return menuDisplayAllHabitacoes();
}
/**
 * Select house menu. The admin can choose a house to remove or edit its info.
 * @param remover If true, selecting will remove the house. If false, selecting will edit its info.
 */
int Main::menuSelectHabitacao(bool remover) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE A HABITACAO:\n" << endl;
	if (remover)
		cout << "[ENTER] Remover" << endl;
	else
		cout << "[ENTER] Editar" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Habitacao      Renda         NIF Proprietario" << endl;
	if (this->condominio.getHabitacoes().empty()) {
		cout << "Nao existem habitacoes no condominio" << endl;
		pressEnterToContinue();
		return menuGerirHabitacoes();
	}
	displaySelectHabitacao(this->condominio.getHabitacoes());

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getHabitacoes().size())
			option++;
		break;
	case KEY_ENTER:
		if (remover)
			return menuDeleteHabitacao(option, 0);
		else
			return menuEditHabitacao(this->condominio.getHabitacoes()[option]);
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirHabitacoes();
		break;
	default:
		break;
	}
	return menuSelectHabitacao(remover);
}
/**
 * Edit house menu. The admin can choose a house data to be edited.
 * @param habitacao Pointer to the house that is going to be changed.
 * @return A new menu.
 */
int Main::menuEditHabitacao(Habitacao* habitacao) {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ALTERAR DADOS" << endl;

	int tipoHabitacao = 0;
	if (habitacao->getTipo() == "Vivenda")
		tipoHabitacao = 13;
	else
		tipoHabitacao = 14;

	displayMenuOptions(tipoHabitacao);

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->menu[tipoHabitacao].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 5) {
			resetOption();
			return menuGerirHabitacoes();
		} else {
			editHabitacao(option, habitacao);
			this->condominio.sortHabitacoes(2);
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirHabitacoes();
		break;
	default:
		break;
	}
	return menuEditHabitacao(habitacao);
}
/**
 * Delete house menu. The admin can remove a house from the condominium.
 * @param pos Position of the house in the vector of houses of the condominium.
 * @param menuOption Option to be highlighted. 0 = Yes, 1 = No.
 */
int Main::menuDeleteHabitacao(int pos, int menuOption) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DA HABITACAO\n" << endl;
	cout << "Tipo: ";
	this->condominio.getHabitacoes()[pos]->info();

	cout << "Tem a certeza que pretende remover esta habitacao?" << endl;
	displayYesNo(menuOption);

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (menuOption - 1 >= 0)
			menuOption--;
		break;
	case KEY_RIGHT:
		if (menuOption + 1 < 2)
			menuOption++;
		break;
	case KEY_ENTER:
		if (menuOption == 0) {
			this->condominio.eraseHabitacao(pos);
			cout << "\nHabitacao removida." << endl;
			if (this->option > 0)
				option--;
			pressEnterToContinue();
			return menuSelectHabitacao(true);
		} else if (menuOption == 1) {
			return menuSelectHabitacao(true);
		}
		break;
	default:
		break;
	}
	return menuDeleteHabitacao(pos, menuOption);
}
/**
 * Select user or add an empty house menu. The admin can choose a user to add a house or add an empty house to the condominium.
 * @return A new menu.
 */
int Main::menuSelectOrVacantHabitacao() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ADICIONAR HABITACAO" << endl;
	displayMenuOptions(16);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[16].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Selecionar condomino
			resetOption();
			return menuSelectOwnerHabitacao();
		} else if (option == 1) { //Habitacao sem proprietario
			resetOption();
			Condomino c1 = Condomino("nome", "password", "nomeCivil", "");
			return menuAddHabitacao(c1);
		} else { //Voltar atras
			resetOption();
			return menuGerirHabitacoes();
		}
		break;
	default:
		break;
	}

	return menuSelectOrVacantHabitacao();
}
/**
 * Select user to whom a house is added menu. The admin can choose the owner of the house about to be added.
 * @return A new menu.
 */
int Main::menuSelectOwnerHabitacao() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE O UTILIZADOR:\n" << endl;
	cout << "[ENTER] Selecionar" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "Utilizador   Nome Civil                    NIF" << endl;
	displaySelectCondomino();

	int pos = -1;

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getMoradores().size())
			option++;
		break;
	case KEY_ENTER:
		pos = option;
		resetOption();
		return menuAddHabitacao(this->condominio.getMoradores()[pos]);
		break;
	case KEY_ESC:
		resetOption();
		return menuSelectOrVacantHabitacao();
		break;
	default:
		break;
	}

	return menuSelectOwnerHabitacao();

}

/**
 * Manage employees menu. The admin can list, hire or fire employees.
 */
int Main::menuGerirFuncionarios() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "GERIR FUNCIONARIOS" << endl;
	displayMenuOptions(10);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[10].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) //Ver lista de todos os funcionarios
			return menuDisplayFuncionariosBy();
		else if (option == 1) { //Contratar funcionario
			resetOption();
			return menuAddFuncionario();
		} else if (option == 2) { //Despedir funcionario
			resetOption();
			return menuFireFuncionario();
		} else if (option == 3) { //Voltar atras
			resetOption();
			return menuAdministrador();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuAdministrador();
		break;
	default:
		break;
	}
	return menuGerirFuncionarios();
}

/**
 * Display employees by menu. The admin can list employees by ID, specialty, occupation status or services done.
 * @return A new menu.
 */
int Main::menuDisplayFuncionariosBy() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "ORDENAR POR" << endl;
	displayMenuOptions(19);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[19].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Ordenar por ID
			resetOption();
			this->condominio.sortFuncionarios(0);
			return menuDisplayAllFuncionarios();
		} else if (option == 1) { //Ordenar por especialidade
			resetOption();
			this->condominio.sortFuncionarios(1);
			return menuDisplayAllFuncionarios();
		} else if (option == 2) { //Ordenar por estado de ocupacao
			resetOption();
			this->condominio.sortFuncionarios(2);
			return menuDisplayAllFuncionarios();
		} else if (option == 3) { //Ordenar por servicos feitos
			resetOption();
			this->condominio.sortFuncionarios(3);
			return menuDisplayAllFuncionarios();
		} else { //Voltar atras
			resetOption();
			return menuGerirFuncionarios();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirFuncionarios();
		break;
	default:
		break;
	}
	return menuDisplayFuncionariosBy();
}
/**
 * Display all employees menu. The admin can choose an employee to view its info.
 * @return A new menu.
 */
int Main::menuDisplayAllFuncionarios() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE O FUNCIONARIO:\n" << endl;
	cout << "[ENTER] Ver dados" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "ID\tEspecialidade\tEstado\tServicos Feitos" << endl;
	if (this->condominio.getFuncionarios().empty()) {
		cout << "Nao existem funcionarios no condominio" << endl;
		pressEnterToContinue();
		return menuDisplayFuncionariosBy();
	}
	displaySelectFuncionario();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getFuncionarios().size())
			option++;
		break;
	case KEY_ENTER:
		displayFuncionarioInfo(option);
		break;
	case KEY_ESC:
		resetOption();
		return menuDisplayFuncionariosBy();
		break;
	default:
		break;
	}
	return menuDisplayAllFuncionarios();
}
/**
 * Hire employee menu. The admin can choose a type of employee to hire.
 * @return A new menu.
 */
int Main::menuAddFuncionario() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "CONTRATAR FUNCIONARIO DE" << endl;
	displayMenuOptions(20);

	displayTime();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < menu[20].size())
			option++;
		break;
	case KEY_ENTER:
		if (option == 0) { //Limpeza
			return menuConfirmAddFuncionario(0, 0);
		} else if (option == 1) { //Canalizacao
			return menuConfirmAddFuncionario(1, 0);
		} else if (option == 2) { //Pintura
			return menuConfirmAddFuncionario(2, 0);
		} else { //Voltar atras
			resetOption();
			return menuGerirFuncionarios();
		}
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirFuncionarios();
		break;
	default:
		break;
	}
	return menuAddFuncionario();
}
/**
 * Confirm hiring an employee menu. Shows the condominium funds and number of employees.
 * The admin can confirm or not hiring an employee.
 * @param specialty Type of employee to hire.
 * @param menuOption Changes the highlighted option. 0 = Yes, 1 = No.
 * @return A new menu.
 */
int Main::menuConfirmAddFuncionario(int specialty, int menuOption) {
	displayLogo();
	gotoxy(0, 8);

	string especialidade;
	if (specialty == 0) {
		cout << "CONTRATAR FUNCIONARIO DE LIMPEZA\n" << endl;
		especialidade = "Limpeza";
	} else if (specialty == 1) {
		cout << "CONTRATAR CANALIZADOR\n" << endl;
		especialidade = "Canalizacao";
	} else if (specialty == 2) {
		cout << "CONTRATAR PINTOR\n" << endl;
		especialidade = "Pintura";
	}

	cout << "Numero total de funcionarios no condominio = "
			<< this->condominio.getFuncionarios().size() << endl;
	if (specialty == 0)
		cout << "Numero de funcionarios de limpeza actual = "
				<< this->condominio.getNumFuncLimpeza() << endl;
	else if (specialty == 1)
		cout << "Numero de canalizadores actual = "
				<< this->condominio.getNumFuncCanalizacao() << endl;
	else if (specialty == 2)
		cout << "Numero de pintores actual = "
				<< this->condominio.getNumFuncPintura() << endl;

	cout << "\nFundos do condominio = " << this->condominio.getFundos() << "$"
			<< endl;
	cout << "Preco inicial do funcionario = 1000$" << endl;
	cout << "Salario mensal = 500$\n" << endl;

	if (this->condominio.getFundos() < 1000) {
		cout << "O condominio nao tem fundos para contratar o funcionario.\n"
				<< endl;
		pressEnterToContinue();
		return menuAddFuncionario();
	}

	cout << "Tem a certeza que pretende contratar este funcionario?" << endl;
	displayYesNo(menuOption);

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (menuOption - 1 >= 0)
			menuOption--;
		break;
	case KEY_RIGHT:
		if (menuOption + 1 < 2)
			menuOption++;
		break;
	case KEY_ENTER:
		if (menuOption == 0) {
			Funcionario f1 = Funcionario(especialidade);
			this->condominio.addFuncionario(f1);
			cout << "\nFuncionario contratado." << endl;
			pressEnterToContinue();
			return menuAddFuncionario();
		} else if (menuOption == 1) {
			return menuAddFuncionario();
		}
		break;
	default:
		break;
	}
	return menuConfirmAddFuncionario(specialty, menuOption);
}
/**
 * Fire employee menu. The admin can choose an employee to fire.
 * @return A new menu.
 */
int Main::menuFireFuncionario() {
	displayLogo();

	gotoxy(10, 6);
	cout << "Bem-vindo, ";
	setcolor(YELLOW, BLACK);
	cout << this->currentUser->getNomeUtilizador() << "\n" << endl;
	setcolor(WHITE, BLACK);

	gotoxy(30, 8);
	cout << "SELECIONE O FUNCIONARIO:\n" << endl;
	cout << "[ENTER] Despedir" << endl;
	cout << "[ESC] Voltar atras\n" << endl;
	cout << "ID\tEspecialidade\tEstado\tServicos Feitos" << endl;
	if (this->condominio.getFuncionarios().empty()) {
		cout << "Nao existem funcionarios no condominio" << endl;
		pressEnterToContinue();
		return menuDisplayFuncionariosBy();
	}
	displaySelectFuncionario();

	int c = getch();
	switch (c) {
	case KEY_UP:
		if (option - 1 >= 0)
			option--;
		break;
	case KEY_DOWN:
		if (option + 1 < this->condominio.getFuncionarios().size())
			option++;
		break;
	case KEY_ENTER:
		menuDeleteFuncionario(option, 0);
		break;
	case KEY_ESC:
		resetOption();
		return menuGerirFuncionarios();
		break;
	default:
		break;
	}
	return menuFireFuncionario();
}
/**
 * Confirm firing an employee menu. Shows the employee info and a confirmation menu.
 * @param pos Position of the employee in condominium's the vector of employees.
 * @param menuOption Changes the highlighted option. 0 = Yes, 1 = No.
 * @return A new menu.
 */
int Main::menuDeleteFuncionario(int pos, int menuOption) {
	displayLogo();
	gotoxy(0, 8);
	cout << "DADOS DO FUNCIONARIO\n" << endl;
	this->condominio.getFuncionarios()[pos].info();

	cout << "Tem a certeza que pretende despedir este funcionario?" << endl;
	displayYesNo(menuOption);

	int c = getch();
	switch (c) {
	case KEY_LEFT:
		if (menuOption - 1 >= 0)
			menuOption--;
		break;
	case KEY_RIGHT:
		if (menuOption + 1 < 2)
			menuOption++;
		break;
	case KEY_ENTER:
		if (menuOption == 0) {
			this->condominio.eraseFuncionario(pos);
			cout << "\nFuncionario despedido." << endl;
			if (this->option > 0)
				option--;
			pressEnterToContinue();
			return menuFireFuncionario();
		} else if (menuOption == 1) {
			return menuFireFuncionario();
		}
		break;
	default:
		break;
	}
	return menuDeleteFuncionario(pos, menuOption);
}

//TODO menuGerirServicos()
int Main::menuGerirServicos() {
	return EXIT_FAILURE;
}

/**
 * Imports condominium data from a .txt file. Updates condominium funds and current month.
 * @retval TRUE Successfully imported data.
 * @retval FALSE Couldn't read from .txt file.
 */
bool Main::importCondominio() {
	ifstream myfile(pathCondominio);
	string line = "";
	long int fundos = 0;
	int currentMes = 0;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			fundos = atol(line.c_str());
			getline(myfile, line);
			currentMes = atoi(line.c_str());
			this->condominio.setFundos(fundos);
			this->condominio.setCurrentMes(currentMes);
		}
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro do condominio.\n";
		pressEnterToContinue();
		return false;
	}
}
/**
 * Exports condominium data to a .txt file. Exports condominum funds and current month.
 * @retval TRUE Successfully exported data.
 * @retval FALSE Couldn't write to .txt file.
 */
bool Main::exportCondominio() {
	ofstream myfile(pathCondominio);

	if (myfile.is_open()) {
		myfile << this->condominio.getFundos() << endl;
		myfile << this->condominio.getMes() << endl;
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro do condominio.\n";
		pressEnterToContinue();
		return false;
	}
}
/**
 * Imports user data from a .txt file. Updates condominium users.
 * @retval TRUE Successfully imported data.
 * @retval FALSE Couldn't read from .txt file.
 */
bool Main::importCondominos() {
	ifstream myfile(pathCondominos);
	string line = "";
	bool admin = false;
	string nomeUtilizador = "";
	string password = "";
	string nomeCivil = "";
	string NIF = "";
	long int fundosMensais = 0;
	long int divida = 0;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line == "1") {
				admin = true;
			} else if (line == "0") {
				admin = false;
			}
			getline(myfile, nomeUtilizador);
			getline(myfile, password);
			getline(myfile, nomeCivil);
			getline(myfile, NIF);
			getline(myfile, line);
			fundosMensais = atol(line.c_str());
			getline(myfile, line);
			divida = atol(line.c_str());
			Condomino c1 = Condomino(nomeUtilizador, password, admin, nomeCivil,
					NIF, fundosMensais, divida);
			this->condominio.addMorador(c1);
			getline(myfile, line);
		}
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de condominos.\n";
		pressEnterToContinue();
		return false;
	}

}
/**
 * Exports user data to a .txt file. Exports condominum users.
 * @retval TRUE Successfully exported data.
 * @retval FALSE Couldn't write to .txt file.
 */
bool Main::exportCondominos() {
	ofstream myfile(pathCondominos, ios::trunc);

	if (myfile.is_open()) {
		for (size_t i = 0; i < this->condominio.getMoradores().size(); i++) {
			if (this->condominio.getMoradores()[i].isAdmin())
				myfile << "1" << endl;
			else
				myfile << "0" << endl;
			myfile << this->condominio.getMoradores()[i].getNomeUtilizador()
					<< endl;
			myfile << this->condominio.getMoradores()[i].getPassword() << endl;
			myfile << this->condominio.getMoradores()[i].getNomeCivil() << endl;
			myfile << this->condominio.getMoradores()[i].getNIF() << endl;
			myfile << this->condominio.getMoradores()[i].getFundosMensais()
					<< endl;
			myfile << this->condominio.getMoradores()[i].getDivida() << endl;
			myfile << endl;
		}
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de condominos.\n";
		pressEnterToContinue();
		return false;
	}
}
/**
 * Imports house data from a .txt file. Updates condominium houses.
 * @retval TRUE Successfully imported data.
 * @retval FALSE Couldn't read from .txt file.
 */
bool Main::importHabitacoes() {
	ifstream myfile(pathHabitacoes);
	string line = "";
	string tipo = "";
	string morada = "";
	string codigoPostal = "";
	string nifProprietario = "";
	string substr = "";
	bool pago[12] = { 0 };

	float areaInterior = 0;
	float areaExterior = 0;
	bool piscina = false;

	int tipologia = 0;
	int piso = 0;

	int idServico = -1;

	vector<Habitacao*> habitacoes;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			tipo = line;
			getline(myfile, morada);
			getline(myfile, codigoPostal);
			getline(myfile, nifProprietario);
			getline(myfile, line);
			for (size_t i = 0; i < 12; i++) {
				substr = line.substr(i, 1);
				if (substr == "0")
					pago[i] = false;
				else
					pago[i] = true;
			}

			if (tipo == "Vivenda") {
				getline(myfile, line);
				areaInterior = atof(line.c_str());
				getline(myfile, line);
				areaExterior = atof(line.c_str());
				getline(myfile, line);
				if (line == "0")
					piscina = false;
				else
					piscina = true;
				getline(myfile, line);
				idServico = atoi(line.c_str());

				Vivenda* v1 = new Vivenda(morada, codigoPostal, nifProprietario,
						pago, idServico, areaInterior, areaExterior, piscina);
				habitacoes.push_back(v1);
			} else if (tipo == "Apartamento") {
				getline(myfile, line);
				tipologia = atoi(line.c_str());
				getline(myfile, line);
				areaInterior = atof(line.c_str());
				getline(myfile, line);
				piso = atoi(line.c_str());
				getline(myfile, line);
				idServico = atoi(line.c_str());
				Apartamento* a1 = new Apartamento(morada, codigoPostal,
						nifProprietario, pago, idServico, tipologia, areaInterior, piso);
				habitacoes.push_back(a1);
			}
			getline(myfile, line);
		}
		myfile.close();
		sort(habitacoes.begin(), habitacoes.end(), compHabitacaoNIF);
		this->condominio.setHabitacoes(habitacoes);
		this->condominio.updateHabitacoesCondominos();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de habitacoes.\n";
		pressEnterToContinue();
		return false;
	}
}
/**
 * Exports house data to a .txt file. Exports condominum houses.
 * @retval TRUE Successfully exported data.
 * @retval FALSE Couldn't write to .txt file.
 */
bool Main::exportHabitacoes() {
	ofstream myfile(pathHabitacoes, ios::trunc);

	if (myfile.is_open()) {
		vector<Habitacao*> habitacoes = this->condominio.getHabitacoes();

		for (size_t j = 0; j < habitacoes.size(); j++) {
			myfile << habitacoes[j]->getTipo() << endl;
			myfile << habitacoes[j]->getMorada() << endl;
			myfile << habitacoes[j]->getCodigoPostal() << endl;
			myfile << habitacoes[j]->getNIFProprietario() << endl;
			for (size_t k = 0; k < 12; k++) {
				if (habitacoes[j]->getPago(k) == false)
					myfile << "0";
				else
					myfile << "1";
			}
			myfile << endl;
			if (habitacoes[j]->getTipo() == "Vivenda") {
				myfile << habitacoes[j]->getAreaInterior() << endl;
				myfile << habitacoes[j]->getAreaExterior() << endl;
				if (habitacoes[j]->getPiscina() == false)
					myfile << "0" << endl;
				else
					myfile << "1" << endl;
				myfile << habitacoes[j]->getServico() << endl;
				myfile << endl;
			} else if (habitacoes[j]->getTipo() == "Apartamento") {
				myfile << habitacoes[j]->getTipologia() << endl;
				myfile << habitacoes[j]->getAreaInterior() << endl;
				myfile << habitacoes[j]->getPiso() << endl;
				myfile << habitacoes[j]->getServico() << endl;
				myfile << endl;
			}
		}
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de habitacoes.\n";
		pressEnterToContinue();
		return false;
	}
}
/**
 * Imports employee data from a .txt file. Updates condominium employees.
 * @retval TRUE Successfully imported data.
 * @retval FALSE Couldn't read from .txt file.
 */
bool Main::importFuncionarios() {
	ifstream myfile(pathFuncionarios);
	string line = "";
	int id = 0;
	string especialidade = "";

	vector<Funcionario> funcionarios;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			id = atoi(line.c_str());
			getline(myfile, especialidade);
			Funcionario f1 = Funcionario(especialidade, id);
			funcionarios.push_back(f1);

			getline(myfile, line);
		}
		myfile.close();
		insertionSort(funcionarios);
		this->condominio.setFuncionarios(funcionarios);
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de funcionarios.\n";
		pressEnterToContinue();
		return false;
	}
}
/**
 * Exports employee data to a .txt file. Exports condominum employees.
 * @retval TRUE Successfully exported data.
 * @retval FALSE Couldn't write to .txt file.
 */
bool Main::exportFuncionarios() {
	ofstream myfile(pathFuncionarios, ios::trunc);

	if (myfile.is_open()) {
		vector<Funcionario> funcionarios = this->condominio.getFuncionarios();

		for (size_t i = 0; i < funcionarios.size(); i++) {
			myfile << funcionarios[i].getID() << endl;
			myfile << funcionarios[i].getEspecialidade() << endl;
			myfile << endl;
		}
		myfile.close();
		return true;
	} else {
		displayLogo();
		cout
				<< "ERRO: Ocorreu um problema ao aceder ao ficheiro de funcionarios.\n";
		pressEnterToContinue();
		return false;
	}
}
/**
 * Calls functions to export data to several .txt files.
 * @retval TRUE Successfully exported data.
 * @retval FALSE At least one of the called functions couldn't export data.
 */
int Main::exitFunction() {
	if (!this->exportCondominio() || !this->exportCondominos()
			|| !this->exportHabitacoes() || !this->exportFuncionarios())
		return EXIT_FAILURE;
	else
		return EXIT_SUCCESS;
}

/*
 * Non-class functions
 */

/**
 * Checks if string has one or more whitespaces.
 * @param s String to be checked.
 * @retval TRUE String has at least one whitespace.
 * @retval FALSE No whitespaces were found.
 */
bool hasWhitespace(string s) {
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == ' ')
			return true;
	}
	return false;
}
/**
 * Checks if string is a positive integer.
 * @param s String to be checked.
 * @retval TRUE String is a positive integer.
 * @retval FALSE String isn't a positive integer.
 */
bool isNumber(string s) {
	string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return (!s.empty() && it == s.end());
}
/** Checks if string is a valid name:
 * - Name must start with an uppercase letter;
 * - No consecutive spaces;
 * - Letter after space must be uppercase;
 * - Name must end with a letter;
 * @param s String to be checked.
 * @retval TRUE String is a valid name.
 * @retval FAIL Name failed one of above requirements.
 */
bool isName(string s) {
	if (s.empty() || islower(s[0]) || s[0] == ' ')
		return false;

	bool prevSpace = false;
	for (size_t i = 1; i < s.size(); i++) {
		if (prevSpace) {
			if (!isupper(s[i]))
				return false;
			else
				prevSpace = false;
		} else if (s[i] == ' ') {
			prevSpace = true;
		} else if (!islower(s[i]))
			return false;
	}

	if (s[s.size() - 1] == ' ')
		return false;
	return true;
}

/**
 * Displays the program logo.
 */
void displayLogo() {
	ifstream myfile(pathLogo);
	string line = "";
	clrscr();
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			setcolor(YELLOW, BLACK);
			cout << line << endl;
		}
		myfile.close();
		setcolor(WHITE, BLACK);
	} else {
		cout << "ERRO: Ocorreu um problema ao aceder ao ficheiro do logo."
				<< endl;
	}
}
/**
 * Get current time, format is HH:mm:ss
 * @return A string with the time.
 */
string currentTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
//strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
	strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);
	return buf;
}
/**
 * Waits until user presses Enter.
 */
void pressEnterToContinue() {
	cout << "Pressione ENTER para continuar." << endl;
	cin.ignore();
	fflush(stdin);
}

/**
 * Initializes a vector<string> of months. Updates mesesAno vector.
 */
void createMesesAno() {
	mesesAno.push_back("Janeiro");
	mesesAno.push_back("Fevereiro");
	mesesAno.push_back("Marco");
	mesesAno.push_back("Abril");
	mesesAno.push_back("Maio");
	mesesAno.push_back("Junho");
	mesesAno.push_back("Julho");
	mesesAno.push_back("Agosto");
	mesesAno.push_back("Setembro");
	mesesAno.push_back("Outubro");
	mesesAno.push_back("Novembro");
	mesesAno.push_back("Dezembro");
}
/**
 * Initializes a vector with vectors of strings, containing the options for each menu. Updates menuOptions vector.
 */
void createMenuOptions() {
	vector<vector<string> > menuOptions;

	vector<string> menuInicial;
	menuOptions.push_back(menuInicial);

	menuOptions[0].push_back("Login");										//0
	menuOptions[0].push_back("Registo");									//1
	menuOptions[0].push_back("Sair");										//2

	vector<string> menuUtilizadorAdmin;
	menuOptions.push_back(menuUtilizadorAdmin);

	menuOptions[1].push_back("Menu Administrador");							//0
	menuOptions[1].push_back("Alterar dados da conta");						//1
	menuOptions[1].push_back("Ver dados de condomino");						//2
	menuOptions[1].push_back("Alterar dados de condomino");					//3
	menuOptions[1].push_back("Ver habitacoes possuidas");					//4
	menuOptions[1].push_back("Adicionar habitacao");						//5
	menuOptions[1].push_back("Ver servicos requisitados");  				//6
	menuOptions[1].push_back("Requisitar um servico");						//7
	menuOptions[1].push_back("Sair");										//8

	vector<string> menuUtilizadorNormal;
	menuOptions.push_back(menuUtilizadorNormal);

	menuOptions[2].push_back("Alterar dados da conta");						//0
	menuOptions[2].push_back("Ver dados de condomino");						//1
	menuOptions[2].push_back("Alterar dados de condomino");					//2
	menuOptions[2].push_back("Ver habitacoes possuidas");					//3
	menuOptions[2].push_back("Adicionar habitacao");						//4
	menuOptions[2].push_back("Ver servicos requisitados");					//5
	menuOptions[2].push_back("Requisitar um servico");						//6
	menuOptions[2].push_back("Sair");										//7

	vector<string> menuDadosConta;
	menuOptions.push_back(menuDadosConta);

	menuOptions[3].push_back("Alterar nome de utilizador");					//0
	menuOptions[3].push_back("Alterar password");							//1
	menuOptions[3].push_back("Voltar atras");								//2

	vector<string> menuDadosCondomino;
	menuOptions.push_back(menuDadosCondomino);

	menuOptions[4].push_back("Alterar nome civil");							//0
	menuOptions[4].push_back("Alterar NIF");								//1
	menuOptions[4].push_back("Alterar fundos mensais");						//2
	menuOptions[4].push_back("Saldar divida");								//3
	menuOptions[4].push_back("Voltar atras");								//4

	vector<string> menuHabitacoesPossuidas;
	menuOptions.push_back(menuHabitacoesPossuidas);

	menuOptions[5].push_back("Ver informacao das habitacoes");				//0
	menuOptions[5].push_back("Ver estado da renda");						//1
	menuOptions[5].push_back("Remover habitacao");							//2
	menuOptions[5].push_back("Voltar atras");								//3

	vector<string> menuRequisitarServico;
	menuOptions.push_back(menuRequisitarServico);

	menuOptions[6].push_back("Limpeza (2 min)");							//0
	menuOptions[6].push_back("Canalizacao (5 min)");						//1
	menuOptions[6].push_back("Pintura (10 min)");							//2
	menuOptions[6].push_back("Voltar atras");								//3

	vector<string> menuAdmin;
	menuOptions.push_back(menuAdmin);

	menuOptions[7].push_back("Gerir condominos");							//0
	menuOptions[7].push_back("Gerir habitacoes");							//1
	menuOptions[7].push_back("Gerir funcionarios");							//2
	menuOptions[7].push_back("Gerir servicos");								//3
	menuOptions[7].push_back("Fim do Mes");									//4
	menuOptions[7].push_back("Voltar atras");								//5

	vector<string> menuGerirCondominos;
	menuOptions.push_back(menuGerirCondominos);
	menuOptions[8].push_back("Ver lista de todos os condominos");			//0
	menuOptions[8].push_back("Alterar condomino");							//1
	menuOptions[8].push_back("Adicionar condomino");						//2
	menuOptions[8].push_back("Remover condomino");							//2
	menuOptions[8].push_back("Voltar atras");								//3

	vector<string> menuGerirHabitacoes;
	menuOptions.push_back(menuGerirHabitacoes);
	menuOptions[9].push_back("Ver lista de todas as habitacoes");			//0
	menuOptions[9].push_back("Alterar habitacao");							//1
	menuOptions[9].push_back("Adicionar habitacao");						//2
	menuOptions[9].push_back("Remover habitacao");							//3
	menuOptions[9].push_back("Voltar atras");								//4

	vector<string> menuGerirFuncionarios;
	menuOptions.push_back(menuGerirFuncionarios);
	menuOptions[10].push_back("Ver lista de todos os funcionarios");		//0
	menuOptions[10].push_back("Contratar funcionario");						//1
	menuOptions[10].push_back("Despedir funcionario");						//3
	menuOptions[10].push_back("Voltar atras");								//4

	vector<string> menuGerirServicos;
	menuOptions.push_back(menuGerirServicos);
	menuOptions[11].push_back("Ver lista de todos os servicos efectuados");	//0
	menuOptions[11].push_back("Ver lista de todos os servicos em curso");	//1
	menuOptions[11].push_back("Ver lista de todos os servicos em espera");	//2
	menuOptions[11].push_back("Cancelar servico");							//3
	menuOptions[11].push_back("Voltar atras");								//4

	vector<string> menuDadosContaCondomino;
	menuOptions.push_back(menuDadosContaCondomino);

	menuOptions[12].push_back("Alterar nome de utilizador");				//0
	menuOptions[12].push_back("Alterar password");							//1
	menuOptions[12].push_back("Alterar estado da conta");					//2
	menuOptions[12].push_back("Alterar nome civil");						//3
	menuOptions[12].push_back("Alterar NIF");								//4
	menuOptions[12].push_back("Alterar fundos mensais");					//5
	menuOptions[12].push_back("Saldar divida");								//6
	menuOptions[12].push_back("Voltar atras");								//7

	vector<string> menuDadosVivenda;
	menuOptions.push_back(menuDadosVivenda);

	menuOptions[13].push_back("Alterar morada");							//0
	menuOptions[13].push_back("Alterar codigo postal");						//1
	menuOptions[13].push_back("Alterar area habitacional");					//2
	menuOptions[13].push_back("Alterar area exterior");						//3
	menuOptions[13].push_back("Alterar piscina");							//4
	menuOptions[13].push_back("Voltar atras");								//5

	vector<string> menuDadosApartamento;
	menuOptions.push_back(menuDadosApartamento);

	menuOptions[14].push_back("Alterar morada");							//0
	menuOptions[14].push_back("Alterar codigo postal");						//1
	menuOptions[14].push_back("Alterar area habitacional");					//2
	menuOptions[14].push_back("Alterar tipologia");							//3
	menuOptions[14].push_back("Alterar piso");								//4
	menuOptions[14].push_back("Voltar atras");								//5

	vector<string> menuAddHabitacaoNormal;
	menuOptions.push_back(menuAddHabitacaoNormal);

	menuOptions[15].push_back("Selecionar habitacao");						//0
	menuOptions[15].push_back("Nova habitacao");							//1
	menuOptions[15].push_back("Voltar atras");								//2

	vector<string> menuAddHabitacaoAdmin;
	menuOptions.push_back(menuAddHabitacaoAdmin);

	menuOptions[16].push_back("Selecionar condomino");						//0
	menuOptions[16].push_back("Habitacao sem proprietario");				//1
	menuOptions[16].push_back("Voltar atras");								//2

	vector<string> menuDisplayCondominosBy;
	menuOptions.push_back(menuDisplayCondominosBy);

	menuOptions[17].push_back("Nome de utilizador");						//0
	menuOptions[17].push_back("Nome Civil");								//1
	menuOptions[17].push_back("NIF");										//2
	menuOptions[17].push_back("Voltar atras");								//3

	vector<string> menuDisplayHabitacoesBy;
	menuOptions.push_back(menuDisplayHabitacoesBy);

	menuOptions[18].push_back("Tipo");										//0
	menuOptions[18].push_back("Renda");										//1
	menuOptions[18].push_back("NIF Proprietario");							//2
	menuOptions[18].push_back("Voltar atras");								//3

	vector<string> menuDisplayFuncionariosBy;
	menuOptions.push_back(menuDisplayFuncionariosBy);

	menuOptions[19].push_back("ID");										//0
	menuOptions[19].push_back("Especialidade");								//1
	menuOptions[19].push_back("Estado de ocupacao");						//2
	menuOptions[19].push_back("Servicos efectuados");						//3
	menuOptions[19].push_back("Voltar atras");								//4

	vector<string> menuEspecialidade;
	menuOptions.push_back(menuEspecialidade);

	menuOptions[20].push_back("Limpeza");									//0
	menuOptions[20].push_back("Canalizacao");								//1
	menuOptions[20].push_back("Pintura");									//2
	menuOptions[20].push_back("Voltar atras");								//3

	vector<string> menuServicosRequisitados;
	menuOptions.push_back(menuServicosRequisitados);

	menuOptions[21].push_back("Ver a lista dos servicos efectuados");		//0
	menuOptions[21].push_back("Ver a lista dos servicos em curso");			//1
	menuOptions[21].push_back("Ver a lista dos servicos em espera");		//2
	menuOptions[21].push_back("Cancelar servico");							//3
	menuOptions[21].push_back("Voltar atras");								//4

	vector<string> menuCancelarServico;
	menuOptions.push_back(menuCancelarServico);

	menuOptions[22].push_back("Servico em Curso");							//0
	menuOptions[22].push_back("Servico em Espera");							//1
	menuOptions[22].push_back("Voltar atras");								//2

	menu = menuOptions;
}

/**
 * Main function.
 * @retval EXIT_SUCCESS No errors occurred during the execution.
 * @retval EXIT_FAILURE Error occurred.
 */
int main() {
	Main main = Main();

	createMesesAno();
	createMenuOptions();
	main.setMenus(menu);

	main.importCondominio();
	main.importCondominos();
	main.importHabitacoes();
	main.importFuncionarios();

	main.menuInicial();

	return main.exitFunction();
}

