### Dalsze kroki w WebGL

#### Graphics Primitives

Proszę wybróbować działanie innych graficznych elemntów. W tym celu należy w funkcji `drawArrays` zamienić pierwszy argument 
na jeden z 

-   gl.POINTS
-   gl.LINES
-   gl.LINE_STRIP
-   gl.LINE_LOOP
-   gl.TRIANGLE_STRIP
-   gl.TRIANGLE_FAN

#### Color i inne atrybuty 

Proszę  pokolorować trójkaty. W tym celu należy :

-  Dodać nowy atrybut `aVertecColor` typu `vec4` do szadera wierzchołków. Ten atrybut będzie zawierał color wierzchołka 
w formacie RGBA.
- Dodać zmienna `vVertexColor` typu `varying`  do szadear wierzchołków która posłuży do przekazania koloru do szadera 
fragmentów.

````
attribute vec4 aVertexPosition;
attribute vec4 aVertexColor;
varying vec4 vVertexColor;

uniform mat4 uM;

void main(void) {
    vVertexColor=aVertexColor;
    gl_Position=uM*aVertexPosition;
}
````



- Dodać taką samą zmienną do szadera fragmentów i przypisac ją do  zmiennej systemowej  `gl_FragColor`.

````
precision mediump float;
varying vec4 vVertexColor;

void main(void) {
    gl_FragColor = vVertexColor;
}
````

- W funkcji `onLoad` 
    - w funkcji `initShaders` dodać drugi atrybut
        ```` 
        initShaders(gl, ['aVertexPosition', 'aVertexColor']);
        ````
    - zainicjalizować bufor kolorów    
        ````
        var colorBuffer = initBuffer(gl,4,1,VertexColors);
        gl.colorBuffer = colorBuffer;
        ````
        gdzie `VertexColors` nazwa zmiennej przechowywującej kolory po kolei cztery wartości dla każdego wierzchołka. 
        ````
        gl.enableVertexAttribArray(gl.shaderProgram.attribute['aVertexColor']);
        ````
-   w funkcji `draw` "powiedzieć" enginowi skad ma brać kolory
    ````
    gl.bindBuffer(gl.ARRAY_BUFFER, gl.colorBuffer);
    gl.vertexAttribPointer(gl.shaderProgram.attribute['aVertexColor'],4,gl.FLOAT, false,0,0);
    ````
         