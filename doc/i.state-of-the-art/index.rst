
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
````````````````````
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


Conceptos y ontologías
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
semántica estructural y los principales que se dan entre significados y que han de ser
considerados en una ontología de conceptos.

--> homonimia, hiperonimia, sinonimia,...
--> ontologías y taxonomías


El lenguaje universal UNL
`````````````````````````



.. attention:: Métricas automáticas de evaluación de traducciones: http://en.wikipedia.org/wiki/Machine_translation#Evaluation