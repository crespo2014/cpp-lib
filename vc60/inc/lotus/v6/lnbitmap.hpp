//===========================================================================
//
// Module:  LNBITMAP.HPP
//
// Description:
//
//		Class library definition for the LNRTBitmap and related classes.
//
//===========================================================================
//
// Copyright (c) 1997-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNBITMAP_HPP
#define LNBITMAP_HPP


enum LNBITMAPTYPE
{
	LNBITMAPTYPE_MONOCHROME,
	LNBITMAPTYPE_GRAY_SCALE,
	LNBITMAPTYPE_8_BIT_COLOR,
	LNBITMAPTYPE_16_BIT_COLOR
};

enum LNBITMAPCOLORVALUE
{
	LNBITMAPCOLORVALUE_RED = CT_RED_OFFSET,
	LNBITMAPCOLORVALUE_GREEN = CT_GREEN_OFFSET,
	LNBITMAPCOLORVALUE_BLUE = CT_BLUE_OFFSET
};


class LNIMPEXPCL LNBitmap : public LNRTObject
{

public:

	LNBitmap();
	LNBitmap(const LNRTObject &object);
	LNBitmap(const LNBitmap &bitmap);

	~LNBitmap();

	LNBitmap&				operator=(const LNRTObject &object);
	LNBitmap&				operator=(const LNBitmap &bitmap);

	LNBitmapSegment		    operator[](LNINT pos) const;
	
	LNINT					GetBitsPerPixel() const;

	virtual LNCLASSID		GetClassID() const { return LNCLASSID_LNBITMAP; };

	LNSTATUS				GetColorTable(LNBitmapColorTable *colorTable) const;

	LNINT					GetDestinationHeight() const;
	
	LNINT					GetDestinationWidth() const;

	LNINT					GetHeight() const;

	LNSTATUS				GetPatternTable(LNBitmapPatternTable *patternTable) const;

	LNINT					GetSegmentCount() const;

	LNSTATUS				GetTransparencyTable(LNBitmapTransparencyTable *table) const;

	LNINT					GetWidth() const;

protected:

	virtual void			ValidateRTType(const LNRTObject &other) const;
	virtual void			ValidateRTType(const LNRTObjectBody *other) const;

private:

	LNBitmapBody			*GetBitmapBody() const;
};


class LNIMPEXPCL LNBitmapSegment : public LNRTObject
{
public:

	LNBitmapSegment();
	LNBitmapSegment(const LNRTObject &object);
	LNBitmapSegment(const LNBitmapSegment &segment);

	~LNBitmapSegment();

	LNBitmapSegment&	operator=(const LNRTObject &object);
	LNBitmapSegment&	operator=(const LNBitmapSegment &segment);

	LNSTATUS			GetBitmap(LNBitmap* bitmap) const;
	
	virtual LNCLASSID	GetClassID() const { return LNCLASSID_LNBITMAPSEGMENT; };

	LNINT				GetDataSize() const;

	LNINT				GetScanlineCount() const;

	LNSTATUS			Read(LNINT bytesToRead, void *buf, LNINT offset = 0);

protected:

	virtual void		ValidateRTType(const LNRTObject &other) const;
	virtual void		ValidateRTType(const LNRTObjectBody *other) const;

private:

	LNBitmapSegmentBody	*GetBitmapSegmentBody() const;

};


class LNIMPEXPCL LNBitmapColorTable : public LNRTObject
{
public:
	
	LNBitmapColorTable();
	LNBitmapColorTable(const LNRTObject &object);
	LNBitmapColorTable(const LNBitmapColorTable &table);

	~LNBitmapColorTable();

	LNBitmapColorTable&		operator=(const LNRTObject &object);
	LNBitmapColorTable&		operator=(const LNBitmapColorTable &table);

	LNINT					operator()(LNINT entry, LNBITMAPCOLORVALUE color) const;

	LNSTATUS				GetBitmap(LNBitmap* bitmap) const;

	virtual LNCLASSID		GetClassID() const { return LNCLASSID_LNBITMAPCOLORTABLE; };

	LNINT					GetCount();
	
	LNSTATUS				Read(LNINT bytesToRead, void *buffer, LNINT offset = 0);

protected:

	virtual void			ValidateRTType(const LNRTObject &other) const;
	virtual void			ValidateRTType(const LNRTObjectBody *other) const;

private:

	LNBitmapColorTableBody	*GetBitmapColorTableBody() const;

};


class LNIMPEXPCL LNBitmapPatternTable : public LNRTObject
{
public:

	LNBitmapPatternTable();
	LNBitmapPatternTable(const LNRTObject &object);
	LNBitmapPatternTable(const LNBitmapPatternTable &table);

	~LNBitmapPatternTable();

	LNBitmapPatternTable&	operator=(const LNRTObject &object);
	LNBitmapPatternTable&	operator=(const LNBitmapPatternTable &table);

	LNINT					operator()(LNINT pattern, LNINT element, LNBITMAPCOLORVALUE color) const;

	LNSTATUS				GetBitmap(LNBitmap* bitmap) const;

	virtual LNCLASSID		GetClassID() const { return LNCLASSID_LNBITMAPPATTERNTABLE; };

	LNINT					GetCount() const;
	
	LNSTATUS				Read(LNINT bytesToRead, void *buffer, LNINT offset = 0);

protected:

	virtual void			ValidateRTType(const LNRTObject &other) const;
	virtual void			ValidateRTType(const LNRTObjectBody *other) const;

private:

	LNBitmapPatternTableBody	*GetBitmapPatternTableBody() const;

};


class LNIMPEXPCL LNBitmapTransparencyTable : public LNRTObject
{
public:

	LNBitmapTransparencyTable();
	LNBitmapTransparencyTable(const LNRTObject &object);
	LNBitmapTransparencyTable(const LNBitmapTransparencyTable &table);

	~LNBitmapTransparencyTable();

	LNBitmapTransparencyTable&	operator=(const LNRTObject &object);
	LNBitmapTransparencyTable&	operator=(const LNBitmapTransparencyTable &table);
	
	LNINT						operator()(LNINT entry, LNBITMAPCOLORVALUE color) const;

	LNSTATUS					GetBitmap(LNBitmap* bitmap) const;

	virtual LNCLASSID			GetClassID() const { return LNCLASSID_LNBITMAPTRANSPARENCYTABLE; };

	LNINT						GetCount() const;
	
	LNSTATUS					Read(LNINT bytesToRead, void *buffer, LNINT offset = 0);

protected:
		
	virtual void				ValidateRTType(const LNRTObject &other) const;
	virtual void				ValidateRTType(const LNRTObjectBody *other) const;

private:

	LNBitmapTransparencyTableBody	*GetBitmapTransparencyTableBody() const;

};


#endif

