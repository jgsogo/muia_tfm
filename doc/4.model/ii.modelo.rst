

El modelo
=========
Sean dos grafos conceptuales :math:`G_1` y :math:`G_2`, nuestro objetivo es encontrar un 
subgrafo :math:`H_1` de :math:`G_1` y un subgrafo :math:`H_2` de :math:`G_2` tal que 
:math:`H_1` y :math:`H_2` sean isomorfos y maximicen la similaridad entre los grafos
de partida. Los subgrafos :math:`H_1` y :math:`H_2` no es necesario que sean conexos.

La correspondencia entre los subgrafos :math:`H_1` y :math:`H_2` se realiza a través de una
función de similaridad semántica entre conceptos :math:`s_C(c_i, c_j)` y de similaridad entre
relaciones :math:`s_R(r_i, r_j)` que se pueden configurar con un umbral de tolerancia entre
cada pareja de conceptos o relaciones, :math:`t_c` y :math:`t_r` respectivamente, en el
intervalo :math:`[0, 1)` donde :math:`0` exige una correspondencia exacta y :math:`1`
aceptaría como iguales cualquier pareja.

La búsqueda de los subgrafos :math:`H_1` y :math:`H_2` se realiza utilizando el algoritmo
McGregor y guardando todos los subgrafos comunes candidatos a ser máximo subgrafo común;
en un paso posterior se escoge de entre los candidatos el subconjunto que maximice la
similaridad entre los grafos de partida (no se consideran componentes formados por
un único nodo). Así:

.. math::

   sim(G_1, G_2) = argmax \sum_{i \in G_1, j \in G_2} sim(c_i, c_j) + sim(r_i, r_j)

Este valor se normaliza teniendo en cuenta el valor máximo que podría alcanzar, el cual
se calcula considerando todos los ejes y conexiones de ambos grafos:

.. math::

   sim_{MAX}(G_1, G_2) = max(|G_1|, |G_2|) + max(e_{G_1}, e_{G_2})
   
donde :math:`|G_i|` representa la cardinalidad del grafo :math:`G_i`, es decir, el
número de nodos y :math:`e_{G_i}` es el número de conexiones existentes en el 
grafo :math:`G_i`.

Por lo tanto, el valor de similaridad se calcularía como 

.. math::   

   s(G_1, G_2) = \frac{sim(G_1, G_2)}{sim_{MAX}(G_1, G_2)}
   
y tomará siempre valores en el intervalo :math:`[0, 1]`.

.. _fig-model-example-graph:
.. graphviz::
   :caption: Grafos de ejemplo :math:`g_1` (izda) y :math:`g_2` (dcha).

   digraph foo {
     subgraph cluster_A {
         a0 [label="A"]
         a1 [label="B"]
         a2 [label="C"]
         a3 [label="D"]
         a4 [label="E"]
         a5 [label="F"]
         a6 [label="G"]
         a7 [label="H"]
         a8 [label="I"]
         a0 -> a3
         a1 -> a3 -> a4 -> a5
         a1 -> a2 -> a3 
         a3 -> a5
         a1 -> a5
         a6 -> a7 -> a8
         a4 -> a8
         label = "Grafo g1";
         color = gray;
     }

     subgraph cluster_B {
         b0 [label="A"]
         b1 [label="B"]
         #b2 [label="C"]
         b3 [label="D"]
         b4 [label="E"]
         b5 [label="F"]
         b6 [label="G"]
         b7 [label="H"]
         b8 [label="i"]
         b1 -> b3-> b4 -> b5
         b1 -> b5
         b0 -> b4
         b0 -> b5
         b6 -> b7 -> b8
         b4 -> b7
         label = "Grafo g2";
         color = gray;
     }
   }

En la :num:`figura #fig-model-example-graph` se muestran dos grafos que servirán de
ejemplo para ilustrar el modelo. En este caso no se han introducido etiquetas en las
relaciones para simplificar la representación.

El algoritmo de McGregor nos permitirá realizar la búsqueda del máximo grafo común
de una forma ordenada. Utilizando un nivel de tolerancia entre conceptos :math:`t_c=0`
exigimos una correspondencia exacta entre ellos y obtenemos el resultado de la
:num:`figura #fig-model-example-mcs1`.

