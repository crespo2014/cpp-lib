TCP Proxy nivel 0.

La aplicaci�n es un ejecutable est�ndar de Linux que implementa un Proxy o puente de conexiones TCP/IP de nivel 0.
Se denomina nivel 0 porque no incorpora ning�n protocolo ni capa de comunicaci�n sobre la conexi�n establecida.
La funcionalidad b�sica consiste en esperar una conexi�n entrante sobre un puerto TCP/IP especifico y una vez conectado un cliente o maquina origen, se establece autom�ticamente una conexi�n con un servidor o maquina destino en un puerto especificado, estableciendo un puente de comunicaci�n entre las dos computadoras, toda la informaci�n que se reciba de la maquina origen ser� enviada �ntegramente a la maquina destino y viceversa, la informaci�n es enviada entre una maquina y otra tal cual se recibe, sin alteraciones ni procesamiento extra.
Cuando una de las dos conexiones es cerrada, autom�ticamente la otra se cierra y el puente establecido queda cerrado. 
La aplicaci�n adem�s incorpora un puerto de control o comando que permite configurar algunos par�metros en tiempo real, este puerto utilizara un protocolo en modo texto para permitir operar desde un telnet o aplicaci�n de consola.
Por el momento la �nica configuraci�n que se puede cambiar es la maquina de destino de las conexiones.

La aplicaci�n incorpora las siguientes restricciones, dejando abierta la posibilidad de incorporar m�s en un futuro.
Solo se establece la conexi�n con una maquina destino o servidor a la vez.
No se puede cambiar la maquina destino si hay alguna conexi�n puente abierta o activa.

CONFIGURACION.
La aplicaci�n dispondr� de un fichero de configuraci�n donde se especifican todos los par�metros necesarios para su correcto funcionamiento. A continuaci�n un ejemplo del fichero de configuraci�n.

[MAIN]
LOG_FILE = /export/home/ess33/appl/ess.version/log/exit9.log
LOG_LEVEL=8
LOG_CONSOLE = 1
TCP_CMD_PORT = 100

[TCP_FORWARD_PORT]
*:100;*:22
*:80;*:21

El fichero se compone de dos secciones, (MAIN y TCP_FORWARD_PORT).
En la secci�n MAIN se definen los siguientes par�metros.
LOG_FILE 		Fichero de trazas a utilizar, este fichero es utilizado por los desarrolladores para resolver incidencias en la aplicaci�n el contenido del mismo es responsabilidad del desarrollador de la aplicaci�n.

LOG_LEVEL		Indica el nivel que se utilizara para generar las trazas en el fichero, a menor nivel menos trazas.
LOG_CONSOLE 	Se especifica un valor de 1 cuando se desea que las trazas sean enviadas a la consola o salida est�ndar, a la vez que se env�an al fichero de trazas. El nivel de trazas es aplicado a esta salida tambi�n.
TCP_CMD_PORT 	Se especifica el puerto TCP/IP que utiliza la aplicaci�n para recibir y procesar los comandos definidos.

En la secci�n TCP_FORWARD_PORT se especifican los puertos TCP/IP por los que la aplicaci�n debe esperar la conexiones de la computadora cliente, el primer numero especifica el puerto origen o de escucha y el segundo el puerto destino.
Seg�n el ejemplo cualquier conexi�n que se establezca con el puerto 100 de la computadora donde se ejecute la aplicaci�n ser� autom�ticamente reconectado con el puerto 22 de la computadora que se haya especificado como destino (Para especificar una computadora como destino hay que utilizar el puerto de comando).


PUERTO O CANAL DE COMANDOS.
El canal de comando es el encargado de procesar los comandos definidos para la aplicaci�n, actualmente solo hay disponible un comando que consiste en modificar la maquina destino de la conexiones.  
Por cada comando que se ejecute se devolver� un mensaje con el siguiente formato.
OK - <mensaje> , las operaciones realizadas de forma satisfactoria
ERRXXX - <mensaje>, las operaciones que no se pueden llevar a cabo donde XXX es un c�digo de error num�rico de 3 d�gitos
Los c�digos de error devueltos por el puerto o canal de comando se definir�n seg�n se desarrolle la aplicaci�n.


