//===========================================================================
//
// Module:  LNJSCRS.HPP
//
// Description:
//
//		Class library definition for LNJavaScript.
//
//===========================================================================
//
// Copyright (c) 1998 Java Development Corporation. All rights reserved.
// This software is subject to the Java Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNJSCRS_HPP
#define LNJSCRS_HPP
//===========================================================================
//
//		Class definition for LNJavaScript
//
//===========================================================================
// It is important to keep the values in this enum as is
// because they are used as indexes in array of CD records
enum LNJSEVENT
{
	LNJSEVENT_ONCLICK = 0,     
	LNJSEVENT_ONDBLCLICK,  
	LNJSEVENT_ONMOUSEDOWN, 
	LNJSEVENT_ONMOUSEUP,   
	LNJSEVENT_ONMOUSEOVER, 
	LNJSEVENT_ONMOUSEMOVE, 
	LNJSEVENT_ONMOUSEOUT,  
	LNJSEVENT_ONKEYPRESS,  
	LNJSEVENT_ONKEYDOWN,   
	LNJSEVENT_ONKEYUP,     
	LNJSEVENT_ONFOCUS,	  
	LNJSEVENT_ONBLUR,	  
	LNJSEVENT_ONLOAD,	  
	LNJSEVENT_ONUNLOAD,	  
	LNJSEVENT_HEADER,	  
	LNJSEVENT_ONSUBMIT,	  
	LNJSEVENT_ONRESET,	  
	LNJSEVENT_ONCHANGE,	  
	LNJSEVENT_ONERROR,	  
	LNJSEVENT_ONHELP,	  
	LNJSEVENT_ONSELECT,
	LNJSEVENT_COUNT	
};
					
class LNIMPEXPCL LNJavaScript : public LNSmartPtr
{
	public:
		LNJavaScript (void);
		LNJavaScript (const LNJavaScript & other);
		~LNJavaScript (void);

		LNJavaScript & operator= (const LNJavaScript & other);

		void Clear();

		LNCLASSID GetClassID (void) const
								{ return LNCLASSID_LNJAVASCRIPT; }

		LNString GetScript(LNJSEVENT event) const;
		void SetScript(const LNString &script, LNJSEVENT event);

	protected:

	private:
		LNINT GetSize() const;
		LNSTATUS Load(const LNRTContainer &container);
		LNSTATUS ParseJavaScript(char *pData, DWORD dataLength);
		LNSTATUS Update(LNRTContainer *container) const;
		LNSTATUS Update(void *start, void **end);
		LNJavaScriptBody * GetJavaScriptBody (void) const
		{ return (LNJavaScriptBody *)Body;}
		void PrepareToModify (void);
};

#endif
