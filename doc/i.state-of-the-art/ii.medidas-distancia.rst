
Medidas de distancia y similaridad
----------------------------------
La diferencia semántica entre dos grafos que codifican información puede interpretarse en
términos de distancia o similaridad entre la estructura de los grafos y también entre los
conceptos que están presentes en cada grafo. Dos grafos (coceptuales o UNL) pueden
codificar una información totalmente distinta a pesar de compartir la estructura, pero
también pueden tener la misma información a pesar de mostrar estructuras
diferentes (paráfrasis).

Una distancia o disimilaridad entre dos individuos :math:`i` y :math:`j` es una medida,
indicada por :math:`d(i,j)` que mide la desemejanza entre ambos objetos en relación a un
conjunto de características cuantitativas o cualitativas. El valor de :math:`d(i,j)` es
siempre no negativo y cuanto mayor sea mayor será la diferencia entre los individuos.

Toda medida de distancia debe verificar como mínimo las siguientes propiedades:

 * :math:`d(i,j)>0` (no negatividad)
 * :math:`d(i,i)=0`
 * :math:`d(i,j)=d(j,i)` (simetría)

Diremos que la distancia es euclidiana si además verifica que:

 * :math:`d(i,j) \leq d(i,t)+d(t,j)` (desigualdad triangular)

Existe una gran cantidad de medidas de distancia e indicadores de disimilaridad, y no hay
ninguna regla general que nos permita definir una medida que sea válida para todo tipo de
análisis en cualquier escenario. De las propiedades de los objetos, la naturaleza de las
variables seleccionadas y la finalidad del estudio dependerá la elección adecuada de una u
otra.

También podemos utilizar indicadores de similitud entre los individuos para determinar su
homogeneidad; estos indicadores actúan de forma contraria a las distancias, cuanto mayor
es su valor, más parecidos son los objetos.

La conversión entre valores de distancia y similaridad resulta intuitiva, pero dependerá
del rango de valores que pueda alcanzar la medida que se tome como referencia. Para medidas
de distancia en el rango :math:`d(i,j) \in [0, 1]` la similaridad asociada podrá calcularse como 
:math:`s(i,j) = 1-d(i,j)`, en el caso de medidas no acotadas donde :math:`d(i,j) \in [0, \infty)`
tendrá que utilizarse algo como :math:`s(i,j) \propto \frac{1}{1 + d(i,j)}`. No obstante,
la relación adecuada entre distancia y similaridad podría no ser lineal según el
problema con el que se trabaje.


Comparación de grafos
`````````````````````
La comparación de grafos es un problema muy prolífico en la literatura; desde hace tiempo,
multitud de problemas en el ámbito del reconocimiento de patrones se han codificado en forma
de grafos, una herramienta muy potente para representar la información de forma clara y
concisa. Pero los grafos no sólo se utilizan para almacenar la información, en muchos casos
es precisa la búsqueda de patrones dentro de un conjunto de grafos, o la clasificación de
un nuevo grafo. 

El interés por los grafos aparece a finales los 1970s, momento en el que se plantean
algoritmos y técnicas basadas en grafos para el reconocimiento de patrones, pero el coste
computacional para su aplicación no es compatible con las tecnologías de la
época :cite:`Conte2004`. A partir del año 2000 este interés despierta de nuevo, la
potencia de los ordenadores empieza a ser suficiente para ejecutar los algoritmos de
manera práctica y en las referencias bibliográficas empiezan a aparecer aplicaciones
(:num:`tabla #table-graph-articles`).


.. tabularcolumns:: |p{3cm}|p{4cm}|p{4cm}|
.. _table-graph-articles:
.. list-table:: Número de artículos exponiendo técnicas de comparación de grafos
   clasificados por períodos, y artículos centrados en aplicaciones. Datos obtenidos
   de :cite:`Conte2004`.
   :class: longtable
   :header-rows: 1
   :stub-columns: 1

   *  -  Período
      -  Artículos
      -  Aplicaciones
   *  -  hasta 1990
      -  4
      -  1
   *  -  1991-1994
      -  7
      -  4
   *  -  1995-1998
      -  29
      -  19
   *  -  1999-2002
      -  51
      -  33
   


El problema que se plantea, de acuerdo con Jolion :cite:`Jolion2001` es, ¿qué significa
exactamente comparar dos grafos? ¿Comparar su estructura? ¿Su contenido? ¿Con qué
flexibilidad debe hacerse? Un planteamiento comunmente aceptado para comparar dos grafos
consistiría en "encontrar en un grafo :math:`G_1` cuál es el subgrafo :math:`G'_1`
que es similar (exacto o parcial) a un subgrafo :math:`G'_2` de otro grafo :math:`G_2`".

