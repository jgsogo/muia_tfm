
Estado del Arte
===============

La base de los sistemas de traducción automáticos basados en una interlingua es
que ésta debe representar todas las oraciones que tienen el mismo
significado de la misma manera, con el mismo conjunto de símbolos, independientemente
del idioma original del texto. Partiendo de esta representación única no ambigua
se generan las traducciones a todos los idiomas de destino como se muestra en
la :num:`figura #fig-interlingua-esquema`.

.. _fig-interlingua-esquema:
.. graphviz::
   :caption: Sistema de traducción automática basado en interlingua

   digraph foo {
        rankdir=LR
        n1[label="Texto original"]
        n2[label="Analizador", shape=box]
        n3[label="Interlingua"]
        n4[label="Generador", shape=box]
        n5[label="Texto traducido"]

        ndots[label="...", shape=box]
        ndots2[label="..."]

        n6[label="Generador", shape=box]
        n7[label="Texto traducido"]

        n1 -> n2 -> n3 -> n4 -> n5
        n3 -> ndots -> ndots2
        n3 -> n6 -> n7
   }

Si convirtiéramos cualquiera de los textos traducidos de nuevo en la representación
en interlingua, deberíamos obtener una representación idéntica a la que hemos
utilizado para generarlos. La calidad de la traducción en cuanto a su fiabilidad, 
entendida como contenido semántico transmitido, estará por lo tanto directamente
relacionada con la proximidad entre las dos representaciones en interlingua; así
un medida adecuada de distancia o de similaridad entre ambas representaciones resulta
en una herramienta de extremada utilidad para evaluar un sistema de traducción automática.

En este capítulo estudiamos el estado del arte de los sistemas de representación del
conocimiento que son utilizados como interlinguas, y en concreto nos centraremos en
aquéllos cuya representación formal es un grafo; posteriormente expondremos las 
medidas que se han propuesto en la bibliografía para estudiar la similaridad entre dos
grafos, veremos cómo evaluar la distancia semántica entre conceptos y textos, y
finalmente repasaremos los modelos propuestos que integran lo anterior para evaluar
la distancia entre grafos conceptuales, analizando en profundidad cuáles son sus
principales aportaciones y las dificultades que aún están presentes.

.. warning:: Quizá estos párrafos anteriores son más introducción que estado del arte


Sistemas de representación del conocimiento
-------------------------------------------


