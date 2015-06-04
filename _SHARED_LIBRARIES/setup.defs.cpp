#include <string.h>
#include "setup.defs.h"

void TMenuItemToCompTMenuItem(compTMenuItem *nmi,uint32_t targetOffs,TARMMenuItem *mi){
	unsigned long typ=mi->type &0xFF;
  nmi->level				=mi->level;// Уровень подменю
  strncpy((char*)(nmi->name),(char*)(mi->name),32);
  if((typ==vProc)
         ||(typ==vAdjustProc)
         ||(typ==vSettingsProc)
         ||(typ==vSystemProc)
         ||((typ==vSub)&&(mi->target==0)))
       nmi->target			  =(uint32_t)(mi->target);
  else nmi->target			  =(uint32_t)(mi->target)-targetOffs;// адрес переменной в RAM
  nmi->units				=0;// адрес строки единиц измерения
  nmi->mask         =mi->mask;
  nmi->imin         =mi->rmin.imin;
  nmi->imax         =mi->rmax.imax;
  nmi->defaultVal   =mi->defaultVal;
  nmi->type				  =mi->type;// тип элемента меню
}  

void  TARMTableRecToCompTTableRec(compTTableRec *ctr, TARMTableRec *tr){
  ctr->TID=          tr->TID;
  strncpy((char*)(ctr->name),(char*)(tr->name),20);
  ctr->adr=          0;
  ctr->tableSize=    tr->tableSize;
  ctr->readAdr=      0;
  ctr->writeAdr=     0;
  ctr->dataSize=     tr->dataSize;
  ctr->flags=        tr->flags;
}
