/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/* vim: set ts=4 sw=4 tw=0: */
/*
 * input.cc
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

#include "input.h"

ReadLineInput ReadLineInput::end() {
	return ReadLineInput(0);
}

bool ReadLineInput::equal(const ReadLineInput &that) const
{
	return (this == &that) || (eof == true && that.eof == true);
}

void ReadLineInput::increment() {
	if (eof) throw "EOF";

	/* Get a line from the user. */
	char *line_read = readline (prompt().c_str());

#ifdef HAVE_READLINE_HISTORY
	/* If the line has any text in it,
	 *      save it on the history. */
	if (line_read && *line_read && (!line || line->compare(line_read) != 0))
		add_history (line_read);
#endif
	if (line_read == NULL) {
		eof = true;
		line.reset();
	} else
		line.reset(new std::string(line_read));
}
