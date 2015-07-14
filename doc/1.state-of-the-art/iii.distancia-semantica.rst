
Distancia semántica entre textos
--------------------------------
El problema que pretendemos abordar en esta tesis debe combinar una medida de distancia
asociada al grafo de representación del contenido con una medida de distancia entre
conceptos. Para medir la distancia que separa un grafo de otro tenemos que considerar la
estructura de los mismos, pero también debemos medir cuál es la distancia que separa los
atributos de los nodos (conceptos) y los arcos (relaciones).

En la literatura encontramos algunas medidas de distancia asociadas a los grafos conceptuales
(:ref:`sección 2.1.2 <grafos-conceptuales>`), en ellas se aborda el problema conjunto que estamos
presentando aquí; en algunos casos se orienta hacia la búsqueda exacta de un patrón en un
conjunto de grafos, pero en otros se implementan medidas de similaridad que pueden tomar
valores en un rango continuo.

Antes de mostrar los modelos propuestos en la bibliografía debemos exponer dos
características del lenguaje que tenemos que tener muy presentes para valorar las
dificultades a las que se enfrentan.

.. _fenomenos-linguisticos:

Fenómenos lingüísticos
``````````````````````
El lenguaje natural está repleto de ambigüedades que solo se resuelven en la interacción
entre los interlocutores (o entre el escritor y el lector de un texto), lo presentábamos
anteriormente como "principio de cooperación" :cite:`Grice1975`. Además, una gran cantidad
de matices (o incluso elementos relevantes de una lengua) no pueden ser representados
ni en los grafos conceptuales ni en los grafos UNL, y, lo que puede ser más grave, la
interpretación de una misma oración puede ser muy distinta incluso entre personas del
mismo sustrato cultural como han mostrado Teixeira *et al.* :cite:`Martins2002` o
Hutchins :cite:`Hutchins1992`.

Estas ambigüedades pueden darse asociadas a tres fenómenos presentes en los
lenguajes naturales, a saber:

 * **Sinonimia**: la RAE define el término sinónimo como "Dicho de un vocablo o de una
   expresión: Que tiene una misma o muy parecida significación que otro." [#]_, por lo
   tanto a la hora de asignar términos a un concepto o UW en el lenguaje UNL, según
   el grado de semejanza, se identificarán con la misma UW o diferentes.
   
   El problema es que no hay una unidad de medida objetiva para la semejanza
   semántica entre palabras; dos sinónimos *totales* son intercambiables en cualquier
   contexto y deberán ser asignados a la misma UW, pero en el caso de sinonimia *parcial*
   donde cada voz conserva rasgos connotativos propios, la asignación o no a una misma UW 
   resulta subjetiva, dependiente del sustrato socio-cultural o incluso del
   contexto en que aparece (melioración y peyoración) :cite:`MartinellGifre1994`
   :cite:`Gelabert1994`.

   Muchos de estos matices se pierden cuando en el grafo son representados por una misma UW,
   aunque los atributos de UNL permiten codificar algunos de estos rasgos.

 * **Polisemia**: un mismo término puede hacer referencia a dos conceptos distintos; este
   fenómeno queda perfectamente cubierto en la codificación a través de UWs. Teniendo el
   grafo, la polisemia está perfectamente desambiguada.

 * **Paráfrasis**: la paráfrasis consiste en transmitir un mismo mensaje utilizando otras
   palabras. Una buena traducción debe ser fiel al texto original, pero podemos encontrarnos
   con dos traducciones igual de buenas donde algunas expresiones sean distintas. Una medida
   de distancia será sensible a estas diferencias, debemos ser conscientes de ellas para poder
   interpretar los resultados.

