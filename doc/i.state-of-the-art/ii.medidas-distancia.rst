
Medidas de distancia y similaridad
----------------------------------
La diferencia semántica entre dos grafos que codifican información puede interpretarse en
términos de distancia o similaridad entre la estructura de los grafos y también entre los
conceptos que están presentes en cada grafo. Dos grafos (coceptuales o UNL) pueden
codificar una información totalmente distinta a pesar de compartir la estructura, pero
también pueden tener la misma información a pesar de mostrar estructuras ligeramente
diferentes (lo veremos en el próximo capítulo).

.. warning:: Comentar diferencias entre distancia y similaridad. Una medida de distancia
   debe cumplir las tres propiedades mientras que una de similaridad para que no es tan
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
de otro grafo :math:`G_2`.

La comparación entre los grafos puede realizarse de manera exacta (isomorfismo, *exact matching*)
o bien permitir cierta tolerancia a errores puesto que los datos pueden contener ruido. 
En el caso de la traducción automática lo que pretendemos medir es precisamente las variaciones
introducidas por cada traductor respecto al contenido del texto original, en definitiva, el ruido;
por lo tanto nos interesarán las técnicas de comparación inexacta, nuestro objetivo no es
*encontrar* un grafo igual, sino medir comparar dos grafos que *a priori* van a ser distintos.
También debemos tener presente que nuestros grafos tienen atributos tanto en los nodos
como en los arcos.

.. warning:: Si en el modelo convertimos nuestro grafo UNL a un **grafo bipartito** entonces no
   tendríamos atributos en los arcos...

.. warning:: Introducir en lo anterior citas a los papers con surveys de algoritmos de
   comparación de grafos de los que se toma lo que sigue: :cite:`Conte2004`

Comparación inexacta de grafos
++++++++++++++++++++++++++++++
Una de las estrategias habituales para abordar este problema es asignar un coste a las
discrepancias/errores existentes entre los grafos, surge así un problema combinatorio cuya solución
consistirá en encontrar la correspondencia cuyo coste sea mínimo (*error correcting* o 
*error-tolerant*).
Otra aproximación al problema consiste en definir un conjunto de operaciones de edición de un
grafo, asignar un coste a cada una de ellas y buscar la secuencia de ediciones cuyo coste sea
menor (*graph edit cost*).

Cualquiera de estas estrategias de coste mínimo puede ser utilizada para calcular una medida de
disimilaridad entre grafos; una adecuada elección de los costes de cada una de las operaciones
puede provocar que la métrica de coste de edición cumpla las propiedades matemáticas de una
distancia, definiéndose una *distancia entre grafos* que permite aplicar a este dominio algunos
algoritmos de otros espacios métricos :cite:`Conte2004`; se conoce entonces como
*graph edit distance*. Algunos autores como Bunke han demostrado que el problema del *subgrafo
máximo común*, y el isomorfismo entre grafos y subgrafos, pueden ser reducidos al cálculo de
la *graph edit distance*.

.. warning:: Revisar las referencias de Bunke en :cite:`Conte2004` para incluirlas si procede
   en el párrafo anterior cuando se habla de las "demostraciones de Bunke".

Muchos de los algoritmos utilizados para la comparación inexacta de grafos utilizan heurísticas
para explorar el espacio de búsqueda, ya que en muchos casos se considera un probleam NP-completo;
sin embargo el tipo de grafos que utilizaremos nosotros son suficientemente pequeños como para
que el tiempo de cálculo no sea una variable a tener en cuenta. Nos interesa, por tanto,
mostrar las familias de algoritmos utilizados desde el punto de vista de la formulación del
problema, así en :cite:`Conte2004` identificamos:

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

Graph edit distance
...................
Aquí hay unos cuantos papers, preparar un compendio.

Continouos optimization - relaxation labelling
..............................................
In 1995, Christmas et al.27 proposed a method, based on the theoretical framework of Kittler and Hancock, that is able to take into account during the iteration process (and not only during initialization) both node and edge attributes.

Bipartite graph matching
........................
For this approach we can cite the papers by Wang et al.163 in 1994, by El-Sonbaty and Ismail42 in 1998, by Baeza and Valiente5 in 2000 and by Liu et al.92 in the same year


Distancia en redes de conceptos
```````````````````````````````
