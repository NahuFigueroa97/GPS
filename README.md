Biblioteca liviana para la lectura de un GPS NEO-6M

El módulo GPS en su modelo GY-GPS6MV2 viene con un módulo de serie U-Blox NEO 6M equipado en el PCB, una EEPROM con configuración de fábrica, una pila de botón para mantener los datos de configuración en la memoria EEPROM, un indicador LED y una antena cerámica. También posee los pines o conectores Vcc, Rx, Tx y Gnd por el que se puede conectar a algún microcontrolador mediante una interfaz serial. Para que nuestro módulo GPS funcione a la perfección se recomienda hacer las pruebas en un ambiente abierto o cercano a la ventana para una correcta recepción de la señal. Los datos que recibimos en nuestro módulo GPS siguen el protocolo NMEA (siglas de National Marine Electronics Asociation), las cuales son sentencias estándares para la recepción de datos GPS. Una de ellas y la más usada son las sentencias $GPRMC, las cuales tienen la siguiente estructura:

$GPRMC,044235.000,A,4322.0289,N,00824.5210,W,0.39,65.46,020615,,,A*44

Donde si analizamos la trama de este ejemplo y basándose en el protocolo NMEA, podríamos determinar las siguientes variables:

    044235.000 representa la hora GMT (04:42:35)
    “A” es la indicación de que el dato de posición está fijado y es correcto. “V” sería no válido
    4322.0289 representa la longitud (43º 22.0289´)
    N representa el Norte
    00824.5210 representa la latitud (8º 24.5210´)
    W representa el Oeste
    0.39 representa la velocidad en nudos
    65.46 representa la orientación en grados
    020615 representa la fecha (2 de Junio del 2015)
