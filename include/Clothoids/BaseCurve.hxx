/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file BaseCurve.hxx
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
#include <utility>
#include <vector>

#include "G2lib.hxx"
#include "Constants.hxx"
#include "Triangle2D.hxx"

namespace G2lib {

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  /*\
   |  ____                  ____
   | | __ )  __ _ ___  ___ / ___|   _ _ ____   _____
   | |  _ \ / _` / __|/ _ \ |  | | | | '__\ \ / / _ \
   | | |_) | (_| \__ \  __/ |__| |_| | |   \ V /  __/
   | |____/ \__,_|___/\___|\____\__,_|_|    \_/ \___|
  \*/

  extern char const * CurveType_name[];

  using Ipair = std::pair<real_type, real_type>;
  using IntersectList = std::vector<Ipair>;

  /*\
   |   _       _                          _
   |  (_)_ __ | |_ ___ _ __ ___  ___  ___| |_
   |  | | '_ \| __/ _ \ '__/ __|/ _ \/ __| __|
   |  | | | | | ||  __/ |  \__ \  __/ (__| |_
   |  |_|_| |_|\__\___|_|  |___/\___|\___|\__|
  \*/

  class BaseCurve;

  //!
  //! Return `true` if the two curves intersect.
  //!
  //! \param[in] C1 first curve
  //! \param[in] C2 second curve
  //!
  bool collision(BaseCurve const & C1, BaseCurve const & C2);

  //!
  //! Return `true` the the two curves intersect.
  //!
  //! \param[in] C1      first curve
  //! \param[in] offs_C1 offset of the first curve
  //! \param[in] C2      second curve
  //! \param[in] offs_C2 offset of the second curve
  //!
  bool collision_ISO(BaseCurve const & C1, real_type offs_C1, BaseCurve const & C2, real_type offs_C2);

  //!
  //! Return `true` the the two curves intersect.
  //!
  //! \param[in] C1      first curve
  //! \param[in] offs_C1 offset of the first curve
  //! \param[in] C2      second curve
  //! \param[in] offs_C2 offset of the second curve
  //!
  inline bool collision_SAE(BaseCurve const & C1, real_type offs_C1, BaseCurve const & C2, real_type offs_C2) {
    return collision_ISO(C1, -offs_C1, C2, -offs_C2);
  }

  //!
  //! Collect the intersection of the two curve.
  //!
  //! \param[in]  C1          first curve
  //! \param[in]  C2          second curve
  //! \param[out] ilist       list of the intersection (as parameter on the curves)
  //! \param[out] swap_s_vals if true store `(s2,s1)` instead of `(s1,s2)` for each
  //!                         intersection
  //!
  void intersect(BaseCurve const & C1, BaseCurve const & C2, IntersectList & ilist, bool swap_s_vals);

  //!
  //! Collect the intersections of the two curve.
  //!
  //! \param[in]  C1          first curve
  //! \param[in]  offs_C1     offset of the first curve
  //! \param[in]  C2          second curve
  //! \param[in]  offs_C2     offset of the second curve
  //! \param[out] ilist       list of the intersection (as parameter on the curves)
  //! \param[out] swap_s_vals if true store `(s2,s1)` instead of `(s1,s2)` for each
  //!                         intersection
  //!
  void intersect_ISO(
      BaseCurve const & C1,
      real_type         offs_C1,
      BaseCurve const & C2,
      real_type         offs_C2,
      IntersectList &   ilist,
      bool              swap_s_vals);

  //!
  //! Collect the intersections of the two curve.
  //!
  //! \param[in]  C1          first curve
  //! \param[in]  offs_C1     offset of the first curve
  //! \param[in]  C2          second curve
  //! \param[in]  offs_C2     offset of the second curve
  //! \param[out] ilist       list of the intersection (as parameter on the curves)
  //! \param[out] swap_s_vals if true store `(s2,s1)` instead of `(s1,s2)` for each
  //!                         intersection
  //!
  inline void intersect_SAE(
      BaseCurve const & C1,
      real_type         offs_C1,
      BaseCurve const & C2,
      real_type         offs_C2,
      IntersectList &   ilist,
      bool              swap_s_vals) {
    intersect_ISO(C1, -offs_C1, C2, -offs_C2, ilist, swap_s_vals);
  }

  //!
  //! Base classe for all the curve ìn in the library.
  //!
  class BaseCurve {
    // block default constructor
    BaseCurve(BaseCurve const &) = delete;
    BaseCurve const & operator=(BaseCurve const &) = delete;

   protected:
    CurveType m_type;

   public:
    //!
    //! Initialize the class storing the curve type.
    //!
    BaseCurve(CurveType const & type) : m_type(type) {}

    virtual ~BaseCurve() {}

    //!
    //! The name of the curve type
    //!
    CurveType type() const { return m_type; }

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    //!
    //! The length of the curve
    //!
    virtual real_type length() const = 0;

    //!
    //! The length of the curve with offset (ISO)
    //!
    virtual real_type length_ISO(real_type offs) const = 0;

    //!
    //! The length of the curve with offset (SAE)
    //!
    real_type length_SAE(real_type offs) const { return this->length_ISO(-offs); }

    /*\
     |   _     _
     |  | |__ | |__   _____  __
     |  | '_ \| '_ \ / _ \ \/ /
     |  | |_) | |_) | (_) >  <
     |  |_.__/|_.__/ \___/_/\_\
    \*/

    //!
    //! Compute the bounding box of the curve.
    //!
    //! \param[out] xmin left bottom
    //! \param[out] ymin left bottom
    //! \param[out] xmax right top
    //! \param[out] ymax right top
    //!
    virtual void bbox(real_type & xmin, real_type & ymin, real_type & xmax, real_type & ymax) const = 0;

