

Ejemplo #9
``````````

    *the elements of culture that have a decisive impact on the development of individual and collective conditions regarding nutrition, work and health will also be addressed.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S]
   man(address(icl>occur(obj>topic)).@entry.@future,also)
   obj(address(icl>occur(obj>topic)).@entry.@future,element(icl>part).@def.@pl)
   mod(element(icl>part).@def.@pl,culture(icl>abstract thing).@def)
   agt(produce(icl>do),element(icl>part).@def.@pl)
   obj(produce(icl>do),impact(icl>event))
   mod(impact(icl>event),decisive)
   ben(impact(icl>event),development(icl>event).@def)
   mod(development(icl>event).@def,condition(icl>circumstance).@def.@pl)
   mod(condition(icl>circumstance).@def.@pl,collective(mod<thing))
   and(collective(mod<thing),individual(mod<thing))
   mod(condition(icl>circumstance).@def.@pl,regarding)
   obj(regarding,health.@def)
   and(health.@def,work(icl>employment).@def)
   and(work(icl>employment).@def,nutrition.@def)
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   man(address%2:32:04::, also%4:02:00::)
   obj(address%2:32:04::, element%1:09:00::)
   mod(element%1:09:00::, culture%1:14:00::)
   agt(produce%2:36:03::, element%1:09:00::)
   obj(produce%2:36:03::, impact%1:19:00::)
   mod(impact%1:19:00::, decisive%3:00:00::)
   ben(impact%1:19:00::, development%1:22:02::)
   mod(development%1:22:02::, condition%1:26:01::)
   mod(condition%1:26:01::, collective%3:00:00:joint:00)
   and(collective%3:00:00:joint:00, individual%3:00:00::)
   mod(condition%1:26:01::, regard%2:42:00::)
   obj(regard%2:42:00::, health%1:26:00::)
   and(health%1:26:00::, work%1:04:01::)
   and(work%1:04:01::, nutrition%1:13:00::)
   {/unl}


.. figure:: ../data/samples/sample09_original.png
   :name: sample09-original
   :scale: 80 %
   
   Grafo correspondiente al ejemplo #9 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

