

Recursos utilizados
===================
El modelo se apoya en varios recursos, algoritmos y librerías desarrollados por
otras personas, nosotros los combinamos y añadimos nuestra aportación para poder
calcular la medida que nos interesa.

El autor ha podido utilizar algunos de los recursos tal cual estaban disponibles,
pero en otros ha colaborado en su desarrollo o transcripción al lenguaje de
programación seleccionado, en cada caso se indicarán las contribuciones realizadas.


WordNet 3.1
-----------
En la exposición del estado del arte hemos descrito sucintamente la base de datos WordNet y
sus características (ver :ref:`sección 2.1.4 <wordnet>`), no lo repetiremos aquí. Para este
trabajo hemos utilizado el diccionario correspondiente a la versión 3.1 y también la
búsqueda *online* para seleccionar las correspondencias entre las UWs y los *synsets*.


SemCor
------
El *corpus* SemCor es el único recurso etiquetado con WordNet que hemos encontrado; su 
utilización es imprescindible para poder hacer uso de medidas de distancia que tienen
en cuenta el contenido de información
(ver :ref:`sección 2.2.2 <redes-conceptos-contenido-informacion>`). Sin embargo no
se ha analizado cómo de representativo es este *corpus* para el dominio de información
en el que vamos a experimentar, los resultados de algunas medidas de distancia pueden
verse profundamente afectados por esta circunstancia.


