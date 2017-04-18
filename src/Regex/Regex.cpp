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
 * @file
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 4/18/17.
 * 
 * @brief
 *
 * # Description
 * 
 * # TODO
 * 
 *
 */
//</editor-fold>
#include <iostream>
#include "Regex.h"
#include "RegexErrors.h"

namespace Regex {

    Regex::Regex(std::string pattern) {
        pattern_ = pattern;

        try
        {
            compile();
        } catch (InvalidRegexError e)
        {
            std::cout << "Invalid regular expression with pattern: " + pattern;
            throw e;
        }

    }

    void Regex::compile() {
        try
        {
            parser.parse(pattern_);
        } catch (ParserError e)
        {
            throw InvalidRegexError();
        }

        nfa_ = parser.getBuiltNFA();
    }

    bool Regex::match(std::string str) {
        return nfa_.match(str);
    }

    Regex::Regex() {
        pattern_ = "";
    }

    void Regex::setPattern(std::string pattern) {
        pattern_ = pattern;
        compile();
    }
}
