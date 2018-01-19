# JavaScript and canvas 2d graphics

To ćwiczenie ma za zadanie zaznajomić Państwa  z  językiem JavaScript oraz elementem HTML5 `<canvas>`.


## Gitlab

Na początek proszą wszystkich Pańswta o założenie sobie konta na [Gitlabie](https://sorbus.if.uj.edu.pl), a następnie
stworzenie w nim projektu o nazwie Canvas2D.

Jeżeli na pracowni będzie klient git-a :( to proszę sklonować projekt. 


## Prostokąt

Zaczynając od [pliku](canvas2d.html)  prosze narysować prostokat o wysokości 100 i 200 szerokości na środku canvasu.
W tym celu należy najpierw  w funkcji `load()` pobrać referencję do elementu `canvas` za pomocą polecenia
`document.getElementById()`,
a następnię popbrać z niej kontekst graficzny poleceniem `getContext("2d")`;
 
```javascript
var canvas =  document.getElementById("canvas");
var ctx    = canvas.getContex("2d");
```

Otrzymany obiekt kontekstu `ctx` zawiera metody służące do rysowania na canvasie.
W szczególności  prostokat rysujemy poleceniem `ctx.strokeRect(x,y,w,h)`, a wypełniamy go poleceniem
`ctx.fillRect(x,y,w,h)`, gdzie `x` i `y` to współrzedne lewego górnego rogu, a `w` i `h` to odpowiednio szerokość i wysokość.
Do ustalenia koloru lini i wypełnienia służa polecenia `ctx.fillStyle` oraz `ctx.strokeStyle` :
```javascript
ctx.fillStyle="#ff000"; //red
ctx.strokeStyle="#000000" //black
```
Całe API graficzne elementu canvas jest opisane n.p. [tutaj](https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D).

## Scieżki

W celu narysowania bardziej skomplikowanych kształtów  musimy posłużyć się *ścieżkami* (paths).
Tworzenie ścieżki zaczynamy poleceniem 
```javascript
ctx.beginPath();
``` 
Następnie możemy dodawać do ścieżki różne elementy. Polecenie 
```javascript
ctx.moveTo(x,y)
```
przesuwa pióro *bez rysowania* do punktu `(x,y)`, polecenie
```
ctx.lineTo(x,y)
```
przesuwa pióro *rysując* linię  do punktu `(x,y)`, polecenie
```
ctx.closePath()
```
przesuwa piórko rysując linię do początkowego punktu ścieżki.   Żadne z tych poleceń tak naprawdę nieczego nie rysuje. Dopiero polecenie 
```
ctx.stroke();
``` 
rysuje bieżącą ścieżkę, a polecenie
```javascript
ctx.fill();
``` 
wypełnia ścieżkę kolorem domykając ją jesli trzeba. Pierwsze polecenie wydane na ścieżce zawsze powoduje samo
przesunięcie pióra bez rysowania niezależnie czy jest to `moveTo` czy `lineTo`. 
 
Korzystając z tych poleceń proszę napisać funkcje :
```
function polygon(ctx, x, y , r, n)
```
która za pomocą kontekstu `ctx` rysuje wielokąt foremny o `n` ścianach, środku w punkcie `(x,y)` i promieniu `r`.

  
 
### Wskazowka

Można skorzystać z pętli 
```javascript
for(var i=0;i<n;i++) {
}
```
Funkcje matematyczne zawarte są w obiekcie `Math`:
 
```javascript
Math.sin();
Math.cos();
Math.PI
```
 
 
## Gwiazdki

Proszę napisać funkcję  
```javascript
function doodle(ctx, x, y , r, n,k)
```
którą  rysuje wielokąt powstały w nstaepujący sposób: jeśli ponumerujemy wierzchołki n-kąta foremnego o środku `(x,y)` 
i promieniu `r`
0, 1, ..., n-1,  to `doodle` rysuje wielokąt powstały poprzez narysowanie  lini  łamanej przez wierzchołki
0,(k-1)%n, (2k-1)%n, (3k-1)%n, ... , 0. Operacja `j%n` oznacza resztę dzielenia `j` przez `n`. 

### Wskazówka

Ponieważ liczba iteracji nie jest znana można skorzystać z petli 
```javascript
while(warunek) {
    
}
``` 

Wierzchołki wielokąta moża przechowywać w tablicy (array)
```javascript
var v = [];
for(var i=0;i<n;i++) {
    var p = {};
    p.x = ...
    p.y = ...
    v[i]=p;
}
```
 
 
Za pomocą tych dwu funkcji proszę narysować  na środku canvasu pentagram wpisany w pięciokąt o promieniu 100:)
  
  
## Transformacje

API 2D umożliwia również zdefiniowanie *przekształceń* którym będą poddawane wszystkię punkty. Transformacje sa składane.
Polecenia
```
ctx.translate(x,y);
```
Dodaje transformacje przesunięcia o  wektor `(x,y)`, a polecenie
```
ctx.rotate(angle)
```
dokonuje obrotu o kąt `angle` (w radianach) wokół środka układu współrzednych.

**Uwaga** przekształcenia są  składane w odwroten kolejności tzn. polecenia
```
ctx.translate(x,y);
ctx.rotate(angle);
```
definiują transformację która najpierw obraca punkty, apotem je przesuwa.  Transformację można zresetować poleceniem
```
ctx.setTransform(1,0,0,1,0,0);
```

Proszę napisać wersje funkcji `polygon` i `doodle`, w których nie trzeba podawać współrzednych środka figury i które
rysują je w środku układu współrzednych. Proszę wykorzystać te funkcje wraz z transformacjami, 
aby narysować razem pentagram i pięciokąt podobnie jak poprzednio, ale w punkcie (120,400) układu współrzędnych,
z pentagramem obróconym o 30 stopni w stosunku do pięciokata.