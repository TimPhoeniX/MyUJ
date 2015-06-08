set title "World X"
set xlabel "Długość"
set ylabel "Szerokość"
set nokey
set autoscale
set pointsize 0.01
set grid
set xrange [-180:180]
set yrange [-90:90]

set term svg enhanced background rgb 'white'
set output "plot.svg"

plot "plot.txt" using 2:3 with linespoints pointtype 7, \
	"plot.txt" using 4:5 with linespoints pointtype 7, \
	"plot.txt" using 6:7 with linespoints pointtype 7, \
	"plot.txt" using 8:9 with linespoints pointtype 7, \
	"plot.txt" using 10:11 with linespoints pointtype 7, \
	"plot.txt" using 12:13 with linespoints pointtype 7, \
	"plot.txt" using 14:15 with linespoints pointtype 7, \
	"plot.txt" using 16:17 with linespoints pointtype 7, \
	"plot.txt" using 18:19 with linespoints pointtype 7, \
	"plot.txt" using 20:21 with linespoints pointtype 7, \
	"plot.txt" using 22:23 with linespoints pointtype 7, \
	"plot.txt" using 24:25 with linespoints pointtype 7, \
	"plot.txt" using 26:27 with linespoints pointtype 7