Grafos conceptuales
```````````````````
La característica fundamental que debe tener una interlingua es su capacidad para 
representar cualquier tipo de conocimiento de una forma no ambigua. Una de las
herramientas más potentes para la representación del conocimiento que además
permite realizar inferencias son los grafos conceptuales (CG, *Conceptual Graph*),
éstos son introducidos por Sowa en 1976 :cite:`Sowa1976` donde los define como:

    A *conceptual graph* is a finite, connected, undirected, bipartite graph with
    nodes of one type called *concepts* and nodes of the other type called
    *conceptual relations*. A conceptual graph may consist of a single concept,
    but it cannot have conceptual relations with unattached links. [#]_
    (Cursivas en el original)

.. [#] Traducción: Un *grafo conceptual* es un grafo bipartito finito, conectado y no
   dirigido en el que los nodos de un tipo se llaman *conceptos* y los del otro tipo se
   conocen como *relaciones conceptuales*. Un grafo conceptual puede constar de un único
   concepto, pero no puede contener relaciones conceptuales que tengan enlaces sin conectar.

La primera aproximación de Sowa a los grafos conceptuales la realiza en el contexto
de las bases de datos y los sistemas de recuperación de información [#]_, como una herramienta
intermedia de comunicación entre los usuarios y las máquinas: el grafo describe el 
significado desde el punto de vista del humano, pero su codificación puede ser fácilmente
interpretada por un programa:

 * Los conceptos están representados por cajas que contienen un etiqueta identificativa del
   tipo de concepto que representan. Los conceptos pueden identificar cualquier entidad real
   o abstracción. También es importante señalar que Sowa introduce una propiedad de ordenamiento
   :math:`<` entre conceptos; así, si :math:`a` y :math:`b` son conceptos y se
   cumple que :math:`a < b` entonces :math:`a` es un *subtipo* de `b`. Hay que señalar que un
   concepto :math:`a` puede ser un *subtipo común* a varios conceptos.

 * Las relaciones conceptuales están representadas por círculos en el grafo y puede tener una
   o más conexiones. Estas relaciones actúan como restricciones al seleccionar qué conceptos
   pueden unir :cite:`Clancey1985`, incorporando una dimensión lógica en los grafos.


.. [#] John F. Sowa desarrolla los CGs en más profundidad en sus libros
   *Conceptual Structures: Information Processing in Mind and Machine*, Addison Wesley
   Publishing Co., London, UK, 1984 y *Knowledge Representation: Logical, Philosophical and
   Computational Foundations*, Brooks Cole Publishing Co., Pacific Grove, CA, 2000.

Sowa habla de ontologías en relación a los conceptos, indica que la selección de las categorías
ontológicas debe ser el primer paso para diseñar una base de datos, de conocimiento o un
sistema orientado a objetos :cite:`Shapiro2012`. Sin embargo no introduce ningún tipo de
restricción en cuanto a las relaciones.

.. En :cite:`Sowa2003` Sowa introduce los *nested graph models* (NGM) que permiten expresar el contexto de una relación, de tal forma que era posible incorporar lógica modal y temporal.

.. warning:: ¿Incluir algo de cómo escribir estos grafos? CGIF,...  ¿Algo de los contextos?
   No añade nada en la dirección que queremos llevar.


Semántica estructural
`````````````````````
En los nodos de tipo *concepto* de los CGs tiene que tener cabida cualquier entidad real
o abstracta y ésta tiene que poder expresarse de una manera no ambigua. En su artículo de
1976 :cite:`Sowa1976` Sowa ya indica que estos conceptos son meros identificadores y que
por conveniencia son representados con una breve etiqueta en inglés, pero podría tratarse
de un número o una dirección de memoria en un ordenador.

Más importante es la jerarquización entre conceptos que introduce, en futuros artículos ya
hablará de ontología y categorías. El término *ontología* hace referencia a la ciencia del
ser, del todo; y es un concepto metafísico que se ha estudiado desde época clásica, tratando
de realizar una clasificación de todo lo que *es*.