    //!
    //! Compute the bounding box of the curve with offset (ISO).
    //!
    //! \param[in]  offs curve offset
    //! \param[out] xmin left bottom
    //! \param[out] ymin left bottom
    //! \param[out] xmax right top
    //! \param[out] ymax right top
    //!
    virtual void bbox_ISO(
        real_type offs, real_type & xmin, real_type & ymin, real_type & xmax, real_type & ymax) const = 0;

    //!
    //! Compute the bounding box of the curve (SAE).
    //!
    //! \param[in]  offs curve offset
    //! \param[out] xmin left bottom
    //! \param[out] ymin left bottom
    //! \param[out] xmax right top
    //! \param[out] ymax right top
    //!
    void bbox_SAE(real_type offs, real_type & xmin, real_type & ymin, real_type & xmax, real_type & ymax) const {
      this->bbox_ISO(-offs, xmin, ymin, xmax, ymax);
    }

    /*\
     |   _    _   _____    _                _
     |  | |__| |_|_   _| _(_)__ _ _ _  __ _| |___
     |  | '_ \ '_ \| || '_| / _` | ' \/ _` | / -_)
     |  |_.__/_.__/|_||_| |_\__,_|_||_\__, |_\___|
     |                                |___/
    \*/

    //!
    //! Build a cover with triangles of the curve.
    //!
    //! \param[out] tvec      list of covering triangles
    //! \param[out] max_angle maximum angle variation of the curve covered by a triangle
    //! \param[out] max_size  maximum admissible size of the covering tirnagles
    //! \param[out] icurve    index of the covering triangles
    //!
    //! \rst
    //!
    //!   .. image:: ../../images/biarc_cover.jpg
    //!      :width: 80%
    //!      :align: center
    //!
    //! \endrst
    //!
    virtual void bbTriangles(
        std::vector<Triangle2D> & tvec,
        real_type                 max_angle = Utils::m_pi / 18,
        real_type                 max_size  = 1e100,
        int_type                  icurve    = 0) const = 0;

    //!
    //! Build a cover with triangles of the curve with offset (ISO).
    //!
    //! \param[out] offs      curve offset
    //! \param[out] tvec      list of covering triangles
    //! \param[out] max_angle maximum angle variation of the curve covered by a triangle
    //! \param[out] max_size  maximum admissible size of the covering tirnagles
    //! \param[out] icurve    index of the covering triangles
    //!
    virtual void bbTriangles_ISO(
        real_type                 offs,
        std::vector<Triangle2D> & tvec,
        real_type                 max_angle = Utils::m_pi / 18,
        real_type                 max_size  = 1e100,
        int_type                  icurve    = 0) const = 0;

    //!
    //! Build a cover with triangles of the curve with offset (SAE).
    //!
    //! \param[out] offs      curve offset
    //! \param[out] tvec      list of covering triangles
    //! \param[out] max_angle maximum angle variation of the arc covered by a triangle
    //! \param[out] max_size  maximum admissible size of the covering tirnagles
    //! \param[out] icurve    index of the covering triangles
    //!
    virtual void bbTriangles_SAE(
        real_type                 offs,
        std::vector<Triangle2D> & tvec,
        real_type                 max_angle = Utils::m_pi / 18,
        real_type                 max_size  = 1e100,
        int_type                  icurve    = 0) const = 0;

    /*\
     |   ____             _          _______           _
     |  | __ )  ___  __ _(_)_ __    / / ____|_ __   __| |
     |  |  _ \ / _ \/ _` | | '_ \  / /|  _| | '_ \ / _` |
     |  | |_) |  __/ (_| | | | | |/ / | |___| | | | (_| |
     |  |____/ \___|\__, |_|_| |_/_/  |_____|_| |_|\__,_|
     |              |___/
    \*/

    //!
    //! Initial angle of the curve.
    //!
    virtual real_type theta_begin() const { return this->theta(0); }

    //!
    //! Final angle of the curve.
    //!
    virtual real_type theta_end() const { return this->theta(this->length()); }

    //!
    //! Initial curvature.
    //!
    virtual real_type kappa_begin() const { return this->kappa(0); }

    //!
    //! Final curvature.
    //!
    virtual real_type kappa_end() const { return this->kappa(this->length()); }

    //!
    //! Initial x-coordinate.
    //!
    virtual real_type x_begin() const { return this->X(0); }

    //!
    //! Initial y-coordinate.
    //!
    virtual real_type y_begin() const { return this->Y(0); }

    //!
    //! Final x-coordinate.
    //!
    virtual real_type x_end() const { return this->X(this->length()); }

    //!
    //! Final y-coordinate.
    //!
    virtual real_type y_end() const { return this->Y(this->length()); }

    //!
    //! Initial x-coordinate with offset (ISO standard).
    //!
    virtual real_type x_begin_ISO(real_type offs) const { return this->X_ISO(0, offs); }

    //!
    //! Initial y-coordinate with offset (ISO standard).
    //!
    virtual real_type y_begin_ISO(real_type offs) const { return this->Y_ISO(0, offs); }

    //!
    //! Final x-coordinate with offset (ISO standard).
    //!
    virtual real_type x_end_ISO(real_type offs) const { return this->X_ISO(this->length(), offs); }

    //!
    //! Final y-coordinate with offset (ISO standard).
    //!
    virtual real_type y_end_ISO(real_type offs) const { return this->Y_ISO(this->length(), offs); }

    //!
    //! Initial x-coordinate with offset (SAE standard).
    //!
    real_type x_begin_SAE(real_type offs) const { return this->x_begin_ISO(-offs); }

    //!
    //! Initial y-coordinate with offset (SAE standard).
    //!
    real_type y_begin_SAE(real_type offs) const { return this->y_begin_ISO(-offs); }

