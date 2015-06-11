

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

wordnet-blast
-------------

Medidas de distancia entre conceptos
------------------------------------
En el estado del arte hemos visto varios intentos por diferentes autores para lograr una
medida de distancia (similaridad en algunos casos) entre conceptos utilizando la jerarquía de
WordNet. Nosotros hemos implementado las siguientes utilizando el lenguaje C++:

 * Jiang y Conrath (1997)
 * Leacock y Chodorow (1998)
 * Lin
 * Resnik (1995)
 
 * Sussna (1993) :cite:`Sussna1993`: en la ecuación :eq:`sussna` mostramos la formulación
   que aparece en la bibliografía para el cálculo del peso de las conexiones entre los 
   conceptos. Según Sussna este peso, que representa la distancia semántica, debe ser menor
   cuanto mayor sea el número de conexiones del mismo tipo que parten de cada nodo; sin embargo
   la formulación proporcionada no se comporta según lo pretendido.
   
   En nuestro modelo hemos implementado el comportamiento que creemos que debería ser el
   correcto [#]_.
   
.. TODO: Insertar imagen con gráfica distancia-vs-numero conexiones
   
   
 * Wu y Palmer
 * Rada *et al* (1989)

 
.. [#] No se ha contactado con el autor del artículo para consultar esta discrepancia.
 
Todas estas medidas pueden ser intercambiadas en nuestro modelo obteniéndose diferentes valores
de similaridad entre grafos, podemos evaluarlas de este modo en un contexto más amplio y
verificar cuál es la más adecuada para nuestro algoritmo.

Al programar todas las medidas de distancia anteriores se han tenido en cuenta los siguientes
punto:

 * Todas utilizan la jerarquía de WordNet 3.1 construida con ```wordnet-blast``` haciendo uso
   únicamente de las relaciones de hiponimia/hiperonima.

 * A las medidas basadas en el contenido de información que necesitaban de un *corpus* se les
   ha proporcionado los datos del SemCor expuesto anteriormente.

 * Todos los valores devueltos de distancia, ``d``, y similaridad, ``s`` se han normalizado en
   el intervalo :math:`[0, 1]` de tal forma que se cumpla para cualquier par de conceptos
   :math:`c_i, c_j` la igualdad siguiente :math:`s(c_i, c_j) + d(c_i, c_j) = 1`.


Jerarquía de relaciones UNL
---------------------------

Algoritmo de McGregor
---------------------
