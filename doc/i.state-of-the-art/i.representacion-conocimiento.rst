

Sistemas de representación del conocimiento
-------------------------------------------


.. grafos-conceptuales_
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


.. wordnet_
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
nodos de un grafo conceptual y medir la distancia semántica entre conceptos utilizados
en diferentes traducciones de un mismo texto.


El lenguaje universal UNL
`````````````````````````
Un paso adelante en las interlinguas para representación del conocimiento es el lenguaje
universal (UNL, *Universal Networking Language*); este *lenguaje* surgió como una
iniciativa del Instituto de Estudios Avanzados de la Universidad de la Naciones Unidas
en 1996 con el objetivo de eliminar las barreras lingüísticas para el comercio y la
educación.

La representación de un texto en UNL se realiza oración por oración, cada oración se
codifica en un hipergrafo donde los conceptos son los nodos y las relaciones entre ellos
constituyen los arcos. ESte hipergrafo también puede ser representado como un conjunto
de relaciones binarias que enlazan los conceptos presentes en la oración. Los conceptos
se representan con etiquetas literales que reciben el nombre de *Palabras Universales*
(UW, Universal Words) que además pueden ir acompañadas de diferentes attributos que
permiten mostrar más informacón sobre el uso específico del concepto en la oración
original :cite:`Uchida1999`.

Como ejemplo, mostramos el utilizado por Uchida y Zhu en :cite:`Uchida2001` donde muestran
la codificación de la oración "Hace tiempo, en la ciudad de Babilonia, la gente comenzó a
construir una torre enorme, que parecía alcanzar los cielos." tanto en su forma
gráfica (:num:`figura #fig-example-unl`) como codificada (:num:`listado #code-example-unl`).


.. _fig-example-unl:
.. graphviz::
   :caption: Representación gráfica en UNL de la oración "Hace tiempo, en la ciudad de Babilonia, la gente comenzó a construir una torre enorme, que parecía alcanzar los cielos.".

   digraph foo {

        begun[label="begin(icl>do).@entry.@past"]
        long_ago[label="long ago(icl>ago)"]
        city[label="city(icl>region).@def"]
        Babylon[label="Babylon(iof>city)"]
        people[label="people(icl>person).@def"]
        build[label="build(icl>do)"]
        tower[label="tower(icl>building).@indef"]
        huge[label="huge(icl>big)"]
        seemed[label="seem(icl>be).@past"]
        reach[label="reach(icl>come).@begin.@soon"]
        heaven[label="heaven(icl>region).@def.@pl"]

        begun -> build [label="obj"]
        build -> tower [label="obj"]
        begun -> people [label="agt"]
        begun -> long_ago [label="tim"]
        begun -> city [label="plc"]
        city -> Babylon [label="mod"]
        build -> people [label="agt"]
        tower -> huge [label="aoj"]
        reach -> tower [label="obj"]
        seemed -> tower [label="aoj"]
        reach -> seemed [label="obj", dir=back]
        reach -> heaven [label="gol"]

        {rank=same; begun build tower}
        }


.. code-block:: unl
   :caption: Codificación en UNL de la oración "Hace tiempo, en la ciudad de Babilonia, la gente comenzó a construir una torre enorme, que parecía alcanzar los cielos.".
   :name: code-example-unl
   
    [S:2]
    {org:es}
    Hace tiempo, en la ciudad de Babilonia, la gente comenzó a construir una torre enorme, que parecía alcanzar los cielos.
    {/org}
    {unl}
    tim(begin(icl>do).@entry.@past, long ago(icl>ago))
    mod(city(icl>region).@def, Babylon(iof>city))
    plc(begin(icl>do).@entry.@past, city (icl>region).@def)
    agt(begin(icl>do).@entry.@past, people(icl>person).@def)
    obj(begin(icl>do).@entry.@past, build(icl>do))
    agt(build(icl>do), people.@def)
    obj(build(icl>do), tower(icl>building).@indef)
    aoj(huge(icl>big), tower(icl>building).@indef)
    aoj(seem(icl>be).@past, tower(icl>building).@indef)
    obj(seem(icl>be).@past, reach(icl>come).@begin.@soon)
    obj(reach(icl>come).@begin-soon, tower(icl>building).@indef)
    gol(reach(icl>come).@begin-soon, heaven(icl>region).@def.@pl)
    {/unl}
    [/S]


En el ejemplo indicado aparecen numerosas relaciones como ``mod``, ``agt``, ``aoj``, etc
indicando la relación entre los conceptos (UWs) que enlazan, aparecen varias UWs como
``city(icl>region)``, ``tower(icl>building)`` que indican objetos o ``seem(icl>be)``, 
``begin(icl>do)`` que son verbos, e incluso adjetivos como ``huge(icl>big)`` o el adverbio
``long ago(icl>ago)``; también aparece una UW que es un nombre propio de ciudad
``Babylon(iof>city)``. Muchas UWs están acompañada por varios attributos como ``@past``,
``@def`` o ``@entry``.
Las palabras universales UWs y las relaciones están diseñadas para representar el contenido
objetivo del texto (el mensaje, la información, el contenido semántico), mientras que los
atributos codifican rasgos gramaticales del lenguaje, intencionalidad, etc. que pueden
no ser representables en todas las lenguas.

