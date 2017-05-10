
ionCore
=======

ionCore is the basis for all other modules, a set of boilerplate functions, classes, and templates.

Everything is organized by file.


Files
-----

ionBitwise.h
^^^^^^^^^^^^

* :doc:`doxy/class_ion_Bitwise`

Tools for bitwise operations.


ionClass.h
^^^^^^^^^^

Type information and base classes.

* :doc:`doxy/class_Singleton`
* :doc:`doxy/class_SingletonPointer`
* :doc:`doxy/struct_Type`


ionComparison.h
^^^^^^^^^^^^^^^

Floating point comparison functions.

* :doc:`doxy/struct_RoundingError-2`
* :doc:`doxy/struct_RoundingError`
* :doc:`doxy/struct_RoundingError-3`


ionComponent.h
^^^^^^^^^^^^^^

Component-Entity base classes.

* :doc:`doxy/class_IEntity`


ionLogger.h
^^^^^^^^^^^

Logging class.

* :doc:`doxy/class_Log`


ionRand.h
^^^^^^^^^

Random number generators and helpers.

* :doc:`doxy/class_Random`
* :doc:`doxy/class_IRandomGenerator`
* :doc:`doxy/class_CLinearCongruentialGenerator`


ionStandardLibrary.h
^^^^^^^^^^^^^^^^^^^^

Brings a lot of elements from ``std`` namespace into the global namespace.
Includes some helper functions for general tasks.

* :doc:`doxy/class_File`
* :doc:`doxy/class_String`


ionTreeNode.h
^^^^^^^^^^^^^

Base classes to create trees (e.g. for event graphs).

* :doc:`doxy/class_ITreeNode`
* :doc:`doxy/class_IMultiTreeNode`


ionTypes.h
^^^^^^^^^^

Defines typedefs for integer and floating point types.


ionUtils.h
^^^^^^^^^^

Some general helper functions.
