
.. raw:: latex

    \newpage


Descripción del problema
========================

La distancia semántica
----------------------
En la revisión del estado del arte del capítulo anterior hemos mostrado los diferentes
elementos que se han de tener en cuenta para la comparación de dos oraciones en lenguaje
natural. Hemos comentado muy sucintamente los problemas relacionados con la conversión de
este en una representación del conocimiento independiente de la lengua y que
no presente ambigüedades, que es la base de los sistemas de traducción basados en
interlingua. Hemos repasado los grafos conceptuales y la evolución de estos hasta el
*Universal Networking Language* (UNL).

Hemos mostrado las principales medidas de distancia entre conceptos que se
proponen en la bibliografía y los algoritmos de comparación de grafos que son la base
para la comparación de grafos conceptuales, presentados en la última sección del
estado del arte.

Sin embargo, ninguno de los artículos revisados es concluyente, debido, en primer lugar
a que **no existe una definición objetiva de distancia semántica** a nivel de conceptos y,
por lo tanto, este problema se arrastra hasta la comparación de grafos conceptuales y de
textos completos. No hay una unidad de medida que permita saber cómo de lejos está
un significado de otro y, probablemente, dadas las características del lenguaje natural,
su ambigüedad, diversidad y subjetividad, sea imposible establecer una medida absoluta.

Como hemos dicho, la problemática se presenta en dos niveles: el primero de ellos en
los conceptos individualizados y el segundo en el conjunto de la oración.


Distancia entre conceptos
`````````````````````````
Cada autor considera unas características diferentes a la hora de desarrollar su métrica
de distancia entre conceptos: unos la restringen a un contexto concreto, otros utilizan el
*corpus* que mejor se adecua al experimento que van a realizar.

Existen esfuerzos como el de Budanitsky y Hirst :cite:`Budanitsky1998` :cite:`Budanitsky2006`
o el dirigido por Slimani :cite:`Slimani2013` que muestran la correlación entre diferentes
medidas de similaridad semántica o con datos obtenidos de estudios de campo.
Aún así, estas comparaciones con datos de distancia percibidos por
personas se basan en pequeños experimentos (pocos sujetos y pocos pares de palabras) que
parten del realizado por Rubenstein y Goodenough :cite:`Rubenstein1965` en 1965 con 51 nativos
ingleses sobre 65 pares de palabras.

El estudio de Rubenstein y Goodenough ha sido comparado con otras muestras obtenidas
de otros sujetos varias veces obteniéndose unos niveles de correlación muy altos: Miller
y Charles en 1991 :cite:`Miller1991`, Resnik en 1995 :cite:`Resnik1995` y Pirró más
recientemente en 2009 :cite:`Pirro2009`. Los resultados muestran estabilidad en
la distancia semántica percibida por las personas a lo largo del tiempo para el conjunto de
palabras elegido, pero la lengua cambia, los usos de las palabras se modifican y no se
puede aceptar esta premisa como válida en términos generales (e.g. la palabra bizarro que
la RAE define como "valiente", pero que en su uso está más próxima al concepto
"raro, extravagante" importado del inglés *bizarre*).

Resulta imprescindible disponer de un conjunto mayor de palabras y mejor etiquetado, que
identifique, además de la distancia semántica, a las personas que han
realizado el trabajo de clasificación: procedencia, edad, educación, contexto
socio-cultural, etc. que pueden afectar a la identificación de la realidad
extralingüística con un término concreto.


Distancia entre oraciones
`````````````````````````
El otro gran problema asociado a la representación del conocimiento es la interpretación
del mensaje, que también tiene un componente subjetivo difícilmente medible. Una parte
muy importante del mensaje es implícito y su comprensión depende del sustrato cultural
común de los interlocutores, es un problema que mencionábamos al hablar de los 
fenómenos lingüísticos (:ref:`sección 2.3.1 <fenomenos-linguisticos>`).

De acuerdo con la teoría de la dependencia conceptual dos oraciones con el mismo contenido
semántico deberán representarse de la misma forma, pero pueden tener realizaciones
distintas en el lenguaje natural en función de parámetros subjetivos que ya hemos enunciado.
Este hecho puede provocar que un mismo mensaje sea codificado de formas diferentes
y, por lo tanto, detectar una distancia semántica en teoría inexistente; una buena medida
de distancia deberá ofrecer un valor muy bajo indicando que son muy similares.

