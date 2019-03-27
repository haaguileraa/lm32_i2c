#include <fuente_6x8.c>

int main(void)
{

char bib [53] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};


uint8_t ascii[53];
uint8_t n[53];
uint8_t letra[53][6];

for(uint8_t i = 0; i<53; i++){
ascii[i] = bib[i];
n[i] = (ascii[i] - 0x20);
for(uint8_t j = 0; j<6; j++){
letra[i][j] = fuente[n[i]][j];
}
}


char texto[] = "hola mundo";


uint8_t mx = sizeof(texto);

uint8_t output[mx][6];


for(uint8_t k=0; k<mx; k++){
for(uint8_t l=0; l<53; l++){
for(uint8_t r=0; r<6; r++){
if(texto [k] == bib[l]){
output[k][r] = letra[l][r];
}
}
}
}

for(uint8_t y=0; y<mx; y++){
for(uint8_t x=0; x<6; x++){
cout<<output[y][x];
cout<<"\n";
}
}

return 0;
}




























