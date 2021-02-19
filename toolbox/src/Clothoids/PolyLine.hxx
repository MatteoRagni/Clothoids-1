/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2017                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                |
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

///
/// file: PolyLine.hxx
///

namespace G2lib {

  /*\
   |  ____       _       _     _
   | |  _ \ ___ | |_   _| |   (_)_ __   ___
   | | |_) / _ \| | | | | |   | | '_ \ / _ \
   | |  __/ (_) | | |_| | |___| | | | |  __/
   | |_|   \___/|_|\__, |_____|_|_| |_|\___|
   |               |___/
  \*/

  class CircleArc;
  class Biarc;
  class BiarcList;
  class ClothoidCurve;
  class ClothoidList;

  //! Class to manage a collection of straight segment
  class PolyLine : public BaseCurve {
    friend class ClothoidList;
    friend class BiarcList;
  private:
    vector<LineSegment> m_polylineList;
    vector<real_type>   m_s0;
    real_type           m_xe;
    real_type           m_ye;

    mutable Utils::BinarySearch<int_type> m_lastInterval;

    mutable bool     m_aabb_done;
    mutable AABBtree m_aabb_tree;

    class Collision_list {
      PolyLine const * pPL1;
      PolyLine const * pPL2;
    public:
      Collision_list( PolyLine const * _pPL1, PolyLine const * _pPL2 )
      : pPL1(_pPL1)
      , pPL2(_pPL2)
      {}

      bool
      operator () ( BBox::PtrBBox ptr1, BBox::PtrBBox ptr2 ) const {
        LineSegment const & LS1 = pPL1->m_polylineList[size_t(ptr1->Ipos())];
        LineSegment const & LS2 = pPL2->m_polylineList[size_t(ptr2->Ipos())];
        return LS1.collision( LS2 );
      }
    };

    void
    resetLastInterval() {
      bool ok;
      int_type & lastInterval = *m_lastInterval.search( std::this_thread::get_id(), ok );
      lastInterval = 0;
    }

  public:

    //explicit
    PolyLine()
    : BaseCurve(G2LIB_POLYLINE)
    , m_aabb_done(false)
    { this->resetLastInterval(); }

    void
    init();

    void
    copy( PolyLine const & l );

    //explicit
    PolyLine( PolyLine const & PL )
    : BaseCurve(G2LIB_POLYLINE)
    , m_aabb_done(false)
    { this->resetLastInterval(); copy(PL); }

    int_type
    findAtS( real_type & s ) const;

    explicit PolyLine( LineSegment const & LS );
    explicit PolyLine( CircleArc const & C, real_type tol );
    explicit PolyLine( Biarc const & B, real_type tol );
    explicit PolyLine( ClothoidCurve const & B, real_type tol );
    explicit PolyLine( ClothoidList const & B, real_type tol );
    explicit PolyLine( BaseCurve const & C );

    PolyLine const & operator = ( PolyLine const & s )
    { copy(s); return *this; }

    LineSegment const &
    getSegment( int_type n ) const;

    int_type
    numSegment() const
    { return int_type(m_polylineList.size()); }

    int_type
    numPoints() const
    { return int_type(m_s0.size()); }

    void polygon( real_type x[], real_type y[]) const;
    void init( real_type x0, real_type y0 );
    void push_back( real_type x, real_type y );
    void push_back( LineSegment const & C );
    void push_back( CircleArc const & C, real_type tol );
    void push_back( Biarc const & C, real_type tol );
    void push_back( ClothoidCurve const & C, real_type tol );
    void push_back( ClothoidList const & L, real_type tol );

    void
    build(
      real_type const x[],
      real_type const y[],
      int_type npts
    );

    void build( LineSegment const & L );
    void build( CircleArc const & C, real_type tol );
    void build( Biarc const & B, real_type tol );
    void build( ClothoidCurve const & C, real_type tol );
    void build( ClothoidList const & CL, real_type tol );

    virtual
    void
    bbox(
      real_type & xmin,
      real_type & ymin,
      real_type & xmax,
      real_type & ymax
    ) const UTILS_OVERRIDE;

    virtual
    void
    bbox_ISO(
      real_type   /* offs */,
      real_type & /* xmin */,
      real_type & /* ymin */,
      real_type & /* xmax */,
      real_type & /* ymax */
    ) const UTILS_OVERRIDE {
      UTILS_ERROR0( "PolyLine::bbox( offs ... ) not available!\n" );
    }

    virtual
    real_type
    length() const UTILS_OVERRIDE
    { return m_s0.back(); }

