### Oświetlenie



#### Oświetlenie dyfuzyjne 

Proszę dodać do poprzednich modeli oświetlenie  punktowe dyfuzyjne za pomocą cieniowanie Gourauda, 
czyli  przez wykonywanie obliczeń w szaderze wierzchołków. W tym celu należy wszystkie wektory 
przetransformować do współrzędnych/układu kamery/oka. 

Potrzebne będą w tym celu normalne dla każdego wierzchołka.
W przypadku trójkata normalną można obliczyć jako iloczyn wektorowy (cross) dwu wektorów krawędzi.
Po obliczeniu iloczyny wektor należy znormalizować.  


Kolor powierzchni ma być brany z tekstury. 