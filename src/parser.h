/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/* vim: set ts=4 sw=4 tw=0: */
/*
 * parser.h
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

#ifndef PARSER_H
#define PARSER_H

#include <boost/shared_ptr.hpp>

template <typename Iterator> struct Grammar;
class Executor;

class Parser {
	public:
		Parser();
		void operator() (const std::string & input);
	private:
		boost::shared_ptr<Executor> executor;
		boost::shared_ptr<Grammar<std::string::const_iterator> > grammar;
};

#endif /* end of include guard: PARSER_H */
