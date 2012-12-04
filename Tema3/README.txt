========EGC - Tema3============================================================

		*Labyrinth*
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
	Se cere implementarea unui joc numit Labyrinth. In acest joc
personajul principal se deplaseaza intr-un labirint pentru a gasi
portalul de scapare. El se poate deplasa in fata/spate, stanga/dreapta,
respectiv roti.

******** 2. Utilizare **********************
	2.1 Consola
		Se ruleaza Tema3.exe

	2.2 Input Tastatura
	Taste de baza:
		ESC 	- Terminare aplicatie
		r		- Resetare joc la starea initiala
		1		- Selectare camera mod FPS
		2		- Selectare camera mod TPS
		3		- Selectare camera mod TOP

	Taste functionale rotire cub:
		UP		- Rotire camera in sus
		DOWN	- Rotire camera in jos
		LEFT	- Rotire camera la stanga
		RIGHT	- Rotire camera la dreapta

	Taste functionale deplasare:
		w		- Deplasare inainte
		s		- Deplasare inapoi
		a		- Deplasare la stanga
		d		- Deplasare la dreapta

	Taste functionale departare/apropiere in mod TPS/TOP
		[		- Apropiere camera
		]		- Departare camera

	2.3 Input Mouse
	Mouse left clicked: in mod FPS/TPS
		Miscare stanga	- Rotire camera la stanga
		Miscare dreapta - Rotire camera la dreapta
		Miscare sus		- Rotire camera in sus
		Miscare jos		- Rotire camera in jos

	Mouse scroll/wheel: in mod TPS/TOP
		Miscare sus		- Apropiere camera
		Miscare jos		- Departare camera

******** 3. Implementare *******************
	Platforma: Windows 7 x64 SP1, Visual Studio 2012
	Biblioteci auxiliare: FreeGlut - din framework-ul de la laborator

	3.1 Schema Generala
		* deschidere aplicatie
		* executare joc folosind Inputul de la Tastatura si Mouse
		* terminare aplicatie

	3.2 Diagrama Clase
	+--WorldDrawer--+
	+--Point2d--+
    +--Vector3d--+
	+--Labyrinth--+
	+--Camera--+

	3.3 Evenimente
		Display - Reafisare obiecte in fereastra
		Reshape - Redimensionare fereastra
		Idle - Logica animatiilor
		Keyboard - Tasta apasata
		Mouse - Mouse click sau miscare mouse

******** 4. Testare ************************
	Platforma: Aceeasi ca si cea de implementare
	
	Am testat functionalitatile de baza ale jocului (rotiri ale camerei, deplasare,
coliziune cu peretii, generare labirint, zoom, resetare joc etc).
	De asemeni, am testat afisarea corecta a obiectelor ce compun harta de joc.

******** 5. Probleme aparute ***************
	Au fost mici probleme cu coliziunile, in sensul ca am gasit greu balansul dimensiunilor
jucatorului/zidurilor pentru a fi sigur ca nu trece prin zid jucatorul.

******** 6. Continutul arhivei *************
	**** Fisiere generate de solutia Visual Studio 2012
	**** Fisiere ce definesc tema
	* Main.cpp
		Sursa principala a aplicatiei
	* camera.cpp
		Implementare a clasei de camera
	* camera.h
		Header pentru clase de camera
	* ground.h
		Header pentru desenarea ground-ului
	* HeadersAndDefines.h
		Header pentru diverse constante si define-uri
	* Labyrinth.h
		Header pentru clasa ce tine un maze
	* Labyrinth.cpp
		Implementare a clasei ce tine un maze
	* Point2d.h
		Header pentru clasa ce defineste un punct (x, y)
	* Point2d.cpp
		Implementare a clasei ce defineste un punct
	* Vector3D.h
		Header pentru clasa ce defineste un vector 3d
	* Vector3D.cpp
		Implementare pentru clasa vector
	* WorldDrawer.h
		Header pentru clasa ce tine informatii de afisare si logica jocului
	* WorldDrawer.cpp
		Implementare pentru clasa ce tine informatii de afisare
	* README.txt
		Acest fisier
	**** Alte fisiere din cadrul framework-ului de la laborator

******** 7. Functionalitati ****************
	* Functionalitati standard (ca in enunt)
		* Plasare harta joc
		* Afisare labirint
		* Afisare player in modurile TPS si TOP
		* Rotirea camerei cu jucatorul
		* Deplasarea camerei cu jucatorul
		* Afisare torus (portal)
		* Posibilitate resetare joc
	* Functionalitati bonus
		* Labirint generat random, automat
		* Labirintul se modifica la fiecare rulare
		* Afisare text cu scor sau mesaj de incepere joc
		* Posibilitate redimensionare labirint din taste