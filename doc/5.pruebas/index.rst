
.. raw:: latex

    \newpage


Pruebas
=======
Con el objetivo de probar el modelo se ha diseñado un experimento que permite
contrastar textos generados por dos sistemas diferentes de traducción automática
para evaluar la distancia con respecto al texto original.

El experimento consiste en comparar un conjunto de grafos UNL
(convertidos a grafos cuyos nodos son *synsets* de WordNet) extraídos de un 
documento perteneciente al Forum Universal de las Culturas 2004 [#]_ celebrado
en Barcelona, con los grafos resultantes de traducir estas oraciones al
español y de vuelta al inglés utilizando software de traducción disponible
en internet.

.. [#] Fòrum Universal de les Cultures. 
   http://www.barcelona2004.org/www.barcelona2004.org/cat/index.html
   (accedida en junio de 2015)
   
   
.. _fig-experiment-layout:
.. graphviz::
   :caption: Metodología elaborada para obtener el conjunto de datos utilizado en la experimentación del modelo. Se muestra la obtención de la distancia entre el grafo original y el obtenido a partir de la traducción de Yandex.

   digraph foo {
   
    rankdir=LR
    
    A[label="Oración\n[inglés]", shape=box]
    B[label="Oración\n[español]", shape=box]
    C[label="Oración Google\n[inglés]", shape=box]
    D[label="Oración Yandex\n[inglés]", shape=box]    
    
    UNL[label="Grafo UNL"]
    WordNet[label="Grafo WordNet"]
    
    WNYandex[label="Grafo Yandex\nWordNet"]
    
    {rank=same C,D, WNYandex}
    {rank=same A,UNL,WordNet}
    
    A -> B [label="Systrans"]
    B -> C [label="Google"]
    B -> D [label="Yandex"]
    
    A -> UNL [label="Spanish\nLanguage Centre"]
    UNL -> WordNet [label="autor"]
    
    D -> WNYandex [label="autor"]
    
    DistYandex[label="d(ori, yandex)"]
        
    model [label="Modelo propuesto", shape=diamond, style=filled]
    {rank=same B,model, DistYandex}
    
    
    WordNet -> model
    WNYandex -> model    
    model -> DistYandex
    
    # Invisible to fit layout
    inv1[shape=none, label=""]
    inv2[shape=none, label=""]
    {rank=same B,model, inv1, inv2, DistYandex}
    B -> inv1 -> inv2 -> model [style=invis]
   }

En la :num:`figura #fig-experiment-layout` se muestra el proceso seguido para cada
una de las oraciones seleccionadas y los actores que intervienen en la generación de
los recursos; como ya se indicó en la :num:`sección #planteamiento-problema`, al
carecer de tiempo y medios para generar un conjunto de datos adecuado, ha sido 
necesario crearlos *ex profeso* para este trabajo [#]_. Se asume así que los resultados
deben ser revisados con un enfoque más científico.

.. [#] En el :num:`apéndice #appendix-data` se encuentran disponibles todos los datos
   utilizado para la realización del experimento.


Metodología
-----------
Ilustraremos la metodología mostrada en la :num:`figura #fig-experiment-layout` con
el ejemplo número 7 del *dataset* que hemos elaborado. El procedimiento se detalla
en los siguientes apartados.

Datos de partida: oración y grafo UNL
`````````````````````````````````````
En el documento al que hemos hecho referencia anteriormente tenemos disponibles las
oraciones en inglés y su transcripción como grafo UNL (:num:`listado #code-example-unl-7`).

Ejemplo 7
  : *Sustainable Development satisfies the needs of the present without compromising future generations' abilities to satisfy theirs, and is based on the natural environment's capacity to provide for humankind.*
  
  
.. code-block:: unl
   :caption: Codificación UNL original de la oración ejemplo 7.
   :name: code-example-unl-7
   
   [S]
   aoj:01(rest(icl>be).@entry,:02)
   mod:02(development(icl>event).@def.@entry,sustainable(mod<thing))
   met:01(rest(icl>be).@entry,capacity(icl>ability).@def)
   mod:01(capacity(icl>ability).@def,environment.@def)
   mod:01(environment.@def,natural(mod<thing))
   obj:01(capacity(icl>ability).@def,provide_for)
   ben:01(provide_for,humankind.@def)
   and(:01.@entry,:03)
   agt:03(satisfy(icl>do):01.@entry,:02)
   obj:03(satisfy(icl>do):01.@entry,need(icl<abstract thing):01.@def.@pl)
   mod:03(need(icl<abstract thing):01.@def.@pl,present(icl>time).@def)
   man:03(satisfy(icl>do):01.@entry,without(icl>how))
   obj:03(without(icl>how),compromise(icl>do))
   obj:03(compromise(icl>do),ability)
   mod:03(ability,:04)
   mod:04(generation(icl>human group).@def.@entry.@pl,future(mod<thing))
   obj:03(ability,satisfy(icl>do):02)
   obj:03(satisfy(icl>do):02,need(icl<abstract thing):02.@def.@pl)
   mod:03(need(icl<abstract thing):02.@def.@pl,:04)
   [/S]
   

Traducción a idioma intermedio
``````````````````````````````
El siguiente paso consiste en traducir la oración original a un segundo idioma que
servirá de punto de partida para las traducciones generadas por los sistemas que vamos
a comparar.

En nuestro caso el idioma intermedio será el español, y la traducción la generaremos
utilizando Systrans [#]_.

.. [#] SYSTRANet – Online translation software and tools – Dictionary
   http://www.systranet.com/dictionary/english-spanish (accedido en junio
   de 2015)
     
  **Systrans**: El desarrollo sostenible satisface las necesidades del presente sin las capacidades de las futuras generaciones de compromiso de satisfacer el suyo, y se basa en la capacidad del ambiente natural de prever humanidad.
  

Traducción al idioma original
`````````````````````````````
La oración en español es traducida nuevamente al idioma de partida (inglés) utilizando
dos sistemas de traducción automática: Google [#]_ y Yandex [#]_, con los que obtenemos
los siguientes resultados:

  **Google**: *Sustainable development meets the needs of the present without the ability of future generations to meet his commitment, and is based on the ability of the natural environment to provide for humanity.*
  
  **Yandex**: *Sustainable development meets the needs of the present without the capabilities of future generations of commitment to meet yours, and is based on the ability of the natural environment to provide for humanity.*
  
.. [#] Traductor de Google. https://translate.google.es (accedido en junio de 2015)

.. [#] Yandex.Translate. https://translate.yandex.com/ (accedido en junio de 2015)

Leyendo las traducciones podemos observar cómo las traducciones no son idénticas entre
ellas y se han alejado del contenido semántico original. Nuestro modelo trabaja conç
estos datos para obtener una medida de distancia entre las traducciones y la oración
original.

Identificación de los *synsets* de WordNet
``````````````````````````````````````````
Como hemos indicado, la ontología UNL no está disponible, por lo que la manera
de utilizar las medidas de distancia que hemos expuesto en el estado del arte debe
ser a través de la jerarquía de conceptos de WordNet. Para ello hemos tenido que
identificar los conceptos expresados por las UWs con un *synset* concreto en WordNet.

Este proceso se ha realizado manualmente y, con total seguridad, introduce una primera
desviación semántica entre la oración original y el grafo base para la comparación; no
obstante, siempre que aparecen los mismos conceptos se tiene la precaución de
sustituirlos por el mismo *synset*.

De este modo, el grafo UNL original, se convierte en el grafo mostrado en el 
:num:`listado #code-example-original-7` que también se muestra en la
:num:`figura #sample07-original`.

.. code-block:: unl
   :caption: Codificación utilizando los *synsets* de WordNet de la oración ejemplo 7.
   :name: code-example-original-7
   
   {unl}
   aoj(rest%2:42:12::, development%1:22:02::)
   mod(development%1:22:02::, sustainable%3:01:00::)
   met(rest%2:42:12::, capacity%1:07:00::)
   mod(capacity%1:07:00::, environment%1:15:00::)
   mod(environment%1:15:00::, natural%3:00:02::)
   obj(capacity%1:07:00::, provide%2:34:00::)
   ben(provide%2:34:00::, humankind%1:05:00::)
   and(rest%2:42:12::, satisfy%2:34:01::)
   agt(satisfy%2:34:01::, development%1:22:02::)
   obj(satisfy%2:34:01::, need%1:17:00::)
   mod(need%1:17:00::, present%3:00:01::)
   man(satisfy%2:34:01::, compromise%2:32:03::)
   obj(compromise%2:32:03::, ability%1:07:00::)
   mod(ability%1:07:00::, generation%1:14:01::)
   mod(generation%1:14:01::, future%3:00:00::)
   obj(ability%1:07:00::, 02%satisfy%2:34:01::)
   obj(02%satisfy%2:34:01::, 02%need%1:17:00::)
   mod(02%need%1:17:00::, generation%1:14:01::)
   {/unl}


.. figure:: ../../data/samples/sample07_original.png
   :name: sample07-original
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente al ejemplo #7 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).

La conversión de los conceptos UNL expresados en las UWs en los *synsets* de WordNet
se ha realizado utilizando el buscador accesible en la página web de la Universidad
de Princeton [#]_, de entre todas las opciones proporcionadas para cada palabra se
ha seleccionado el concepto más próximo dentro de la categoría gramatical adecuada.

.. [#] WordNet Search - 3.1. http://wordnetweb.princeton.edu/perl/webwn (accedido en
   junio de 2015).

El mismo procedimiento se ha realizado para convertir las traducciones de Google y
Yandex en grafos. Los resultados obtenidos se pueden consultar en los listados
:num:`#code-example-google-7` y :num:`#code-example-yandex-7` y las figuras
:num:`#sample07-google` y :num:`#sample07-yandex`.

.. code-block:: unl
   :caption: Codificación utilizando los *synsets* de WordNet del resultado de la traducción de la oración ejemplo 7 mediante el sistema Google.
   :name: code-example-google-7

    {unl}
    aoj(rest%2:42:12::, development%1:22:02::)
    mod(development%1:22:02::, sustainable%3:01:00::)
    met(rest%2:42:12::, ability%1:07:00::)
    mod(ability%1:07:00::, environment%1:15:00::)
    mod(environment%1:15:00::, natural%3:00:02::)
    obj(ability%1:07:00::, provide%2:34:00::)
    ben(provide%2:34:00::, humankind%1:05:00::)
    and(rest%2:42:12::, meet%2:42:02::)
    agt(meet%2:42:02::, development%1:22:02::)
    obj(meet%2:42:02::, need%1:17:00::)
    mod(need%1:17:00::, present%3:00:01::)
    man(meet%2:42:02::, 02%ability%1:07:00::)
    mod(02%ability%1:07:00::, generation%1:14:01::)
    mod(generation%1:14:01::, future%3:00:00::)
    obj(02%ability%1:07:00::, 02%meet%2:42:02::)
    agt(02%meet%2:42:02::, generation%1:14:01::)
    agt(02%meet%2:42:02::, commitment%1:04:00::)
    {/unl}


.. figure:: ../../data/samples/sample07_google.png
   :name: sample07-google
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente a la traducción de Google del ejemplo #7.
   
   
.. code-block:: unl
   :caption: Codificación utilizando los *synsets* de WordNet del resultado de la traducción de la oración ejemplo 7 mediante el sistema Yandex.
   :name: code-example-yandex-7

    {unl}
    aoj(rest%2:42:12::, development%1:22:02::)
    mod(development%1:22:02::, sustainable%3:01:00::)
    met(rest%2:42:12::, ability%1:07:00::)
    mod(ability%1:07:00::, environment%1:15:00::)
    mod(environment%1:15:00::, natural%3:00:02::)
    obj(ability%1:07:00::, provide%2:34:00::)
    ben(provide%2:34:00::, humankind%1:05:00::)
    and(rest%2:42:12::, meet%2:42:02::)
    agt(meet%2:42:02::, development%1:22:02::)
    obj(meet%2:42:02::, need%1:17:00::)
    mod(need%1:17:00::, present%3:00:01::)
    man(meet%2:42:02::, capability%1:07:00::)
    mod(capability%1:07:00::, generation%1:14:01::)
    mod(generation%1:14:01::, future%3:00:00::)
    mod(capability%1:07:00::, commitment%1:04:00::)
    mod(commitment%1:04:00::, 02%meet%2:42:02::)
    {/unl}


.. figure:: ../../data/samples/sample07_yandex.png
   :name: sample07-yandex
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente a la traducción de Yandex del ejemplo #7.


Ejecución del modelo
````````````````````
Una vez que se tienen disponibles los grafos generados por los traductores, se 
realiza la comparación de cada uno de ellos con el grafo de referencia para calcular
la distancia semántica introducida por cada uno de los sistemas de traducción y
poder evaluar su rendimiento de una forma automática.

A la hora de ejecutar el modelo, el usuario debe seleccionar algunos parámetros:

 * Algoritmo para el cálculo de la distancia entre conceptos.
 * Tolerancia en la comparación entre conceptos.
 * Tolerancia en la comparación entre relaciones.




Resultados
----------

Valoración
----------
