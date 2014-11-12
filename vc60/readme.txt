La compilación multiplataforma se logra utilizando un fichero .h con la definicion de los metodos, y un fichero .cpp que no implementa pero incluye el fichero necesario mediante preprocesado. ejemplo.


file.h

void open()
void close()
void write()

file.cpp
#ifdef W32
#include "w32\file.cpp"
#endif  

#ifdef UNIX
#include "linux\file.cpp"
#endif