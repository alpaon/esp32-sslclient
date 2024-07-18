#!/bin/bash

python .pio/libdeps/esp32-s3-devkitc-1/SSLClient/tools/pycert_bearssl/pycert_bearssl.py download -o ./include/certificates.h www.arduino.cc api.device.connect.alpaon.dev www.google.com
# api.device.connect.alpaon.dev www.google.com
sed -i '' '3i\
#include <bearssl.h>' ./include/certificates.h

# openssl s_client -showcerts -connect api.device.connect.alpaon.dev:443 </dev/null > ./include/certs.pem
# python ./scripts/split_certs.py ./include/certs.pem --output-prefix ./include/cert
# python .pio/libdeps/esp32-s3-devkitc-1/SSLClient/tools/pycert_bearssl/pycert_bearssl.py convert -o ./include/certificates.h ./include/cert_*.pem

# openssl s_client -showcerts -connect s3.ap-northeast-2.amazonaws.com:443 </dev/null > ./include/s3_certs.pem
# python ./scripts/split_certs.py ./include/s3_certs.pem --output-prefix ./include/s3_cert
# python .pio/libdeps/esp32-s3-devkitc-1/SSLClient/tools/pycert_bearssl/pycert_bearssl.py convert -o ./include/certificates.h ./include/s3_cert_*.pem

# sed -i '' '3i\
# #include <bearssl.h>' ./include/certificates.h