##  Pierwsze  kroki w  WebGL


### Wprowadzenie 

Proszę  sciągnąć i wyświetlić  plik [webgl_start.html](https://sorbus.if.uj.edu.pl/pbialas/3DGraphicsProgrammingTutorials/blob/master/WebGL/webgl_start.html).
Prosze zapoznać się z zamieszczonym w nim kodem.
 
 
Proszę   się  "pobawić" zmienić kształt trójkata oraz narysować dodatkowe trójkaty. 

### Sześciokat

Proszę narysować  sześciokat. 


### Przekształcenia

Korzystając z biblioteki   glMatrix.js do pobrania [tutaj](https://sorbus.if.uj.edu.pl/pbialas/3DGraphicsProgrammingTutorials/blob/master/WebGL/gl-matrix-min.js) proszę dokonać przesunięcia sześciokata. 
Opis biblioteki można znaleźć [tutaj](http://glmatrix.net/docs/2.2.0/index.html)
W tym celu należy

1. Zmodyfikować kod szadera wierzchołków tak, aby  wejściowe współrzędne były przemnażane przez macierz przekształceń. 
   Macierz `uM` ma być zmienna typu uniform. 
   
````
gl_Position  = uM*aVertexPosition;
````
   
2. Poleceniem `gl.getUniformLocation(shader, name)` pobrać adres zmiennej uniform w  pogramie shadera.

3. Stworzyć macierz translacji

```` 
var I=mat4.create();
mat4.identity(I);   
var M = mat4.create();
mat4.translate(M, I, [0.0, 0.5,0]);
````

4. Za pomocą polecenia `gl.uniformMatrix4fv(location,false , M )` przekazać macierz do szadera. 


### Model View Projection


Zamiast macieryz translacji z poprzedniego ćwiczenia, proszę postawić macierz `P*V*M` gdzie

1. Macierz `P` otrzymuje się za pomoca  polecenia  `mat4.perspective(P,fov, aspect, near, far)`.
2. Macierz `V` otrzymuje się za pomocą  polecenia  `mat4.lookAt(P,eye,center,up)`.
3. `M` jest dowolna macierzą transformacji modelu. 