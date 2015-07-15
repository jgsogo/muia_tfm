:orphan:

.. raw:: latex

   \cleardoublepage
   \chapter*{Abstract}
   
.. only:: html

    Abstract
    ========

The work presented here develops a model to calculate the semantic distance
between two sentences represented by their UNL graphs. This problem arises
in the context of machine translation where different translators can generate
slightly different sentences from the same original. The distance measure that
is proposed aims to provide an objective evaluation on the quality of the
process involved in the generation of text.

The author carries out an exploration of the state of the art on this subject,
bringing together in a single work the proposed models of semantic distance between
concepts, models for comparison of graphs and the few proposals made to calculate
distances between conceptual graphs. It also assesses the few resources available
to experience the model and presents a methodology to generate the datasets that
would be needed to develop the proposal with the scientific rigor required
and to carry out the experimentation.

Using the previous parts a new model is proposed to compute differences between
conceptual graphs; this model allows the use of different algorithms of distance
between concepts and is parametrized in order to be able to perform a flexible
comparison between the resulting sentences.

This model is implemented in C++ programming language, it is powered with the
resources referenced above and is experienced with a set of sentences created
by the author due to the lack of other available resources.

The results of the model show that the methodology and the implementation can
lead to the achievement of a measure of distance between UNL graphs with application
in machine translation systems, however, lack of resources and of labeled data
to validate the algorithm requires an important effort to be done first in order
to be able to provide conclusive results.

