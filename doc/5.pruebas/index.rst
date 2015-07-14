
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
en Barcelona. La comparación se realizará contra los grafos resultantes de traducir
estas oraciones al español y de vuelta al inglés utilizando software de traducción
disponible en internet.

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
los recursos; como ya se indicó en la :ref:`sección 3.3 <planteamiento-problema>`, al
carecer de tiempo y medios para generar un conjunto de datos adecuado, ha sido 
necesario crearlos *ex profeso* para este trabajo [#]_. Se asume así que los resultados
deben ser revisados con un enfoque más científico, pero creemos que los datos generados
de esta forma pueden servir para realizar una primera evaluación del modelo.

.. [#] En el :ref:`Apéndice A <appendix-data>` se encuentran disponibles todos los datos
   utilizados para la realización del experimento.


Metodología
-----------
Ilustraremos la metodología mostrada en la :num:`figura #fig-experiment-layout` con
el ejemplo número 3 del *dataset* que hemos elaborado. El procedimiento se detalla
en los siguientes apartados.

Datos de partida: oración y grafo UNL
`````````````````````````````````````
En el documento al que hemos hecho referencia anteriormente tenemos disponibles las
oraciones en inglés y su transcripción como grafo UNL. La oración sobre la que
trabajaremos es la siguiente,

Ejemplo 3
  : *These concepts are essential for advancing towards a sustainable, more human world agenda, and they will undoubtedly continue to be relevant for many years to come.*
  
cuyo grafo UNL se muestra en el :num:`listado #code-example-unl-3`.

.. code-block:: unl
   :caption: Codificación UNL original de la oración ejemplo 3.
   :name: code-example-unl-3
   
   [S]
   obj(continue(icl>occur).@entry,:01)
   mod:01(concept(icl>logic).@entry.@pl,this)
   man(continue(icl>occur).@entry,undoubtedly(icl>man))
   gol(continue(icl>occur).@entry,:02)
   aoj:02(relevant(mod<thing).@entry,:01)
   dur:02(relevant(mod<thing).@entry,year(icl>time).@pl)
   mod:02(year(icl>time).@pl,many)
   mod:02(year(icl>time).@pl,forthcoming(mod<thing))
   and(continue(icl>occur).@entry,essential(mod<thing))
   aoj(essential(mod<thing),:01)
   pur(essential(mod<thing),advance(icl>progress(icl>do)))
   man(advance(icl>progress(icl>do)),towards)
   obj(towards,:03)
   mod:03(agenda(icl>programme).@entry,world(mod<thing))
   mod(:03,human(mod<thing))
   man(human(mod<thing),more)
   and(human(mod<thing),sustainable(mod<thing))
   [/S]
   

Traducción a idioma intermedio
``````````````````````````````
El siguiente paso consiste en traducir la oración original a un segundo idioma que
servirá de punto de partida para las traducciones generadas por los sistemas que vamos
a comparar.

En nuestro caso el idioma intermedio será el español, y la traducción la generaremos
utilizando el sistema Systrans [#]_:

  **Systrans**: Estos conceptos son esenciales para avanzar hacia un orden del día sostenible, más humano del mundo, y continuarán indudablemente siendo relevantes durante muchos años de venir.


.. [#] SYSTRANet – Online translation software and tools – Dictionary.
   http://www.systranet.com/dictionary/english-spanish (accedido en junio
   de 2015)


Como podemos ver, este sistema ya ha introducido alguna variación respecto al contenido
original, incluso la corrección gramatical de la oración parece estar comprometida.


Traducción al idioma original
`````````````````````````````
La oración en español es traducida nuevamente al idioma de partida (inglés) utilizando
dos sistemas de traducción automática: Google [#]_ y Yandex [#]_, con los que obtenemos
los siguientes resultados:

  **Google**: *These concepts are essential in order to move towards a more sustainable day human world, and will undoubtedly continue to be relevant for many years to come.*
  
  **Yandex**: *These concepts are essential for progress towards an agenda for sustainable, more human world, and undoubtedly will continue to remain relevant for many years to come.*
  
.. [#] Traductor de Google. https://translate.google.es (accedido en junio de 2015)

.. [#] Yandex.Translate. https://translate.yandex.com/ (accedido en junio de 2015)

Leyendo las oraciones resultantes podemos observar cómo las traducciones no son idénticas
entre ellas y se han alejado del contenido semántico original. Nuestro modelo trabajará con
estos datos para obtener una medida de distancia entre las traducciones y la oración
original.

Identificación de los *synsets* de WordNet
``````````````````````````````````````````
Como hemos indicado, la ontología UNL no está disponible, por lo que la manera
de utilizar las medidas de distancia que hemos expuesto en el estado del arte debe
ser a través de la jerarquía de conceptos de WordNet. Para ello hemos tenido que
identificar cada concepto expresado por las UWs con un *synset* concreto en WordNet.

Este proceso se ha realizado manualmente y, con total seguridad, el autor está
introduciendo una primera
desviación semántica entre la oración original y el grafo base para la comparación; no
obstante, se ha tenido la precaución de que siempre que aparecen los mismos conceptos
se sustituye por el mismo *synset*.

De este modo, el grafo UNL original, se convierte en el grafo mostrado en el 
:num:`listado #code-example-original-3` que también se muestra en la
:num:`figura #sample03-original`.

.. code-block:: unl
   :caption: Codificación utilizando los *synsets* de WordNet de la oración ejemplo 7.
   :name: code-example-original-3
   
   {unl}
   obj(continue%2:42:01::, concept%1:09:00::)
   man(continue%2:42:01::, undoubtedly%4:02:00::)
   gol(continue%2:42:01::, be%2:42:03::)
   aoj(be%2:42:03::, concept%1:09:00::)
   obj(be%2:42:03::, relevant%3:00:00::)
   dur(relevant%3:00:00::, year%1:28:01::)
   mod(year%1:28:01::, many%3:00:00::)
   mod(year%1:28:01::, forthcoming%5:00:00:future:00)
   and(continue%2:42:01::, essential%3:00:00:necessary:00)
   aoj(essential%3:00:00:necessary:00, concept%1:09:00::)
   pur(essential%3:00:00:necessary:00, advance%2:38:00::)
   plc(advance%2:38:00::, agenda%1:10:00::)
   mod(agenda%1:10:00::, world%1:14:02::)
   mod(agenda%1:10:00::, human%3:01:00::)
   man(human%3:01:00::, more%4:02:00::)
   and(human%3:01:00::, sustainable%3:01:00::)
   {/unl}


.. figure:: ../../data/samples/sample03_original.png
   :name: sample03-original
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente al ejemplo #3 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).

La conversión de los conceptos UNL expresados en las UWs en los *synsets* de WordNet
se ha realizado utilizando el buscador de WordNet accesible en la página web de la Universidad
de Princeton [#]_, de entre todas las opciones proporcionadas para cada palabra se
ha seleccionado el concepto más próximo dentro de la categoría gramatical adecuada.

.. [#] WordNet Search - 3.1. http://wordnetweb.princeton.edu/perl/webwn (accedido en
   junio de 2015).

El mismo procedimiento se ha realizado para convertir las traducciones de Google y
Yandex en grafos. Los resultados obtenidos se pueden consultar en los listados
:num:`#code-example-google-3` y :num:`#code-example-yandex-3` y las figuras
:num:`#sample03-google` y :num:`#sample03-yandex`.

.. code-block:: unl
   :caption: Codificación utilizando los *synsets* de WordNet del resultado de la traducción de la oración ejemplo 3 mediante el sistema Google.
   :name: code-example-google-3

    {unl}
    obj(continue%2:42:01::, concept%1:09:00::)
    man(continue%2:42:01::, undoubtedly%4:02:00::)
    gol(continue%2:42:01::, be%2:42:03::)
    aoj(be%2:42:03::, concept%1:09:00::)
    obj(be%2:42:03::, relevant%3:00:00::)
    dur(relevant%3:00:00::, year%1:28:01::)
    mod(year%1:28:01::, many%3:00:00::)
    mod(year%1:28:01::, forthcoming%5:00:00:future:00)
    and(continue%2:42:01::, essential%3:00:00:necessary:00)
    aoj(essential%3:00:00:necessary:00, concept%1:09:00::)
    pur(essential%3:00:00:necessary:00, move%2:41:01::)
    plc(move%2:41:01::, day%1:26:00::)
    mod(day%1:26:00::, world%1:14:02::)
    mod(day%1:26:00::, human%3:01:00::)
    mod(day%1:26:00::, sustainable%3:01:00::)
    {/unl}


.. figure:: ../../data/samples/sample03_google.png
   :name: sample03-google
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente a la traducción de Google del ejemplo #3.
   
   
.. code-block:: unl
   :caption: Codificación utilizando los *synsets* de WordNet del resultado de la traducción de la oración ejemplo 3 mediante el sistema Yandex.
   :name: code-example-yandex-3

    {unl}
    obj(continue%2:42:01::, concept%1:09:00::)
    man(continue%2:42:01::, undoubtedly%4:02:00::)
    gol(continue%2:42:01::, be%2:42:03::)
    aoj(be%2:42:03::, concept%1:09:00::)
    obj(be%2:42:03::, relevant%3:00:00::)
    dur(relevant%3:00:00::, year%1:28:01::)
    mod(year%1:28:01::, many%3:00:00::)
    mod(year%1:28:01::, forthcoming%5:00:00:future:00)
    and(continue%2:42:01::, essential%3:00:00:necessary:00)
    aoj(essential%3:00:00:necessary:00, concept%1:09:00::)
    pur(essential%3:00:00:necessary:00, progress%2:30:00::)
    plc(progress%2:30:00::, agenda%1:10:00::)
    pur(agenda%1:10:00::, world%1:14:02::)
    mod(world%1:14:02::, human%3:01:00::)
    man(human%3:01:00::, more%4:02:00::)
    and(world%1:14:02::, sustainable%3:01:00::)
    {/unl}


.. figure:: ../../data/samples/sample03_yandex.png
   :name: sample03-yandex
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente a la traducción de Yandex del ejemplo #3.


Ejecución del modelo
````````````````````
Una vez que se tienen disponibles los grafos generados por los traductores, se 
realiza la comparación de cada uno de ellos con el grafo de referencia para calcular
la distancia semántica introducida por cada uno de los sistemas de traducción y
poder evaluar su rendimiento de forma automática.

A la hora de ejecutar el modelo, el usuario debe seleccionar algunos parámetros:

 * Algoritmo para el cálculo de la distancia entre conceptos.
 * Tolerancia en la comparación entre conceptos.
 * Tolerancia en la comparación entre relaciones.


.. figure:: ../../data/samples/sample03-brief/measures-yandex-synset.png
   :name: sample03-measures-yandex-synset
   :scale: 100 %
   :width: 100 %
   
   Similaridad entre el grafo original y el grafo generado por el traductor de Yandex en función de la tolerancia entre conceptos. Se muestra la evolución de este valor para todas las métricas de distancia incorporadas en el algoritmo.


.. figure:: ../../data/samples/sample03-brief/measures-google-synset.png
   :name: sample03-measures-google-synset
   :scale: 100 %
   :width: 100 %
   
   Similaridad entre el grafo original y el grafo generado por el traductor de Google en función de la tolerancia entre conceptos. Se muestra la evolución de este valor para todas las métricas de distancia incorporadas en el algoritmo.
   
En la :num:`figura #sample03-measures-yandex-synset` y en la
:num:`figura #sample03-measures-google-synset`
se muestra el valor calculado de similaridad para estos grafos utilizando todas
las medidas de similaridad/distancia entre conceptos disponibles y para
diferentes valores de tolerancia entre conceptos, :math:`t_c \in [0.0, 0.9]`.

Una gráfica similar se ha realizado fijando un valor de tolerancia para la
distancia entre conceptos y variando la tolerancia entre relaciones, no se ha
reproducido aquí porque no se produce ninguna variación en el valor de 
similaridad.

Tanto en la comparación con el grafo generado por el traductor de Google como
en el de Yandex, existe un umbral de :math:`t_c` en el que se produce un salto
en el valor de similaridad entre los grafos para la mayoría de los algoritmos
de distancia semántica. Una inspección detallada de los resultados nos permite
encontrar el par de palabras que empiezan a ser equivalentes cuando la tolerancia
supera cierto umbral.

En la comparación entre la traducción de Google y el grafo original, el par de
palabras que pasa a ser considerado equivalente es ``agenda`` y ``day``, en cada
caso con un valor de similaridad diferente:
 
 * Sussna :math:`s_c(agenda, day) = 0.828666`
 * Shortest-path :math:`s_c(agenda, day) = 0.684211`
 * Leacock-Chodorow: :math:`s_c(agenda, day) = 0.31688`
 * Wu-Palmer :math:`s_c(agenda, day) = 0.142857`
 * Resnik :math:`s_c(agenda, day) = 0.122799`
 * Jiang-Conrath :math:`s_c(agenda, day) < 0.1`
 * Lin :math:`s_c(agenda, day) < 0.1`
   
En el caso de la traducción de Yandex el par de palabras que se incorpora al
máximo grafo común es ``agenda`` y ``populace``, con los siguientes valores:

 * Sussna :math:`s_c(agenda, populace) = 0.85633`
 * Shortest-path :math:`s_c(agenda, populace) = 0.763158`
 * Leacock-Chodorow :math:`s_c(agenda, populace) = 0.395966`
 * Wu-Palmer :math:`s_c(agenda, populace) = 0.181818`
 * Resnik :math:`s_c(agenda, populace) = 0.122799`
 * Jiang-Conrath :math:`s_c(agenda, populace) < 0.1`
 * Lin :math:`s_c(agenda, populace) < 0.1`

Como consecuencia de la incorporación de un nuevo nodo al grafo resultante, 
se añaden nuevas conexiones con sus valores de similaridad que incrementan
el valor calculado para la pareja de grafos.


.. figure:: ../../data/samples/sample03-brief/sussna-synset_tol-00.png
   :name: sample03-sussna-synset-tol-0
   :scale: 100 %
   :width: 100 %
   
   Conjunto de nodos y relaciones equivalentes en la comparación entre el grafo original y las traducciones de Google (en rojo) y Yandex (azul), cuando :math:`t_c = 0`.


.. figure:: ../../data/samples/sample03-brief/sussna-synset_tol-09.png
   :name: sample03-sussna-synset-tol-0
   :scale: 100 %
   :width: 100 %
   
   Conjunto de nodos y relaciones equivalentes en la comparación entre el grafo original y las traducciones de Google (en rojo) y Yandex (azul), con tolerancia entre conceptos :math:`t_c = 0.9`.


Valor de similaridad
````````````````````
Puesto que se dispone de varios algoritmos de medida de similaridad entre conceptos,
para calcular el valor final de similaridad entre los grafos podemos utilizar la media
de todos ellos, de este modo se obtiene un resultado como el que se muestra en la
:num:`figura #sample03-relation-tol-0`: el valor de similaridad muestra una incremento
monótono conforme la tolerancia entre los conceptos aumenta, que es lo que cabría
esperar y que hemos comentado al exponer el modelo.

.. figure:: ../../data/samples/sample03-brief/synset_tol-relation_tol-0.png
   :name: sample03-relation-tol-0
   :scale: 100 %
   :width: 100 %

   Similaridad semántica entre el grafo original y los grafos correspondientes a las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia :math:`t_c` entre conceptos (intervalo de confianza 95%).

En este caso concreto, el algoritmo indica que la distancia semántica es menor en el
caso de la traducción de Yandex que en la de Google; un conjunto de oraciones
etiquetado adecuadamente (probablemente fuera necesario realizarlo manualmente)
nos podría servir para valorar el desempeño de los traductores.


Resultados
----------
Para la experimentacion se ha preparado un *dataset* con 10 oraciones extraídas del
documento del Forum Universal de las Culturas de Barcelona 2004 y traducidas utilizando
los servicios indicados anteriormente. El conjunto completo de oraciones se incluye a
continuación; la codificacion original, así como las correspondencias con WordNet y
la representación gráfica tanto del original como de las traducciones puede
consultarse en el *dataset* completo que se adjunta en el :ref:`Apéndice A <appendix-data>`.


Ejemplo 1
  : *The Universal Forum of Cultures will be held from April 23 to September 24, 2004, and will include exhibitions, debates and festivals to celebrate cultural diversity throughout the world.*

  **Systrans**: El foro universal de culturas será sostenido del 23 de abril al 24 de septiembre de 2004, e incluirá exposiciones, discusiones y festivales para celebrar diversidad cultural en el mundo entero.

  **Google**: *The Universal Forum of Cultures will be held from April 23 to September 24, 2004, and will include exhibitions, debates and festivals to celebrate cultural diversity in the world.*

  **Yandex**: *The universal forum of cultures will be held from April 23 to September 24, 2004, and will include exhibitions, discussions, and festivals that celebrate cultural diversity in the world.*


.. figure:: ../../data/samples/sample01-brief/synset_tol-relation_tol-0.png
   :name: sample01-relation-tol-0
   :scale: 100 %
   :width: 100 %
   
   Similaridad semántica entre el grafo original y las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia entre conceptos (intervalo de confianza 95%).
   
   
Ejemplo 2
  : *In their 29th General Conference, the 186 member states of the Unesco ratified their unanimous support of the project, jointly organized by the Spanish government, the Catalan autonomous government and the Barcelona City Council.*

  **Systrans**: En su 29na conferencia general, los 186 Estados miembros de la UNESCO ratificaron su ayuda unánime del proyecto, organizada en común por el gobierno español, el gobierno autónomo catalán y el Ayuntamiento de Barcelona.

  **Google**: *In its 29th general conference, the 186 Member States of UNESCO unanimously reaffirmed their support of the project, organized jointly by the Spanish government, the Catalan Autonomous Government and the City of Barcelona.*

  **Yandex**: *In your 29na general conference, the 186 member States of UNESCO have ratified their unanimous support of the project, organized jointly by the Spanish government, the autonomous government of catalonia and the Barcelona city Council.*

  
.. figure:: ../../data/samples/sample02-brief/synset_tol-relation_tol-0.png
   :name: sample02-relation-tol-0
   :scale: 100 %
   :width: 100 %
   
   Similaridad semántica entre el grafo original y las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia entre conceptos (intervalo de confianza 95%).
   
 
      
Ejemplo 3
  : *These concepts are essential for advancing towards a sustainable, more human world agenda, and they will undoubtedly continue to be relevant for many years to come*

  **Systrans**: Estos conceptos son esenciales para avanzar hacia un orden del día sostenible, más humano del mundo, y continuarán indudablemente siendo relevantes durante muchos años de venir

  **Google**: *These concepts are essential in order to move towards a more sustainable day human world, and will undoubtedly continue to be relevant for many years to come*

  **Yandex**: *These concepts are essential for progress towards an agenda for sustainable, more human world, and undoubtedly will continue to remain relevant for many years to come*


Ejemplo 4
  : *Knowledge of other cultures is essential for establishing a constructive dialogue between different communities.*

  **Systrans**: El conocimiento de otras culturas es esencial para establecer un diálogo constructivo entre diversas comunidades.

  **Google**: *Knowledge of other cultures is essential to establish a constructive dialogue between different communities.*

  **Yandex**: *The knowledge of other cultures is essential to establish a constructive dialogue between various communities.*


.. figure:: ../../data/samples/sample04-brief/synset_tol-relation_tol-0.png
   :name: sample04-relation-tol-0
   :scale: 100 %
   :width: 100 %
   
   Similaridad semántica entre el grafo original y las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia entre conceptos (intervalo de confianza 95%).
   

Ejemplo 5
  : *This knowledge implies reflection about the common ground between all individuals as well as the qualities that differentiate them.*

  **Systrans**: Este conocimiento implica la reflexión sobre el terreno común entre todos los individuos así como las calidades que las distingan.

  **Google**: *This knowledge involves reflection on the common ground between all individuals and the qualities that distinguish them.*

  **Yandex**: *This knowledge implies reflection on the common ground between all individuals as well as the qualities that distinguish them.*


.. figure:: ../../data/samples/sample05-brief/synset_tol-relation_tol-0.png
   :name: sample05-relation-tol-0
   :scale: 100 %
   :width: 100 %
   
   Similaridad semántica entre el grafo original y las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia entre conceptos (intervalo de confianza 95%).
   

Ejemplo 6
  : *The Forum strives to foster the kind of understanding and respect capable of increasing both our appreciation of our human environment and our ability to work together to make the world a better place.*

  **Systrans**: El foro se esfuerza fomentar la clase de comprensión y respetar capaz de aumentar nuestro aprecio de nuestro ambiente humano y nuestra capacidad de trabajar junto para hacer el mundo un mejor lugar.

  **Google**: *The forum strives to promote the kind of understanding and respect able to increase our appreciation of our human environment and our ability to work together to make the world a better place.*

  **Yandex**: *The forum strives to foster the kind of understanding and respect able to increase our appreciation of our human environment and our ability to work together to make the world a better place.*


.. figure:: ../../data/samples/sample06-brief/synset_tol-relation_tol-0.png
   :name: sample06-relation-tol-0
   :scale: 100 %
   :width: 100 %
   
   Similaridad semántica entre el grafo original y las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia entre conceptos (intervalo de confianza 95%).
   
   
Ejemplo 7
  : *Sustainable Development satisfies the needs of the present without compromising future generations' abilities to satisfy theirs, and is based on the natural environment's capacity to provide for humankind.*

  **Systrans**: El desarrollo sostenible satisface las necesidades del presente sin las capacidades de las futuras generaciones de compromiso de satisfacer el suyo, y se basa en la capacidad del ambiente natural de prever humanidad.

  **Google**: *Sustainable development meets the needs of the present without the ability of future generations to meet his commitment, and is based on the ability of the natural environment to provide for humanity.*

  **Yandex**: *Sustainable development meets the needs of the present without the capabilities of future generations of commitment to meet yours, and is based on the ability of the natural environment to provide for humanity.*


.. figure:: ../../data/samples/sample07-brief/synset_tol-relation_tol-0.png
   :name: sample07-relation-tol-0
   :scale: 100 %
   :width: 100 %
   
   Similaridad semántica entre el grafo original y las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia entre conceptos (intervalo de confianza 95%).
   
   
Ejemplo 8
  : *People from all cultures must join forces to achieve this goal, pooling their knowledge and experience to find solutions to a problem with a global scope and impact.*

  **Systrans**: La gente de todas las culturas debe unirse a fuerzas para alcanzar esta meta, reuniendo su conocimiento y experiencia para encontrar soluciones a un problema con un ámbito global y un impacto.

  **Google**: *People of all cultures must join forces to achieve this goal by bringing together their knowledge and experience to find solutions to a problem with a global scope and impact.*

  **Yandex**: *People of all cultures must join forces to achieve this goal, bringing together their knowledge and experience to find solutions to a problem with a global scope and impact.*


.. figure:: ../../data/samples/sample08-brief/synset_tol-relation_tol-0.png
   :name: sample08-relation-tol-0
   :scale: 100 %
   :width: 100 %
   
   Similaridad semántica entre el grafo original y las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia entre conceptos (intervalo de confianza 95%).
   
   
Ejemplo 9
  : *the elements of culture that have a decisive impact on the development of individual and collective conditions regarding nutrition, work and health will also be addressed.*

  **Systrans**: los elementos de la cultura que tienen un impacto decisivo en el desarrollo de condiciones individuales y colectivas con respecto la nutrición, el trabajo y a la salud también serán dirigidos.

  **Google**: *the elements of culture that have a decisive impact on the development of individual and collective regarding nutrition conditions, work and health will also be addressed.*

  **Yandex**: *the elements of culture that have a decisive impact on the development of conditions for individual and collective regarding nutrition, work and health will also be addressed.*


.. figure:: ../../data/samples/sample09-brief/synset_tol-relation_tol-0.png
   :name: sample09-relation-tol-0
   :scale: 100 %
   :width: 100 %
   
   Similaridad semántica entre el grafo original y las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia entre conceptos (intervalo de confianza 95%).
 
   
Ejemplo 10
  : *Stable and lasting peace requires something more than stopping war and other situations of conflict.*

  **Systrans**: La paz estable y duradera requiere algo más que parando guerra y otras situaciones del conflicto.

  **Google**: *Stable and lasting peace requires more than stopping war and conflict situations.*

  **Yandex**: *The stable and lasting peace requires more than stopping war and other situations of conflict.*


.. figure:: ../../data/samples/sample10-brief/synset_tol-relation_tol-0.png
   :name: sample10-relation-tol-0
   :scale: 100 %
   :width: 100 %
   
   Similaridad semántica entre el grafo original y las traducciones realizadas con Google (rojo) y Yandex (azul) en función de la tolerancia entre conceptos (intervalo de confianza 95%).


Valoración
----------
En el apartado anterior hemos mostrado los resultados obtenidos para el pequeño conjunto
de datos que se ha preparado con objeto de probar el algoritmo. Se puede observar cómo
la similaridad permanece constante o bien se incrementa a medida que se aumenta la
tolerancia entre conceptos, tal y como se pretendía al plantear el modelo.

También parece adecuada la aproximación que se ha realizado utilizando varios algoritmos
de medida de distancia entre conceptos y calculando el valor de similaridad como la media
de todos ellos; a pesar de que los intervalos de confianza mostrados en las imágenes se
superponen, la media muestra un crecimiento suave.

Sin embargo, existen algunos resultados que no parecen correctos:

 * En el ejemplo 9 (ver :num:`figura #sample09-relation-tol-0`), la evolución de la similaridad
   es contraria a lo que hemos comentado anteriormente, a medida que aumenta la tolerancia
   entre conceptos, la similaridad disminuye. Un examen más detallado de los
   resultados intermedios que se van generando durante la ejecución del algoritmo sugiere
   que el error se produce en la elección de los subgrafos que forman el máximo grafo común
   entre los candidatos encontrados por el algoritmo de McGregor. El estudio (y solución) de esta
   circunstancia se tiene que dejar como trabajo futuro.
   
 * En el ejemplo 7 se produce un fenómeno atípico con la similaridad calculada utilizando
   la distancia semántica entre conceptos propuesta por Sussna. Como se ve en la
   :num:`figura #sample07-measures-yandex-synset` la similaridad baja cuando la tolerancia entre
   conceptos aumenta, para volver a subir posteriormente. Todo indica a pensar que
   esta anomalía también comparte causa con la comentada anteriormente, pero su análisis
   y solución deben aplazarse. Lo mismo ocurre en el ejemplo 2 con la distancia de
   Wu-Palmer (ver :num:`figura #sample02-measures-yandex-synset`).


.. figure:: ../../data/samples/sample07-brief/measures-yandex-synset.png
   :name: sample07-measures-yandex-synset
   :scale: 100 %
   :width: 100 %
   
   Similaridad entre el grafo original y el grafo generado por el traductor de Yandex en función de la tolerancia entre conceptos. Se muestra la evolución de este valor para todas las métricas de distancia incorporadas en el algoritmo.


.. figure:: ../../data/samples/sample02-brief/measures-yandex-synset.png
   :name: sample02-measures-yandex-synset
   :scale: 100 %
   :width: 100 %
   
   Similaridad entre el grafo original y el grafo generado por el traductor de Google en función de la tolerancia entre conceptos. Se muestra la evolución de este valor para todas las métricas de distancia incorporadas en el algoritmo.


NOTA.- El objetivo de esta experimentación no es valorar los traductores, no creemos
que la muestra de oraciones sobre la que hemos trabajado sea suficientemente
significativa para ello.
   

