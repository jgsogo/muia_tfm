

Ejemplo #10
```````````

    *Stable and lasting peace requires something more than stopping war and other situations of conflict.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S:3]
   aoj(require(icl>need(icl>be)).@entry,peace(icl>abstract thing).@def)
   mod(peace(icl>abstract thing).@def,lasting(mod<thing))
   and(lasting(mod<thing),stable(mod<thing))
   obj(require(icl>need(icl>be)).@entry,more(icl>thing))
   mod(more(icl>thing),a_little)
   bas(more(icl>thing),stop(icl>do))
   obj(stop(icl>do),situation(icl>condition).@pl)
   mod(situation(icl>condition).@pl,other(mod<thing))
   mod(situation(icl>condition).@pl,conflict)
   and(situation(icl>condition).@pl,war.@def)
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   aoj(require%2:34:00::, peace%1:26:00::)
   mod(peace%1:26:00::, lasting%3:00:00:long:02)
   and(lasting%3:00:00:long:02, stable%3:00:00::)
   obj(require%2:34:00::, more%4:02:00::)
   bas(more%4:02:00::, stop%2:42:00::)
   obj(stop%2:42:00::, situation%1:26:00::)
   mod(situation%1:26:00::, other%3:00:00::)
   mod(situation%1:26:00::, conflict%1:26:00::)
   and(situation%1:26:00::, war%1:04:00::)
   {/unl}


.. figure:: ../data/samples/sample10_original.png
   :name: sample10-original
   :scale: 70 %
   
   Grafo correspondiente al ejemplo #10 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

