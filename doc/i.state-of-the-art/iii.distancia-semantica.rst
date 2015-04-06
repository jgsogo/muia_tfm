
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

Limitaciones del lenguajes
``````````````````````````
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
