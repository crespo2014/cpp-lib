TCP Proxy nivel 0.

La aplicación es un ejecutable estándar de Linux que implementa un Proxy o puente de conexiones TCP/IP de nivel 0.
Se denomina nivel 0 porque no incorpora ningún protocolo ni capa de comunicación sobre la conexión establecida.
La funcionalidad básica consiste en esperar una conexión entrante sobre un puerto TCP/IP especifico y una vez conectado un cliente o maquina origen, se establece automáticamente una conexión con un servidor o maquina destino en un puerto especificado, estableciendo un puente de comunicación entre las dos computadoras, toda la información que se reciba de la maquina origen será enviada íntegramente a la maquina destino y viceversa, la información es enviada entre una maquina y otra tal cual se recibe, sin alteraciones ni procesamiento extra.
Cuando una de las dos conexiones es cerrada, automáticamente la otra se cierra y el puente establecido queda cerrado. 
La aplicación además incorpora un puerto de control o comando que permite configurar algunos parámetros en tiempo real, este puerto utilizara un protocolo en modo texto para permitir operar desde un telnet o aplicación de consola.
Por el momento la única configuración que se puede cambiar es la maquina de destino de las conexiones.

La aplicación incorpora las siguientes restricciones, dejando abierta la posibilidad de incorporar más en un futuro.
Solo se establece la conexión con una maquina destino o servidor a la vez.
No se puede cambiar la maquina destino si hay alguna conexión puente abierta o activa.

CONFIGURACION.
La aplicación dispondrá de un fichero de configuración donde se especifican todos los parámetros necesarios para su correcto funcionamiento. A continuación un ejemplo del fichero de configuración.

[MAIN]
LOG_FILE = /export/home/ess33/appl/ess.version/log/exit9.log
LOG_LEVEL=8
LOG_CONSOLE = 1
TCP_CMD_PORT = 100

[TCP_FORWARD_PORT]
*:100;*:22
*:80;*:21

El fichero se compone de dos secciones, (MAIN y TCP_FORWARD_PORT).
En la sección MAIN se definen los siguientes parámetros.
LOG_FILE 		Fichero de trazas a utilizar, este fichero es utilizado por los desarrolladores para resolver incidencias en la aplicación el contenido del mismo es responsabilidad del desarrollador de la aplicación.

LOG_LEVEL		Indica el nivel que se utilizara para generar las trazas en el fichero, a menor nivel menos trazas.
LOG_CONSOLE 	Se especifica un valor de 1 cuando se desea que las trazas sean enviadas a la consola o salida estándar, a la vez que se envían al fichero de trazas. El nivel de trazas es aplicado a esta salida también.
TCP_CMD_PORT 	Se especifica el puerto TCP/IP que utiliza la aplicación para recibir y procesar los comandos definidos.

En la sección TCP_FORWARD_PORT se especifican los puertos TCP/IP por los que la aplicación debe esperar la conexiones de la computadora cliente, el primer numero especifica el puerto origen o de escucha y el segundo el puerto destino.
Según el ejemplo cualquier conexión que se establezca con el puerto 100 de la computadora donde se ejecute la aplicación será automáticamente reconectado con el puerto 22 de la computadora que se haya especificado como destino (Para especificar una computadora como destino hay que utilizar el puerto de comando).


PUERTO O CANAL DE COMANDOS.
El canal de comando es el encargado de procesar los comandos definidos para la aplicación, actualmente solo hay disponible un comando que consiste en modificar la maquina destino de la conexiones.  
Por cada comando que se ejecute se devolverá un mensaje con el siguiente formato.
OK - <mensaje> , las operaciones realizadas de forma satisfactoria
ERRXXX - <mensaje>, las operaciones que no se pueden llevar a cabo donde XXX es un código de error numérico de 3 dígitos
Los códigos de error devueltos por el puerto o canal de comando se definirán según se desarrolle la aplicación.


