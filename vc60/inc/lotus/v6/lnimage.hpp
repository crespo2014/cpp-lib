//====================================================================
//
// Module:		LNIMAGE.HPP
//
// Description:
//
//		Class library definition for the LNImageResource and related classes.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNIMAGE_HPP
#define LNIMAGE_HPP

enum LNIMAGEFORMAT
{
	LNIMAGEFORMAT_GIF,
	LNIMAGEFORMAT_JPEG,
	LNIMAGEFORMAT_BMP,
	LNIMAGEFORMAT_UNKNOWN
};
//
//	Class definition for LNImageResource.
//
class LNIMPEXPCL LNImageResource : public LNNote
{
public:

	LNBOOL GetAllowDesignRefreshToModify () const;
	virtual LNCLASSID GetClassID() const 
      {return LNCLASSID_LNIMAGERESOURCE;}
	LNBOOL GetAllowPublicAccessUsers() const;
	LNBOOL GetColorizeGrays() const;
	LNString GetComment() const;
	LNBOOL GetHideFromBrowsers() const;
	LNBOOL GetHideFromClients() const;
	LNString GetImageFilename() const;
	LNIMAGEFORMAT GetImageFormat() const;
	LNINT GetImagesAcross() const;
	LNINT GetImagesDown() const;
    LNString GetInheritsFromTemplateName () const;
	LNBOOL GetPropagateAllowDesignChange () const;

	LNSTATUS ExportImage(const LNString &directory = "", const LNString &filename = "");

	LNImageResource();
	LNImageResource( const LNImageResource &other );
	LNImageResource( const LNNote &other );

	LNSTATUS RefreshImage(const LNString &filename);

	LNSTATUS SetAlias (const LNString& alias);
    void SetAllowDesignRefreshToModify (LNBOOL allow);
	void SetAllowPublicAccessUsers(LNBOOL allow);

	LNSTATUS SetComment(const LNString &comment);
	void SetColorizeGrays(LNBOOL colorize);


	void SetHideFromBrowsers(LNBOOL hide);
	void SetHideFromClients(LNBOOL hide);
	LNSTATUS SetImagesAcross(LNINT num);
	LNSTATUS SetImagesDown(LNINT num);
    LNSTATUS SetInheritsFromTemplateName (const LNString &name);
    LNSTATUS SetName (const LNString& name);
    void SetPropagateAllowDesignChange (LNBOOL propagate);
	LNImageResource& operator=( const LNImageResource &other );
	LNImageResource& operator=( const LNNote &other );
	~LNImageResource();

protected:
private:

	LNImageResource( LNImageResourceBody *note );
	LNSTATUS GetRTImageResource(LNINT width, LNINT height, LNGraphic *rtImage) const;
	LNImageResource( LNDatabaseBody *db, NOTEID idnote );
	LNImageResource & operator=( LNImageResourceBody *note );

	void ValidateNoteType( const LNNote &note ) const; 
	void ValidateNoteType( const LNNoteBody *note ) const; 
	void ValidateNoteType( LNNOTETYPE notetype ) const; 

};
#endif	// LNIMAGE_HPP
