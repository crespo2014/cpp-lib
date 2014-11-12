//===========================================================================
//
// Module:  LNMETAFL.HPP
//
// Description:
//
//		Class library definition for the LNMetafile, LNMetafileBody and
//		the associated classes for CGM, PM, WIN and MAC
//
//===========================================================================
//
// Copyright (c) 1996-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================


#ifndef LNMETAFILE_HPP
#define LNMETAFILE_HPP

enum LNMETAFILETYPE
{
	LNMETAFILETYPE_CGM = 0,
	LNMETAFILETYPE_PM,
	LNMETAFILETYPE_MAC,
	LNMETAFILETYPE_WIN
};



/* Notes doesn't provide values for these first two */
typedef SWORD LNWINMAPPINGMODE;

typedef SWORD LNPMMAPPINGMODE;

typedef SWORD LNCGMMAPPINGMODE;

#define LNCGMMAPPINGMODE_ABSTRACT	 CGM_MAPMODE_ABSTRACT
#define LNCGMMAPPINGMODE_METRIC		 CGM_MAPMODE_METRIC



class LNIMPEXPCL LNMetafile : public LNRTObject
{
public:
	
	LNMetafile();
	LNMetafile(const LNRTObject &object);
	LNMetafile(const LNMetafile &metafile);

	~LNMetafile();

	LNMetafile&			operator=(const LNRTObject &object);
	LNMetafile&			operator=(const LNMetafile &metafile);

	LNMETAFILETYPE		GetMetafileType() const;

	virtual LNCLASSID	GetClassID() const { return LNCLASSID_LNMETAFILE; };

protected:

	virtual void		ValidateRTType(const LNRTObject &other) const;
	virtual void		ValidateRTType(const LNRTObjectBody *other) const;

private:
};

/*	*******************************************************************
	Begin Windows metafile and segment
	*******************************************************************		*/

class LNIMPEXPCL LNWinMetafile : public LNMetafile
{

public:
	LNWinMetafile();
	LNWinMetafile(const LNRTObject &object);
	LNWinMetafile(const LNWinMetafile &metafile);

	~LNWinMetafile();

	LNWinMetafile&			operator=(const LNRTObject &object);
	LNWinMetafile&			operator=(const LNWinMetafile &metafile);

	LNWinMetafileSegment&	operator[](LNINT pos) const;

	virtual LNCLASSID		GetClassID() const { return LNCLASSID_LNWINMETAFILE; };

	LNINT					GetDrawingHeight() const;
	
	LNINT					GetDrawingWidth() const;

	LNWINMAPPINGMODE		GetMappingMode() const;

	LNINT					GetMetafileSize() const;

	LNINT					GetOriginalHeight() const;
	
	LNINT					GetOriginalWidth() const;

	LNINT					GetSegmentCount() const;

protected:
	
	virtual void			ValidateRTType(const LNRTObject &other) const;
	virtual void			ValidateRTType(const LNRTObjectBody *other) const;

private:
	
	LNWinMetafileBody		*GetWinMetafileBody() const;
};


class LNIMPEXPCL LNWinMetafileSegment : public LNRTObject
{
public:
	
	LNWinMetafileSegment();
	LNWinMetafileSegment(const LNRTObject &obj);
	LNWinMetafileSegment(const LNWinMetafileSegment &obj);

	~LNWinMetafileSegment();

	LNWinMetafileSegment&		operator=(const LNRTObject &object);
	LNWinMetafileSegment&		operator=(const LNWinMetafileSegment &object);

	LNSTATUS					GetMetafile(LNWinMetafile *metafile) const;

	virtual LNCLASSID			GetClassID() const { return LNCLASSID_LNWINMETAFILESEGMENT; };

	LNINT						GetDataSize() const;

	LNSTATUS					Read(LNINT bytesToRead, void *retBuffer, LNINT offset = 0);

protected:
	
	LNINT						GetSegmentSize() const;

	virtual void				ValidateRTType(const LNRTObject &other) const;
	virtual void				ValidateRTType(const LNRTObjectBody *other) const;

private:
	
	LNWinMetafileSegmentBody	*GetWinMetafileSegmentBody() const;
};


class LNIMPEXPCL LNPMMetafile : public LNMetafile
{

public:

	LNPMMetafile();
	LNPMMetafile(const LNRTObject &object);
	LNPMMetafile(const LNPMMetafile &metafile);

	~LNPMMetafile();

	LNPMMetafile&			operator=(const LNRTObject &object);
	LNPMMetafile&			operator=(const LNPMMetafile &metafile);
	
	LNPMMetafileSegment&	operator[](LNINT pos) const;

	virtual LNCLASSID		GetClassID() const { return LNCLASSID_LNPMMETAFILE; };

	LNINT					GetDrawingHeight() const;
	
	LNINT					GetDrawingWidth() const;

	LNPMMAPPINGMODE			GetMappingMode() const;

