//===========================================================================
//
// Module:  LNSACTIO.HPP
//
// Description:
//
//		Class library definition for LNSimpleAction and related classes.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNSACTIO_HPP
#define LNSACTIO_HPP

#ifndef LNSFIELD_HPP
#include "lnsfield.hpp"
#endif


//===========================================================================
//
//		Data types and constants
//
//===========================================================================

	// Type codes for simple actions
enum LNSIMPLEACTIONTYPE
{
	LNSIMPLEACTIONTYPE_UNKNOWN = 0,
	LNSIMPLEACTIONTYPE_COPY_TO_DATABASE,
	LNSIMPLEACTIONTYPE_COPY_TO_FOLDER,
	LNSIMPLEACTIONTYPE_DELETE,
	LNSIMPLEACTIONTYPE_MODIFY_FIELDS_IN_FORM,
	LNSIMPLEACTIONTYPE_MARK_READ,
	LNSIMPLEACTIONTYPE_MARK_UNREAD,
	LNSIMPLEACTIONTYPE_MODIFY_FIELD,
	LNSIMPLEACTIONTYPE_MOVE_TO_FOLDER,
	LNSIMPLEACTIONTYPE_REMOVE_FROM_FOLDER,
	LNSIMPLEACTIONTYPE_RUN_AGENT,
	LNSIMPLEACTIONTYPE_RUN_FORMULA,
	LNSIMPLEACTIONTYPE_RUN_JAVA,
	LNSIMPLEACTIONTYPE_RUN_LOTUS_SCRIPT,
	LNSIMPLEACTIONTYPE_SEND_DOCUMENT,
	LNSIMPLEACTIONTYPE_SEND_MAIL,
	LNSIMPLEACTIONTYPE_SEND_NEWSLETTER,
	LNSIMPLEACTIONTYPE_SEND_REPLY
};

