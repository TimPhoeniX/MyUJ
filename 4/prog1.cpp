#include<cstdio>

struct pudlo
{
	char producent[40];
	float wysokosc;
	float szerokosc;
	float dlugosc;
	float objetosc;
};

void show(struct pudlo box)
{
	printf("%s\n%f\n%f\n%f\n%f\n",box.producent,box.wysokosc,box.szerokosc,box.dlugosc,box.objetosc);
}

void volume(struct pudlo *box)
{
	(*box).objetosc=(*box).wysokosc*(*box).dlugosc*(*box).szerokosc;
}

int main()
{
	struct pudlo P = { "Producent", 5, 5, 5, 0 };
	show(P);
	volume(&P);
	show(P);
}-