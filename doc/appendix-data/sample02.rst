

Ejemplo #2
``````````

    *In their 29th General Conference, the 186 member states of the Unesco ratified their unanimous support of the project, jointly organized by the Spanish government, the Catalan autonomous government and the Barcelona City Council.*
    

.. code-block:: unl
   :caption: Codificación UNL original.
   
   [S]
   agt(ratify(icl>do).@complete.@entry.@past,member state.@def.@pl)
   qua(member state.@def.@pl,186)
   mod(member state.@def.@pl,unesco.@def)
   scn(ratify(icl>do).@complete.@entry.@past,conference(icl>meeting).@def)
   mod(conference(icl>meeting).@def,29.@ordinal)
   mod(conference(icl>meeting).@def,member state.@def.@pl)
   obj(ratify(icl>do).@complete.@entry.@past,support(icl>action))
   mod(support(icl>action),unanimous(mod<thing))
   mod(support(icl>action),member state.@def.@pl)
   obj(support(icl>action),project(icl>plan(icl>thing)).@def)
   obj(organize(icl>do),project(icl>plan(icl>thing)).@def)
   man(organize(icl>do),jointly)
   agt(organize(icl>do),government(icl>organization):01.@def)
   mod(government(icl>organization):01.@def,spanish(mod<thing))
   and(government(icl>organization):01.@def,government(icl>organization):02.@def)
   mod(government(icl>organization):02.@def,Catalonian)
   mod(government(icl>organization):02.@def,autonomous(mod<thing))
   and(government(icl>organization):02.@def,:02)
   mod:02(council(icl>organization).@def.@entry,city.@def)
   mod(:02,Barcelona) 
   [/S]

.. Comentario

.. code-block:: unl
   :caption: Codificación utilizada para el experimento (la codificación de los conceptos se corresponde con WordNet 3.1).
   
   {unl}
   agt(ratify%2:41:00::, state%1:14:00::)
   mod(state%1:14:00::, unesco%1:14:00::)
   plc(ratify%2:41:00::, conference%1:14:00::)
   mod(conference%1:14:00::, state%1:14:00::)
   obj(ratify%2:41:00::, support%1:04:00::)
   mod(support%1:04:00::, consentaneous%5:00:00:accordant:00)
   mod(support%1:04:00::, state%1:14:00::)
   obj(support%1:04:00::, project%1:04:00::)
   obj(organize%2:41:00::, project%1:04:00::)
   man(organize%2:41:00::, jointly%4:02:02::)
   agt(organize%2:41:00::, 01%government%1:14:00::)
   mod(01%government%1:14:00::, spanish%3:01:00::)
   and(01%government%1:14:00::, 02%government%1:14:00::)
   mod(02%government%1:14:00::, autonomous%5:00:00:free:00)
   and(02%government%1:14:00::, council%1:14:01::)
   mod(council%1:14:01::, city%1:15:01::)
   mod(council%1:14:01::, barcelona%1:15:00::)
   {/unl}


.. figure:: ../data/samples/sample02_original.png
   :name: sample02-original
   :scale: 100 %
   :width: 100 %
   
   Grafo correspondiente al ejemplo #2 utilizado en el experimento (se muestran
   únicamente las *headwords* correspondientes a cada concepto).
   

   

