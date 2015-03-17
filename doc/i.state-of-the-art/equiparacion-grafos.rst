
Equiparación de grafos
======================

En la literatura se pueden encontrar diferentes metodologías para medir la distancia entre dos grafos dados:

 #. Graph edit distance
 #. Minimum/maximum common subgraph
 #. Matrices representing the graph - spectral matching
        Tienen el serio incoveniente de que sólo sirven para comparar estructura, pero no consideran los atributos de los nodos ni de los edges.
 
Debemos repasarlas todas ellas para ver cómo se adecúan al problema que estamos intentando abordar en este trabajo.

En [Gelbukh2002] se habla de que los grafos son bipartitos (por un lado la información de los nodos y por otro la de los
edges) y propone una medida de similaridad que es la combinación de dos diferentes: conceptual similarity and
relational similarity