/***************************************************************************
                               mgap.hpp
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

#ifndef MGAP_HPP
#define MGAP_HPP

#include "element.hpp"

class Mgap final : public Element {
private :
	std::string const m_descriptor="microstrip_gap";
	long double m_w1;
	long double m_w2;
	long double m_s;
	std::string m_net1;
	std::string m_net2;
public :
	Mgap(std::string _label,
			std::string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			std::string _subst,
			long double _w1,
			long double _w2,
			long double _s);
	~Mgap();
	std::string getDescriptor(void) override;
	long double getW1(void) override;
	long double getW2(void) override;
	long double getS(void) override;
	std::string getNet1(void) override;
	std::string getNet2(void) override;
	void getStep(int const _net, long double& xstep, long double& ystep) override;
	void getEdge(int const _net, long double& edge, short& dir) override;
	bool isOemsMeshInterface(int const _port, long double const _w) override;
	int setNet1(std::string _net1) override;
	int setNet2(std::string _net2) override;
};

#endif // MGAP_HPP
