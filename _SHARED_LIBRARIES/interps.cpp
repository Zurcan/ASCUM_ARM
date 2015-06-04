#include <string.h>
#include "interps.h"

void  toDataRegistryItem(DataRegistryItem_RM_t *ctr, DataRegistryItem_ARM_t *tr){
  strncpy((char*)(ctr->name),(char*)(tr->name),20);
  ctr->TID=          tr->TID;
  ctr->_reserv1=     0;
  ctr->tableSize=    tr->tableSize;
  ctr->_reserv2=     0;
  ctr->_reserv3=     0;
  ctr->dataSize=     tr->dataSize;//dataSize;
  ctr->flags=        tr->flags;
  if((tr->flags & ff__PurelyNative)==0){
    ctr->tableSize=  sizeof(InterpretationItem_RM_t)*(tr->tableSize/sizeof(InterpretationItem_ARM_t));
  }
}

void toInterpretationItem        (InterpretationItem_RM_t *nmi,unsigned long targetOffs,InterpretationItem_ARM_t *mi){
	unsigned long typ=mi->type &0xFF;
  nmi->level				=mi->level;// Уровень подменю
  strncpy((char*)(nmi->name),(char*)(mi->name),32);
  if((typ==vProc)
         ||(typ==vAdjustProc)
         ||(typ==vSettingsProc)
         ||(typ==vSystemProc)
         ||(typ==vDivider)
         ||(typ==vSub)
  )
       nmi->target			  =(uint32_t)(mi->target);
  else nmi->target			  =(uint32_t)(mi->target)-targetOffs;// адрес переменной в RAM
  nmi->hintCode		  =0;// адрес строки единиц измерения
  nmi->mask         =mi->mask;
  nmi->imin         =mi->rmin.imin;
  nmi->imax         =mi->rmax.imax;
  nmi->defaultVal   =mi->defaultVal;
  nmi->type				  =mi->type;// тип элемента меню
}  

