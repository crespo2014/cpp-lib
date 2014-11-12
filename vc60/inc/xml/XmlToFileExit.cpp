/*=========================================================================+

   Name:
      XmlToFileExit.cpp

   Abstract:
      This module defines a sample Program Exits DLL. It writes all the received
      data to the file XmlToFileExit.txt located in %ETAHOME%\Logs

      This sample defines one Program Exit function WriteToFile
	  
			To create a program exit object within Admin for this program exit,
			use the following steps in ETA Manager:
				1. Go to the Namespace task
				2. Select objectclass "Program Exit" (aka common program exit)
				3. Press New, and fill in the fields as follows:
					a.  Name:  pick any name
					b.  Description:  optional description
					c.	Type:  DLL
					d.  Location: c:\...\XmlToFileExit.DLL  (full path to DLL)
					e.  Method:  WriteToFile

			Then to set this registered program exit as the one to call,
			create one or more reference to this program exit object
			you just created.  Exit references can be placed on any or
			all of the following kinds of objects:	
				Common Program Exits Configuration Object
				Role
				Policy
				Directory


   Created:
      30/04/04

   Notes:

+=========================================================================*/

#pragma warning(disable:4786)

#include <stdio.h>
#include <string>
#include <sys/timeb.h>
#include <time.h>
#include <memory.h>

// ExitXMLBlock is a helper class that is used to hide most XML knowledge
#include "ExitXMLBlock.h"


#define COMMONEXIT_API __declspec(dllexport)

std::string
Timestamp()
{
   struct _timeb timebuffer;
   char *timeline;
   char buf[100];

   _ftime( &timebuffer );
   timeline = ctime( & ( timebuffer.time ) );
   memset( buf, 0, 100 );
   sprintf( buf, "%.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20] );
   return std::string(buf);
}

/*-------------------------------------------------------------------------+
   PUBLIC FUNCTIONS in the XmlToFileExit DLL (main entry points)
+-------------------------------------------------------------------------*/

extern "C"
COMMONEXIT_API int
WriteToFile(
		char *		input_XML,
		char **		return_XML,
		int *		return_XML_length	// IN/OUT
	)
{
	bool				continue_eta_execution		= true;
	std::string				error_msg;
	STATUS_T			status						= E_SUCCESS;
// Remove trailing "\".
    std::string sFileName = std::string(getenv("ETAHOME"))
            + std::string("\\Logs\\XmlToFileExit.txt");
    FILE *outf;
    outf = fopen( sFileName.c_str(), "a" );
    fprintf( outf, "=================================\n");

// Timestamp
    fprintf(outf, "%s", Timestamp().c_str());
    fprintf( outf, "---------------------------------\n");
    fprintf( outf, "XML payload:\n");
    fprintf( outf, "---------------------------------\n");
    fprintf(outf, "%s\n", input_XML);
    fprintf( outf, "=================================\n");

	/* Check the exit type */
	/* Build the return XML block. */
	int max_return_length = *return_XML_length;
	std::string return_string = std::string("<eTExitReturn><eTExitReturnCategory>SUCCESS</eTExitReturnCategory><eTExitReturnNative>0</eTExitReturnNative><eTExitContinue>TRUE</eTExitContinue></eTExitReturn>");
 	*return_XML_length = return_string.length();
	sprintf(*return_XML, "%s", return_string.c_str());
    fclose(outf);
	return status;
}

