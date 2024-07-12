package io.github.yuxiqian.libcollage

object ReflectionUtils {
  def getStaticField[T](clazz: Class[?], fieldName: String): T = {
    val field = clazz.getDeclaredField(fieldName)
    field.setAccessible(true)
    field.get(null).asInstanceOf[T]
  }

  def getField[T](objekt: Object, fieldName: String): T = {
    val field = objekt.getClass.getDeclaredField(fieldName)
    field.setAccessible(true)
    field.get(objekt).asInstanceOf[T]
  }
}
