package io.github.yuxiqian.libcollage

import org.scalatest.funsuite.AnyFunSuite

class CollageTest extends AnyFunSuite {

  test("check collation resource loading") {
    assert(CollationList.collationMapping.size == 286)
    assert(CollationList.charsetMapping.size == 286)
  }

  test("check collation list lookup") {
    assert(Collation.getIndex("utf8mb4_general_ci").contains(45))
    assert(Collation.getName(13).contains("sjis_japanese_ci"))

    assert(Collation.getIndex("not there").isEmpty)
    assert(Collation.getName(11037).isEmpty)
  }

  test("check MySQL charset to Java encoding") {
    assert(CollationList.javaEncodingMapping.size == 41)
    CollationList.charsetMapping.values.foreach(e =>
      assert(CollationList.javaEncodingMapping.contains(e))
    )
  }

  test("check collation lookup") {
    assert(CollationList.collationMapping.keys.map(Collation.get).size == 286)
    assert(
      Collation
        .get("ucs2_icelandic_ci")
        .map(_.toString)
        .contains(
          "Collation{name=ucs2_icelandic_ci, id=129, charset=ucs2, encoding=UTF-16}"
        )
    )
    assert(
      Collation
        .get("utf8mb4_czech_ci")
        .map(_.toString)
        .contains(
          "Collation{name=utf8mb4_czech_ci, id=234, charset=utf8mb4, encoding=UTF8}"
        )
    )
    assert(Collation.get("not there").isEmpty)

    // Copied from https://dev.mysql.com/doc/refman/8.4/en/show-collation.html
    val references =
      """
      |+----------------------------+---------+-----+---------+----------+---------+---------------+
      || Collation                  | Charset | Id  | Default | Compiled | Sortlen | Pad_attribute |
      |+----------------------------+---------+-----+---------+----------+---------+---------------+
      || latin1_german1_ci          | latin1  |  5  |         | Yes      |       1 |               |
      || latin1_swedish_ci          | latin1  |  8  | Yes     | Yes      |       1 |               |
      || latin1_danish_ci           | latin1  | 15  |         | Yes      |       1 |               |
      || latin1_german2_ci          | latin1  | 31  |         | Yes      |       2 |               |
      || latin1_bin                 | latin1  | 47  |         | Yes      |       1 |               |
      || latin1_general_ci          | latin1  | 48  |         | Yes      |       1 |               |
      || latin1_general_cs          | latin1  | 49  |         | Yes      |       1 |               |
      || latin1_spanish_ci          | latin1  | 94  |         | Yes      |       1 |               |
      || utf8mb4_0900_ai_ci         | utf8mb4 | 255 | Yes     | Yes      |       0 | NO PAD        |
      || utf8mb4_0900_as_ci         | utf8mb4 | 305 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_0900_as_cs         | utf8mb4 | 278 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_0900_bin           | utf8mb4 | 309 |         | Yes      |       1 | NO PAD        |
      || utf8mb4_bin                | utf8mb4 |  46 |         | Yes      |       1 | PAD SPACE     |
      || utf8mb4_croatian_ci        | utf8mb4 | 245 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_cs_0900_ai_ci      | utf8mb4 | 266 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_cs_0900_as_cs      | utf8mb4 | 289 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_czech_ci           | utf8mb4 | 234 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_danish_ci          | utf8mb4 | 235 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_da_0900_ai_ci      | utf8mb4 | 267 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_da_0900_as_cs      | utf8mb4 | 290 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_de_pb_0900_ai_ci   | utf8mb4 | 256 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_de_pb_0900_as_cs   | utf8mb4 | 279 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_eo_0900_ai_ci      | utf8mb4 | 273 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_eo_0900_as_cs      | utf8mb4 | 296 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_esperanto_ci       | utf8mb4 | 241 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_estonian_ci        | utf8mb4 | 230 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_es_0900_ai_ci      | utf8mb4 | 263 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_es_0900_as_cs      | utf8mb4 | 286 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_es_trad_0900_ai_ci | utf8mb4 | 270 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_es_trad_0900_as_cs | utf8mb4 | 293 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_et_0900_ai_ci      | utf8mb4 | 262 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_et_0900_as_cs      | utf8mb4 | 285 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_general_ci         | utf8mb4 |  45 |         | Yes      |       1 | PAD SPACE     |
      || utf8mb4_german2_ci         | utf8mb4 | 244 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_hr_0900_ai_ci      | utf8mb4 | 275 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_hr_0900_as_cs      | utf8mb4 | 298 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_hungarian_ci       | utf8mb4 | 242 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_hu_0900_ai_ci      | utf8mb4 | 274 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_hu_0900_as_cs      | utf8mb4 | 297 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_icelandic_ci       | utf8mb4 | 225 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_is_0900_ai_ci      | utf8mb4 | 257 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_is_0900_as_cs      | utf8mb4 | 280 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_ja_0900_as_cs      | utf8mb4 | 303 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_ja_0900_as_cs_ks   | utf8mb4 | 304 |         | Yes      |      24 | NO PAD        |
      || utf8mb4_latvian_ci         | utf8mb4 | 226 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_la_0900_ai_ci      | utf8mb4 | 271 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_la_0900_as_cs      | utf8mb4 | 294 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_lithuanian_ci      | utf8mb4 | 236 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_lt_0900_ai_ci      | utf8mb4 | 268 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_lt_0900_as_cs      | utf8mb4 | 291 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_lv_0900_ai_ci      | utf8mb4 | 258 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_lv_0900_as_cs      | utf8mb4 | 281 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_persian_ci         | utf8mb4 | 240 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_pl_0900_ai_ci      | utf8mb4 | 261 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_pl_0900_as_cs      | utf8mb4 | 284 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_polish_ci          | utf8mb4 | 229 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_romanian_ci        | utf8mb4 | 227 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_roman_ci           | utf8mb4 | 239 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_ro_0900_ai_ci      | utf8mb4 | 259 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_ro_0900_as_cs      | utf8mb4 | 282 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_ru_0900_ai_ci      | utf8mb4 | 306 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_ru_0900_as_cs      | utf8mb4 | 307 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_sinhala_ci         | utf8mb4 | 243 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_sk_0900_ai_ci      | utf8mb4 | 269 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_sk_0900_as_cs      | utf8mb4 | 292 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_slovak_ci          | utf8mb4 | 237 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_slovenian_ci       | utf8mb4 | 228 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_sl_0900_ai_ci      | utf8mb4 | 260 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_sl_0900_as_cs      | utf8mb4 | 283 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_spanish2_ci        | utf8mb4 | 238 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_spanish_ci         | utf8mb4 | 231 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_sv_0900_ai_ci      | utf8mb4 | 264 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_sv_0900_as_cs      | utf8mb4 | 287 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_swedish_ci         | utf8mb4 | 232 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_tr_0900_ai_ci      | utf8mb4 | 265 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_tr_0900_as_cs      | utf8mb4 | 288 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_turkish_ci         | utf8mb4 | 233 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_unicode_520_ci     | utf8mb4 | 246 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_unicode_ci         | utf8mb4 | 224 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_vietnamese_ci      | utf8mb4 | 247 |         | Yes      |       8 | PAD SPACE     |
      || utf8mb4_vi_0900_ai_ci      | utf8mb4 | 277 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_vi_0900_as_cs      | utf8mb4 | 300 |         | Yes      |       0 | NO PAD        |
      || utf8mb4_zh_0900_as_cs      | utf8mb4 | 308 |         | Yes      |       0 | NO PAD        |
      |+----------------------------+---------+-----+---------+----------+---------+---------------+
      |""".stripMargin

    references
      .split("\n")
      .drop(4)
      .filter(s => s.startsWith("|"))
      .foreach(l => {
        val Array(_, collation, charset, id, _*) = {
          l.split("\\|").map(e => e.trim)
        }
        assert(
          Collation
            .get(collation)
            .exists(s =>
              s.toString.contains(
                s"Collation{name=$collation, id=$id, charset=$charset, encoding="
              )
            )
        )
      })
  }

