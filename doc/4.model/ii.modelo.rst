

El modelo
=========
Sean dos grafos conceptuales :math:`G_1` y :math:`G_2`, nuestro objetivo es encontrar un 
subgrafo :math:`H_1` de :math:`G_1` y un subgrafo :math:`H_2` de :math:`G_2` tal que 
:math:`H_1` y :math:`H_2` sean isomorfos y maximicen la similaridad entre los grafos
de partida. Los subgrafos :math:`H_1` y :math:`H_2` no es necesario que sean conexos.

La correspondencia entre los subgrafos :math:`H_1` y :math:`H_2` se realiza a través de una
función de similaridad semántica entre conceptos :math:`s_c(c_i, c_j)` y de similaridad entre
relaciones :math:`s_R(r_i, r_j)` que se pueden configurar con un umbral de tolerancia entre
cada pareja, :math:`t_c` y :math:`t_r`, en el intervalo :math:`[0, 1)` donde ``0`` exige
una correspondencia exacta y ``1`` aceptaría como iguales cualquier pareja.

