/***************************************************************************
                               data.cpp
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

#include <iostream>

#include "data.hpp"
using namespace std;

//******************************************************************************
Block::Block(void) :
	elements(vector<shared_ptr<Element>>()),
	subst(shared_ptr<Element>()),
	extrem_pos({0.0, 0.0, 0.0, 0.0}),
	margin(0.0)
	{}

//******************************************************************************
void Block::set_extrem_pos(void) {
	//reset extrem_pos to a random existant point
	for(shared_ptr<Element> it : elements) {
		if(it->getNpoint()) {
			extrem_pos[XMIN]=it->getP(1, X, R, ABS);
			extrem_pos[XMAX]=it->getP(1, X, R, ABS);
			extrem_pos[YMIN]=it->getP(1, Y, R, ABS);
			extrem_pos[YMAX]=it->getP(1, Y, R, ABS);
			break;
			}
		}
	//set extrem_pos
	for(shared_ptr<Element> it : elements) {
		it->setP();
		for(int i=0;i<it->getNpoint();i++) {
			if(it->getP(i, X, R, ABS)<extrem_pos[XMIN]) extrem_pos[XMIN]=it->getP(i, X, R, ABS);
			if(it->getP(i, X, R, ABS)>extrem_pos[XMAX]) extrem_pos[XMAX]=it->getP(i, X, R, ABS);
			if(it->getP(i, Y, R, ABS)<extrem_pos[YMIN]) extrem_pos[YMIN]=it->getP(i, Y, R, ABS);
			if(it->getP(i, Y, R, ABS)>extrem_pos[YMAX]) extrem_pos[YMAX]=it->getP(i, Y, R, ABS);
			}
		}
	//set boundary
	boundary[XMIN]=extrem_pos[XMIN]-margin;
	boundary[XMAX]=extrem_pos[XMAX]+margin;
	boundary[YMIN]=extrem_pos[YMIN]-margin;
	boundary[YMAX]=extrem_pos[YMAX]+margin;
	}

//******************************************************************************
void Block::shift(long double const x, long double const y) {
	for(shared_ptr<Element> it : elements) {
		it->setX(it->getX()+x);
		it->setY(it->getY()+y);
		}
	set_extrem_pos();
	}

//******************************************************************************
void Block::print_extrem_pos(void) {
	cout << "\tXmin : " << extrem_pos[XMIN] << "\n"
	        "\tXmax : " << extrem_pos[XMAX] << "\n"
	        "\tYmin : " << extrem_pos[YMIN] << "\n"
	        "\tYmax : " << extrem_pos[YMAX] << "\n";
	}

//******************************************************************************
void Block::print(void) {
	cout << "Elements :" << endl;
	for(shared_ptr<Element> it : elements) {
		cout << "\t" << it->getLabel() << "\t" << it->getType() << endl;
		}

	cout << "Substrate :" << endl;
	if(subst)
		cout << "\t" << subst->getLabel() << endl;

	cout << "Extrem positions :\n";
	print_extrem_pos();
	cout << endl;
	}

//******************************************************************************
Data::Data(void) :
	extrem_pos({0.0, 0.0, 0.0, 0.0}),
	out_format(".kicad_pcb"),
	export_each_block(false),
	export_each_subst(false),
	keep_tmp_files(false),
	is_volume_error(false),
	subst_margin_factor(10),
	port_default_l(0.2),
	oems_boundary_factor(1),
	oems_highres_div(200),
	oems_metalres_div(60),
	oems_substres_div(30),
	oems_timeres(300000)
	{}

//******************************************************************************
Data::~Data(void) {
	clear();
	}

//******************************************************************************
void Data::clear(void) {
	all_blocks.clear();
	for(shared_ptr<Element> it : tab_all) {
		it->prev=nullptr;
		it->setAdjacent(1, nullptr, 0);
		it->setAdjacent(2, nullptr, 0);
		it->setAdjacent(3, nullptr, 0);
		it->setAdjacent(4, nullptr, 0);
		}
	tab_all.clear();
	extrem_pos.fill(0.0);
	is_volume_error=false;
	volume_error.clear();
	}
