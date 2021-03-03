Języki i Metody Programowania 2 - Projekt 1
Jakub Łaba i Daniel Ślusarczyk

Dokument ten stanowi opis szczegółowy projektu cyfrowego "The Game of Life" oraz związany z nim zakres prac, funkcje programu, interakcje zachodzące między system
a użytkownikiem i instrukcje prawidłowego użytkowania.

CEL PROJEKTU
Program emuluje działanie automatu komórkowego Johna Conwaya - Grę w Życie (ang. "The Game of Life").
Na prostokątnej planszy znajdują się komórki żywe (zazwyczaj oznaczane kolorem czarnym) oraz martwe (zazwyczaj oznaczane kolorem białym, lub brakiem koloru).
"Życie" na planszy toczy się przez określoną liczbę generacji, które są rozdzielone dyskretnymi odstępami czasowymi.
W każdej generacji komórki ożywają/obumierają na następujących zasadach:
Komórki żywe - pozostają żywe w kolejnej generacji jeżeli posiadają dokładnie 2 lub 3 żywych sąsiadów, w każdym innym przypadku umierają
Komórki martwe - ożywają w kolejnej generacji jeżeli posiadają dokładnie trzech żywych sąsiadów, w przeciwnym przypadku pozostają martwe
Komórki znadujące się poza planszą są uznawane za martwe.

DANE WEJŚCIOWE:
Program potrzebuje danych z informacjami o stanie wyjściowej planszy (generacji 0),
oraz o liczbie generacji, którą użytkownik chce wygenerować.
Plik wejściowy powinien zawierać trzy linie, sformatowane następująco:
1 <row> <col>
2 <x1> <x2> ... <xn>
3 <y1> <y2> ... <yn>
Gdzie:
row - liczba rzędów planszy
col - liczba kolumn planszy
x1, x2, ..., xn - współrzędne x-owe kolejnych żywych komórek
y1, y2, ..., yn - współrzędne y-owe kolejnych żywych komórek
(x1, y1) są współrzędnymi pierwszej żywej komórki, (x2, y2) - drugiej, itd.
Współrzędne określamy względem klasycznego 2-wymiarowego kartezjańskiego układu współrzędnych.

Przykładowo, jeżeli chcemy wczytać planszę 2x3 z jedną żywą komórką w lewym górnym rogu, oraz jedną w prawym dolnym rogu,
plik powinien wyglądać w następujący sposób:
1 2 3
2 1 3
3 2 1

ARGUMENTY WYWOŁANIA PROGRAMU:
Niezbędne do uruchomienia programu:
./TGOL <plik wejściowy> <liczba generacji> <plik wyjściowy>
plik wejściowy - ścieżka do pliku z informacjami o stanie planszy wyjściowej
liczba generacji - liczba naturalna >= 1, określająca pożądaną przez użytkownika liczbę generacji

Dodatkowe:
Ponadto, można wywołać program z parametrem "-sbs", przekazywanym zawsze jako pierwszy argument,
w celu uruchomienia go w trybie "step by step" - tj. program będzie czekał na naciśnięcie klawisza przez użytkownika po każdej generacji.

URUCHOMIENIE PROGRAMU:
Program został przygotowany do uruchomienia w systemie Linux (zalecana dystrybucja: Ubuntu 20.04).
Uruchomienia programu odbywa się poprzez wpisanie niezbędnych arugumentów wywołania programu w terminalu systemu Linux: ./TGOL <plik wejściowy> <liczba generacji> <plik wyjściowy>

Przykład
Znajdując się w folderze projektu i mając odpowiednio przygotowany plik wejściowy (zgodnie z punktem dane wejściowe) pod nazwą "dane1" w folderze "generacje" i chcąc przeprowadzić 10 generacji
oraz zapisać wynik w pliku "wynik" powinniśmy wpisać następujące polecenie:
./TGOL generacje/dane1 10 wynik

WYNIK DZIAŁANIA PROGRAMU:
Wynikiem działania programu jest przeanalizowanie przez program wszystkich następujących generacji i wyświetlenie finalnej (zadeklarowanej w argumencie <liczba generacji>) w oknie terminala.
Jeśli program został uruchomiony w trybie "step by step" to wynikiem działania pierwszego etapu będzie wyświetlenie kolejnej zachodzącej generacji i oczekiwania na kolejne komendy.
Po osiągnięciu finalnej generacji w obu przypadkach program kończy działanie, a wszystkie przeanalizowane generacje zostają zapisane w pliku podanym przez użytkownika w formacie zgodnym
z danymi wejściowymi programu oraz jpg.

SCENARIUSZ DZIAŁANIA PROGRAMU:
	Tryb podstawowy:
		Wywołanie:
		./TGOL <plik wejściowy> <liczba generacji> <plik wyjściowy>
		Wynik:
		Przeprowadzenie przez program wszystkich generacji. Zapisanie je do <plik wyjściowy>. Wyświetlenie informacji o ostatniej generacji w oknie terminala.

	Tryb step by step:
		Wywołanie:
		./TGOL <plik wejściowy> <liczba generacji> <plik wyjściowy> -sbs
		Wynik:
		Przeprowadzenie przez program pierwszej generacji. Wyświetlenie informacji na jej temat w oknie terminala. Czekanie na instrukcje od użytkownika.
		Możliwe kroki:
		a) Wpisanie polecenia "n"
		Wynik:
		Przeprowadzenie przez program kolejnej generacji. Wyświetlenie informacji na jej temat w oknie terminala. Czekanie na instrukcje od użytkownika.
		b) Wpisanie polecenia "continue"
		Wyłączenie przez program trybu step by step. Przeprowadzenie przez program wszystkich pozostałych generacji. 
		Zapisanie je do <plik wyjściowy>. Wyświetlenie informacji o ostatniej generacji w oknie terminala.
		c) Wpisanie polecenia "out"
		Wynik:
		Zakończenie działania programu.
		
ROZSZERZONY SCENARIUSZ DZIAŁANIA PROGRAMU - ZAPIS BŁĘDÓW:
	Tryb podstawowy:
		- Wywołanie z niewłaściwymi argumentami:
		  Możliwe wyniki kończące działanie programu:
			(Komunikat programu)		|Brak lub błędny format pliku wejściowego/problem z otworzeniem
			(Komunikat programu) 		|Brak lub błędny format liczby generacji 
			(Komunikat programu) 		|Brak lub błędny format pliku wyjściowego/problem z otworzeniem
			(Komunikat programu)		|Błąd w działaniu programu
			(Komunikat programu)		|Zbyt duża żądana ilość generacji
	Tryb step by step:
		-Wywołanie z niewłaściwymi argumentami:
		 Możliwe wyniki kończące działanie programu:
			(Komunikat programu)		|Brak lub błędny format pliku wejściowego/problem z otworzeniem
			(Komunikat programu) 		|Brak lub błędny format liczby generacji 
			(Komunikat programu) 		|Brak lub błędny format pliku wyjściowego/problem z otworzeniem
			(Komunikat programu)		|Błąd w działaniu programu
			(Komunikat programu)		|Zbyt duża żądana ilość generacji
		 Możliwe wyniki kontuujące działanie programu:
			(Komunikat programu)		|Wpisano złe polecenie. Program kontynuuje czekanie na polecenie

		