    //!
    //! Final y-coordinate with offset (SAE standard).
    //!
    real_type x_end_SAE(real_type offs) const { return this->x_end_ISO(-offs); }

    //!
    //! Final y-coordinate with offset (ISO standard).
    //!
    real_type y_end_SAE(real_type offs) const { return this->y_end_ISO(-offs); }

    //!
    //! Initial tangent x-coordinate.
    //!
    virtual real_type tx_Begin() const { return this->tx(0); }

    //!
    //! Initial tangent y-coordinate.
    //!
    virtual real_type ty_Begin() const { return this->ty(0); }

    //!
    //! Final tangent x-coordinate.
    //!
    virtual real_type tx_End() const { return this->tx(this->length()); }

    //!
    //! Final tangent y-coordinate.
    //!
    virtual real_type ty_End() const { return this->ty(this->length()); }

    //!
    //! Intial normal x-coordinate (ISO).
    //!
    virtual real_type nx_Begin_ISO() const { return -this->ty(0); }

    //!
    //! Intial normal y-coordinate (ISO).
    //!
    virtual real_type ny_Begin_ISO() const { return this->tx(0); }

    //!
    //! Final normal x-coordinate (ISO).
    //!
    virtual real_type nx_End_ISO() const { return -this->ty(this->length()); }

    //!
    //! Final normal y-coordinate (ISO).
    //!
    virtual real_type ny_End_ISO() const { return this->tx(this->length()); }

    //!
    //! Intial normal x-coordinate (SAE).
    //!
    real_type nx_Begin_SAE() const { return -nx_Begin_ISO(); }

    //!
    //! Intial normal y-coordinate (SAE).
    //!
    real_type ny_Begin_SAE() const { return -ny_Begin_ISO(); }

    //!
    //! Final normal x-coordinate (SAE).
    //!
    real_type nx_End_SAE() const { return -nx_End_ISO(); }

    //!
    //! Intial normal y-coordinate (SAE).
    //!
    real_type ny_End_SAE() const { return -ny_End_ISO(); }

    /*\
     |  _   _          _
     | | |_| |__   ___| |_ __ _
     | | __| '_ \ / _ \ __/ _` |
     | | |_| | | |  __/ || (_| |
     |  \__|_| |_|\___|\__\__,_|
    \*/

    //!
    //! Angle at curvilinear coodinate `s`.
    //!
    virtual real_type theta(real_type s) const = 0;

    //!
    //! Angle derivative (curvature) at curvilinear coodinate `s`.
    //!
    virtual real_type theta_D(real_type s) const = 0;

    //!
    //! Angle second derivative (devitive of curvature) at curvilinear coodinate `s`.
    //!
    virtual real_type theta_DD(real_type s) const = 0;

    //!
    //! Angle third derivative at curvilinear coodinate `s`.
    //!
    virtual real_type theta_DDD(real_type s) const = 0;

    /*\
     |   _
     |  | | ____ _ _ __  _ __   __ _
     |  | |/ / _` | '_ \| '_ \ / _` |
     |  |   < (_| | |_) | |_) | (_| |
     |  |_|\_\__,_| .__/| .__/ \__,_|
     |            |_|   |_|
    \*/

    //!
    //! Ccurvature at curvilinear coodinate `s`.
    //!
    real_type kappa(real_type s) const { return theta_D(s); }

    //!
    //! Curvature derivative at curvilinear coodinate `s`.
    //!
    real_type kappa_D(real_type s) const { return theta_DD(s); }

    //!
    //! Curvature second derivative at curvilinear coodinate `s`.
    //!
    real_type kappa_DD(real_type s) const { return theta_DDD(s); }

    /*\
     |  _____                   _   _   _
     | |_   _|   __ _ _ __   __| | | \ | |
     |   | |    / _` | '_ \ / _` | |  \| |
     |   | |   | (_| | | | | (_| | | |\  |
     |   |_|    \__,_|_| |_|\__,_| |_| \_|
    \*/

    //!
    //! Tangent x-coordinate at curvilinear coodinate `s`.
    //!
    virtual real_type tx(real_type s) const;

    //!
    //! Tangent y-coordinate at curvilinear coodinate `s`.
    //!
    virtual real_type ty(real_type s) const;

    //!
    //! Tangent derivative x-coordinate at curvilinear coodinate `s`.
    //!
    virtual real_type tx_D(real_type s) const;

    //!
    //! Tangent derivative y-coordinate at curvilinear coodinate `s`.
    //!
    virtual real_type ty_D(real_type s) const;

    //!
    //! Tangent second derivative x-coordinate at curvilinear coodinate `s`.
    //!
    virtual real_type tx_DD(real_type s) const;

    //!
    //! Tangent second derivative y-coordinate at curvilinear coodinate `s`.
    //!
    virtual real_type ty_DD(real_type s) const;

    //!
    //! Tangent third derivative x-coordinate at curvilinear coodinate `s`.
    //!
    virtual real_type tx_DDD(real_type s) const;

    //!
    //! Tangent third derivative y-coordinate at curvilinear coodinate `s`.
    //!
    virtual real_type ty_DDD(real_type s) const;

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    //!
    //! Normal x-coordinate at curvilinear coodinate `s` (ISO).
    //!
    real_type nx_ISO(real_type s) const { return -ty(s); }

    //!
    //! Normal derivative x-coordinate at curvilinear coodinate `s` (ISO).
    //!
    real_type nx_ISO_D(real_type s) const { return -ty_D(s); }

    //!
    //! Normal second derivative x-coordinate at curvilinear coodinate `s` (ISO).
    //!
    real_type nx_ISO_DD(real_type s) const { return -ty_DD(s); }

    //!
    //! Normal third derivative x-coordinate at curvilinear coodinate `s` (ISO).
    //!
    real_type nx_ISO_DDD(real_type s) const { return -ty_DDD(s); }

