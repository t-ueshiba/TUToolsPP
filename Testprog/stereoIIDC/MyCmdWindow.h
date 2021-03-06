/*
 *  平成14-19年（独）産業技術総合研究所 著作権所有
 *  
 *  創作者：植芝俊夫
 *
 *  本プログラムは（独）産業技術総合研究所の職員である植芝俊夫が創作し，
 *  （独）産業技術総合研究所が著作権を所有する秘密情報です．創作者によ
 *  る許可なしに本プログラムを使用，複製，改変，第三者へ開示する等の著
 *  作権を侵害する行為を禁止します．
 *  
 *  このプログラムによって生じるいかなる損害に対しても，著作権所有者お
 *  よび創作者は責任を負いません。
 *
 *  Copyright 2002-2007.
 *  National Institute of Advanced Industrial Science and Technology (AIST)
 *
 *  Creator: Toshio UESHIBA
 *
 *  [AIST Confidential and all rights reserved.]
 *  This program is confidential. Any using, copying, changing or
 *  giving any information concerning with this program to others
 *  without permission by the creator are strictly prohibited.
 *
 *  [No Warranty.]
 *  The copyright holders or the creator are not responsible for any
 *  damages in the use of this program.
 *  
 *  $Id: MyCmdWindow.h 1495 2014-02-27 15:07:51Z ueshiba $
 */
#include <iomanip>
#include <sstream>
#include <sys/time.h>
#include "TU/v/App.h"
#include "TU/v/CmdWindow.h"
#include "TU/v/CmdPane.h"
#include "TU/v/Timer.h"
#include "TU/v/FileSelection.h"
#include "TU/v/Notify.h"
#include "TU/Rectify.h"
#include "MyCanvasPane.h"
#include "ComputeThreeD.h"
#if defined(DISPLAY_3D)
#  if defined(DEMO)
#    include "MyOglWindow.h"
#  else
#    include "MyOglCanvasPane.h"
#  endif
#endif
#include "stereoGUI.h"

namespace TU
{
/************************************************************************
*  global functions							*
************************************************************************/
static inline u_int
align16(u_int n)
{
    return 16*((n-1)/16 + 1);
}

static inline void
countTime()
{
    static int		nframes = 0;
    static timeval	start;
    
    if (nframes == 10)
    {
	timeval	end;
	gettimeofday(&end, NULL);
	double	interval = (end.tv_sec  - start.tv_sec) +
	    (end.tv_usec - start.tv_usec) / 1.0e6;
	std::cerr << nframes / interval << " frames/sec" << std::endl;
	nframes = 0;
    }
    if (nframes++ == 0)
	gettimeofday(&start, NULL);
}

/************************************************************************
*  struct Epsilon<STEREO>						*
************************************************************************/
template <class STEREO>
struct Epsilon
{
    typedef typename STEREO::Parameters			params_type;

    int		get(const params_type& params)	  const	{ return 0; }
    void	set(int val, params_type& params) const	{}
};
template <class SCORE, class DISP>
struct Epsilon<GFStereo<SCORE, DISP> >
{
    typedef typename GFStereo<SCORE, DISP>::Parameters	params_type;
	