En dicha figura se ha marcado en color los nodos y las relaciones que pertenecen a
la solución de nuestro algoritmo: en este caso estaría formada por dos subgrafos
(el rojo se correspondenría con el máximo grafo común) y ambos contribuyen al
valor de similaridad. A pesar de que hay otros nodos que también están presentes
en ambos grafos (como el nodo :math:`A`) éste no forma parte de la solución puesto
que está aislado y ya hemos comentado que sólo se consideran aquellos componentes que
estén formados por un mínimo de dos nodos (como es el caso de la pareja :math:`G, H`).

 
.. _fig-model-example-mcs1:
.. graphviz::
   :caption: Máximo grafo común de :math:`g_1` y :math:`g_2` con nivel de tolerancia, :math:`t_c=0` (exige correspondencia exacta en los nodos).

   digraph foo {
     subgraph cluster_A {
         a0 [label="A"]
         a1 [label="B", color=red]
         a2 [label="C"]
         a3 [label="D", color=red]
         a4 [label="E", color=red]
         a5 [label="F", color=red]
         a6 [label="G", color=blue]
         a7 [label="H", color=blue]
         a8 [label="I"]
         a0 -> a3
         a1 -> a3 -> a4 -> a5 [color=red]
         a1 -> a2 -> a3 
         a3 -> a5
         a1 -> a5 [color=red]
         a6 -> a7 [color=blue]
         a7 -> a8
         a4 -> a8
         label = "Grafo g1";
         color = gray;
     }

     subgraph cluster_B {
         b0 [label="A"]
         b1 [label="B", color=red]
         #b2 [label="C"]
         b3 [label="D", color=red]
         b4 [label="E", color=red]
         b5 [label="F", color=red]
         b6 [label="G", color=blue]
         b7 [label="H", color=blue]
         b8 [label="i"]
         b1 -> b3-> b4 -> b5 [color=red]
         b1 -> b5 [color=red]
         b0 -> b4
         b0 -> b5
         b6 -> b7  [color=blue]
         b7 -> b8
         b4 -> b7
         label = "Grafo g2";
         color = gray;
     }
   }

El valor de similaridad calculado por el modelo sería la suma de las similaridades de
los dos subgrafos coincidentes, entre la máxima posible:

.. math::

   s(g_1, g_2)_{t_c=0}=\frac{s_{g_{ROJO}} + s_{g_{AZUL}}}{max(|g_1|, |g_2|) + max(e_{g_1}, e_{g_2})}
   
y como hemos exigido una correspondencia exacta (:math:`t_c=0`) entonces la similaridad
entre cada pareja de nodos será la máxima (la unidad) y podemos calcular el valor
resultante de forma sencilla:

.. math::

   s(g_1, g_2)_{t_c=0}=\frac{|g_{ROJO}| + |g_{AZUL}| + e_{g_{ROJO}} + e_{g_{AZUL}}}{|g_1| + e_{g_1}} = \frac{4 + 2 + 4 + 1}{9 + 11} = \frac{11}{20}


Si aumentamos la tolerancia entre conceptos, :math:`t_c`, ocurrirá que nodos que
antes no aparecían en la solución comiencen a hacerlo puesto que su distancia semántica
según la medida elegida será menor que el umbral de tolerancia utilizado como
parámetro. En concreto, si hacemos que el valor :math:`t_c` verifique que

.. math::

    t_c \geq d(I, i)  \Rightarrow  t_c \geq 1 - s(I, i)

entonces la solución de nuestro algoritmo será la mostrada en la
:num:`figura #fig-model-example-mcs2` donde se verifica que :math:`I \approx i` y se
incorporan a la solución en el subgrafo azul.


.. _fig-model-example-mcs2:
.. graphviz::
   :caption: Máximo grafo común de :math:`g_1` y :math:`g_2` con nivel de toleracia, :math:`t_c \geq d(I, i)`.

   digraph foo {
     subgraph cluster_A {
         a0 [label="A"]
         a1 [label="B", color=red]
         a2 [label="C"]
         a3 [label="D", color=red]
         a4 [label="E", color=red]
         a5 [label="F", color=red]
         a6 [label="G", color=blue]
         a7 [label="H", color=blue]
         a8 [label="I", color=blue]
         a0 -> a3
         a1 -> a3 -> a4 -> a5 [color=red]
         a1 -> a2 -> a3 
         a3 -> a5
         a1 -> a5 [color=red]
         a6 -> a7 [color=blue]
         a7 -> a8 [color=blue]
         a4 -> a8
         label = "Grafo g1";
         color = gray;
     }

     subgraph cluster_B {
         b0 [label="A"]
         b1 [label="B", color=red]
         #b2 [label="C"]
         b3 [label="D", color=red]
         b4 [label="E", color=red]
         b5 [label="F", color=red]
         b6 [label="G", color=blue]
         b7 [label="H", color=blue]
         b8 [label="i", color=blue]
         b1 -> b3-> b4 -> b5 [color=red]
         b1 -> b5 [color=red]
         b0 -> b4
         b0 -> b5
         b6 -> b7 [color=blue]
         b7 -> b8 [color=blue]
         b4 -> b7
         label = "Grafo g2";
         color = gray;
     }
   }

El valor de similaridad será mayor que el calculado anteriormente, en concreto se 
incrementará debido a la similaridad aportada por la nueva conexión que pasa a 
formar parte de la solución y la similaridad entre los nodos:

.. math::

   s(g_1, g_2)_{t_c \geq d(I,i)}= s(g_1, g_2)_{t_c=0} + \frac{1 + s(I, i)}{20} = \frac{12 + s(I, i)}{20}
   
El valor de similaridad se incrementa a medida que aumentamos los umbrales de
tolerancia. En grafos donde la correspondencia entre nodos no sea tan evidente al
aumentar el umbral de tolerancia van a aparecer subgrafos
superpuestos, en estos casos el modelo deberá explorar todas las combinaciones posibles
para quedarse con la solución que maximice la similaridad.




