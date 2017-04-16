//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/23/17 Carlos Brito
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
 * @file TokenDecls.h
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 3/22/17
 *
 * # Description
 * This file contains the declaration of tokens and token tags.
 *
 * - We have instanced some of the fixed tokens which we already
 * know will appear like LPAREN and KLEENE_STAR.
 *
 * - We have instanced token tags which will aid in creating new tokens.
 *
 * # TODO
 * Nothing for the moment.
 */
//</editor-fold>

#ifndef MYREGEX_REGEXPTOKENS_H
#define MYREGEX_REGEXPTOKENS_H

#include "Token.h"

namespace Regex {

/**
 * @brief This type aids in defining the ids for the Token Tags
 *
 * # Description
 * In order to get unique ids, we use an enum structure to assign
 * each of the tokens an id.
 */
enum {
    TOK_EOF = -1,
    TOK_NONE = 0,

    TOK_LPAREN,
    TOK_RPAREN,
    TOK_KLEENE,
    TOK_ALTER,
    TOK_CONCAT,
    TOK_QMARK,

    TOK_CHAR,
    TOK_SPACE,
    TOK_ESCAPE_SEQUENCE
};

// Declare token tags
    /// Tag for left parentheses.
    static const Regex::Token::Tag TAG_LPAREN(TOK_LPAREN, "left parentheses");

    /// Tag for right parentheses.
    static const Regex::Token::Tag TAG_RPAREN(TOK_RPAREN, "right parentheses");

    /// Tag for Kleene Star operator.
    static const Regex::Token::Tag TAG_KLEENE_STAR(TOK_KLEENE, "kleene star");

    /// Tag for Alternation operator.
    static const Regex::Token::Tag TAG_ALTER(TOK_ALTER, "alternation");

    /// Tag for Concatenation operator.
    static const Regex::Token::Tag TAG_CONCAT(TOK_CONCAT, "concatenation");

    /// Tag for Question mark symbol. Also known as, the optional operator.
    static const Regex::Token::Tag TAG_QMARK(TOK_QMARK, "question mark");

    /// Tag for an escape sequence.
    static const Regex::Token::Tag TAG_ESCAPE_SEQUENCE(TOK_ESCAPE_SEQUENCE, "escape sequence");

    /// Tag for a character.
    static const Regex::Token::Tag TAG_CHAR(TOK_CHAR, "character");

    /// Tag for whitespace
    static const Regex::Token::Tag TAG_SPACE(TOK_SPACE, "whitespace");

    /// Tag for eof.
    static const Regex::Token::Tag TAG_EOF(TOK_EOF, "eof");

    /// Tag for "no-tag".
    static const Regex::Token::Tag TAG_NONE(TOK_NONE, "none");

}

#endif //MYREGEX_REGEXPTOKENS_H