//===========================================================================
//
//		Class definition for LNSimpleAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleAction : public LNSmartPtr
{
	friend class LNSimpleActions;
	friend class LNSimpleFolderAction;
	friend class LNSimpleFieldsInFormAction;
	friend class LNSimpleDatabaseAction;
	friend class LNSimpleModifyFieldAction;
	friend class LNSimpleRunFormulaAction;
	friend class LNSimpleRunAgentAction;
	friend class LNSimpleSendMailAction;
	friend class LNSimpleSendNewsletterAction;
	friend class LNSimpleSendReplyAction;

	public:
		LNSimpleAction (void);
		LNSimpleAction (LNSIMPLEACTIONTYPE type);
		LNSimpleAction (const LNSimpleAction & other);

		~LNSimpleAction (void);

		LNSimpleAction &	operator= (const LNSimpleAction & other);

		LNCLASSID			GetClassID (void) const
								{ return (LNCLASSID_LNSIMPLEACTION); }

		LNSIMPLEACTIONTYPE	GetSimpleActionType (void) const;

	protected:
		LNSimpleAction (LNSimpleActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		LNSimpleActionBody * GetSimpleActionBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleActions
//
//===========================================================================

class LNIMPEXPCL LNSimpleActions : public LNSmartPtr
{

	public:
		LNSimpleActions (void);
		LNSimpleActions (const LNSimpleActions & other);

		~LNSimpleActions (void);

		LNSimpleActions &	operator= (const LNSimpleActions & other);

		LNSimpleAction		operator[] (LNINT n);

		LNSTATUS			Append (const LNSimpleAction & newAction);
		LNSTATUS			Delete (LNINT index, LNINT count = 1);
		virtual LNCLASSID	GetClassID (void) const
								{ return (LNCLASSID_LNSIMPLEACTIONS); }
		LNINT				GetCount (void) const;
		LNSTATUS			Insert (LNINT position,
								const LNSimpleAction & newAction);
		LNSTATUS			ParseSimpleActions (HANDLE pool,
								DBLOCK block, DWORD cdsize);
		LNSTATUS			ParseSimpleActions (char *pData, DWORD length);

protected:
		LNSimpleActions (LNSimpleActionsBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

private:
		void				CreateBody (LNSimpleActionsBody * pBody);
		LNSimpleActionsBody * GetSimpleActionsBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleDatabaseAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleDatabaseAction : public LNSimpleAction
{
	friend class LNSimpleActions;
	friend class LNSimpleActionsBody;

	public:
		LNSimpleDatabaseAction (void);
		LNSimpleDatabaseAction (const LNSimpleDatabaseAction & other);
		LNSimpleDatabaseAction (const LNSimpleAction & other);

		~LNSimpleDatabaseAction (void);

		LNSimpleDatabaseAction & operator= (const LNSimpleDatabaseAction & other);
		
		LNCLASSID	GetClassID (void) const
						{ return (LNCLASSID_LNSIMPLEDATABASEACTION); }
		LNString	GetDatabasePathname (void) const;
		LNBOOL		GetDeleteFromSource (void) const;
		LNString	GetServerName (void) const;

		LNSTATUS	SetDatabasePathname (const LNString & newName);
		LNSTATUS	SetDeleteFromSource (LNBOOL newFlag);
		LNSTATUS	SetServerName (const LNString & newName);

	protected:
		LNSimpleDatabaseAction (LNSimpleDatabaseActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		LNSimpleDatabaseAction (LNSIMPLEACTIONTYPE type);	// disabled

		void		CreateBody (LNSimpleDatabaseActionBody * pBody);
		LNSimpleDatabaseActionBody * GetSimpleDatabaseActionBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleFieldsInFormAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleFieldsInFormAction : public LNSimpleAction
{
	friend class LNSimpleActions;
	friend class LNSimpleActionsBody;
	friend class LNSimpleFieldValueBody;

	public:
		LNSimpleFieldsInFormAction (void);
		LNSimpleFieldsInFormAction (const LNSimpleFieldsInFormAction & other);
		LNSimpleFieldsInFormAction (const LNSimpleAction & other);

		~LNSimpleFieldsInFormAction (void);

		LNSimpleFieldsInFormAction & operator= (const LNSimpleFieldsInFormAction & other);
		LNSimpleFieldValue	operator[] (LNINT n);

		LNSTATUS	Append (const LNSimpleFieldValue & newField);
		LNSTATUS	Delete (LNINT index, LNINT count = 1);
		LNCLASSID	GetClassID (void) const
								{ return (LNCLASSID_LNSIMPLEFIELDSINFORMACTION); }
		LNINT		GetFieldCount (void) const;
		LNString	GetFormName (void) const;
		LNSTATUS	Insert (LNINT position, const LNSimpleFieldValue & newField);
		LNSTATUS	SetFormName (const LNString & newName);

	protected:
		LNSimpleFieldsInFormAction (LNSimpleFieldsInFormActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		LNSimpleFieldsInFormAction (LNSIMPLEACTIONTYPE type);	// disabled

		void		CreateBody (LNSimpleFieldsInFormActionBody * pBody);
		LNSimpleFieldsInFormActionBody * GetSimpleFieldsInFormActionBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleFolderAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleFolderAction : public LNSimpleAction
{
	friend class LNSimpleActions;
	friend class LNSimpleActionsBody;

	public:
		LNSimpleFolderAction (void);
		LNSimpleFolderAction (LNSIMPLEACTIONTYPE type);
		LNSimpleFolderAction (const LNSimpleFolderAction & other);
		LNSimpleFolderAction (const LNSimpleAction & other);

		~LNSimpleFolderAction (void);

		LNSimpleFolderAction &	operator= (const LNSimpleFolderAction & other);

		LNCLASSID	GetClassID (void) const
								{ return (LNCLASSID_LNSIMPLEFOLDERACTION); }
		LNBOOL		GetCreateNewFolder (void) const;
		LNString	GetFolderName (void) const;
		LNBOOL		GetPrivateFolder (void) const;

		LNSTATUS	SetCreateNewFolder (LNBOOL newFlag);
		LNSTATUS	SetFolderName (const LNString & newFolder);
		LNSTATUS	SetPrivateFolder (LNBOOL newFlag);

	protected:
		LNSimpleFolderAction (LNSimpleFolderActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		void		CreateBody (LNSimpleFolderActionBody * pBody);
		LNSimpleFolderActionBody * GetSimpleFolderActionBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleModifyFieldAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleModifyFieldAction : public LNSimpleAction
{
	friend class LNSimpleActions;
	friend class LNSimpleActionsBody;

	public:
		LNSimpleModifyFieldAction (void);
		LNSimpleModifyFieldAction (const LNSimpleModifyFieldAction & other);
		LNSimpleModifyFieldAction (const LNSimpleAction & other);

		~LNSimpleModifyFieldAction (void);
		
		LNSimpleModifyFieldAction & operator= (const LNSimpleModifyFieldAction & other);
		
		LNBOOL		GetAppendToField (void) const;

		LNCLASSID	GetClassID (void) const
						{ return (LNCLASSID_LNSIMPLEMODIFYFIELDACTION); }
		
		LNString	GetFieldName (void) const;
		
		LNBOOL		GetReplaceField (void) const;

		LNString	GetValueString (void) const;

		LNSTATUS	SetAppendToField (LNBOOL newFlag);

		LNSTATUS	SetFieldName (const LNString & newName);
		
		LNSTATUS	SetReplaceField (LNBOOL newFlag);
		
		LNSTATUS	SetValueString (const LNString & newValue);

	protected:
		LNSimpleModifyFieldAction (LNSimpleModifyFieldActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		LNSimpleModifyFieldAction (LNSIMPLEACTIONTYPE type);	// disabled

		void		CreateBody (LNSimpleModifyFieldActionBody * pBody);
		LNSimpleModifyFieldActionBody * GetSimpleModifyFieldActionBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleRunFormulaAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleRunFormulaAction : public LNSimpleAction
{
	friend class LNSimpleActions;
	friend class LNSimpleActionsBody;

	public:
		LNSimpleRunFormulaAction (void);
		LNSimpleRunFormulaAction (const LNSimpleRunFormulaAction & other);
		LNSimpleRunFormulaAction (const LNSimpleAction & other);

		~LNSimpleRunFormulaAction (void);

		LNSimpleRunFormulaAction & operator= (const LNSimpleRunFormulaAction & other);

		LNCLASSID		GetClassID (void) const
							{ return (LNCLASSID_LNSIMPLERUNFORMULAACTION); }

		LNBOOL			GetCopyToNewDocument (void) const;

		LNSTATUS		GetFormula (LNFormula * pFormula) const;

		LNBOOL			GetSelectDocuments (void) const;

		LNSTATUS		SetCopyToNewDocument (LNBOOL newFlag);

		LNSTATUS		SetFormula (const LNFormula & newFormula);

		LNSTATUS		SetSelectDocuments (LNBOOL newFlag);

	protected:
		LNSimpleRunFormulaAction (LNSimpleRunFormulaActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		LNSimpleRunFormulaAction (LNSIMPLEACTIONTYPE type);	// disabled

		void		CreateBody (LNSimpleRunFormulaActionBody * pBody);
		LNSimpleRunFormulaActionBody * GetSimpleRunFormulaActionBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleRunAgentAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleRunAgentAction : public LNSimpleAction
{
	friend class LNSimpleActions;
	friend class LNSimpleActionsBody;

	public:
		LNSimpleRunAgentAction (void);
		LNSimpleRunAgentAction (const LNSimpleRunAgentAction & other);
		LNSimpleRunAgentAction (const LNSimpleAction & other);

		~LNSimpleRunAgentAction (void);

		LNSimpleRunAgentAction & operator= (const LNSimpleRunAgentAction & other);

		LNCLASSID	GetClassID (void) const
							{ return (LNCLASSID_LNSIMPLERUNAGENTACTION); }

		LNString	GetAgentName (void) const;

		LNSTATUS	SetAgentName (const LNString & newAgent);

	protected:
		LNSimpleRunAgentAction (LNSimpleRunAgentActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		LNSimpleRunAgentAction (LNSIMPLEACTIONTYPE type);	// disabled

		void		CreateBody (LNSimpleRunAgentActionBody * pBody);
		LNSimpleRunAgentActionBody * GetSimpleRunAgentActionBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleSendMailAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleSendMailAction : public LNSimpleAction
{
	friend class LNSimpleActions;
	friend class LNSimpleActionsBody;

	public:
		LNSimpleSendMailAction (void);
		LNSimpleSendMailAction (const LNSimpleSendMailAction & other);
		LNSimpleSendMailAction (const LNSimpleAction & other);

		~LNSimpleSendMailAction (void);

		LNSimpleSendMailAction & operator= (const LNSimpleSendMailAction & other);

		LNCLASSID	GetClassID (void) const
							{ return (LNCLASSID_LNSIMPLESENDMAILACTION); }

		LNSTATUS	GetBCCFormula (LNFormula * pFormula) const;
		LNString	GetBCCString (void) const;

		LNSTATUS	GetCCFormula (LNFormula * pFormula) const;
		LNString	GetCCString (void) const;

		LNBOOL		GetIncludeDoclink (void) const;
		LNBOOL		GetIncludeDocument (void) const;

		LNString	GetMessageBody (void) const;

		LNBOOL		GetSaveMessage (void) const;

		LNSTATUS	GetSubjectFormula (LNFormula * pFormula) const;
		LNString	GetSubjectString (void) const;

		LNSTATUS	GetToFormula (LNFormula * pFormula) const;
		LNString	GetToString (void) const;

		LNBOOL		HasBCCField (void) const;
		LNBOOL		HasCCField (void) const;
		LNBOOL		HasMessageBody (void) const;
		LNBOOL		HasSubjectField (void) const;
		LNBOOL		HasToField (void) const;

		LNBOOL		IsBCCFormula (void) const;
		LNBOOL		IsCCFormula (void) const;
		LNBOOL		IsSubjectFormula (void) const;
		LNBOOL		IsToFormula (void) const;

		LNSTATUS	SetBCCFormula (const LNFormula & newAddress);
		LNSTATUS	SetBCCString (const LNString & newAddress);

		LNSTATUS	SetCCFormula (const LNFormula & newAddress);
		LNSTATUS	SetCCString (const LNString & newAddress);

		LNSTATUS	SetIncludeDoclink (LNBOOL newFlag);
		LNSTATUS	SetIncludeDocument (LNBOOL newFlag);

		LNSTATUS	SetMessageBody (const LNString & newText);

		LNSTATUS	SetSaveMessage (LNBOOL newFlag);

		LNSTATUS	SetSubjectFormula (const LNFormula & newAddress);
		LNSTATUS	SetSubjectString (const LNString & newAddress);

		LNSTATUS	SetToFormula (const LNFormula & newAddress);
		LNSTATUS	SetToString (const LNString & newAddress);

	protected:
		LNSimpleSendMailAction (LNSimpleSendMailActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		LNSimpleSendMailAction (LNSIMPLEACTIONTYPE type);	// disabled

		void		CreateBody (LNSimpleSendMailActionBody * pBody);
		LNSimpleSendMailActionBody * GetSimpleSendMailActionBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleSendNewsletterAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleSendNewsletterAction : public LNSimpleAction
{
	friend class LNSimpleActions;
	friend class LNSimpleActionsBody;

	public:
		LNSimpleSendNewsletterAction (void);
		LNSimpleSendNewsletterAction (const LNSimpleSendNewsletterAction & other);
		LNSimpleSendNewsletterAction (const LNSimpleAction & other);

		~LNSimpleSendNewsletterAction (void);

		LNSimpleSendNewsletterAction & operator= (const LNSimpleSendNewsletterAction & other);

		LNCLASSID	GetClassID (void) const
							{ return (LNCLASSID_LNSIMPLESENDNEWSLETTERACTION); }

		LNSTATUS	GetBCCFormula (LNFormula * pFormula) const;
		LNString	GetBCCString (void) const;

		LNSTATUS	GetCCFormula (LNFormula * pFormula) const;
		LNString	GetCCString (void) const;

		LNINT		GetGatherCount (void) const;

		LNBOOL		GetIncludeSummary () const;

		LNString	GetMessageBody (void) const;

		LNSTATUS	GetSubjectFormula (LNFormula * pFormula) const;
		LNString	GetSubjectString (void) const;

		LNSTATUS	GetToFormula (LNFormula * pFormula) const;
		LNString	GetToString (void) const;

		LNString	GetViewName (void) const;

		LNBOOL		HasBCCField (void) const;
		LNBOOL		HasCCField (void) const;
		LNBOOL		HasGatherCount (void) const;
		LNBOOL		HasMessageBody (void) const;
		LNBOOL		HasSubjectField (void) const;
		LNBOOL		HasToField (void) const;

		LNBOOL		IsBCCFormula (void) const;
		LNBOOL		IsCCFormula (void) const;
		LNBOOL		IsSubjectFormula (void) const;
		LNBOOL		IsToFormula (void) const;

		LNSTATUS	SetBCCFormula (const LNFormula & newAddress);
		LNSTATUS	SetBCCString (const LNString & newAddress);

		LNSTATUS	SetCCFormula (const LNFormula & newAddress);
		LNSTATUS	SetCCString (const LNString & newAddress);

		LNSTATUS	SetGatherCount (LNINT newCount);

		LNSTATUS	SetIncludeSummary (LNBOOL newFlag);

		LNSTATUS	SetMessageBody (const LNString & newText);

		LNSTATUS	SetSubjectFormula (const LNFormula & newAddress);
		LNSTATUS	SetSubjectString (const LNString & newAddress);

		LNSTATUS	SetToFormula (const LNFormula & newAddress);
		LNSTATUS	SetToString (const LNString & newAddress);

		LNSTATUS	SetViewName (const LNString & newView);

	protected:
		LNSimpleSendNewsletterAction (LNSimpleSendNewsletterActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		LNSimpleSendNewsletterAction (LNSIMPLEACTIONTYPE type);	// disabled

		void		CreateBody (LNSimpleSendNewsletterActionBody * pBody);
		LNSimpleSendNewsletterActionBody * GetSimpleSendNewsletterActionBody (void) const;
};


//===========================================================================
//
//		Class definition for LNSimpleSendReplyAction
//
//===========================================================================

class LNIMPEXPCL LNSimpleSendReplyAction : public LNSimpleAction
{
	friend class LNSimpleActions;
	friend class LNSimpleActionsBody;

	public:
		LNSimpleSendReplyAction (void);
		LNSimpleSendReplyAction (const LNSimpleSendReplyAction & other);
		LNSimpleSendReplyAction (const LNSimpleAction & other);

		~LNSimpleSendReplyAction (void);

		LNSimpleSendReplyAction & operator= (const LNSimpleSendReplyAction & other);

		LNCLASSID	GetClassID (void) const
							{ return (LNCLASSID_LNSIMPLESENDREPLYACTION); }

		LNString	GetMessageBody (void) const;
		
		LNBOOL		GetIncludeDocument (void) const;
		LNBOOL		GetReplyOnce (void) const;
		LNBOOL		GetReplyToAgents (void) const;
		LNBOOL		GetReplyToAll (void) const;
		LNBOOL		GetSaveMessage (void) const;

		LNBOOL		HasMessageBody (void) const;

		LNSTATUS	SetIncludeDocument (LNBOOL newFlag);
		LNSTATUS	SetReplyOnce (LNBOOL newFlag);
		LNSTATUS	SetReplyToAgents (LNBOOL newFlag);
		LNSTATUS	SetReplyToAll (LNBOOL newFlag);
		LNSTATUS	SetSaveMessage (LNBOOL newFlag);

		LNSTATUS	SetMessageBody (const LNString & newText);

	protected:
		LNSimpleSendReplyAction (LNSimpleSendReplyActionBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr) const;

	private:
		LNSimpleSendReplyAction (LNSIMPLEACTIONTYPE type);	// disabled

		void		CreateBody (LNSimpleSendReplyActionBody * pBody);
		LNSimpleSendReplyActionBody * GetSimpleSendReplyActionBody (void) const;
};


#endif