La comparación entre los grafos puede realizarse de manera exacta (isomorfismo,
*exact matching*) o bien permitir cierta tolerancia a errores puesto que los datos
pueden contener ruido. La comparación exacta se utilizará cuando el objetivo sea
la búsqueda o el reconocimiento de patrones.

En el caso de la traducción automática asumimos que va a haber discrepancias en los grafos,
fruto tanto de la elección de las palabras o los conceptos para expresar ciertas ideas,
como de la estructura sintáctica utilizada para expresar la oración. Lo que nos interesa
es precisamente medir las variaciones introducidas por cada traductor con respecto al 
texto original, el ruido que separa dos grafos que *a priori* deberían ser iguales, tal y
como se plantea la Teoría de la Dependencia Conceptual
(ver :num:`sección #teoria-dependencia-conceptual`).

Como hemos visto anteriormente, los grafos conceptuales y los grafos UNL que representan
las oraciones tienen nodos y relaciones con atributos por lo que muchas de las técnicas
de comparación (aún inexacta) de grafos no serán aplicables, pero resulta imprescindible
conocerlas para exponer posteriormente los algoritmos donde sí se tienen en cuenta estos
atributos.

Máximo grafo común
++++++++++++++++++
Uno de los problemas que mayor interés atrae en la literatura asociado a la comparación
exacta de grafos es la búsqueda del **máximo grafo común** (MCS, *maximum common subgraph*),
es decir, la búsqueda de un subgrafo del primer grafo que sea isomorfo con algún subgrafo
que pueda extraerse del segundo, básicamente la idea de Jolion :cite:`Jolion2001` que
exponíamos anteriormente.

El problema de búsqueda del MCS puede reducirse a la búsqueda del máximo
*clique* :cite:`Ambler1973`. La mayoría de algoritmos utilizan una búsqueda en árbol
con marcha atrás (*backtracking*) utilizando su conversión al problema del máximo
*clique*, como es el caso de Ullmann :cite:`Ullmann1976`, Ghahraman *et al.*
:cite:`Ghahraman1980`, Cordella *et al* :cite:`Cordella2000` :cite:`Cordella1998` o
Balas y Yu :cite:`Balas1986`. Larrosa y Valiente :cite:`Larrosa2002` lo plantean también
cómo búsqueda de máximo *clique* en el ámbito de los problemas de satisfacción de
restricciones (CSP, *Constraint Satisfaction Problem*).

Se trata de un problema costoso computacionalmente por lo que también se investigan
algoritmos de procesamiento en paralelo, como Shinano *et al.* :cite:`Shinano1998`,
Pardalo *et al.* :cite:`Pardalos1998` o San Segundo *et al.* :cite:`SanSegundo2011`.

Otro algoritmo que aplica marcha atrás en la búsqueda del MCS se debe a McGregor en
1979 :cite:`McGregor1982`, éste no convierte el problema en la búsqueda del máximo *clique*
y, según Bunke *et al.* :cite:`Bunke2002` ofrece resultados más rápido que los otros
algoritmos que sí lo hacen cuando los grafos son dispersos. McGregor implementa
el algoritmo dentro de un programa para analizar las modificaciones en los enlaces de
los compuestos químicos.


Comparación inexacta de grafos
++++++++++++++++++++++++++++++
Cuando las restricciones impuestas por la correspondencia exacta entre grafos
no se adaptan al problema, es necesario relajar estas restricciones para obtener un
resultado adecuado en un tiempo suficientemente corto. En este tipo de algoritmos se
introducen penalizaciones cuando la correspondencia entre los nodos o los arcos no es
exacta. Por lo tanto, el algoritmo deberá encontrar la solución que minimice este coste.

Hay algoritmos que garantizan la solución óptima (exacta en caso de que exista) y otros
que sólo la aproximen ofreciendo un resultado que sea mínimo local, generalmente los
segundos ofrecerán tiempos de respuesta mucho más breves.

En función de la estrategia utilizada por los algoritmos podemos clasificarlos en:

 * Algoritmos *error correcting* o *error-tolerant*: asignan un coste a las
   discrepacias y errores existentes entre los grafos.
 * Algoritmos *edit cost*: definen un conjunto de operaciones de edición de un grafo,
   cada una con un coste asociado y buscan una secuencia de operaciones que permita
   transformar un grafo en otro.

En ambos casos estamos ante un problema de optimización donde el objetivo será conseguir
la combinación de errores o de ediciones que minimice el coste de correspondencia entre
los grafos a comparar.