    //!
    //! Normal y-coordinate at curvilinear coodinate `s` (ISO).
    //!
    real_type ny_ISO(real_type s) const { return tx(s); }

    //!
    //! Normal derivative y-coordinate at curvilinear coodinate `s` (ISO).
    //!
    real_type ny_ISO_D(real_type s) const { return tx_D(s); }

    //!
    //! Normal second derivative y-coordinate at curvilinear coodinate `s` (ISO).
    //!
    real_type ny_ISO_DD(real_type s) const { return tx_DD(s); }

    //!
    //! Normal third derivative y-coordinate at curvilinear coodinate `s` (ISO).
    //!
    real_type ny_ISO_DDD(real_type s) const { return tx_DDD(s); }

    //!
    //! Normal x-coordinate at curvilinear coodinate `s` (SAE).
    //!
    real_type nx_SAE(real_type s) const { return ty(s); }

    //!
    //! Normal derivative x-coordinate at curvilinear coodinate `s` (SAE).
    //!
    real_type nx_SAE_D(real_type s) const { return ty_D(s); }

    //!
    //! Normal second derivative x-coordinate at curvilinear coodinate `s` (SAE).
    //!
    real_type nx_SAE_DD(real_type s) const { return ty_DD(s); }

    //!
    //! Normal third derivative x-coordinate at curvilinear coodinate `s` (SAE).
    //!
    real_type nx_SAE_DDD(real_type s) const { return ty_DDD(s); }

    //!
    //! Normal y-coordinate at curvilinear coodinate `s` (ISO)
    //!
    real_type ny_SAE(real_type s) const { return -tx(s); }

    //!
    //! Normal derivative y-coordinate at curvilinear coodinate `s` (SAE).
    //!
    real_type ny_SAE_D(real_type s) const { return -tx_D(s); }

    //!
    //! Normal second derivative x-coordinate at curvilinear coodinate `s` (SAE).
    //!
    real_type ny_SAE_DD(real_type s) const { return -tx_DD(s); }

    //!
    //! Normal third derivative y-coordinate at curvilinear coodinate `s` (SAE).
    //!
    real_type ny_SAE_DDD(real_type s) const { return -tx_DDD(s); }

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    //!
    //! Tangent at curvilinear coodinate `s`.
    //!
    virtual void tg(real_type s, real_type & tg_x, real_type & tg_y) const {
      tg_x = this->tx(s);
      tg_y = this->ty(s);
    }

    //!
    //! Tangent derivative at curvilinear coodinate `s`.
    //!
    virtual void tg_D(real_type s, real_type & tg_x_D, real_type & tg_y_D) const {
      tg_x_D = this->tx_D(s);
      tg_y_D = this->ty_D(s);
    }

    //!
    //! Tangent second derivative at curvilinear coodinate `s`.
    //!
    virtual void tg_DD(real_type s, real_type & tg_x_DD, real_type & tg_y_DD) const {
      tg_x_DD = this->tx_DD(s);
      tg_y_DD = this->ty_DD(s);
    }

    //!
    //! Tangent third derivative at curvilinear coodinate `s`.
    //!
    virtual void tg_DDD(real_type s, real_type & tg_x_DDD, real_type & tg_y_DDD) const {
      tg_x_DDD = this->tx_DDD(s);
      tg_y_DDD = this->ty_DDD(s);
    }

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    //!
    //! Normal at curvilinear coodinate `s` (ISO).
    //!
    void nor_ISO(real_type s, real_type & nx, real_type & ny) const {
      tg(s, ny, nx);
      nx = -nx;
    }

    //!
    //! Normal derivative at curvilinear coodinate `s` (ISO).
    //!
    void nor_ISO_D(real_type s, real_type & nx_D, real_type & ny_D) const {
      tg_D(s, ny_D, nx_D);
      nx_D = -nx_D;
    }

    //!
    //! Normal second derivative at curvilinear coodinate `s` (ISO).
    //!
    void nor_ISO_DD(real_type s, real_type & nx_DD, real_type & ny_DD) const {
      tg_DD(s, ny_DD, nx_DD);
      nx_DD = -nx_DD;
    }

    //!
    //! Normal third derivative at curvilinear coodinate `s` (ISO).
    //!
    void nor_ISO_DDD(real_type s, real_type & nx_DDD, real_type & ny_DDD) const {
      tg_DDD(s, ny_DDD, nx_DDD);
      nx_DDD = -nx_DDD;
    }

    //!
    //! Normal at curvilinear coodinate `s` (SAE).
    //!
    void nor_SAE(real_type s, real_type & nx, real_type & ny) const {
      tg(s, ny, nx);
      ny = -ny;
    }

    //!
    //! Normal derivative at curvilinear coodinate `s` (SAE).
    //!
    void nor_SAE_D(real_type s, real_type & nx_D, real_type & ny_D) const {
      tg_D(s, ny_D, nx_D);
      ny_D = -ny_D;
    }

    //!
    //! Normal second derivative at curvilinear coodinate `s` (SAE).
    //!
    void nor_SAE_DD(real_type s, real_type & nx_DD, real_type & ny_DD) const {
      tg_DD(s, ny_DD, nx_DD);
      ny_DD = -ny_DD;
    }

    //!
    //! Normal third at curvilinear coodinate `s` (SAE).
    //!
    void nor_SAE_DDD(real_type s, real_type & nx_DDD, real_type & ny_DDD) const {
      tg_DDD(s, ny_DDD, nx_DDD);
      ny_DDD = -ny_DDD;
    }

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    //!
    //! Evaluate curve at curvilinear coordinate `s`.
    //!
    //! \param[in]  s  curvilinear coordinate
    //! \param[out] th angle
    //! \param[out] k  curvature
    //! \param[out] x  x-coordinate
    //! \param[out] y  y-coordinate
    //!
    virtual void evaluate(real_type s, real_type & th, real_type & k, real_type & x, real_type & y) const {
      eval(s, x, y);
      th = theta(s);
      k  = theta_D(s);
    }

