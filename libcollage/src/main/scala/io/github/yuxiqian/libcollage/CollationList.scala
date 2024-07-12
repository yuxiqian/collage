package io.github.yuxiqian.libcollage

import com.mysql.cj.CharsetMapping

import io.github.yuxiqian.libcollage.ReflectionUtils._
import scala.collection.JavaConverters._

object CollationList {
  val charsetMapping: Map[Int, String] = {
    val fieldGetter = getField[String](_, "charsetName")
    getStaticField(
      classOf[CharsetMapping],
      "COLLATION_INDEX_TO_CHARSET"
    )
      .asInstanceOf[java.util.Map[Integer, String]]
      .asScala
      .map(e => e._1.toInt -> fieldGetter(e._2))
      .toMap
  }

  val collationMapping: Map[Int, String] = {
    getStaticField(
      classOf[CharsetMapping],
      "COLLATION_INDEX_TO_COLLATION_NAME"
    ).asInstanceOf[Array[String]]
      .zipWithIndex
      .filter(_._1 != null)
      .map(e => e._2 -> e._1)
      .toMap
  }

  val collationInverseMapping: Map[String, Int] =
    collationMapping.map(e => e._2 -> e._1)
}