La principal diferencia entre el UNL y otros sistemas de representación del conocimiento como
los grafos conceptuales (ver :num:`sección #grafos-conceptuales`) o el *Resource Description
Framework* (RDF :cite:`Brickley2014`) es que el número y el significado de las relaciones y
attributos forman parte del estándar :cite:`TeixeiraMartins2005`. La última específicación del
lenguaje, UNL Version II (16 de febrero de 2014) :cite:`Zhu2014`, incluye 57 relaciones y
94 atributos.
Las UWs no son un conjunto cerrado, cualquier persona puede proponer nuevas UWs que expresen
un concepto no contemplado hasta el momento, si bien existe una base de datos, UNL Knowledge Base,
con todas las UWs aceptadas y sus relaciones :cite:`Zhu2002`.

.. warning:: Aquí se puede hablar muchísimo más sobre UNL, describirlo incluso, ¿interesa? De
   momento sólo vamos a pasar por encima de los conceptos más relevantes para lo que nos
   traemos entre manos.


Palabras universales (UWs)
++++++++++++++++++++++++++

Las UWs constituyen una red de palabras similar a la vista en WordNet (:num:`sección #wordnet`),
UNL tiene las mismas cuatro categorías de conceptos: sustantivos, verbos, adjetivos y adverbios.
Las UWs se forman utilizando una palabra inglesa como etiqueta seguida de un conjunto de 
restricciones: ``<UW> ::= <headword> [<constraint list>]``:

 * La *headword* es una expresión en inglés (usualmente es una plabra, pero puede ser una
   palabra compuesta o una oración si es necesario) que representa un conjunto de conceptos
   a los que hace referencia esa expresión en inglés, se conoce como ***Basic UW***. Si no
   existe una etiqueta en inglés para hacer referencia al concepto, entonces la UW se 
   conoce como *Extra UW*.
 * La lista de restricciones sirve para desambiguar los distintos significados a los que puede
   hacer referencia una misma *headword*. Cada restricción está formada por una relación UNL
   y otra UW previamente definida que se combina con esta UW en dicha relación. Estas UWs
   desambiguadas se conocen como *Restricted UW*. 

La :num:`tabla #table-uws-example` muestra algunos ejemplos de UWs con los significados
correspondientes; aparecen algunas UWs básicas como *go* o *house*, UWs restringidas

.. list-table:: Ejemplos de UWs.
   :name: table-uws-example
   :header-rows: 1

   * - UW
     - Headword
     - Restricciones
     - Significado
   * - go
     - go
     -
     - Ir
   * - house
     - house
     -
     - Casa
   * - state(icl>country)
     - state
     - icl>country
     - País
   * - state(icl>region)
     - state
     - icl>region
     - Región de un país
   * - state(icl>express(agt>thing,gol>person,obj>thing))
     - state
     - icl>express(agt>thing,gol>person,obj>thing)
     - Acción por la que una persona expresa algo
   * - samba(icl>dance)
     - samba
     - icl>dance
     - Danza popular brasileña.
   * - soufflé(icl>food)
     - soufflé
     - icl>food
     - Tipo de comida


UNL Ontology - UNL Knowledge Base [#]_
++++++++++++++++++++++++++++++++++++++

.. [#] En la bibliografía anterior a la especificación UNL Version II la *UNL Ontology*
   aparece como *UNL Knowledge Base*

Esta base de datos constituye una red semántica con todas las relaciones binarias dirigidas que
existen entre las palabras universales (UWs); asigna a estas relaciones un grado de certeza
absoluto (imposible o verdadero). De esta forma cualquier UW aceptada aparecerá en la
ontología relacionada con otras palabras.

Todas las UWs aparecen relacionadas con otras utilizando alguna de estas tres relaciones:

 * ``icl`` (incluido en, tipo de): indica un concepto superior o más general, codifica la
   relación de hiponimia descrita en apartados anteriores.
 * ``equ`` (equivalencia): indica equivalencia entre dos conceptos, se puede asimilar a
   una relación de sinonimia.
 * ``iof`` (instancia de): indica el tipo de concepto al que pertenece la instancia, se
   utiliza con entidades y nombres propios.
 * ``pof`` (parte de): codifica la relación de meronimia.

La Ontología UNL contiene también el resto de relaciones posibles entre cualquier par de
UWs, no obstante, estas relaciones aparecen entre los conceptos más generales posibles,
de tal forma que se explota la propiedad de herencia de las UWs: cualquier UWs hereda las
relaciones más restrictivas de sus hiperónimos.

Esta ontología constituye una red semántica con características similares a WordNet, por lo
que las técnicas y metodologías utilizadas sobre WordNet podrán ser aplicadas al sistema UNL
sin requerir una adaptación especial. En concreto en el problema de distancia entre grafos
conceptuales, la distancia entre los conceptos podrá ser medida utilizando las relaciones
presentes en esta ontología.
