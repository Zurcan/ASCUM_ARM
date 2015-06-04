#ifndef _ARM_UART
#define _ARM_UART

struct	HW_UART{
   union{
   	int	RBR;
	int	THR;
	int	DLL;
   };
   union{
   	int	IER;
	int	DLM;
   };
   union{
   	int IIR;
	int FCR;
   };
   int	LCR;
   int	MCR;
   int	LSR;
   int	MSR;
   int	SCR;
};

#endif
