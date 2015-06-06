
Distancia semántica entre textos
--------------------------------
El problema que pretendemos abordar en esta tesis debe combinar una medida de distancia
asociada al grafo de representación del contenido con una medida de distancia entre
conceptos. Para medir la distancia que separa un grafo de otro tenemos que considerar la
estructura de los mismos, pero también debemos medir cuál es la distancia que separa los
atributos de los nodos (conceptos) y los arcos (relaciones).

En la literatura encontramos algunas medidas de distancia asociadas a los grafos conceptuales
(:num:`sección #grafos-conceptuales`), en ellas se aborda el problema conjunto que estamos
presentando aquí; en algunos casos se orienta hacia la búsqueda exacta de un patrón en un
conjunto de grafos, pero en otros se implementan medidas de similaridad que pueden tomar
valores en un rango continuo.


Fenómenos lingüísticos
``````````````````````
El lenguaje natural está repleto de ambigüedades que sólo se resuelven en la interacción
entre los interlocutores (o entre el escritor y el lector de un texto), lo presentábamos
anteriormente como "principio de cooperación" :cite:`Grice1975`. Además, una gran cantidad
de matices (o incluso elementos relevantes de una lengua) no pueden ser representados
ni en los grafos conceptuales ni en los grafos UNL, y, lo que puede ser más grave, la
interpretación de una misma oración puede ser muy distinta incluso entre personas del
mismo sustrato cultural como han mostrado Teixeira *et al.* :cite:`Martins2002` o
Hutchins :cite:`Hutchins1992`.

Estas ambigüedades pueden darse asociadas a dos fenómenos presentes en cualquier
lenguaje natural, a saber:

 * **Sinonimia**: la RAE define el término sinónimo como "Dicho de un vocablo o de una
   expresión: Que tiene una misma o muy parecida significación que otro." [#]_, por lo
   tanto a la hora de asignar términos a un concepto o UW en el lenguaje UNL, según
   el grado de semejanza, dos términos sinónimos se identificarán con la misma UW o
   diferentes. El problema es que no hay una unidad de medida objetiva para la semejanza
   semántica entre palabras.

   Los matices que portan los sinónimos se pierden cuando son asignados a la misma UW. 

.. [#] Real Academia Española. Diccionario de la lengua española. 22ª edición (2012)

 * **Polisemia**: un mismo término puede hacer referencia a dos conceptos distintos; este
   fenómeno queda perfectamente cubierto en la codificación a través de UWs. Teniendo el
   grafo, la polisemia está perfectamente desambiguada.

 * **Paráfrasis**: la paráfrasis consiste en transmitir un mismo mensaje utilizando otras
   palabras. Una buena traducción debe ser fiel al texto original, pero podemos encontrarnos
   con dos traducciones igual de buenas donde algunas expresiones sean distintas. Una medida
   de distancia será sensible a estas diferencias, debemos ser conscientes de ellas para poder
   interpretar los resultados.

Estos fenómenos pueden afectar muy sensiblemente a la medida de distancia semántica entre
grafos indicando que son diferentes dos oraciones cuyo contenido semántico podría ser el
mismo. Hay que ser consciente de estos fenómenos para identificarlos cuando aparezcan y 
valorar su influencia en las medidas propuestas.



Limitaciones del lenguaje
`````````````````````````
En el proceso de traducción automática que hemos mostrado en la
:num:`figura #fig-problema-interlingua` donde comparamos los grafos de interlingua producidos
a partir de los generadores con el grafo en interlingua de partida, la información que
tendrán los grafos generados a partir de los textos traducidos no podrá ser mayor que la
información que es posible expresar en los lenguajes de destino. Es decir, ningún grafo
obtenido a partir de un texto puede contener más información que el propio texto.

Así, si el texto original es en japonés y aparece el término *ikebana*, éste será codificado
en UNL mediante la UW ``ikebana(icl>flower arrangement)``, al traducir este texto al español,
idioma en el que no existe una tradución fiel para este concepto, el generador tendrá que optar
por un término aproximado como *arreglo floral* donde ya se han perdido las connotaciones que
este término tenía en japonés.

Al generar a partir de la traducción en español la interlingua
de nuevo, no podrán recuperarse los matices que ya se han perdido y en el nuevo
grafo aparecerá la UW ``flower arrangement``. En este ejemplo existirá una distancia entre la
interlingua original (generada a partir del texto en japonés) y la producida después de la
traducción (generada a partir del texto en español), pero esta distancia no podrá
achacarse al generador sino a las limitaciones del lenguaje.

Esta pérdida de información que hemos mostrado como ejemplo está provocada por carencia de
vocabulario, pero las diferencias entre las lenguas son muy diversas y mucho
más profundas (el lector interesado podrá encontrar una buena muestra en la obra de
Eco :cite:`Eco1999`)

.. TODO: Documentar las carencias del lenguaje en el libro de Bernárdez.


Modelos propuestos en la bibliografía
`````````````````````````````````````
La mayoría de los modelos de comparación de grafos aparecen relacionados con la investigación
en el campo de la recuperación de información; muchos de ellos se limitan al problema de
determinar si un grafo está contenido dentro de otro, son problemas de búsqueda donde
no se obtiene ninguna medida de similaridad. Otros métodos más generales miden la similaridad
en base al conjunto de elementos que son comunes en ambos grafos a comparar :cite:`Montes2000`.

En el problema que nos ocupa necesitamos poder comparar grafos de una forma flexible, donde se
permita que los atributos de los nodos o los arcos sean diferentes, pero aún así se establezca
una relación entre ellos que permita continuar con la comparación.

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
de todas las combinaciones de subgrafos que sean hijos de estos nodos ponderadas 
por el peso de las relaciones que los unen con el nodo de entrada correspondiente.
El algoritmo va progresando por el grafo hasta que se agotan todas las combinaciones posibles.
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
cuestionable, no obstante, al igual que en nuestro caso, se centran en pequeñas oraciones donde
el número de nodos y conexiones es relativamente pequeño por lo que los tiempos de cálculo
son aceptables para la experimentación.
