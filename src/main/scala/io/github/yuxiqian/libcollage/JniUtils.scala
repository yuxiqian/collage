package io.github.yuxiqian.libcollage

object JniUtils {

  private def getPlatform: String = {
    System.getProperty("os.name").toLowerCase match {
      case mac if mac.contains("mac")       => "darwin"
      case win if win.contains("win")       => "win32"
      case linux if linux.contains("linux") => "linux"
      case osName =>
        throw new RuntimeException(s"Unknown operating system $osName")
    }
  }

  private def getArchitecture: String = {
    System.getProperty("os.arch").toLowerCase
  }

  def loadLibrary(): Unit = {
    val url = getClass.getResource(
      s"/libcollage/$getPlatform/$getArchitecture/libcollage.dylib"
    )
    System.load(url.getFile)
  }
}
