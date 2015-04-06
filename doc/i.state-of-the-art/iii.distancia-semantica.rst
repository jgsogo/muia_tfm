
Distancia semántica entre textos
--------------------------------
El problema que pretendemos abordar en esta tesis debe combinar una medida de distancia
asociada al grafo de representación del contenido con una medida de distancia entre
conceptos. Para medir la distancia que separa un grafo de otro debemos medir también
cuál es la distancia que separa los atributos de los nodos y los arcos de un grafo respecto
a los del otro y, en nuestro caso, los atributos de los nodos son conceptos, por lo que
tendremos que aplicar medidas de distancia semánticas entre dichos conceptos.

En la literatura encontramos algunas medidas de distancia asociadas a los grafos conceptuales
(:num:`sección #grafos-conceptuales`), en ellas se aborda el problema conjunto que estamos
presentando aquí; en algunos casos se orienta hacia la búsqueda exacta de un patrón en un
conjunto de grafos, pero en otros se implementan medidas de similaridad que pueden tomar
valores en un rango continuo.


Fenómenos lingüísticos
``````````````````````
Introducimos aquí una problemática que surge en el problema de comparación de grafos que
codifican información. En algunos casos una misma información puede codificarse de formas
diferentes, una medida de distancia que no tuviera en cuenta esta posibilidad podría señalar
dos grafos como diferentes cuando la información codificada es exactamente la misma.

Los dos fenómenos lingüísticos principales que pueden provocar este engaño son:

 * Sinonimia: dos términos diferentes pueden representar exactamente el mismo concepto; en el
   caso de los grafos UNL donde los nodos contienen conceptos en vez de términos este fenómeno
   no es un problema puesto que, por construcción, si dos términos representan el mismo
   concepto entonces estarán representados por la misma palabra universal.
 * Paráfrasis: la paráfrasis consiste en transmitir el contenido del texto utilizando otras
   palabras. Una buena traducción debe ser fiel al texto original, pero podemos encontrarnos
   con dos traducciones igual de buenas donde algunas expresiones sean distintas. Una medida
   de distancia captará estas diferencias, debemos ser conscientes de ellas para poder
   interpretar los resultados.

.. warning:: Puesto que los fenómenos lingüísticos entre conceptos individuales en ontologías
   como WordNet ya han sido tratados más arriba, aquí sólo quedaría hablar de dos tipos de
   fenómenos: 1) metáforas y otras figuras retóricas, que se escapan a las pretensiones de
   NLP y 2) paráfrasis, que probablemente quede fuera del ámbito de esta tesis. 

   Hablar de **paráfrasis** básicamente consistiría en describir el fenómeno, identificar los
   distintos tipos de paráfrasis y ver cuál es el resultado de cada uno de ellos en un grafo
   UNL. La distancia entre dos contrucciones parafrásticas debería ser cero. Básicamente son
   estructuras equivales en un grafo.

   ¿Existen otros fenómenos que modifiquen la estructura pero no alteren el contenido semántico?

Limitaciones del lenguaje
`````````````````````````
En el proceso de traducción automática que hemos mostrado en la
:num:`figura #fig-problema-interlingua` donde comparamos los grafos de interlingua producidos
a partir de los generadores con el grafo en interlingua de partida, la información que
tendrán los grafos generados a partir de los textos traducidos no podrá ser mayor que la
información que es posible expresar en los lenguajes de destino.

Así, si el texto original es en japonés y aparece el término ``ikebana``, éste será codificado
en UNL mediante la UW ``ikebana(icl>flower arrangement)``, al traducir este texto al español,
idioma en el que no existe una tradución fiel para este concepto, el generador tendrá que optar
por un térmmino aproximado como ``arreglo floral`` donde ya se han perdido las connotaciones que
este término tenía en japonés. Al generar a partir de la traducción en español la interlingua
de nuevo, las connotaciones que se han perdido ya no volverán a recuperarse y en el nuevo
grafo aparecerá la UW ``flower arrangement``. En este ejemplo existirá una distancia entre la
interlingua original y la producida después de la traducción, pero esta distancia no podrá
achacarse al generador sino a las limitaciones del lenguaje.

Hemos visto una limitación provocada por carencia de vocabulario, pero las diferencias entre
las lenguas son muy diversas y en cada traducción se pierden inevitablemente matices que no
pueden volver a recuperarse sin la ayuda humana que pueda extraerlos del contexto o
interpretarlos e incorporarlos al texto traducido.

.. warning:: Documentar las carencias del lenguaje en el libro de Enrique Bernárdez.


Modelos propuestos en la bibliografía
`````````````````````````````````````
La mayoría de los modelos de comparación de grafos aparecen relacionados con la investigación
en el campo de la recuperación de información; muchos de ellos se limitan al problema de
determinar si un grafo está contenido dentro de otro, se limitan a problemas de búsqueda donde
no se obtiene ninguna medida de similaridad. Otros métodos más generales miden la similaridad
en base al conjunto de elementos que tienen en común los grafos a comparar :cite:`Montes2000`.

En el problema que nos ocupa necesitamos poder comparar grafos de una forma flexible, donde se
permita que los atributos de los nodos o los arcos sean diferentes.

En :cite:`Montes2001` Montes-y-Gómez *et al.* proponen un modelo flexible para comparar grafos
conceptuales, en él primero se construye el conjunto de todos los solapamientos posibles entre
ambos grafos y posteriomente se calcula la similaridad a partir de dos valores de similaridad
conceptual y relacional igual que en :cite:`Montes2000`, cada uno de estos valores se obtiene
utilizando una expresión análoga al coeficiente Sørensen-Dice. En los cálculos el modelo
propuesto utiliza un tesauro de conceptos (con relaciones de hiponimia) y varios parámetros
que el usuario puede modificar de acuerdo a sus intereses.

Otra aproximación interesante es la mostrada por Zhong *et al.* en :cite:`Zhong2002`, en ella
se utiliza el nodo de entrada del grafo conceptual como nodo de comienzo del algoritmo y se
propone un método recursivo. La similaridad entre dos grafos conceptuales consistirá en la
similaridad entre estos dos nodos de entrada y el máximo valor de similaridad que se obtenga
de todas las combinaciones de subgrafos que sean hijos de este nodo de entrada ponderadas 
por el peso de las relaciones que los unen con el nodo de entrada. El algoritmo va progresando
por el grafo hasta que se agotan todas las combinaciones posibles.
En el artículo limitan la aplicación a grafos con estructura de árbol (no presentan ciclos).


.. warning:: Artículos pendientes de revisión:

   :cite:`Ganapathy2013` (sin acceso al contenido)

   :cite:`Myaeng1992` (sin acceso al contenido) Uno de los autores es Aurelio López-López,
   que aparece en las referencias de Montes-y-Gómez y este articulo es 10 años anterior, así
   que probablemente no añada nada.

   :cite:`Cho2010` (sin acceso al contenido) Utiliza un RandomWalk para calcular la
   similaridad entre los grafos. Es una idea que lleva un tiempo rondándote por la cabeza,
   al menos ver cómo la implementa.

Ambas aproximaciones utilizan modelos combinatorios cuya aplicación en grafos grandes es
cuestionable, no obstante, al igual que en nuestro caso, se centrar en pequeñas oraciones donde
el número de nodos y conexiones es relativamente pequeño por lo que los tiempos de cálculo
son aceptables para la experimentación.