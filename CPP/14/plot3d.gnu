set title "World X"
set nokey
set autoscale
set view equal xyz
set pointsize 0.01
set grid
set xrange [-100:100]
set yrange [-100:100]
set zrange [-100:100]

R = 100
X(phi,psi) = R*cos(psi*pi/180)*cos(phi*pi/180)
Y(phi,psi) = R*cos(psi*pi/180)*sin(phi*pi/180)
Z(psi)     = R*sin(psi*pi/180)

splot "plot.txt" using (X($2,$3)):(Y($2,$3)):(Z($3)) with lines, \
	"plot.txt" using (X($4,$5)):(Y($4,$5)):(Z($5)) with lines, \
	"plot.txt" using (X($6,$7)):(Y($6,$7)):(Z($7)) with lines, \
	"plot.txt" using (X($8,$9)):(Y($8,$9)):(Z($9)) with lines, \
	"plot.txt" using (X($10,$11)):(Y($10,$11)):(Z($11)) with lines, \
	"plot.txt" using (X($12,$13)):(Y($12,$13)):(Z($13)) with lines, \
	"plot.txt" using (X($14,$15)):(Y($14,$15)):(Z($15)) with lines, \
	"plot.txt" using (X($16,$17)):(Y($16,$17)):(Z($17)) with lines, \
	"plot.txt" using (X($18,$19)):(Y($18,$19)):(Z($19)) with lines, \
	"plot.txt" using (X($20,$21)):(Y($20,$21)):(Z($21)) with lines, \
	"plot.txt" using (X($22,$23)):(Y($22,$23)):(Z($23)) with lines, \
	"plot.txt" using (X($24,$25)):(Y($24,$25)):(Z($25)) with lines, \
	"plot.txt" using (X($26,$27)):(Y($26,$27)):(Z($27)) with lines	