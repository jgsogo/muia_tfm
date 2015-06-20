

El modelo
=========
Sean dos grafos conceptuales :math:`G_1` y :math:`G_2`, nuestro objetivo es encontrar un 
subgrafo :math:`H_1` de :math:`G_1` y un subgrafo :math:`H_2` de :math:`G_2` tal que 
:math:`H_1` y :math:`H_2` sean isomorfos y maximicen la similaridad entre los grafos
de partida. Los subgrafos :math:`H_1` y :math:`H_2` no es necesario que sean conexos.

La correspondencia entre los subgrafos :math:`H_1` y :math:`H_2` se realiza a través de una
función de similaridad semántica entre conceptos :math:`s_c(c_i, c_j)` y de similaridad entre
relaciones :math:`s_R(r_i, r_j)` que se pueden configurar con un umbral de tolerancia entre
cada pareja de conceptos o relaciones, :math:`t_c` y :math:`t_r` respectivamente, en el
intervalo :math:`[0, 1)` donde ``0`` exige una correspondencia exacta y ``1`` aceptaría
como iguales cualquier pareja.

La búsqueda de los subgrafos :math:`H_1` y :math:`H_2` se realiza utilizando el algoritmo
McGregor y guardando todos los subgrafos comunes candidatos a ser máximo subgrafo común;
en un paso posterior se escoge de entre los candidatos, el subconjunto que maximice la
similaridad entre los grafos de partida.

.. warning:: Meter un poco de formulación


.. _fig-model-example-graph:
.. graphviz::
   :caption: Grafos de ejemplo :math:`g_1` (izda) y :math:`g_2` (dcha).

   digraph foo {
    # Grafo 1
    A[label="A"]
    B[label="B"]
    C[label="C"]
    D[label="D"]
    E[label="E"]
    
    A -> B
    A -> C
    D -> C
    D -> E
    
    # Grafo 2
    A2[label="A"]
    B2[label="B"]
    C2[label="F"]
    D2[label="d"]
    E2[label="E"]
    
    A2 -> B2
    A2 -> C2
    D2 -> C2
    D2 -> E2
   }


Así, por ejemplo, dada la pareja de grafos :math:`g_1` y :math:`g_2` de la
:num:`figura #fig-model-example-graph`, el modelo deberá ser capaz de encontrar
el máximo grafo común que comparten ambos, :math:`mcs(g_1, g_2)` para un nivel de
tolerancia dado. 
 
.. _fig-model-example-mcs1:
.. graphviz::
   :caption: Máximo grafo común de :math:`g_1` y :math:`g_2` con nivel de tolerancia, :math:`t_c=0`. NOTA.- En el modelo final se eliminarán los componentes del grafos que consten de un único nodo.

   digraph foo {
    # MCS
    A[label="A"]
    B[label="B"]
    E[label="E"]
    
    A -> B
   }

En la :num:`figura #fig-model-example-mcs1` se muestra el resultado con un nivel de
tolerancia, :math:`t_c=0`, que exige que los nodos sean idénticos. Como se puede
comprobar sólo existen tres nodos que cumplan esta condición, y sólo hay una conexión
entre ellos.


.. _fig-model-example-mcs2:
.. graphviz::
   :caption: Máximo grafo común de :math:`g_1` y :math:`g_2` con nivel de toleracia, :math:`t_c \neq 0`, suficiente para considerar :math:`D \approx d`.

   digraph foo {
    # MCS
    A[label="A"]
    B[label="B"]
    D[label="D = d"]
    E[label="E"]
    
    A -> B
    D -> E
   }


