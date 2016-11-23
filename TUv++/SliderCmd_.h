/*
 *  平成14-19年（独）産業技術総合研究所 著作権所有
 *  
 *  創作者：植芝俊夫
 *
 *  本プログラムは（独）産業技術総合研究所の職員である植芝俊夫が創作し，
 *  （独）産業技術総合研究所が著作権を所有する秘密情報です．著作権所有
 *  者による許可なしに本プログラムを使用，複製，改変，第三者へ開示する
 *  等の行為を禁止します．
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
 *  without permission by the copyright holder are strictly prohibited.
 *
 *  [No Warranty.]
 *  The copyright holder or the creator are not responsible for any
 *  damages caused by using this program.
 *
 *  $Id$  
 */
#ifndef __VSLIDERCMD_H
#define __VSLIDERCMD_H

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class SliderCmd							*
************************************************************************/
class SliderCmd : public Cmd
{
  public:
    SliderCmd(Object& parentObject, const CmdDef& cmd)		;
    virtual ~SliderCmd()					;

    virtual const Widget&	widget()		const	;

    virtual CmdVal		getValue()		const	;
    virtual void		setValue(CmdVal val)		;
    virtual void		setProp(const void* prop)	;
    void			setPercent(float percent)	;
    
  private:
    void			setValueInternal(float val)	;

    const Widget	_widget;			// gridboxWidget
    const Widget	_title;				// labelWidget
    const Widget	_slider;			// slider3dWidget
    const Widget	_text;				// labelWidget
    float		_min;
    float		_max;
    float		_step;
    CmdVal		_val;
};

}
}
#endif	// !__VSLIDERCMD_H