Una elección adecuada de los costes asociados a los errores o a las operaciones de edición
permite que los valores obtenidos cumplan las propiedades de una distancia métrica y, por
lo tanto, podríamos hablar de **distancia entre grafos** y así aplicar a este dominio
algoritmos de otros espacios métricos :cite:`Conte2004`.

Un caso particular de distancia entre grafos, cuando se utiliza un algoritmo *edit cost*,
se conoce como *graph edit distance*. Bunke demostró en 1997 :cite:`Bunke1997` que el problema
de máximo grafo común puede ser considerado un caso especial del cálculo de la *graph
edit distance* cuando se asignan valores adecuados a los costes de edición, y también lo son
el isomorfismo entre grafos y el isomorfismo entre subgrafos :cite:`Bunke1999`.

.. Y aquí entramos en la comparación inexacta de grafos propiamente dicha

Muchos de los algoritmos utilizados para la comparación inexacta de grafos utilizan heurísticas
para explorar el espacio de búsqueda, ya que en muchos casos se considera un problema NP-completo;
sin embargo el tipo de grafos que utilizaremos nosotros son suficientemente pequeños como para
que el tiempo de cálculo no sea una variable a tener en cuenta. Nos interesa, por tanto,
mostrar las familias de algoritmos utilizados desde el punto de vista de la formulación del
problema, en :cite:`Conte2004` encontramos las siguientes :

 * **Optimización continua**: convierte el problema de comparación de grafos, que en principio es
   un problema de optimización discreta, en un problema continuo no lineal y se aplican
   diferentes algoritmos o heurísticas para obtener un solución suficientemente buena.
 * **Métodos espectrales**: basadas en los autovalores y autovectores calculados a partir de la
   matriz de adyacencia. El inconveniente de estos métodos es que sólo tienen en cuenta la
   estructura del grafo y no los atributos de los nodos y arcos.
 * **Conversión a un grafo bipartito**: convertir el problema a este tipo de grafos permite
   aplicar algoritmos con tiempo de solución de orden polinómico.
 * ***Elastic Graph Matching* (EGM)**: se trata de abordar el problema comparando las imágenes de
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

La medida de la similaridad entre conceptos se ha abordado desde tres perspectivas principales
:cite:`Slimani2013`:

 * basadas en la estructura de la red de conceptos, 
 * centradas en el contenido de información de cada nodo, y 
 * aproximaciones basadas en características de los términos.

Por supuesto, también hay otros propuestas que utilizan medidas híbridas que combinan
varias de estas perspectivas. Desarrollamos cada uno de los puntos anteriores a continuación.

Basadas en la estructura
++++++++++++++++++++++++
Considerar la jerarquía de conceptos y el número de conexiones existentes entre ellos es una
de las maneras más sencillas y naturales de calcular su similaridad. La formulación más
simple consiste en calcular el camino más corto entre dos conceptos dentro de la red
(utilizaremos :math:`len(c_1, c_2)` para designar la longitud del camino más corto entre
un concepto :math:`c_1` y otro :math:`c_2`) y
considerar su distancia semántica proporcional a la longitud de este camino.

**Rada et al.** :cite:`Rada1989` aplican este principio para calcular la distancia entre
conceptos en la red MeSH (*Medical Subject Headers*), Jarmasz y Szpakowicz
:cite:`Jarmasz2003` utilizan la misma técnica con el *Roget's Thesaurus*.
En ambos casos los resultados son bastante buenos debido a que sólo utilizan las relaciones
``is-a`` :cite:`Lee1993`. Esta distancia se formularía como:

.. math::

    dist_r(c_1, c_2) = len(c_1, c_2)


No obstante, parece lógico pensar que la distancia entre dos nodos adyacentes cualesquiera
no tiene por qué ser idéntica, así cada conexión debe tener un peso asignado en el cálculo
de esta distancia.
En redes muy grandes, como es el caso que nos ocupa, esta peso no puede ser asignado manualmente
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

**Sussna** :cite:`Sussna1993` propone una métrica de distancia que considera la profundidad
dentro de la red de conceptos de tal forma que la distancia semántica entre ellos es
tanto menor cuanto más se desciende en la jerarquía. Asigna a cada relación :math:`r` que 
parte de un node :math:`c_1` un peso dentro de un intervalo :math:`[min_r, max_r]` en
función del número de relaciones del mismo tipo que parten de él:

.. math::
	
    wt(c_1 \rightarrow_r) = min_r + \frac{max_r - min_r}{edges_r (c_1)}


