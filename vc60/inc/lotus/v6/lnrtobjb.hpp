//===========================================================================
//
// Module:  LNRTOBJB.HPP
//
// Description:
//
//		Class library definition for LNRTObjectBody and related classes.
//
//===========================================================================
//
// Copyright (c) 1997-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTOBJB_HPP
#define LNRTOBJB_HPP

//
//	Class definition for LNCompositeDataArray
//
class LNIMPEXPCL LNCompositeDataArray : public LNSmartPtr
{
public:
	LNCompositeDataArray();
	LNCompositeDataArray( const LNCompositeDataArray &other );
	LNCompositeDataArray( const LNRTContainer &container );
	LNCompositeDataArray& operator=( const LNCompositeDataArray &other );
	LNCompositeDataArray& operator=( const LNRTContainer &other );
	~LNCompositeDataArray();
	operator LNRTContainer() const;
	LNCompositeData& operator[](LNINT i) const;
	LNCompositeDataArray& operator <<(const LNCompositeData &data);
	LNCompositeDataArray& operator << (const LNCompositeDataArray &array);
	LNSTATUS Append(const LNCompositeData &data);
	LNSTATUS Append(const LNCompositeDataArray &array);
	LNSTATUS Delete(LNINT i);
	LNSTATUS DeleteAll();
	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNCOMPOSITEDATAARRAY; }
	WORD GetCDSignature(LNINT i) const;
	LNINT GetCount() const;
	LNSTATUS FindEntry( WORD signature, LNCompositeData *cd = 0, LNINT *index = 0) const;
	LNSTATUS Insert(LNINT i, const LNCompositeData &data);
	LNSTATUS Insert(LNINT i, const LNCompositeDataArray &array);
	LNSTATUS RefreshObject();
protected:
private:
	char* GetCompositeBuffer( LNINT *length = 0);
	LNCompositeDataArray(LNCompositeDataArrayBody *Body);
	LNCompositeDataArrayBody *GetCompositeDataArrayBody()
	{ return (LNCompositeDataArrayBody *)Body; }
};



#endif