  test("check latin comparison") {
    Collation.get("latin1_general_ci") match {
      case Some(col) =>
        assert(col.compare("Alice", "Bob") < 0)
        assert(col.compare("Dorothy", "Carolle") > 0)
        assert(col.compare("eve", "EVE") == 0)
        assert(col.compare("Foxtrot", "Golg") < 0)
        assert(col.compare("Hotel", "India") < 0)
        assert(col.compare("Juilet", "Kilo") < 0)
        assert(col.compare("Lima", "Mike") < 0)
        assert(col.compare("November", "Oscar") < 0)
        assert(col.compare("Papa", "Quebec") < 0)
        assert(col.compare("Romeo", "Sierra") < 0)
        assert(col.compare("Tango", "Uniform") < 0)
        assert(col.compare("Victor", "Whisky") < 0)
        assert(col.compare("X-ray", "Yankee") < 0)
        assert(col.compare("Zulu", "Alpha") > 0)
      case None => fail("Unrecognized charset")
    }

    Collation.get("latin1_general_cs") match {
      case Some(col) =>
        assert(col.compare("alice", "Alice") > 0)
        assert(col.compare("Alice", "alice") < 0)
        assert(col.compare("Alice", "Alice") == 0)
      case None => fail("Unrecognized charset")
    }

    Collation.get("utf8mb4_icelandic_ci") match {
      case Some(col) =>
        assert(col.compare("Norðurlandanna", "Braggahverfi") > 0)
        assert(col.compare("Reykjavík", "Þannig") < 0)
        assert(col.compare("íSLENSKA", "íslenska") == 0)
      case None => fail("Unrecognized charset")
    }

    Collation.get("not_a_valid_collation") match {
      case Some(_) =>
        fail("Recognized unexpected collation")
      case None => "OK"
    }
  }