Pero también puede ocurrir que un mismo mensaje sea interpretado de manera diferente por
distintos sujetos sin que ninguno esté equivocado, entonces la representación mental del
significado deberá ser diferente en cada caso y existirá una distancia semántica entre
ellas. El analizador de lenguaje natural debería tener en cuenta estas subjetividades a
la hora de codificar el grafo, un problema para nada trivial que escapa del objeto de esta
tesis.

En la literatura que hemos consultado hay numerosos artículos en torno a la comparación
de grafos, pero pocos de ellos se centran en grafos conceptuales y, mucho menos, en la
comparación flexible de grafos UNL que es el problema que nosotros abordamos. Tampoco
se ha encontrado ningún artículo en el que se ofrezca una comparativa entre los resultados
obtenidos por diferentes algoritmos ni recursos etiquetados. 

El problema de la distancia semántica entre oraciones parece que apenas ha sido 
objeto de estudio.


Recursos disponibles
--------------------
Como hemos hecho mención más arriba, el problema que planteamos desde el principio
también se ve condicionado por la disponibilidad (o carencia) de recursos adecuados:

 * Los ejemplos de pares de palabras etiquetados por personas con la distancia
   semántica entre ellos son muy pocos y bastante pequeños. Cualquier medida de
   distancia que propongamos apenas podrá ser contrastada contra un conjunto de
   datos de test, solo podrá ser evaluada contra otras medidas presentes en la
   bibliografía.

 * Mucho menos existe un repositorio con oraciones y las distancias entre ellas, en
   este caso, además, los artículos que se han encontrado se limitan a presentar el
   algoritmo y mostrar algunas pruebas de su funcionamiento.

Respecto al enfoque desde el lenguaje UNL que quiere abordarse en esta tesis hay que
señalar que tampoco se ha encontrado la Ontología UNL o *UNL Knowledge Base* a la que
se hacía referencia en el capítulo anterior. Esta carencia puede ser subsanada
utilizando WordNet cuya base de datos es accesible; sin embargo será necesario establecer
una correspondencia entre las UWs y los *synsets*.

