

Ejemplo #7
``````````

    *Sustainable Development satisfies the needs of the present without compromising future generations' abilities to satisfy theirs, and is based on the natural environment's capacity to provide for humankind.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S]
   aoj:01(rest(icl>be).@entry,:02)
   mod:02(development(icl>event).@def.@entry,sustainable(mod<thing))
   met:01(rest(icl>be).@entry,capacity(icl>ability).@def)
   mod:01(capacity(icl>ability).@def,environment.@def)
   mod:01(environment.@def,natural(mod<thing))
   obj:01(capacity(icl>ability).@def,provide_for)
   ben:01(provide_for,humankind.@def)
   and(:01.@entry,:03)
   agt:03(satisfy(icl>do):01.@entry,:02)
   obj:03(satisfy(icl>do):01.@entry,need(icl<abstract thing):01.@def.@pl)
   mod:03(need(icl<abstract thing):01.@def.@pl,present(icl>time).@def)
   man:03(satisfy(icl>do):01.@entry,without(icl>how))
   obj:03(without(icl>how),compromise(icl>do))
   obj:03(compromise(icl>do),ability)
   mod:03(ability,:04)
   mod:04(generation(icl>human group).@def.@entry.@pl,future(mod<thing))
   obj:03(ability,satisfy(icl>do):02)
   obj:03(satisfy(icl>do):02,need(icl<abstract thing):02.@def.@pl)
   mod:03(need(icl<abstract thing):02.@def.@pl,:04)
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   aoj(rest%2:42:12::, development%1:22:02::)
   mod(development%1:22:02::, sustainable%3:01:00::)
   met(rest%2:42:12::, capacity%1:07:00::)
   mod(capacity%1:07:00::, environment%1:15:00::)
   mod(environment%1:15:00::, natural%3:00:02::)
   obj(capacity%1:07:00::, provide%2:34:00::)
   ben(provide%2:34:00::, humankind%1:05:00::)
   and(rest%2:42:12::, satisfy%2:34:01::)
   agt(satisfy%2:34:01::, development%1:22:02::)
   obj(satisfy%2:34:01::, need%1:17:00::)
   mod(need%1:17:00::, present%3:00:01::)
   man(satisfy%2:34:01::, compromise%2:32:03::)
   obj(compromise%2:32:03::, ability%1:07:00::)
   mod(ability%1:07:00::, generation%1:14:01::)
   mod(generation%1:14:01::, future%3:00:00::)
   obj(ability%1:07:00::, 02%satisfy%2:34:01::)
   obj(02%satisfy%2:34:01::, 02%need%1:17:00::)
   mod(02%need%1:17:00::, generation%1:14:01::)
   {/unl}


.. figure:: ../data/samples/sample07_original.png
   :name: sample07-original
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente al ejemplo #7 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