  test("check chinese comparison") {
    Collation.get("gbk_chinese_ci") match {
      case Some(col) =>
        assert(col.compare("安", "彼") < 0)
        assert(col.compare("彼", "此") < 0)
        assert(col.compare("此", "等") < 0)
        assert(col.compare("等", "厄") < 0)
        assert(col.compare("厄", "飞") < 0)
        assert(col.compare("飞", "顾") < 0)
        assert(col.compare("凄然", "望江关") < 0)
        assert(col.compare("飞云黯淡", "夕阳间") < 0)
        assert(col.compare("当时宋玉悲感", "当时宋江悲感") > 0)
        assert(col.compare("临水", "登山") > 0)
      case None => fail("Unrecognized charset")
    }
  }

  test("check vietnamese comparison") {
    Collation.get("utf8mb4_vietnamese_ci") match {
      case Some(col) =>
        assert(col.compare("Vương Thúy Kiều", "Kim Trọng") > 0)
        assert(col.compare("Trăm năm", "trong cõi người ta") < 0)
        assert(col.compare("Chữ tài", "chữ mệnh") > 0)
        assert(col.compare("khéo là", "ghét nhau") > 0)
        assert(col.compare("Trải qua một", "cuộc bể dâu") > 0)
        assert(col.compare("Những điều trông thấy", "mà đau đớn lòng") > 0)
        assert(col.compare("Lạ gì bỉ sắc", "tư phong") < 0)
        assert(col.compare("Trời xanh quen thói", "má hồng đánh ghen") > 0)
        assert(
          col.compare("Đoạn Trường Tân Thanh", "ĐOẠN TRƯỜNG TÂN THANH") == 0
        )
      case None => fail("Unrecognized charset")
    }
  }
}
