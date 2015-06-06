
.. raw:: latex

    \newpage


Propuesta de modelo
===================

.. <= 20 páginas
.. Herramientas utilizadas

.. toctree::
   :maxdepth: 2
   
   ideas.rst



.. a medida que nos alejamos del punto de entrada del grafo, las modificaciones que encontramos son menos importantes.

.. dependiendo del tamaño del grafo, podemos abordarlo como un problema de "Exact matching" o bien como un
problema aproximado (quizá para grafos grandes... quizá para textos completos) <<-- ¿cuándo empieza a ser grande?


Propuesta
---------

La propuesta puede hacerse en varias aproximaciones. Se tratará siempre de calcular la distancia entre un grafo
A y otro grafo B

 #. Generación de paráfrasis
   #. Generar todas las posibles paráfrasis de cada uno de los grafos (¿me valdría con hacerlo de uno sólo de ellos?
      Depende de cómo de bien sea capaz de generarlas), así creo dos conjuntos de grafos C_A y C_B.
   #. La distancia entre A y B será la menor de las distancias entre cada pareja C_A x C_B

 #. Cálculo de distancias
   #. *Edit distance* --- el problema podría ser combinatorio, puesto que puedo modificar el grafo de varias formas
      para obtener el mismo resultado.
     #. Coste asociado a sustituir un UW por otro: dependerá de su distancia en la taxonomia.
     #. Coste asociado a los rasgos/atributos de un UW --> en primera aproximación lo vamos a ignorar.
     #. Coste asociado a eliminar/crear una relación.

Propuesta II
------------

Un DAG de UNL es un grafo bipartito (todo nodo-concepto se conecta con un nodo-relación y éste con un nodo-concepto); para este tipo de grafos se ha desarrollado una métrica de próximidad llamada SimRank (¡buscar!); este algoritmo me sirve para poner en relación con un nodo todos los que estén más próximos a él. <<< Salía en el vídeo "Proximity in Graphs de la Week#7 del [Coursera] Mining Massive Data Sets".

Puedo construir el minimum.common-supergraph, expresarlo como grafo bipartito y resolver el problema de minimum-flow-cost.


Propuesta III
-------------

Calculo la matriz de distancias entre todos los conceptos que aparecen en el grafo origen y en el grafo destino de la comparación, y a partir de ella calcula la máxima verosimilitud del matching, es decir, cuál es la mejor combinación de pares, la que tiene el mínimo coste de distancias (¿es una matriz de adyacencia que puedo expresar de alguna otra forma?). Una vez tengo las mejores soluciones combinatorias paso a por las relaciones entre conceptos.

 * La primera opción es simplemente ver qué relaciones se mantienen e incorporarlas a la métrica de similaridad \cite{ManuelMontes-y-GomezAlexanderGelbukh} 
 * Otra opción es expresar también el problema como combinatorio: ver la combinación de relaciones entre los conceptos que minimiza la distancia <-- aunque entonces esta combinatoria debería incorporarla también en el problema inicial a minimizar.

OJOJOJOJOJOJJO!!! La distancia entre los nodos-concepto en la matriz es su distancia semántica (en WordNet o en cualquier tesauro/taxonomia, hay literatura sobre ello). Y el problema es que hay que incorporar los nodos-relación... y sigo dándole vueltas al grafo-bipartito, creo que ahí hay algo. 


Propuesta IV
------------

Y que pasa si hago el grafo-bipartito y aplico un algoritmo HITS (el que explican en Coursera con el hubs-authorities para los grafos, en la semana 7). Mi idea es que inicializo el algoritmo con valores únicamente en los nodos-relacion y nodos-concepto de unos de los grafos, hago el power-iteration y miro cuál es la puntuación obtenida por los nodos-relación y nodos-concepto del otro grafo.

A lo mejor habría que mejorarlo considerando que el salto aleatorio tendría que ir siempre a uno de lso nodos del grafo origen para calcular de alguna manera la proximidad del otro grafo respecto a ese perfil. Pero realmente si quiero hacer esto tendría que aplicarlo en el grafo completo de conceptos y relaciones...

Básicamente sería crear el grafo-bipartito con todos los conceptos y todas las relaciones, uniéndolos de todas las formas posibles (¡aquí ya tenemos hecha la paráfrasis! ¡Es un preprocesado que sólo tengo que hacer una vez! ¡en la práctica la lengua es "estática" por lo que no tengo que recalcular el mega-grafo! ¿es posible crear ese grafo?). Después, para comparar la proximidad entre dos DAG me basta con aplicar un random-walk tomando como conjunto de "autoridades" (nodos a los que salta aleatoriamente con baja probabilidad) los nodos de uno de los grafos (incluirlos tantas veces como aparezcan, la relación sujeto aparecerá varias veces seguro) y, cuando se estabilice, ver cuáles son los valores de relevancia de los nodos del otro grafo. Me indica SIMILARIDAD.

Ventajas: no es combinatorio, es un algoritmo de tiempo constante.
Problemas: no creo que pueda servirme para comparar más allá de una frase.