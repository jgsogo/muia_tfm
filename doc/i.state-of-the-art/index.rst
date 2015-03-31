
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




El lenguaje universal UNL
-------------------------

.. attention:: Métricas automáticas de evaluación de traducciones: http://en.wikipedia.org/wiki/Machine_translation#Evaluation