//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 4/18/17 Carlos Brito
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.*
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

//<editor-fold desc="Description">
/**
 * @file Regex.h
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 4/18/17.
 *
 */
//</editor-fold>
#ifndef MYREGEX_REGEX_H
#define MYREGEX_REGEX_H

#include <string>
#include "../Automata/NFA.h"
#include "Parser.h"

namespace Regex {

    /**
     * @class Regex
     * @author Carlos Brito (carlos.brito524@gmail.com)
     * @date 4/18/17.
     *
     * @brief Regular expression engine clcass
     *
     * # Description
     * It parses regular expressions.
     *
     * # TODO
     * Many many things.
     *
     */
    class Regex {
        std::string pattern_;
        Automata::NFA nfa_;
        Parser parser;

    public:
        Regex();
        Regex(std::string pattern);
        void setPattern(std::string pattern);
        bool match(std::string str);

    private:
        void compile();

    };
}

#endif //MYREGEX_REGEX_H
