/***************************************************************************
                               parser.hpp
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

#ifndef SCHPARSER_HPP
#define SCHPARSER_HPP

#include <fstream>
#include <initializer_list>
#include <memory>

#include "data.hpp"

#ifdef QRFL_UNITTEST
#define private public
#endif // QRFL_UNITTEST

class SchParser {
private:
	Data& data;

	void parse_port_shift_args(void);
	void parse_port_size_args(void);

	int check_qucsstudio(std::ifstream& f_sch, std::string& n_tmp, bool& is_qucsstudio);
	int generate_netlist(std::string const& n_sch, std::string const& n_net);
	void parse_schematic(std::ifstream& f_sch, std::vector<std::string>& unprintables);
	void parse_netlist(std::ifstream& f_net);
	void warn_unprintable(std::vector<std::string> const& unprintables);
	void rm_tmp_files(std::initializer_list<std::string> args);

	int open_file(std::ifstream& file, std::string const name);
	long double suffix(std::string const s_sci, std::string const s_eng, bool const is_length);
	std::string check_void(std::string const match, std::string const label="");
	std::string mstub_shift(bool const xy, std::string const str, std::string const r);

public:
	SchParser(Data& _data);
	int run(void);
};

#ifdef QRFL_UNITTEST
#undef private
#endif // QRFL_UNITTEST

#endif // SCHPARSER_HPP