    //!
    //! Evaluate curve with offset at curvilinear coordinate `s` (ISO).
    //!
    //! \param[in]  s    curvilinear coordinate
    //! \param[in]  offs offset
    //! \param[out] th   angle
    //! \param[out] k    curvature
    //! \param[out] x    x-coordinate
    //! \param[out] y    y-coordinate
    //!
    virtual void evaluate_ISO(
        real_type s, real_type offs, real_type & th, real_type & k, real_type & x, real_type & y) const {
      eval_ISO(s, offs, x, y);
      th = theta(s);
      k  = theta_D(s);
      k /= 1 + offs * k;  // scale curvature
    }

    //!
    //! Evaluate curve with offset at curvilinear coordinate `s` (SAE).
    //!
    //! \param[in]  s    curvilinear coordinate
    //! \param[in]  offs offset
    //! \param[out] th   angle
    //! \param[out] k    curvature
    //! \param[out] x    x-coordinate
    //! \param[out] y    y-coordinate
    //!
    virtual void evaluate_SAE(
        real_type s, real_type offs, real_type & th, real_type & k, real_type & x, real_type & y) const {
      eval_SAE(s, offs, x, y);
      th = theta(s);
      k  = theta_D(s);
      k /= 1 - offs * k;  // scale curvature
    }

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    //!
    //! x-coordinate at curvilinear coordinate `s`.
    //!
    virtual real_type X(real_type s) const = 0;

    //!
    //! y-coordinate at curvilinear coordinate `s`.
    //!
    virtual real_type Y(real_type s) const = 0;

    //!
    //! x-coordinate derivative at curvilinear coordinate `s`.
    //!
    virtual real_type X_D(real_type s) const = 0;

    //!
    //! y-coordinate derivative at curvilinear coordinate `s`.
    //!
    virtual real_type Y_D(real_type s) const = 0;

    //!
    //! x-coordinate second derivative at curvilinear coordinate `s`.
    //!
    virtual real_type X_DD(real_type s) const = 0;

    //!
    //! y-coordinate second derivative at curvilinear coordinate `s`.
    //!
    virtual real_type Y_DD(real_type s) const = 0;

    //!
    //! x-coordinate third derivative at curvilinear coordinate `s`.
    //!
    virtual real_type X_DDD(real_type s) const = 0;

    //!
    //! y-coordinate third derivative at curvilinear coordinate `s`.
    //!
    virtual real_type Y_DDD(real_type s) const = 0;

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    //!
    //! x and y-coordinate at curvilinear coordinate `s`.
    //!
    virtual void eval(real_type s, real_type & x, real_type & y) const = 0;

    //!
    //! x and y-coordinate derivative at curvilinear coordinate `s`.
    //!
    virtual void eval_D(real_type s, real_type & x_D, real_type & y_D) const = 0;

    //!
    //! x and y-coordinate second derivative at curvilinear coordinate `s`.
    //!
    virtual void eval_DD(real_type s, real_type & x_DD, real_type & y_DD) const = 0;

    //!
    //! x and y-coordinate third derivative at curvilinear coordinate `s`.
    //!
    virtual void eval_DDD(real_type s, real_type & x_DDD, real_type & y_DDD) const = 0;

    /*\
     |         __  __          _
     |   ___  / _|/ _|___  ___| |_
     |  / _ \| |_| |_/ __|/ _ \ __|
     | | (_) |  _|  _\__ \  __/ |_
     |  \___/|_| |_| |___/\___|\__|
    \*/

    //!
    //! x-coordinate at curvilinear coordinate `s` with offset `offs` (ISO).
    //!
    virtual real_type X_ISO(real_type s, real_type offs) const;

    //!
    //! y-coordinate at curvilinear coordinate `s` with offset `offs` (ISO).
    //!
    virtual real_type Y_ISO(real_type s, real_type offs) const;

    //!
    //! x-coordinate derivative at curvilinear coordinate `s` with offset `offs` (ISO).
    //!
    virtual real_type X_ISO_D(real_type s, real_type offs) const;

    //!
    //! y-coordinate derivative at curvilinear coordinate `s` with offset `offs` (ISO).
    //!
    virtual real_type Y_ISO_D(real_type s, real_type offs) const;

    //!
    //! x-coordinate second derivative at curvilinear coordinate `s` with offset `offs` (ISO).
    //!
    virtual real_type X_ISO_DD(real_type s, real_type offs) const;

    //!
    //! y-coordinate second derivative at curvilinear coordinate `s` with offset `offs` (ISO).
    //!
    virtual real_type Y_ISO_DD(real_type s, real_type offs) const;

    //!
    //! x-coordinate third derivative at curvilinear coordinate `s` with offset `offs` (ISO).
    //!
    virtual real_type X_ISO_DDD(real_type s, real_type offs) const;

    //!
    //! y-coordinate third derivative at curvilinear coordinate `s` with offset `offs` (ISO).
    //!
    virtual real_type Y_ISO_DDD(real_type s, real_type offs) const;

    //!
    //! x-coordinate at curvilinear coordinate `s` with offset `offs` (SAE).
    //!
    real_type X_SAE(real_type s, real_type offs) const { return this->X_ISO(s, -offs); }

    //!
    //! y-coordinate at curvilinear coordinate `s` with offset `offs` (SAE).
    //!
    real_type Y_SAE(real_type s, real_type offs) const { return this->Y_ISO(s, -offs); }

    //!
    //! x-coordinate derivative at curvilinear coordinate `s` with offset `offs` (SAE).
    //!
    real_type X_SAE_D(real_type s, real_type offs) const { return this->X_ISO_D(s, -offs); }

