/***************************************************************************
                               mgap.cpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "mgap.hpp"
using namespace std;

Mgap::Mgap(string _label,
			string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			string _subst,
			long double _w1,
			long double _w2,
			long double _s) :
	Element(_label, _type, _active, _mirrorx, _r, 2, _subst),
	m_w1(_w1),
	m_w2(_w2),
	m_s(_s)
	{}

Mgap::~Mgap() {
	}

string Mgap::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mgap::getW1(void) {
	return(m_w1);
	}

long double Mgap::getW2(void) {
	return(m_w2);
	}

long double Mgap::getS(void) {
	return(m_s);
	}

string Mgap::getNet1(void) {
	return(m_net1);
	}

string Mgap::getNet2(void) {
	return(m_net2);
	}

int Mgap::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mgap::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

void Mgap::getStep(int const _net, long double& xstep, long double& ystep) {
	if(m_r==0) {
		if(_net==1) {
			xstep= - m_s/2;
			ystep=0;
		} else if(_net==2) {
			xstep= + m_s/2;
			ystep=0;
			}
	} else if(m_r==90) {
		if(_net==1) {
			xstep=0;
			ystep= + m_s/2;
		} else if(_net==2) {
			xstep=0;
			ystep= - m_s/2;
			}
	} else if(m_r==180) {
		if(_net==1) {
			xstep= + m_s/2;
			ystep=0;
		} else if(_net==2) {
			xstep= - m_s/2;
			ystep=0;
			}
	} else if(m_r==270) {
		if(_net==1) {
			xstep=0;
			ystep= - m_s/2;
		} else if(_net==2) {
			xstep=0;
			ystep= + m_s/2;
			}
		}
	}

void Mgap::getEdge(int const _net, long double& edge, short& dir) {
	if(_net==1) {
		edge=m_w1;
		switch(m_r) {
			case 0: dir=XMIN; break;
			case 90: dir=YMAX; break;
			case 180: dir=XMAX; break;
			case 270: dir=YMIN; break;
			}
	} else if(_net==2) {
		edge=m_w2;
		switch(m_r) {
			case 0: dir=XMAX; break;
			case 90: dir=YMIN; break;
			case 180: dir=XMIN; break;
			case 270: dir=YMAX; break;
			}
		}
	}

bool Mgap::isOemsMeshInterface(int const _port, long double const /*_w*/) {
	if(_port==1 || _port==2) {
		return(true);
	} else {
		return(false);
		}
	}