.. [#] Real Academia Española. Diccionario de la lengua española. 22ª edición (2012)

Estos fenómenos pueden afectar de forma importante a la medida de distancia semántica entre
grafos indicando que son diferentes dos oraciones cuyo contenido semántico podría ser el
mismo. Hay que ser consciente de estos fenómenos para identificarlos cuando aparezcan y 
valorar su influencia en las medidas propuestas.



Limitaciones del lenguaje
`````````````````````````
En el proceso de traducción automática que hemos mostrado en la
:ref:`figura 1.2 <fig-problema-interlingua>` donde comparamos los grafos de interlingua producidos
a partir de los generadores con el grafo en interlingua de partida, la información que
tendrán los grafos generados a partir de los textos traducidos no podrá ser mayor que la
información que es posible expresar en los lenguajes de destino. Es decir, ningún grafo
obtenido a partir de un texto puede contener más información que el propio texto.

Así, si el texto original es en japonés y aparece el término *ikebana*, este será codificado
en UNL mediante la UW ``ikebana(icl>flower arrangement)``, al traducir este texto al español,
idioma en el que no existe una traducción exacta para este concepto, el generador tendrá que optar
por un término aproximado como *arreglo floral* donde ya se han perdido las connotaciones
artísticas que este término tenía en japonés.

Al generar a partir de la traducción en español la interlingua no podrán recuperarse
los matices que ya se han perdido y en el nuevo
grafo aparecerá la UW ``flower arrangement``. En este ejemplo existirá una distancia entre la
interlingua original (generada a partir del texto en japonés) y la producida después de la
traducción (generada a partir del texto en español), pero esta distancia no podrá
achacarse al generador ni al algoritmo, sino que será consecuencia de las limitaciones
del lenguaje.

Esta pérdida de información que hemos mostrado como ejemplo está provocada por carencia de
vocabulario, pero las diferencias entre las lenguas son muy diversas y mucho
más profundas (el lector interesado podrá encontrar una buena muestra en la obra de
Eco :cite:`Eco1999`).

.. TODO: Documentar las carencias del lenguaje en el libro de Bernárdez.


Modelos propuestos en la bibliografía
`````````````````````````````````````
La mayoría de los modelos de comparación de grafos conceptuales aparecen relacionados con
la investigación en el campo de la recuperación de información; muchos de ellos se limitan
al problema de determinar si un grafo está contenido dentro de otro, son problemas de
recuperación de información donde no se obtiene ninguna medida de similaridad :cite:`Ellis1994` :cite:`Huibers1996` :cite:`Cardenosa2013`.
En el problema que nos ocupa necesitamos poder comparar grafos de una forma flexible, donde se
permita que los atributos de los nodos o los arcos sean diferentes, pero aún así se establezca
una relación entre ellos que permita continuar con la comparación.

Algunos algoritmos, como el de Myaeng y López-López :cite:`Myaeng1992` introducen un primer 
nivel de flexibilidad al realizar la búsqueda utilizando el concepto de máximo subgrafo común
(ver :ref:`sección 2.2.1 <maximo-grafo-comun>`); su algoritmo calcula una medida de similaridad
en función del conjunto de todos los MCS, sin embargo, la correspondencia entre los elementos
tiene que ser exacta.

**Montes-y-Gómez et al.** :cite:`Montes2000` utilizan el mismo planteamiento: el
proceso de comparación comienza por el cálculo de todos los MCS y partiendo de esta nueva
estructura se calcula una medida de similaridad, :math:`s`, que combina la similaridad
conceptual :math:`s_c` y la relacional :math:`s_r`.

Dados dos grafos conceptuales :math:`G_1` y :math:`G_2` y el grafo :math:`G_1 \cap G_2 = G_c`
se calculan la similaridad conceptual de forma análaga al coeficiente de Sørensen-Dice
utilizado en recuperación de información:

.. math::
    
    s_c = \frac{2 \cdot n(G_c)}{n(G_1) + n(G_2)}

donde :math:`n(G)` es el número de nodos tipo concepto del grafo ``G``.

Para la similaridad relacional utilizan los arcos que unen los conceptos y que están presentes
en :math:`G_c` o en conexión con él:

.. math::

    s_r = \frac{2 \cdot m(G_c)}{m_{G_c}(G_1) + m_{G_c}(G_2)}

:math:`m(G_c)` es el número de arcos que hay en :math:`G_c`, y :math:`m_{G_c}(G)` es el número
de arcos que hay en la inmediata vecindad de :math:`G_c` y que pertenecen al grafo ``G``.

El valor final de similaridad se obtiene como combinación lineal de los otros dos:

.. math::

    s = s_c \cdot (a + b \cdot s_r)

de tal forma que aunque no compartan ninguna conexión podrá haber una similaridad basada en
los conceptos presentes en ambos grafos.

Un año después, **Montes-y-Gómez et al.** :cite:`Montes2001` proponen un nuevo algoritmo
que permite una mayor flexibilidad en la correspondencia de los términos utilizando un
tesauro con relaciones de hiponimia adaptado al usuario. En primer lugar calculan el conjunto
de todas las superposiciones (*overlaps*) posibles de tamaño máximo entre los dos grafos
a comparar :math:`G_1` y :math:`G_2`.

A continuación calculan la similaridad entre los grafos de partida y cada uno de los
*overlaps* calculados utilizando una formulación igual a la del anterior artículo donde
combinan similaridad conceptual y relacional: :math:`s = s_c \cdot (a + b \cdot s_r)`.

Para la comparación entre cada par de conceptos y de relaciones utilizan una formulación
en la que intervienen numerosos parámetros que debe definir el usuario que ponderan el
peso de cada concepto según su categoría gramatical o la distancia en el tesauro, y lo mismo
para las relaciones.


**Zhong et al.** :cite:`Zhong2002` proponen un algoritmo para recuperación de información
en motores de búsqueda para un dominio específico. El algoritmo utiliza una medida de
similaridad entre conceptos y otra entre relaciones para utilizarlas en la comparación de
los grafos conceptuales.

La similaridad entre conceptos la basan en la profundidad de éstos dentro de la red jerárquica
de hiponimia de WordNet, desarrollan una medida propia de una manera análoga a la mostrada en la
:ref:`sección 2.2.2 <redes-conceptos-estructura>`.

Para la similaridad entre relaciones también utilizan una jerarquía de relaciones desarrollada
por ellos mismos, de tal forma que el valor de similaridad entre una relación :math:`r_Q` del
grafo de búsqueda y otra :math:`r_R` del grafo en el que se busca es:

.. math::

    s(r_Q, r_R) = 1 - d(r_Q, r_R) = \begin{cases}
    1, & r_Q \quad subsumes \quad r_R\\
    0, & otherwise.
    \end{cases}

es decir, que la similaridad solo valdrá :math:`1` en el caso de que la relación presente en el
grafo de búsqueda sea más general que la presente en el grafo con el que se compara. Esta
circunstancia provoca que la medida resultante del algoritmo no sea simétrica.

Para la comparación de los grafos, Zhong *et al.* además tienen en cuenta que éstos poseen un
nodo de entrada o raíz (este nodo está presente en los grafos conceptuales y también en
los grafos UNL), que será por el que comience su algoritmo.

De este modo crean un algoritmo recursivo que comienza por el nodo raíz de cada grafo y
continúa comparando todas las posibles combinaciones de los subgrafos que cuelgan de este, el
algoritmo devolverá el valor máximo de similaridad entre todas las posibles combinaciones.

.. TODO: Artículos pendientes de revisión:

   :cite:`Ganapathy2013` (sin acceso al contenido)

   :cite:`Myaeng1992` (sin acceso al contenido) Uno de los autores es Aurelio López-López,
   que aparece en las referencias de Montes-y-Gómez y este articulo es 10 años anterior, así
   que probablemente no añada nada.

   :cite:`Cho2010` (sin acceso al contenido) Utiliza un RandomWalk para calcular la
   similaridad entre los grafos. Es una idea que lleva un tiempo rondándote por la cabeza,
   al menos ver cómo la implementa.

.. Ambas aproximaciones utilizan modelos combinatorios cuya aplicación en grafos grandes es
   cuestionable, no obstante, al igual que en nuestro caso, se centran en pequeñas oraciones donde
   el número de nodos y conexiones es relativamente pequeño por lo que los tiempos de cálculo
   son aceptables para la experimentación.
