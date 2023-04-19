#include <iostream>
#include <cmath>
using namespace std;

class Fractie {
	private:
		int numarator, numitor;
		void simplifica() {
			int a = abs(numarator), b = abs(numitor), r;
			while(b) {
				r = a % b;
				a = b, b = r;
			}
			numarator /= a, numitor /= a;
		}
	public:
		void afiseaza();
		friend void afiseaza(Fractie F); //declararea functiei prietene
		void seteaza(int a, int b);
		Fractie(int a, int b); //constructor, constructorul poate fi utilizat ca un obiect al clasei ex: cout << Fractie(a, y).Numarator() + 1
		Fractie(const Fractie & F); //constructor de copiere IMPORTANT: Atunci cand ducem un obiect in functie ca valoare
									//atuncti se apeleaza constructorul de copiere
		~Fractie() {
			cout << "fractia " << numarator << "/" << numitor << " a fost eliminata\n";
		}
		Fractie & citeste();
		Fractie & scrie();
		//friend Fractie suma(Fractie F, Fractie G);
		friend Fractie produs(Fractie F, Fractie G);
		//metode get
		int Numarator();
		int Numitor();
		//metode set
		Fractie & Numarator(int a);
		Fractie & Numitor(int b);
		//supraincarcarea functiilor
		Fractie & creste();
		Fractie & creste(int n);
		//supraincarcarea operatorilor
		//operator binar
		Fractie operator+(Fractie F);
		Fractie operator+(int n);
		friend Fractie operator+(int n, Fractie F);
		//operator unar
		Fractie operator-();
		//operator relational
		friend bool operator<(Fractie F, Fractie G);
		friend bool operator<(Fractie F, int n);
		friend bool operator<(int n, Fractie F);
		//operatorul de atribuire
		Fractie & operator=(const Fractie &F);
		Fractie & operator=(const int &n);
		Fractie & operator+=(const Fractie &F);
		Fractie & operator+=(const int &n);
		//operatorii de citire si afisare
		friend istream & operator >> (istream & in, Fractie & F);
		friend ostream & operator << (ostream & out, Fractie & F);
		//operator de incrementare prefixata si postfixata
		Fractie & operator ++();
		Fractie operator ++(int);
};

void Fractie::afiseaza() {
	cout << numarator << "/" << numitor << "\n";
}

void afiseaza(Fractie F) { //functie prietena
	cout << F.numarator << "/" << F.numitor << "\n";
}

void Fractie::seteaza(int a, int b) {
	numarator = a, numitor = b;
}

Fractie::Fractie(int a = 0, int b = 1) { //constructor, am atribuit valori implicite pentru a si b in caz ca lipsesc
	if(b < 0)
		a = -a, b = -b;
	numarator = a, numitor = b;
	simplifica();
}

Fractie::Fractie(const Fractie & F) { //declararea constructorului de copiere
			numarator = F.numarator, numitor = F.numitor;
			simplifica();
		}
		
Fractie & Fractie::citeste() {
	int a, b;
	cin >> a >> b;
	if(b == 0) {
		cout << "Valoarea numitorului este nula\n";
		return *this;
	}
	if(b < 0)
		a = -a, b = -b;
	numarator = a, numitor = b;
	simplifica();
	return *this;
}

Fractie & Fractie::scrie() {
	cout << numarator << " " << numitor << "\n";
	return *this;
}

Fractie suma(Fractie F, Fractie G) {
	//folosim get
	int x = F.Numarator() * G.Numitor() + G.Numarator() * F.Numitor();
	int y = F.Numitor() * G.Numitor();
	Fractie rez;
	//folosim set
	rez.Numarator(x).Numitor(y);
	return rez;
}

Fractie produs(Fractie F, Fractie G) {
	int x = F.numarator * G.numarator;
	int y = F.numitor * G.numitor;
	return Fractie(x, y); //aici se apeleaza constructorul
	//putem afisa si in modul urmator:
	//Fractie rez(x, y);
	//return rez;
}

int Fractie::Numarator() {
	return numarator;
}

int Fractie::Numitor() {
	return numitor;
}

Fractie & Fractie::Numarator(int a) {
	numarator = a;
	simplifica();
	return *this;
}

Fractie & Fractie::Numitor(int b) {
	if(b == 0) {
		cout << "Valoarea numitorului este nula\n";
		return *this;
	}
	numitor = b;
	if(b < 0)
		numarator *= -1, numitor *= -1;
	simplifica();
	return *this;
}

Fractie & Fractie::creste() {
	numarator += numitor;
	return *this;
}

Fractie & Fractie::creste(int n) {
	numarator += n * numitor;
	return *this;
}

Fractie Fractie::operator+(Fractie F) {
	Fractie R;
	R.numarator =  numarator * F.numitor + F.numarator * numitor;
	R.numitor = numitor * F.numitor;
	R.simplifica();
	return R;   
}

Fractie Fractie::operator+(int n) {
	return Fractie(numarator + n * numitor, numitor);
}

Fractie operator+(int n, Fractie F) {
	return Fractie(F.numarator + n * F.numitor, F.numitor);
}

Fractie Fractie::operator-() {
	return Fractie(-numarator, numitor);
}

bool operator<(Fractie F, Fractie G) {
	return F.numarator * G.numitor < G.numarator * F.numitor;
}

bool operator<(Fractie F, int n) {
	return F.numarator < n * F.numitor;
}

bool operator<(int n, Fractie F) {
	return n * F.numitor < F.numarator;
}

Fractie & Fractie::operator=(const Fractie &F) {
	this->numarator = F.numarator;
	this->numitor = F.numitor;
	simplifica();
	return *this;
}

Fractie & Fractie::operator=(const int &n) {
	this->numarator = n;
	this->numitor = 1;
	simplifica();
	return *this;
}