    int		get(const params_type& params) const
		{
		    return params.epsilon;
		}
    void	set(int val, params_type& params) const
		{
		    params.epsilon = val;
		}
};
    
namespace v
{
/************************************************************************
*  global functions							*
************************************************************************/
template <class CAMERA> CmdDef*
createMenuCmds(CAMERA& camera)
{
    static MenuDef fileMenu[] =
    {
	{"Open stereo images",		M_Open,			false, noSub},
	{"Save stereo images",		M_Save,			false, noSub},
	{"Save rectified images",	c_SaveRectifiedImages,	false, noSub},
	{"Save 3D data",		c_SaveThreeD,		false, noSub},
#if defined(DISPLAY_3D)
	{"Save 3D-rendered image",	c_SaveThreeDImage,	false, noSub},
#endif
	{"-",				M_Line,			false, noSub},
	{"Save camera config.",		c_SaveConfig,		false, noSub},
	{"Save camera matrices",	c_SaveMatrices,		false, noSub},
	{"-",				M_Line,			false, noSub},
	{"Quit",			M_Exit,			false, noSub},
	EndOfMenu
    };

    static float  range[] = {0.5, 3.0, 0};

    static CmdDef radioButtonCmds[] =
    {
	{C_RadioButton, c_Texture, 0, "Texture", noProp, CA_None,
	 0, 0, 1, 1, 0},
	{C_RadioButton, c_Polygon, 0, "Polygon", noProp, CA_None,
	 1, 0, 1, 1, 0},
	{C_RadioButton, c_Mesh,    0, "Mesh",    noProp, CA_None,
	 2, 0, 1, 1, 0},
	EndOfCmds
    };
    
    static CmdDef menuCmds[] =
    {
	{C_MenuButton, M_File,		0,
	 "File",			fileMenu, CA_None, 0, 0, 1, 1, 0},
	{C_MenuButton, M_Format, 0,
	 "Format",			noProp, CA_None, 1, 0, 1, 1, 0},
#if defined(DISPLAY_3D)
	{C_ChoiceFrame,  c_DrawMode,	 c_Texture,
	 "",		radioButtonCmds,	CA_NoBorder, 2, 0, 1, 1, 0},
	{C_Slider, c_GazeDistance,	1.3,
	 "Gaze distance",		range,	CA_None, 3, 0, 1, 1, 0},
	{C_ToggleButton, c_SwingView,   0,
	 "Swing view",			noProp,	CA_None, 4, 0, 1, 1, 0},
	{C_ToggleButton, c_StereoView,	0,
	 "Stereo view",			noProp, CA_None, 5, 0, 1, 1, 0},
#endif
	EndOfCmds
    };

    menuCmds[1].prop = createFormatMenu(camera);

    return menuCmds;
}

inline CmdDef*
createCaptureCmds()
{
    static float	prop[6][3];
    static CmdDef	captureCmds[] =
    {
	{C_ToggleButton, c_ContinuousShot, 0,
	 "Continuous shot",		noProp,  CA_None,     0, 0, 1, 1, 0},
	{C_Button, c_OneShot,		0,
	 "One shot",			noProp,  CA_None,     0, 1, 1, 1, 0},
	{C_ToggleButton,  c_DoHorizontalBackMatch,	0,
	 "Hor. back match",		noProp,  CA_None,     5, 0, 1, 1, 0}, 
	{C_ToggleButton,  c_DoVerticalBackMatch,	0,
	"Ver. back match",		noProp,  CA_None,     6, 0, 1, 1, 0},
	{C_ToggleButton,c_Binocular,	0,
	 "Binocular",			noProp,  CA_None,     1, 0, 1, 1, 0},
	{C_Label, c_Cursor,		0,
	 "(   ,   )",			noProp,  CA_None,     2, 0, 1, 1, 0},
	{C_Label, c_DisparityLabel,	0,
	 "Disparity:",			noProp,  CA_NoBorder, 1, 1, 1, 1, 0},
	{C_Label, c_Disparity,		0,
	 "     ",			noProp,  CA_None,     2, 1, 1, 1, 0},
	{C_Label, c_DepthRange,		0,
	 "",				noProp,	 CA_NoBorder, 0, 8, 3, 1, 0},
	{C_Slider, c_WindowSize,	0,
	 "Window size",			prop[0], CA_None,     0, 2, 3, 1, 0},
	{C_Slider, c_DisparitySearchWidth,	0,
	 "Disparity search width",	prop[1], CA_None,     0, 3, 3, 1, 0},
	{C_Slider, c_DisparityMax,	0,
	 "Maximum disparity",		prop[2], CA_None,     0, 4, 3, 1, 0},
	{C_Slider, c_DisparityInconsistency,	0,
	 "Disparity inconsistency",	prop[3], CA_None,     0, 5, 3, 1, 0},
	{C_Slider, c_IntensityDiffMax,	0,
	 "Maximum intensity diff.",	prop[4], CA_None,     0, 6, 3, 1, 0},
	{C_Slider, c_Regularization,	0,
	 "Regularization",		prop[5], CA_None,     0, 7, 3, 1, 0},
	EndOfCmds
    };
    
  // Window size
    prop[0][0]  = 3;
    prop[0][1]  = 31;
    prop[0][2]  = 1;

  // Disparity search width
    prop[1][0]  = 16;
    prop[1][1]  = 192;
    prop[1][2]  = 1;

  // Max. disparity
    prop[2][0]  = 48;
    prop[2][1]  = 192;
    prop[2][2]  = 1;

  // Disparity inconsistency
    prop[3][0]  = 0;
    prop[3][1]  = 20;
    prop[3][2]  = 1;

  // Max. intensity diff.
    prop[4][0]  = 0;
    prop[4][1]  = 100;
    prop[4][2]  = 1;
    
  // Regularization
    prop[5][0]  = 1;
    prop[5][1]  = 255;
    prop[5][2]  = 1;

    return captureCmds;
}

/************************************************************************
*  class MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>			*
************************************************************************/
template <class STEREO, class CAMERAS, class PIXEL=u_char, class DISP=float>
class MyCmdWindow : public CmdWindow
{
  public:
    typedef STEREO			stereo_type;
    typedef PIXEL			pixel_type;
    typedef DISP			disparity_type;

