set title "World X"
set xlabel "Długość"
set ylabel "Szerokość"
set nokey
set autoscale
set pointsize 0.17
set grid
set xrange [-180:180]
set yrange [-90:90]

do for[loop=1:5] { 
#	do for [ii=1:199] { plot \
#	"plot.txt" every ::ii::ii using 2:3 with points, \
#	"plot.txt" every ::ii::ii using 4:5 with points, \
#	"plot.txt" every ::ii::ii using 6:7 with points, \
#	"plot.txt" every ::ii::ii using 8:9 with points, \
#	"plot.txt" every ::ii::ii using 10:11 with points, \
#	"plot.txt" every ::ii::ii using 12:13 with points, \
#	"plot.txt" every ::ii::ii using 14:15 with points, \
#	"plot.txt" every ::ii::ii using 16:17 with points, \
#	"plot.txt" every ::ii::ii using 18:19 with points, \
#	"plot.txt" every ::ii::ii using 20:21 with points, \
#	"plot.txt" every ::ii::ii using 22:23 with points, \
#	"plot.txt" every ::ii::ii using 24:25 with points, \
#	"plot.txt" every ::ii::ii using 26:27 with points
#	}

	do for [ii=1:199] { plot \
	"plot.txt" every ::1::ii using 2:3 with lines, \
	"plot.txt" every ::1::ii using 4:5 with lines, \
	"plot.txt" every ::1::ii using 6:7 with lines, \
	"plot.txt" every ::1::ii using 8:9 with lines, \
	"plot.txt" every ::1::ii using 10:11 with lines, \
	"plot.txt" every ::1::ii using 12:13 with lines, \
	"plot.txt" every ::1::ii using 14:15 with lines, \
	"plot.txt" every ::1::ii using 16:17 with lines, \
	"plot.txt" every ::1::ii using 18:19 with lines, \
	"plot.txt" every ::1::ii using 20:21 with lines, \
	"plot.txt" every ::1::ii using 22:23 with lines, \
	"plot.txt" every ::1::ii using 24:25 with lines, \
	"plot.txt" every ::1::ii using 26:27 with lines
	}
} 
