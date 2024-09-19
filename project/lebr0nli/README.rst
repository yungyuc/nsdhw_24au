###################################
 py-rbush: Porting rbush to Python
###################################

*******************
 Basic Information
*******************

Github repository: `lebr0nli/py-rbush <https://github.com/lebr0nli/py-rbush>`_

R-Tree structures are widely used for spatial indexing, enabling fast searches
in multi-dimensional space. There's already a `parietal-io/py-rbush
<https://github.com/parietal-io/py-rbush>`_ which is a Python port of the
popular JavaScript library `mourner/rbush <https://github.com/mourner/rbush>`_,
designed for 2D spatial indexing of points and rectangles. However, the Python
version, `py-rbush`, is an outdated and dead project, with its last commit made
over six years ago. This project seeks to rewrite `py-rbush` from the ground up,
aiming to bring the performance and capabilities of the original `rbush` to
Python, while taking advantage of Python-specific optimizations. Also I will add
some missing features of the current `py-rbush` from the `rbush`.

******************
 Problem to Solve
******************

Although `numpy` is used in `py-rbush`, I believe there are areas where
performance can still be improved. The primary focus of this project will be:

#. Rewriting the core algorithms to enhance performance while maintaining the
   simplicity of use.
#. `py-rbush` didn't implement all the features of the original `rbush`, so I
   will add those missing features.

*******************
 Prospective Users
*******************

The updated version of `py-rbush` will be valuable for developers and
researchers in fields that require fast, scalable spatial indexing, such as:

-  Geographic Information Systems (GIS)
-  Computer Vision and Image Processing
-  Game Development
-  Computational Geometry

*********************
 System Architecture
*********************

`py-rbush` will consist of two main components:

#. **C++ Backend:** The core R-Tree implementation will be written in C++ for
   performance reasons. This will be wrapped using `pybind11` to provide a
   Python interface.

#. **Python Frontend:** The Python frontend will provide a user-friendly API for
   interacting with the R-Tree. This will include methods for inserting,
   deleting, and querying spatial data.

*****************
 API Description
*****************

The library will follow the design and functionality of the original `prbush`.
The core API will include:

#. **Creating a Tree**

   .. code:: python

      tree = RBush(max_entries=9)

   An optional `max_entries` parameter defines the maximum number of entries in
   each tree node. A value of `9` is used by default, but this can be adjusted
   based on performance needs.

#. **Adding Data**

   Insert an item:

   .. code:: python

      item = {"minX": 20, "minY": 40, "maxX": 30, "maxY": 50, "data": "example"}
      tree.insert(item)

   .. epigraph::

      This term project currently supports only two dimensions but aims to include three-dimensional support in the future.

#. **Removing Data**

   Remove a previously inserted item:

   .. code:: python

      tree.remove(item)

   If a custom comparison is needed (e.g., comparing by specific fields), a
   function can be provided:

   .. code:: python

      tree.remove(item_copy, lambda a, b: a["id"] == b["id"])

   Remove all items:

   .. code:: python

      tree.clear()

#. **Data Format**

   By default, items are expected to have `minX`, `minY`, `maxX`, and `maxY`
   properties. This format can be customized by overriding methods:

   .. code:: python

      class MyRBush:
          def to_bbox(self, item):
              return {"minX": item[0], "minY": item[1], "maxX": item[0], "maxY": item[1]}

          def compare_min_x(self, a, b):
              return a[0] - b[0]

          def compare_min_y(self, a, b):
              return a[1] - b[1]

#. **Bulk-Inserting Data**

   Bulk-insert data into the tree:

   .. code:: python

      tree.load([item1, item2, ...])

   Bulk insertion improves performance compared to inserting items individually,
   especially for clustered data.

#. **Search**

   Search for items within a given bounding box:

   .. code:: python

      result = tree.search({"minX": 40, "minY": 20, "maxX": 80, "maxY": 70})

   Returns items that intersect the specified bounding box.

#. **Collisions**

   Check if any items intersect the given bounding box:

   .. code:: python

      result = tree.collides({"minX": 40, "minY": 20, "maxX": 80, "maxY": 70})

   Returns `True` if there are any intersecting items, otherwise `False`.

#. **Export and Import**

   Export the tree data as JSON:

   .. code:: python

      tree_data = tree.to_json()

   Import data from a previously exported JSON:

   .. code:: python

      tree = RBush.from_json(tree_data)

   Ensure that the `max_entries` parameter is consistent between export and
   import operations.

****************************
 Engineering Infrastructure
****************************

-  **Version Control:** The project will be open-source and hosted on GitHub.
-  **Build System:** The build will be fully automated using `setuptools`.
-  **Testing:** Unit tests will be provided using `pytest` to ensure correctness
   and performance benchmarks.
-  **Documentation:** Full documentation will be available with usage examples
   and detailed API references.

**********
 Schedule
**********

#. **Week 1-2:** Research and analysis of `rbush` and `py-rbush`.
#. **Week 3-4:** Prototype the core R-Tree structure and implement insertion.
   Begin writing tests, and add deletion and search functionality.
#. **Week 5-6:** Add support for dynamic updates and optimize performance.
#. **Week 7:** Finalize documentation, and benchmark performance.
#. **Week 8:** Final review and presentation.

************
 References
************

-  `mourner/rbush <https://github.com/mourner/rbush>`_

-  `parietal-io/py-rbush <https://github.com/parietal-io/py-rbush>`_

-  `R-trees: a Dynamic Index Structure For Spatial Searching
   <http://www-db.deis.unibo.it/courses/SI-LS/papers/Gut84.pdf>`_

-  `The R*-tree: An Efficient and Robust Access Method for Points and
   Rectangles+
   <http://dbs.mathematik.uni-marburg.de/publications/myPapers/1990/BKSS90.pdf>`_

-  `OMT: Overlap Minimizing Top-down Bulk Loading Algorithm for R-tree
   <http://ftp.informatik.rwth-aachen.de/Publications/CEUR-WS/Vol-74/files/FORUM_18.pdf>`_

-  `Bulk Insertions into R-Trees Using the Small-Tree-Large-Tree Approach
   <http://www.cs.arizona.edu/~bkmoon/papers/dke06-bulk.pdf>`_

-  `R-Trees: Theory and Applications (book)
   <http://www.apress.com/9781852339777>`_
