# proyecto-seminario-documentacion

 documentacion - proyecto - seminiario

REQUERIMIENTOS 

objetivos principal

monitorear en tiempo real el voltaje de las baterias  para automatizar  las sig. decisiones

    1. si la bateria tiene un valor de voltajes que se aproxime a disminuir por debajo de 3.2 v - cortar cualuier proceso de uso o consumo donde la bateria es quien suministra energia y se activara AUTOMATICAMENTE el MODO carga de BATERIAS

2. mostrar una grafica en tiempoo real sobre el proceso de carga de las baterias dicha graifica debe mostrar el compartimiento (aumento en su normalidad) del voltaje del banco de baterias
3. presentar un boton a nivel de interfaz junto a la grafica que permita detener el proceso de carga de la bateria de forma manual (boton tambien existira en fisico en la placa)
4. si por algun motivo la lectura de voltaje del banco de bateria disminuye por debajo de 3.2v  el sistema automaticamente se debe bloquear (parado de emergencia ) y este solo se debe poder activar de forma manual (lo cual indica que se remplazo el banco de baterias o bien se reviso el motivo por el cual el valor disminuyo y se soluciono de alguna otra forma).
5. si las baterias no estan en uso (suministrando la energia para otros dispositivos /  las baterias se estan cargando ) y su nivel de voltaje, Alcanza el voltaje maximo. el proceso de carga debe detenerse. pero para activarse debe disminuir un % considerable para activar nuevamente la carga de forma automatica
6. REQUIRIMIENTO ORIGINAL. monitorear en tiempo real el flujo constante de la corriente domiciliar y si esta es interrumpida valorar si el banco de baterias esta en estado optimo para activar automaticamente su uso


* ***nuevos requisitos***

2. si el flujo de la corriente domiciliar es constante  PERO el banco de baterias tiene un vaoltaje, un porcentaje % (DEFINIR UN NUMERO AQUI) **OPTIMO**  y la  ORDEN ACTIVAR ALIMENTACION POR BATERIAS ES **verdadera**   (EL USUARIO MEDIANTE LA APLICACION DECIDIO ACTIVAR EL MODO SUMINISTRO DE ENERGIA POR BATERIAS) entonces el sistema deja de cargar la bateria y   realiza lo sig:
   1. el sistema cortara la entrada de sumistro de corriente domiciliar
   2. el sistema activara la alimentacion de corriente con baterias
3.
