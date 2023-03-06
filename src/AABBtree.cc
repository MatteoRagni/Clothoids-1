/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file AABBtree.cc
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
#include "Clothoids/AABBtree.hxx"
#include "Utils.hxx"

// Workaround for Visual Studio
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include <algorithm>

namespace G2lib {

  using std::abs;
  using std::max;
  using std::min;
  using std::numeric_limits;

  /*\
   |   ____  ____
   |  | __ )| __ )  _____  __
   |  |  _ \|  _ \ / _ \ \/ /
   |  | |_) | |_) | (_) >  <
   |  |____/|____/ \___/_/\_\
  \*/

  void BBox::join(vector<PtrBBox> const & bboxes) {
    if (bboxes.empty()) {
      std::fill_n(m_bbox, 4, 0.0);
    } else {
      vector<PtrBBox>::const_iterator it = bboxes.begin();

      x_min() = (*it)->x_min();
      y_min() = (*it)->y_min();
      x_max() = (*it)->x_max();
      y_max() = (*it)->y_max();

      for (++it; it != bboxes.end(); ++it) {
        BBox const & currBox = **it;
        if (currBox.x_min() < x_min())
          x_min() = currBox.x_min();
        if (currBox.y_min() < y_min())
          y_min() = currBox.y_min();
        if (currBox.x_max() > x_max())
          x_max() = currBox.x_max();
        if (currBox.y_max() > y_max())
          y_max() = currBox.y_max();
      }
    }
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  real_type BBox::distance(real_type x, real_type y) const {
    /*\
     |
     |   6          7          8
     |       +-------------+
     |       |             |
     |   3   |      4      |   5
     |       |             |
     |       +-------------+
     |   0          1          2
     |
    \*/
    int_type icase = 4;
    if (x < x_min())
      icase = 3;
    else if (x > x_max())
      icase = 5;
    if (y < y_min())
      icase -= 3;
    else if (y > y_max())
      icase += 3;
    real_type dst = 0;
    switch (icase) {
      case 0:
        dst = hypot(x - x_min(), y - y_min());
        break;
      case 1:
        dst = y_min() - y;
        break;
      case 2:
        dst = hypot(x - x_max(), y - y_min());
        break;
      case 3:
        dst = x_min() - x;
        break;
      case 4:
        break;
      case 5:
        dst = x - x_max();
        break;
      case 6:
        dst = hypot(x - x_min(), y - y_max());
        break;
      case 7:
        dst = y - y_max();
        break;
      case 8:
        dst = hypot(x - x_max(), y - y_max());
        break;
    }
    return dst;
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  real_type BBox::maxDistance(real_type x, real_type y) const {
    real_type dx = max(abs(x - x_min()), abs(x - x_max()));
    real_type dy = max(abs(y - y_min()), abs(y - y_max()));
    return hypot(dx, dy);
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  void BBox::print(ostream_type & stream) const {
    stream << Utils::format_string("BBOX (xmin,ymin,xmax,ymax) = (%f, %f, %f, %f)\n", x_min(), y_min(), x_max(), y_max());
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  BBox const & BBox::operator=(BBox const & rhs) {
    std::copy_n(rhs.m_bbox, 4, m_bbox);
    m_id   = rhs.m_id;
    m_ipos = rhs.m_ipos;
    return *this;
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  bool BBox::collision(BBox const & box) const {
    return !((box.x_min() > x_max()) || (box.x_max() < x_min()) || (box.y_min() > y_max()) || (box.y_max() < y_min()));
  }

  /*\
   |      _        _    ____  ____  _
   |     / \      / \  | __ )| __ )| |_ _ __ ___  ___
   |    / _ \    / _ \ |  _ \|  _ \| __| '__/ _ \/ _ \
   |   / ___ \  / ___ \| |_) | |_) | |_| | |  __/  __/
   |  /_/   \_\/_/   \_\____/|____/ \__|_|  \___|\___|
  \*/

  AABBtree::AABBtree() {
    pBBox.reset();
    children.clear();
  }

  AABBtree::~AABBtree() {
    pBBox.reset();
    children.clear();
  }

  void AABBtree::clear() {
    pBBox.reset();
    children.clear();
  }

  bool AABBtree::empty() const { return children.empty() && !pBBox; }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  void AABBtree::build(vector<PtrBBox> const & bboxes) {
    clear();

    if (bboxes.empty())
      return;

    size_t size = bboxes.size();

    if (size == 1) {
      this->pBBox = bboxes.front();
      return;
    }

    pBBox = shared_ptr<BBox>(new BBox(bboxes, 0, 0));

    real_type xmin = pBBox->Xmin();
    real_type ymin = pBBox->Ymin();
    real_type xmax = pBBox->Xmax();
    real_type ymax = pBBox->Ymax();

    vector<PtrBBox> posBoxes;
    vector<PtrBBox> negBoxes;

    if ((ymax - ymin) > (xmax - xmin)) {
      real_type                       cutPos = (ymax + ymin) / 2;
      vector<PtrBBox>::const_iterator it;
      for (it = bboxes.begin(); it != bboxes.end(); ++it) {
        real_type ymid = ((*it)->Ymin() + (*it)->Ymax()) / 2;
        if (ymid > cutPos)
          posBoxes.push_back(*it);
        else
          negBoxes.push_back(*it);
      }
    } else {
      real_type                       cutPos = (xmax + xmin) / 2;
      vector<PtrBBox>::const_iterator it;
      for (it = bboxes.begin(); it != bboxes.end(); ++it) {
        real_type xmid = ((*it)->Xmin() + (*it)->Xmax()) / 2;
        if (xmid > cutPos)
          posBoxes.push_back(*it);
        else
          negBoxes.push_back(*it);
      }
    }

    if (negBoxes.empty()) {
      vector<PtrBBox>::iterator midIdx;
      midIdx = posBoxes.begin() + posBoxes.size() / 2;
      negBoxes.insert(negBoxes.end(), midIdx, posBoxes.end());
      posBoxes.erase(midIdx, posBoxes.end());
    } else if (posBoxes.empty()) {
      vector<PtrBBox>::iterator midIdx;
      midIdx = negBoxes.begin() + negBoxes.size() / 2;
      posBoxes.insert(posBoxes.end(), midIdx, negBoxes.end());
      negBoxes.erase(midIdx, negBoxes.end());
    }

    PtrAABB neg = make_shared<AABBtree>();
    PtrAABB pos = make_shared<AABBtree>();

    neg->build(negBoxes);
    if (!neg->empty())
      children.push_back(neg);

    pos->build(posBoxes);
    if (!pos->empty())
      children.push_back(pos);
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  void AABBtree::print(ostream_type & stream, int level) const {
    if (empty()) {
      stream << "[EMPTY AABB tree]\n";
    } else {
      stream << Utils::format_string("BBOX xmin=%-12.4f ymin=%-12.4f xmax=%-12.4f ymax=%-12.4f\n", 
        pBBox->x_min(), pBBox->y_min(), pBBox->x_max(), pBBox->y_max());
      vector<PtrAABB>::const_iterator it;
      for (it = children.begin(); it != children.end(); ++it)
        (*it)->print(stream, level + 1);
    }
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  void AABBtree::intersect(AABBtree const & tree, VecPairPtrBBox & intersectionList, bool swap_tree) const {
    // check bbox with
    if (!tree.pBBox->collision(*pBBox))
      return;

    int icase = (children.empty() ? 0 : 1) + (tree.children.empty() ? 0 : 2);

    switch (icase) {
      case 0:  // both leaf
        if (swap_tree)
          intersectionList.push_back(PairPtrBBox(tree.pBBox, pBBox));
        else
          intersectionList.push_back(PairPtrBBox(pBBox, tree.pBBox));
        break;
      case 1:  // first is a tree, second is a leaf
      {
        vector<PtrAABB>::const_iterator it;
        for (it = children.begin(); it != children.end(); ++it)
          tree.intersect(**it, intersectionList, !swap_tree);
      } break;
      case 2:  // first leaf, second is a tree
      {
        vector<PtrAABB>::const_iterator it;
        for (it = tree.children.begin(); it != tree.children.end(); ++it)
          this->intersect(**it, intersectionList, swap_tree);
      } break;
      case 3:  // first is a tree, second is a tree
      {
        vector<PtrAABB>::const_iterator c1;
        vector<PtrAABB>::const_iterator c2;
        for (c1 = children.begin(); c1 != children.end(); ++c1)
          for (c2 = tree.children.begin(); c2 != tree.children.end(); ++c2)
            (*c1)->intersect(**c2, intersectionList, swap_tree);
      } break;
    }
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  real_type AABBtree::min_maxdist(real_type x, real_type y, AABBtree const & tree, real_type mmDist) {
    vector<PtrAABB> const & children = tree.children;

    if (children.empty()) {
      real_type dst = tree.pBBox->maxDistance(x, y);
      return min(dst, mmDist);
    }

    real_type dmin = tree.pBBox->distance(x, y);
    if (dmin > mmDist)
      return mmDist;

    // check bbox with
    vector<PtrAABB>::const_iterator it;
    for (it = children.begin(); it != children.end(); ++it)
      mmDist = min_maxdist(x, y, **it, mmDist);

    return mmDist;
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  void AABBtree::min_maxdist_select(
      real_type x, real_type y, real_type mmDist, AABBtree const & tree, VecPtrBBox & candidateList) {
    vector<PtrAABB> const & children = tree.children;
    real_type               dst      = tree.pBBox->distance(x, y);
    if (dst <= mmDist) {
      if (children.empty()) {
        candidateList.push_back(tree.pBBox);
      } else {
        // check bbox with
        vector<PtrAABB>::const_iterator it;
        for (it = children.begin(); it != children.end(); ++it)
          min_maxdist_select(x, y, mmDist, **it, candidateList);
      }
    }
  }

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  void AABBtree::min_distance(real_type x, real_type y, VecPtrBBox & candidateList) const {
    real_type mmDist = min_maxdist(x, y, *this, numeric_limits<real_type>::infinity());
    min_maxdist_select(x, y, mmDist, *this, candidateList);
  }

}  // namespace G2lib

///
/// eof: AABBtree.cc
///
