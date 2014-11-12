//===========================================================================
//
// Module:  LNSCRIPT.HPP
//
// Description:
//
//		Class library definition for LNLotusScript.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNSCRIPT_HPP
#define LNSCRIPT_HPP

//===========================================================================
//
//		Class definition for LNLotusScript
//
//===========================================================================

class LNIMPEXPCL LNLotusScript : public LNSmartPtr
{
	public:
		LNLotusScript (void);
		LNLotusScript (const LNLotusScript & other);
		LNLotusScript (const LNString & source);
		LNLotusScript (char * pObjectCode, LNINT objectCodeLength);
		LNLotusScript (const LNString & source,
			char * pObjectCode, LNINT objectCodeLength);
		LNLotusScript (char * pSource, LNINT sourceLength,
			char * pObjectCode, LNINT objectCodeLength);

		~LNLotusScript (void);

		LNLotusScript & operator= (const LNLotusScript & other);

		LNCLASSID	GetClassID (void) const
								{ return (LNCLASSID_LNLOTUSSCRIPT); }

		LNINT		GetSourceCodeLength (void) const;

		char *		GetObjectCode (void) const;

		LNINT		GetObjectCodeLength (void) const;

		LNString	GetSource (void) const;

		LNBOOL		HasObjectCode (void) const;

		LNBOOL		HasSource (void) const;

		LNSTATUS	ReadObjectCode (LNINT offset, char * buf, LNINT num) const;

		LNSTATUS	SetObjectCode (char * pObjectCode, LNINT objectCodeLength);

		LNSTATUS	SetObjectCodeLength (LNINT newLength);

		LNSTATUS	SetSource (const LNString & source);

		LNSTATUS	WriteObjectCode (LNINT offset, char * pData, LNINT num);

	protected:
		LNLotusScript (LNLotusScriptBody * pBody);

	private:
		LNLotusScriptBody * GetLotusScriptBody (void) const;
		void		PrepareToModify (void);
};


#endif

