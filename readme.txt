Języki i Metody Programowania 2 - Projekt 1
Jakub Łaba i Daniel Ślusarczyk

CEL PROJEKTU
Program emuluje działanie automatu komórkowego Johna Conwaya - Grę w Życie (ang. "The Game of Life").
Na prostokątnej planszy znajdują się komórki żywe (zazwyczaj oznaczane kolorem czarnym) oraz martwe (zazwyczaj oznaczane kolorem białym, lub brakiem koloru).
"Życie" na planszy toczy się przez określoną liczbę generacji, które są rozdzielone dyskretnymi odstępami czasowymi.
W każdej generacji komórki ożywają/obumierają na następujących zasadach:
Komórki żywe - pozostają żywe w kolejnej generacji jeżeli posiadają dokładnie 2 lub 3 żywych sąsiadów, w każdym innym przypadku umierają
Komórki martwe - ożywają w kolejnej generacji jeżeli posiadają dokładnie trzech żywych sąsiadów, w przeciwnym przypadku pozostają martwe

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
(x1, y1) są współrzędnymi pierwszej żywej komórki, (x2, y2) - drugiej, (xn, yn) - n-tej, itd.
Współrzędne określa się względem klasycznego 2-wymiarowego kartezjańskiego układu współrzędnych.

ARGUMENTY WYWOŁANIA PROGRAMU:
Program należy wywołać w następujący sposób:
./<plik wykonywalny> <plik wejściowy> <liczba generacji>
plik wykonywalny - ścieżka do pliku wykonywalnego, do którego program został skompilowany
plik wejściowy - ścieżka do pliku z informacjami o stanie planszy wyjściowej
liczba generacji - liczba naturalna >= 1, określająca pożądaną przez użytkownika liczbę generacji
Ponadto, program można wywoływać z flagami:
"-sts" - tryb "step by step", tzn. program będzie pokazywał wszystkie generacje, czekając na wciśnięcie przycisku przed przejściem do każdej następnej generacji
"-save" - jeżeli wywołamy program z tą flagą, ostatnia generacja zostanie zapisana do pliku wynikowego, sformatowanego identycznie jak plik wejściowy (dzięki temu można użyć pliku wynikowego jako wejścia do kolejnego uruchomienia programu)
Przy wywołaniu programu z flagą "-save" należy od razu po niej podać nazwę pliku wynikowego.
"-ovw" - skrót od "overwrite", przy wywołaniu z tą flagą, ostatnia generacja zostanie nadpisana w pliku podanym jako wejściowy
Flagi należy umieścić jako ostatnie argumenty wywołania

SCENARIUSZE DZIAŁANIA:
Jeżeli program zostanie uruchomiony poprawnie, z poprawnie sformatowanym plikiem wejściowym, wyświetli on stan ostatniej zadanej generacji.
W przypadku poprawnego uruchomienia z odpowiednimi flagami, mogą zostać pokazane wszystkie kolejne generacje, oraz końcowa generacja może poza wyświetleniem zostać zapisana do odpowiedniego pliku.
Gdy zostaną użyte flagi, program wyświetli informację o ich uruchomieniu (np. "Uruchomiono w trybie step by step").
W przypadkach niepoprawnego uruchomienia programu, zwracane są odpowiednie kody błędów:
1: INCORRECT_NUMBER_OF_ARGS - niepoprawna ilość argumentów uruchomienia programu
2: INCORRECT_ARGS - poprawna ilość, ale jeden lub więcej typów argumentów wywołania jest niewłaściwa, lub zostały umieszczone w niewłaściwej kolejności
3: UNKNOWN_FLAG - użycie nieznanej flagi
4: INPUT_ERR - nie można otworzyć podanego pliku wejściowego
5: INCORRECT_GENS - niewłaściwa liczba generacji
6: INPUT_NOT_NMBR - w pliku wejściowym znajdują się wartości niebędące liczbami naturalnymi
7: INPUT_SHORT - w pliku wejściowym znajduje się za mało danych określających wymiary planszy
8: INPUT_XY - w pliku wejściowym liczba współrzędnych x-owych jest niezgodna z liczbą współrzędnych y-owych
9: NO_OUT - wywołano z flagą "-save", ale nie podano nazwy pliku wynikowego
10: FILENAME_TAKEN- wywołano z flagą "-save" i podano nazwę pliku wynikowego, ale w danej lokalizacji już istnieje plik o tej nazwie