En cuanto a oraciones codificadas en forma de grafos UNL o grafos conceptuales pueden
extraerse ejemplos de algunos artículos, aunque en este caso tenemos disponible en la
web del Centro de Lengua Española del Consorcio UNL un conjunto de ejemplos [#]_ que
podremos utilizar como punto de partida para generar variaciones y ver cómo afectan a
nuestra medida.

.. [#] En la Web del Centro de Lengua Española hay una serie de ejemplos de generación
   de lenguaje partiendo de grafos codificados en UNL:
   http://www.unl.fi.upm.es/CLE/spanish/fr_examples.htm (accedido en junio de 2015).

   
.. _planteamiento-problema:
Planteamiento del problema
--------------------------
A la vista del estado del arte, las dificultades encontradas en la bibliografía y las
carencias detectadas, el problema que se plantea en esta tesis es un problema no
resuelto: **una medida de distancia entre grafos UNL**.

Realmente no creemos que el problema esté completamente resuelto en ninguna de sus partes,
si acaso más avanzado en lo referente a propuestas de modelos para el cálculo de distancias
entre conceptos dentro de una estructura jerárquica, pero al no haber un conjunto de datos
de validación suficientemente amplio no puede fundamentarse qué modelo es mejor que otro.

En esta situación creemos que hay un trabajo pendiente en todas las fases
involucradas en esta tesis:

 #. Creación de la **Ontología UNL**: es el recurso principal para poder automatizar el
    cálculo de distancias entre conceptos. Esfuerzos como el de Iraola :cite:`Iraola2003`,
    UNLWordNet [#]_ o la base de datos de UWs del Grupo de Validación y Aplicaciones
    Industriales de la UPM deben ser tenidos en cuenta e integrados [#]_.
    
 #. Creación de una **jerarquía de relaciones UNL**: las relaciones entre conceptos también
    deben ser tenidas en cuenta en la distancia entre oraciones; para ello es necesario
    saber cómo se vinculan unas relaciones con otras. A este trabajo se añade el esfuerzo
    de definir y acordar entre los diferentes grupos de trabajo cuáles son las
    relaciones válidas.

 #. Obtención de un **dataset con distancias semánticas etiquetadas** entre palabras que
    sea suficientemente amplio y generalista para cubrir cualquier dominio. Hay que
    tener en cuenta dos características de la lengua: su variación a lo largo del tiempo
    y también su localidad, los significados de las palabras cambian en el tiempo y en
    el espacio. Trabajar a nivel de conceptos (WordNet o UWs) en teoría permite
    abstraerse de estos problemas, pero no podemos olvidar que los conceptos deben
    expresarse utilizando el lenguaje natural con la ambigüedad que implica. Debe
    desarrollarse un proceso de obtención de datos que sea fácilmente reproducible y
    replicable para mantener actualizado el *dataset*.

 #. **Corpus etiquetado con UWs**: las medidas de distancia basadas en el contenido
    de información requieren de un *corpus* para poder calcular la frecuencia de aparición
    de los diferentes conceptos. Etiquetado para WordNet solo se ha encontrado el
    corpus SemCor [#]_ que es un subconjunto del Brown Corpus [#]_ anotado con los conceptos de
    WordNet 1.6 y mapeado automáticamente a las versiones posteriores de WordNet.
    
 #. **Modelo de distancia entre UWs**: la mayoría de los modelos propuestos sobre WordNet
    pueden ser aplicados a la Ontología UNL. Con un dataset de validación adecuado puede
    realizarse una comparación de los diferentes modelos para caracterizar su comportamiento
    e idoneidad en diferentes aplicaciones.

 #. Obtención de un **dataset con distancias semánticas entre grafos UNL**: aunque no se
    ha realizado una búsqueda intensiva, parece que tampoco hay disponible un *dataset*
    con distancias entre oraciones y, menos, con distancias entre grafos conceptuales o
    UNL.
    
    Hay aquí dos trabajos diferentes relacionados: la obtención de las oraciones y
    su distancia semántica por un lado y, por otro, la construcción de los grafos con
    sus conceptos y los problemas de interpretación y ambigüedades que conllevan.

 #. **Modelo de distancia entre grafos UNL**: también resultaría sencillo trasladar los
    modelos propuestos para grafos conceptuales en modelos válidos para grafos UNL. A
    diferencia de los modelos de distancia entre conceptos, creemos que aquí todavía
    pueden proponerse nuevos modelos y, por supuesto, algoritmos que hagan viable su
    aplicación a grafos de grandes dimensiones.

    La validación y comparación de estos modelos tendría que realizarse contra el *dataset*
    al que hacíamos referencia en el punto anterior.


.. [#] Martins, Ronaldo. *UNLWordNet*. Mackenzie University. São Paulo. Brazil. Disponible
   online en http://www.ronaldomartins.pro.br/unlwordnet/ (accedido en junio de 2015).

.. [#] J. Bekios, I. Boguslavsky, J. Cardeñosa y C. Gallardo. *Universal Words Dictionary*.
   Disponible online en http://pacifico.dia.fi.upm.es:8080/dicweb/index.jsp (accedido en
   junio de 2015).

.. [#] El corpus SemCor lo hemos podido encontrar en la página de R. Mihalcea (Universidad
   de Michigan, USA) http://web.eecs.umich.edu/~mihalcea/downloads.html#semcor (accedido
   en junio de 2015). También está disponible en los corpus de datos que ofrece la
   librería NLTK de Python (http://www.nltk.org/).
   
   Sin embargo, según ha podido saber el autor de este trabajo a través de correos
   electrónicos intercambiados con la profesora R. Mihalcea, la actualización de este
   corpus no está garantizada. A este hecho hay que añadir que no se ha encontrado ningún
   otro corpus etiquetado para WordNet.

.. [#] El Brown Corpus se crea en los 1960s por Henry Kucera y
   W. Nelson Francis (Brown University, Providence, Rhode Island) tomando 500 muestras de
   artículos de periódico escritos por hablantes nativos de inglés americano. Hay que hacer
   notar la triple limitación: medio (escrito), local (USA), temporal (1961) y
   cuantitativo (un millón de palabras); no podemos darle una validez general.


Los trabajos reseñados anteriormente exceden con mucho el alcance de esta tesis, pero hemos
creído conveniente exponerlos como fruto de la investigación que se ha realizado sobre la
materia y servirán para orientar el trabajo futuro. Nosotros nos centraremos en proponer 
un nuevo modelo para el último de los puntos a los que se ha hecho referencia.


