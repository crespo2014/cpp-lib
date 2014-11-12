#if !defined (NEUROFBDLL_DEF_FILE)
#define NEUROFBDLL_DEF_FILE

#ifdef NEUROFBDLL_EXPORTS
#define NEUROFBDLL_API _declspec(dllexport)
#else
#define NEUROFBDLL_API _declspec(dllimport)
#endif

typedef struct parametros
{
    long	m_Af_I_Eeg;    //filtro para IEEG
	long	m_Af_R_Eeg;
	long	m_Bf_I_Eeg;   //filtro para REEG
	long	m_Bf_R_Eeg;
	long    m_Af_Musculo;  //filtro de af para el musculo
	long	m_Crit_Comp_Burst;
	long	m_Duracion_Cond;
	double	m_Nivel_I_Eeg;
	double	m_Nivel_I_Musculo;
	double	m_Nivel_R_Eeg;
	long	m_Temperatura;
	long	m_Tiempo_Conteo_Burst;
}S_PARAMETROS;

typedef struct datos
{
	long minuto;
	long puntos;
	double prom_ieeg_min;
	double prom_reeg_min;
	double prom_iemg_min;
	double prom_temp_min;
}S_DATOS;

#endif