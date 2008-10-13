/********************************** 
*
*  Strings
*
***********************************/

#ifndef _strings_
#define _strings_

/* strcpy
*  Copia la cadena src a dst
*
*  Recibe como parametros:
*  - char *src: cadena de origen
*  - char *dst: cadena de destino
*
**/
int strcpy(char* dst, char* src);

/* strlen
*  Cuenta la canitdad de caracteres que tiene la cadena
*
*  Recibe como parametros:
*  - char *s: cadena a contar la cantidad de caracteres
*
**/
int strlen(char *s);

/* strinstr
*  Busca una cadena dentro de otra y devuelve su posicion
*
*  Recibe como parametros:
*  - char *haystack: cadena de origen
*  - char *needle: cadena a buscar
*
**/
int strinstr(const char * haystack, const char * needle);

/* strcmp
*  Compara si las cadenas son iguales
*
*  Recibe como parametros:
*  - char *: cadena1
*  - char *: cadena2
*
**/
int strcmp(char* string1, char* string2);

/* isAlpha
*  Se fija si el caracter es alfabetico
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int isAlpha(int c);

/* isUpper
*  Se fija si el caracter es alfabetico y esta en mayuscula
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int isUpper(int c);

/* isLower
*  Se fija si el caracter es alfabetico y esta en minuscula
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int isLower(int c);

/* toLower
*  retorna el caracter dado a minuscula
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int toLower(int c);

/* toUpper
*  retorna el caracter dado a mayuscula
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int toUpper(int c);

int isNumeric(int c);

/* strchr
*  retorna la direccion donde encuentra el caracter
*  o NULL si no lo encuentra
*
*  Recibe como parametros:
*  - char: caracter
*
**/
char *
strchr(const char *s, char c);

#endif
