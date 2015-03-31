
Estado del Arte
===============

La base de los sistemas de traducción automáticos basados en una interlingua es
que la interlingua debe representar todas las oraciones que tienen el mismo
significado de la misma manera, con el mismo conjunto de símbolos, independientemente
del idioma original del texto. Partiendo de esta representación única no ambigua
se generar las traducciones a todos los idiomas de destino como se muestra en
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

