/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file AABBtree.hxx
 * @author Matteo Ragni (info@ragni.me)
 *
 * @copyright Copyright (c) 2022 Matteo Ragni
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Based on the work of:
 * Enrico Bertolazzi http://ebertolazzi.github.io/Clothoids/
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include <memory>
#include <vector>
#include <utility>

#include "Types.hxx"

namespace G2lib {

  using std::pair;
  using std::vector;

  using std::make_shared;
  using std::shared_ptr;

  class AABBtree;

  /*\
   |   ____  ____
   |  | __ )| __ )  _____  __
   |  |  _ \|  _ \ / _ \ \/ /
   |  | |_) | |_) | (_) >  <
   |  |____/|____/ \___/_/\_\
  \*/
  //!
  //! Class to manipulate bounding box
  //!
  class BBox {
   public:
    typedef shared_ptr<BBox const> PtrBBox;

   private:
    real_type m_bbox[4]{0.0, 0.0, 0.0, 0.0}; //!< bounds of the box: [xmin, ymin, xmax, ymax]
    int_type  m_id;    //!< id of the bbox
    int_type  m_ipos;  //!< rank of the bounding box used in external algorithms

    BBox();

    BBox(BBox const &) = default;
    BBox(BBox &&)      = default;

   public:
    //!
    //! Construct a bounding box with additional information
    //!
    //! \param[in] xmin x-minimimum box coordinate
    //! \param[in] ymin y-minimimum box coordinate
    //! \param[in] xmax x-maximum box coordinate
    //! \param[in] ymax y-maximum box coordinate
    //! \param[in] id   identifier of the box
    //! \param[in] ipos ranking position of the box
    //!
    BBox(real_type xmin, real_type ymin, real_type xmax, real_type ymax, int_type id, int_type ipos) {
      x_min() = xmin;
      y_min() = ymin;
      x_max() = xmax;
      y_max() = ymax;
      m_id   = id;
      m_ipos = ipos;
    }

    //!
    //! Build a buonding box that cover a list of bounding box
    //!
    //! \param[in] bboxes list of bounding box
    //! \param[in] id     identifier of the box
    //! \param[in] ipos   ranking position of the box
    //!
    BBox(vector<PtrBBox> const & bboxes, int_type id, int_type ipos) {
      m_id   = id;
      m_ipos = ipos;
      this->join(bboxes);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    real_type const * bbox() { return m_bbox; }
    real_type const * bbox_min() { return m_bbox; }
    real_type const * bbox_max() { return m_bbox + 2; }

    // Deprecated: retrocompatibility
    real_type Xmin() const { return m_bbox[0]; }  //!< x-minimum coordinate of the bbox
    real_type Ymin() const { return m_bbox[1]; }  //!< y-minimum coordinate of the bbox
    real_type Xmax() const { return m_bbox[2]; }  //!< x-maximum coordinate of the bbox
    real_type Ymax() const { return m_bbox[3]; }  //!< y-maximum coordinate of the bbox

    // Deprecated: retrocompatibility
    real_type & Xmin() { return m_bbox[0]; }  //!< x-minimum coordinate of the bbox
    real_type & Ymin() { return m_bbox[1]; }  //!< y-minimum coordinate of the bbox
    real_type & Xmax() { return m_bbox[2]; }  //!< x-maximum coordinate of the bbox
    real_type & Ymax() { return m_bbox[3]; }  //!< y-maximum coordinate of the bbox

    real_type x_min() const { return m_bbox[0]; }  //!< x-minimum coordinate of the bbox
    real_type y_min() const { return m_bbox[1]; }  //!< y-minimum coordinate of the bbox
    real_type x_max() const { return m_bbox[2]; }  //!< x-maximum coordinate of the bbox
    real_type y_max() const { return m_bbox[3]; }  //!< y-maximum coordinate of the bbox

    real_type & x_min() { return m_bbox[0]; }  //!< x-minimum coordinate of the bbox
    real_type & y_min() { return m_bbox[1]; }  //!< y-minimum coordinate of the bbox
    real_type & x_max() { return m_bbox[2]; }  //!< x-maximum coordinate of the bbox
    real_type & y_max() { return m_bbox[3]; }  //!< y-maximum coordinate of the bbox

    int_type const & Id() const { return m_id; }      //!< return BBOX id
    int_type const & Ipos() const { return m_ipos; }  //!< return BBOX position

    //!
    //! copy a bbox
    //!
    BBox const & operator=(BBox const & rhs);

    //!
    //! detect if two bbox collide
    //!
    bool collision(BBox const & box) const;

    //!
    //! Build bbox for a list of bbox
    //!
    void join(vector<PtrBBox> const & bboxes);

    //!
    //! distance of the point `(x,y)` to the bbox
    //!
    real_type distance(real_type x, real_type y) const;

    //!
    //! Maximum distance of the point `(x,y)` to the point of bbox
    //!
    real_type maxDistance(real_type x, real_type y) const;

    //!
    //! Pretty print a bbox
    //!
    void print(ostream_type & stream) const;

    friend class AABBtree;
  };

  //!
  //! Pretty print a bbox
  //!
  inline ostream_type & operator<<(ostream_type & stream, BBox const & bb) {
    bb.print(stream);
    return stream;
  }

