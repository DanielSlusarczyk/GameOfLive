Języki i Metody Programowania 2 - Projekt 1
Jakub Łaba i Daniel Ślusarczyk

CEL PROJEKTU
Program emuluje działanie automatu komórkowego Johna Conwaya - Grę w Życie (ang. "The Game of Life").
Na prostokątnej planszy mamy komórki żywe (zazwyczaj oznaczane kolorem czarnym) oraz martwe (zazwyczaj oznaczane kolorem białym, lub brakiem koloru).
"Życie" na planszy toczy się przez określoną liczbę generacji, które są rozdzielone dyskretnymi odstępami czasowymi.
W każdej generacji komórki ożywają/obumierają na następujących zasadach:
Komórki żywe - pozostają żywe w kolejnej generacji jeżeli posiadają dokładnie 2 lub 3 żywych sąsiadów, w każdym innym przypadku umierają
Komórki martwe - ożywają w kolejnej generacji jeżeli posiadają dokładnie trzech żywych sąsiadów, w przeciwnym przypadku pozostają martwe

DANE WEJŚCIOWE:
Program potrzebuje danych z informacjami o stanie wyjściowej planszy (generacji 0),
oraz o liczbie generacji, którą użytkownik chce wygenerować.
Plik wejściowy powinien zawierać pojedynczy ciąg znaków, sformatowany w następujący sposób:
<liczba wierszy><liczba kolumn><zawartość kolejnych wierszy planszy>
Gdzie żywe komórki oznaczone są jako '1', natomiast martwe jako '0'.

Przykładowo, jeżeli chcemy wczytać planszę 2x3 z jedną żywą komórką w lewym górnym rogu, oraz jedną w prawym dolnym rogu,
plik powinien zawierać ciąg znaków "23100001"

ARGUMENTY WYWOŁANIA PROGRAMU:
Program wywołujemy w następujący sposób:
./<plik wykonywalny> <plik wejściowy> <liczba generacji>
plik wejściowy - ścieżka do pliku z informacjami o stanie planszy wyjściowej
liczba generacji - liczba naturalna >= 1, określająca pożądaną przez użytkownika liczbę generacji
Ponadto, można wywołać program z parametrem "-sts", przekazywanym zawsze jako pierwszy argument,
w celu uruchomienia go w trybie "step by step" - tj. program będzie czekał na naciśnięcie klawisza przez użytkownika po każdej generacji.