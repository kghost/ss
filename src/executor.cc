/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/* vim: set ts=4 sw=4 tw=0: */
/*
 * executor.cc
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

#include "executor.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>

void Executor::operator() (const std::vector<std::string> & input) {
	if (input.size() == 0) {
		return;
	} else if (input[0] == "cd" && input.size() == 2) {
		if (chdir(input[1].c_str()) < 0) perror(input[0].c_str());
	} else if (input[0] == "export" && input.size() == 2) {
		if (unsetenv(input[1].c_str()) < 0) perror(input[0].c_str());
	} else if (input[0] == "export" && input.size() == 3) {
		if (setenv(input[1].c_str(), input[2].c_str(), true) < 0) perror(input[0].c_str());
	} else {
		int pid = fork();
		if (pid < 0) {
			perror(input[0].c_str());
		} else if (pid == 0) {
			char* argv[input.size()+1];
			argv[input.size()] = NULL;
			std::transform(input.begin(), input.end(), argv,
					[](const std::string & i) { return const_cast<char*>(i.c_str()); });
			execvp(argv[0], argv);
			perror(input[0].c_str());
			exit(-1);
		} else if (pid > 0) {
			int status = 0;
			if (waitpid(pid, &status, 0) < 0)
				perror("waitpid");
		}
	}
}
