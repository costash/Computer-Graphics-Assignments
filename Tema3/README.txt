========EGC - Tema2============================================================

		*Rubik*
		*Serban-Radoi Constantin 333CA*

******** Cuprins ***************************
	1. Cerinta
	2. Utilizare
	3. Implementare
	4. Testare
	5. Probleme Aparute
	6. Continutul Arhivei
	7. Functionalitati

******** 1. Cerinta ************************
	Se cere implementarea unui joc ce permite rezolvarea cubului lui Rubik.
Functionalitatile de baza presupun rotirea cubului si a layerelor acestuia.
Se porneste de la un cub rezolvat, utilizatorul face mai multe rotiri, si
din momentul in care a apasat o tasta incepe jocul si counter-ul pentru
numarul de rotiri. Daca a ajuns la o solutie, se afiseaza faptul ca a castigat.
Oricand poate reseta jocul.

******** 2. Utilizare **********************
	2.1 Consola
		Se ruleaza Tema2.exe

	2.2 Input Tastatura
	Taste de baza:
		Space 	- Pauza
		ESC 	- Terminare aplicatie
		1		- Resetare joc la starea initiala
		ENTER	- Incepere joc si numaratoare mutari

	Taste functionale rotire straturi:
		q 		- Rotire strat selectat in sens trigonometric pe OX
		a		- Rotire strat selectat in sens invers trig pe OX
		w		- Rotire strat selectat in sens trigonometric pe OY
		s		- Rotire strat selectat in sens invers trig pe OY
		e		- Rotire strat selectat in sens trigonometric pe OZ
		d		- Rotire strat selectat in sens invers trig pe OZ

	Taste functionale selectie straturi:
		t		- Creste indicele stratului selectat pe OX
		g		- Scade indicele stratului selectat pe OX
		y		- Creste indicele stratului selectat pe OY
		h		- Scade indicele stratului selectat pe OY
		u		- Creste indicele stratului selectat pe OZ
		j		- Scade indicele stratului selectat pe OZ

	Taste functionale rotire cub:
		UP		- Rotire cub in sus
		DOWN	- Rotire cub in jos
		LEFT	- Rotire cub la stanga
		RIGHT	- Rotire cub la dreapta

	Taste functionale marire/micsorare cub
		[		- Marire cub
		]		- Micsorare cub

	2.3 Input Mouse
	Mouse left clicked:
		Miscare stanga	- Rotire cub la stanga
		Miscare dreapta - Rotire cub la dreapta
		Miscare sus		- Rotire cub in sus
		Miscare jos		- Rotire cub in jos

	Mouse right clicked:
		Miscare sus		- Micsorare cub
		Miscare jos		- Marire cub

	Mouse scroll/wheel:
		Miscare sus		- Marire cub
		Miscare jos		- Micsorare cub

******** 3. Implementare *******************
	Platforma: Windows 7 x64 SP1, Visual Studio 2012
	Biblioteci auxiliare: FreeGlut - din framework-ul de la laborator

	3.1 Schema Generala
		* deschidere aplicatie
		* executare joc folosind Inputul de la Tastatura si Mouse
		* terminare aplicatie

	3.2 Diagrama Clase
	+--WorldDrawer3d--+
	+--Point3d--+
	+--CoordinateSystem3d--+
	+--Object3d+----+Cube
    +--Rubik--+
	+--Color--+

	3.3 Evenimente
		Display - Reafisare obiecte in fereastra
		Reshape - Redimensionare fereastra
		Idle - Logica animatiilor
		Keyboard - Tasta apasata
		Mouse - Mouse click sau miscare mouse

******** 4. Testare ************************
	Platforma: Aceeasi ca si cea de implementare
	
	Am testat functionalitatile de baza ale jocului (rotiri ale cubului, rotiri
ale axelor, afisare scor, resetare etc).
	De asemeni, am testat afisarea corecta a obiectelor ce compun harta de joc.

******** 5. Probleme aparute ***************
	Nu a fost clar in enunt modul de rotire al cubului. Am ales sa rotesc toata
lumea, desenand dupa rotire, pastrand mereu aceeasi pozitie relativa a axelor.
	Cel mai dificil de implementat au fost rotirile straturilor cubului,
datorita necesitatii de a roti linii/coloane/a_treia_dimensiune dintr-o
matrice tridimensionala liniarizata.
	Am incercat sa creez ferestre folosind framework-ul glut, dar nu am reusit
sa afisez nimic in acele ferestre, de aceea am renuntat la ele. Mai mult,
callback-urile din prima fereastra continuau sa se execute dupa crearea unei
noi ferestre, si de exemplu daca aveam apasata tasta 'q' cand se crea noua
fereastra, tasta q ramanea apasata, pana cand ma intorceam in fereastra
initiala. Acest lucru m-a determinat sa renunt la lucrul cu ferestre pentru
aceasta tema.
	Am avut probleme cu evenimentele de tastatura, deoarece am implementat
key buffering pentru a putea apasa mai multe taste simultan, si din cauza
acestui lucru, daca doream sa selectez un strat sa zicem, evenimentul de
apasare era inregistrat de prea multe ori, si a fost nevoie sa pun un timer,
care sa limiteze trigger-uirea acestui eveniment.

******** 6. Continutul arhivei *************
	**** Fisiere generate de solutia Visual Studio 2012
	**** Fisiere ce definesc tema
	* main.cpp
		Sursa principala a aplicatiei
	* Color.cpp
		Implementare a clasei o culoare RGB
	* Color.h
		Header pentru declaratia clasei Color
	* Cube.cpp
		Implementare a clasei ce defineste un un cub si operatiile sale
	* Cube.h
		Header pentru declaratia clasei Cube
	* Rubik.cpp
		Implementare a clasei ce defineste cubul Rubik
	* Rubik.h
		Header pentru declaratia clasei Rubik
	* README.txt
		Acest fisier
	**** Alte fisiere din cadrul framework-ului de la laborator

******** 7. Functionalitati ****************
	* Functionalitati standard (ca in enunt)
		* Plasare harta joc
		* Afisare cub rezolvat
		* Forma si culorile cubului
		* Rotirea cubului
		* Rotirea straturilor cubului
		* Afisare scor la castig
		* Posibilitate resetare joc
	* Functionalitati bonus
		* Cub extensibil (chiar si 15 x 15 x 15)
		* Afisare text cu scor sau mesaj de incepere joc
		* Scorul este reprezentat de numarul de mutari executate
		* Afisare text in cazul castigului