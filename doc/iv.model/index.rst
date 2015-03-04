
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