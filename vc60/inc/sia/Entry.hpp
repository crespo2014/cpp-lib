// _Entry.h: interface for the C_Entry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__ENTRY_H__2E8C7002_3537_11D4_9960_0060970D22B5__INCLUDED_)
#define AFX__ENTRY_H__2E8C7002_3537_11D4_9960_0060970D22B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ldapv3.h"

class SIALDAP_API C_Entry
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	//All functions described below are propietary of the Class C_Entry
	///////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////
	int Modify_Value(int mod_op, const char* mod_type, const char* val,DWORD val_size,int posit);
	//This function modifies the value of an entry, changin its value into the new one.
	//It needs several parameters to perform the operation. In those parameters we introduce
	//the value we are going to change, and the position where its stored that value in 
	//the structure of the C_Entry instance. It uses a parameter where indicates the type of
	//operation, (add, remove, modify, it is an integer value, called mod_op. There are 
	//several values defined), it also uses a parameter that indicates the type of value,
	//(it's a const char* value that indicates the attribute name where the value is going
	//to be stored). It uses a parameter that indicates the value of the entry, (it's a 
	//const char* where stores the value of the attribute), and there is a value that 
	//indicates the size of the data that is going to be stored (it's a DWORD type variable)
	//and the last value is the possition where this new value is going to be stored, (it's
	//an integer).
	//This function returns an integer value with the error code returned.
	///////////////////////////////////////////////////////////////////////////////////	

	///////////////////////////////////////////////////////////////////////////////////
	int Remove_value(char* mod_type);
	//This function removes an attribute from the instance of the C_Entry class, this value
	//is indicated by the parameter mod_type, (it's a char* variable with the value of
	//the mod_type stored).
	//This function returns an integer value with the appropiate error code resulting from
	//the operation.
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	int Add_Value(int mod_op, char* mod_type, const char* val,DWORD val_size);
	//This function adds a new value to an entry.
	//It needs several parameters to perform the operation. In those parameters we introduce
	//the value we are going to add. It uses a parameter where indicates the type of
	//operation, (add, remove, modify, it is an integer value, called mod_op. There are 
	//several values defined), it also uses a parameter that indicates the type of value,
	//(it's a const char* value that indicates the attribute name where the value is going
	//to be stored). It uses a parameter that indicates the value of the entry, (it's a 
	//const char* where stores the value of the attribute), and there is a value that 
	//indicates the size of the data that is going to be stored (it's a DWORD type variable)
	//This function returns an integer value with the error code returned.
	///////////////////////////////////////////////////////////////////////////////////	

	///////////////////////////////////////////////////////////////////////////////////
	int Get_Value(char* mod_type, char* mod_value);	
	//Esta método devuelve el valor de un atributo.	
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	int Get_Values(char* mod_type, char** mod_value);	
	//Esta método devuelve los valores de un atributo multievaluado
	///////////////////////////////////////////////////////////////////////////////////
		
	///////////////////////////////////////////////////////////////////////////////////
	char* DN;
	//This variable is used to store the DN of the instance of C_Entry
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	C_Entry(const C_Entry &entrada);
	//This function is a copy constructor, used to create an instance, with the values
	//of the instance passed as a parameter
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	void Print_entry();
	//This function is used to print the values of a C_Entry class
	// with HTML tags
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	void PrintHTML_entry();
	//This function is used to print the values of a C_Entry class
	///////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	void Clean_attributes();
	//This funcition frees the memory used by the attributes of a C_Entry instance
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	void Add_attributes(LDAPMessage *e,LDAP *ld);
	//This function gets the result of a search and adds the values of the first entry
	//returned by that search and adds those values to the C_Entry instance that called 
	//this method.
	///////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	C_Entry();
	//This Function is the constructor of the Class. Just initialize its variables.
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	virtual ~C_Entry();
	//This function is the Destructor of the class
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	LDAPMod* Attribs[100];
	//This variable represents the structure necesary to store the values of an entry
	//of the directory
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	void Clean_attributes(int i);
	//This function cleans one of the attributes stored in a C_Entry instance. It just 
	//clean an entry in the possition indicated by the parameter of the function(is an 
	//integer value that indicates the position of the attribute that is goin to be 
	//liberated), freeing the memory of that attribute. If the possition doesn't exist
	//it does nothing.
	///////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////
	DWORD Count_values(LDAPMod* Attrib);
	//This function just count the values stored in an attribute, (use as parameter the 
	//attribute of the C_Entry class that is going to count). This function returns the 
	//number of values that are associated at that attribute
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	DWORD Count_values(char* mod_type);
	//This function just count the values stored in an attribute, (use as parameter the 
	//attribute of the C_Entry class that is going to count). This function returns the 
	//number of values that are associated at that attribute
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	bool IsEmpty() const;
	//This is a boolean function that return true if the C_Entry is empty,(with no values)
	//or false if it has any values different from NULL.
	///////////////////////////////////////////////////////////////////////////////////

	int Find (char* mod_type);
	// Devuelve la posición donde se encuentra el atributo.
	// -9 si el atributo no existe.
	// -1 si esta vacio.

	int Compare (char *value, char* mod_type);
	// This returns TRUE if the mod_type is the value passed as 1st arg.
};

#endif // !defined(AFX__ENTRY_H__2E8C7002_3537_11D4_9960_0060970D22B5__INCLUDED_)

