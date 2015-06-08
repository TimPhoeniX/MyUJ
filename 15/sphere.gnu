reset 

R = 98

set xrange [-R:R]
set yrange [-R:R]
set zrange [-R:R]

X(phi,psi) = R*cos(psi)*cos(phi)
Y(phi,psi) = R*cos(psi)*sin(phi)
Z(psi)     = R*sin(psi)

set palette defined (-100 'pink',100 'pink')

set samples 25
set isosamples 25

set parametric
set urange[0:2*pi]
set vrange[-pi/2:pi/2]

set table 'sphere.dat'

splot X(u,v),Y(u,v),Z(v)

unset parametric
unset table