  private:
    typedef typename STEREO::Parameters	params_type;

  public:
    MyCmdWindow(App&			parentApp,
#if defined(DISPLAY_3D)
		const XVisualInfo*	vinfo,
		bool			textureMapping,
		double			parallax,
#endif
		CAMERAS&		cameras,
		const params_type&	params,
		double			scale,
		bool			sync)				;

    virtual void	callback(CmdId, CmdVal)				;
    virtual void	tick()						;
    
  private:
    void		restoreCalibration()				;
    void		initializeRectification()			;
    void		stopContinuousShotIfRunning()			;
    void		stereoMatch()					;
#if defined(DISPLAY_2D)
    void		scaleDisparity()				;
#endif
    void		putThreeD(std::ostream& out)		const	;
#if defined(DISPLAY_3D)
    void		putThreeDImage(std::ostream& out)	const	;
#endif

  private:
  // Stereo stuffs.
    CAMERAS&			_cameras;
    const double		_initialWidth;
    const double		_initialHeight;
    const double		_scale;
    const bool			_sync;
    Rectify			_rectify;
    stereo_type			_stereo;
    size_t			_nimages;
    Image<pixel_type>		_images[3];
    Image<pixel_type>		_rectifiedImages[3];
    Image<disparity_type>	_disparityMap;

