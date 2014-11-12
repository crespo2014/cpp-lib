// _directorio.h: interface for the C_directorio class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX__DIRECTORIO_H__2E8C7001_3537_11D4_9960_0060970D22B5__INCLUDED_)
#define AFX__DIRECTORIO_H__2E8C7001_3537_11D4_9960_0060970D22B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SIALDAP_API C_Directorio  

	///////////////////////////////////////////////////////////////////////////////////
	//All functions described below are propietary of the Class C_Directorio
	///////////////////////////////////////////////////////////////////////////////////
	
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	int Remove_Entry_DN(char* DN);
	//This function removes an Entry from the Directory. It uses the DN of the Entry, 
	//(that is a char* type) to delete it, it doesn't use an instance of C_Entry.
	//It returns an integer value with the result of the operation, (0 if no error occurs;
	//anything else if there is an error)
	///////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	int Modify_Entry(C_Entry* Modified_Entry);
	//this function modifies an entry of the directory replacing the entry existing in the 
	//directory with the given entry; It uses as parmeters an instance of C_Entry that is 
	//the entry modified.
	//It returns an integer value with the result of the operation, (0 if no error occurs;
	//anything else if there is an error)
	//////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	int Modify_Entry2(C_Entry* Modified_Entry);
	//this function modifies an entry of the directory replacing the entry existing in the 
	//directory with the given entry; It uses as parmeters an instance of C_Entry that is 
	//the entry modified.
	//It returns an integer value with the result of the operation, (0 if no error occurs;
	//anything else if there is an error)
	//////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	int Remove_Entry(C_Entry* Delete_Entry);
	//This function removes an Entry from the Directory. It needs the Instance of the C_Entry
	//class that is going to be removed. From thisIt uses the DN of the Entry to delete it.
	//It returns an integer value with the result of the operation, (0 if no error occurs;
	//anything else if there is an error)	
	///////////////////////////////////////////////////////////////////////////////////
	

	///////////////////////////////////////////////////////////////////////////////////
	int Logout();
	//This function performs a session logout. First it verifies that is loged in, and then it 
	//logs out. If not, it does nothing.
	//It returns an integer value with the result of the operation, (0 if no error occurs;
	//anything else if there is an error)	
	///////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	bool Find_Close();
	//this functions must end a Search. It should frees the memory allocated by the results
	//of the search.
	//It returns a boolean value depending on the result of the operation
	///////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	int Add_Entry(C_Entry *New_Entry);
	//This functions adds an instance of C_Entry that is passed as parameters in the 
	//function. 
	//It returns an integer value with the result of the operation, (0 if no error occurs;
	//anything else if there is an error).	
	///////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	C_Directorio (char* Ip_add,int Port_number);
	//This is the constructor of the class. It requires the ip address of the machine 
	//where is the LDAP server, and port number that uses the LDAP server. It uses this 
	//parameters to stabilish a link with the directory when the appropiate function is 
	//called.
	//This function just creates an instance of this class
	///////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	bool Find_Next(C_Entry* Next_Entry);
	//This function search for the first entry of the result of a search and it stores 
	//that value on the C_Entry instance passed as a parameter. That Instace must exists
	//before calling the function.
	//of the list resulted from the search
	//This function returns a boolena value: True when there is an entry in the result 
	//of the search, and False when there isn't any Entry left.
	///////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	int Find (char* Base_tree,char* Filter, int Deep,C_Entry* New_Entry);
	//This function performs a search in the directory, it needs four parameters 
	//the base from which the search starts (This is a char* type with the format:"ou=aaaa,
	//o=aaaa,c=aaaa"),the Filter to select the entries to search (This is a cha* type with 
	//the format: "(attribute=value)"), the Deep of the search, indicates the tree level
	//that we are going to search, (This is an int type which its values has been defined 
	//as constants).
	//It returns an integer value with the result of the operation, (0 if no error occurs;
	//anything else if there is an error)	
	///////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////
	int Find_Attrib (char* Base_tree,char* Filter, int Deep,C_Entry* New_Entry,char** Attrib);
	//This function performs a search in the directory, it needs four parameters 
	//the base from which the search starts (This is a char* type with the format:"ou=aaaa,
	//o=aaaa,c=aaaa"),the Filter to select the entries to search (This is a cha* type with 
	//the format: "(attribute=value)"), the Deep of the search, indicates the tree level
	//that we are going to search, (This is an int type which its values has been defined 
	//as constants).
	//It returns an integer value with the result of the operation, (0 if no error occurs;
	//anything else if there is an error)	
	///////////////////////////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////////////////////////////////////////////
	int Login(char* User,char* Password);
	//This function perfom a login to the directory with a user and a Password, (both 
	//arguments are char* type).Before login you must verify that nobody is loged in 
	//with the same instance, and if there is someone already loged,you must logout and 
	//then login with the new parameters.
	//It returns an integer value with the result of the operation, (0 if no error occurs;
	//anything else if there is an error)	
	///////////////////////////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////////////////////////////////////////////
	bool clean_Entry(C_Entry *New_Entry);
	//This functions takes an instance of C_Entry class and deletes all attributes that
	//contains values given automatically by the directory. Those values are given in a 
	//global list, that is stored in the prohib_list variable of the instance of
	//C_Directorio.
	//This function is used to prepare an instance of C_Entry to be added to the directory
	//without any problem.
	//It returns a boolean value with the result of the operation.
	///////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////	
	virtual ~C_Directorio();
	//This functions is the destructor of the Class C_Directorio.
	///////////////////////////////////////////////////////////////////////////////////

private:
	///////////////////////////////////////////////////////////////////////////////////
	//Declaration of the private statements of the Class
	///////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////
	char** prohib_list;
	//This variable is the list where it stores the attributes that should be removed 
	//before addign the entry to the directory. It is given automatically
	///////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////
	bool IsLoged;
	//This variable indicates if someone is already loged with this instance
	///////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////
	LDAPMessage* Result;
	//This variable is used to store the results of a search. 
	///////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////
	LDAP* ld;
	//This variable is the handler of the conection to the directory
	///////////////////////////////////////////////////////////////////////////////////	
	
	///////////////////////////////////////////////////////////////////////////////////
	int Port;
	//This variable indicates the port where the directory is supposed to be listening
	//LDAP requests
	///////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////
	char* Ip_Address;
	//This variable indicates the IP address of the machine where the LDAP server is 
	//supposed to be.
	///////////////////////////////////////////////////////////////////////////////////	
};

#endif // !defined(AFX__DIRECTORIO_H__2E8C7001_3537_11D4_9960_0060970D22B5__INCLUDED_)