.. warning:: Aquí he modificado la relación original porque creo que verdaderamente hay un error tanto
   en el artículo original como en las referencias que apuntan a él. En origen el peso de los arcos
   está expresado como :math:`max_r - \frac{max_r - min_r}{edges_r (c_1)}`, así ocurre que el peso 
   es mayor cuanto mayor sea el número de arcos lo que es contrario a la intuición de que a
   mayor densidad de la red menor es la distancia entre conceptos.


La distancia entre dos conceptos adyacentes :math:`c_1` y :math:`c_2` es la media
de los pesos de la relación en ambas direcciones ponderada por la profundidad de los nodos.

.. math::

    dist_s(c_1, c_2) = \frac{wt(c_1 \rightarrow_r) + wt(c_2 \rightarrow_{r'}) }{2 \cdot max\{depth(c_1), depth(c_2)\}}

La distancia semántica entre dos nodos cualesquiera de la red se calcularía como la suma de
distancias entre cada par de nodos adyacentes a lo largo del camino más corto que los une.

**Wu and Palmer** :cite:`Wu1994` proponen una medida de similaridad entre conceptos que tiene
en cuenta al hiperónimo común más profundo en la jerarquía (*lowest-super-ordinate*, ``lso``)
de ambos conceptos:

.. math::

    sim_{WP}(c_1, c_2) = \frac{2 \cdot depth(lso(c_1, c_2))}{len(c_1, lso(c_1, c_2)) + len(c_2, lso(c_1, c_2)) + 2 \cdot depth(lso(c_1, c_2))}

y la distancia se puede expresar como:

.. math::

    dist_{WP}(c_1, c_2) = 1 - sim_{WP}(c_1, c_2)

Así, la distancia entre los conceptos es menor cuanto mayor es la profundidad del hiperónimo común dentro de la jerarquía.

**Leacock and Chodorow** :cite:`Leacock1998` proponen una función de similaridad semántica
que tiene en cuenta la profundidad máxima de la jerarquía de conceptos:

.. math::

    sim_{LC}(c_1, c_2) = -log \frac{len(c_1, c_2)}{2 \cdot \underset{c \in WordNet}{max} depth(c)}

**Li et al.** :cite:`Li2003` plantean una función no lineal que pondera la longitud del camino
más corto entre el par de conceptos y la profundidad del hiperónimo común:

.. math::

    sim_{Li}(c_1, c_2) = e^{-\alpha \cdot len(c_1, c_2)} \frac{e^{\beta \cdot N} - e^{-\beta \cdot N}}{e^{\beta \cdot N} + e^{-\beta \cdot N}}

donde :math:`N = depth(lso(c_1, c_2))`, :math:`\alpha \geq 0` y :math:`\beta \geq 0`. Después del
análisis que realizan en el artículo concluyen que los parámetros óptimos en la fórmula
anterior son :math:`\alpha = 0.2` y :math:`\beta = 0.6`.


Basadas en el contenido de información
++++++++++++++++++++++++++++++++++++++
Una de las formas de evaluar la densidad de la red de conceptos es considerar el contenido de
información de un concepto :cite:`Resnik1999`, para ello no basta con la red de conceptos
sino que es necesario contar con un *corpus* suficientemente grande. Así, si la probabilidad
de encontrar un concepto :math:`c` en el corpus es :math:`p(c)`, es contenido de información
dado por este concepto, según la teoría de la información es:

.. math::

    IC(c) = -log(p(c))

La primera vez en la que se utiliza el contenido de información para calcular la distancia
semántica entre conceptos pudo ser en 1995 por Resnik quien sólo tenía
en cuenta la frecuencia de aparición de un término para evaluarlo.

**Resnik** :cite:`Resnik1995` propone la siguiente medida de similaridad semántica:

.. math::

    sim_R(c_1, c_2) = -log \, p(lso(c_1, c_2))

Para el cálculo de las frecuencias de aparición de los conceptos en el corpus, Resnik realiza
el cálculo contando como una aparición del concepto cada vez que aparece el propio concepto
o uno de sus hipónimos en la jerarquía (hay que hacer notar que Resnik trabaja a nivel de palabras
y no de conceptos desambiguados), formalmente:

.. math::
    
    freq(c) = \sum_{w \in words(c)} count(w)

donde :math:`words(c)` sería el conjunto de conceptos cuyo hiperónimo es :math:`c`. De este modo
la probabilidad de un concepto puede calcularse como su frecuencia relativa de aparición:

.. math::

    p(c) = \frac{freq(c)}{N}

siendo :math:`N` el número total de conceptos en la jerarquía. 

.. warning:: Verificar que N es el número total de conceptos, hay que pensar que estamos sumando
   una aparición cada vez que aparece un hipónimo, por lo que N podría referirse al número de
   conceptos o también al número de elementos sumados que va a ser mucho mayor.

Como señala Budanitsky y Hirst :cite:`Budanitsky1998` uno de los mayores incovenientes de esta
medida es que se obtiene el mismo valor de similaridad para cualesquiera dos conceptos que
tengan el mismo ``lso``, algo que en las medidas que consideran la longitud del camino mínimo
no ocurre.

**Jiang y Conrath** :cite:`Jiang1997` ofrecen una aproximación en la que combinan las técnicas
basadas en nodos y las basadas en arcos, la estructura de la red y la información estadística
ofrecida por el corpus.

En primer lugar consideran el peso de las conexiones en la red y postulan que este peso es
proporcional a la probabilidad condicionada de encontrar una instancia de un concepto :math:`c`
cuando ha aparecido el concepto padre :math:`f`:

.. math::

    p(c|f) = \frac{p(c \cap f)}{p(f)} = \frac{p(c)}{p(f)}

la segunda igualdad se justifica según :cite:`Resnik1999` puesto que toda aparición de ``c``
contará también como una aparición de ``par(c)``. De este modo el peso de cada conexión puede
calcularse a través de la teoría de la información como:

.. math::

    wt(c, f) = -log [p(c|f)] = IC(c) - IC(f)

es decir, el peso de cada conexión es simplemente la diferencia en el contenido de información
entre el concepto hijo y su hiperónimo directo.

Jiang y Conrath consideran también otros factores que deben incorporarse al peso de cada
conexión, estos son: la densidad local, la profundidad del nodo y el tipo de enlace; obteniendo
entonces una formulación como la que se sigue:

.. math::

    wt(c, f) = \bigg(\beta + (1-\beta)\frac{\overline{E}}{E(f)}\bigg) \bigg(\frac{d(f) + 1}{d(f)}\bigg)^{\alpha} [IC(c) - IC(f)] \, T(c, f)

donde :math:`d(f)` es la profundidad del nodo ``f`` en la jerarquía, :math:`E(f)` el número
de arcos (densidad local), :math:`\overline{E}` la densidad media en la jerarquía y :math:`T(c,f)`
es el factor correspondiente al tipo de enlace. Los parámetros :math:`\alpha (\alpha \geq 0)`
y :math:`\beta (0 \leq \beta \leq 1)` controlan el grado de influencia de los diferentes factores
en el peso final del enlace.

Utilizando esta formulación puede calcularse la distancia entre dos conceptos como la suma de los
pesos de las conexiones del camino más corto que los une. En el caso especial en el que sólo se 
considera el peso de los enlaces de tipo hiperónimo/hipónimo con un peso 1,
:math:`\alpha = 0, \beta = 1, T(c,f)=1`, entonces la distancia puede calcularse como:

.. math::

    dist_{JC}(c_1, c_2) = IC(c_1) + IC(c_2) - 2 \cdot IC(lso(c_1, c_2))

es decir,

.. math::

    dist_{JC}(c_1, c_2) = 2log\, p(lso(c_1, c_2)) - (log \, p(c_1) + log \, p(c_2))

**Lin** :cite:`Lin1998` propone una medida de similaridad universal, que no dependa de la
representación de los conceptos ni de un recurso o aplicación específico. Así Lin prueba
el siguiente teorema:

    **Similarity Theorem**: The similarity between A and B is measured by the ratio between the
    amount of information needed to state the commonality of A and B and the information
    needed to fully describe what A and B are:

    .. math::

        sim(A, B) = \frac{log P(common(A, B))}{log P(description(A,B))}

es decir, la similaridad es el ratio entre la información que ambos conceptos tienen en común
y la información necesaria para describirlos. La aplicación de este teorema a una jerarquía
de conceptos es automática:

.. math::

    sim_{Lin}(c_1, c_2) = \frac{2 \cdot log \, p(lso(c_1, c_2))}{log(p(c_1)) + log(p(c_2))}


Basadas en características de los términos
++++++++++++++++++++++++++++++++++++++++++
Una aproximación diferente permite calcular la similaridad entre dos conceptos basándose en
características descriptivas de cada uno de ellos, el valor de similaridad se calcula
utilizando formulaciones análogas al coeficiente de Jaccard.
Uno de los principales incovenientes para poder aplicar este tipo de modelos es que normalmente
no se dispone de un conjunto de características homogeneo para todos los conceptos.

Como referencia citamos los trabajos de Petrakis *et al.* :cite:`Petrakis2006` y
Tversky :cite:`Tversky1977`, pero su enfoque se aparta del planteamiento de esta tesis donde contamos
con los conceptos desambiguados y con una red de conceptos a nuestra disposición.


