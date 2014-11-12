 ORG 800CH
 JMP INT_SERIE
 ORG 8003H
 RETI
 ORG 8009H
 RETI
 ORG 8300H
 MOV SP,#7
 ORL IE,#82H
 ORL IP,#02H
 SETB SM0
 SETB SM1
 SETB SM2; si SM2 esta activo solo interrumpe la rutina serie cuando entra un byte  con paridad forzada a uno
 CLR TI
 CLR RI
 SETB REN     ;INICIALIZAR SUBRUTINA SERIE
 SETB ES
 LOOP:
 JMP LOOP

 INT_SERIE:

 MOV C,RI    
 JNC SEE_TI
 CLR RI
 MOV A,SBUF
 CJNE A,#'A',NADA
 MOV SBUF,A
 RETI


 SEE_TI:
 MOV C,TI
 JNC NADA
 CLR TI
 NADA:
 RETI

