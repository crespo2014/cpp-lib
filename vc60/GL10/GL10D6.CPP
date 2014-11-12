 // gl10d6.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "gl10d6.h"
#include "gl10c10.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVariableInstanceDlg dialog


 CVariableInstanceDlg::CVariableInstanceDlg(CWnd* pParent /*=NULL*/)
 	: CDialog(CVariableInstanceDlg::IDD, pParent)
 {
 	//{{AFX_DATA_INIT(CVariableInstanceDlg)
 	m_minimo = 0.0f;
 	m_pendiente = 0.0f;
 	m_posx = 0.0f;
	m_posy = 0.0f;
 	m_posz = 0.0f;
 	m_rotcenx = 0.0f;
 	m_rotceny = 0.0f;
 	m_rotcenz = 0.0f;
 	m_rotvecx = 0.0f;
 	m_rotvecy = 0.0f;
 	m_rotvecz = 0.0f;
 	//}}AFX_DATA_INIT
}


void CVariableInstanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVariableInstanceDlg)
	DDX_Text(pDX, IDC_MINIMO, m_minimo);
	DDX_Text(pDX, IDC_PENDIENTE, m_pendiente);
	DDX_Text(pDX, IDC_POSX, m_posx);
	DDX_Text(pDX, IDC_POSY, m_posy);
	DDX_Text(pDX, IDC_POSZ, m_posz);
	DDX_Text(pDX, IDC_ROTCENX, m_rotcenx);
	DDX_Text(pDX, IDC_ROTCENY, m_rotceny);
	DDX_Text(pDX, IDC_ROTCENZ, m_rotcenz);
	DDX_Text(pDX, IDC_ROTVECTX, m_rotvecx);
	DDX_Text(pDX, IDC_ROTVECY, m_rotvecy);
	DDX_Text(pDX, IDC_ROTVECZ, m_rotvecz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVariableInstanceDlg, CDialog)
	//{{AFX_MSG_MAP(CVariableInstanceDlg)
	ON_BN_CLICKED(IDC_MODIFICAR, OnModificar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVariableInstanceDlg message handlers

void CVariableInstanceDlg::OnModificar() 
{
	m_OnRotar=!m_OnRotar;
	UpdateButton();
}

BOOL CVariableInstanceDlg::OnInitDialog() 
{
	if (m_Object->GetModifier()==MOD_ROT)
		m_OnRotar=true;
	else
		m_OnRotar=false;
	UpdateButton();

	float	rotvect[3];
	m_Object->GetRotationVector(rotvect);
	m_rotvecx=rotvect[0];
	m_rotvecy=rotvect[1];
	m_rotvecz=rotvect[2];
	m_Object->GetRotationPoint(rotvect);
	m_rotcenx=rotvect[0];
	m_rotceny=rotvect[1];
	m_rotcenz=rotvect[2];
	m_pendiente=m_Object->GetFactor();
	m_minimo=m_Object->GetMin();
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVariableInstanceDlg::UpdateButton()
{
	if (m_OnRotar)
		GetDlgItem(IDC_MODIFICAR)->SetWindowText("Rotar");
	else
		GetDlgItem(IDC_MODIFICAR)->SetWindowText("Trasladar");
}

void CVariableInstanceDlg::OnOK() 
{
	UpdateData(true);
	float	temp[3];
	temp[0]=m_posx;temp[1]=m_posy;temp[2]=m_posz;
	m_Object->SetPosition(temp);
	temp[0]=m_rotcenx;temp[1]=m_rotceny;temp[2]=m_rotcenz;
	m_Object->SetRotationPoint(temp);
	temp[0]=m_rotvecx;temp[1]=m_rotvecy;temp[2]=m_rotvecz;
	m_Object->SetRotationVector(temp);
	if (m_OnRotar)
		m_Object->SetModifier(MOD_ROT);
	else
		m_Object->SetModifier(MOD_POS);
	m_Object->SetMin(m_minimo);
	CDialog::OnOK();
}