	LNINT					GetMetafileSize() const;

	LNINT					GetOriginalHeight() const;
	
	LNINT					GetOriginalWidth() const;

	LNINT					GetSegmentCount() const;


protected:
	
	virtual void			ValidateRTType(const LNRTObject &other) const;
	virtual void			ValidateRTType(const LNRTObjectBody *other) const;

private:
	
	LNPMMetafileBody		*GetPMMetafileBody() const;
};


class LNIMPEXPCL LNPMMetafileSegment : public LNRTObject
{
public:

	LNPMMetafileSegment();
	LNPMMetafileSegment(const LNRTObject &obj);
	LNPMMetafileSegment(const LNPMMetafileSegment &obj);

	~LNPMMetafileSegment();

	LNPMMetafileSegment&	operator=(const LNRTObject &object);
	LNPMMetafileSegment&	operator=(const LNPMMetafileSegment &object);

	LNSTATUS				GetMetafile(LNPMMetafile *metafile) const;

	virtual LNCLASSID		GetClassID() const { return LNCLASSID_LNPMMETAFILESEGMENT; };

	LNINT					GetDataSize() const;

	LNSTATUS				Read(LNINT bytesToRead, void *retBuffer, LNINT offset = 0);

protected:

	LNINT					GetSegmentSize() const;

	virtual void			ValidateRTType(const LNRTObject &other) const;
	virtual void			ValidateRTType(const LNRTObjectBody *other) const;

private:
	
	LNPMMetafileSegmentBody	*GetPMMetafileSegmentBody() const;
};



/*	*************************************************************************
	Begin LNMacMetafile and LNMacMetafileSegment classes and bodies
	*************************************************************************	*/

class LNIMPEXPCL LNMacMetafile : public LNMetafile
{

public:

	LNMacMetafile();
	LNMacMetafile(const LNRTObject &object);
	LNMacMetafile(const LNMacMetafile &metafile);

	~LNMacMetafile();

	LNMacMetafile&			operator=(const LNRTObject &object);
	LNMacMetafile&			operator=(const LNMacMetafile &metafile);
	
	LNMacMetafileSegment&	operator[](LNINT pos) const;

	virtual LNCLASSID		GetClassID() const { return LNCLASSID_LNMACMETAFILE; };

	LNINT					GetMetafileSize() const;

	LNINT					GetOriginalHeight() const;
	LNINT					GetOriginalWidth() const;

	LNINT					GetSegmentCount() const;

protected:
	
	virtual void			ValidateRTType(const LNRTObject &other) const;
	virtual void			ValidateRTType(const LNRTObjectBody *other) const;

private:
	
	LNMacMetafileBody		*GetMacMetafileBody() const;
};
 

class LNIMPEXPCL LNMacMetafileSegment : public LNRTObject
{
public:
	
	LNMacMetafileSegment();
	LNMacMetafileSegment(const LNRTObject &obj);
	LNMacMetafileSegment(const LNMacMetafileSegment &obj);

	~LNMacMetafileSegment();

	LNMacMetafileSegment&		operator=(const LNRTObject &object);
	LNMacMetafileSegment&		operator=(const LNMacMetafileSegment &object);

	LNSTATUS					GetMetafile(LNMacMetafile *metafile) const;

	virtual LNCLASSID			GetClassID() const { return LNCLASSID_LNMACMETAFILESEGMENT; };

	LNINT						GetDataSize() const;

	LNSTATUS					Read(LNINT bytesToRead, void *retBuffer, LNINT offset = 0);

protected:
	
	LNINT						GetSegmentSize() const;

	virtual void				ValidateRTType(const LNRTObject &other) const;
	virtual void				ValidateRTType(const LNRTObjectBody *other) const;

private:
	
	LNMacMetafileSegmentBody	*GetMacMetafileSegmentBody() const;
};




class LNIMPEXPCL LNCGMMetafile : public LNMetafile
{
public:

	LNCGMMetafile();
	LNCGMMetafile(const LNRTObject &object);
	LNCGMMetafile(const LNCGMMetafile &metafile);

	~LNCGMMetafile();

	LNCGMMetafile&		operator=(const LNRTObject &object);
	LNCGMMetafile&		operator=(const LNCGMMetafile &metafile);

	virtual LNCLASSID	GetClassID() const { return LNCLASSID_LNCGMMETAFILE; };

	LNINT				GetDrawingHeight() const;
	
	LNINT				GetDrawingWidth() const;

	LNCGMMAPPINGMODE	GetMappingMode() const;

	LNINT				GetOriginalHeight() const;
	
	LNINT				GetOriginalWidth() const;

protected:
	
	virtual void		ValidateRTType(const LNRTObject &other) const;
	virtual void		ValidateRTType(const LNRTObjectBody *other) const;

private:
	
	LNCGMMetafileBody	*GetCGMMetafileBody() const;
};


#endif

