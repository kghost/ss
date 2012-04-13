/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/* vim: set ts=4 sw=4 tw=0: */
/*
 * parser.cc
 * Copyright (C) 2012 Zang MingJie <zealot0630@gmail.com>
 * 
 * ss is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ss is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>

#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include "parser.h"
#include "executor.h"

template <typename Iterator>
struct Grammar : boost::spirit::qi::grammar<Iterator, std::vector<std::string>()>
{
	Grammar() : Grammar::base_type(line) {
		using boost::spirit::qi::lexeme;
		using boost::spirit::omit;
		using boost::spirit::standard_wide::char_;
		using boost::spirit::standard_wide::string;
		using boost::spirit::standard_wide::space;
		using namespace boost::spirit::qi::labels;

		escape = omit[char_('\\')] >> char_;
		single_quoted = '\'' >> +(char_ - '\'') >> '\'';
		quoted = '"' >> +(escape | (char_ - '\"' - '\\')) >> '"';
		lit = +(escape | (char_ - space - '\"' - '\'' - '\\'));

		parts = +(lit | quoted | single_quoted);
		text = +parts;
		line = omit[*space] >> text % space >> omit[*space];
	}

	boost::spirit::qi::rule<Iterator, std::vector<std::string>()> line;
	boost::spirit::qi::rule<Iterator, std::string()> text;
	boost::spirit::qi::rule<Iterator, std::string()> parts;
	boost::spirit::qi::rule<Iterator, std::string()> lit;
	boost::spirit::qi::rule<Iterator, std::string()> quoted;
	boost::spirit::qi::rule<Iterator, std::string()> single_quoted;
	boost::spirit::qi::rule<Iterator, boost::spirit::char_encoding::standard_wide::char_type()> escape;
};

#include <iterator>
#include <algorithm>

Parser::Parser() : executor(new Executor()), grammar(new Grammar<std::string::const_iterator>()) {}

void Parser::operator() (const std::string & input) {
	using boost::spirit::standard_wide::char_;
	using boost::spirit::standard_wide::space;
	std::vector<std::string> out;
	std::string::const_iterator begin = input.begin();
	std::string::const_iterator end = input.end();
	bool r = boost::spirit::qi::parse(begin, end, *grammar, out);
	if (r && begin == end) {
		(*executor)(out);
	} else {
		std::string::const_iterator some = begin+30;
		std::string context(begin, (some>end)?end:some);
		std::cout << "Syntax error at: \"" << context << '"' << std::endl;
	}
}