    virtual
    real_type
    length_ISO( real_type ) const UTILS_OVERRIDE {
      UTILS_ERROR0( "PolyLine::length( offs ) not available!\n" );
      return 0;
    }

    virtual
    real_type
    xBegin() const UTILS_OVERRIDE
    { return m_polylineList.front().xBegin(); }

    virtual
    real_type
    yBegin() const UTILS_OVERRIDE
    { return m_polylineList.front().yBegin(); }

    virtual
    real_type
    xEnd() const UTILS_OVERRIDE
    { return m_polylineList.back().xEnd(); }

    virtual
    real_type
    yEnd() const UTILS_OVERRIDE
    { return m_polylineList.back().yEnd(); }

    virtual
    real_type
    X( real_type s ) const UTILS_OVERRIDE {
      int_type idx = this->findAtS( s );
      real_type ss = m_s0[size_t(idx)];
      return m_polylineList[size_t(idx)].X(s-ss);
    }

    virtual
    real_type
    X_D( real_type s ) const UTILS_OVERRIDE {
      int_type idx = this->findAtS( s );
      return m_polylineList[size_t(idx)].m_c0;
    }

    virtual
    real_type
    X_DD( real_type ) const UTILS_OVERRIDE
    { return 0; }

    virtual
    real_type
    X_DDD( real_type ) const UTILS_OVERRIDE
    { return 0; }

    virtual
    real_type
    Y( real_type s ) const UTILS_OVERRIDE {
      int_type idx = this->findAtS( s );
      real_type ss = m_s0[size_t(idx)];
      return m_polylineList[size_t(idx)].Y(s-ss);
    }

    virtual
    real_type
    Y_D( real_type s ) const UTILS_OVERRIDE {
      int_type idx = this->findAtS( s );
      return m_polylineList[size_t(idx)].m_s0;
    }

    virtual
    real_type
    Y_DD( real_type ) const UTILS_OVERRIDE
    { return 0; }

    virtual
    real_type
    Y_DDD( real_type ) const UTILS_OVERRIDE
    { return 0; }

