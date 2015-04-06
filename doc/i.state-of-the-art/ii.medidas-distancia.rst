
Medidas de distancia y similaridad
----------------------------------
La diferencia semántica entre dos grafos que codifican información puede interpretarse en
términos de distancia o similaridad entre la estructura de los grafos y también entre los
conceptos que están presentes en cada grafo. Dos grafos (coceptuales o UNL) pueden
codificar una información totalmente distinta a pesar de compartir la estructura, pero
también pueden tener la misma información a pesar de mostrar estructuras ligeramente
diferentes (paráfrasis).

.. warning:: Comentar diferencias entre distancia y similaridad. Una medida de distancia
   debe cumplir las tres/cuatro propiedades mientras que una de similaridad para que no es tan
   estricta. Documentar e introducir brevemente.

.. warning:: Por aquí comienza a emerger el caracter combinatorio del problema, queremos
   medir la distancia entre dos grafos que tienen ruido, donde la distancia se va a deber
   tanto a la diferencia de estructura como de los conceptos presentes en los nodos. Nos
   interesa la mínima distancia considerando todas las combinaciones de estructuras y
   conceptos.

Comparación de grafos
`````````````````````
La comparación de grafos es un problema muy prolífico en la literatura; desde hace tiempo,
multitud de problemas en el ámbito del reconocimiento de patrones se han codificado en forma
de grafos, una herramienta muy potente para representar la información de forma clara y
concisa. Pero los grafos no sólo se utilizan para almacenar la información, en muchos casos
es precisa la búsqueda de patrones dentro de un conjunto de grafos, o la clasificación de
un nuevo grafo. Y aquí es donde se plantea el problema, ¿qué significa exactamente comparar
dos grafos? :cite:`Jolion2001`. Una definición puede ser "encontrar en un grafo :math:`G_1`
cuál es el subgrafo :math:`G'_1` que es similar (exacto o parcial) a un subgrafo :math:`G'_2`
de otro grafo :math:`G_2`".

La comparación entre los grafos puede realizarse de manera exacta (isomorfismo, *exact matching*)
o bien permitir cierta tolerancia a errores puesto que los datos pueden contener ruido. 
En el caso de la traducción automática lo que pretendemos medir es precisamente las variaciones
introducidas por cada traductor respecto al contenido del texto original, en definitiva, el ruido;
por lo tanto nos interesarán las técnicas de comparación inexacta. Nuestro objetivo no es
*encontrar* un grafo igual, sino comparar dos grafos que *a priori* van a ser distintos.
Además debemos tener presente que nuestros grafos tienen atributos tanto en los nodos
como en los arcos.

.. warning:: Si en el modelo convertimos nuestro grafo UNL a un **grafo bipartito** entonces no
   tendríamos atributos en los arcos... Es una opción.

.. warning:: Introducir en lo anterior citas a los papers con surveys de algoritmos de
   comparación de grafos de los que se toma el apartado de comparación de grafos: :cite:`Conte2004`

Comparación inexacta de grafos
++++++++++++++++++++++++++++++
Una de las estrategias habituales para abordar este problema es asignar un coste a las
discrepancias/errores existentes entre los grafos, surge así un problema combinatorio cuya solución
consistirá en encontrar la correspondencia cuyo coste sea mínimo (*error correcting* o 
*error-tolerant*).
Otra aproximación al problema consiste en definir un conjunto de operaciones de edición de un
grafo, asignar un coste a cada una de ellas y buscar la secuencia de ediciones cuyo coste sea
menor que nos permiten convertir un grafo en otro (*graph edit cost*).

Cualquiera de estas estrategias de coste mínimo puede ser utilizada para calcular una medida de
disimilaridad entre grafos; una adecuada elección de los costes de cada una de las operaciones
permite que la métrica de coste de edición cumpla las propiedades matemáticas de una
distancia, definiéndose una *distancia entre grafos* que permite aplicar a este dominio algunos
algoritmos de otros espacios métricos :cite:`Conte2004`; se conoce entonces como
*graph edit distance*. Algunos autores como Bunke han demostrado que el problema del *subgrafo
máximo común*, y el isomorfismo entre grafos y subgrafos, pueden ser reducidos al cálculo de
la *graph edit distance*.

.. warning:: Revisar las referencias de Bunke en :cite:`Conte2004` para incluirlas si procede
   en el párrafo anterior cuando se habla de las "demostraciones de Bunke".

.. warning:: En el párrafo anterior se habla del concepto *subgrafo máximo común*, pero no se
   ha introducido en ningún momento. Antes de este punto habría que introducir también la
   comparación de grafos utilizando el subgrafo-máximo-común y el supergrafo-mínimo, son dos
   alternativas que también ofrecen referencias.

Muchos de los algoritmos utilizados para la comparación inexacta de grafos utilizan heurísticas
para explorar el espacio de búsqueda, ya que en muchos casos se considera un probleam NP-completo;
sin embargo el tipo de grafos que utilizaremos nosotros son suficientemente pequeños como para
que el tiempo de cálculo no sea una variable a tener en cuenta. Nos interesa, por tanto,
mostrar las familias de algoritmos utilizados desde el punto de vista de la formulación del
problema, así en podemos identificar las siguientes :cite:`Conte2004`:

 * Optimización continua: convierte el problema de comparación de grafos, que en principio es
   un problema de optimización discreta, en un problema continuo no lineal y se aplican
   diferentes algoritmos o heurísticas para obtener un solución suficientemente buena.
 * Métodos espectrales: basadas en los autovalores y autovectores calculados a partir de la
   matriz de adyacencia. El inconveniente de estos métodos es que sólo tienen en cuenta la
   estructura del grafo y no los atributos de los nodos y arcos.
 * Conversión a un grafo bipartito: convertir el problema a este tipo de grafos permite
   aplicar algoritmos con tiempo de solución de orden polinómico.
 * *Elastic Graph Matching* (EGM): se trata de abordar el problema comparando las imágenes de
   las estructuras de los dos grafos.

.. warning:: A continuación puedo exponer algunos métodos con bibliografía donde vayan depurando
   el algoritmo, pero prefiero esperar un poco para profundizar en el algoritmo elegido para el
   modelo e implementación. Si no, esto va a parecer un *survey* de algoritmos de comparación
   de grafos. De todos modos puede ser interesante explorar las diferentes formulaciones del
   problema, ya que en algún momento habrá que justificar por qué se ha elegido una de ellas.
   Por tener ejemplos:

   Graph edit distance
      Aquí hay unos cuantos papers, si seguimos este camino hay que preparar un compendio.

   Continouos optimization - relaxation labelling
      In 1995, Christmas et al.27 proposed a method, based on the theoretical framework of Kittler and Hancock, that is able to take into account during the iteration process (and not only during initialization) both node and edge attributes.

   Bipartite graph matching
      For this approach we can cite the papers by Wang et al.163 in 1994, by El-Sonbaty and Ismail42 in 1998, by Baeza and Valiente5 in 2000 and by Liu et al.92 in the same year


Distancia en redes de conceptos
```````````````````````````````
Igual de importante que comparar los grafos que codifican la información es ser capaces de
estimar cuál es la distancia o la similaridad entre dos conceptos. De esta forma podemos asignar
costes a la sustitución de un nodo por otro o a los errores en la correspondencia de los
elementos de los grafos en los algoritmos mostrados en el apartado anterior. Debemos tener presente
que en nuestro caso no existe el problema de desambiguar puesto que los conceptos presentes en 
un grafo conceptual o en UNL están perfectamente identificados [#]_.

.. [#] La identificación en UNL está realizada en base a las *Universal Words* cuya correspondencia
   con los *synsets* de WordNet no es inmediata. Aunque la mayoría de las medidas de distancia
   hacen referencia a WordNet, la Ontología UNL tiene una estructura basada en las mismas
   relaciones de hiponimia y meronimia por lo que los algoritmos pueden aplicarse en una u otra
   red de conceptos de la misma manera.

La distancia semántica entre conceptos ha sido un tema que ha captado la atención investigadora
desde hace mucho tiempo; y con el surgimiento de las redes de conceptos como MeSH
(http://www.nlm.nih.gov/mesh/) o WordNet ha tenido un impulso notable.

.. warning:: Para un review de medidas más amplio se puede empezar por :cite:`Slimani2013` y
   :cite:`Jiang1997`. Tengo que decidir el nivel de la exposición que voy a hacer aquí,
   no puedo convertir cada apartado en una recopilación de todos los métodos...

La medida de la similaridad entre conceptos se ha abordado desde tres perspectivas principales
:cite:`Slimani2013`: basadas en la estructura de la red de conceptos, centradas en el contenido
de información de cada nodo y aproximaciones basadas en características de
los términos. Por supuesto, también hay otros propuestas que utilizan medidas híbridas que combinan
varias de estas perspectivas.

Basadas en la estructura
++++++++++++++++++++++++
Considerar la jerarquía de conceptos y el número de conexiones existentes entre ellos es una
de las maneras más sencillas y naturales de calcular su similaridad. No obstante, parece
lógico pensar que la distancia entre dos nodos adyacentes cualesquiera no tiene por qué ser
idéntica, así cada conexión debe tener un peso asignado en el cálculo de esta distancia. En
redes muy grandes, como es el caso que nos ocupa, esta peso no puede ser asignado manualmente
para cada conexión, deben implementarse algoritmos que permitan calcularlo basándose en
características de la red. Algunas de estas características estructurales típicamente
relacionadas con una red de conceptos jerárquica son :cite:`Jiang1997`:

 * **Densidad**: la densidad de la red no es la misma en todas sus partes, se puede sugerir
   que cuanto mayor es la densidad en una zona, menor es la distancia entre los nodos que 
   están en esa zona :cite:`Richardson1995`.
 * **Profundidad**: cuanto más se desciende en la jerarquía más sutiles son las diferencias
   entre los conceptos, por lo tanto la distancia entre los nodos es cada vez menor.
 * **Tipo de conexión**: el peso de cada conexión será diferente según el tipo de relación
   que indique: hiponimia, meronimia, antonimia, etc.
 * **Fuerza de cada conexión**: en la relación de un nodo con sus hijos no todas las
   conexiones tienen que tener el mismo peso. En este punto es donde los métodos estadísticos
   basados en el contenido de información (ver más abajo) pueden ser útiles.

En general, todos los algoritmos que utilizan la estructura de la red calculan la distancia
entre dos conceptos a través del camino más corto entre ellos utilizando únicamente las
relaciones de hiponimia. 

Contenido de información
++++++++++++++++++++++++
Los métodos basados en el contenido de información de los nodos se apoyan en una colección
de documentos de la que extraen las frecuencias de aparición de cada término. La primera
vez en la que se utiliza el contenido de información pudo ser en 1995 por Resnik 
:cite:`Resnik1995` quien sólo tenía en cuenta la frecuencia de aparición de un término para
evaluar su contenido de información. Propuestas más recientes consideran también los posibles
conceptos a los que puede hacer referencia el término. El cálculo de la distancia entre dos
conceptos puede realizarse combinando en una ecuación el contenido de información de ambos
términos y el de todos los elementos que se encuentran en el camino que los une.

.. warning:: Explicar más esto, mostrando cómo funciona algún modelo de los que aparecen en
   :cite:`Slimani2013` o :cite:`Jiang1997`

Basadas en características de los términos
++++++++++++++++++++++++++++++++++++++++++
Una aproximación diferente permite calcular la similaridad entre dos conceptos basándose en
características descriptivas de cada uno de ellos, el valor de similaridad se calcula
utilizando formulaciones análogas al coeficiente de Jaccard.
Uno de los principales incovenientes para poder aplicar este tipo de modelos es que normalmente
no se dispone de un conjunto de características homogeneo para todos los conceptos.