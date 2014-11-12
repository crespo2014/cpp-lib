// IMem.h: interface for the IMem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMEM_H__701CA602_F15A_468A_A724_AA751A48E17C__INCLUDED_)
#define AFX_IMEM_H__701CA602_F15A_468A_A724_AA751A48E17C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "itube.h"

/*
	utilizar un lock para luego aplicar un tube no tiene sentido
	la idea del look es acumular datos que depues se van a compactar y utilizar
	un lock debe generar una tuberia de escritura
	que permite ponchar datos hasta x cantidad y entonces compactar
	y se puede utilizar en ficheros de propiedades.
	pero despues de compactar se puede desechar el dato

	formas de cerrar el lock, 
	close	 los datos actuales son compactados y se devuelve el tamaño y el void*
	preclose los datos son compactados y se devuelve tamaño y void* pero no se libera
			 despues de utilizar los datos se invoca al free o de lo contrario se solapan
	free	se libera toda la memoria bloqueada

	cuando se necesitan varios bloqueos, se puede solicitar la posicion actual del bloqueo,
	porque una vez que tengamos todo compactado se puede utilizar esa posicion para distinguir entre datos

*/
class IMem 
{
public:
	// get align memory block max 4GB size
	virtual DWORD get(DWORD size,void** ppvoid) = 0;		
	/*
	add align memory block 
	OUT 
		ppvoid : pointer to memory
	*/
	virtual DWORD add(void* pdata,DWORD size,void** ppvoid) = 0;
	/*
	get unaligned block
	*/
	virtual DWORD getU(DWORD size,void **ppvoid) = 0;
	/*
		add unaligned memory block, only applied to char* or BYTE*
	*/
	virtual DWORD addU(void* pdata,DWORD size,void** ppvoid) = 0;
	/*
		add unaligned cero end string if len = 0. otherwise use len
		the result string es len + 1 (cero is append at end)
	*/
	virtual DWORD addS(char* str,DWORD size,char **pstr) = 0;
	/*
		Conseguir un bloque alineado continuo con un tamaño x.
	*/
	//virtual DWORD avaliable(DWORD* size,void** ppvoid)=0;
	/*
		Hacer efectivo el tamaño del bloque reservado
		se pudiera liberar despues porque siempre se ubica al final de un bloque
		pero es un lio bloquear todo un bloque para obligar a crear otro y luego liberar
		el anterior
	*/
	//virtual DWORD commit(DWORD size)=0;

	/*
		bloquea el final de un bloque y lo prepara para recivir datos que seran alineados
		cuando se colocan todos lo datos se pueden :
		compactar.
		la idea es meter datos uno detras de otro y al final pedir un bloque continuo
		utilizarlo o desecharlo luego con close o free
	*/
	virtual DWORD lock() = 0;
	/*
		Agregar datos a la zona de memoria bloqueada, los datos no son alineados.
	*/
	virtual DWORD lockAdd(void* dt,DWORD size)=0;
	/*
		Se pueden solicitar bloques al lock para poner datos, se devolvera la maxima cantidad de datos contiguos posibles
		una vez tomados los datos se procede a indicar la cantidad
	*/
	virtual DWORD lockAvaliable(void** ppvoid,DWORD* ppsize) = 0;
	/*
		Indicar cuantos datos han sido utilizados en el ultimo lock
		se asume que han sido adicionados esa cantidad de datos.
		si no se ejecuta esta funcion los datos se perderan
	*/
	virtual DWORD lockCommit(DWORD size) = 0;
	/*
		Se compactan los datos del lock en una zona de memoria
		es decir se crea un nuevo lock con todos los datos
		pero no se cierra el lock
	*/
	virtual DWORD lockCompact(void** ppvoid,DWORD* ppsize) = 0;
	/*
	Se cierra el lock y se mantienen los datos en memoria
	previamente hay que compactar la memoria de lo contrario no se podra acceder a los datos
	*/
	virtual DWORD lockClose() = 0;
	/*
	Se cierra el lock y se libera toda la memoria utilizada por este
	*/
	virtual DWORD lockFree()=0;
	/*
		Obtener el tamaño actua ocupado por la zona de bloqueo
	*/
	virtual DWORD lockSize()=0;

	/*
		Obtener una tuberia, que aplica el lock automaticamente
	*/

	virtual ITube* getTube()=0;
	
	/*
		Crear un pto de partida. esto se utiliza para recuperar la memoria en este punto
		se devuelve un estructura shot
	*/
	//virtual DWORD getShot(void** pshot)=0;
	/*
	Volver a un punto
	*/
	//virtual DWORD setShot(void* pshot)=0;


};

/*
	Las especificaciones para la gestion de memoria son:
	la unidad de trabajo es el bloque con un tamaño multiplo del tamaño de pagina
	block: 
		next				proximo bloque
		maxindex o size		tamaño del bloque,	(0 - max)
		freeindex			cantidad de datos en uso 
		shotindex			si hay un pto de bloqueo este es el primer	//opcional poner en clase
	Cuando se necesita un bloque de memoria en el cual meter datos uno tras de otro, se puede utilizar el remanente que hay 
	en cada bloque, y su luego se convierte este bloque en un tubo no se necesita compactar.
	la estructura a utilizar en esta situacion es.
	estructura incial
	lmem:
		datasize	: tamaño de dato o alineacion ( se puede devolver un ITube) y olvidar este dato
		block		: primer bloque que se utiliza
		blockindex	: indice dentro del bloque donde se encuentra la estructura tblock
	tblock:
		nextblock:	:indica el proximo bloque en el cual se encuentra la memoria
		starindex	:inicio dentro del bloque para esta estrutura, permite liberar el espacio rapidamente
	// el tamaño ocupado lo determina el dato de fin del bloque

   Si se solicita un bloque tipo byte se puede aprovechar al maximo el fin de bloque

	Cuando se crea un pto de shot hay que estar seguro se utilizara una estructura shot
	shot
		block	:bloque actual es para validar
		next	:proximo punto de bloqueo


*/
#endif // !defined(AFX_IMEM_H__701CA602_F15A_468A_A724_AA751A48E17C__INCLUDED_)
