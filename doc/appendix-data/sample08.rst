

Ejemplo #8
``````````

    *People from all cultures must join forces to achieve this goal, pooling their knowledge and experience to find solutions to a problem with a global scope and impact.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S]
   agt(join(icl>do).@entry.@obligation,:01)
   mod:01(people(icl>nation).@def.@entry.@pl,with(icl>have):01)
   obj:01(with(icl>have):01,culture(icl>abstract thing).@pl)
   mod:01(culture(icl>abstract thing).@def.@pl,all)
   obj(join(icl>do).@entry.@obligation,force(icl>thing).@pl)
   pur(join(icl>do).@entry.@obligation,achieve(icl>do))
   obj(achieve(icl>do),goal(icl>notion).@def)
   mod(goal(icl>notion).@def,this)
   coo(join(icl>do).@entry.@obligation,pool(icl>do))
   obj(pool(icl>do),:02)
   pos(:02,:01)
   and:02(experience(icl>knowledge).@def.@entry,knowledge(icl>notion).@def)
   pur(pool(icl>do),find(icl>do))
   obj(find(icl>do),solution(icl>abstract thing).@pl)
   ben(solution(icl>abstract thing).@pl,problem(icl>abstract thing))
   mod(problem(icl>abstract thing),with(icl>have):02)
   obj(with(icl>have):02,:03)
   and:03(impact(icl>abstract thing).@entry,scope(icl>extent))
   mod(:03,global(mod<thing))
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   agt(join%2:35:00::, people%1:14:00::)
   mod(people%1:14:00::, culture%1:14:00::)
   mod(culture%1:14:00::, all%3:00:00::)
   obj(join%2:35:00::, force%1:18:00::)
   pur(join%2:35:00::, achieve%2:41:00::)
   obj(achieve%2:41:00::, goal%1:09:00::)
   coo(join%2:35:00::, pool%2:40:00::)
   obj(pool%2:40:00::, experience%1:09:01::)
   pos(experience%1:09:01:: , people%1:14:00::)
   and(experience%1:09:01::, knowledge%1:03:00::)
   pur(pool%2:40:00::, find%2:32:00::)
   obj(find%2:32:00::, solution%1:10:00::)
   ben(solution%1:10:00::, problem%1:26:00::)
   mod(problem%1:26:00::, impact%1:19:00::)
   and(impact%1:19:00::, scope%1:07:00::)
   mod(impact%1:19:00::, global%5:00:00:international:00)
   {/unl}


.. figure:: ../data/samples/sample01_original.png
   :name: sample01-original
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente al ejemplo #8 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