    //!
    //! y-coordinate derivative at curvilinear coordinate `s` with offset `offs` (SAE).
    //!
    real_type Y_SAE_D(real_type s, real_type offs) const { return this->Y_ISO_D(s, -offs); }

    //!
    //! x-coordinate second derivative at curvilinear coordinate `s` with offset `offs` (SAE).
    //!
    real_type X_SAE_DD(real_type s, real_type offs) const { return this->X_ISO_DD(s, -offs); }

    //!
    //! y-coordinate second derivative at curvilinear coordinate `s` with offset `offs` (SAE).
    //!
    real_type Y_SAE_DD(real_type s, real_type offs) const { return this->Y_ISO_DD(s, -offs); }

    //!
    //! x-coordinate third derivative at curvilinear coordinate `s` with offset `offs` (SAE).
    //!
    real_type X_SAE_DDD(real_type s, real_type offs) const { return this->X_ISO_DDD(s, -offs); }

    //!
    //! y-coordinate third derivative at curvilinear coordinate `s` with offset `offs` (SAE).
    //!
    real_type Y_SAE_DDD(real_type s, real_type offs) const { return this->Y_ISO_DDD(s, -offs); }

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    //!
    //! Compute curve at position `s` with offset `offs` (ISO).
    //!
    //! \param[in]  s     parameter on the curve
    //! \param[in]  offs  offset of the curve
    //! \param[out] x     coordinate
    //! \param[out] y     coordinate
    //!
    virtual void eval_ISO(real_type s, real_type offs, real_type & x, real_type & y) const;

    //!
    //! Compute curve at position `s` with offset `offs` (SAE).
    //!
    //! \param[in]  s     parameter on the curve
    //! \param[in]  offs  offset of the curve
    //! \param[out] x     coordinate
    //! \param[out] y     coordinate
    //!
    void eval_SAE(real_type s, real_type offs, real_type & x, real_type & y) const { this->eval_ISO(s, -offs, x, y); }

    //!
    //! Compute derivative curve at position `s` with offset `offs` (ISO).
    //!
    //! \param[in]  s     parameter on the curve
    //! \param[in]  offs  offset of the curve
    //! \param[out] x_D   x-coordinate
    //! \param[out] y_D   y-coordinate
    //!
    virtual void eval_ISO_D(real_type s, real_type offs, real_type & x_D, real_type & y_D) const;

    //!
    //! Compute derivative curve at position `s` with offset `offs` (SAE).
    //!
    //! \param[in]  s     parameter on the curve
    //! \param[in]  offs  offset of the curve
    //! \param[out] x_D   x-coordinate first derivative
    //! \param[out] y_D   y-coordinate first derivative
    //!
    void eval_SAE_D(real_type s, real_type offs, real_type & x_D, real_type & y_D) const {
      this->eval_ISO_D(s, -offs, x_D, y_D);
    }

    //!
    //! Compute second derivative curve at position `s` with offset `offs` (ISO).
    //!
    //! \param[in]  s     parameter on the curve
    //! \param[in]  offs  offset of the curve
    //! \param[out] x_DD  x-coordinate second derivative
    //! \param[out] y_DD  y-coordinate second derivative
    //!
    virtual void eval_ISO_DD(real_type s, real_type offs, real_type & x_DD, real_type & y_DD) const;

    //!
    //! Compute second derivative curve at position `s` with offset `offs` (SAE).
    //!
    //! \param[in]  s     parameter on the curve
    //! \param[in]  offs  offset of the curve
    //! \param[out] x_DD  x-coordinate second derivative
    //! \param[out] y_DD  y-coordinate second derivative
    //!
    void eval_SAE_DD(real_type s, real_type offs, real_type & x_DD, real_type & y_DD) const {
      this->eval_ISO_DD(s, -offs, x_DD, y_DD);
    }

    //!
    //! Compute third derivative curve at position `s` with offset `offs` (ISO).
    //!
    //! \param[in]  s     parameter on the curve
    //! \param[in]  offs  offset of the curve
    //! \param[out] x_DDD x-coordinate third derivative
    //! \param[out] y_DDD y-coordinate third derivative
    //!
    virtual void eval_ISO_DDD(real_type s, real_type offs, real_type & x_DDD, real_type & y_DDD) const;

    //!
    //! Compute third derivative curve at position `s` with offset `offs` (SAE).
    //!
    //! \param[in]  s     parameter on the curve
    //! \param[in]  offs  offset of the curve
    //! \param[out] x_DDD x-coordinate third derivative
    //! \param[out] y_DDD y-coordinate third derivative
    //!
    void eval_SAE_DDD(real_type s, real_type offs, real_type & x_DDD, real_type & y_DDD) const {
      this->eval_ISO_DDD(s, -offs, x_DDD, y_DDD);
    }

    /*\
     |  _                        __
     | | |_ _ __ __ _ _ __  ___ / _| ___  _ __ _ __ ___
     | | __| '__/ _` | '_ \/ __| |_ / _ \| '__| '_ ` _ \
     | | |_| | | (_| | | | \__ \  _| (_) | |  | | | | | |
     |  \__|_|  \__,_|_| |_|___/_|  \___/|_|  |_| |_| |_|
    \*/

    //! translate curve by \f$ (t_x,t_y) \f$
    virtual void translate(real_type tx, real_type ty) = 0;

    //!
    //! Rotate curve by angle \f$ theta \f$ centered at point  \f$ (c_x,c_y)\f$.
    //!
    //! \param[in] angle angle  \f$ theta \f$
    //! \param[in] cx    \f$ c_x\f$
    //! \param[in] cy    \f$ c_y\f$
    //!
    virtual void rotate(real_type angle, real_type cx, real_type cy) = 0;

