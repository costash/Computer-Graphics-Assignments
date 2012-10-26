========EGC - Tema1============================================================

		*Fotbal Static*
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
	Se cere implementarea unui mini-fotball game static. Se doreste folosirea
transformarilor 2d implementate la laborator. Regulamentul jocului este cel
din enuntul temei.

******** 2. Utilizare **********************
	2.1 Consola
		Se ruleaza Tema1.exe

	2.2 Input Tastatura
	Taste:
		r - Reseteaza jocul (scorul si pozitiile jucatorilor respectiv mingii)
		q - Rotire minge in sensul trigonometric atunci cand mingea este
			la un jucator
		e - Rotire minge in sens invers trigonometric, la fel ca mai sus
		space - Lansare minge / pauza
		ESC - Terminare aplicatie
		w - Deplasare jucator in sus
		a - Deplasare jucator la stanga
		s - Deplasare jucator in jos
		d - Deplasare jucator la dreapta

******** 3. Implementare *******************
	Platforma: Windows 7 x64 SP1, Visual Studio 2012
	Biblioteci auxiliare: FreeGlut - din framework-ul de la laborator

	3.1 Schema Generala
		* deschidere aplicatie
		* executare joc folosind Inputul de la Tastatura
		* terminare aplicatie

	3.2 Diagrama Clase
	+--Object2d+----+Circle2d+--------+Ball-+
             |
             +----+Rectangle2d

	3.3 Evenimente
		Display - Reafisare obiecte in fereastra
		Reshape - Redimensionare fereastra
		Idle - Logica animatiilor
		Keyboard - Tasta apasata

******** 4. Testare ************************
	Platforma: Aceeasi ca cea de implementare
	
	Am testat functionalitatile de baza ale jocului (sut minge, pauza, afisare
scor corect, resetare joc, coliziuni).
	De asemeni, am testat afisarea corecta a obiectelor ce compun harta de joc.

******** 5. Probleme aparute ***************
	Cel mai dificil de implementat au fost coliziunile, in special coliziunile
dintre jucatori si minge.
	Am incercat sa implementez coliziunea prin testarea cadrului curent din
animatie, insa aceasta a generat un bug, si anume ca mingea intra putin in
jucator si apoi pentru a suta din nou, fiind nevoie de doua suturi, si nu unul.
	O alta problema, cauzata de cea anterioara, este ca atunci cand un jucator
este aproape de un perete si are mingea "in el", sutand de 2 ori, face ca
mingea sa intre in perete si sa nu poata fi recuperata. Un workaround a fost sa
interzic playerilor sa se apropie de pereti la mai putin de o distanta fixata.

******** 6. Continutul arhivei *************
	**** Fisiere generate de solutia Visual Studio 2012
	**** Fisiere ce definesc tema
	* main.cpp
		Sursa principala a aplicatiei
	* Circle2d.cpp
		Implementare a clasei ce defineste un cerc
	* Circle2d.h
		Header pentru declaratia clasei Circle2d
	* Rectangle2d.cpp
		Implementare a clasei ce defineste un dreptunghi
	* Rectangle2d.h
		Header pentru declaratia clasei Rectangle2d
	* Ball.cpp
		Implementare a clasei ce defineste mingea
	* Ball.h
		Header pentru declaratia clasei Ball
	* README.txt
		Acest fisier
	**** Alte fisiere din cadrul framework-ului de la laborator

******** 7. Functionalitati ****************
	* Functionalitati standard (ca in enunt)
		* Plasare harta joc
		* Forma terenului
		* Forma jucatori, minge
		* Rotire jucatori(cu mingea)
		* Propulsare minge
		* Reprezentare scor
		* Inversare culori de 2 ori la terminarea unui joc
	* Functionalitati bonus
		* Mutare jucator care se afla la minge
	* Alte functionalitati
		* Inversare culoare de 2 ori a mingii la gol