WordNet-blast
-------------
WordNet-blast es un proyecto de código abierto desarrollado por Ugo Jardonnet que pretende
proveer un acceso rápido a la ontología WordNet [#]_. El código fuente está disponible en
Github [#]_, nosotros hemos tenido que realizar algunas modificaciones sobre el mismo para
subsanar algún error y prepararlo para su utilización desde nuestro modelo [#]_.

.. [#] Página personal de Ugo Jardonnet: http://logserv.free.fr/ (accedida en junio de 2015)

.. [#] Github. Código fuente de Wordnet-blast. https://github.com/jardon-u/wordnet-blast

.. [#] Algunas de estas modificaciones han sido incorporadas al código fuente del repositorio
   principal, otras están disponibles en la rama perteneciente al autor de esta
   tesis: https://github.com/jgsogo/wordnet-blast

.. medidas-distancia-conceptos_
Medidas de distancia entre conceptos
------------------------------------
En el estado del arte hemos visto varios intentos por diferentes autores para lograr una
medida de distancia (similaridad en algunos casos) entre conceptos utilizando la jerarquía de
WordNet. Nosotros hemos implementado las siguientes utilizando el lenguaje C++:

 * Jiang y Conrath (1997) :cite:`Jiang1997`.
 * Leacock y Chodorow (1998) :cite:`Leacock1998`.
 * Lin (1998) :cite:`Lin1998`.
 * Resnik (1995) :cite:`Resnik1995`.
 
 * Sussna (1993) :cite:`Sussna1993`: en la :ref:`sección 2.2.2 <redes-conceptos-estructura>`)
   mostramos la formulación que aparece en la bibliografía para el cálculo del peso
   de las conexiones entre los conceptos.
   
   Según Sussna, este peso, que representa la distancia semántica, debe ser menor
   cuanto mayor sea el número de conexiones del mismo tipo que parten de cada nodo; a pesar
   de que en el texto del artículo de 1993 se expresa claramente que *"the two inverse
   weights for an edge are averaged"* tanto en la formulación presente en dicho artículo
   como en la literatura posterior no se tiene en cuenta este punto.
   
   En nuestro modelo hemos implementado la formulación que debería ser la
   correcta [#]_: a medida que el número de relaciones aumenta, la distancia semántica se 
   hace más pequeña (ver :num:`figura #fig-sussna-fail`):
   
   .. math::

      d_{S}(c_i, c_j) = \frac{ \frac{1}{wt(c_i \rightarrow_r)} + \frac{1}{wt(c_j \rightarrow_{r'})} }{2 \cdot max\{depth(c_i), depth(c_j)\}}
   
   
 * Wu y Palmer :cite:`Wu1994`.
 * Rada *et al* (1989) :cite:`Rada1989`.

.. [#] No se ha contactado con el autor del artículo para consultar esta discrepancia.


.. figure:: ../img/sussnafail.png
   :name: fig-sussna-fail

   Variación de la distancia asociada a una conexión en función del número relaciones
   entre los elementos. A la izquierda los resultados según la formulación de
   Sussna, a la derecha los resultados según la modificación propuesta. La línea roja
   muestra la variación de la distancia cuando el concepto está en el primer nivel de
   profundidad de la jerarquía y la azul cuando está a una profundidad de 10.
   

Al programar todas las medidas de distancia anteriores se han tenido en cuenta los siguientes
puntos:

 * Todas utilizan la jerarquía de WordNet 3.1 construida con ``WordNet-blast`` haciendo uso
   únicamente de las relaciones de hiponimia/hiperonima.

 * A las medidas basadas en el contenido de información que necesitaban de un *corpus* se les
   ha proporcionado los datos del *corpus* SemCor expuesto anteriormente.

 * Todas estas medidas se han programado de tal forma que ofrezcan un valor de distancia
   :math:`d` o similaridad :math:`s` comprendido en el intervalo :math:`[0,1]` tal que
   se cumpla la relación

   .. math::
    
       d(c_1, c_2) + s(c_1, c_2) = 1

   para cualquier par de conceptos :math:`c1` y :math:`c2` de la jerarquía. En algunos
   casos la formulación estaba preparada para devolver este valor, en otros ha tenido
   que calcularse el máximo valor posible dados los recursos utilizados (WordNet y SemCor)
   para poder normalizar el resultado.

Gracias a estas consideraciones y, en especial, a la normalización realizada,
todas estas medidas pueden ser intercambiadas en el modelo de distancia entre grafos,
se pueden así comparar los resultados obtenidos con ellas. 


Distancia y jerarquía entre relaciones UNL
------------------------------------------
En la bibliografía no hemos encontrado ningún documento acerca de la distancia semántica entre
relaciones UNL, por lo que debemos proponer una. Para ello planteamos un modelo muy simple
basado en la jerarquía de relaciones que aparece en UNLWeb [#]_ (ver :num:`tabla #table-unl-relations`).

.. [#] UNL Wiki. Universal Relations. http://www.unlweb.net/wiki/Universal_Relations 
   (accedido en junio de 2015)
   

.. _table-unl-relations:
.. table:: Jerarquía de relaciones UNL según UNLWeb.
   :class: longtable
   
   +------------------------------------------------------------------------+
   | | **agt**: agent                                                       |
   | | **and**: conjuntion                                                  |
   | | **aoj**: object of an attribute                                      |
   | |   **ant**: antonym, different from                                   |
   | |   **equ**: synonym, equal to                                         |
   | |   **fld**: field                                                     |
   | |   **icl**: hyponym, a kind of                                        |
   | |   **iof**: example, instance of                                      |
   | |   **pof**: meronym, part of                                          |
   | | **ben**: beneficiary                                                 |
   | | **cnt**: content or theme                                            |
   | | **con**: condition                                                   |
   | | **exp**: experiencer                                                 |
   | | **mod**: modifier                                                    |
   | |   **mat**: material                                                  |
   | |   **nam**: name                                                      |
   | |   **pos**: possessor                                                 |
   | |   **qua**: quantifier                                                |
   | | **obj**: patient                                                     |
   | |   **opl**: objective place                                           |
   | |   **res**: result                                                    |
   | | **or**: disjunction                                                  |
   | | **per**: proportion, rate, distribution or basis for a comparison    |
   | |   **bas**: basis for a comparison                                    |
   | | **plc**: location: physical or logical                               |
   | |   **gol**: final place or state, destination                         |
   | |   **lpl**: logical place, scene                                      |
   | |   **src**: initial place or state, origin                            |
   | |   **via**: intermediate place, path                                  |
   | | **ptn**: partner                                                     |
   +------------------------------------------------------------------------+
   | | **tim**: time                                                        |
   | |   **tmf**: initial time                                              |
   | |   **tmt**: final time                                                |
   | |   **dur**: duration                                                  |
   | |     **coo**: co-occurrence                                           |
   | | **man**: manner                                                      |
   | |   **ins**: instrument or method                                      |
   | |     **met**: method                                                  |
   | |   **pur**: purpose                                                   |
   | | **rsn**: reason                                                      |
   | | **seq**: consequence                                                 |
   +------------------------------------------------------------------------+


Proponemos un modelo según el cual dos relaciones son iguales si pertenecen a la misma
tipología de primer nivel (agt, and, aoj,...) y distintas en caso contrario (ver
:num:`tabla #table-unl-relations`), así, sean dos relaciones, :math:`r_1` y :math:`r_2`,
que conectan dos pares de conceptos equivalentes según la medida de similaridad entre
conceptos seleccionada, entonces:

.. math::

    s_r(r_1, r_2) = 1 - d_r(r_1, r_2) = \begin{cases}
    1, & r_1 \equiv r_2\\
    0.8, & \exists r_p \mid r_p \quad subsumes \quad \{r_1, r_2\}\\
    0.2, & otherwise.
    \end{cases}
 
Como se puede observar la mínima similaridad entre dos relaciones es :math:`0.2`, se
considera así que la mera existencia de una relación entre dos mismos conceptos
indica un grado mínimo de similaridad.


Algoritmo de McGregor
---------------------
El modelo que proponemos se basa en la búsqueda de máximos grafos comunes, es un problema
bastante tratado en la bibliografía. Existen dos aproximaciones muy frecuentes para la 
resolución de este problema: convertirlo en un problema de búsqueda del máximo *clique* o
realizar una búsqueda con retroceso.

El algoritmo propuesto por McGregor en 1982 :cite:`McGregor1982` pertenece a los de búsqueda
con retroceso y según diferentes autores esta aproximación es más eficiente en grafos
dispersos :cite:`Bunke2002` :cite:`Conte2007` :cite:`Welling2011`, como es el caso de
los grafos conceptuales.

Este algoritmo lo hemos incorporado a nuestro modelo utilizando la implementación disponible 
en la librería *graph* dentro de las Boost [#]_, que además están programadas en C++.

.. [#] Boost Graph Library: McGregor Common Subgraphs. Boost C++ Libraries.
   http://www.boost.org/doc/libs/1_58_0/libs/graph/doc/mcgregor_common_subgraphs.html
   (accedido en junio de 2015)
   
La implementación disponible en la Boost nos permite aplicar con facilidad dos ideas
que perseguimos en el planteamiento de nuestro modelo:

 * Podemos ejecutar el algoritmo con una función de comparación entre los nodos
   de los grafo definida por nosotros mismos. Utilizaremos esta funcionalidad para
   incorporar cualquiera de las medidas de distancia entre conceptos que ya hemos
   expuesto, pero también para codificar el umbral de tolerancia entre ellos.
   
   Nuestra función indicará al algoritmo McGregor de las Boost que dos nodos son
   iguales cuando la distancia entre ellos sea menor que el umbral indicado:
   
   .. math::
   
       c_1 \equiv c_2 \iff d_T(c_1, c_2) \leq t_c
       
   El mismo razonamiento lo utilizaremos para aplicar la distancia entre relaciones.
   
 * La librería también nos permite ejecutar el algoritmo de tal forma que podemos 
   acceder a todos los grafos que encuentra, aunque no sean el máximo grafo común;
   esto nos permite almacenarlos todos ellos, algo que utilizaremos posteriormente en
   nuestro modelo.
   


   
