/*
 *  $Id: draw.cc,v 1.3 2009-07-31 07:05:24 ueshiba Exp $
 */
#include "draw.h"

namespace TU
{
namespace v
{
OglDC&
operator <<(OglDC& dc, const BSplineCurve3f& c)
{
    gluBeginCurve(dc.nurbsRenderer());
    gluNurbsCurve(dc.nurbsRenderer(),
		  c.M() + 1, const_cast<float*>(c.knots().data()),
		  c.dim(), const_cast<float*>(c.data()), c.degree() + 1,
		  GL_MAP1_VERTEX_3);
    gluEndCurve(dc.nurbsRenderer());

  // draw control polygon
    glPushAttrib(GL_LINE_BIT);
    glPushAttrib(GL_POINT_BIT);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xaaaa);
    glBegin(GL_LINE_STRIP);
      for (u_int i = 0; i <= c.N(); ++i)
	  glVertex3fv(c[i].data());
    glEnd();
    glPointSize(3.0);
    glBegin(GL_POINTS);
      for (u_int i = 0; i <= c.N(); ++i)
	  glVertex3fv(c[i].data());
    glEnd();

    glPopAttrib();
    glPopAttrib();
    
    return dc;
}

OglDC&
operator <<(OglDC& dc, const RationalBSplineCurve3f& c)
{
    gluBeginCurve(dc.nurbsRenderer());
    gluNurbsCurve(dc.nurbsRenderer(),
		  c.M() + 1, const_cast<float*>(c.knots().data()),
		  c.dim(), const_cast<float*>(c.data()), c.degree() + 1,
		  GL_MAP1_VERTEX_4);
    gluEndCurve(dc.nurbsRenderer());

  // draw control polygon
    glPushAttrib(GL_LINE_BIT);
    glPushAttrib(GL_POINT_BIT);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xaaaa);
    glBegin(GL_LINE_STRIP);
      for (u_int i = 0; i <= c.N(); ++i)
	  glVertex4fv(c[i].data());
    glEnd();
    glPointSize(3.0);
    glBegin(GL_POINTS);
      for (u_int i = 0; i <= c.N(); ++i)
	  glVertex4fv(c[i].data());
    glEnd();

    glPopAttrib();
    glPopAttrib();

    return dc;
}

OglDC&
operator <<(OglDC& dc, const BSplineSurface3f& s)
{
    gluBeginSurface(dc.nurbsRenderer());
    gluNurbsSurface(dc.nurbsRenderer(),
		    s.uM() + 1, const_cast<float*>(s.uKnots().data()),
		    s.vM() + 1, const_cast<float*>(s.vKnots().data()),
		    s.dim(), (s.uN() + 1) * s.dim(),
		    const_cast<float*>(s.data()),
		    s.uDegree() + 1, s.vDegree() + 1, GL_MAP2_VERTEX_3);
    gluEndSurface(dc.nurbsRenderer());

  // draw control polygon
    glPushAttrib(GL_LINE_BIT);
    glPushAttrib(GL_POINT_BIT);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xaaaa);
    for (u_int j = 0; j <= s.vN(); ++j)
    {
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	for (u_int i = 0; i <= s.uN(); ++i)
	    glVertex3fv(s[j][i].data());
	glEnd();
	glPointSize(3.0);
	glBegin(GL_POINTS);
	for (u_int i = 0; i <= s.uN(); ++i)
	    glVertex3fv(s[j][i].data());
	glEnd();
    }
    for (u_int i = 0; i <= s.uN(); ++i)
    {
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	for (u_int j = 0; j <= s.vN(); ++j)
	    glVertex3fv(s[j][i].data());
	glEnd();
	glPointSize(3.0);
	glBegin(GL_POINTS);
	for (u_int j = 0; j <= s.vN(); ++j)
	    glVertex3fv(s[j][i].data());
	glEnd();
    }

    glPopAttrib();
    glPopAttrib();

    return dc;
}
 
}
}