  /*\
   |      _        _    ____  ____  _
   |     / \      / \  | __ )| __ )| |_ _ __ ___  ___
   |    / _ \    / _ \ |  _ \|  _ \| __| '__/ _ \/ _ \
   |   / ___ \  / ___ \| |_) | |_) | |_| | |  __/  __/
   |  /_/   \_\/_/   \_\____/|____/ \__|_|  \___|\___|
  \*/
  //!
  //! Class to build and manage an AABB tree (Axis-Aligned Bounding Box Trees)
  //!
  //! The class provides 2-dimensional aabb-tree construction and search
  //! for arbitrary collections of spatial objects.
  //! These tree-based indexing structures are useful when seeking to implement
  //! efficient spatial queries, reducing the complexity of intersection tests
  //! between collections of objects.
  //!
  //!
  class AABBtree {
   public:
    using PtrBBox = shared_ptr<BBox const>;
    using PtrAABB = shared_ptr<AABBtree>;
    using PairPtrBBox = pair<PtrBBox, PtrBBox>;
    using VecPtrBBox = vector<PtrBBox>;
    using VecPairPtrBBox = vector<PairPtrBBox>;

   private:
    // bbox of the tree
    PtrBBox         pBBox;
    vector<PtrAABB> children;

    AABBtree(AABBtree const & tree);

    //!
    //! Compute the minimum of the maximum distance
    //! between a point and the bbox contained in the `AABBtree`
    //!
    //! \param[in] x      x-coordinate of the point
    //! \param[in] y      y-coordinate of the point
    //! \param[in] tree   `AABBtree` with the bboxes
    //! \param[in] mmDist initial value of the minimum of the maximum distance
    //!                   used in the recursive call.
    //!
    //!
    static real_type min_maxdist(real_type x, real_type y, AABBtree const & tree, real_type mmDist);

    //!
    //! Select the candidate bboxes which have distance less than mmDist
    //!
    //! \param[in]  x      x-coordinate of the point
    //! \param[in]  y      y-coordinate of the point
    //! \param[in]  mmDist minimum distance used  for the selection of bboxes
    //! \param[in]  tree   `AABBtree` with the bbox's
    //! \param[out] candidateList  list of bbox which have minim distance less than `mmDist`
    //!
    //!
    static void min_maxdist_select(
        real_type x, real_type y, real_type mmDist, AABBtree const & tree, VecPtrBBox & candidateList);

   public:
    //! Create an empty AABB tree.
    AABBtree();

    //! destroy the stored AABB tree.
    ~AABBtree();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    //! Initialized AABB tree.
    void clear();

    //! Check if AABB tree is empty.
    bool empty() const;

    //!
    //! Get the Bounding Box of the whole AABB tree
    //!
    //! \param[in] xmin x-minimimum box coordinate
    //! \param[in] ymin y-minimimum box coordinate
    //! \param[in] xmax x-maximum box coordinate
    //! \param[in] ymax y-maximum box coordinate
    //!
    void bbox(real_type & xmin, real_type & ymin, real_type & xmax, real_type & ymax) const {
      xmin = pBBox->x_min();
      ymin = pBBox->y_min();
      xmax = pBBox->x_max();
      ymax = pBBox->y_max();
    }

    //!
    //! Build AABB tree given a list of bbox
    //!
    void build(vector<PtrBBox> const & bboxes);

    //!
    //! Pretty print the AABB tree
    //!
    void print(ostream_type & stream, int level = 0) const;

    //!
    //! Check if two AABB tree collide
    //!
    //! \param[in] tree      an AABB tree that is used to check collision
    //! \param[in] ifun      function the check if the contents of two bbox (curve) collide
    //! \param[in] swap_tree if true exchange the tree in computation
    //! \return true if the two tree collides
    //!
    template<typename COLLISION_fun>
    bool collision(AABBtree const & tree, COLLISION_fun ifun, bool swap_tree = false) const {
      // check bbox with
      if (!tree.pBBox->collision(*pBBox))
        return false;

      int icase = (children.empty() ? 0 : 1) + (tree.children.empty() ? 0 : 2);

      switch (icase) {
        case 0:  // both leaf, use GeomPrimitive intersection algorithm
          if (swap_tree)
            return ifun(tree.pBBox, pBBox);
          else
            return ifun(pBBox, tree.pBBox);
        case 1:  // first is a tree, second is a leaf
        {
          typename vector<PtrAABB>::const_iterator it;
          for (it = children.begin(); it != children.end(); ++it)
            if (tree.collision(**it, ifun, !swap_tree))
              return true;
        } break;
        case 2:  // first leaf, second is a tree
        {
          typename vector<PtrAABB>::const_iterator it;
          for (it = tree.children.begin(); it != tree.children.end(); ++it)
            if (this->collision(**it, ifun, swap_tree))
              return true;
        } break;
        case 3:  // first is a tree, second is a tree
        {
          typename vector<PtrAABB>::const_iterator c1;
          typename vector<PtrAABB>::const_iterator c2;
          for (c1 = children.begin(); c1 != children.end(); ++c1)
            for (c2 = tree.children.begin(); c2 != tree.children.end(); ++c2)
              if ((*c1)->collision(**c2, ifun, swap_tree))
                return true;
        } break;
      }
      return false;
    }

    //!
    //! Compute all the intersection of AABB trees.
    //!
    //! \param[in]  tree             an AABB tree that is used to check collision
    //! \param[out] intersectionList list of pair bbox that overlaps
    //! \param[in]  swap_tree        if true exchange the tree in computation
    //!
    void intersect(AABBtree const & tree, VecPairPtrBBox & intersectionList, bool swap_tree = false) const;

    //!
    //! Select all the bboxes candidate to be at minimum distance.
    //!
    //! \param[in]  x             x-coordinate of the point
    //! \param[in]  y             y-coordinate of the point
    //! \param[out] candidateList candidate list
    //!
    void min_distance(real_type x, real_type y, VecPtrBBox & candidateList) const;
  };

}  // namespace G2lib

///
/// eof: AABBtree.hxx
///