    virtual
    real_type
    theta( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    theta_D( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    theta_DD( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    theta_DDD( real_type s ) const UTILS_OVERRIDE;

    virtual
    void
    eval(
      real_type   s,
      real_type & x,
      real_type & y
    ) const UTILS_OVERRIDE {
      int_type idx = this->findAtS( s );
      real_type ss = m_s0[size_t(idx)];
      m_polylineList[size_t(idx)].eval( s-ss, x, y );
    }

    virtual
    void
    eval_D(
      real_type   s,
      real_type & x_D,
      real_type & y_D
    ) const UTILS_OVERRIDE {
      int_type idx = this->findAtS( s );
      real_type ss = m_s0[size_t(idx)];
      m_polylineList[size_t(idx)].eval_D( s-ss, x_D, y_D );
    }

    virtual
    void
    eval_DD(
      real_type,
      real_type & x_DD,
      real_type & y_DD
    ) const UTILS_OVERRIDE
    { x_DD = y_DD = 0; }

    virtual
    void
    eval_DDD(
      real_type,
      real_type & x_DDD,
      real_type & y_DDD
    ) const UTILS_OVERRIDE
    { x_DDD = y_DDD = 0; }

    // ---

    virtual
    void
    eval_ISO(
      real_type   s,
      real_type   offs,
      real_type & x,
      real_type & y
    ) const UTILS_OVERRIDE {
      int_type idx = this->findAtS( s );
      real_type ss = m_s0[size_t(idx)];
      m_polylineList[size_t(idx)].eval_ISO( s-ss, offs, x, y );
    }

    virtual
    void
    eval_ISO_D(
      real_type   s,
      real_type   offs,
      real_type & x_D,
      real_type & y_D
    ) const UTILS_OVERRIDE {
      int_type idx = this->findAtS( s );
      real_type ss = m_s0[size_t(idx)];
      m_polylineList[size_t(idx)].eval_ISO_D( s-ss, offs, x_D, y_D );
    }

    virtual
    void
    eval_ISO_DD(
      real_type,
      real_type,
      real_type & x_DD,
      real_type & y_DD
    ) const UTILS_OVERRIDE
    { x_DD = y_DD = 0; }

    virtual
    void
    eval_ISO_DDD(
      real_type,
      real_type,
      real_type & x_DDD,
      real_type & y_DDD
    ) const UTILS_OVERRIDE
    { x_DDD = y_DDD = 0; }

    /*\
     |  _                        __
     | | |_ _ __ __ _ _ __  ___ / _| ___  _ __ _ __ ___
     | | __| '__/ _` | '_ \/ __| |_ / _ \| '__| '_ ` _ \
     | | |_| | | (_| | | | \__ \  _| (_) | |  | | | | | |
     |  \__|_|  \__,_|_| |_|___/_|  \___/|_|  |_| |_| |_|
    \*/

    virtual
    void
    translate( real_type tx, real_type ty ) UTILS_OVERRIDE {
      std::vector<LineSegment>::iterator il;
      for ( il = m_polylineList.begin(); il != m_polylineList.end(); ++il )
        il->translate( tx, ty );
    }

    virtual
    void
    rotate(
      real_type angle,
      real_type cx,
      real_type cy
    ) UTILS_OVERRIDE {
      std::vector<LineSegment>::iterator il;
      for ( il = m_polylineList.begin(); il != m_polylineList.end(); ++il )
        il->rotate( angle, cx, cy );
    }

    virtual
    void
    reverse() UTILS_OVERRIDE;

    virtual
    void
    scale( real_type sc ) UTILS_OVERRIDE;

    virtual
    void
    changeOrigin( real_type newx0, real_type newy0 ) UTILS_OVERRIDE;

    virtual
    void
    trim( real_type s_begin, real_type s_end ) UTILS_OVERRIDE;

    void
    trim( real_type s_begin, real_type s_end, PolyLine & newPL ) const;

    /*!
     * \brief compute the point at minimum distance from a point `[x,y]` and the line segment
     *
     * \param x x-coordinate
     * \param y y-coordinate
     * \param X x-coordinate of the closest point
     * \param Y y-coordinate of the closest point
     * \param S param of the closest point
     * \return the distance point-segment
     */
    virtual
    int_type
    closestPoint_ISO(
      real_type   x,
      real_type   y,
      real_type & X,
      real_type & Y,
      real_type & S,
      real_type & T,
      real_type & DST
    ) const UTILS_OVERRIDE;

    virtual
    int_type
    closestPoint_ISO(
      real_type   /* x    */,
      real_type   /* y    */,
      real_type   /* offs */,
      real_type & /* X    */,
      real_type & /* Y    */,
      real_type & /* S    */,
      real_type & /* T    */,
      real_type & /* DST  */
    ) const UTILS_OVERRIDE {
      UTILS_ERROR( "PolyLine::closestPoint( ... offs ... ) not available!\n" );
    }

    /*\
     |             _ _ _     _
     |    ___ ___ | | (_)___(_) ___  _ __
     |   / __/ _ \| | | / __| |/ _ \| '_ \
     |  | (_| (_) | | | \__ \ | (_) | | | |
     |   \___\___/|_|_|_|___/_|\___/|_| |_|
    \*/

    bool
    collision( PolyLine const & C ) const;

    bool
    collision_ISO(
      real_type        offs,
      PolyLine const & CL,
      real_type        offs_CL
    ) const {
      UTILS_ASSERT0(
        Utils::isZero(offs) && Utils::isZero(offs_CL),
        "PolyLine::collision( offs ... ) not available!\n"
      );
      return this->collision( CL );
    }

    /*\
     |   _       _                          _
     |  (_)_ __ | |_ ___ _ __ ___  ___  ___| |_
     |  | | '_ \| __/ _ \ '__/ __|/ _ \/ __| __|
     |  | | | | | ||  __/ |  \__ \  __/ (__| |_
     |  |_|_| |_|\__\___|_|  |___/\___|\___|\__|
    \*/

    void
    intersect(
      PolyLine const         & pl,
      std::vector<real_type> & s1,
      std::vector<real_type> & s2
    ) const;

    void
    intersect(
      PolyLine const & pl,
      IntersectList  & ilist,
      bool             swap_s_vals
    ) const;

    void
    intersect_ISO(
      real_type        offs,
      PolyLine const & pl,
      real_type        offs_pl,
      IntersectList  & ilist,
      bool             swap_s_vals
    ) {
      UTILS_ASSERT0(
        Utils::isZero(offs) && Utils::isZero(offs_pl),
        "PolyLine::intersect( offs ... ) not available!\n"
      );
      this->intersect( pl, ilist, swap_s_vals );
    }

    virtual
    void
    info( ostream_type & stream ) const UTILS_OVERRIDE
    { stream << "PolyLine\n" << *this << '\n'; }

    friend
    ostream_type &
    operator << ( ostream_type & stream, PolyLine const & P );

    void
    build_AABBtree( AABBtree & aabb ) const;

    void
    build_AABBtree() const {
      if ( !m_aabb_done ) {
        this->build_AABBtree( m_aabb_tree );
        m_aabb_done = true;
      }
    }

  };

}

///
/// eof: PolyLine.hxx
///