  // GUI stuffs.
    float			_b;
    CmdPane			_menuCmd;
    CmdPane			_captureCmd;
    CmdPane			_featureCmd;
#if defined(DISPLAY_2D)
    MyCanvasPane<pixel_type>	_canvasL;
#  if !defined(NO_RV)
    MyCanvasPane<pixel_type>	_canvasR;
    MyCanvasPane<pixel_type>	_canvasV;
#  endif
    Image<u_char>		_disparityMapUC;
    MyCanvasPane<u_char>	_canvasD;
#endif
#if defined(DISPLAY_3D)
    const double		_parallax;
#  if defined(DEMO)
    MyOglWindow<pixel_type>	_window3D;
#  else
    MyOglCanvasPane<disparity_type, pixel_type>	_canvas3D;
#  endif
#endif
    Timer			_timer;
};

/************************************************************************
*  class MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>			*
************************************************************************/
template <class STEREO, class CAMERAS, class PIXEL, class DISP>
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::MyCmdWindow(App&	 parentApp,
#if defined(DISPLAY_3D)
					      const XVisualInfo* vinfo,
					      bool		 textureMapping,
					      double		 parallax,
#endif
					      CAMERAS&		 cameras,	
					      const params_type& params,
					      double		 scale,
					      bool		 sync)
    :CmdWindow(parentApp, "Real-time stereo vision using IIDC cameras",
#if defined(DISPLAY_3D) && !defined(DEMO)
	       vinfo,
#endif
	       Colormap::RGBColor, 256, 0, 0),
   // Stereo stuffs.
     _cameras(cameras),
     _initialWidth(_cameras[0].width()),
     _initialHeight(_cameras[0].height()),
     _scale(scale),
     _sync(sync),
     _rectify(),
     _stereo(params),
     _nimages(_cameras.size()),
   // GUI stuffs.
     _b(0.0),
     _menuCmd(*this, createMenuCmds(_cameras[0])),
     _captureCmd(*this, createCaptureCmds()),
     _featureCmd(*this, createFeatureCmds(_cameras[0], _cameras.size())),
#if defined(DISPLAY_2D)
     _disparityMapUC(),
     _canvasL(*this, 320, 240, _rectifiedImages[0]),
#  if !defined(NO_RV)
     _canvasR(*this, 320, 240, _rectifiedImages[1]),
     _canvasV(*this, 320, 240, _rectifiedImages[2]),
#  endif
     _disparityMap(),
     _canvasD(*this, 320, 240, _disparityMapUC),
#endif
#if defined(DISPLAY_3D)
     _parallax(parallax),
#  if defined(DEMO)
     _window3D(*this, vinfo, 640, 480, _disparityMap,
	       (textureMapping ? _images[0] : _rectifiedImages[0]),
	       (textureMapping ? &_rectify.warp(0) : 0)),
#  else
     _canvas3D(*this, 640, 480, _disparityMap,
	       (textureMapping ? _images[0] : _rectifiedImages[0]),
	       (textureMapping ? &_rectify.warp(0) : 0)),
#  endif
#endif
     _timer(*this, 0)
{
    using namespace	std;
    
    _menuCmd.place(0, 0, 2, 1);
    _captureCmd.place(0, 1, 1, 1);
    _featureCmd.place(1, 1, 1, 1);
#if defined(DISPLAY_2D)
    _canvasL.place(0, 3, 1, 1);
#  if !defined(NO_RV)
    _canvasR.place(1, 3, 1, 1);
    _canvasV.place(0, 2, 1, 1);
    _canvasD.place(1, 2, 1, 1);
#  else
    _canvasD.place(0, 2, 1, 1);
#  endif
#endif

#if defined(DISPLAY_3D) && !defined(DEMO)
#  if defined(DISPLAY_2D)
#    if !defined(NO_RV)
    _canvas3D.place(2, 2, 1, 2);
#    else
    _canvas3D.place(1, 2, 1, 2);
#  endif
#  else
    _canvas3D.place(0, 2, 2, 1);
#  endif
#endif

    refreshFeatureCmds(_cameras, _featureCmd);
    
    show();

#if defined(DISPLAY_2D)
    _canvasL.setZoom(0.5);
#  if !defined(NO_RV)
    _canvasR.setZoom(0.5);
    _canvasV.setZoom(0.5);
#  endif    
    _canvasD.setZoom(0.5);
#endif

#if defined(COLOR)
  // カラー画像の場合は，フォーマットをYUV422とし基準カメラ以外の画像サイズを半分にする．
    for (size_t i = 0; i < cameras.size(); ++i)
	_cameras[i].setFormatAndFrameRate((i == 0 ?
					   IIDCCamera::YUV422_640x480 :
					   IIDCCamera::YUV422_320x240),
					   IIDCCamera::FrameRate_30);
#endif

  // ステレオマッチング処理のためのパラメータをGUIに表示．
    const params_type&	p = _stereo.getParameters();
    _captureCmd.setValue(c_DoHorizontalBackMatch, p.doHorizontalBackMatch);
    _captureCmd.setValue(c_DoVerticalBackMatch, p.doVerticalBackMatch);
    _captureCmd.setValue(c_WindowSize, int(p.windowSize));
    _captureCmd.setValue(c_DisparitySearchWidth, int(p.disparitySearchWidth));
    _captureCmd.setValue(c_DisparityMax, int(p.disparityMax));
    _captureCmd.setValue(c_DisparityInconsistency,
			 int(p.disparityInconsistency));
    _captureCmd.setValue(c_IntensityDiffMax, int(p.intensityDiffMax));
    _captureCmd.setValue(c_Regularization, Epsilon<stereo_type>().get(p));
#if defined(DISPLAY_3D)
    _canvas3D.setParallax(_menuCmd.getValue(c_StereoView) ? _parallax : -1.0);
#endif
}

template <class STEREO, class CAMERAS, class PIXEL, class DISP> void
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::callback(CmdId id, CmdVal val)
{
    using namespace	std;
    
    static int		u_prev, v_prev;

    try
    {
	if (setFormat(_cameras, id, val, *this))
	{
	    refreshFeatureCmds(_cameras, _featureCmd);
	    return;
	}
	else if (setFeature(_cameras, id, val, _featureCmd))
	    return;
	
	switch (id)
	{
	  case M_Exit:
	    stopContinuousShotIfRunning();
	    app().exit();
	    break;

	  case M_Open:
	  {
	    stopContinuousShotIfRunning();

	    FileSelection	fileSelection(*this);
	    ifstream		in;
	    if (fileSelection.open(in))
	    {
		_rectifiedImages[2] = 0;
	    
		for (_nimages = 0; _nimages < 3; ++_nimages)
		    if (!_images[_nimages].restore(in))
			break;
		initializeRectification();
		stereoMatch();
	    }
	  }
	    break;
      
	  case M_Save:
	  {
#if defined(DIRECT_CAPTURE)
	    Notify	notify(*this);
	    notify << "Cannot save images when using IIDCCamera::captureDirectry()!!";
	    notify.show();
#else
	    stopContinuousShotIfRunning();

	    FileSelection	fileSelection(*this);
	    ofstream		out;
	    if (fileSelection.open(out))
	    {
		size_t	nimages = (_captureCmd.getValue(c_Binocular) ? 2 : 3);
		for (size_t i = 0; i < nimages; ++i)
		    _images[i].save(out);
	    }
#endif
	  }
	    break;
      
	  case c_SaveRectifiedImages:
	  {
	    stopContinuousShotIfRunning();

	    FileSelection	fileSelection(*this);
	    ofstream		out;
	    if (fileSelection.open(out))
	    {
		size_t	nimages = (_captureCmd.getValue(c_Binocular) ? 2 : 3);
		for (size_t i = 0; i < nimages; ++i)
		    _rectifiedImages[i].save(out);
	    }
	  }
	    break;
      
	  case c_SaveThreeD:
	  {
	    stopContinuousShotIfRunning();

	    FileSelection	fileSelection(*this);
	    ofstream		out;
	    if (fileSelection.open(out))
		putThreeD(out);
	  }
	    break;
#if defined(DISPLAY_3D)
	  case c_SaveThreeDImage:
	  {
	    stopContinuousShotIfRunning();

	    FileSelection	fileSelection(*this);
	    ofstream		out;
	    if (fileSelection.open(out))
		putThreeDImage(out);
	  }
	    break;
#endif
	  case c_SaveConfig:
	  {
	    stopContinuousShotIfRunning();

	    ofstream	out(_cameras.configFile().c_str());
	    if (!out)
		throw runtime_error("Failed to open camera configuration file!!");
	    out << _cameras;
	  }
	    break;

	  case c_SaveMatrices:
	  {
	      FileSelection	fileSelection(*this);
	      ofstream		out;
	      if (fileSelection.open(out))
	      {
		  for (size_t i = 0; i < _nimages; ++i)
		      out << _rectifiedImages[i].P;
	      }
	  }
	    break;

	  case c_ContinuousShot:
	    if (val)
	    {
		restoreCalibration();
		initializeRectification();
		for (auto& camera : _cameras)
		    camera.continuousShot(true);
		_timer.start(1);
	    }
	    else
	    {
		_timer.stop();
		for (auto& camera : _cameras)
		    camera.continuousShot(false);
	    }
	    break;
#ifdef __TU_IIDCPP_H
	  case c_OneShot:
	    stopContinuousShotIfRunning();
	    restoreCalibration();
	    initializeRectification();
	    for (auto& camera : _cameras)
		camera.oneShot();
	    for (auto& camera : _cameras)
		camera.snap();			// カメラに画像取り込みを指示．
	    for (size_t i = 0; i < _cameras.size(); ++i)
		_cameras[i] >> _images[i];	// カメラから画像転送．
	    stereoMatch();
	    break;
#endif
	  case c_Binocular:
	    stopContinuousShotIfRunning();
	    initializeRectification();
	    stereoMatch();
	    break;
	
	  case c_DoHorizontalBackMatch:
	  {
	    params_type	params = _stereo.getParameters();
	    params.doHorizontalBackMatch = val;
	    _stereo.setParameters(params);
	  }
	    break;
	    
	  case c_DoVerticalBackMatch:
	  {
	    params_type	params = _stereo.getParameters();
	    params.doVerticalBackMatch = val;
	    _stereo.setParameters(params);
	  }
	    break;
	    
	  case c_WindowSize:
	  {
	    params_type	params = _stereo.getParameters();
	    params.windowSize = val;
	    _stereo.setParameters(params);
	  }
	    break;
	
	  case c_DisparitySearchWidth:
	  {
	    params_type	params = _stereo.getParameters();
	    params.disparitySearchWidth = val;
	    _stereo.setParameters(params);
	    initializeRectification();
	    params = _stereo.getParameters();
	    _captureCmd.setValue(c_DisparitySearchWidth,
				 int(params.disparitySearchWidth));
	    _captureCmd.setValue(c_DisparityMax, int(params.disparityMax));
	  }
	    break;
	
	  case c_DisparityMax:
	  {
	    params_type	params = _stereo.getParameters();
	    params.disparityMax = val;
	    _stereo.setParameters(params);
	    initializeRectification();
	    params = _stereo.getParameters();
	    _captureCmd.setValue(c_DisparityMax, int(params.disparityMax));
	  }
	    break;

	  case c_Regularization:
	  {
	    params_type	params = _stereo.getParameters();
	    Epsilon<stereo_type>().set(val, params);
	    _stereo.setParameters(params);
	  }
	    break;

	  case c_DisparityInconsistency:
	  {
	    params_type	params = _stereo.getParameters();
	    params.disparityInconsistency = val;
	    _stereo.setParameters(params);
	  }
	    break;

	  case c_IntensityDiffMax:
	  {
	    params_type	params = _stereo.getParameters();
	    params.intensityDiffMax = val;
	    _stereo.setParameters(params);
	  }
	    break;

#if defined(DISPLAY_2D)
	  case Id_MouseButton1Drag:
	    _canvasL.repaintUnderlay();
#  if !defined(NO_RV)
	    _canvasR.repaintUnderlay();
	    _canvasV.repaintUnderlay();
#  endif
	    _canvasD.repaintUnderlay();
	  case Id_MouseButton1Press:
	  {
	    _canvasL.drawEpipolarLine(val.v());
	    _canvasL.drawEpipolarLineV(val.u());
#  if !defined(NO_RV)
	    _canvasR.drawEpipolarLine(val.v());
	    _canvasV.drawEpipolarLine(val.u());
#  endif
	    _canvasD.drawEpipolarLine(val.v());
	    _canvasD.drawEpipolarLineV(val.u());
	    ostringstream	s;
	    disparity_type	d;
	    if (0 <= val.u() && val.u() < _disparityMap.width()  &&
		0 <= val.v() && val.v() < _disparityMap.height() &&
		(d = _disparityMap[val.v()][val.u()]) != 0)
	    {
		s.precision(4);
		s << d;
		s.precision(4);
		s << " (" << _b / d << "m)";
#  if !defined(NO_RV)
		const int	dc = int(_stereo.getParameters().disparityMax
					 - d + 0.5);
		_canvasR.drawPoint(val.u() + dc, val.v());
		_canvasV.drawPoint(_rectifiedImages[0].height() - 1
				   - val.v() + dc,
				   val.u());
#  endif
#  if defined(DISPLAY_3D)
		_canvas3D.setCursor(val.u(), val.v(), d);
	    }
	    else
		_canvas3D.setCursor(0, 0, 0.0);
	    _canvas3D.repaintUnderlay();
#  else
	    }
#  endif
	    _captureCmd.setString(c_Disparity, s.str().c_str());
	  }
	  
	  case Id_MouseMove:
	  {
	    ostringstream	s;
	    s << '(' << val.u() << ',' << val.v() << ')';
	    _captureCmd.setString(c_Cursor, s.str().c_str());
	    u_prev = val.u();
	    v_prev = val.v();
	  }
	    break;
	
	  case Id_MouseButton1Release:
	    _canvasL.repaintUnderlay();
#  if !defined(NO_RV)
	    _canvasR.repaintUnderlay();
	    _canvasV.repaintUnderlay();
#  endif
	    _canvasD.repaintUnderlay();
#  if defined(DISPLAY_3D)
	    _canvas3D.setCursor(0, 0, 0.0);
	    _canvas3D.repaintUnderlay();
#  endif
	    break;
#endif
#if defined(DISPLAY_3D)
	  case c_DrawMode:
	    switch (val)
	    {
	      case c_Texture:
		_canvas3D.setDrawMode(MyOglCanvasPaneBase<DISP>::Texture);
		_canvas3D.repaintUnderlay();
		break;
	
	      case c_Polygon:
		_canvas3D.setDrawMode(MyOglCanvasPaneBase<DISP>::Polygon);
		_canvas3D.repaintUnderlay();
		break;
	      
	      case c_Mesh:
		_canvas3D.setDrawMode(MyOglCanvasPaneBase<DISP>::Mesh);
		_canvas3D.repaintUnderlay();
		break;
	    }
	    break;
	
	  case c_GazeDistance:
	    _canvas3D.setDistance(1000.0 * val.f());
	    break;

	  case c_SwingView:
	    if (val)
		_canvas3D.resetSwingView();
	    break;

	  case c_StereoView:
	    _canvas3D.setParallax(val ? _parallax : -1.0);
	    _canvas3D.repaintUnderlay();
	    break;
#endif
	}
    }
    catch (exception& err)
    {
	Notify	notify(*this);
	notify << err.what();
	notify.show();
    }
}

template <class STEREO, class CAMERAS, class PIXEL, class DISP> void
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::tick()
{
    countTime();

    if (_sync)
	syncedSnap(_cameras, std::chrono::milliseconds(1));
    else
	for (auto& camera : _cameras)
	    camera.snap();
    
    for (size_t i = 0; i < _cameras.size(); ++i)
#if defined(DIRECT_CAPTURE)
	_cameras[i].captureDirectly(_images[i]);
#else
	_cameras[i] >> _images[i];		// カメラから画像転送．
#endif
    stereoMatch();
}

template <class STEREO, class CAMERAS, class PIXEL, class DISP> void
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::restoreCalibration()
{
    using namespace	std;

    ifstream	in(_cameras.calibFile().c_str());
    if (!in)
	throw runtime_error("Failed to open camera calibration file!!");
    for (_nimages = 0;
	 (_nimages < 3) && (_nimages < _cameras.size()); ++_nimages)
    {
	Image<pixel_type>&	image = _images[_nimages];
	
	in >> image.P >> image.d1 >> image.d2;
	image.resize(_cameras[_nimages].height(), _cameras[_nimages].width());
	image.P[0] *= (image.width()  / _initialWidth);
	image.P[1] *= (image.height() / _initialHeight);
    }
}

template <class STEREO, class CAMERAS, class PIXEL, class DISP> void
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::initializeRectification()
{
    using namespace	std;
    
    if (_nimages < 2)
	throw runtime_error("Two or more images needed!!");
    if (_nimages == 2)
	_captureCmd.setValue(c_Binocular, 1);
	
    if (_captureCmd.getValue(c_Binocular))
    {
	_rectify.initialize(_images[0], _images[1],
			    _scale,
			    _stereo.getParameters().disparitySearchWidth,
			    _stereo.getParameters().disparityMax);
#if defined(DISPLAY_2D) && !defined(NO_RV)
	_rectifiedImages[2] = 0;
	_canvasV.repaintUnderlay();
#endif
    }
    else
    {
	_rectify.initialize(_images[0], _images[1], _images[2],
			    _scale,
			    _stereo.getParameters().disparitySearchWidth,
			    _stereo.getParameters().disparityMax);
	_rectifiedImages[2].P  = _rectify.H(2) * _images[2].P;
	_rectifiedImages[2].P /= length(slice(_rectifiedImages[2].P[2], 0, 3));
#if defined(DISPLAY_2D) && !defined(NO_RV)
	_canvasV.resize(align16(_rectify.width(2)),
			align16(_rectify.height(2)));
#endif
    }
    _disparityMap.resize(_rectify.height(0), _rectify.width(0));
    
    _rectifiedImages[0].P  = _rectify.H(0) * _images[0].P;
    _rectifiedImages[0].P /= length(slice(_rectifiedImages[0].P[2], 0, 3));
    _disparityMap.P = _rectifiedImages[0].P;
    _rectifiedImages[1].P  = _rectify.H(1) * _images[1].P;
    _rectifiedImages[1].P /= length(slice(_rectifiedImages[1].P[2], 0, 3));
#if defined(DISPLAY_2D)
    _canvasL.resize(align16(_rectify.width(0)), align16(_rectify.height(0)));
#  if !defined(NO_RV)
    _canvasR.resize(align16(_rectify.width(1)), align16(_rectify.height(1)));
#  endif
    _canvasD.resize(align16(_rectify.width(0)), align16(_rectify.height(0)));
#endif
#if defined(DISPLAY_3D)
    _canvas3D.resize(_rectify.width(0), _rectify.height(0));
    _canvas3D.initialize(_rectifiedImages[0].P, _rectifiedImages[1].P,
			 1.0 / _scale);
#endif

  // Display depth range of measurement.
    const Matrix34d&	Pr = _rectifiedImages[1].P;
    Vector4d		tR;
    tR[0] = -Pr[0][3];
    tR[1] = -Pr[1][3];
    tR[2] = -Pr[2][3];
    tR[3] = 1.0;
  // the right camera center    
    solve(transpose(slice(Pr, 0, 3, 0, 3)), slice(tR, 0, 3));
    
    const Matrix34d&	Pl = _rectifiedImages[0].P;
    _b = (Pl[0]*tR) / length(slice(Pl[2], 0, 3)) / 1000;

    float	range[3];
    range[0] = _b / _stereo.getParameters().disparityMax;
    range[1] = _b / _stereo.getParameters().disparityMin();
    range[2] = 0;
    _menuCmd.setProp(c_GazeDistance, range);

    std::ostringstream	s;
    s.precision(3);
    s << "Depth range: " << _b / _stereo.getParameters().disparityMax
      << " -- "		 << _b / _stereo.getParameters().disparityMin()
      << "(m)";
    _captureCmd.setString(c_DepthRange, s.str().c_str());

    std::cerr << "--- Stereo matching parameters ---\n";
    _stereo.getParameters().put(std::cerr);
}

template <class STEREO, class CAMERAS, class PIXEL, class DISP> void
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::stopContinuousShotIfRunning()
{
    if (_captureCmd.getValue(c_ContinuousShot))
    {
	_timer.stop();
	for (auto& camera : _cameras)
	    camera.continuousShot(false);
	_captureCmd.setValue(c_ContinuousShot, 0);
    }
}

template <class STEREO, class CAMERAS, class PIXEL, class DISP> void
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::stereoMatch()
{
    if (_captureCmd.getValue(c_Binocular))
    {
	_rectify(_images[0], _images[1],
		 _rectifiedImages[0], _rectifiedImages[1]);
	_stereo(_rectifiedImages[0].cbegin(), _rectifiedImages[0].cend(),
		_rectifiedImages[1].cbegin(), _disparityMap.begin());
    }
    else
    {
	_rectify(_images[0], _images[1], _images[2],
		 _rectifiedImages[0], _rectifiedImages[1], _rectifiedImages[2]);
	_stereo(_rectifiedImages[0].cbegin(), _rectifiedImages[0].cend(),
		_rectifiedImages[0].cend(),
		_rectifiedImages[1].cbegin(), _rectifiedImages[2].cbegin(),
		_disparityMap.begin());
#if defined(DISPLAY_2D) && !defined(NO_RV)
	_canvasV.repaintUnderlay();	// rectifyされた上画像を表示．
#endif
    }
#if defined(DISPLAY_2D)
    _canvasL.repaintUnderlay();		// rectifyされた左画像を表示．
#  if !defined(NO_RV)
    _canvasR.repaintUnderlay();		// rectifyされた右画像を表示．
#  endif
    scaleDisparity();
    _canvasD.repaintUnderlay();		// 計算された視差画像を表示．
#endif
#if defined(DISPLAY_3D)
    _canvas3D.repaintUnderlay();	// 3次元復元結果を表示．
    if (_menuCmd.getValue(c_SwingView))
	_canvas3D.swingView();
#endif
}

#if defined(DISPLAY_2D)
template <class STEREO, class CAMERAS, class PIXEL, class DISP> void
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::scaleDisparity()
{
    const float	s = 255.0 / _stereo.getParameters().disparityMax;
    _disparityMapUC.resize(_disparityMap.height(), _disparityMap.width());

    for (int v = 0; v < _disparityMap.height(); ++v)
    {
	const disparity_type*	src = _disparityMap[v].begin();
	u_char*			dst = _disparityMapUC[v].begin();
	u_char* const		end = dst + _disparityMapUC.width();
#if 0
      //#if defined(SSE)
	using namespace	mm;
	
	const F32vec	s2(s);
	for (u_char* const
		 end2 = dst + Iu8vec::size*((end - dst)/Iu8vec::size);
	     dst < end2; )
	{
#  if defined(SSE2)
	    store<false>(dst,
			 cvt<u_char>(
			     cvt<short>(
				 cvt<int>(s2 * load<false>(src)),
				 cvt<int>(s2 *
					  load<false>(src + F32vec::size))),
			     cvt<short>(
				 cvt<int>(s2 *
					  load<false>(src + 2*F32vec::size)),
				 cvt<int>(s2 *
					  load<false>(src + 3*F32vec::size)))));
	    src += 4*F32vec::size;
#  else
	    store<false>(dst,
			 cvt<u_char>(
			     cvt<short>(s2 * load<false>(src)),
			     cvt<short>(s2 *
					load<false>(src + F32vec::size))));
	    src += 2*F32vec::size;
#  endif
	    dst += Iu8vec::size;
	}
	mm::empty();
#endif
	while (dst < end)
	    *dst++ = s * *src++;
    }
}
#endif

template <class STEREO, class CAMERAS, class PIXEL, class DISP> void
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::putThreeD(std::ostream& out) const
{
    using namespace	std;

  // Put header.
    int	npoints = 0;
    for (int v = 0; v < _disparityMap.height(); ++v)
	for (int u = 0; u < _disparityMap.width(); ++u)
	    if (_disparityMap[v][u] != 0.0)
		++npoints;
    const Matrix34d&	P = _rectifiedImages[0].P;
    out << "PX" << endl
	<< "# PinHoleParameterH11: " << P[0][0] << endl
	<< "# PinHoleParameterH12: " << P[0][1] << endl
	<< "# PinHoleParameterH13: " << P[0][2] << endl
	<< "# PinHoleParameterH14: " << P[0][3] << endl
	<< "# PinHoleParameterH21: " << P[1][0] << endl
	<< "# PinHoleParameterH22: " << P[1][1] << endl
	<< "# PinHoleParameterH23: " << P[1][2] << endl
	<< "# PinHoleParameterH24: " << P[1][3] << endl
	<< "# PinHoleParameterH31: " << P[2][0] << endl
	<< "# PinHoleParameterH32: " << P[2][1] << endl
	<< "# PinHoleParameterH33: " << P[2][2] << endl
	<< "# PinHoleParameterH34: " << P[2][3] << endl
	<< _disparityMap.width() << ' ' << _disparityMap.height()
	<< '\n' << npoints << endl;

  // Put the 2D image coordinates, pixel intensity and the 3D coordinates.
    ComputeThreeD	toThreeD(_rectifiedImages[0].P, _rectifiedImages[1].P);
    for (int v = 0; v < _disparityMap.height(); ++v)
	for (int u = 0; u < _disparityMap.width(); ++u)
	    if (_disparityMap[v][u] != 0.0)
	    {
		const Point3d&	x = toThreeD(u, v, _disparityMap[v][u]);
		out << u << ' ' << v
		    << '\t' << int(_rectifiedImages[0][v][u])
		    << '\t' << x;
	    }
}

#if defined(DISPLAY_3D)
template <class STEREO, class CAMERAS, class PIXEL, class DISP> void
MyCmdWindow<STEREO, CAMERAS, PIXEL, DISP>::putThreeDImage(std::ostream& out) const
{
    const Image<RGB>&	threeDImage = _canvas3D.template getImage<RGB>();
    
    threeDImage.save(out);
}
#endif
}
}
