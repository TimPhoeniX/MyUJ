#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>

// gdImage * wczytajPng(const char * nazwa_pliku)
// {
//     gdImage * img;
//     FILE * f;
//     long size;
//     void * data;
// 
//     img = NULL;
//     if ((f = fopen(nazwa_pliku, "rb")) == NULL) {
//         /* błąd otwarcia pliku */
//         ;
//         goto end;
//     }
//     if (fseek(f, 0, SEEK_END) == -1) {
//         /* błąd fseek */
//         ;
//         goto close;
//     }
//     if ((size = ftell(f)) == -1) {
//         /* błąd ftell */
//         ;
//         goto close;
//     }
//     if (fseek(f, 0, SEEK_SET) == -1) {
//         /* błąd fseek */
//         ;
//         goto close;
//     }
//     if ((data = malloc(size)) == NULL) {
//         /* brak pamięci */
//         ;
//         goto close;
//     }
//     if (fread(data, 1, size, f) != size) {
//         /* błąd odczytu */
//         ;
//         goto close;
//     }
//     img = gdImageCreateFromPngPtr(size, data);
//     free(data);
// close:
//     fclose(f);
// end:
//     return img;
// }

gdImage* wczytajPng(const char * nazwa_pliku)
{
	std::ifstream in(nazwa_pliku, std::ifstream::binary|std::ifstream::in);
	std::vector<char> dat;
	long size = -1;
	if(!in.is_open()) return nullptr;
	in.seekg(0,std::ifstream::end);
	if((size = in.tellg())==-1) return nullptr;
	in.seekg(0);
	if(!in.good()) return nullptr;
	dat.reserve(size);
	if(dat.capacity()<size) return nullptr;
	in.read(dat.data(),size);
	if(in.fail()) return nullptr;
	return gdImageCreateFromPngPtr(size, dat.data());
}