Fractie & Fractie::operator+=(const Fractie &F) {
	this->numarator = numarator * F.numitor + F.numarator * numitor;
	this->numitor = numitor * F.numitor;
	simplifica();
	return *this;
}

Fractie & Fractie::operator+=(const int &n) {
	this->numarator = numarator + n * numitor;
	this->numitor = numitor;
	//simplifica();
	return *this;
}

istream & operator >> (istream & in, Fractie & F) {
    in >> F.numarator >> F.numitor;
    return in;
}

ostream & operator << (ostream & out, Fractie & F) {
	out << F.numarator << "/" << F.numitor;
	return out;
}

Fractie & Fractie::operator ++() {
	numarator += numitor;
	return *this;
}

Fractie Fractie::operator ++(int) {
	Fractie tmp(numarator, numitor);
	numarator += numitor;
	return tmp;
}

//Derivarea claselor

class Animal {
	protected:
		int varsta;
	public:
		Animal();
		~Animal();
		void creste();
		virtual void vorbeste();
};

Animal::Animal() {
	varsta = 0;
	cout << "S-a nascut un animal cu varsta 0\n";
}

Animal::~Animal() {
	cout << "A murit un animal cu varsta " << varsta << "\n";
}

void Animal::creste() {
	varsta ++;
	cout << "Animalul a crescut si are varsta " << varsta << "\n";
}

void Animal::vorbeste() {
	cout << "Animalul vorbeste\n";
}

class Caine: public Animal { //Clasa Caine mosteneste clasa animal
	public:
		Caine();
		~Caine();
		void latra();
		void creste();
		void vorbeste();
};

Caine::Caine() {
	cout << "S-a nascut un caine\n";
}

Caine::~Caine() {
	cout << "A murit un caine cu varsta " << varsta << "\n";
}

void Caine::latra() {
	for(int i = 0; i < varsta; i ++)
		cout << "Ham ";
	cout << "\n";
}

void Caine::creste() {
	varsta ++;
	cout << "Cainele a crescut si are varsta " << varsta << "\n";
}

void Caine::vorbeste() {
	cout << "Cainele latra\n";
}

int main() {
	/*Fractie F(5, 5);
	//F.seteaza(5, 5);
	F.afiseaza();
	Fractie x, y(5), z(2, 10);
	x.afiseaza(),y.afiseaza(), z.afiseaza();
	x.~Fractie(); // apelarea destructorului
	z = y; //apelarea constructorului de copiere
	z.afiseaza();
	afiseaza(z); //apelarea functiei prietene*/
	
	/*Fractie A , B;
    A.citeste(), B.citeste();
    Fractie S = suma(A , B);
    S.scrie();
    produs(A , B).scrie();*/
    
    /*Fractie a , b;
    a.citeste(), b.citeste();
    suma(a , b).scrie();*/
    
    /*Fractie().citeste().scrie(); //cascadare folosind *this
    suma(Fractie().citeste(), Fractie().citeste()).scrie(); //inlantuire in cazul sumei, nu returneaza insusi obiectul, ci un nou obiect*/
    
    /*Fractie x(1 , 4);
    x.afiseaza();
    x.creste();
    x.afiseaza();
    x.creste(3);
    x.afiseaza();*/
    
    /*Fractie X(2 , 2), Y(2, 4);
    Fractie R = X + Y;
    R.afiseaza();
	R = X + 4;
    R.afiseaza();
    R = 4 + X;
    R.afiseaza();*/
    
    /*Fractie X(1 , - 4);
    (-X).afiseaza();*/
    
    /*Fractie X(1 , 4), Y(2, 3);
    cout << (X < Y) << "\n";
    cout << (Y < X) << "\n";
    cout << (X < 2) << "\n";
    cout << (2 < X) << "\n";*/
    
    /*Fractie X(2 , 4), Y(2, 3);
    X += Y;
    X.afiseaza(); // 11/12
    X = Fractie(1 , 4);
    X.afiseaza(); // 1/4
    X += 2;
    X.afiseaza(); // 9/4
    X = Fractie(1 , 4) , Y = Fractie(2 , 3);
    swap(X , Y);
    X.afiseaza(); // 2/3
    Y.afiseaza(); // 1/4
    X = Fractie(1 , 4) , Y = Fractie(2 , 3);
    X = (Y += 1);
    X.afiseaza(); // 5/3
    Y.afiseaza(); // 5/3*/
    
    /*Fractie X;
    cin >> X; // 3 5
    cout << X << endl; // 3/5*/
    
    /*Fractie X , Y;
    Y = Fractie(1 , 2);
    X = Y ++;
    cout << X << " " << Y << endl; // 1/2 3/2
    Y = Fractie(1 , 2);
    X = ++ Y;
    cout << X << " " << Y << endl; // 3/2 3/2*/
    
    //Derivarea claselor
    
    /*Caine X;
    X.creste(); 
    X.Animal::creste();
    X.latra(); 
    X.creste();
    X.latra();*/
    
    /*Caine C;
    Animal A;
    C.vorbeste();
    A.vorbeste();
    C.Animal::vorbeste();
    // A.Caine::vorbeste(); // imposibil*/
    
	/*//pointeri
    Caine C;
	Animal A;
	Animal * p;
	p = & A;
	p->vorbeste(); // Animalul vorbeste.
	p = & C;
	p->vorbeste(); // Animalul vorbeste. (?!?)
	Caine * q;
	q = & C;
	q->vorbeste();
	// q = & A; // imposibil*/
	
	/*Caine C;
    Animal A;
    Animal * p;
    p = & A;
    p->vorbeste(); // Animalul vorbeste.
    p = & C;
    p->vorbeste(); // Cainele latra. (!)*/
}
