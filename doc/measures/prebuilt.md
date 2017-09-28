---
currentSection: measures
currentSubsection: predef
currentItem:
---

#Prebuilt measures

NeuroSTR includes a huge library of prebuilt measures some new, others already presented in the scientific literature or implemented in existing neuroanatomy tools.

Prebuilt measures are organized in the same way as [Selectors](../selectors.html), by their input element type: all measure functions that take either a single node or a node set as input fall into the *Node* category. You can find more details about each measure by clicking on their name.

You might notice (and it seems odd) that there are very few Neurite and Neuron measures, but it is on purpose. Since we can use [Selectors](../selectors.html) and [Aggregators](../measures.html#aggregators) along with measures to create new measures, we focus on defining "low level" measures, that can be use to create "high level measures". Check the [Create a measure](../measures.html#create) to see a simple example of this.

### [Node Measures](#node)

- [X,Y,Z component](#node_component)
- [Radius, Diameter](#node_radius)
- [Centrifugal order](#node_order)
- [Distance to parent](#node_parent_length)
- [Compartment volume](#node_volume)
- [Compartment surface](#node_surface)
- [Compartment section area](#node_section)
- [Local Hillman taper rate](#node_hillman)
- [Local Burker taper rate](#node_burker)
- [Distance to root](#node_rootdist)
- [Distance to soma](#node_somadist)
- [Path length to root](#node_rootpath)
- [Number of descendants](#node_desccount)
- [Non-aligned minimum box volume](#node_boxvol)
- [Vector to parent](#node_parentvector)
- [Local bifurcation angle](#node_localbif)
- [Local elongation angle](#node_localelong)
- [Extreme angle](#node_extreme)
- [Local orientation](#node_localorientation)
- [In terminal branch](#node_interminalbranch)
- [Distance to closest segment](#node_distclosest)
- [Fractal dimension](#node_fractal)

---

### [Branch Measures](#branch)

- [Hillman taper rate](#branch_hillman)
- [Burker taper rate](#branch_burker)
- [Tortuosity](#branch_tortuosity)
- [Node count](#branch_size)
- [Branch index](#branch_index)
- [Centrifugal order](#branch_order)
- [Child diameter ratio](#branch_childdimratio)
- [Parent-Child diameter ratio](#branch_parentchildiamratio)
- [Partition asymmetry](#branch_partition)
- [Rall power fit](#branch_rall)
- [Pk](#branch_pk)
- [Hillman threshold](#branch_hillman_threshold)
- [Local bifurcation angle](#branch_localbif)
- [Remote bifurcation angle](#branch_remotebif)
- [Local bifurcation angle](#branch_localbif)
- [Remote bifurcation angle](#branch_remotebif)
- [Local tilt angle](#branch_localtilt)
- [Remote tilt angle](#branch_remotetilt)
- [Local plane vector](#branch_localplane)
- [Remote plane vector](#branch_remoteplane)
- [Local torque angle](#branch_localtorque)
- [Remote torque angle](#branch_remotetorque)
- [Length](#branch_length)
- [Intersects](#branch_intersects)

---

### [Neurite Measures](#neurite)

- [Root is soma](#neurite_rootsoma)

---

### [Neuron Measures](#neuron)

- [Has soma](#neuron_hassoma)
- [Neurite count](#neuron_neurite_count)
- [Neurite type count](#neuron_neurite_type_count)
- [Soma surface](#neuron_soma_surface)

---

### [Generic Measures](#generic)

- [Set size](#generic_setsize)

---

###[L-measure Measures](#lmeasure)

- [Soma surface](#lmeasure_somasurface)
- [Number of stems](#lmeasure_nstems)
- [Number of bifurcations](#lmeasure_nbifs)
- [Number of branches](#lmeasure_nbranches)
- [Number of terminal tips](#lmeasure_nterminals)
- [Width, Height and Depth](#lmeasure_width)
- [Diameter](#lmeasure_diameter)
- [Diameter power](#lmeasure_diameterpow)
- [Compartment length](#lmeasure_length)
- [Branch length](#lmeasure_branchlength)
- [Compartment surface](#lmeasure_surface)
- [Branch surface](#lmeasure_branchsurface)
- [Compartment section area](#lmeasure_section_area)
- [Compartment volume](#lmeasure_volume)
- [Branch volume](#lmeasure_branch_volume)
- [Distance to root](#lmeasure_rootdist)
- [Path length to root](#lmeasure_rootpath)
- [Branch centrifugal order](#lmeasure_branchorder)
- [Node terminal degree](#lmeasure_terminaldegree)
- [Branch terminal degree](#lmeasure_branch_terminaldegree)
- [Taper 1: Burker taper rate](#lmeasure_burker)
- [Taper 2: Hillman taper rate](#lmeasure_hillman)
- [Contraction](#lmeasure_contraction)
- [Fragmentation](#lmeasure_fragmentation)
- [Partition asymmetry](#lmeasure_partition_asymmetry)
- [Rall's power](#lmeasure_rall)
- [Pk fitted value](#lmeasure_pkfit)
- [Pk classic and squared](#lmeasure_pkclassic)
- [Local bifurcation amplitude](#lmeasure_local_bif)
- [Remote bifurcation amplitude](#lmeasure_remote_bif)
- [Local bifurcation tilt](#lmeasure_local_tilt)
- [Remote bifurcation tilt](#lmeasure_remote_tilt)
- [Local bifurcation torque](#lmeasure_local_torque)
- [Remote bifurcation_torque](#lmeasure_remote_torque)
- [Terminal bifurcation diameter](#lmeasure_terminaldiam)
- [Hillman threshold](#lmeasure_hillman_threshold)
- [Fractal dimension](#lmeasure_fractal_dimension)

--- 

###[L-measure comparison](#lmeasure-comparison)

---

# Node measures {#node}

### X, Y, Z components<a id="node_component"> </a>

**Function:** `node_x, node_y, node_z = [](const Node& n) -> float`

**Description:** Returns the x, y, z component of the given [Node] position.

**Output:** Real number.



---

### Radius, diameter<a id="node_radius"> </a>

**Function:** `node_radius,node_diameter = [](const Node& n) -> float`

**Description:** Returns the radius/diameter of the given [Node].

**Output:** Real number.

**Details:** The Hillman taper rate defined as the ratio of the difference between first and last node diameters and the first node diameter. If the branch's root exists, it is taken as the first node. If we assume non-decreasing diameters, the hillman taper rate should be non-negative. Note that it will throw an
exception for a [Branch] with no nodes.



---

### Centrifugal order<a id="node_order"> </a>

**Function:** `node_order = [](const Node& n) -> int`

**Description:** Returns the centrifugal order of the [Branch] that the [Node] belongs to.

**Output:** Integer. Centrifugal order

**Details:** See [Branch order](branch.html#order)



---

### Distance to parent<a id="node_parent_length"> </a>

**Function:** `node_length_to_parent,node_length_to_parent_border = [](const Node& n) -> float`

**Description:** Returns the euclidean distance between the given [Node] and its parent. the *border* variant subtract the radius of both nodes to the distance.

**Output:** Real Number.

**Details:** Please note that the border variant might return negative values if the sum of radius is greater than the distance



---

### Distance to root<a id="node_rootdist"> </a>

**Function:** `node_distance_to_root = [](const Node& n) -> float`

**Description:** Computes the euclidean distance between the given [Node] and the root of the [Neurite] that the node belongs to.

**Output:** Non negative real Number.

**Details:** If the [Neurite] doesn't have a root node, the distance is computed to its first [Node]



---

### Distance to soma<a id="node_somadist"> </a>

**Function:** `node_distance_to_soma = [](const Node& n) -> float`

**Description:** Computes the euclidean distance between the given [Node] and the closest [Soma] point in the neuron.

**Output:** Non negative real Number.

**Details:** If the [Neuron] doesn't have a [Soma], the the method returns the distance between the given node and the point (0,0,0).



---

### Path length to root<a id="node_rootpath"> </a>

**Function:** `node_path_to_root = [](const Node& n) -> float`

**Description:** Computes the length of the path from the given [Node] to the root of the [Neurite] that the node belongs to.

**Output:** Non negative real Number.



---


### Compartment volume<a id="node_volume"> </a>

**Function:** `node_volume = [](const Node& n) -> float`

**Description:** Computes the volume of the truncated cone from the given [Node] to its parent.

**Output:** Non negative real Number.

**Details:** The aforementioned cone has the radius of the parent at one end and the radius of the given [Node] at the other. If the parent of the given [Node] cannot be determined, it returns 0.



---

### Compartment surface<a id="node_surface"> </a>

**Function:** `node_compartment_surface = [](const Node& n) -> float`

**Description:** Computes the surface of the truncated open cone from the given [Node] to its parent.

**Output:** Non negative real Number.

**Details:** The aforementioned cone has the radius of the parent at one end and the radius of the given [Node] at the other. If the parent of the given [Node] cannot be determined, it returns 0.



---

### Compartment section area<a id="node_section"> </a>

**Function:** `node_compartment_section_area = [](const Node& n) -> float`

**Description:** Computes section area as the area of the circle with radius the average of the given [Node] and its parent radius.

**Output:** Non negative real Number.

**Details:** If the parent of the given [Node] cannot be determined, the circle radius is just the given node radius.



---

### Local Hillman taper rate<a id="node_hillman"> </a>

**Function:** `node_segment_taper_rate_hillman = [](const Node& n) -> float`

**Description:** Computes the Hillman taper rate between the given [Node] and its parent

**Output:** Non negative real Number.

**Details:** If the parent of the given [Node] cannot be determined, the taper rate is 0. The Hillman taper rate is given by:
`(parent.radius-node.radius)/parent.radius`



---

### Local Burker taper rate<a id="node_burker"> </a>

**Function:** `node_segment_taper_rate_burker = [](const Node& n) -> float`

**Description:** Computes the Burker taper rate between the given [Node] and its parent

**Output:** Non negative real Number.

**Details:** If the parent of the given [Node] cannot be determined, the taper rate is 0. The Burker taper rate is given by:
`(parent.radius-node.radius)/distance(parent,node)`



---

### Non axis aligned minimum box volume<a id="node_boxvol"> </a>

**Function:** `box_volume = [](const const_node_iterator& b,
                           const const_node_iterator& e) -> double`

**Description:** Computes the minimum box volume for the given [Node] set. The box is not restricted to be axis-aligned.

**Output:** Non negative real Number.

**Details:** The box volume is computed by applying a PCA over the position of the nodes, and then computing the axis-aligned box volume on the rotated positions.



---

### Vector to parent<a id="node_parentvector"> </a>

**Function:** `node_parent_vector = [](const Node& n) -> point_type`

**Description:** Computes the vector from the given [Node] to its parent.

**Output:** 3D Vector

**Details:** If the parent of the given [Node] cannot be determined, the method returns the null vector.



---

### Local bifurcation angle<a id="node_localbif"> </a>

**Function:** `node_local_bifurcation_angle = [](const Node& n) -> float`

**Description:** If the given node is a bifurcation, it returns the local bifurcation angle.

**Output:** Angle in radians [0,pi)

**Details:** If the node is not a bifurcation node it returns 0. See [Branch local bifurcation angle](branch.html#localbif)



---

### Local elongation angle<a id="node_localelong"> </a>

**Function:** `node_local_elongation_angle = [](const Node& n) -> float`

**Description:** If the given [Node] is an elongation, i.e. it only has one descendant, returns the oriented angle between the vector form the parent to the given [Node] and the vector from the [Node] to its descendant.

**Output:** Angle in radians

**Details:** If the node is not an elongation node it returns 0. The reference vector for 3D angle orientation is the [Neuron] up vector (by default it is the (0,0,1) vector)



---

### Local orientation<a id="node_localorientation"> </a>

**Function:** `node_local_orientation = [](const Node& n) -> std::pair<float, float>`

**Description:** It computes the values of azimuth and elevation for the given [Node] using the orthonormal basis span by the vector from the parent and the neuron up vector as reference.

**Output:** Pair of angles in radians (-pi,pi). Azimuth and elevation



---

### In terminal branch<a id="node_interminalbranch"> </a>

**Function:** `node_in_terminal_segment = [](const Node& n) -> bool`

**Description:** Returns true if the [Branch] that the node belongs to is a terminal branch

**Output:** Boolean value. True if the node's branch is terminal.



---

### Distance to closest segment<a id="node_distclosest"> </a>

**Function:** `segment_distance_to_closest = [](const Node& n) -> bool`

**Description:** Returns the minimum distance between the segment [parent,node] to any other segment in the neuron.

**Output:** Non negative value. If the parent of the given [Node] cannot be determined, the method returns the highest value representable in a float.



---

### Distance to closest segment<a id="node_distclosest"> </a>

**Function:** `segment_distance_to_closest = [](const Node& n) -> bool`

**Description:** Returns the minimum distance between the segment [parent,node] to any other segment in the neuron.

**Output:** Non negative value. If the parent of the given [Node] cannot be determined, the method returns the highest value representable in a float.



---

### Fractal dimension<a id="node_fractal"> </a>

**Function:** ` node_set_fractal_dim = [](const const_node_iterator& b,
                                     const const_node_iterator& e) -> float`

**Description:** Computes the fractal dimension of the given set of nodes (assuming that they are a sequence).


**Output:** Fractal dimension, real value between 1 (straight line) and 2 (random walk)

**Details:** See [L-measure fractal dimension documentation](http://cng.gmu.edu:8080/Lm/help/Fractal_Dim.htm).




---

# Branch measures {#branch}

### Hillman taper rate<a id="branch_hillman"> </a>

**Function:** `taper_rate_hillman = [](const Branch& b) -> float`

**Description:** Computes the Hillman taper rate for the given [Branch]

**Output:** real number. Hillman taper rate.

**Details:** The Hillman taper rate defined as the ratio of the difference between first and last node diameters and the first node diameter. If the branch's root exists, it is taken as the first node. If we assume non-decreasing diameters, the hillman taper rate should be non-negative. Note that it will throw an
exception for a [Branch] with no nodes.

`(first.diameter - last.diameter) / first.diameter`



---

### Burker taper rate <a id="branch_burker"> </a>

**Function:** `taper_rate_burker = [](const Branch& b) -> float`

**Description:** Computes the Burker taper rate for the given [Branch]

**Output:** real number. Burker taper rate.

**Details:** The Burker taper rate defined as the ratio of the difference between the first and last node diameters and the euclidean distance between these two same nodes. If the branch's root exists, it is taken as the first node. If we assume non-decreasing diameters, the hillman taper rate should be non-negative. Note that it will throw an exception for a [Branch] with no nodes.

`(first.diameter - last.diameter) / distance(first,last)`



---

### Tortuosity <a id="branch_tortuosity"> </a>

**Function:** `tortuosity = [](const Branch& b) -> float`

**Description:** Computes the branch tortuosity value.

**Output:** Non-negative real number. Greater or equal than 1.

**Details:** The tortuosity value is defined as the ratio of the total length of the branch and  the euclidean distance between the first and the last nodes. If the branch's root exists, it is taken as the first node.

`branch.length / distance(first,last)`



---

### Node count <a id="branch_size"> </a>

**Function:** `branch_size = [](const Branch &b) -> int`

**Description:** Returns the number of nodes in the [Branch].

**Output:** Non-negative integer

**Details:** This returns the number of nodes that are part of the Branch excluding the root. In our data model, the branch's root node belongs to the parent branch (or to the soma) and not to the branch itself.

---

### Branch index <a id="branch_index"> </a>

**Function:** `branch_index = [](const Branch &b) -> unsigned int`

**Description:** Returns the index of the given branch as daughter of the parent branch.

**Output:** Non-negative integer

**Details:** This returns 0 for the first branch, 1 for the second and so on. If the [Neurite] has been sorted, the first and last branches are ordered by they azimuth, in other words the rightmost and leftmost branches correspond to the first and last position respectively.

---

### Centrifugal order <a id="branch_order"> </a>

**Function:** `branch_order = [](const Branch &b) -> int`

**Description:** Returns the centrifugal order of the given [Branch]

**Output:** Non-negative integer

**Details:** Branch orders counts the number of bifurcations in the path from the given [Branch] to the root of the [Neurite]. That is, the root [Branch] has a centrifugal order of 0, it's daughters have a centrifugal order of 1, and so on.



---

### Child diameter ratio <a id="branch_childdimratio"> </a>

**Function:** `child_diam_ratio = [](const Branch& b) -> float`

**Description:** Returns the child-diameter ratio of the daughters of the given [[Branch], the ratio of the daughter branches first node's diameters.

**Output:** Real number

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always return 0.

` branch.child[0].first.diameter /  branch.child[1].first.diameter `

---

### Parent-Child diameter ratio <a id="branch_childdimratio"> </a>

**Function:** `parent_child_diam_ratio = [](const Branch& b) -> std::pair<float,float>`

**Description:** Returns the ratio between the diameter of the last node of the given branch and the first nodes of the daughter branches.

**Output:** Real number pair

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always return the pair (0,0).

` (branch.child[0].first.diameter/branch.last.diameter, branch.child[1].first.diameter/branch.last.diameter) `


---

### Partition asymmetry <a id="branch_partition"> </a>

**Function:** `partition_asymmetry = [](const Branch& b) -> float`

**Description:** The partition asymmetry first computes the number of terminal points in the left/right subtrees, *n1* and *n2* respectively. Then computes the following quantity as the partition asymmetry value:

` |n1-n2| / (n1 + n2 - 2)|`

**Output:** Non negative real number

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always returns -1.



---

### Rall's power fit <a id="branch_rall"> </a>

**Factory function:** `auto rall_power_fit_factory(float min = 0 , float max = 5)`

**Function:** `(const Branch &b) -> float `

**Description:** Computes the best value for the parameter *r* in the range [*min*,*max*] that minimizes the following quantity:

`(branch.diameter^r - branch.child[0].diameter^r - branch.child[1].diameter^r)^2`

**Output:** Real number - best fit value

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always returns -1.

---

### Pk measure <a id="branch_pk"> </a>

**Factory function:** `auto pk_factory(float r)`

**Function:** `(const Branch &b) -> float`

**Description:** Given the parameter *r*, computes the quantity:

`(branch.child[0].diameter^r - branch.child[1].diameter^r)/branch.diameter^r`

**Output:** Real number

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always returns -1.

**Note:** `pk_fit_factory(float min = 0 , float max = 5)` just applies this same measure where *r* is computed using [Rall's power fit](#rall).

---

### Hillman threshold <a id="branch_hillman_threshold"> </a>

**Function:** `hillman_threshold = [](const Branch &b) -> float`

**Description:** Computes the Hillman threshold value for the given [Branch] bifurcation. The Hillman threshold is the weighted sum of parent and daugther diameters (0.5,0.25,0.25). Hillman threshold only applies to pre-terminal branches (i.e to terminal bifurcation nodes).

`0.25*(branch.child[0].diameter + branch.child[1].diameter) + 0.5*branch.diameter`

**Output:** Real number

**Details:** If the number of descendants of the given [Branch] is not equal to 2 or it is not a pre-terminal branch the measure returns -1.

---

### Local bifurcation angle <a id="branch_localbif"> </a>

**Function:** `local_bifurcation_angle = [](const Branch &b) -> float`

**Description:** Computes the bifurcation amplitude, measured as the shortest planar angle between the vectors from the bifurcation node (the last node of the given branch) to the first nodes of the daughter branches.

**Output:** Real number. Angle in radians [0,pi]

**Details:** If the number of descendants of the given [Branch] is not equal to 2 it returns -1. NAN values might appear if null segments are present.



---

### Remote bifurcation angle <a id="branch_remotebif"> </a>

**Function:** `remote_bifurcation_angle = [](const Branch &b) -> float`

**Description:** Computes the bifurcation amplitude, measured as the shortest planar angle between the vectors from the bifurcation node (the last node of the given branch) to the last nodes of the daughter branches.

**Output:** Real number. Angle in radians [0,pi]

**Details:** If the number of descendants of the given [Branch] is not equal to 2 it returns -1. NAN values might appear if null segments are present.



---

### Local tilt angle <a id="branch_localtilt"> </a>

**Function:** `local_tilt_angle = [](const Branch &b) -> float`

**Description:** Computes the tilt angle at the last node bifurcation point. Tilt angle is the smallest angle between the branch director vector and the vectors form the bifurcation point to the first node of the daughter branches.

**Output:** Real number. Angle in radians [0,pi]

**Details:** If the number of descendants of the given [Branch] is not equal to 2 it returns -1. NAN values might appear if null segments are present.



---

### Remote tilt angle <a id="branch_remotetilt"> </a>

**Function:** `remote_tilt_angle = [](const Branch &b) -> float`

**Description:** Computes the tilt angle at the last node bifurcation point. Tilt angle is the smallest angle between the branch director vector and the vectors form the bifurcation point to the last node of the daughter branches.

**Output:** Real number. Angle in radians [0,pi]

**Details:** If the number of descendants of the given [Branch] is not equal to 2 it returns -1. NAN values might appear if null segments are present.



---

### Local plane vector <a id="branch_localplane"> </a>

**Function:** `local_plane_vector = [](const Branch &b) -> point_type `

**Description:** Computes the normal vector to the plane defined by the vectors from the root to the first node of the daughter branches.

**Output:** Plane normal vector

**Details:** If the branch don't have a sibling branch, it returns the null vector.



---

### Remote plane vector <a id="branch_remoteplane"> </a>

**Function:** `remote_plane_vector = [](const Branch &b) -> point_type `

**Description:** Computes the normal vector to the plane defined by the vectors from the branch root and the last node of the daughter branches.

**Output:** Plane normal vector

**Details:** If the branch don't have a sibling branch, it returns the null vector.



---

### Local torque angle <a id="branch_localtorque"> </a>

**Function:** `local_plane_vector = [](const Branch &b) -> point_type `

**Description:** Computes the angle between the branch local plane vector  and the daughter branches plane vector.

**Output:** Angle in radians [0,pi)]

**Details:** If the number of daughter branches is not equal to 2, returns -1. NAN values might appear if the tree is malformed. See [Local plane vector](#localplane) function.



---

### Remote torque angle <a id="branch_remotetorque"> </a>

**Function:** `local_plane_vector = [](const Branch &b) -> point_type `

**Description:** Computes the angle between the branch local plane vector  and the daughter branches plane vector.

**Output:** Angle in radians [0,pi)]

**Details:** If the number of daughter branches is not equal to 2, returns -1. NAN values might appear if the tree is malformed. See [Local plane vector](#localplane) function.



---

### Length <a id="branch_length"> </a>

**Function:** `branch_length = [](const Branch &b) -> float `

**Description:** Computes the branch total length.

**Output:** Non negative real number - branch length.



---

### Intersects <a id="branch_intersects"></a>

**Factory:**  `branch_intersects_factory(bool ignore_radius = false)`

**Function:** `(const Branch &b ) -> std::string`

**Description:** Checks if the given [Branch] intersects with any other [Branch] in the [Neuron], and returns its id in that case. If *ignore_radius* flag is set to true, the radius of each compartment is taken into account when checking intersections.

**Output:** Id of the intersecting [branch] + "@ Neurite: id". An empty string otherwise.

**Details:** The function pre-checks the possible intersection by checking the bounding box of each pair of [Branches]. If the boxes intersect, then computes the branch-branch distance (that is, the segment-segment distance for each pair of segments).



---

# Neurite measures {#neurite}

### Root is soma <a id="neurite_rootsoma"> </a>

**Function:** `root_is_soma`

**Description:** Returns true if the [Neurite] is attached to the soma

**Output:** Boolean flag. True if the [Neurite] root is a soma point (or it is inside the soma)

**Details:** `root_is_soma` measure just calls the `Neurite.root_is_soma()` member function which checks if the root branch of the neurite has a root node.

---

# Neuron measures {#neuron}

### Neuron has soma <a id="neuron_hassoma"> </a>

**Function:** `has_soma`

**Description:** Returns true if the neuron has at least one soma node.

**Output:** Boolean flag. True if the [Soma] is defined in the [Neuron]

**Details:** `has_soma` measure just calls the `Neuron.has_soma()` member function which checks if the number of soma points in the neuron is greater than 0.

---

### Neurite count <a id="neuron_neurite_count"> </a>

**Function:** `neuron_neurite_count`

**Description:** Returns the number of [Neurite]s in the [Neuron].

**Output:** Non-negative integer value. The number of [Neurite]s (of any type) in the [Neuron].

---

### Neurite type count <a id="neuron_neurite__type_count"> </a>

**Function:** `neuron_type_counter` (factory method)

**Parameters:** **type** - *NeuriteType* - Neurite type.

**Description:** Returns the number of [Neurite]s in the [Neuron] of certain type.

**Instances:**
  - `neuron_dendrite_counter` Counts the number of dendrites in the [Neuron]
  - `neuron_axon_counter` Counts the number of axons in the [Neuron]
  - `neuron_apical_counter` Counts the number of apical dendrites in the [Neuron]

**Output:** Non-negative integer value. The number of [Neurite]s of type *type* in the [Neuron].

---

### Soma surface area <a id="neuron_soma_surface"> </a>

**Function:** `soma_surface`

**Description:** Returns the [Soma] surface area under spherical shape assumption.

**Output:** Non-negative real value. The computed soma surface area.

**Details:** If there are several soma points, the computed area is the surface of the sphere centered at the soma barycenter with radius the average distance from the barycenter to the external border of the sphere. Otherwise, for a sigle-point [Soma], the sphere surface area is computed.

---

# L-measure measures {#lmeasure}

### Soma surface <a id="lmeasure_somasurface"> </a>

**Function:** `soma_surface`

**Description:** Computes the soma surface area under spherical shape assumption.

**Output:** Non-negative real number. Soma surface area. Zero if the neuron don't have soma points.

**Details:** If there are several soma points, the computed area is the surface of the sphere centered at the soma barycenter with radius the average distance from the barycenter to the external border of the sphere. See [soma_surface](neuron.html#soma_surface) measure.



---

### Number of stems <a id="lmeasure_nstems"> </a>

**Function:** `n_stems`

**Description:** Returns the number of stems (what we call neurites) in the neuron.

**Output:** Non-negative integer. Number of stems/neurites.

**Details:**  See [neuron_neurite_count](neuron.html#neurite_count) measure.

---

### Number of bifurcations <a id="lmeasure_nbifs"> </a>

**Function:** `n_bifs`

**Description:** Returns the number of bifurcation points in the neuron.

**Output:** Non-negative integer. Number of bifurcations.

---

### Number of branches <a id="lmeasure_nbranches"> </a>

**Function:** `n_branch`

**Description:** Counts the number of branches in the neuron.

**Output:** Non-negative integer. Number of branches.

---

### Number of terminal tips <a id="lmeasure_nterminals"> </a>

**Function:** `n_tips`

**Description:** Counts the number of terminal tips in the neuron.

**Output:** Non-negative integer. Terminal tips count.

---

### Width, Height and Depth <a id="lmeasure_width"> </a>

**Function:** `width`, `height`, `depth`

**Description:** Computes the neuron [range length](../measures.html#range) for the x,y and z axis respectively.

**Output:** Non-negative real number.



---

### Diameter <a id="lmeasure_diameter"> </a>

**Function:** `diameter`

**Description:** Computes the [Summary] statistics for the [Node] diameter value.

**Output:** Diameter [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node diameter](node.html#diameter) measure.

---

### Diameter power <a id="lmeasure_diameterpow"> </a>

**Function:** `diameter_pow`

**Description:** Computes the [Summary] statistics for the [Node] diameter value power to 1.5.

**Output:** Diameter power [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node diameter pow](node.html#diameterpow) measure.

---

### Length <a id="lmeasure_length"> </a>

**Function:** `length`

**Description:** Computes the [Summary] statistics for compartment lengths.

**Output:** Compartment length [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node length to parent](node.html#length) measure.



---

### Branch length <a id="lmeasure_branchlength"> </a>

**Function:** `branch_pathlength`

**Description:** Computes the [Summary] statistics for branch lengths.

**Output:** Branch length [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Branch length](branch.html#length) measure.



---

### Surface <a id="lmeasure_surface"> </a>

**Function:** `surface`

**Description:** Computes the [Summary] statistics for compartment surface area.

**Output:** Compartment surface [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node compartment surface](node.html#surface) measure.



---

### Branch surface <a id="lmeasure_branchsurface"> </a>

**Function:** `branch_surface`

**Description:** Computes the [Summary] statistics for branch surface area.

**Output:** Branch surface area [Summary] stats (sum, max, min, median, mean and sd).

**Details:** Branch surface is computed as the sum of compartment surfaces. See [Node compartment surface](node.html#surface) measure.



---

### Compartment section area <a id="lmeasure_section_area"> </a>

**Function:** `section_area`

**Description:** Computes the [Summary] statistics for compartment section area.

**Output:** Compartment section area [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node compartment section area](node.html#section_area) measure.



---


### Compartment volume <a id="lmeasure_volume"> </a>

**Function:** `volume`

**Description:** Computes the [Summary] statistics for compartment volume.

**Output:** Compartment volume [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node compartment volume](node.html#volume) measure.



---

### Branch Volume <a id="lmeasure_branch_volume"> </a>

**Function:** `branch_volume`

**Description:** Computes the [Summary] statistics for branch compartment volume.

**Output:** Branch volume [Summary] stats (sum, max, min, median, mean and sd).

**Details:** Branch volume is computed as the sum of compartment surfaces. See [Node compartment volume](node.html#volume) measure.



---

### Distance to root <a id="lmeasure_rootdist"> </a>

**Function:** `euc_distance`

**Description:** Computes the [Summary] statistics for the euclidean distance of each [Node] to the [Neurite] root.

**Output:** Distance [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node root distance](node.html#rootdist) measure.



---

### Path length to root <a id="lmeasure_rootpath"> </a>

**Function:** `path_distance`

**Description:** Computes the [Summary] statistics for the path distance of each [Node] to the [Neurite] root.

**Output:** Distance [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node path distance](node.html#rootpath) measure.



---

### Branch centrifugal order <a id="lmeasure_branchorder"> </a>

**Function:** `branch_order`

**Description:** Computes the [Summary] statistics for the branch centrifugal order of each [Branch] in the neuron.

**Output:** Centrifugal order [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Branch centrifugal order](branch.html#order) measure.



---

### Node Terminal degree <a id="lmeasure_terminaldegree"> </a>

**Function:** `terminal_degree`

**Description:** Computes the [Summary] statistics for the terminal degree centrifugal order of each [Node] in the neuron. The terminal degree is the number of terminal tips in the subtree of the given [Node].

**Output:** Terminal degree [Summary] stats (sum, max, min, median, mean and sd).



---

### Branch Terminal degree <a id="lmeasure_branch_terminaldegree"> </a>

**Function:** `branch_terminal_degree`

**Description:** Computes the [Summary] statistics for the terminal degree centrifugal order of each [Branch] in the neuron. The terminal degree is the number of terminal tips in the subtree of the given [Branch].

**Output:** Terminal degree [Summary] stats (sum, max, min, median, mean and sd).



---


### Taper 1: Burker taper rate <a id="lmeasure_burker"> </a>

**Function:** `taper_1`

**Description:** Computes the [Summary] statistics for the branch Burker taper rate [Branch] in the neuron for every [Branch] in the [Neuron].

**Output:** Taper rate [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Burker taper rate](branch.html#burker) measure.



---

### Taper 2: Hillman taper rate <a id="lmeasure_hillman"> </a>

**Function:** `taper_2`

**Description:** Computes the [Summary] statistics for the branch Hillman taper rate [Branch] in the neuron for every [Branch] in the [Neuron].

**Output:** Taper rate [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Hillman taper rate](branch.html#hillman) measure.



---

### Contraction <a id="lmeasure_contraction"> </a>

**Function:** `contraction`

**Description:** Computes the [Summary] statistics for the [Branch] contraction, i.e. its tortuosity for every [Branch] in the [Neuron].

**Output:** Contraction [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Tortuosity](branch.html#tortuosity) measure.



---

### Fragmentation <a id="lmeasure_fragmentation"> </a>

**Function:** `fragmentation`

**Description:** Computes the [Summary] statistics for the [Branch] fragmentation, i.e. its number of nodes for every [Branch] in the [Neuron].

**Output:** Fragmentation [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Branch size](branch.html#size) measure.



---

### Daughter ratio <a id="lmeasure_daughter_ratio"> </a>

**Function:** `daughter_ratio`

**Description:** Computes the [Summary] statistics for the [Branch] daughter ratio, i.e. the ratio of the diameters of its daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Daughter ratio [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Child diameter ratio](branch.html#chid_diam) measure.



---

### Partition asymmetry <a id="lmeasure_partition_asymmetry"> </a>

**Function:** `partition_asymmetry`

**Description:** Computes the [Summary] statistics for the [Branch] partition asymmetry value, i.e. the ratio between the number of terminals in the left-subtree and the right-subtree , for every non-terminal [Branch] in the [Neuron].

**Output:** Partition asymmetry [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Partition asymmetry](branch.html#partition_asymmetry) measure.



---

### Rall's power <a id="lmeasure_rall"> </a>

**Function:** `rall_power`

**Description:** Computes the [Summary] statistics for the Rall's power fitted value for every non-terminal [Branch] in the [Neuron].

**Output:** Rall's power fitted value [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Rall's power fit ](branch.html#rall) measure.



---

### Pk fitted value <a id="lmeasure_pkfit"> </a>

**Function:** `pk`

**Description:** Computes the [Summary] statistics for the Pk with factor given by the fitted value returned by the [Rall's power fit ](branch.html#rall) measure for every non-terminal [Branch] in the [Neuron].

**Output:** Pk value [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Rall's power fit ](branch.html#rall) and [Pk factory](branch.html#pk) measures.



---

### Pk classic and squared <a id="lmeasure_pkclassic"> </a>

**Function:** `pk_classic`, `pk2`

**Description:** Computes the [Summary] statistics for the Pk with factors 1.5 and 2 respectively for every non-terminal [Branch] in the [Neuron].

**Output:** Pk value [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Pk factory](branch.html#pk) measure.



---

### Local bifurcation amplitude <a id="lmeasure_local_bif"> </a>

**Function:** `bif_ampl_local`

**Description:** Computes the [Summary] statistics for the bifurcation angle computed w.r.t. the  firs node in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Bifurcation amplitude (angle in radians) [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Local bifurcation angle](branch.html#local_bif) measure.



---

### Remote bifurcation amplitude <a id="lmeasure_remote_bif"> </a>

**Function:** `bif_ampl_remote`

**Description:** Computes the [Summary] statistics for the bifurcation angle computed w.r.t. the last nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Bifurcation amplitude (angle in radians) [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Remote bifurcation angle](branch.html#remote_bif) measure.



---

### Local bifurcation tilt <a id="lmeasure_local_tilt"> </a>

**Function:** `bif_tilt_local`

**Description:** Computes the [Summary] statistics for the bifurcation tilt angle computed w.r.t. the first nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Tilt angle in radians [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Local tilt angle](branch.html#local_tilt) measure.



---

### Remote bifurcation tilt <a id="lmeasure_remote_tilt"> </a>

**Function:** `bif_tilt_remote`

**Description:** Computes the [Summary] statistics for the bifurcation tilt angle computed w.r.t. the last nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Bifurcation tilt angle in radians [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Remote tilt angle](branch.html#remote_tilt) measure.



---

### Local bifurcation torque <a id="lmeasure_local_torque"> </a>

**Function:** `bif_torque_local`

**Description:** Computes the [Summary] statistics for the bifurcation torque angle computed w.r.t. the first nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Torque angle in radians [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Local torque angle](branch.html#local_torque) measure.



---

### Remote bifurcation tilt <a id="lmeasure_remote_torque"> </a>

**Function:** `bif_torque_remote`

**Description:** Computes the [Summary] statistics for the bifurcation torque angle computed w.r.t. the last nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Bifurcation torque angle in radians [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Remote torque angle](branch.html#remote_torque) measure.



---

### Terminal bifurcation diameter <a id="lmeasure_terminaldiam"> </a>

**Function:** `last_parent_diam`

**Description:** Computes the [Summary] statistics for the diameter of every terminal bifurcation (see [Terminal bifurcation selector](../selectors/neurite.html#terminal_bif)) [Node] in the [Neuron].

**Output:** [Node] diameter [Summary] stats (sum, max, min, median, mean and sd).



---

### Hillman threshold <a id="lmeasure_hillman_threshold"> </a>

**Function:** `hillman_threshold`

**Description:** Computes the [Summary] statistics for the Hillman threshold value (see [Hillman threshold measure](branch.html#hillman_threshold)) for every pre-terminal [Branch] in the [Neuron].

**Output:** Hillman threshold value [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Hillman threshold](branch.html#hillman_threshold) measure.



---

### Fractal dimension <a id="lmeasure_fractal_dimension"> </a>

**Function:** `fractal_dim`

**Description:** Computes the [Summary] statistics for the Fractal dimension of every [Branch] in the [Neuron].

**Output:** Fractal dimension [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Fractal dimension](node.html#fractal_dimension) measure.



---

# L-measure comparison {#lmeasure-comparison} 
This compares 17 L-Measure analyses to the corresponding ones computed with NeuroSTR. The table shows the mean absolute difference and correlation across on 219 interneurons (the names correspond to the L-Measure [ones](http://cng.gmu.edu:8080/Lm/help/index.htm)). Measures with an absolute correlation &lt; 0.90 are marked as different.

For most of the measures, NeuroSTR produces identical or very similar results as L-Measure. Differing measures include fractal dimension, and torque and tilt angles. As far as tilt angles, the definition used by NeuroSTR seems to differ form the one used by L-Measure, as NeuroSTR produces significantly smaller tilt angles than L-Measure. PathDistance\_min, for example, differs because L-Measure seems to be computing the distance to soma centroid, and not to the point of insertion.

|                           |  abs difference| correlation         | different |
|---------------------------|---------------:|:--------------------|:----------|
| Partition\_asymmetry\_min |    0.000000e+00|                     | X         |
| Partition\_asymmetry\_avg |    2.071100e-03| 0.996100276045597   |           |
| Partition\_asymmetry\_std |    7.656900e-03| 0.907571434440884   |           |
| Partition\_asymmetry\_max |    0.000000e+00|                     | X         |
| Partition\_asymmetry\_sum |    1.200151e+00| 0.999083527492007   |           |
| PathDistance\_min         |    2.229969e+01|                     | X         |
| PathDistance\_avg         |    2.001725e+01| 0.991257984928102   |           |
| PathDistance\_std         |    6.976029e-01| 0.999907974623442   |           |
| PathDistance\_max         |    2.230283e+01| 0.998855843934241   |           |
| PathDistance\_sum         |    2.816866e+05| 0.99922990822852    |           |
| Fractal\_Dim\_min         |    3.160400e-03| 0.0206401479615145  | X         |
| Fractal\_Dim\_avg         |    1.236650e-02| 0.410283477603493   | X         |
| Fractal\_Dim\_std         |    1.034990e-02| 0.785722143517184   | X         |
| Fractal\_Dim\_max         |    1.070795e-01| 0.581901774924155   | X         |
| Fractal\_Dim\_sum         |    3.844008e+01| 0.979548213398901   |           |
| Branch\_pathlength\_min   |    5.446470e-01| 0.708340638736405   | X         |
| Branch\_pathlength\_avg   |    2.324426e-01| 0.999865047347315   |           |
| Branch\_pathlength\_std   |    6.052271e-01| 0.999786069805852   |           |
| Branch\_pathlength\_max   |    2.728793e-01| 0.999998964420045   |           |
| Branch\_pathlength\_sum   |    6.211538e+01| 0.999984856890684   |           |
| Contraction\_min          |    1.197640e-02| 0.977796130877257   |           |
| Contraction\_avg          |    1.021690e-02| 0.97321722383137    |           |
| Contraction\_std          |    4.501100e-03| 0.986251109426759   |           |
| Contraction\_max          |    4.993800e-03| 0.477191281053891   | X         |
| Contraction\_sum          |    3.084918e+00| 0.999757237623208   |           |
| EucDistance\_min          |    1.349360e+00| 0.988231220230445   |           |
| EucDistance\_avg          |    1.823260e+00| 0.999863574895347   |           |
| EucDistance\_std          |    7.403589e-01| 0.999898926332369   |           |
| EucDistance\_max          |    1.728592e+00| 0.999977217689101   |           |
| EucDistance\_sum          |    6.910249e+04| 0.99979683332156    |           |
| Length\_min               |    7.839590e-02| 0.8273460933385     | X         |
| Length\_avg               |    2.148606e-01| 0.998762273938329   |           |
| Length\_std               |    9.202530e-02| 0.993449609351132   |           |
| Length\_max               |    9.703300e-03| 0.999994727485554   |           |
| Length\_sum               |    6.369182e+01| 0.999984572724984   |           |
| Branch\_Order\_min        |    0.000000e+00|                     | X         |
| Branch\_Order\_avg        |    4.141417e-01| 0.97069802899676    |           |
| Branch\_Order\_std        |    2.137369e-01| 0.986986520821249   |           |
| Branch\_Order\_max        |    1.050228e-01| 0.998969212978679   |           |
| Branch\_Order\_sum        |    7.898101e+04| 0.673317766087749   | X         |
| Bif\_torque\_remote\_min  |    1.680708e+00| 0.635288359081423   | X         |
| Bif\_torque\_remote\_avg  |    4.272049e+01| 0.0404260940147207  | X         |
| Bif\_torque\_remote\_std  |    2.587815e+01| 0.108875636009112   | X         |
| Bif\_torque\_remote\_max  |    8.639793e+01| 0.218415684125337   | X         |
| Bif\_torque\_remote\_sum  |    6.806988e+03| 0.987680908722341   |           |
| Bif\_ampl\_remote\_min    |    6.683836e-01| 0.948920995214031   |           |
| Bif\_ampl\_remote\_avg    |    1.783731e+00| 0.989652715694246   |           |
| Bif\_ampl\_remote\_std    |    1.164879e+00| 0.9882689021774     |           |
| Bif\_ampl\_remote\_max    |    2.317163e+00| 0.890147511797299   | X         |
| Bif\_ampl\_remote\_sum    |    2.761723e+02| 0.998837863523185   |           |
| Bif\_tilt\_remote\_min    |    1.949893e+01| 0.134134833363253   | X         |
| Bif\_tilt\_remote\_avg    |    8.376762e+01| -0.473003077459945  | X         |
| Bif\_tilt\_remote\_std    |    1.209846e+01| 0.390476990326114   | X         |
| Bif\_tilt\_remote\_max    |    7.490481e+01| -0.0163546264278658 | X         |
| Bif\_tilt\_remote\_sum    |    1.336028e+04| 0.926173733334739   |           |
| Bif\_torque\_local\_min   |    5.472301e+00| -0.0414314037376772 | X         |
| Bif\_torque\_local\_avg   |    5.194249e+01| 0.0278312934989923  | X         |
| Bif\_torque\_local\_std   |    2.301028e+01| 0.0592057638788328  | X         |
| Bif\_torque\_local\_max   |    8.810073e+01| 0.0752406964607671  | X         |
| Bif\_torque\_local\_sum   |    8.028468e+03| 0.00506177323461263 | X         |
| Bif\_tilt\_local\_min     |    1.237795e+02| -0.0473856576332252 | X         |
| Bif\_tilt\_local\_avg     |    1.422379e+02| -0.185367299328921  | X         |
| Bif\_tilt\_local\_std     |    1.475418e+01| 0.111155845900793   | X         |
| Bif\_tilt\_local\_max     |    7.678624e+01|                     | X         |
| Bif\_tilt\_local\_sum     |    1.611524e+04| 0.955729654829031   |           |
| N\_bifs\_sum              |    1.574247e+02| 0.999960965731527   |           |


[Node]: ../data_model.html#node
[Branch]: ../data_model.html#branch
[Neurite]: ../data_model.html#neurite
[Neuron]: ../data_model.html#neuron
[Summary]: (../measures.html#summary)