    //!
    //! Scale curve by factor `sc`.
    //!
    virtual void scale(real_type sc) = 0;

    //!
    //! Reverse curve parameterization.
    //!
    virtual void reverse() = 0;

    //!
    //! Translate curve so that origin will be (`newx0`, `newy0`).
    //!
    virtual void change_origin(real_type newx0, real_type newy0) = 0;

    //!
    //! Cut curve at parametrix coordinate `s_begin` and `s_end`.
    //!
    virtual void trim(real_type s_begin, real_type s_end) = 0;

    /*\
     |   _       _                          _
     |  (_)_ __ | |_ ___ _ __ ___  ___  ___| |_
     |  | | '_ \| __/ _ \ '__/ __|/ _ \/ __| __|
     |  | | | | | ||  __/ |  \__ \  __/ (__| |_
     |  |_|_| |_|\__\___|_|  |___/\___|\___|\__|
    \*/

    //!
    //! Check collision with another curve.
    //!
    bool collision(BaseCurve const & C) const { return G2lib::collision(*this, C); }

    //!
    //! Check collision with another curve with offset (ISO).
    //!
    //! \param[in] offs   curve offset
    //! \param[in] C      second curve to check collision
    //! \param[in] offs_C curve offset of the second curve
    //! \return true if collision is detected
    //!
    bool collision_ISO(real_type offs, BaseCurve const & C, real_type offs_C) const {
      return G2lib::collision_ISO(*this, offs, C, offs_C);
    }

    //!
    //! Check collision with another curve with offset (SAE).
    //!
    //! \param[in] offs   curve offset
    //! \param[in] C      second curve to check collision
    //! \param[in] offs_C curve offset of the second curve
    //! \return true if collision is detected
    //!
    bool collision_SAE(real_type offs, BaseCurve const & C, real_type offs_C) const {
      return G2lib::collision_SAE(*this, offs, C, offs_C);
    }

    //!
    //! Intersect the curve with another curve.
    //!
    //! \param[in]  C           second curve intersect
    //! \param[out] ilist       list of the intersection (as parameter on the curves)
    //! \param[in]  swap_s_vals if true store `(s2,s1)` instead of `(s1,s2)` for each
    //!                         intersection
    //!
    void intersect(BaseCurve const & C, IntersectList & ilist, bool swap_s_vals) const {
      G2lib::intersect(*this, C, ilist, swap_s_vals);
    }

    //!
    //! Intersect the curve with another curve with offset (ISO)
    //!
    //! \param[in]  offs        offset first curve
    //! \param[in]  C           second curve intersect
    //! \param[in]  offs_C      offset second curve
    //! \param[out] ilist       list of the intersection (as parameter on the curves)
    //! \param[in]  swap_s_vals if true store `(s2,s1)` instead of `(s1,s2)` for each
    //!                         intersection
    //!
    void intersect_ISO(
        real_type offs, BaseCurve const & C, real_type offs_C, IntersectList & ilist, bool swap_s_vals) const {
      G2lib::intersect_ISO(*this, offs, C, offs_C, ilist, swap_s_vals);
    }

    //!
    //! Intersect the curve with another curve with offset (SAE).
    //!
    //! \param[in]  offs        offset first curve
    //! \param[in]  C           second curve intersect
    //! \param[in]  offs_C      offset second curve
    //! \param[out] ilist       list of the intersection (as parameter on the curves)
    //! \param[in]  swap_s_vals if true store `(s2,s1)` instead of `(s1,s2)` for each
    //!                         intersection
    //!
    void intersect_SAE(
        real_type offs, BaseCurve const & C, real_type offs_C, IntersectList & ilist, bool swap_s_vals) const {
      G2lib::intersect_SAE(*this, offs, C, offs_C, ilist, swap_s_vals);
    }

    /*\
     |      _ _     _
     |   __| (_)___| |_ __ _ _ __   ___ ___
     |  / _` | / __| __/ _` | '_ \ / __/ _ \
     | | (_| | \__ \ || (_| | | | | (_|  __/
     |  \__,_|_|___/\__\__,_|_| |_|\___\___|
    \*/

    //!
    //! Given a point find closest point on the curve.
    //!
    //! \param  qx  x-coordinate of the point
    //! \param  qy  y-coordinate of the point
    //! \param  x   x-coordinate of the projected point on the curve
    //! \param  y   y-coordinate of the projected point on the curve
    //! \param  s   parameter on the curve of the projection
    //! \param  t   curvilinear coordinate of the point x,y (if orthogonal projection)
    //! \param  dst distance point projected point
    //! \return 1 = point is projected orthogonal
    //!         0 = more than one projection (first returned)
    //!        -1 = minimum point is not othogonal projection to curve
    //!
    virtual int_type closest_point_ISO(
        real_type qx, real_type qy, real_type & x, real_type & y, real_type & s, real_type & t, real_type & dst)
        const = 0;

    //!
    //! Given a point find closest point on the curve.
    //!
    //! \param  qx  x-coordinate of the point
    //! \param  qy  y-coordinate of the point
    //! \param  x   x-coordinate of the projected point on the curve
    //! \param  y   y-coordinate of the projected point on the curve
    //! \param  s   parameter on the curve of the projection
    //! \param  t   curvilinear coordinate of the point x,y (if orthogonal projection)
    //! \param  dst distance point projected point
    //! \return 1 = point is projected orthogonal
    //!         0 = more than one projection (first returned)
    //!        -1 = minimum point is not othogonal projection to curve
    //!
    int_type closest_point_SAE(
        real_type qx, real_type qy, real_type & x, real_type & y, real_type & s, real_type & t, real_type & dst) const {
      int_type res = this->closest_point_ISO(qx, qy, x, y, s, t, dst);
      t            = -t;
      return res;
    }