Nosotros abordaremos las ontologías desde el punto de vista de la Ingeniería del Conocimiento,
una de las definiciones más extendidas y aceptadas es la que se ofrece en :cite:`Studer1998`:
*"An ontology is a formal, explicit specification of a shared conceptualization"* [#]_. Por
*conceptualización* se entiende una modelización abstracta de un fenómeno identificando sus
conceptos relavantes. Por *explícito* se hace referencia a que tanto los conceptos como sus
relaciones y restricciones tienen que estar definidas explícitamente. Al ser *formal* la
ontología puede procesarse mediante un programa informático (no estará expresada en lenguaje
natural). Y también tiene que ser *compartida*, tiene que recoger un conocimiento consensuado,
ha de ser aceptada por un grupo.

.. [#] Traducción: una ontología es una especificación explícita y formal de un
   conceptualización compartida.

En los sistemas de traducción automática una ontología de los conceptos deberá recoger toda
la realidad expresable en cualquier lenguaje natural, todos los significados posibles a los
que haga referencia cualquier significante, ya sean realidades o pensamientos, abstracciones
o acciones.

.. Nos adentramos en terrenos de semiótica, y cosas superinteresantes de estructuralismo y demás, hablamos de Saussure, Hjelmslev, Wittgenstein... si tuviéramos tiempo nos adentraríamos más por este camino para bordar este capítulo y ponerle un título meritorio.

El estudio de los conceptos, los referentes, los símbolos,... es una rama de la lingüística que 
se desarrolla como ciencia durante el siglo XX y de forma sistemática a partir de los 1960s.
La semiótica comienza su andadura con lingüísticas y filólogos como Ferdinand de Saussure,
Louis Hjelmslev, Roman Jakobson y Ludwig Wittgenstein en Europa y paralelamente en
Estados Unidos con Charles Sanders Peirce. Peirce y Saussure son contemporaneos y abordan el
mismo problema, la creación de una *ciencia de los signos*, pero desde perspectivas diferentes.
Saussure, lingüísta, la aborda desde una perspectiva psicosocial e indica que se trata de una
nueva ciencia a la que llama *semiología*, Peirce considera que esta
ciencia de los signos ya existe desde la antigüedad, aunque no plenamente desarrollada
:cite:`Castanares2000`, así su trabajo consistió en la exploración, sistematización y ampliación
de la lógica heredada de Aristóteles :cite:`Peirce1902`. Peirce desarrolló los grafos
existenciales, que son el punto de partida para los grafos conceptuales de John F. Sowa.

Fruto de estos estudios en el campo de la lingüística se realizan avances muy importantes
relacionados con el significado de las palabras, nos interesa aquí hacer referencia a la
semántica estructural y las principales relaciones que se dan entre significados y que
han de ser considerados en una ontología de conceptos :cite:`WPSemantica`:

 * **Hiperonimia**: es la relación que se da entre una palabra (hiperónimo) cuyo significado
   está totalmente incluido en los significados de otras más específicas (hipónimos).
 * **Hiponimia**: es la relación en la que el significado de una palabra más específica
   (hipónimo) contiene todos los rasgos de significado del término más general (hiperónimo).
   Dos hipónimos de un mismo hiperónimo, son cohipónimos.
 * **Holonimia**: es la relación que se establece entre una palabra (holónimo) y otra u
   otras (merónimos) que designan partes de lo denotado por la primera. No se trata de una
   relación entre significados, sino de rasgos extralingüísticos.
 * **Meronimia**: un merónimo designa una parte de la realidad nombrada por un holónimo.

Atendiendo a las propias palabras en relación con sus significados encontramos los siguientes
fenómenos :cite:`WPSemantica`:

 * **Monosemia**: palabras que tienen un único significado o acepción.
 * **Polisemia**: una sóla palabra tiene varios significados, estando todos ellos emparentados
   semánticamente.
 * **Homonimia**: varios significados asociados a una misma forma, pero con orígenes diferentes.
 * **Sinonimia**: es la relación entre dos términos de significados similares e intercambiables
   en el discurso por pertenecer a la misma categoría sintáctica.
 * **Antonimia**: es la relación que mantienen dos palabras cuyos significados se oponen.

En la :num:`figura #fig-wordnet-lightning` se muestran algunos casos de hiperonimia y holonimia
en torno a la palabra *candle*. En la misma imágen se puede ver también el fenómeno polisémico de
esta palabra en inglés que puede denotar los conceptos de *vela*, *candela* o hacer referencia
al verbo, inexistente en español, para referirse a la realización de una ovoscopia.


.. _fig-wordnet-lightning:
.. graphviz::
   :caption: Esquema de relaciones semánticas en torno a la palabra *candle*, que en inglés hace referencia a los conceptos *vela* y *candela*, y también al verbo que hace referencia a la *ovoscopia*. Cada nodo representa un concepto (por lo tanto podría representarse por varios sinónimos). Las relaciones han sido extraídas de Wordnet v3.1.

   digraph foo {
        
        wick2[label="(n) wick#2\n<es:mecha>"]
        candle1[label="(n) candle#1\n<es:vela>"]
        candlewick1[label="(n) candlewick#1\n<es:pabilo>"]
        snuff1[label="(n) snuff#1"]
        lamp1[label="(n) lamp#1\n<es:lámpara>"]
        lantern1[label="(n) lantern#1\n<es:linterna>"]
        sourceofillumination1[label="(n) source of illumination#1\n<es:fuente de iluminación>"]
        dots1[label="..."]
        dip7[label="(n) dip#7"]
        vigillight1[label="(n) vigil light#1"]

        candle2[label="(n) candle#2\n<es:candela>"]
        luminousintensityunit1[label="(n) luminous intensity unit#1\n<es:unidad de intensidad lumínica>"]
        lightunit1[label="(n) light unit#1"]
        dots2[label="..."]

        entity[label="(n) entity#1\n<es:entidad>"]

        candle1v[label="(v) candle#1"]
        examine2v[label="(v) examine#2\n<es:examinar>"]

        # Hiperónimos
        wick2 -> candlewick1 [label="hyponym"]
        lamp1 -> candle1 [label="hyponym"]
        lamp1 -> lantern1 [label="hyponym"]
        sourceofillumination1 -> lamp1 [label="hyponym"]
        dots1 -> sourceofillumination1 [label="hyponym"]
        candle1 -> dip7 [label="hyponym"]
        candle1 -> vigillight1 [label="hyponym"]

        # Holónimos
        {rank=same; snuff1 candlewick1 candle1}
        snuff1 -> candlewick1 -> candle1 [style=dotted, label="meronym"]
        wick2 -> candle1 [style=dotted, label="meronym"]

        # Otra rama para candle
        dots2 -> lightunit1 -> luminousintensityunit1 -> candle2 [label="hyponym"]

        entity -> dots1 [label="hyponym"]
        entity -> dots2 [label="hyponym"]

        # Y otra más
        examine2v -> candle1v [label="hyponym"]
   }


WordNet
```````
Una de los esfuerzos más importantes para realizar una ontología de conceptos es WordNet
:cite:`Fellbaum1998`, contiene información codificada manualmente sobre sustantivos, verbos,
adjetivos y adverbios en inglés, y los organiza en torno al concepto de *synset*. Un *synset*
es un conjunto de palabras de la misma categoría gramatical que hacen referencia al mismo
concepto, por lo tanto pueden ser intercambiadas en un texto sin afectar al significado.
WordNet se encuentra actualmente en su versión 3.1 y se puede acceder online en 
``https://wordnet.princeton.edu``, cuenta con más de 117.000 synsets.

.. warning:: Incluir un poco más de WordNet, quizá fusionarlo con el apartada anterior. Podría
   hablar de taxonomías/tesauros vs ontologías/wordnet. Usos o ejemplos más concretos.

Las principales relaciones codificadas en WordNet son las de hiperonimia/hiponimia, seguidas
por las de holonimia/meronimia, ambas estructuran los conceptos en jerarquías como la que
se muestra en la :num:`figura #fig-wordnet-lightning`. Los verbos también están organizados
en jerarquías arbóreas donde los hijos expresan maneras cada vez más específicas de realizar
la acción (troponimia). Los adjetivos incluyen relaciones de antonimia, similaridad
semántica y también relaciones con los sustantivos de los cuales derivan. En cuanto a los
adverbios, son la categoría gramatical menos representada, en general están relacionados
con los adjetivos de los que derivan.

Apoyándose en WordNet se han desarrollado multitud de aplicaciones de procesamiento de
lenguaje natural, *wordnets* en otros idiomas :cite:`Atserias2004`, ontologías como SUMO
:cite:`Niles2001` o la *EuroWordNet Top Concept Ontology* :cite:`Alvez2008`.

WordNet es un recurso valiosísimo para cualquier tipo de aplicación con contenido semántico,
como lo es una interlingua para representación del conocimiento, WordNet se puede utilizar
como un diccionario para definir los conceptos que se están utilizando en cada uno de los
nodos de un grafo conceptual.


.. warning:: A este trozo se le puede dar el enfoque inverso. Titularlo como "Semántica
   estructural" e ir escribiendo poco a poco el embudo hasta llegar a hablar de las
   taxonomias y wordnet


El lenguaje universal UNL
`````````````````````````



.. attention:: Métricas automáticas de evaluación de traducciones: http://en.wikipedia.org/wiki/Machine_translation#Evaluation