export LIBRARY_PATH=$LIBRARY_PATH:$(brew --prefix zstd)/lib/
export LIBRARY_PATH=$LIBRARY_PATH:$(brew --prefix zlib)/lib/
export LIBRARY_PATH=$LIBRARY_PATH:$(brew --prefix openssl)/lib/
cmake .. -DJAVA_HOME=$(/usr/libexec/java_home) -DJAVA_INCLUDE_PATH=$(/usr/libexec/java_home)/include -DJAVA_INCLUDE_PATH2=$(/usr/libexec/java_home)/include/darwin -DJAVA_AWT_INCLUDE_PATH=$(/usr/libexec/java_home)/include/usr/libexec/java_home