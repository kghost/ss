/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/* vim: set ts=4 sw=4 tw=0: */
/*
 * input.h
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
#ifndef INPUT_H
#define INPUT_H

#include <config.h>

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/iterator/iterator_facade.hpp>

#ifdef HAVE_READLINE_H
#include <readline.h>
#elif defined(HAVE_READLINE_READLINE_H)
#include <readline/readline.h>
#endif

#ifdef HAVE_READLINE_HISTORY_H
#include <readline/history.h>
#endif

#include "prompt.h"

class ReadLineInput : public boost::iterator_facade<ReadLineInput, std::string, boost::incrementable_traversal_tag> {
	public:
		ReadLineInput() : line(), eof(false) {
			increment();
		}
		ReadLineInput(const ReadLineInput &that) : line(that.line), eof(that.eof) {}
		static ReadLineInput end();
	private:
		ReadLineInput(int) : line(), eof(true) {}

		friend class boost::iterator_core_access;
		bool equal(const ReadLineInput &that) const;
		void increment();
		std::string & dereference() const {
			return *line.get();
		}

		Prompt prompt;
		boost::shared_ptr<std::string> line;
		bool eof;
};

#endif /* end of include guard: INPUT_H */
