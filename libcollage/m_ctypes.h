/* Copyright (c) 2000, 2024, Oracle and/or its affiliates.

This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License, version 2.0,
   as published by the Free Software Foundation.

   This program is designed to work with certain software (including
   but not limited to OpenSSL) that is licensed under separate terms,
   as designated in a particular file or component or in included license
   documentation.  The authors of MySQL hereby grant you an additional
   permission to link the program and your derivative works with the
   separately licensed software that they have either included with
   the program or referenced in the documentation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License, version 2.0, for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */

#ifndef M_CTYPES_H
#define M_CTYPES_H

#include <cstdint>

typedef unsigned long my_wc_t;

typedef int myf; /* Type of MyFlags in my_funcs */

struct CHARSET_INFO;

struct MY_UNICASE_CHARACTER {
  uint32_t toupper;
  uint32_t tolower;
  uint32_t sort;
};

struct MY_UNICASE_INFO {
  my_wc_t maxchar;
  const MY_UNICASE_CHARACTER **page;
};

struct MY_UCA_INFO;

struct MY_UNI_CTYPE {
  uint8_t pctype;
  uint8_t *ctype;
};

struct MY_UNI_IDX {
  uint16_t from;
  uint16_t to;
  const uint8_t *tab;
};

enum Pad_attribute { PAD_SPACE, NO_PAD };

typedef int (*my_charset_conv_mb_wc)(const CHARSET_INFO *, my_wc_t *,
                                     const uint8_t *, const uint8_t *);

typedef int (*my_charset_conv_wc_mb)(const CHARSET_INFO *, my_wc_t, uint8_t *,
                                     uint8_t *);

typedef size_t (*my_charset_conv_case)(const CHARSET_INFO *, char *, size_t,
                                       char *, size_t);

struct my_match_t {
  unsigned end;
  unsigned mb_len;
};

struct MY_COLLATION_HANDLER {
  bool (*init)(CHARSET_INFO *, void *, void *);

  void (*uninit)(CHARSET_INFO *, void *);

  int (*strnncoll)(const CHARSET_INFO *, const uint8_t *s, size_t slen,
                   const uint8_t *t, size_t tlen, bool t_is_prefix);

  int (*strnncollsp)(const CHARSET_INFO *, const uint8_t *, size_t,
                     const uint8_t *, size_t);

  size_t (*strnxfrm)(const CHARSET_INFO *, uint8_t *dst, size_t dstlen,
                     unsigned num_codepoints, const uint8_t *src, size_t srclen,
                     unsigned flags);

  size_t (*strnxfrmlen)(const CHARSET_INFO *, size_t num_bytes);

  bool (*like_range)(const CHARSET_INFO *, const char *s, size_t s_length,
                     char w_prefix, char w_one, char w_many, size_t res_length,
                     char *min_str, char *max_str, size_t *min_len,
                     size_t *max_len);

  int (*wildcmp)(const CHARSET_INFO *, const char *str, const char *str_end,
                 const char *wildstr, const char *wildend, int escape,
                 int w_one, int w_many);

  int (*strcasecmp)(const CHARSET_INFO *, const char *, const char *);

  bool (*strstr)(const CHARSET_INFO *, const char *b, size_t b_length,
                 const char *s, size_t s_length, my_match_t *match);

  void (*hash_sort)(const CHARSET_INFO *cs, const uint8_t *key, size_t len,
                    uint64_t *nr1, uint64_t *nr2);

  bool (*propagate)(const CHARSET_INFO *cs, const uint8_t *str, size_t len);
};

struct CHARSET_INFO {
  unsigned number;
  unsigned primary_number;
  unsigned binary_number;
  unsigned state;
  const char *csname;
  const char *m_coll_name;
  const char *comment;
  const char *tailoring;
  struct Coll_param *coll_param;
  const uint8_t *ctype;
  const uint8_t *to_lower;
  const uint8_t *to_upper;
  const uint8_t *sort_order;
  MY_UCA_INFO *uca; /* This can be changed in apply_one_rule() */
  const uint16_t *tab_to_uni;
  const MY_UNI_IDX *tab_from_uni;
  const void *caseinfo;
  const struct lex_state_maps_st *state_maps; /* parser internal data */
  const uint8_t *ident_map; /* parser internal data */
  unsigned strxfrm_multiply;
  uint8_t caseup_multiply;
  uint8_t casedn_multiply;
  unsigned mbminlen;
  unsigned mbmaxlen;
  unsigned mbmaxlenlen;
  my_wc_t min_sort_char;
  my_wc_t max_sort_char; /* For LIKE optimization */
  uint8_t pad_char;
  bool escape_with_backslash_is_dangerous;
  uint8_t levels_for_compare;
  void *cset;
  MY_COLLATION_HANDLER *coll;
  Pad_attribute pad_attribute;
};
#endif //M_CTYPES_H