    //!
    //! Given a point find closest point on the curve.
    //!
    //! \param  qx   x-coordinate of the point
    //! \param  qy   y-coordinate of the point
    //! \param  offs offset of the curve
    //! \param  x    x-coordinate of the projected point on the curve
    //! \param  y    y-coordinate of the projected point on the curve
    //! \param  s    parameter on the curve of the projection
    //! \param  t    curvilinear coordinate of the point x,y (if orthogonal projection)
    //! \param  dst  distance point projected point
    //! \return 1 = point is projected orthogonal
    //!         0 = more than one projection (first returned)
    //!        -1 = minimum point is not othogonal projection to curve
    //!
    virtual int_type  // true if projection is unique and orthogonal
    closest_point_ISO(
        real_type   qx,
        real_type   qy,
        real_type   offs,
        real_type & x,
        real_type & y,
        real_type & s,
        real_type & t,
        real_type & dst) const = 0;

    //!
    //! Given a point find closest point on the curve.
    //!
    //! \param  qx   x-coordinate of the point
    //! \param  qy   y-coordinate of the point
    //! \param  offs offset of the curve
    //! \param  x    x-coordinate of the projected point on the curve
    //! \param  y    y-coordinate of the projected point on the curve
    //! \param  s    parameter on the curve of the projection
    //! \param  t    curvilinear coordinate of the point x,y (if orthogonal projection)
    //! \param  dst  distance point projected point
    //! \return 1 = point is projected orthogonal
    //!         0 = more than one projection (first returned)
    //!        -1 = minimum point is not othogonal projection to curve
    //!
    int_type closest_point_SAE(
        real_type   qx,
        real_type   qy,
        real_type   offs,
        real_type & x,
        real_type & y,
        real_type & s,
        real_type & t,
        real_type & dst) const {
      int_type res = this->closest_point_ISO(qx, qy, -offs, x, y, s, t, dst);
      t            = -t;
      return res;
    }

    //!
    //! Compute the distance between a point \f$ q=(q_x,q_y) \f$ and the curve.
    //!
    //! \param[in] qx component \f$ q_x \f$
    //! \param[in] qy component \f$ q_y \f$
    //! \return the computed distance
    //!
    virtual real_type distance(real_type qx, real_type qy) const {
      real_type x, y, s, t, dst;
      closest_point_ISO(qx, qy, x, y, s, t, dst);
      return dst;
    }

    //!
    //! Compute the distance between a point \f$ q=(q_x,q_y) \f$ and the curve with offset (ISO).
    //!
    //! \param[in] qx   component \f$ q_x \f$
    //! \param[in] qy   component \f$ q_y \f$
    //! \param[in] offs offset of the curve
    //! \return the computed distance
    //!
    real_type distance_ISO(real_type qx, real_type qy, real_type offs) const {
      real_type x, y, s, t, dst;
      this->closest_point_ISO(qx, qy, offs, x, y, s, t, dst);
      return dst;
    }

    //!
    //! Compute the distance between a point \f$ q=(q_x,q_y) \f$ and the curve with offset (SAE).
    //!
    //! \param[in] qx   component \f$ q_x \f$
    //! \param[in] qy   component \f$ q_y \f$
    //! \param[in] offs offset of the curve
    //! \return the computed distance
    //!
    real_type distance_SAE(real_type qx, real_type qy, real_type offs) const {
      real_type x, y, s, t, dst;
      this->closest_point_SAE(qx, qy, offs, x, y, s, t, dst);
      return dst;
    }

    /*\
     |    __ _           _ ____ _____
     |   / _(_)_ __   __| / ___|_   _|
     |  | |_| | '_ \ / _` \___ \ | |
     |  |  _| | | | | (_| |___) || |
     |  |_| |_|_| |_|\__,_|____/ |_|
    \*/

    //!
    //! Find the curvilinear coordinate of point \f$ P=(x,y) \f$
    //! respect to the curve (ISO), i.e.
    //!
    //! \f[
    //!     P = C(s)+N(s)t
    //! \f]
    //!
    //! where \f$ C(s) \f$ is the curve position respect to the curvilinear coordinates
    //! and \f$ C(s) \f$ is the normal at the point \f$ C(s) \f$.
    //!
    //! \param[in]  x component \f$ x \f$
    //! \param[in]  y component \f$ y \f$
    //! \param[out] s curvilinear coordinate
    //! \param[out] t offset respect to the curve of \f$ (x,y) \f$
    //! \return true if the coordinate are found
    //!
    bool findST_ISO(real_type x, real_type y, real_type & s, real_type & t) const {
      real_type X, Y, dst;
      int_type  icode = this->closest_point_ISO(x, y, X, Y, s, t, dst);
      return icode >= 0;
    }

    //!
    //! Find the curvilinear coordinate of point \f$ (x,y) \f$
    //! respect to the curve (SAE), i.e.
    //!
    //! \f[
    //!     P = C(s)+N(s)t
    //! \f]
    //!
    //! where \f$ C(s) \f$ is the curve position respect to the curvilinear coordinates
    //! and \f$ C(s) \f$ is the normal at the point \f$ C(s) \f$.
    //!
    //! \param[in]  x component \f$ x \f$
    //! \param[in]  y component \f$ y \f$
    //! \param[out] s curvilinear coordinate
    //! \param[out] t offset respect to the curve of \f$ (x,y) \f$
    //! \return true if the coordinate are found
    //!
    bool findST_SAE(real_type x, real_type y, real_type & s, real_type & t) const {
      real_type X, Y, dst;
      int_type  icode = this->closest_point_SAE(x, y, X, Y, s, t, dst);
      return icode >= 0;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    //!
    //! Pretty print of the curve data.
    //!
    virtual void info(ostream_type & stream) const = 0;
  };

}  // namespace G2lib

///
/// eof: BaseCurve.hh
///
