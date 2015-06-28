
.. raw:: latex

    \newpage


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
en interlingua, deberíamos obtener una codificación idéntica a la que hemos
utilizado para generarlos [#]_. La calidad de la traducción en cuanto a su fiabilidad, 
entendida como contenido semántico transmitido, estará por lo tanto directamente
relacionada con la proximidad entre las dos representaciones en interlingua; así
una medida adecuada de distancia o de similaridad entre ambas representaciones resulta
ser una herramienta de extremada utilidad para evaluar un sistema de traducción automática.

.. [#] Podrán existir diferencias debidas a fenómenos lingüísticos como la paráfrasis y
   también pérdidas de significado debidas a limitaciones de la lengua de destino si ésta
   no es capaz de representar toda la riqueza semántica del texto original.

En este capítulo estudiamos el estado del arte de los sistemas de representación del
conocimiento que son utilizados como interlinguas, y en concreto nos centraremos en
aquéllos cuya representación formal es un grafo; posteriormente expondremos las 
medidas que se han propuesto en la bibliografía para estudiar la similaridad entre dos
grafos, veremos cómo evaluar la distancia semántica entre conceptos y textos, y
finalmente repasaremos los modelos propuestos que integran lo anterior para evaluar
la distancia entre grafos conceptuales (manifiestan una distancia debida a la estructura
del grafo y también al contenido de los nodos) analizando en profundidad cuáles son sus
principales aportaciones y las dificultades que aún están presentes.

.. TODO: Quizá estos párrafos anteriores son más introducción que estado del arte

.. toctree::
   :maxdepth: 4

   i.representacion-conocimiento
   ii.medidas-distancia
   iii.distancia-semantica
.. iv.evaluacion-traducciones
.. v.problemas-combinatorios
