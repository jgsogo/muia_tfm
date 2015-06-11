

Recursos utilizados
===================
El modelo propuesto se apoya en varios recursos, algoritmos y librerías desarrollados por
otras personas, nosotros las combinamos y añadimos nuestra pequeña aportación para poder
calcular la medida de similaridad.

El autor ha podido utilizar algunos de los recursos tal cual estaban disponibles, pero en otros
ha colaborado en su desarrollo o transcripción al lenguaje de programación seleccionado, se
indicará en cada caso las contribuciones realizadas.

WordNet 3.1
-----------


SemCor
------


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


Medidas de distancia entre conceptos
------------------------------------
En el estado del arte hemos visto varios intentos por diferentes autores para lograr una
medida de distancia (similaridad en algunos casos) entre conceptos utilizando la jerarquía de
WordNet. Nosotros hemos implementado las siguientes utilizando el lenguaje C++:

 * Jiang y Conrath (1997) :cite:`Jiang1997`.
 * Leacock y Chodorow (1998) :cite:`Leacock1998`.
 * Lin (1998) :cite:`Lin1998`.
 * Resnik (1995) :cite:`Resnik1995`.
 
 * Sussna (1993) :cite:`Sussna1993`: en la :num:`sección #redes-conceptos-estructura` mostramos la formulación
   que aparece en la bibliografía para el cálculo del peso de las conexiones entre los 
   conceptos. Según Sussna este peso, que representa la distancia semántica, debe ser menor
   cuanto mayor sea el número de conexiones del mismo tipo que parten de cada nodo; sin embargo
   la formulación proporcionada no se comporta según lo pretendido.
   
   En nuestro modelo hemos implementado el comportamiento que creemos que debería ser el
   correcto [#]_: a medida que el número de relaciones aumenta, la distancia semántica se 
   hace más pequeña (ver :num:`figura #fig-sussna-fail`).
   
 * Wu y Palmer :cite:`Wu1994`.
 * Rada *et al* (1989) :cite:`Rada1989`.

.. [#] No se ha contactado con el autor del artículo para consultar esta discrepancia.

.. figure:: ../img/sussnafail.png
   :name: fig-sussna-fail

   Variación de la distancia asociada a una conexión en función del número relaciones entre los
   elementos (mismo número en cada sentido). A la izquierda los resultados según la formulación de
   Sussna, a la derecha los resultados según la modificación propuesta.
   
 
Todas estas medidas pueden ser intercambiadas en nuestro modelo obteniéndose diferentes valores
de similaridad entre grafos, así podemos evaluarlas de este modo en un contexto más amplio y
verificar cuál es la más adecuada para nuestro algoritmo.

Al programar todas las medidas de distancia anteriores se han tenido en cuenta los siguientes
puntos:

 * Todas utilizan la jerarquía de WordNet 3.1 construida con ```wordnet-blast``` haciendo uso
   únicamente de las relaciones de hiponimia/hiperonima.

 * A las medidas basadas en el contenido de información que necesitaban de un *corpus* se les
   ha proporcionado los datos del SemCor expuesto anteriormente.

 * Todos los valores devueltos de distancia, ``d``, y similaridad, ``s`` se han normalizado en
   el intervalo :math:`[0, 1]` de tal forma que se cumpla para cualquier par de conceptos
   :math:`c_i, c_j` la igualdad siguiente :math:`s(c_i, c_j) + d(c_i, c_j) = 1`.


Distancia y jerarquía entre relaciones UNL
------------------------------------------
En la bibliografía no hemos encontrado ningún documento acerca de la distancia semántica entre
relaciones UNL, así es que tenemos que proponer una. Para ello planteamos un modelo muy simple
basado en la jerarquía de relaciones que aparece en UNLWeb [#]_.

.. [#] UNL Wiki. Universal Relations. http://www.unlweb.net/wiki/Universal_Relations 
   (accedido en junio de 2015)
   
Proponemos un modelo según el cual dos relaciones son iguales si pertenecen a la misma
tipología de primer nivel (agt, and, aoj,...) y distintas en caso contrario (ver
:num:`figura #fig-unl-relations`).

.. _fig-unl-relations:
.. graphviz::
   :caption: Jerarquía de relaciones UNL propuesta en UNLWeb.

   digraph foo {
        rankdir=LR
        node [shape=box]
        
        r[label="rel\n[relation]"]
        
        n01[label="agt\n[agent]"]
        n02[label="and\n[conjunction]"]
        n03[label="aoj\n[object of an attribute]"]
            n03_m01[label="ant\n[antyonym, different form]"]
            n03_m02[label="equ\n[synonym, equal to]"]
            n03_m03[label="fld\n[field]"]
            n03_m04[label="icl\n[hyponym, a kind of]"]
            n03_m05[label="iof\n[example, instance of]"]
            n03_m06[label="pof\n[meronym, part of]"]
            
        n04[label="ben\n[beneficiary]"]
        n05[label="cnt\n[content or theme]"]
        n06[label="con\n[condition]"]
        n07[label="exp\n[experiencer]"]
        n08[label="mod\n[modifier]"]
            n08_m01[label="mat\n[material]"]
            n08_m02[label="nam\n[name]"]
            n08_m03[label="pos\n[possessor]"]
            n08_m04[label="qua\n[quantifier]"]

        n09[label="obj\n[patient]"]
            n09_m01[label="opl\n[objective place]"]
            n09_m02[label="res\n[result]"]
            
        n10[label="or\n[disjunction]"]
        n11[label="per\n[proportion, rate, distribution\nor basis for a comparison]"]
            n11_m01[label="bas\n[basis for a comparison]"]

        n12[label="plc\n[location: physical or logical]"]
            n12_m01[label="gol\n[final place or state, destination]"]
            n12_m02[label="lpl\n[logical place, scene]"]
            n12_m03[label="src\n[initial place or state, origin]"]
            n12_m04[label="via\n[intermediate place, path]"]

        n13[label="ptn\n[partner]"]
        n14[label="tim\n[time]"]
            n14_m01[label="tmf\n[initial time]"]
            n14_m02[label="tmt\n[final time]"]
            n14_m03[label="dur\n[duration]"]
                n14_m03_l01[label="coo\n[co-occurrence]"]
        
        n15[label="man\n[manner]"]
            n15_m01[label="ins\n[instrument or method]"]
                n15_m01_l01[label="met\n[method]"]
            n15_m02[label="pur\n[purpose]"]

        n15[label="rsn\n[reason]"]
        n15[label="seq\n[consequence]"]
        
        r -> n01
        r -> n02
        r -> n03
            n03 -> n03_m01
            n03 -> n03_m02
            n03 -> n03_m03
            n03 -> n03_m04
            n03 -> n03_m05
            n03 -> n03_m06
        r -> n04
        r -> n05
        r -> n06
        r -> n07
        r -> n08
            n08 -> n08_m01
            n08 -> n08_m02
            n08 -> n08_m03
            n08 -> n08_m04
        r -> n09
            n09 -> n09_m01
            n09 -> n09_m02
        r -> n10
        r -> n11
            n11 -> n11_m01
        r -> n12
            n12 -> n12_m01
            n12 -> n12_m02
            n12 -> n12_m03
            n12 -> n12_m04
        r -> n13
        r -> n14
            n14 -> n14_m01
            n14 -> n14_m02
            n14 -> n14_m03
                n14_m03 -> n14_m03_l01
        r -> n15
            n15 -> n15_m01
                n15_m01 -> n15_m01_l01
            n15 -> n15_m02
   }


Algoritmo de McGregor
---------------------
El modelo que proponemos se basa en la búsqueda de máximos grafos comunes, es un problema
bastante tratado en la bibliografía. Existen dos aproximaciones muy frecuentes para la 
resolución de este problema: convertirlo en un problema de búsqueda del máximo *clique* o
realizar una búsqueda con retroceso.

El algoritmos propuesto por McGregor en 1982 :cite:`McGregor1982` pertenece a los segundos, 
según Bunke *et al* :cite:`Bunke2002` esta aproximación es más eficiente cuando el número de
conexiones es pequeño, como es el caso de los grafos conceptuales.

Este algoritmo lo hemos incorporado a nuestro modelo utilizando la implementación disponible 
en las librerías Boost de C++ [#]_.

.. [#] Boost Graph Library: McGregor Common Subgraphs. Boost C++ Libraries.
   http://www.boost.org/doc/libs/1_58_0/libs/graph/doc/mcgregor_common_subgraphs.html
   (accedido en junio de 2015)

   