#include "../include/strings.h"
#include "../include/defs.h"

/********************************** 
*
*  Strings
*
***********************************/

/* strlen
*  Cuenta la canitdad de caracteres que tiene la cadena
*
*  Recibe como parametros:
*  - char *s: cadena a contar la cantidad de caracteres
*
**/
int 
strlen(char *s)
{
	int i = 0;

	if (s == NULL)
		return -1;

	while(s[i++]!='\0');

	return i;
}

/* strcpy
*  Copia la cadena src a dst
*
*  Recibe como parametros:
*  - char *src: cadena de origen
*  - char *dst: cadena de destino
*
**/
int
strcpy(char* dst, char* src)
{
	int i=0;

	while(src[i]!='\0')
	{
		dst[i]=src[i];
		i++;
	}

	dst[i]='\0';
	
	return i;
}

/* strinstr
*  Busca una cadena dentro de otra y devuelve su posicion
*
*  Recibe como parametros:
*  - char *haystack: cadena de origen
*  - char *needle: cadena a buscar
*
**/
int 
strinstr(const char * haystack, const char * needle)
{
	int i = 0, j = 0;

	if (haystack[i] == '\0')
		return -1;
	
	// Busco el comienzo de la cadena needle
	while (haystack[i] != '\0' && haystack[i] != needle[0])
		i++;

	// Verifico que sean iguales
	while (haystack[i + j] != '\0' && needle[j] != '\0' && haystack[i + j] == needle[j])
		j++;
	
	if (haystack[i + j] == needle[j] || needle[j] == '\0')
		return i;
	else
	{
		if (haystack[i] == '\0')
			return -1;
		else
			return i + 1 + strinstr(haystack + i + 1, needle);
	}
}

/* strcmp
*  Compara si las cadenas son iguales
*
*  Recibe como parametros:
*  - char *: cadena1
*  - char *: cadena2
*
**/
int 
strcmp(char* string1, char* string2)
{
	int i = 0, resp = 0;

	//Mientras las cadenas sean iguales sigo
	while((resp = string1[i] - string2[i]) == 0 && string1[i]!='\0' && string2[i]!='\0')
		i++;

	return resp;
}

/* isAlpha
*  Se fija si el caracter es alfabetico
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int 
isAlpha(int c)
{
	return ( ( (c) >= 'a' && (c) <= 'z' ) || ( (c) >= 'A' && (c) <= 'Z' ) );
}

/* isNumeric
*  Se fija si el caracter es numerico
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int 
isNumeric(int c)
{
	return ( (c) >= '0' && (c) <= '9');
}

/* isUpper
*  Se fija si el caracter es alfabetico y esta en mayuscula
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int 
isUpper(int c)
{
	return ( (c) >= 'A' && (c) <= 'Z' );
}

/* isLower
*  Se fija si el caracter es alfabetico y esta en minuscula
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int 
isLower(int c)
{
	return ((c) >= 'a' && (c) <= 'z');
}

/* toLower
*  retorna el cacaracter dado a minuscula
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int 
toLower(int c)
{
	return ( isUpper((c)) ? (c) - 'A' + 'a' : (c) );
}

/* toUpper
*  retorna el cacaracter dado a mayuscula
*
*  Recibe como parametros:
*  - char: caracter
*
**/
int 
toUpper(int c)
{
	return ( isLower((c)) ? (c) - 'a' + 'A' : (c) );
}

/* strchr
*  retorna la direccion donde encuentra el caracter
*  o NULL si no lo encuentra
*
*  Recibe como parametros:
*  - char: caracter
*
**/
char *
strchr(const char *s, char c)
{
	int i=0, found=0;

	while(!found && s[i] != '\0')
		if (s[i++] == c)
			found=1;

	return (found)?(char*)(s+i-1):(char*)NULL;
}

