#include "../headers/Condomino.h"

Condomino::Condomino(string nomeUtilizador, string password) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = false;
	this->nomeCivil = "NAO DEFINIDO";
	this->NIF = "NAO DEFINIDO";
	this->fundosMensais = 0;
	this->divida = 0;
}
Condomino::Condomino(string nomeUtilizador, string password, string nomeCivil,
		string NIF) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = false;
	this->nomeCivil = nomeCivil;
	this->NIF = NIF;
	this->fundosMensais = 0;
	this->divida = 0;
}
Condomino::Condomino(string nomeUtilizador, string password, bool admin,
		string nomeCivil, string NIF, long int fundosMensais, long int divida) {
	this->nomeUtilizador = nomeUtilizador;
	this->password = password;
	this->admin = admin;
	this->nomeCivil = nomeCivil;
	this->NIF = NIF;
	this->fundosMensais = fundosMensais;
	this->divida = divida;
}

string Condomino::getNomeUtilizador() const {
	return nomeUtilizador;
}
string Condomino::getPassword() const {
	return password;
}
bool Condomino::isAdmin() const {
	return admin;
}
string Condomino::getNomeCivil() const {
	return nomeCivil;
}
string Condomino::getNIF() const {
	return NIF;
}
int Condomino::getFundosMensais() const {
	return fundosMensais;
}
int Condomino::getDivida() const {
	return divida;
}
vector<Habitacao *> Condomino::getHabitacoes() {
	return habitacoes;
}

void Condomino::setNomeUtilizador(string novoNomeUtilizador) {
	this->nomeUtilizador = novoNomeUtilizador;
}
void Condomino::setPassword(string novaPassword) {
	this->password = novaPassword;
}
void Condomino::setAdmin(bool admin){
	this->admin = admin;
}
void Condomino::setNomeCivil(string novoNomeCivil) {
	this->nomeCivil = novoNomeCivil;
}
void Condomino::setNIF(string novoNIF) {
	this->NIF = novoNIF;
	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		this->habitacoes[i]->setProprietario(novoNIF);
	}
}
void Condomino::setFundosMensais(long int novosFundos){
	this->fundosMensais = novosFundos;
}
void Condomino::setDivida(long int novaDivida){
	this->divida = novaDivida;
}
void Condomino::setHabitacoes(vector<Habitacao*> habitacoes) {
	this->habitacoes = habitacoes;
}

bool Condomino::addHabitacao(Habitacao* h1) {
	int pos = -1;
	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		if (habitacoes[i]->getMorada() == h1->getMorada())
			pos = i;
	}
	if (pos == -1) {
		h1->setProprietario(this->NIF);
		this->habitacoes.push_back(h1);
		insertionSort(this->habitacoes);
		return true;
	} else
		return false;
}
bool Condomino::eraseHabitacao(Habitacao* h1) {
	int pos = -1;
	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		if (habitacoes[i]->getMorada() == h1->getMorada())
			pos = i;
	}
	if (pos != -1) {
		delete h1;
		habitacoes.erase(habitacoes.begin() + pos);
		insertionSort(this->habitacoes);
		return true;
	} else
		return false;
}

bool Condomino::validPassword(string password) {
	if (this->password == password)
		return true;
	else
		return false;
}
bool Condomino::hasDados() const {
	if (this->nomeCivil == "NAO DEFINIDO" || this->NIF == "NAO DEFINIDO")
		return false;
	else
		return true;
}
bool Condomino::operator==(const Condomino c1) const {
	if (this->nomeUtilizador == c1.nomeUtilizador) {
		return true;
	} else if (this->NIF == "NAO DEFINIDO")
		return false;
	else
		return (this->NIF == c1.NIF);
}
bool Condomino::operator<(const Condomino c1) const {
	if (this->nomeUtilizador < c1.nomeUtilizador)
		return true;
	else
		return false;
	/*if (this->nomeCivil < c1.nomeCivil)
	 return true;
	 else if (this->nomeCivil > c1.nomeCivil)
	 return false;
	 else
	 return (this->NIF < c1.NIF);*/
}

void Condomino::infoConta() const {
	cout << "Nome de utilizador - " << nomeUtilizador << endl;
	cout << "Password - " << password << endl;
	cout << "Admin - ";
	if (this->admin)
		cout << "SIM" << endl;
	else
		cout << "NAO" << endl;
	cout << endl;
}
void Condomino::infoCondomino() const {
	cout << this->nomeCivil << endl;
	cout << "NIF: " << this->NIF << endl;
	cout << "Numero de habitacoes: " << this->habitacoes.size() << endl;
	cout << "Fundos Mensais = " << this->fundosMensais << "$" << endl;
	cout << "Divida = " << this->divida << "$" << "\n" << endl;
}
void Condomino::infoHabitacoes() const {
	cout << "Numero de habitacoes = " << this->habitacoes.size() << "\n"
			<< endl;

	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		cout << i + 1 << " - ";
		habitacoes[i]->info();
	}
}
void Condomino::infoRenda() const {
	cout << "ESTADO DA RENDA:" << endl;
	cout << "Numero de habitacoes = " << this->habitacoes.size() << "\n"
			<< endl;

	cout << "\t\t J F M A M J J A S O N D" << endl;
	for (size_t i = 0; i < this->habitacoes.size(); i++) {
		cout << i + 1 << " - " << habitacoes[i]->getTipo() << "\t|";
		for (size_t j = 0; j < 12; j++) {
			if (this->habitacoes[i]->getPago(j) == 1)
				cout << "X|";
			else
				cout << " |";
		}
		cout << endl;
	}
}
