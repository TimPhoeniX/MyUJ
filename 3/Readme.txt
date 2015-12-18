Program demonstruje optymalizację rekurencji ogonowej.
Zalecane jest użycie GCC na systemie Linux 64-bit (Domyślny rozmiar stosu - 8192KB) (Testowane na Debian 8.2)
Program rekurencyjnie liczy sumę jedynek 4 raz - rekurencja ogonowa i zwykła, a także rekurencja ogonowa i zwykła dla zwiększonej liczby wywołań.
Poziom O1 optymalizacji daje podobne czasy wykonania dla rekurencji zwykłej i ogonowej a także przepełnia stos dla zwiększonej liczby.
Poziom 02 daje optymalizację wywołania rekurencji ogonowej co daje krótszy czas liczenia sumy. Dla zwiękosznej liczby rekurencja ogonowa dochodzi do końca.
