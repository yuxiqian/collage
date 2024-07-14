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
//
// static inline void MY_PUT_MB2(unsigned char *s, uint16_t code) {
//    s[0] = code >> 8;
//    s[1] = code & 0xFF;
// }

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

/* Some typedef to make it easy for C++ to make function pointers */
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


/* See strings/CHARSET_INFO.txt for information about this structure  */
struct MY_COLLATION_HANDLER {
  bool (*init)(CHARSET_INFO *, void *, void *);
  void (*uninit)(CHARSET_INFO *, void *);
  /* Collation routines */
  int (*strnncoll)(const CHARSET_INFO *, const uint8_t *s, size_t slen,
                   const uint8_t *t, size_t tlen, bool t_is_prefix);
  /**
    Compare the two strings under the pad rules given by the collation.

    Thus, for NO PAD collations, this is identical to strnncoll with is_prefix
    set to false. For PAD SPACE collations, the two strings are conceptually
    extended infinitely at the end using space characters (0x20) and then
    compared under the collation's normal comparison rules, so that e.g 'a' is
    equal to 'a '.
  */
  int (*strnncollsp)(const CHARSET_INFO *, const uint8_t *, size_t,
                     const uint8_t *, size_t);
  /**
    Transform the string into a form such that memcmp() between transformed
    strings yields the correct collation order.

    @param [out] dst Buffer for the transformed string.
    @param [out] dstlen Number of bytes available in dstlen.
      Must be even.
    @param num_codepoints Treat the string as if it were of type
      CHAR(num_codepoints). In particular, this means that if the
      collation is a pad collation (pad_attribute is PAD_SPACE) and
      string has fewer than "num_codepoints" codepoints, the string
      will be transformed as if it ended in (num_codepoints-n) extra spaces.
      If the string has more than "num_codepoints" codepoints,
      behavior is undefined; may truncate, may crash, or do something
      else entirely. Note that MY_STRXFRM_PAD_TO_MAXLEN overrides this;
      if it is given for a PAD SPACE collation, this value is taken to be
      effectively infinity.
    @param src The source string, in the required character set
      for the collation.
    @param srclen Number of bytes in src.
    @param flags ORed bitmask of MY_STRXFRM_* flags.

    @return Number of bytes written to dst.
  */
  size_t (*strnxfrm)(const CHARSET_INFO *, uint8_t *dst, size_t dstlen,
                     unsigned num_codepoints, const uint8_t *src, size_t srclen,
                     unsigned flags);

  /**
    Return the maximum number of output bytes needed for strnxfrm()
    to output all weights for any string of the given input length.
    You can use this to e.g. size buffers for sort keys.

    @param num_bytes Number of bytes in the input string. Note that for
      multibyte character sets, this _must_ be a pessimistic estimate,
      ie., one that's cs->mbmaxlen * max_num_codepoints. So for e.g.
      the utf8mb4 string "foo", you will need to give in 12, not 3.
  */
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

  /**
    Compute a sort hash for the given key. This hash must preserve equality
    under the given collation, so that a=b => H(a)=H(b). Note that this hash
    is used for hash-based partitioning (PARTITION KEY), so you cannot change
    it except when writing a new collation; it needs to be unchanged across
    releases, so that the on-disk format does not change. (It is also used
    for testing equality in the MEMORY storage engine.)

    nr1 and nr2 are both in/out parameters. nr1 is the actual hash value;
    nr2 holds extra state between invocations.
  */
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
  const uint8_t *ident_map;                   /* parser internal data */
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

  /**
    If this collation is PAD_SPACE, it collates as if all inputs were
    padded with a given number of spaces at the end (see the "num_codepoints"
    flag to strnxfrm). NO_PAD simply compares unextended strings.

    Note that this is fundamentally about the behavior of coll->strnxfrm.
  */
  enum Pad_attribute pad_attribute;
};
#endif //M_CTYPES_H
